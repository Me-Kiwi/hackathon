/***********************************************************************************************//**
 * \file mtb_tlv320dac3100.c
 *
 * Description: This file contains the TLV320DAC3100 codec control APIs.
 *
 ***************************************************************************************************
 * \copyright
 * Copyright 2023 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **************************************************************************************************/

#include <stdbool.h>

#include "mtb_tlv320dac3100.h"


#define _TLV320DAC3100_I2S_MCTRL_WRD_SIZE_POS     (4)

static mtb_hal_i2c_t* _mtb_dac3100_i2c_ptr = NULL;

uint8_t ndac_div = 1;
uint8_t mdac_div = 1;
uint16_t dosr_div = 2;

//--------------------------------------------------------------------------------------------------
// mtb_tlv320dac3100_init
//
// Initialize the Audio codec.
//--------------------------------------------------------------------------------------------------
cy_rslt_t mtb_tlv320dac3100_init(mtb_hal_i2c_t* i2c_inst)
{
    if (i2c_inst == NULL)
    {
        return CY_RSLT_TLV320DAC3100_INIT_FAIL;
    }

    _mtb_dac3100_i2c_ptr = i2c_inst;

    return CY_RSLT_SUCCESS;
}


//--------------------------------------------------------------------------------------------------
// mtb_tlv320dac3100_free
//
// Free the resources used with the Audio codec.
//--------------------------------------------------------------------------------------------------
void mtb_tlv320dac3100_free(void)
{
    _mtb_dac3100_i2c_ptr = NULL;
}


//--------------------------------------------------------------------------------------------------
// mtb_tlv320dac3100_configure_clocking
//
// This function configure internal clock dividers to achieve desired sample rate
//--------------------------------------------------------------------------------------------------
cy_rslt_t mtb_tlv320dac3100_configure_clocking(uint32_t mclk_hz,
                                               mtb_tlv320dac3100_dac_sample_rate_t sample_rate,
                                               mtb_tlv320dac3100_i2s_word_size_t word_length)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_PAGE_CTRL, 0);
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_SW_RST, 0x01);
    
    // Clock settings
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_CLK_GEN_MUX, 0x00);

    // mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_CLK_PLL_J, 0x04);
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_CLK_PLL_D_MSB, 0x00);
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_CLK_PLL_PR, 0x13);

    /* Set sample rate for the codec
        The next formula used for DAC_Fs calculation:

                        CLK_IN
        DAC_Fs = --------------------
                   NDAC x MDAC x DOSR

        The maximum frequencies for the main clocks:
        - DAC_CLK:     <= 49.152 MHz  (DAC_CLK is getting from NDAC divider)
        - DAC_MOD_CLK:  = 6.758  MHz  (DAC_MOD_CLK is getting from MDAC divider)
     */
    const uint32_t MAX_DAC_CLK_FREQ_HZ = 49152000;
    const uint32_t MAX_DAC_MOD_CLK_FREQ_HZ = 6200000;
    // uint8_t ndac_div = 1;
    // uint8_t mdac_div = 1;
    // uint16_t dosr_div = 2;
    uint32_t mdac_freq, ndac_freq, dac_fs;

    ndac_freq = mclk_hz;
    while ((ndac_freq / ndac_div) > MAX_DAC_CLK_FREQ_HZ)
    {
        ndac_div++;
    }

    /* Set MDAC divider
     * DOSR is limited in its range by the following condition:
     * 2.8 MHz < DOSR × DAC_Fs < 6.2 MHz
     * So the frequency after MDAC divider should be in this range
     */
    mdac_freq = (ndac_freq / ndac_div);
    while ((mdac_freq / mdac_div) > MAX_DAC_MOD_CLK_FREQ_HZ)
    {
        mdac_div++;
    }
    /* Set DOSR divider to achieve desierd sample rate */
    dac_fs = (mdac_freq / mdac_div);
    while ((dac_fs / dosr_div) > (uint32_t)sample_rate)
    {
        dosr_div++;
    }

    // The datasheet recommends to use even DOSR divider.
    // If the DOSR divider is odd, decrease it by 1.
    if (dosr_div % 2 != 0)
    {
        dosr_div--;
    }

    // // NDAC and MDAC power up
    // mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_NDAC_VAL, 0x80 | ndac_div);
    // mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_MDAC_VAL, 0x80 | mdac_div);
    // Set DOSR MSB and LSB values
    // DOSR is a 10-bit register, so get only 2 MSB from the divider value
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_DAC_DOSR_MSB, ((dosr_div >> 8) & 0x3));
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_DAC_DOSR_LSB, (dosr_div & 0xFF));

    // I2S interface, BLCK input, WCLK input
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_CODEC_INTERFACE_1,
                                 (word_length << _TLV320DAC3100_I2S_MCTRL_WRD_SIZE_POS));
    // Processing blocks -> PRB_P11
    // mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_DAC_BSEL, 0x0B);
    // mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_DAC_BSEL, 0x01);
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_DAC_BSEL, 17u);
    // Adaptive filtering enabled
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P8_REG_DAC_COEF_RAM, 0x04);
    // Volume control through register on
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_VOL_MICDET_CTL, 0x00);
    // Headphone output Power Down
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P1_REG_HP_DRV, 0x04);
    // Driver-poweron-time=1.22s Driver ramp up time= 3.9ms
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P1_REG_HP_OUT_POP, 0x4E);
    // DAC_L to left channel mixer and DAC_R to right channel mixer
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P1_REG_DAC_LR_OUT_MIX, 0x44);
    // HPL unmute, 0dB, gain not applied
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P1_REG_HPL_DRV, 0x06);
    // HPR unmute, 0dB, gain not applied
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P1_REG_HPR_DRV, 0x06);
    // Output gain 24dB, Class-D driver unmute, gain not applied
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P1_REG_CLS_D_SPK_DRV, 0x1D);
    // Headphone output Power up
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P1_REG_HP_DRV, 0xC4);
    // Speaker output Power up
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P1_REG_CLS_D_SPK_AMP, 0x86);
    // Left Channel analog routed to output HPL = 18 (0-127)
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P1_REG_HP_LAV, 0x92);
    // Right Channel analog routed to output HPR = 18 (0-127)
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P1_REG_HP_RAV, 0x92);
    // Left Channel analog routed to output SPL = 18 (0-127)
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P1_REG_SP_LAV, 0x92);
    // Power up Left and Right channel
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_DAC_DPATH, 0xD4);
    // DAC Left volume gain = -22dB
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_DAC_LVOL_CTL, 0xE4);
    // DAC Right volume gain = -22dB
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_DAC_RVOL_CTL, 0xE4);
    // Unmute the Left-Right channel
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_DAC_VOL_CTL, 0x00);

    return result;
}


//--------------------------------------------------------------------------------------------------
// mtb_tlv320dac3100_write_byte
//
// This function writes a data byte to an audio codec register
//--------------------------------------------------------------------------------------------------
void mtb_tlv320dac3100_write_byte(mtb_tlv320dac3100_reg_t reg, uint8_t data)
{
    CY_ASSERT(NULL != _mtb_dac3100_i2c_ptr);

    cy_rslt_t rslt;

    uint8_t  page[] =
        { TLV320DAC3100_P0_REG_PAGE_CTRL, (reg >> TLV320DAC3100_PAGE_NUM_Pos) & 0xFF };
    rslt =
        mtb_hal_i2c_controller_write(_mtb_dac3100_i2c_ptr, MTB_TLV320DAC3100_I2C_ADDR, page, sizeof(page),
                               0,
                               true);

    if (CY_RSLT_SUCCESS == rslt)
    {
        uint8_t buf[] = { (reg & 0xFF), data };
        rslt =
            mtb_hal_i2c_controller_write(_mtb_dac3100_i2c_ptr, MTB_TLV320DAC3100_I2C_ADDR, buf,
                                   sizeof(buf),
                                   0,
                                   true);
    }
    CY_UNUSED_PARAMETER(rslt); // CY_ASSERT only processes in DEBUG, ignores for others
    CY_ASSERT(CY_RSLT_SUCCESS == rslt);
}


//--------------------------------------------------------------------------------------------------
// mtb_tlv320dac3100_read_byte
//
// This function reads a data byte from an audio codec register
//--------------------------------------------------------------------------------------------------
uint8_t mtb_tlv320dac3100_read_byte(mtb_tlv320dac3100_reg_t reg)
{
    CY_ASSERT(NULL != _mtb_dac3100_i2c_ptr);

    cy_rslt_t rslt;
    uint8_t   data = 0;

    uint8_t  page[] =
        { TLV320DAC3100_P0_REG_PAGE_CTRL, (reg >> TLV320DAC3100_PAGE_NUM_Pos) & 0xFF };
    rslt =
        mtb_hal_i2c_controller_write(_mtb_dac3100_i2c_ptr, MTB_TLV320DAC3100_I2C_ADDR, page, sizeof(page),
                               0,
                               true);

    if (CY_RSLT_SUCCESS == rslt)
    {
        uint8_t buf[] = { (reg & 0xFF), data };
        rslt =
            mtb_hal_i2c_controller_write(_mtb_dac3100_i2c_ptr, MTB_TLV320DAC3100_I2C_ADDR, buf,
                                   sizeof(buf),
                                   0,
                                   true);
    }

    CY_UNUSED_PARAMETER(rslt); // CY_ASSERT only processes in DEBUG, ignores for others
    CY_ASSERT(CY_RSLT_SUCCESS == rslt);

    rslt =
        mtb_hal_i2c_controller_read(_mtb_dac3100_i2c_ptr, MTB_TLV320DAC3100_I2C_ADDR, &data, 1, 0, true);
    CY_UNUSED_PARAMETER(rslt); // CY_ASSERT only processes in DEBUG, ignores for others
    CY_ASSERT(CY_RSLT_SUCCESS == rslt);

    return data;
}


//--------------------------------------------------------------------------------------------------
// mtb_tlv320dac3100_set
//
// This function sets bits in a register.
//--------------------------------------------------------------------------------------------------
void mtb_tlv320dac3100_set(mtb_tlv320dac3100_reg_t reg, uint8_t mask)
{
    uint8_t data = mtb_tlv320dac3100_read_byte(reg) | mask;
    mtb_tlv320dac3100_write_byte(reg, data);
}


//--------------------------------------------------------------------------------------------------
// mtb_tlv320dac3100_clear
//
// This function clears bits in a register.
//--------------------------------------------------------------------------------------------------
void mtb_tlv320dac3100_clear(mtb_tlv320dac3100_reg_t reg, uint8_t mask)
{
    uint8_t data = mtb_tlv320dac3100_read_byte(reg) & ~mask;
    mtb_tlv320dac3100_write_byte(reg, data);
}


//--------------------------------------------------------------------------------------------------
// mtb_tlv320dac3100_adjust_sp_volume
//
// This function updates the volume of both the left and right channels of the speaker output.
//--------------------------------------------------------------------------------------------------
void mtb_tlv320dac3100_adjust_speaker_output_volume(uint8_t volume)
{
    uint8_t out = volume|0x80;

    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_DAC_LVOL_CTL, out);  //DAC Left volume gain =
                                                                               // -22dB 0 -127
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_DAC_RVOL_CTL, out); // DAC Right volume gain
                                                                              // = -22dB
}


//--------------------------------------------------------------------------------------------------
// mtb_tlv320dac3100_adjust_hp_volume
//
// This function updates the volume of both the left and right channels of the headphone output.
//--------------------------------------------------------------------------------------------------
void mtb_tlv320dac3100_adjust_headphone_output_volume(uint8_t volume)
{
    uint8_t out = volume | 0x80;
    // Left Channel analog routed to output HPL (0-127)
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P1_REG_HP_LAV, out);
    // Right Channel analog routed to output HPR (0-127)
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P1_REG_HP_RAV, out);
}


//--------------------------------------------------------------------------------------------------
// mtb_tlv320dac3100_activate
//
// Activates the codec - This function is called in conjunction with tlv320dac3100_deactivate
// API after successful configuration update of the codec.
//--------------------------------------------------------------------------------------------------
void mtb_tlv320dac3100_activate(void)
{
    // NDAC and MDAC power up
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_NDAC_VAL, 0x80 | ndac_div);
    mtb_tlv320dac3100_write_byte(TLV320DAC3100_P0_REG_MDAC_VAL, 0x80 | mdac_div);
}


//--------------------------------------------------------------------------------------------------
// mtb_tlv320dac3100_deactivate
//
// Deactivates the codec - the configuration is retained, just the codec input/outputs are disabled.
// The function should be called before changing any setting in the codec over I2C
//--------------------------------------------------------------------------------------------------
void mtb_tlv320dac3100_deactivate(void)
{
    // NDAC and MDAC power down
    mtb_tlv320dac3100_clear(TLV320DAC3100_P0_REG_NDAC_VAL, 0x80);
    mtb_tlv320dac3100_clear(TLV320DAC3100_P0_REG_MDAC_VAL, 0x80);
}
