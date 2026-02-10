/******************************************************************************
* File Name : i2s_playback.c
*
* Description : Source file for Audio Playback via I2S.
********************************************************************************
* $ Copyright 2025-YEAR Cypress Semiconductor $
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "app_i2s.h"
#include "audio_playback.h"
#include "FreeRTOS.h"
#include "semphr.h"

/*******************************************************************************
* Global Variables
*******************************************************************************/
mtb_hal_i2c_t MW_I2C_hal_obj;

// extern cy_stc_scb_i2c_context_t disp_i2c_controller_context;
cy_stc_scb_i2c_context_t disp_i2c_controller_context;

mtb_hal_i2c_cfg_t i2c_config = 
{
    .is_target = false,
    .address = I2C_ADDRESS,
    .frequency_hz = I2C_FREQUENCY_HZ,
    .address_mask = MTB_HAL_I2C_DEFAULT_ADDR_MASK,
    .enable_address_callback = false
};

const cy_stc_sysint_t i2s_isr_txcfg = {
    .intrSrc = (IRQn_Type) tdm_0_interrupts_tx_0_IRQn,
    .intrPriority = I2S_INTR_PRIORITY,
};

/* Audio playback tracking variables */
uint32_t i2s_txcount = 0;
volatile bool i2s_flag = false;

bool i2s_skip_frame = false;
bool i2s_initialized = false;

static volatile bool i2s_q_init_complete = false;
static volatile bool i2s_tx_active = false;

QueueHandle_t i2s_playback_task_q;

static i2s_playback_q_data_t i2s_playback_q_data;

uint32_t i2s_playback_sampling_rate_hz = SAMPLING_RATE_48kHz;

const uint8_t volume_level[NUM_VOLUME_STEPS] =
{
    MIN_VOLUME,     /*   0%  */
    50,             /*  20%  */
    75,             /*  40%  */
    90,             /*  60%  */
    102,            /*  80%  */
    MAX_VOLUME,     /* 100%  */
};

uint8_t volume_level_index = DEFAULT_VOLUME_INDEX;

static uint32_t start_time_ms = 0;
static uint32_t end_time_ms = 0;


/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void app_i2s_init(void);
static void app_i2s_deinit(void);
static void app_i2s_enable(void);
static void app_i2s_disable(void);
static void app_i2s_activate(void);
static void app_i2s_deactivate(void);

static void i2s_tx_interrupt_handler(void);

static void app_tlv_codec_init(uint32_t sampling_rate_hz);
static void app_tlv_codec_deinit(void);
static void tlv_codec_i2c_init(void);
static void tlv_codec_i2c_deinit(void);
static void configure_i2s_clocks(uint32_t sampling_rate_hz);

static void handle_notification(void);




/******************************************************************************
* Function Definitions
*******************************************************************************/

/*******************************************************************************
 * Function Name: app_i2s_init
 ********************************************************************************
* Summary:
*  Initialize I2S interrupt and I2S (TDM) block.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void app_i2s_init(void)
{
    /* Initialize the I2S interrupt */
    Cy_SysInt_Init(&i2s_isr_txcfg, i2s_tx_interrupt_handler);

   /* Initialize the I2S */
    cy_en_tdm_status_t volatile return_status = Cy_AudioTDM_Init(TDM_STRUCT0, &CYBSP_TDM_CONTROLLER_0_config);
    if (CY_TDM_SUCCESS != return_status)
    {
        printf(">>> Error: I2S init failed with error code: 0x%0lX\n", (unsigned long)return_status);
        CY_ASSERT(0);
    }
}

/******************************************************************************
* Function Name: app_i2s_deinit
*******************************************************************************
* Summary:
*   De-initialize I2S (TDM) block.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
static void app_i2s_deinit(void)
{
    /* De-initialize the I2S */
    Cy_AudioTDM_DeInit(TDM_STRUCT0);
}

/*******************************************************************************
 * Function Name: app_tlv_codec_init
 ********************************************************************************
* Summary:
*  Initializes the I2C and TLV codec.
*
* Parameters:
*  sampling_rate_hz: I2S playback sampling rate in Hz
*
* Return:
*  None
*
*******************************************************************************/
static void app_tlv_codec_init(uint32_t sampling_rate_hz)
{
    uint32_t mclk_hz = 0;

    if (SAMPLING_RATE_16kHz == sampling_rate_hz)
    {
        mclk_hz = I2S_16KHZ_MCLK_HZ;
    }
    else if (SAMPLING_RATE_24kHz == sampling_rate_hz)
    {
        mclk_hz = I2S_24KHZ_MCLK_HZ;
    }
    else
    {
        mclk_hz = I2S_48KHZ_MCLK_HZ;
    }

    vTaskDelay(pdMS_TO_TICKS(SYSCLK_DIV_CHANGE_WAIT_TIME_MS));


    /* Initialize I2C used to configure TLV codec */
    tlv_codec_i2c_init();

    /* TLV codec/ MW init */
    mtb_tlv320dac3100_init(&MW_I2C_hal_obj);

    /* Configure internal clock dividers to achieve desired sample rate */
    mtb_tlv320dac3100_configure_clocking(mclk_hz,
                                         (mtb_tlv320dac3100_dac_sample_rate_t)sampling_rate_hz,
                                         I2S_WORD_LENGTH);

    /* Activate TLV320DAC3100 */
    mtb_tlv320dac3100_activate();
}

/******************************************************************************
* Function Name: app_tlv_codec_deinit
*******************************************************************************
* Summary:
*   Initializes the I2C and TLV codec.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
static void app_tlv_codec_deinit(void)
{
    mtb_tlv320dac3100_deactivate();
    mtb_tlv320dac3100_free();
    // tlv_codec_i2c_deinit();
}

/*******************************************************************************
 * Function Name: app_i2s_activate
 ********************************************************************************
* Summary: Activate I2S Tx interrupt
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void app_i2s_activate(void)
{
    /* Activate and enable I2S TX interrupts */
    NVIC_EnableIRQ(i2s_isr_txcfg.intrSrc);
    Cy_AudioTDM_ActivateTx(TDM_STRUCT0_TX);
}

/******************************************************************************
* Function Name: app_i2s_deactivate
*******************************************************************************
* Summary:
*   Disable the I2S interrupt and clear TX FIFO and disable the I2S
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
static void app_i2s_deactivate(void)
{
    /* De-initialize the I2S interrupt */
    NVIC_DisableIRQ(i2s_isr_txcfg.intrSrc);

    /* There is no API to clear the HW FIFO. Disabling and enabling the TX
     * will clear the FIFO as a side effect.
     */
    Cy_AudioTDM_DeActivateTx(TDM_STRUCT0_TX);
    Cy_AudioI2S_DisableTx(TDM_STRUCT0_TX);
    Cy_AudioI2S_EnableTx(TDM_STRUCT0_TX);
    Cy_AudioTDM_DeActivateTx(TDM_STRUCT0_TX);
    Cy_AudioI2S_DisableTx(TDM_STRUCT0_TX);
}

/*******************************************************************************
* Function Name: app_i2s_enable
********************************************************************************
* Summary:
*   Enable I2S TX, its interrupts and fill the FIFO with zeros to start TX.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void app_i2s_enable(void)
{
    /* Enable the I2S TX interface */
    Cy_AudioTDM_EnableTx(TDM_STRUCT0_TX);

    /* Clear TX interrupts */
    Cy_AudioTDM_ClearTxInterrupt(TDM_STRUCT0_TX, CY_TDM_INTR_TX_MASK);
    Cy_AudioTDM_SetTxInterruptMask(TDM_STRUCT0_TX, CY_TDM_INTR_TX_MASK);

    /* Fill TX FIFO with zeros to start the transmission */
    for(uint32_t i = 0; i < (HW_FIFO_SIZE / 2); i++)
    {
        /* Write data in FIFO */
        Cy_AudioTDM_WriteTxData(TDM0_TDM_STRUCT0_TDM_TX_STRUCT, 0UL);
        Cy_AudioTDM_WriteTxData(TDM0_TDM_STRUCT0_TDM_TX_STRUCT, 0UL);
    }
}

/******************************************************************************
* Function Name: app_i2s_disable
*******************************************************************************
* Summary:
*   Disable I2S TX and interrupts.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
static void app_i2s_disable(void)
{
    /* Enable the I2S TX interface */
    Cy_AudioTDM_DisableTx(TDM_STRUCT0_TX);

    /* Clear TX interrupts */
    Cy_AudioTDM_ClearTxInterrupt(TDM_STRUCT0_TX, CY_TDM_INTR_TX_MASK);
    Cy_AudioTDM_ClearTxTriggerInterruptMask(TDM_STRUCT0_TX);
}

/*******************************************************************************
* Function Name: tlv_codec_i2c_init
********************************************************************************
* Summary:
*   Initilaize the I2C for the TLV codec.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
static void tlv_codec_i2c_init(void)
{
    cy_en_scb_i2c_status_t result;
    cy_rslt_t hal_result;

    /* Initialize and enable the I2C in controller mode. */
    result = Cy_SCB_I2C_Init(CYBSP_I2C_CONTROLLER_HW, &CYBSP_I2C_CONTROLLER_config, &disp_i2c_controller_context);
    if (CY_RSLT_SUCCESS != result)
    {
        printf(">>> Error: I2C initilization failed with error code: 0x%0lX\n", (unsigned long)result);
        CY_ASSERT(0);
    }

    /* Enable I2C hardware. */
    Cy_SCB_I2C_Enable(CYBSP_I2C_CONTROLLER_HW);


    /* I2C HAL init */
    hal_result = mtb_hal_i2c_setup(&MW_I2C_hal_obj, &CYBSP_I2C_CONTROLLER_hal_config, &disp_i2c_controller_context, NULL);
    if (CY_RSLT_SUCCESS != hal_result)
    {
        printf(">>> Error: I2C HAL setup failed with error code: 0x%0lX\n", (unsigned long)hal_result);
        CY_ASSERT(0);
    }

    /* Configure the I2C block. Master/Slave specific functions only work when the block is configured to desired mode */
    hal_result = mtb_hal_i2c_configure(&MW_I2C_hal_obj, &i2c_config);
    if (CY_RSLT_SUCCESS != hal_result)
    {
        printf(">>> Error: I2C HAL configure failed with error code: 0x%0lX\n", (unsigned long)hal_result);
        CY_ASSERT(0);
    }
}

/******************************************************************************
* Function Name: tlv_codec_i2c_deinit
*******************************************************************************
* Summary:
*   De-initilaize the I2C used by the TLV codec.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
static void tlv_codec_i2c_deinit(void)
{
    /* Disable and deinitialize the I2C resource */
    Cy_SCB_I2C_Disable(CYBSP_I2C_CONTROLLER_HW, &disp_i2c_controller_context);
    Cy_SCB_I2C_DeInit(CYBSP_I2C_CONTROLLER_HW);
}

/*******************************************************************************
* Function Name: i2s_init
********************************************************************************
* Summary:
* Initialize I2S block and Hardware codec.
*
* Parameters:
* None
*
* Return:
*  None
*
*******************************************************************************/
void i2s_init(uint32_t sampling_rate_hz)
{
    /* Create an RTOS queue for I2S if not created already */
    if (!i2s_q_init_complete)
    {
        /* Create a send message queue to communicate audio data to i2s playback task */
        i2s_playback_task_q = xQueueCreate(I2S_PLAYBACK_TASK_QUEUE_LENGTH,
                                        sizeof(i2s_playback_q_data_t));
        i2s_q_init_complete = true;
    }

    if (i2s_initialized)
    {
        if (i2s_tx_active)
        {
            /* Stop I2S if it is already active */
            stop_i2s();
        }

        /* If I2S is already initialized, de-initialize it first */
        i2s_deinit();
    }

#if (PLAYBACK_SAMPLING_RATE == SAMPLING_RATE_16kHz)
        Cy_SysClk_PeriPclkDisableDivider((en_clk_dst_t)CYBSP_TDM_CONTROLLER_0_CLK_DIV_GRP_NUM,
                                            CY_SYSCLK_DIV_16_5_BIT, 0U);
        Cy_SysClk_PeriPclkSetFracDivider((en_clk_dst_t)CYBSP_TDM_CONTROLLER_0_CLK_DIV_GRP_NUM,
                                            CY_SYSCLK_DIV_16_5_BIT, 0U,
                                            I2S_CLK_DIV_16KHZ - 1, 0U);
        Cy_SysClk_PeriPclkEnableDivider((en_clk_dst_t)CYBSP_TDM_CONTROLLER_0_CLK_DIV_GRP_NUM,
                                            CY_SYSCLK_DIV_16_5_BIT, 0U);
#elif (PLAYBACK_SAMPLING_RATE == SAMPLING_RATE_24kHz)
        Cy_SysClk_PeriPclkDisableDivider((en_clk_dst_t)CYBSP_TDM_CONTROLLER_0_CLK_DIV_GRP_NUM,
                                            CY_SYSCLK_DIV_16_5_BIT, 0U);
        Cy_SysClk_PeriPclkSetFracDivider((en_clk_dst_t)CYBSP_TDM_CONTROLLER_0_CLK_DIV_GRP_NUM,
                                            CY_SYSCLK_DIV_16_5_BIT, 0U,
                                            I2S_CLK_DIV_24KHZ - 1, 0U);
        Cy_SysClk_PeriPclkEnableDivider((en_clk_dst_t)CYBSP_TDM_CONTROLLER_0_CLK_DIV_GRP_NUM,
                                            CY_SYSCLK_DIV_16_5_BIT, 0U);
#elif (PLAYBACK_SAMPLING_RATE == SAMPLING_RATE_48kHz)
        Cy_SysClk_PeriPclkDisableDivider((en_clk_dst_t)CYBSP_TDM_CONTROLLER_0_CLK_DIV_GRP_NUM,
                                            CY_SYSCLK_DIV_16_5_BIT, 0U);
        Cy_SysClk_PeriPclkSetFracDivider((en_clk_dst_t)CYBSP_TDM_CONTROLLER_0_CLK_DIV_GRP_NUM,
                                            CY_SYSCLK_DIV_16_5_BIT, 0U,
                                            I2S_CLK_DIV_48KHZ - 1, 0U);
        Cy_SysClk_PeriPclkEnableDivider((en_clk_dst_t)CYBSP_TDM_CONTROLLER_0_CLK_DIV_GRP_NUM,
                                            CY_SYSCLK_DIV_16_5_BIT, 0U);
#endif /* PLAYBACK_SAMPLING_RATE */

    app_i2s_init();

    /* TLV codec initiailization */
    app_tlv_codec_init(sampling_rate_hz);

    /* Set the appropriate flags */
    i2s_initialized = true;

    mtb_tlv320dac3100_adjust_speaker_output_volume(DEFAULT_VOLUME);
}

/*******************************************************************************
* Function Name: i2s_deinit
********************************************************************************
* Summary:
* Set a I2S deinitialize flag and clear the queues and task notifcations.
*
* Parameters:
* None
*
* Return:
*  None
*
*******************************************************************************/
void i2s_deinit(void)
{
    if (i2s_initialized)
    {
        if (i2s_tx_active)
        {
            /* Stop I2S if it is already active */
            stop_i2s();
        }

        /* TLV codec de-initialization */
        app_tlv_codec_deinit();

        /* I2S de-initialization */
        app_i2s_deinit();

        i2s_initialized = false;
    }

    if (i2s_q_init_complete)
    {
        xQueueReset(i2s_playback_task_q);
    }
}

/******************************************************************************
* Function Name: start_i2s
*******************************************************************************
* Summary:
*   Function that enables and activates the I2S transmission (TX) if I2S block
*   is initialized and sets the I2S active flag to true.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void start_i2s(void)
{
    if (i2s_initialized)
    {
        if (!i2s_tx_active)
        {
            app_i2s_enable();
            vTaskDelay(I2S_OPERATION_DELAY_TICKS);
            app_i2s_activate();
            i2s_tx_active = true;
        }
    }
}

/******************************************************************************
* Function Name: stop_i2s
*******************************************************************************
* Summary:
*   Function that stops and clears the I2S transmission (TX) and also clears
*   any existing data in the I2S queues and sets the I2S active flag to false.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void stop_i2s(void)
{
    if (i2s_initialized)
    {
        if (i2s_tx_active)
        {
            app_i2s_deactivate();
            app_i2s_disable();

            i2s_tx_active = false;

            xQueueReset(i2s_playback_task_q);
            
        }
    }
}


/******************************************************************************
* Function Name: i2s_tx_interrupt_handler
*******************************************************************************
* Summary:
*   I2S TX interrupt handler function.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
static void i2s_tx_interrupt_handler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    int16_t* i2s_tx_buffer = NULL;
    uint32_t i2s_tx_num_samples = 0;
    uint32_t i2s_data = 0;
    uint32_t i, intr_status;
    bool send_zeros = true;

    /* Get interrupt status and check for tigger interrupt and errors */
    intr_status = Cy_AudioTDM_GetTxInterruptStatusMasked(TDM_STRUCT0_TX);

    if(CY_TDM_INTR_TX_FIFO_TRIGGER & intr_status)
    {
        if(i2s_tx_active)
        {
// Cy_SCB_UART_Put(CYBSP_DEBUG_UART_HW, '.');
            /* Receive the data from the queue and process it. */
            if (pdTRUE == xQueueReceiveFromISR(i2s_playback_task_q,
                                               &i2s_playback_q_data,
                                               &xHigherPriorityTaskWoken))
            {
                send_zeros = false;
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

                i2s_tx_num_samples = (i2s_playback_q_data.data_len / sizeof(int16_t));
                i2s_tx_buffer = (int16_t *) i2s_playback_q_data.data;

                if ( ((HW_FIFO_SIZE / 2) * i2s_playback_q_data.num_channels) != i2s_tx_num_samples )
                {
                    printf(">> Error: I2S TX data size mismatch !!\n");
                    CY_ASSERT(0);
                }

                if (NULL == i2s_tx_buffer)
                {
                    printf(">> Error: I2S TX buffer is NULL !!\n");
                    CY_ASSERT(0);
                }

                for (i = 0; i < HW_FIFO_SIZE; i++)
                {
                    i2s_data = (uint32_t)(*i2s_tx_buffer++);
                    Cy_AudioTDM_WriteTxData(TDM_STRUCT0_TX, i2s_data);

                    /* If the input data is mono channel, duplicate the samples for
                     * stereo I2S playback
                     */
                    if (CHANNELS_MONO == i2s_playback_q_data.num_channels)
                    {
                        Cy_AudioTDM_WriteTxData(TDM_STRUCT0_TX, i2s_data);
                        i++;
                    }
                }

                if (i2s_playback_q_data.send_trigger)
                {
                    handle_notification();
                }
            }
        }

        if (send_zeros)
        {
            for (i = 0; i < HW_FIFO_SIZE; i++)
            {
                Cy_AudioTDM_WriteTxData(TDM_STRUCT0_TX, 0UL);
            }
        }
    }
    else if(CY_TDM_INTR_TX_FIFO_UNDERFLOW & intr_status)
    {
        printf(">> Error: I2S transmit underflowed !!\r\n");
    }

    /* Clear all TX I2S Interrupt */
    Cy_AudioTDM_ClearTxInterrupt(TDM_STRUCT0_TX, CY_TDM_INTR_TX_MASK);
}

/******************************************************************************
* Function Name: handle_notification
*******************************************************************************
* Summary:
*   Function to handle queue transmissions from the I2S ISR context.
*   Notifies the cm55_audio_task to provide more audio data.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
static void handle_notification(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    /* Notify the audio task that more audio data is needed */
    if (cm55_audio_task_handle != NULL)
    {
        // Cy_SCB_UART_Put(CYBSP_DEBUG_UART_HW, '$');
        xTaskNotifyFromISR(cm55_audio_task_handle, 0, eNoAction,
                                               &xHigherPriorityTaskWoken);
        
        /* Debug: Uncomment the line below for debugging notification issues */
        /* if (result != pdTRUE) printf(">>> Error: Task notification failed!\r\n"); */
    }
    
    /* Yield to higher priority task if necessary */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/*******************************************************************************
* Function Name: i2s_playback_volume_control
********************************************************************************
* Summary:
*  Controls i2s playback volume
*
* Parameters:
*  volume: value between 0 to 127
*
* Return:
*  None
*******************************************************************************/
void i2s_playback_volume_control(uint8_t volume)
{
    if(i2s_initialized)
    {
        mtb_tlv320dac3100_adjust_speaker_output_volume(volume);
    }
    else
    {
#ifdef AUDIO_OUT
        i2s_init(i2s_playback_sampling_rate_hz);
#endif /* AUDIO_OUT */
        mtb_tlv320dac3100_adjust_speaker_output_volume(volume);
#ifdef AUDIO_OUT
        i2s_deinit();
#endif /* AUDIO_OUT */
    }
}

/*******************************************************************************
* Function Name: convert_mono_to_stereo
********************************************************************************
* Summary:
* Converts mono audio data into stereo by duplicating left channel for right channel.
*
* Parameters:
*   mono_data: Pointer to mono audio data
*   mono_data_num_samples: Number of mono samples
*   stereo_data: Pointer to stereo audio data
*
* Return:
*  None
*
*******************************************************************************/
void convert_mono_to_stereo(int16_t *mono_data, uint32_t mono_data_num_samples,
                            int16_t *stereo_data)
{
    for (uint32_t i = 0; i < mono_data_num_samples; i++)
    {
        *stereo_data++ = *mono_data;  /* Copy the mono sample to the left channel */
        *stereo_data++ = *mono_data;  /* Copy the same mono sample to the right channel */
        mono_data++;                  /* Move to the next mono sample */
    }
}

/*******************************************************************************
* Function Name: convert_stereo_to_mono
********************************************************************************
* Summary:
* Converts stereo audio data into mono by extracting only the left channel data.
*
* Parameters:
*   stereo_data: Pointer to stereo audio data
*   stereo_data_num_samples: Number of stereo samples
*   mono_data: Pointer to mono audio data
*
* Return:
*  None
*
*******************************************************************************/
void convert_stereo_to_mono(int16_t *stereo_data, uint32_t stereo_data_num_samples,
                            int16_t *mono_data)
{
    int32_t avg_mono_data = 0;
    for (uint32_t i = 0; i < stereo_data_num_samples; i += 2)
    {
        avg_mono_data = *stereo_data;
        stereo_data++;
        avg_mono_data += *stereo_data;
        stereo_data++;
        avg_mono_data >>= 1;
        *mono_data++ = (int16_t) avg_mono_data;
    }
}


/* [] END OF FILE */
