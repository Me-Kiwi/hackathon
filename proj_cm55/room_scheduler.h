/*******************************************************************************
* File Name: room_scheduler.h
*
* Description: Header file for room scheduling system logic
*
*******************************************************************************/

#ifndef ROOM_SCHEDULER_H
#define ROOM_SCHEDULER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
* Constants
*******************************************************************************/
#define INITIAL_TIMER_SECONDS       30
#define EXTEND_TIMER_SECONDS        30
#define INITIAL_TEMPERATURE         26
#define MIN_TEMPERATURE             16
#define MAX_TEMPERATURE             30

/*******************************************************************************
* Global Variables
*******************************************************************************/
extern int32_t room_timer_seconds;
extern int32_t room_temperature;
extern bool timer_active;
extern bool new_meeting_flag;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void room_scheduler_init(void);
void room_scheduler_deinit(void);
void room_scheduler_start(void);
void room_scheduler_stop(void);
void room_scheduler_extend(void);
void room_scheduler_update_timer(lv_timer_t * timer);
void room_scheduler_increase_temperature(void);
void room_scheduler_decrease_temperature(void);
void room_scheduler_update_display(void);

#ifdef __cplusplus
}
#endif

#endif /* ROOM_SCHEDULER_H */
