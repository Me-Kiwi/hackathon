/*******************************************************************************
* File Name: room_scheduler.c
*
* Description: Implementation of room scheduling system logic
*
*******************************************************************************/

#include "room_scheduler.h"
#include "ui/ui.h"
#include "ui/screens/ui_TEMP.h"
#include <stdio.h>

/*******************************************************************************
* Global Variables
*******************************************************************************/
int32_t room_timer_seconds = INITIAL_TIMER_SECONDS;
int32_t room_temperature = INITIAL_TEMPERATURE;
bool timer_active = false;
static lv_timer_t * scheduler_timer = NULL;

/*******************************************************************************
* Function Name: room_scheduler_init
********************************************************************************
* Summary:
*  Initialize the room scheduler system. Creates LVGL timer for countdown.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void room_scheduler_init(void)
{
    room_timer_seconds = INITIAL_TIMER_SECONDS;
    room_temperature = INITIAL_TEMPERATURE;
    timer_active = false;
    
    /* Create a timer that fires every second (1000ms) */
    if (scheduler_timer == NULL) {
        scheduler_timer = lv_timer_create(room_scheduler_update_timer, 1000, NULL);
        lv_timer_pause(scheduler_timer);
    }
}

/*******************************************************************************
* Function Name: room_scheduler_start
********************************************************************************
* Summary:
*  Start the room timer countdown from initial value.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void room_scheduler_start(void)
{
    room_timer_seconds = INITIAL_TIMER_SECONDS;
    timer_active = true;
    
    if (scheduler_timer != NULL) {
        lv_timer_resume(scheduler_timer);
    }
    
    room_scheduler_update_display();
}

/*******************************************************************************
* Function Name: room_scheduler_stop
********************************************************************************
* Summary:
*  Stop the room timer countdown and reset.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void room_scheduler_stop(void)
{
    timer_active = false;
    room_timer_seconds = INITIAL_TIMER_SECONDS;
    
    if (scheduler_timer != NULL) {
        lv_timer_pause(scheduler_timer);
    }
}

/*******************************************************************************
* Function Name: room_scheduler_extend
********************************************************************************
* Summary:
*  Extend the room timer by adding additional seconds.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void room_scheduler_extend(void)
{
    if (timer_active) {
        room_timer_seconds += EXTEND_TIMER_SECONDS;
        room_scheduler_update_display();
    }
}

/*******************************************************************************
* Function Name: room_scheduler_update_timer
********************************************************************************
* Summary:
*  Timer callback function that decrements the countdown timer.
*  Called every second by LVGL timer.
*
* Parameters:
*  timer: Pointer to the LVGL timer
*
* Return:
*  void
*
*******************************************************************************/
void room_scheduler_update_timer(lv_timer_t * timer)
{
    (void)timer;
    
    if (timer_active && room_timer_seconds > 0) {
        room_timer_seconds--;
        room_scheduler_update_display();
        
        /* If timer reaches zero, meeting ends automatically */
        if (room_timer_seconds <= 0) {
            timer_active = false;
            /* Could navigate back to room selection here if desired */
        }
    }
}

/*******************************************************************************
* Function Name: room_scheduler_increase_temperature
********************************************************************************
* Summary:
*  Increase the room temperature by 1 degree (within limits).
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void room_scheduler_increase_temperature(void)
{
    if (room_temperature < MAX_TEMPERATURE) {
        room_temperature++;
        room_scheduler_update_display();
    }
}

/*******************************************************************************
* Function Name: room_scheduler_decrease_temperature
********************************************************************************
* Summary:
*  Decrease the room temperature by 1 degree (within limits).
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void room_scheduler_decrease_temperature(void)
{
    if (room_temperature > MIN_TEMPERATURE) {
        room_temperature--;
        room_scheduler_update_display();
    }
}

/*******************************************************************************
* Function Name: room_scheduler_update_display
********************************************************************************
* Summary:
*  Update the UI display with current temperature and timer values.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void room_scheduler_update_display(void)
{
    static char temp_str[16];
    static char timer_str[32];
    
    /* Update temperature display */
    if (ui_Label10 != NULL) {
        snprintf(temp_str, sizeof(temp_str), "%d°C", (int)room_temperature);
        lv_label_set_text(ui_Label10, temp_str);
    }
    
    /* Update timer display */
    if (ui_Label24 != NULL) {
        int32_t minutes = room_timer_seconds / 60;
        int32_t seconds = room_timer_seconds % 60;
        snprintf(timer_str, sizeof(timer_str), "%d min %d sec", (int)minutes, (int)seconds);
        lv_label_set_text(ui_Label24, timer_str);
    }
}
