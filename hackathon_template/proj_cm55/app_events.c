/*******************************************************************************
* Header Files
*******************************************************************************/
#include "app_events.h"

/*******************************************************************************
* Macros
*******************************************************************************/
#define GFX_TASK_NAME                       ("CM55 Gfx Task")
#define GFX_TASK_STACK_SIZE                 (configMINIMAL_STACK_SIZE * 20)
#define GFX_TASK_PRIORITY                   (configMAX_PRIORITIES - 1)

#define VOICE_ASSISTANT_TASK_NAME               ("voice-assistant task")
#define VOICE_ASSISTANT_TASK_STACK_SIZE          (configMINIMAL_STACK_SIZE * 32)
#define VOICE_ASSISTANT_TASK_PRIORITY           (configMAX_PRIORITIES - 2)

#define AUDIO_PLAYBACK_TASK_NAME            ("CM55 Audio Task")
#define AUDIO_PLAYBACK_TASK_STACK_SIZE      (configMINIMAL_STACK_SIZE * 4)
#define AUDIO_PLAYBACK_TASK_PRIORITY        (configMAX_PRIORITIES - 3)


TaskHandle_t rtos_cm55_gfx_task_handle = NULL;

int tasks_init(void){

    BaseType_t task_return = pdPASS;

    if( xTaskCreate(cm55_gfx_task, GFX_TASK_NAME,
                              GFX_TASK_STACK_SIZE, NULL,
                              GFX_TASK_PRIORITY, &rtos_cm55_gfx_task_handle) != task_return)
                              return pdFAIL;


    if( xTaskCreate(cm55_audio_task, AUDIO_PLAYBACK_TASK_NAME,
                              AUDIO_PLAYBACK_TASK_STACK_SIZE, NULL,
                              AUDIO_PLAYBACK_TASK_PRIORITY, &cm55_audio_task_handle) != task_return)
                              return pdFAIL;

   if( xTaskCreate(voice_assistant_task, VOICE_ASSISTANT_TASK_NAME, 
                              VOICE_ASSISTANT_TASK_STACK_SIZE, NULL, 
                              VOICE_ASSISTANT_TASK_PRIORITY, NULL) != task_return)
                              return pdFAIL;
    
    return task_return;
}