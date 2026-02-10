/*****************************************************************************
* \file Hackathon_Voice.h
*****************************************************************************
* \copyright
* Copyright 2024, Infineon Technologies.
* All rights reserved.
*****************************************************************************/

#ifndef HACKATHON_VOICE_H
#define HACKATHON_VOICE_H

#include <stdint.h>

#define HACKATHON_VOICE_NUM_INTENTS 4
#define HACKATHON_VOICE_NUM_COMMANDS 15
#define HACKATHON_VOICE_NUM_VARIABLES 4
#define HACKATHON_VOICE_NUM_VARIABLE_PHRASES 6
#define HACKATHON_VOICE_NUM_UNIT_PHRASES 16
#define HACKATHON_VOICE_INTENT_MAP_ARRAY_TOTAL_SIZE 60
#define HACKATHON_VOICE_UNIT_PHRASE_MAP_ARRAY_TOTAL_SIZE 15

extern const char* Hackathon_Voice_intent_name_list[HACKATHON_VOICE_NUM_INTENTS];

extern const char* Hackathon_Voice_variable_name_list[HACKATHON_VOICE_NUM_VARIABLES];

extern const char* Hackathon_Voice_variable_phrase_list[HACKATHON_VOICE_NUM_VARIABLE_PHRASES];

extern const char* Hackathon_Voice_unit_phrase_list[HACKATHON_VOICE_NUM_UNIT_PHRASES];

extern const int Hackathon_Voice_intent_map_array[HACKATHON_VOICE_INTENT_MAP_ARRAY_TOTAL_SIZE];

extern const int Hackathon_Voice_intent_map_array_sizes[HACKATHON_VOICE_NUM_COMMANDS];

extern const int Hackathon_Voice_variable_phrase_sizes[HACKATHON_VOICE_NUM_VARIABLES];

extern const int Hackathon_Voice_unit_phrase_map_array[HACKATHON_VOICE_UNIT_PHRASE_MAP_ARRAY_TOTAL_SIZE];

extern const int Hackathon_Voice_unit_phrase_map_array_sizes[HACKATHON_VOICE_NUM_COMMANDS];

#endif // HACKATHON_VOICE_H
