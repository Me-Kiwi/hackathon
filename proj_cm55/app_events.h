#ifndef _APP_EVENTS_H__
#define _APP_EVENTS_H__

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "cybsp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cyabs_rtos.h"
#include "cyabs_rtos_impl.h"
#include "retarget_io_init.h"
#include "playback_config.h"
#include "audio_playback.h"

/*******************************************************************************
* Global Variables
*******************************************************************************/
extern TaskHandle_t rtos_cm55_gfx_task_handle;
extern TaskHandle_t cm55_audio_task_handle;
/*******************************************************************************
* Macros
*******************************************************************************/
#define GPU_INT_PRIORITY                    (3U)
#define DC_INT_PRIORITY                     (3U)
/*******************************************************************************
* Functions Prototypes
*******************************************************************************/
int tasks_init(void);
void cm55_gfx_task(void *arg);
void voice_assistant_task(void * arg);
void cm55_audio_task(void *arg);


#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif 

/* [] END OF FILE */