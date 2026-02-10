/******************************************************************************
* File Name : voice_control.c
*
* Description :
* Code for voice control using DEEPCRAFT voice assistant
********************************************************************************
* Copyright 2025, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/

#include "stdlib.h"

#include "cy_pdl.h"
#include "cycfg.h"
#include "profiler.h"
#include "voice_assistant.h"
#include "lvgl.h"
#include "ui.h"
#ifdef USE_AUDIO_ENHANCEMENT
#include "audio_enhancement.h"
#endif
#include "app_Hackathon_Voice.h"
#ifdef PROFILER_ENABLE
#include "cy_afe_profiler.h"
#include "cy_profiler.h"
#endif /* PROFILER_ENABLE */


/*******************************************************************************
 * Function Name: Intent to ui changes
 *******************************************************************************/
va_rslt_t intent_to_ui(const char *command , const char *variable_text)
{
    if(handle_command_for_ui)
    {
        if (NULL == command) {
            // printf("No command received.\n");
            return VA_RSLT_INVALID_ARGUMENT;  // Return immediately for invalid input
        }

        // Map the command string to an enum value
        va_detect_cmd_t cmd = va_command_to_id(command,variable_text);

        // Handle the command using a switch statement
        switch (cmd) 
        {
            case Red:
            {
                lv_obj_set_style_bg_color(ui_Slider1, lv_color_hex(0xdc143c), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                break;
            }
             case Blue:
            {
                lv_obj_set_style_bg_color(ui_Slider1, lv_color_hex(0x178bB), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                break;
            }
             case Green:
            {
                lv_obj_set_style_bg_color(ui_Slider1, lv_color_hex(0x3B9B91), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                break;
            }
            case SetMax:
            {
                lv_slider_set_value(ui_Slider1, 100, LV_ANIM_ON);
                break;
            }
             case SetMin:
            {
                lv_slider_set_value(ui_Slider1, 40, LV_ANIM_ON);
                break;
            }
             case SetZero:
            {
                lv_slider_set_value(ui_Slider1, 2, LV_ANIM_ON);
                break;
            }

            default:
            {
                // Handle unknown commands
                if (command && command[0] != '\0') {
                    printf("Unknown command: %s\n", command);
                } else {
                    printf("Unknown or empty command received.\n");
                }
                return VA_RSLT_INVALID_ARGUMENT;  // Return an error for unknown commands
            }
        }
        handle_command_for_ui = false;
    }

    // Successfully handled the command
    return VA_RSLT_SUCCESS;
}