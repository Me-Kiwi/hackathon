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
#include "cybsp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "app_i2s.h"
#include "audio_playback.h"
#include "playback_config.h"

#if (AUDIO_PLAYBACK_FROM_FLASH || AUDIO_PLAYBACK_FROM_FLASH_VIA_PSRAM)
#include "psoc_edge_intro_audio.h"
#endif /* (AUDIO_PLAYBACK_FROM_FLASH || AUDIO_PLAYBACK_FROM_FLASH_VIA_PSRAM) */

/*******************************************************************************
* Global Variables
*******************************************************************************/
// static uint8_t wav_data_buffer[CIRCULAR_BUFFER_SIZE] __attribute__ ((section(".cy_socmem_data"), aligned(4))) = {0};
// static uint8_t wav_data_buffer[CIRCULAR_BUFFER_SIZE] __attribute__ ((section(".cy_itcm"), aligned(4))) = {0};
// static uint8_t wav_data_buffer[CIRCULAR_BUFFER_SIZE] __attribute__ ((section(".cy_socmem_code"), aligned(8))) = {0};
static uint8_t wav_data_buffer[CIRCULAR_BUFFER_SIZE] __attribute__ ((aligned(32))) = {0};
static uint32_t wav_buffer_index = 0;
static uint8_t *wav_data_ptr = NULL;
TaskHandle_t cm55_audio_task_handle;

static uint8_t i2s_playback_buffer_count = 2;
static bool wav_header_skipped = false;
static int32_t bytes_remaining = 0;
// #if AUDIO_PLAYBACK_FROM_FLASH_VIA_PSRAM || AUDIO_PLAYBACK_FROM_SD_CARD_VIA_PSRAM
// static uint8_t psram_audio_buffer[MAX_AUDIO_PSRAM_BUFFER_SIZE] __attribute__ ((section(".cy_xip"), aligned(32))); // 10 MB for Audio data
// #endif /* AUDIO_PLAYBACK_FROM_SD_CARD_VIA_PSRAM */



/******************************************************************************
* Function Prototypes
*******************************************************************************/



/******************************************************************************
* Function Definitions
*******************************************************************************/

void cm55_audio_task(void *arg)
{
    i2s_playback_q_data_t i2s_queue_data;

    while (1)
    {
        if (audio_state == AUDIO_STATE_PLAYING)
        {
            if (bytes_remaining <= 0)
            {
                printf("Audio Playback Done!\r\n");
                audio_state = AUDIO_STATE_STOPPED;
                i2s_deinit();
                continue;
            }

            int32_t chunk_bytes = (bytes_remaining >= WAV_READ_SIZE_BYTES) ? WAV_READ_SIZE_BYTES : bytes_remaining;

            for (int32_t i = 0; i < chunk_bytes;)
            {
                i2s_queue_data.data_len = AUDIO_CHUNK_SIZE;
                i2s_queue_data.data = (int16_t*)&(wav_data_ptr[wav_buffer_index + i]);
                i2s_queue_data.num_channels = INPUT_WAV_NUM_CHANNELS;
                i2s_queue_data.send_trigger = (i >= (chunk_bytes - AUDIO_CHUNK_SIZE));
                i += AUDIO_CHUNK_SIZE;

                if (pdTRUE != xQueueSend(i2s_playback_task_q, &i2s_queue_data, pdMS_TO_TICKS(10)))
                {
                    printf("Warning: Failed to send audio data to I2S queue\r\n");
                }
            }

            wav_buffer_index += chunk_bytes;
            bytes_remaining -= chunk_bytes;

            if (i2s_playback_buffer_count > 0)
            {
                i2s_playback_buffer_count--;
                vTaskDelay(pdMS_TO_TICKS(5));
            }
            else
            {
                xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
            }
        }
        else if (audio_state == AUDIO_STATE_PAUSED)
        {
           
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        else if (audio_state == AUDIO_STATE_STOPPED)
        {
            
            vTaskDelay(pdMS_TO_TICKS(200));
        }
    }
}


void audio_play(void)
{
    if (audio_state == AUDIO_STATE_STOPPED)
    {
        printf("Starting audio...\r\n");
        wav_data_ptr = psoc_edge_intro_audio;
        wav_buffer_index = WAV_HEADER_SIZE_BYTES;
        bytes_remaining = psoc_edge_intro_audio_size - WAV_HEADER_SIZE_BYTES;

        i2s_init(PLAYBACK_SAMPLING_RATE);
        start_i2s();
        vTaskDelay(pdMS_TO_TICKS(AUDIO_PLAYBACK_DELAY_MS));
    }

    audio_state = AUDIO_STATE_PLAYING;
}

void audio_pause(void)
{
    if (audio_state == AUDIO_STATE_PLAYING)
    {
        printf("Audio paused\r\n");
        audio_state = AUDIO_STATE_PAUSED;
    }
}

void audio_stop(void)
{
    if (audio_state != AUDIO_STATE_STOPPED)
    {
        printf("Audio stopped\r\n");
        audio_state = AUDIO_STATE_STOPPED;
        stop_i2s();
        i2s_deinit();
    }
}



/* [] END OF FILE */
