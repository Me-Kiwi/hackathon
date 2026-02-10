/*
 * playback_config.h
 */

#ifndef SHARED_INCLUDE_PLAYBACK_CONFIG_H_
#define SHARED_INCLUDE_PLAYBACK_CONFIG_H_

#define USE_PSRAM_BUFFER					    (0U)

#define AUDIO_PLAYBACK_FROM_FLASH		        (1U)
#define AUDIO_PLAYBACK_FROM_FLASH_VIA_PSRAM     (0U)

#if AUDIO_PLAYBACK_FROM_SD_CARD_VIA_PSRAM
    #define INPUT_WAV_FILE                      "audio.wav"  /* 24 kHz, 1 channel */
#endif
#define INPUT_WAV_NUM_CHANNELS                  (1u)
#define PLAYBACK_SAMPLING_RATE                  (24000UL)
#define PLAYBACK_VOLUME                         (110u) /* Valid range: 0 - 127 */


#endif /* SHARED_INCLUDE_PLAYBACK_CONFIG_H_ */
