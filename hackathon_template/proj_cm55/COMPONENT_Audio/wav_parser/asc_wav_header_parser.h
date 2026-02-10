/******************************************************************************
* File Name : asc_wav_header_parser.h
*
* Description: Header for parsing wav files.
********************************************************************************
* $ Copyright 2025-YEAR Cypress Semiconductor $
*******************************************************************************/

#ifndef __ASC_WAV_HEADER_PARSER_H__
#define __ASC_WAV_HEADER_PARSER_H__

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*******************************************************************************
* Function prototypes
*******************************************************************************/
int asc_byte_stream_read(unsigned char *bitstream, unsigned char *bytes, unsigned int size,unsigned int *current_read_pos, unsigned int bitstream_max );
bool cy_wav_header_decode( uint32_t *n_channels,
                            uint32_t *i_channel_mask, uint32_t *sample_rate,
                            uint32_t *pcm_sz, int32_t *length,
                            unsigned char *pBit_stream,unsigned int *asc_stream_read_counter,unsigned int bit_stream_max);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ASC_WAV_HEADER_PARSER_H__ */
/* [] END OF FILE */
