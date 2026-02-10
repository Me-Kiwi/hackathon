/******************************************************************************
* File Name : audio_playback.h
*
* Description : Header file for i2s containing  function ptototypes.
********************************************************************************
* $ Copyright 2025-YEAR Cypress Semiconductor $
*******************************************************************************/


#ifndef AUDIO_PLAYBACK_H__
#define AUDIO_PLAYBACK_H__


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "cy_pdl.h"
#include "mtb_hal.h"
#include "cybsp.h"

#include "FreeRTOS.h"
#include "task.h"
#include "cyabs_rtos.h"
#include "cybsp_types.h"
#include "app_i2s.h"
#include "playback_config.h"

/*******************************************************************************
* Macros
*******************************************************************************/
#define WAV_HEADER_SIZE_BYTES               (44)
#define AUDIO_CHUNK_SIZE                    (I2S_QUEUE_TX_SAMPLES_PER_CH * INPUT_WAV_NUM_CHANNELS * sizeof(int16_t)) /* 128 bytes */

#define WAV_READ_SIZE_BYTES                 (AUDIO_CHUNK_SIZE * 64)
#define CIRCULAR_BUFFER_SIZE                (WAV_READ_SIZE_BYTES * 4)

#define MAX_AUDIO_PSRAM_BUFFER_SIZE         (1024 * 1024 * 10)

#define AUDIO_PLAYBACK_DELAY_MS             (280UL)

/*******************************************************************************
* Data structure and enumeration
********************************************************************************/
typedef enum {
    AUDIO_STATE_STOPPED,
    AUDIO_STATE_PLAYING,
    AUDIO_STATE_PAUSED,
}audio_state_t;

static audio_state_t audio_state = AUDIO_STATE_STOPPED;
void audio_play(void);
void audio_pause(void);
void audio_stop(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AUDIO_PLAYBACK_H__ */
/* [] END OF FILE */
