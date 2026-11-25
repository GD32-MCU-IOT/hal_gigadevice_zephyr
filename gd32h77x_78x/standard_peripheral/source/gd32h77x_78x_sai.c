/*!
    \file    gd32h77x_78x_sai.c
    \brief   SAI driver

    \version 2026-11-09, V1.0.0, firmware for GD32H77x_78x
*/

/*
    Copyright (c) 2026, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32h77x_78x_sai.h"

/* SAI PDM mode microphone delay mask */
#define PDM_MICROPHONE_DELAY_MASK            ((uint32_t)0x00000007U)
/* bit width of each microphone delay field in SAI_PDMCFG */
#define PDM_MICROPHONE_DELAY_STEP            ((uint32_t)0x00000004U)
/* SAI_CFG1 MTFCNT mask */
#define CFG1_MTFCNT_MASK                     ((uint32_t)0x0000003FU)

/* SAI register bit offset */
#define CFG1_MTFCNT_OFFSET                   ((uint32_t)0x00000007U)
#define FCFG_FSAWD_OFFSET                    ((uint32_t)0x00000008U)
#define SCFG_SLOTNUM_OFFSET                  ((uint32_t)0x00000008U)

/* SAI default value */
#define SAI_DEFAULT_FRAME_WIDTH              ((uint32_t)256U)
#define SAI_DEFAULT_FRAME_SYNC_WIDTH         ((uint32_t)128U)
#define SAI_DEFAULT_SLOT_NUMBER              ((uint32_t)16U)

/* SAI parameter range */
#define SAI_FRAME_WIDTH_MAX                  ((uint32_t)256U)
#define SAI_FRAME_SYNC_WIDTH_MAX             ((uint32_t)128U)
#define SAI_SLOT_NUMBER_MAX                  ((uint32_t)16U)

/*!
    \brief      reset SAI (API_ID: 0x0001U)
    \param[in]  sai_periph: SAIx(x = 0,1,2,3)
    \param[out] none
    \retval     none
*/
void sai_deinit(uint32_t sai_periph)
{
    switch(sai_periph) {
    case SAI0:
        /* reset SAI0 */
        rcu_periph_reset_enable(RCU_SAI0RST);
        rcu_periph_reset_disable(RCU_SAI0RST);
        break;
    case SAI1:
        /* reset SAI1 */
        rcu_periph_reset_enable(RCU_SAI1RST);
        rcu_periph_reset_disable(RCU_SAI1RST);
        break;
    case SAI2:
        /* reset SAI2 */
        rcu_periph_reset_enable(RCU_SAI2RST);
        rcu_periph_reset_disable(RCU_SAI2RST);
        break;
    case SAI3:
        /* reset SAI3 */
        rcu_periph_reset_enable(RCU_SAI3RST);
        rcu_periph_reset_disable(RCU_SAI3RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      initialize SAI parameter struct with the default values (API_ID: 0x0002U)
    \param[in]  none
    \param[out] sai_init_struct: the initialization data needed to initialize SAI
    \retval     none
*/
void sai_struct_para_init(sai_parameter_struct *sai_init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(sai_init_struct)) {
        fw_debug_report_err(SAI_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the initpara struct member with the default value */
        sai_init_struct->operating_mode         = SAI_MASTER_TRANSMITTER;
        sai_init_struct->protocol               = SAI_PROTOCOL_POLYMORPHIC;
        sai_init_struct->data_width             = SAI_DATAWIDTH_32BIT;
        sai_init_struct->shift_dir              = SAI_SHIFT_MSB;
        sai_init_struct->sample_edge            = SAI_SAMPEDGE_FALLING;
        sai_init_struct->sync_mode              = SAI_SYNCMODE_ASYNC;
        sai_init_struct->output_drive           = SAI_OUTPUT_WITH_SAIEN;
        sai_init_struct->clk_div_bypass         = SAI_CLKDIV_BYPASS_OFF;
        sai_init_struct->mclk_div               = SAI_MCLKDIV_1;
        sai_init_struct->mclk_oversampling      = SAI_MCLK_OVERSAMP_256;
        sai_init_struct->mclk_enable            = SAI_MCLK_DISABLE;
        sai_init_struct->fifo_threshold         = SAI_FIFOTH_EMPTY;
    }
}

/*!
    \brief      initialize SAI frame parameter struct with the default values (API_ID: 0x0003U)
    \param[in]  none
    \param[out] sai_frame_init_struct: the initialization data needed to initialize SAI frame
    \retval     none
*/
void sai_frame_struct_para_init(sai_frame_parameter_struct *sai_frame_init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(sai_frame_init_struct)) {
        fw_debug_report_err(SAI_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the initpara struct member with the default value */
        sai_frame_init_struct->frame_width                = SAI_DEFAULT_FRAME_WIDTH;
        sai_frame_init_struct->frame_sync_width           = SAI_DEFAULT_FRAME_SYNC_WIDTH;
        sai_frame_init_struct->frame_sync_function        = SAI_FS_FUNC_START;
        sai_frame_init_struct->frame_sync_polarity        = SAI_FS_POLARITY_LOW;
        sai_frame_init_struct->frame_sync_offset          = SAI_FS_OFFSET_BEGINNING;
    }
}

/*!
    \brief      initialize SAI slot parameter struct with the default values (API_ID: 0x0004U)
    \param[in]  none
    \param[out] sai_slot_init_struct: the initialization data needed to initialize SAI slot
    \retval     none
*/
void sai_slot_struct_para_init(sai_slot_parameter_struct *sai_slot_init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(sai_slot_init_struct)) {
        fw_debug_report_err(SAI_MODULE_ID, API_ID(0x0004U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the initpara struct member with the default value */
        sai_slot_init_struct->slot_number            = SAI_DEFAULT_SLOT_NUMBER;
        sai_slot_init_struct->slot_width             = SAI_SLOT_WIDTH_DATA;
        sai_slot_init_struct->data_offset            = 0U;
        sai_slot_init_struct->slot_active            = SAI_SLOT_ACTIVE_NONE;
    }
}

/*!
    \brief      initialize SAI (API_ID: 0x0005U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  sai_struct: SAI parameter initialization struct members of the structure
                            and the member values are shown as below:
                    operating_mode: SAI_MASTER_TRANSMITTER, SAI_MASTER_RECEIVER, SAI_SLAVE_TRANSMITTER, SAI_SLAVE_RECEIVER;
                    protocol: SAI_PROTOCOL_POLYMORPHIC, SAI_PROTOCOL_SPDIF, SAI_PROTOCOL_AC97
                    data_width: SAI_DATAWIDTH_xBIT (x = 8, 10, 16, 20, 24, 32)
                    shift_dir: SAI_SHIFT_MSB, SAI_SHIFT_LSB
                    sample_edge: SAI_SAMPEDGE_FALLING, SAI_SAMPEDGE_RISING
                    sync_mode: SAI_SYNCMODE_ASYNC, SAI_SYNCMODE_OTHERBLOCK, SAI_SYNCMODE_EXTERNALSAI
                    output_drive: SAI_OUTPUT_WITH_SAIEN, SAI_OUTPUT_NOW
                    clk_div_bypass: SAI_CLKDIV_BYPASS_OFF, SAI_CLKDIV_BYPASS_ON
                    mclk_div: SAI_MCLKDIV_x (x = 1, 2, ..., 63)
                    mclk_oversampling: SAI_MCLK_OVERSAMP_256, SAI_MCLK_OVERSAMP_512
                    mclk_enable: SAI_MCLK_DISABLE, SAI_MCLK_ENABLE
                    fifo_threshold: SAI_FIFOTH_EMPTY, SAI_FIFOTH_QUARTER, SAI_FIFOTH_HALF, SAI_FIFOTH_THREE_QUARTER, SAI_FIFOTH_FULL
    \param[out] none
    \retval     none
    \note       this function must be called when the SAI sub-block is disabled; OPTMOD, PROT, DATAWD,
                SAMPEDGE, SYNCMOD and MDIV must be configured before the sub-block is enabled, ODRIV
                should be set after the configuration is completed and before the sub-block is enabled
*/
void sai_init(uint32_t sai_periph, uint32_t block, sai_parameter_struct *sai_struct)
{
    uint32_t reg = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(sai_struct)) {
        fw_debug_report_err(SAI_MODULE_ID, API_ID(0x0005U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure the SAI CFGR0 value */
        reg = SAI_CFG0(sai_periph, block);
        reg &= ~(SAI_CFG0_OPTMOD | SAI_CFG0_PROT | \
                 SAI_CFG0_DATAWD | SAI_CFG0_SHIFTDIR | \
                 SAI_CFG0_SAMPEDGE | SAI_CFG0_SYNCMOD | \
                 SAI_CFG0_ODRIV | SAI_CFG0_BYPASS | \
                 SAI_CFG0_MDIV | SAI_CFG0_MOSPR | \
                 SAI_CFG0_MCLKEN | SAI_CFG0_SAIEN);

        reg |= (uint32_t)(sai_struct->operating_mode | sai_struct->protocol | \
                          sai_struct->data_width | sai_struct->shift_dir | \
                          sai_struct->sample_edge | sai_struct->sync_mode | \
                          sai_struct->output_drive | sai_struct->clk_div_bypass | \
                          sai_struct->mclk_div | sai_struct->mclk_oversampling | \
                          sai_struct->mclk_enable);
        SAI_CFG0(sai_periph, block) = reg;

        /* configure the SAI CFGR1 FIFO threshold */
        reg = SAI_CFG1(sai_periph, block);
        reg &= ~SAI_CFG1_FFTH;
        reg |= (uint32_t)(sai_struct->fifo_threshold);
        SAI_CFG1(sai_periph, block) = reg;
    }
}

/*!
    \brief      initialize SAI frame (API_ID: 0x0006U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  sai_frame_struct: SAI frame parameter initialization struct members of the structure
                            and the member values are shown as below:
                    frame_width: 1~256, frame width
                    frame_sync_width: 1~128, frame synchronization active width
                    frame_sync_function: SAI_FS_FUNC_START, SAI_FS_FUNC_START_CHANNEL
                    frame_sync_polarity: SAI_FS_POLARITY_LOW, SAI_FS_POLARITY_HIGH
                    frame_sync_offset: SAI_FS_OFFSET_BEGINNING, SAI_FS_OFFSET_ONEBITBEFORE
    \param[out] none
    \retval     none
    \note       this function must be called before the SAI sub-block is enabled
*/
void sai_frame_init(uint32_t sai_periph, uint32_t block, sai_frame_parameter_struct *sai_frame_struct)
{
    uint32_t reg = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(sai_frame_struct)) {
        fw_debug_report_err(SAI_MODULE_ID, API_ID(0x0006U), ERR_PARAM_POINTER);
    } else if((0U == sai_frame_struct->frame_width) || (SAI_FRAME_WIDTH_MAX < sai_frame_struct->frame_width) ||
              (0U == sai_frame_struct->frame_sync_width) || (SAI_FRAME_SYNC_WIDTH_MAX < sai_frame_struct->frame_sync_width)) {
        fw_debug_report_err(SAI_MODULE_ID, API_ID(0x0006U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = SAI_FCFG(sai_periph, block);
        reg &= ~(SAI_FCFG_FWD | SAI_FCFG_FSAWD | SAI_FCFG_FSFUNC | \
                 SAI_FCFG_FSPL | SAI_FCFG_FSOST);
        reg |= (uint32_t)((sai_frame_struct->frame_sync_offset & SAI_FCFG_FSOST) | \
                          (sai_frame_struct->frame_sync_polarity & SAI_FCFG_FSPL) | \
                          (sai_frame_struct->frame_sync_function & SAI_FCFG_FSFUNC) | \
                          (((sai_frame_struct->frame_sync_width - 1U) << FCFG_FSAWD_OFFSET) & SAI_FCFG_FSAWD) | \
                          ((sai_frame_struct->frame_width - 1U) & SAI_FCFG_FWD));
        /* config the SAI frame */
        SAI_FCFG(sai_periph, block) = reg;
    }
}

/*!
    \brief      initialize SAI slot (API_ID: 0x0007U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  sai_slot_struct: SAI slot parameter initialization struct members of the structure
                            and the member values are shown as below:
                    slot_number: 1~16, slot number
                    slot_width: SAI_SLOT_WIDTH_DATA, SAI_SLOT_WIDTH_16BIT, SAI_SLOT_WIDTH_32BIT
                    data_offset: 0~31, data offset
                    slot_active: one or more parameters can be selected, SAI_SLOT_ACTIVE_NONE, SAI_SLOT_ACTIVE_x(x=0..15), SAI_SLOT_ACTIVE_ALL
    \param[out] none
    \retval     none
    \note       this function must be called before the SAI sub-block is enabled
*/
void sai_slot_init(uint32_t sai_periph, uint32_t block, sai_slot_parameter_struct *sai_slot_struct)
{
    uint32_t reg = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(sai_slot_struct)) {
        fw_debug_report_err(SAI_MODULE_ID, API_ID(0x0007U), ERR_PARAM_POINTER);
    } else if((0U == sai_slot_struct->slot_number) || (SAI_SLOT_NUMBER_MAX < sai_slot_struct->slot_number)) {
        fw_debug_report_err(SAI_MODULE_ID, API_ID(0x0007U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = SAI_SCFG(sai_periph, block);
        reg &= ~(SAI_SCFG_DATAOST | SAI_SCFG_SLOTWD | SAI_SCFG_SLOTNUM | SAI_SCFG_SLOTAV);
        reg |= (uint32_t)((((sai_slot_struct->slot_number - 1U) << SCFG_SLOTNUM_OFFSET) & SAI_SCFG_SLOTNUM) | \
                          (sai_slot_struct->slot_width & SAI_SCFG_SLOTWD) | \
                          (sai_slot_struct->data_offset & SAI_SCFG_DATAOST) | \
                          (sai_slot_struct->slot_active & SAI_SCFG_SLOTAV));
        /* configure the SAI slot */
        SAI_SCFG(sai_periph, block) = reg;
    }
}

/*!
    \brief      enable SAI sub-block (API_ID: 0x0008U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[out] none
    \retval     none
    \note       the slave sub-block must be enabled before the master sub-block; SAIEN can only be set when it is 0
*/
void sai_enable(uint32_t sai_periph, uint32_t block)
{
    SAI_CFG0(sai_periph, block) |= SAI_CFG0_SAIEN;
}

/*!
    \brief      disable SAI sub-block (API_ID: 0x0009U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[out] none
    \retval     none
    \note       the disable request takes effect at the end of the current frame, the sub-block is
                completely disabled only when SAIEN is read back as 0
*/
void sai_disable(uint32_t sai_periph, uint32_t block)
{
    SAI_CFG0(sai_periph, block) &= ~SAI_CFG0_SAIEN;
}

/*!
    \brief      configure SAI serial data near inactive slot output management (API_ID: 0x000AU)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  sdout: serial data output management
                only one parameter can be selected which is shown as below:
      \arg        SAI_SDLINE_DRIVE: SD line output is driven entirely during the audio frame
      \arg        SAI_SDLINE_RELEASE: SD line output is released near inactive slots
    \param[out] none
    \retval     none
*/
void sai_sdoutput_config(uint32_t sai_periph, uint32_t block, uint32_t sdout)
{
    SAI_CFG1(sai_periph, block) &= ~SAI_CFG1_SDOM;
    SAI_CFG1(sai_periph, block) |= (sdout & SAI_CFG1_SDOM);
}

/*!
    \brief      configure SAI mono mode (API_ID: 0x000BU)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  mono: stereo and mono mode selection
                only one parameter can be selected which is shown as below:
      \arg        SAI_STEREO_MODE: stereo mode
      \arg        SAI_MONO_MODE: mono mode
    \param[out] none
    \retval     none
*/
void sai_monomode_config(uint32_t sai_periph, uint32_t block, uint32_t mono)
{
    SAI_CFG0(sai_periph, block) &= ~SAI_CFG0_MONO;
    SAI_CFG0(sai_periph, block) |= (mono & SAI_CFG0_MONO);
}

/*!
    \brief      configure SAI companding mode (API_ID: 0x000CU)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  compander: compander mode
                only one parameter can be selected which is shown as below:
      \arg        SAI_COMPANDER_OFF: no compression applies
      \arg        SAI_COMPANDER_ULAW: u-law algorithm
      \arg        SAI_COMPANDER_ALAW: A-law algorithm
    \param[in]  complement:complement mode
                only one parameter can be selected which is shown as below:
      \arg        SAI_COMPLEMENT_1S: data represented in 1's complement form
      \arg        SAI_COMPLEMENT_2S: data represented in 2's complement form
    \param[out] none
    \retval     none
*/
void sai_companding_config(uint32_t sai_periph, uint32_t block, uint32_t compander, uint32_t complement)
{
    uint32_t reg = 0U;
    reg = SAI_CFG1(sai_periph, block);
    reg &= ~(SAI_CFG1_CPLMOD | SAI_CFG1_CPAMOD);
    reg |= ((compander & SAI_CFG1_CPAMOD) | (complement & SAI_CFG1_CPLMOD));
    SAI_CFG1(sai_periph, block) = reg;
}

/*!
    \brief      enable SAI mute detected or mute send (API_ID: 0x000DU)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[out] none
    \retval     none
*/
void sai_mute_enable(uint32_t sai_periph, uint32_t block)
{
    SAI_CFG1(sai_periph, block) |= SAI_CFG1_MT;
}

/*!
    \brief      disable SAI mute detected or mute send (API_ID: 0x000EU)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[out] none
    \retval     none
*/
void sai_mute_disable(uint32_t sai_periph, uint32_t block)
{
    SAI_CFG1(sai_periph, block) &= ~SAI_CFG1_MT;
}

/*!
    \brief      configure SAI mute value (API_ID: 0x000FU)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  value: mute value
                only one parameter can be selected which are shown as below:
      \arg        SAI_MUTESENT_0: 0 is sent via the serial data line when mute is on
      \arg        SAI_MUTESENT_LASTFRAME: if SLOTNUM is less or equal to two, last frame is sent via the serial data line
    \param[out] none
    \retval     none
*/
void sai_mute_value_config(uint32_t sai_periph, uint32_t block, uint32_t value)
{
    SAI_CFG1(sai_periph, block) &= ~SAI_CFG1_MTVAL;
    SAI_CFG1(sai_periph, block) |= (value & SAI_CFG1_MTVAL);
}

/*!
    \brief      configure SAI mute frame count (API_ID: 0x0010U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  count: 0~63, mute frame count
    \param[out] none
    \retval     none
*/
void sai_mute_count_config(uint32_t sai_periph, uint32_t block, uint32_t count)
{
    uint32_t reg = 0U;
    reg = SAI_CFG1(sai_periph, block);
    reg &= ~SAI_CFG1_MTFCNT;
    reg |= ((count & CFG1_MTFCNT_MASK) << CFG1_MTFCNT_OFFSET);
    SAI_CFG1(sai_periph, block) = reg;
}

/*!
    \brief      transmit SAI data (API_ID: 0x0011U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  data: 32-bit data
    \param[out] none
    \retval     none
*/
void sai_data_transmit(uint32_t sai_periph, uint32_t block, uint32_t data)
{
    SAI_DATA(sai_periph, block) = data;
}

/*!
    \brief      receive SAI data (API_ID: 0x0012U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[out] none
    \retval     uint32_t: received data(0x00000000-0xFFFFFFFF)
*/
uint32_t sai_data_receive(uint32_t sai_periph, uint32_t block)
{
    return SAI_DATA(sai_periph, block);
}

/*!
    \brief      get SAI FIFO status (API_ID: 0x0013U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[out] none
    \retval     sai_fifo_state_enum: state of FIFO
      \arg        SAI_FIFO_EMPTY: FIFO empty
      \arg        SAI_FIFO_EMPTY_TO_1_4_FULL: empty < FIFO level <= 1/4 full
      \arg        SAI_FIFO_1_4_FULL_TO_1_2_FULL: 1/4 full < FIFO level <= 1/2 full
      \arg        SAI_FIFO_1_2_FULL_TO_3_4_FULL: 1/2 full < FIFO level <= 3/4 full
      \arg        SAI_FIFO_3_4_FULL_TO_FULL: 3/4 full < FIFO level < full
      \arg        SAI_FIFO_FULL: FIFO full
*/
sai_fifo_state_enum sai_fifo_status_get(uint32_t sai_periph, uint32_t block)
{
    sai_fifo_state_enum sai_fifo_state;
    /* read FIFO status only once */
    uint32_t fifo_stat = (SAI_STAT(sai_periph, block) & SAI_STAT_FFSTAT);

    switch(fifo_stat) {
    case SAI_FIFO_STAT_EMPTY:
        sai_fifo_state = SAI_FIFO_EMPTY;
        break;
    case SAI_FIFO_STAT_QUARTER:
        sai_fifo_state = SAI_FIFO_EMPTY_TO_1_4_FULL;
        break;
    case SAI_FIFO_STAT_HALF:
        sai_fifo_state = SAI_FIFO_1_4_FULL_TO_1_2_FULL;
        break;
    case SAI_FIFO_STAT_THREE_QUARTER:
        sai_fifo_state = SAI_FIFO_1_2_FULL_TO_3_4_FULL;
        break;
    case SAI_FIFO_STAT_NEARFULL:
        sai_fifo_state = SAI_FIFO_3_4_FULL_TO_FULL;
        break;
    default:
        sai_fifo_state = SAI_FIFO_FULL;
        break;
    }
    return sai_fifo_state;
}

/*!
    \brief      flush SAI FIFO (API_ID: 0x0014U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[out] none
    \retval     none
    \note       this function should be called when the SAI sub-block is disabled
*/
void sai_fifo_flush(uint32_t sai_periph, uint32_t block)
{
    SAI_CFG1(sai_periph, block) |= SAI_CFG1_FLUSH;
}

/*!
    \brief      enable SAI DMA (API_ID: 0x0015U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[out] none
    \retval     none
    \note       in receiver mode, OPTMOD must be configured before DMAEN is set, otherwise unexpected DMA requests may be generated
*/
void sai_dma_enable(uint32_t sai_periph, uint32_t block)
{
    SAI_CFG0(sai_periph, block) |= SAI_CFG0_DMAEN;
}

/*!
    \brief      disable SAI DMA (API_ID: 0x0016U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[out] none
    \retval     none
*/
void sai_dma_disable(uint32_t sai_periph, uint32_t block)
{
    SAI_CFG0(sai_periph, block) &= ~SAI_CFG0_DMAEN;
}

/*!
    \brief      configure SAI synchronization input (API_ID: 0x0017U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  input: specify which external SAI to be select for synchronization
                only one parameter can be selected which are shown as below:
      \arg        SAI_SYNCINPUT_SAI0: SAI1 or SAI2 or SAI3 selects the synchronization coming from SAI0
      \arg        SAI_SYNCINPUT_SAI1: SAI0 or SAI2 or SAI3 selects the synchronization coming from SAI1
      \arg        SAI_SYNCINPUT_SAI2: SAI0 or SAI1 or SAI3 selects the synchronization coming from SAI2
      \arg        SAI_SYNCINPUT_SAI3: SAI0 or SAI1 or SAI2 selects the synchronization coming from SAI3
    \param[out] none
    \retval     none
*/
void sai_sync_input_config(uint32_t sai_periph, uint32_t input)
{
    uint32_t reg = 0U;
    reg = SAI_SYNCFG(sai_periph);
    reg &= ~SAI_SYNCFG_SYNI;
    reg |= (input & SAI_SYNCFG_SYNI);
    SAI_SYNCFG(sai_periph) = reg;
}

/*!
    \brief      configure SAI synchronization output (API_ID: 0x0018U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  output: specify which block to be used for further synchronization for others SAI
                only one parameter can be selected which are shown as below:
      \arg        SAI_SYNCOUTPUT_OFF: no synchronization output signals
      \arg        SAI_SYNCOUTPUT_BLOCK0: block 0 used for further synchronization for others SAI
      \arg        SAI_SYNCOUTPUT_BLOCK1: block 1 used for further synchronization for others SAI
    \param[out] none
    \retval     none
*/
void sai_sync_output_config(uint32_t sai_periph, uint32_t output)
{
    uint32_t reg = 0U;
    reg = SAI_SYNCFG(sai_periph);
    reg &= ~SAI_SYNCFG_SYNO;
    reg |= (output & SAI_SYNCFG_SYNO);
    SAI_SYNCFG(sai_periph) = reg;
}

/*!
    \brief      enable SAI PDM mode (API_ID: 0x0019U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void sai_pdm_enable(uint32_t sai_periph)
{
    SAI_PDMCTL(sai_periph) |= SAI_PDMCTL_PDMEN;
}

/*!
    \brief      disable SAI PDM mode (API_ID: 0x001AU)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void sai_pdm_disable(uint32_t sai_periph)
{
    SAI_PDMCTL(sai_periph) &= ~SAI_PDMCTL_PDMEN;
}

/*!
    \brief      configure SAI PDM mode microphone number (API_ID: 0x001BU)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  microphonenum: select microphones number
                only one parameter can be selected which is shown as below:
      \arg        SAI_PDM_MICNUM_2: 2 microphones
      \arg        SAI_PDM_MICNUM_4: 4 microphones
      \arg        SAI_PDM_MICNUM_6: 6 microphones
      \arg        SAI_PDM_MICNUM_8: 8 microphones
    \param[out] none
    \retval     none
*/
void sai_pdm_microphone_number_config(uint32_t sai_periph, uint32_t microphonenum)
{
    uint32_t temp = SAI_PDMCTL(sai_periph);
    temp &= ~SAI_PDMCTL_MICNUMSEL;
    temp |= (microphonenum & SAI_PDMCTL_MICNUMSEL);
    SAI_PDMCTL(sai_periph) = temp;
}

/*!
    \brief      configure SAI PDM mode microphone delay (API_ID: 0x001CU)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  microphone: specify which microphone delay parameter to config
                only one parameter can be selected which are shown as below:
      \arg        SAI_PDM_MICROPHONE0_L: microphone 0 channel left
      \arg        SAI_PDM_MICROPHONE0_R: microphone 0 channel right
      \arg        SAI_PDM_MICROPHONE1_L: microphone 1 channel left
      \arg        SAI_PDM_MICROPHONE1_R: microphone 1 channel right
      \arg        SAI_PDM_MICROPHONE2_L: microphone 2 channel left
      \arg        SAI_PDM_MICROPHONE2_R: microphone 2 channel right
      \arg        SAI_PDM_MICROPHONE3_L: microphone 3 channel left
      \arg        SAI_PDM_MICROPHONE3_R: microphone 3 channel right
    \param[in]  delay: 0~7, the microphone data flow delay period
    \param[out] none
    \retval     none
*/
void sai_pdm_delay_config(uint32_t sai_periph, uint32_t microphone, uint32_t delay)
{
    uint32_t temp = SAI_PDMCFG(sai_periph);
    temp &= ~(PDM_MICROPHONE_DELAY_MASK << ((microphone & SAI_PDM_MICROPHONE3_R) * PDM_MICROPHONE_DELAY_STEP));
    temp |= ((delay & PDM_MICROPHONE_DELAY_MASK) << ((microphone & SAI_PDM_MICROPHONE3_R) * PDM_MICROPHONE_DELAY_STEP));
    SAI_PDMCFG(sai_periph) = temp;
}

/*!
    \brief      enable SAI PDM mode clock line 0 (API_ID: 0x001DU)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void sai_pdm_clk0_enable(uint32_t sai_periph)
{
    SAI_PDMCTL(sai_periph) |= SAI_PDMCTL_CLKL0EN;
}

/*!
    \brief      disable SAI PDM mode clock line 0 (API_ID: 0x001EU)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void sai_pdm_clk0_disable(uint32_t sai_periph)
{
    SAI_PDMCTL(sai_periph) &= ~SAI_PDMCTL_CLKL0EN;
}

/*!
    \brief      enable SAI PDM mode clock line 1 (API_ID: 0x001FU)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void sai_pdm_clk1_enable(uint32_t sai_periph)
{
    SAI_PDMCTL(sai_periph) |= SAI_PDMCTL_CLKL1EN;
}

/*!
    \brief      disable SAI PDM mode clock line 1 (API_ID: 0x0020U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[out] none
    \retval     none
*/
void sai_pdm_clk1_disable(uint32_t sai_periph)
{
    SAI_PDMCTL(sai_periph) &= ~SAI_PDMCTL_CLKL1EN;
}

/*!
    \brief      get SAI flag (API_ID: 0x0025U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  flag: specify which flag to get
                only one parameter can be selected which are shown as below:
      \arg        SAI_FLAG_OUERR: FIFO overrun or underrun flag
      \arg        SAI_FLAG_MTDET: mute detection flag
      \arg        SAI_FLAG_ERRCK: error clock flag
      \arg        SAI_FLAG_FFREQ: FIFO request flag
      \arg        SAI_FLAG_ACNRDY: audio codec not ready flag
      \arg        SAI_FLAG_FSADET: frame synchronization advanced detection flag
      \arg        SAI_FLAG_FSPDET: frame synchronization postpone detection flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus sai_flag_get(uint32_t sai_periph, uint32_t block, uint32_t flag)
{
    FlagStatus reval;
    if(RESET != (SAI_STAT(sai_periph, block) & flag)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      clear SAI flag (API_ID: 0x0026U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  flag: specify which flag to clear
                one or more parameters can be selected which are shown as below:
      \arg        SAI_FLAG_OUERR: FIFO overrun or underrun flag
      \arg        SAI_FLAG_MTDET: mute detection flag
      \arg        SAI_FLAG_ERRCK: error clock flag
      \arg        SAI_FLAG_ACNRDY: audio codec not ready flag
      \arg        SAI_FLAG_FSADET: frame synchronization advanced detection flag
      \arg        SAI_FLAG_FSPDET: frame synchronization postpone detection flag
    \param[out] none
    \retval     none
*/
void sai_flag_clear(uint32_t sai_periph, uint32_t block, uint32_t flag)
{
    SAI_INTC(sai_periph, block) = flag;
}

/*!
    \brief      enable SAI interrupt (API_ID: 0x0021U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  interrupt: specify which interrupt to enable
                one or more parameters can be selected which are shown as below:
      \arg        SAI_INT_OUERR: FIFO overrun or underrun interrupt enable
      \arg        SAI_INT_MTDET: mute detection interrupt enable
      \arg        SAI_INT_ERRCK: error clock interrupt enable
      \arg        SAI_INT_FFREQ: FIFO request interrupt enable
      \arg        SAI_INT_ACNRDY: audio codec not ready interrupt enable
      \arg        SAI_INT_FSADET: frame synchronization advanced detection interrupt enable
      \arg        SAI_INT_FSPDET: frame synchronization postpone detection interrupt enable
    \param[out] none
    \retval     none
    \note       in receiver mode, OPTMOD must be configured before FFREQIE is set
*/
void sai_interrupt_enable(uint32_t sai_periph, uint32_t block, uint32_t interrupt)
{
    SAI_INTEN(sai_periph, block) |= interrupt;
}

/*!
    \brief      disable SAI interrupt (API_ID: 0x0022U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  interrupt: specify which interrupt to disable
                one or more parameters can be selected which are shown as below:
      \arg        SAI_INT_OUERR: FIFO overrun or underrun interrupt
      \arg        SAI_INT_MTDET: mute detection interrupt
      \arg        SAI_INT_ERRCK: error clock interrupt
      \arg        SAI_INT_FFREQ: FIFO request interrupt
      \arg        SAI_INT_ACNRDY: audio codec not ready interrupt
      \arg        SAI_INT_FSADET: frame synchronization advanced detection interrupt
      \arg        SAI_INT_FSPDET: frame synchronization postpone detection interrupt
    \param[out] none
    \retval     none
*/
void sai_interrupt_disable(uint32_t sai_periph, uint32_t block, uint32_t interrupt)
{
    SAI_INTEN(sai_periph, block) &= ~interrupt;
}

/*!
    \brief      get SAI interrupt flag (API_ID: 0x0023U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  int_flag: specify which interrupt flag to get
                only one parameter can be selected which is shown as below:
      \arg        SAI_INT_FLAG_OUERR: FIFO overrun or underrun interrupt flag
      \arg        SAI_INT_FLAG_MTDET: mute detection interrupt flag
      \arg        SAI_INT_FLAG_ERRCK: error clock interrupt flag
      \arg        SAI_INT_FLAG_FFREQ: FIFO request interrupt flag
      \arg        SAI_INT_FLAG_ACNRDY: audio codec not ready interrupt flag
      \arg        SAI_INT_FLAG_FSADET: frame synchronization advanced detection interrupt flag
      \arg        SAI_INT_FLAG_FSPDET: frame synchronization postpone detection interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
    \note       the bit position of each SAI_INT_FLAG_x in STAT is the same as the corresponding interrupt enable
                bit in INTEN; after the interrupt enable bit is cleared, this API returns RESET even if the flag
                is still set, so use sai_flag_get() to check the flag in this case
*/
FlagStatus sai_interrupt_flag_get(uint32_t sai_periph, uint32_t block, uint32_t int_flag)
{
    uint32_t inten = 0U;
    FlagStatus reval;

    /* the interrupt enable bit in INTEN has the same position as the flag bit in STAT */
    inten = SAI_INTEN(sai_periph, block) & int_flag;
    if((RESET != (SAI_STAT(sai_periph, block) & int_flag)) && (RESET != inten)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      clear SAI interrupt flag (API_ID: 0x0024U)
    \param[in]  sai_periph: SAIx(x=0,1,2,3)
    \param[in]  block: specify which block is initialized
                only one parameter can be selected which is shown as below:
      \arg        SAI_BLOCK0: SAI block 0
      \arg        SAI_BLOCK1: SAI block 1
    \param[in]  int_flag: specify which interrupt flag to clear
                one or more parameters can be selected which are shown as below:
      \arg        SAI_INT_FLAG_OUERR: FIFO overrun or underrun interrupt flag
      \arg        SAI_INT_FLAG_MTDET: mute detection interrupt flag
      \arg        SAI_INT_FLAG_ERRCK: error clock interrupt flag
      \arg        SAI_INT_FLAG_ACNRDY: audio codec not ready interrupt flag
      \arg        SAI_INT_FLAG_FSADET: frame synchronization advanced detection interrupt flag
      \arg        SAI_INT_FLAG_FSPDET: frame synchronization postpone detection interrupt flag
    \param[out] none
    \retval     none
*/
void sai_interrupt_flag_clear(uint32_t sai_periph, uint32_t block, uint32_t int_flag)
{
    SAI_INTC(sai_periph, block) = int_flag;
}
