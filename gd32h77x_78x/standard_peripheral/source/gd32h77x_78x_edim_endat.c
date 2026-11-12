/*!
    \file    gd32h77x_78x_edim_endat.c
    \brief   EDIM EnDat driver

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

#include "gd32h77x_78x_edim_endat.h"

#define EDIM_ENDAT_CMD_CMD_OFFSET                   24U
#define EDIM_ENDAT_CMD_MEMADDR_OFFSET               16U
#define EDIM_ENDAT_CMD_CDATA_OFFSET                 0U
#define EDIM_ENDAT_ADDINFO_CRC_OFFSET               24U
#define EDIM_ENDAT_ADDINFO_MRS_OFFSET               16U
#define EDIM_ENDAT_ADDINFO_DATA_OFFSET              0U

/*!
    \brief      deinit EDIM_ENDAT (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_endat_deinit(void)
{
    rcu_periph_reset_enable(RCU_ENDATRST);
    rcu_periph_reset_disable(RCU_ENDATRST);
}

/*!
    \brief      initialize EDIM_ENDAT parameter struct with a default value (API_ID(0x0002U))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void edim_endat_parameter_struct_para_init(edim_endat_parameter_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(EDIM_ENDAT_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        initpara->clk_rate = EDIM_ENDAT_TCLK_16_67MHz;
        initpara->filter = EDIM_ENDAT_FILTER_DISABLE;
        initpara->recovery_time = EDIM_ENDAT_RECOVERY_III_1_2_TCLK;
        initpara->watchdog_value = EDIM_ENDAT_TOTH_STOP;
    }
}

/*!
    \brief      initialize EnDat config (API_ID(0x0003U))
    \param[in]  init_struct: init parameter struct
                  clk_rate: EDIM_ENDAT_TCLK_16_67MHz, EDIM_ENDAT_TCLK_8_33MHz, EDIM_ENDAT_TCLK_4_16MHz,
                            EDIM_ENDAT_TCLK_2MHz, EDIM_ENDAT_TCLK_1MHz, EDIM_ENDAT_TCLK_200KHz, EDIM_ENDAT_TCLK_100KHz
                  recovery_time: EDIM_ENDAT_RECOVERY_III_1_2_TCLK,
                                 EDIM_ENDAT_RECOVERY_III_0_5us, EDIM_ENDAT_RECOVERY_III_1us, EDIM_ENDAT_RECOVERY_III_1_5us,
                                 EDIM_ENDAT_RECOVERY_III_2us, EDIM_ENDAT_RECOVERY_III_4us, EDIM_ENDAT_RECOVERY_III_8us,
                                 EDIM_ENDAT_RECOVERY_III_10us
                  filter: EDIM_ENDAT_FILTER_DISABLE,
                          EDIM_ENDAT_FILTER_3CYCLE, EDIM_ENDAT_FILTER_4CYCLE, EDIM_ENDAT_FILTER_5CYCLE, EDIM_ENDAT_FILTER_6CYCLE,
                          EDIM_ENDAT_FILTER_10CYCLE, EDIM_ENDAT_FILTER_20CYCLE, EDIM_ENDAT_FILTER_40CYCLE
                  watchdog_value: EDIM_ENDAT_TOTH_STOP, stop timeout detection
                                  EDIM_ENDAT_TOTH_n_200us(n), config timeout threshold as n * 200us, n = 0~127,
                                  EDIM_ENDAT_TOTH_n_2us(n), config timeout threshold as n * 2us, n = 0~127,
    \param[out] none
    \retval     none
*/
void edim_endat_init(edim_endat_parameter_struct *init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(EDIM_ENDAT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t tmp;
        tmp = EDIM_ENDAT_CFG0;
        tmp &= (~(EDIM_ENDAT_CFG0_TCLK | EDIM_ENDAT_CFG0_CTNCLK));
        tmp |= ((init_struct->clk_rate & EDIM_ENDAT_CFG0_TCLK));
        EDIM_ENDAT_CFG0 = tmp;

        tmp = EDIM_ENDAT_CFG1;
        tmp &= ~(EDIM_ENDAT_CFG1_TOTH | EDIM_ENDAT_CFG1_RCVTIME3 | EDIM_ENDAT_CFG1_FLT);
        tmp |= ((init_struct->watchdog_value & EDIM_ENDAT_CFG1_TOTH) |
                (init_struct->recovery_time & EDIM_ENDAT_CFG1_RCVTIME3) |
                (init_struct->filter & EDIM_ENDAT_CFG1_FLT));
        EDIM_ENDAT_CFG1 = tmp;
    }
}

/*!
    \brief      configure EnDat slave data length (API_ID(0x0004U))
    \param[in]  clk_pulse: number of bits slave data, 8~48
    \param[out] none
    \retval     none
*/
void edim_endat_data_length(uint32_t clk_pulse)
{
    uint32_t tmp;
    tmp = EDIM_ENDAT_CFG0;
    tmp &= (~(EDIM_ENDAT_CFG0_DATALEN));
    tmp |= CFG0_DWLG(clk_pulse);
    EDIM_ENDAT_CFG0 = tmp;
}

/*!
    \brief      enable EnDat auto reset (API_ID(0x0005U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_endat_auto_reset_enable(void)
{
    EDIM_ENDAT_CFG0 |= EDIM_ENDAT_CFG0_AUTORST;
}

/*!
    \brief      disable EnDat auto reset (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_endat_auto_reset_disable(void)
{
    EDIM_ENDAT_CFG0 &= (~EDIM_ENDAT_CFG0_AUTORST);
}

/*!
    \brief      enable EnDat continue clock (API_ID(0x0007U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_endat_continue_clock_enable(void)
{
    EDIM_ENDAT_CFG0 |= EDIM_ENDAT_CFG0_CTNCLK;
}

/*!
    \brief      disable EnDat continue clock (API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_endat_continue_clock_disable(void)
{
    EDIM_ENDAT_CFG0 &= (~EDIM_ENDAT_CFG0_CTNCLK);
}

/*!
    \brief      enable unconditional data update (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_endat_update_unconditional_data_enable(void)
{
    EDIM_ENDAT_CFG0 |= EDIM_ENDAT_CFG0_DCSEL;
}

/*!
    \brief      disable unconditional data update (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_endat_update_unconditional_data_disable(void)
{
    EDIM_ENDAT_CFG0 &= (~EDIM_ENDAT_CFG0_DCSEL);
}

/*!
    \brief      enable cable propagation compensation for EnDat (API_ID(0x000BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_endat_cable_propagation_compensation_enable(void)
{
    EDIM_ENDAT_CFG0 |= EDIM_ENDAT_CFG0_PDTCEN;
}

/*!
    \brief      disable cable propagation compensation for EnDat (API_ID(0x000CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_endat_cable_propagation_compensation_disable(void)
{
    EDIM_ENDAT_CFG0 &= (~EDIM_ENDAT_CFG0_PDTCEN);
}

/*!
    \brief      write cable propagation time for EnDat (API_ID(0x000DU))
    \param[in]  time: cable propagation time, 0~0xFF
    \param[out] none
    \retval     none
*/
void edim_endat_cable_propagation_time_write(uint8_t time)
{
    uint32_t reg_temp;
    reg_temp = EDIM_ENDAT_CFG0;
    reg_temp &= (~EDIM_ENDAT_CFG0_PTIME);
    reg_temp |= (((uint32_t)time << 16U) & EDIM_ENDAT_CFG0_PTIME);
    EDIM_ENDAT_CFG0 = reg_temp;
}

/*!
    \brief      read cable propagation time for EnDat (API_ID(0x000EU))
    \param[in]  none
    \param[out] none
    \retval     cable propagation time: 0~0xFF
*/
uint8_t edim_endat_cable_propagation_time_read(void)
{
    uint32_t reg_temp;
    reg_temp = EDIM_ENDAT_CFG0;
    return (uint8_t)((reg_temp & 0x00FF0000U) >> 16U);
}

/*!
    \brief      configure reset moment for EnDat (API_ID(0x000FU))
    \param[in]  moment: reset moment selection
                only one parameter can be selected which is shown as below:
      \arg        EDIM_ENDAT_RESET_MOMENT_ANY: The EDIM_ENDAT_STAT register can be reset by software at any time
      \arg        EDIM_ENDAT_RESET_MOMENT_UPDATE: The EDIM_ENDAT_STAT register must be reset by software after EDIM_ENDAT_STAT register is fully updated
    \param[out] none
    \retval     none
*/
void edim_endat_reset_moment_select(uint32_t moment)
{
    uint32_t reg_temp;
    reg_temp = EDIM_ENDAT_CFG0;
    reg_temp &= (~EDIM_ENDAT_CFG0_RSTMSEL);
    reg_temp |= (moment & EDIM_ENDAT_CFG0_RSTMSEL);
    EDIM_ENDAT_CFG0 = reg_temp;
}

/*!
    \brief      configure EnDat command (API_ID(0x0010U))
    \param[in]  mode: config Endat frame mode value,
                only one parameter can be selected which is shown as below:
      \arg        EDIM_ENDAT_MODE_GET_POS: Encoder to send position values
      \arg        EDIM_ENDAT_MODE_SEND_POS_ADD_INFO_SELECT_MEM_AREA: Encoder to send position values with additional information and selection of memory area or of the additional information
      \arg        EDIM_ENDAT_MODE_SELECT_MEM_AREA: Selection of memory area
      \arg        EDIM_ENDAT_MODE_RECEIVE_COMM_CMD: Encoder to receive communication command
      \arg        EDIM_ENDAT_MODE_SEND_TEST_VALUE: Encoder to send test values
      \arg        EDIM_ENDAT_MODE_SEND_POS_ADD_INFO_RECEIVE_PARA: Encoder to send position values with additional information and receive parameters
      \arg        EDIM_ENDAT_MODE_RECEIVE_PARA: Encoder to receive parameters
      \arg        EDIM_ENDAT_MODE_SEND_PARA: Encoder to send parameters
      \arg        EDIM_ENDAT_MODE_SEND_POS_ADD_INFO_PARA: Encoder to send position values with additional information and send parameters
      \arg        EDIM_ENDAT_MODE_RECEIVE_RESET: Encoder to receive reset
      \arg        EDIM_ENDAT_MODE_SEND_POS_ADD_INFO_RECEIVE_ERR_RESET: Encoder to send position values with additional information and receive error reset
      \arg        EDIM_ENDAT_MODE_RECEIVE_TEST_CMD: Encoder to receive test command
      \arg        EDIM_ENDAT_MODE_SEND_POS_ADD_INFO_RECEIVE_TEST_CMD: Encoder to send position values with additional information and receive test command
      \arg        EDIM_ENDAT_MODE_SEND_POS_ADD_INFO: Encoder to send position values with additional information
    \param[in]  mrs_addr: MRS code or register address selected, 0~0xFF
    \param[in]  para: parameter to be sent to encoder, 0~0xFFFF
    \param[out] none
    \retval     none
*/
void edim_endat_command(uint32_t mode, uint32_t mrs_addr, uint32_t para)
{
    EDIM_ENDAT_CMD = (((mode << EDIM_ENDAT_CMD_CMD_OFFSET) & EDIM_ENDAT_CMD_CMD) |
                      ((mrs_addr << EDIM_ENDAT_CMD_MEMADDR_OFFSET) & EDIM_ENDAT_CMD_MEMADDR) |
                      ((para << EDIM_ENDAT_CMD_CDATA_OFFSET) & EDIM_ENDAT_CMD_CDATA));
}

/*!
    \brief      start a frame transmit by software (API_ID(0x0011U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_endat_data_transmission_software_trigger(void)
{
    EDIM_ENDAT_SWT = EDIM_ENDAT_SWT_SWTR;
}

/*!
    \brief      reset all registers of EnDat by software (API_ID(0x0012U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_endat_software_reset(void)
{
    EDIM_ENDAT_CFG0 |= EDIM_ENDAT_CFG0_SWRST;
}

/*!
    \brief      configure EnDat hardware trigger (API_ID(0x0013U))
    \param[in]  newstatus: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void edim_endat_hardware_trigger_config(EventStatus newstatus)
{
    if(ENABLE == newstatus) {
        EDIM_ENDAT_CFG0 |= EDIM_ENDAT_CFG0_HWTRGEN;
    } else {
        EDIM_ENDAT_CFG0 &= (~EDIM_ENDAT_CFG0_HWTRGEN);
    }
}

/*!
    \brief      configure EnDat hardware trigger delay (API_ID(0x0014U))
    \param[in]  delay: hardware trigger delay time
                only one parameter can be selected which is shown as below:
      \arg        EDIM_ENDAT_HWTRGDLY_DISABLE: Disable hardware trigger delay
      \arg        EDIM_ENDAT_HWTRGDLY_nCYCLE(n): Hardware trigger delay n * EnDat cycles, n = 3~255
    \param[out] none
    \retval     none
*/
void edim_endat_hardware_trigger_delay_config(uint32_t delay)
{
    uint32_t reg_temp;
    reg_temp = EDIM_ENDAT_CFG1;
    reg_temp &= (~EDIM_ENDAT_CFG1_HWTRGDELAY);
    reg_temp |= (delay & EDIM_ENDAT_CFG1_HWTRGDELAY);
    EDIM_ENDAT_CFG1 = reg_temp;
}

/*!
    \brief      configure EnDat internal timer trigger period (API_ID(0x0015U))
    \param[in]  period: internal timer trigger period
                only one parameter can be selected which is shown as below:
      \arg        EDIM_ENDAT_PERIOD_DISABLE: Disable internal timer trigger
      \arg        EDIM_ENDAT_PERIOD_n_2us(n): Internal timer trigger period as n * 2us, n = 0~127
      \arg        EDIM_ENDAT_PERIOD_n_200us(n): Internal timer trigger period as n * 200us, n = 0~127
    \param[out] none
    \retval     none
*/
void edim_endat_internal_timer_trigger_period_config(uint32_t period)
{
    uint32_t reg_temp;
    reg_temp = EDIM_ENDAT_CFG1;
    reg_temp &= (~EDIM_ENDAT_CFG1_PERIOD);
    reg_temp |= (period & EDIM_ENDAT_CFG1_PERIOD);
    EDIM_ENDAT_CFG1 = reg_temp;
}

/*!
    \brief      enable EnDat DMA (API_ID(0x0016U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_endat_dma_enable(void)
{
    EDIM_ENDAT_CFG0 |= EDIM_ENDAT_CFG0_DFEN;
}

/*!
    \brief      disable EnDat DMA (API_ID(0x0017U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_endat_dma_disable(void)
{
    EDIM_ENDAT_CFG0 &= (~EDIM_ENDAT_CFG0_DFEN);
}

/*!
    \brief      flush EnDat DMA FIFO (API_ID(0x0018U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_endat_dma_flush(void)
{
    EDIM_ENDAT_CFG0 |= EDIM_ENDAT_CFG0_FIFOFH;
}

/*!
    \brief      select EnDat data to DMA FIFO (API_ID(0x0019U))
    \param[in]  reg_selected: DMA request and FIFO enable for EDIM_ENDAT_RDATA0/1/2/3
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_ENDAT_DMA_SEL_RDATA0: DMA request and FIFO enable for EDIM_ENDAT_RDATA0
      \arg        EDIM_ENDAT_DMA_SEL_RDATA1: DMA request and FIFO enable for EDIM_ENDAT_RDATA1
      \arg        EDIM_ENDAT_DMA_SEL_RDATA2: DMA request and FIFO enable for EDIM_ENDAT_RDATA2
      \arg        EDIM_ENDAT_DMA_SEL_RDATA3: DMA request and FIFO enable for EDIM_ENDAT_RDATA3
    \param[out] none
    \retval     none
*/
void edim_endat_dma_select(uint32_t reg_selected)
{
    uint32_t reg_tmp;

    reg_tmp = EDIM_ENDAT_CFG0;
    reg_tmp &= (~(EDIM_ENDAT_CFG0_DFEN0 | EDIM_ENDAT_CFG0_DFEN1 | EDIM_ENDAT_CFG0_DFEN2 | EDIM_ENDAT_CFG0_DFEN3));
    reg_tmp |= (reg_selected & (EDIM_ENDAT_CFG0_DFEN0 | EDIM_ENDAT_CFG0_DFEN1 | EDIM_ENDAT_CFG0_DFEN2 | EDIM_ENDAT_CFG0_DFEN3));
    EDIM_ENDAT_CFG0 = reg_tmp;
}

/*!
    \brief      read EnDat slave data with low 32bit (API_ID(0x001AU))
    \param[in]  none
    \param[out] none
    \retval     slave data with low 32bit: 0~0xFFFFFFFF
*/
uint32_t edim_endat_data_low_read(void)
{
    return EDIM_ENDAT_RDATA0;
}

/*!
    \brief      read EnDat encoder data (API_ID(0x001BU))
    \param[in]  none
    \param[out] none
    \retval     64bit encoder data: 0~0xFFFFFFFFFFFFFFFF
*/
uint64_t edim_endat_data_read(void)
{
    uint64_t reg1;
    uint64_t reg2;
    reg1 = (uint64_t)EDIM_ENDAT_RDATA0;
    reg2 = (((uint64_t)EDIM_ENDAT_RDATA1 & 0x000000000000FFFFU) << 32U);
    return (reg1 | reg2);
}

/*!
    \brief      read EnDat CRC bit in the received data (API_ID(0x001CU))
    \param[in]  none
    \param[out] none
    \retval     received crc of data: 0~0x1F
*/
uint8_t edim_endat_crc_of_data_read(void)
{
    return (uint8_t)((EDIM_ENDAT_RDATA1 & 0x001F0000U) >> 16U);
}

/*!
    \brief      read EnDat F1 bit in the received data (API_ID(0x001DU))
    \param[in]  none
    \param[out] none
    \retval     received f1 of data: 0~0x01
*/
uint8_t edim_endat_f1_of_data_read(void)
{
    return (uint8_t)((EDIM_ENDAT_RDATA1 & 0x00200000U) >> 21U);
}

/*!
    \brief      read EnDat inverse of F2 bit in the received data (API_ID(0x001EU))
    \param[in]  none
    \param[out] none
    \retval     received the inverse f2 of data: 0~0x01
*/
uint8_t edim_endat_inverse_f2_of_data_read(void)
{
    return (uint8_t)((EDIM_ENDAT_RDATA1 & 0x00400000U) >> 22U);
}

/*!
    \brief      read EnDat encoder data from additional information 1 (API_ID(0x001FU))
    \param[in]  none
    \param[out] none
    \retval     received data of additional information 1: 0~0xFFFF
*/
uint16_t edim_endat_additional_info_1_data_read(void)
{
    return (uint16_t)(EDIM_ENDAT_RDATA3 & 0x0000FFFFU);
}

/*!
    \brief      read EnDat encoder data from additional information 2 (API_ID(0x0020U))
    \param[in]  none
    \param[out] none
    \retval     received data of additional information 2: 0~0xFFFF
*/
uint16_t edim_endat_additional_info_2_data_read(void)
{
    return (uint16_t)(EDIM_ENDAT_RDATA2 & 0x0000FFFFU);
}

/*!
    \brief      initialize EDIM_ENDAT additional information struct with a default value (API_ID(0x0021U))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void edim_endat_additional_info_struct_para_init(edim_endat_additional_info_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(EDIM_ENDAT_MODULE_ID, API_ID(0x0021U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        initpara->crc = 0U;
        initpara->data = 0U;
        initpara->mrs_addr = 0U;
    }
}

/*!
    \brief      read entire EnDat encoder additional information 1 (API_ID(0x0022U))
    \param[in]  none
    \param[out] add_info: pointer to address to store additional information 1
    \retval     none
*/
void edim_endat_additional_info_1_read(edim_endat_additional_info_struct *add_info)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(add_info)) {
        fw_debug_report_err(EDIM_ENDAT_MODULE_ID, API_ID(0x0022U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t tmp = EDIM_ENDAT_RDATA3;
        add_info->crc       = (uint8_t)((tmp & EDIM_ENDAT_RDATA3_CRCADD1) >> EDIM_ENDAT_ADDINFO_CRC_OFFSET);
        add_info->mrs_addr  = (uint8_t)((tmp & EDIM_ENDAT_RDATA3_MRSADD1) >> EDIM_ENDAT_ADDINFO_MRS_OFFSET);
        add_info->data      = (uint16_t)(tmp & EDIM_ENDAT_RDATA3_DATAADD1);
    }
}

/*!
    \brief      read entire EnDat encoder additional information 2 (API_ID(0x0023U))
    \param[in]  none
    \param[out] add_info: pointer to address to store additional information 2
    \retval     none
*/
void edim_endat_additional_info_2_read(edim_endat_additional_info_struct *add_info)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(add_info)) {
        fw_debug_report_err(EDIM_ENDAT_MODULE_ID, API_ID(0x0023U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t tmp = EDIM_ENDAT_RDATA2;
        add_info->crc       = (uint8_t)((tmp & EDIM_ENDAT_RDATA2_CRCADD2) >> EDIM_ENDAT_ADDINFO_CRC_OFFSET);
        add_info->mrs_addr  = (uint8_t)((tmp & EDIM_ENDAT_RDATA2_MRSADD2) >> EDIM_ENDAT_ADDINFO_MRS_OFFSET);
        add_info->data      = (uint16_t)(tmp & EDIM_ENDAT_RDATA2_DATAADD2);
    }
}

/*!
    \brief      configure EDIM_ENDAT status update mode (API_ID(0x0024U))
    \param[in]  flag: EDIM_ENDAT flag
                only one parameter can be selected which is shown as below:
      \arg        EDIM_ENDAT_FLAG_BUSY: BUSY bit in EnDat protocol
      \arg        EDIM_ENDAT_FLAG_RM: RM bit in EnDat protocol
      \arg        EDIM_ENDAT_FLAG_WRN: WRN bit in EnDat protocol
    \param[in]  mode: status update mode
                only one parameter can be selected which is shown as below:
      \arg        EDIM_ENDAT_STAT_DYNAMIC: EDIM_ENDAT status dynamic update mode
      \arg        EDIM_ENDAT_STAT_STATIC: EDIM_ENDAT status static update mode
    \param[out] none
    \retval     none
*/
void edim_endat_status_update_mode_config(uint32_t flag, uint32_t mode)
{
    uint32_t reg_tmp = 0U;
    reg_tmp = EDIM_ENDAT_STATUPMODE;
    switch(flag) {
    case EDIM_ENDAT_FLAG_BUSY:
        reg_tmp &= (~EDIM_ENDAT_STATUPMODE_BUSYMIFMODE);
        reg_tmp |= (mode & EDIM_ENDAT_STATUPMODE_BUSYMIFMODE);
        break;
    case EDIM_ENDAT_FLAG_RM:
        reg_tmp &= (~EDIM_ENDAT_STATUPMODE_RMMIFMODE);
        reg_tmp |= ((mode << 1U) & EDIM_ENDAT_STATUPMODE_RMMIFMODE);
        break;
    case EDIM_ENDAT_FLAG_WRN:
        reg_tmp &= (~EDIM_ENDAT_STATUPMODE_WRNMIFMODE);
        reg_tmp |= ((mode << 2U) & EDIM_ENDAT_STATUPMODE_WRNMIFMODE);
        break;
    default:
        break;
    }
    EDIM_ENDAT_STATUPMODE = reg_tmp;
}

/*!
    \brief      enable the EnDat interrupt (API_ID(0x0025U))
    \param[in]  interrupt: specify which interrupt to enable
                one or more parameters can be selected which are shown as below:
      \arg        EDIM_ENDAT_INT_RDATAUP: EDIM_ENDAT_RDATA0 and EDIM_ENDAT_RDATA1 registers update interrupt
      \arg        EDIM_ENDAT_INT_ERR1: error message 1 interrupt
      \arg        EDIM_ENDAT_INT_CRC: CRC error for received data interrupt
      \arg        EDIM_ENDAT_INT_TYPE1: type I error interrupt
      \arg        EDIM_ENDAT_INT_TYPE2: type II error interrupt
      \arg        EDIM_ENDAT_INT_MRSADDR: MRS code or address  error interrupt enable
      \arg        EDIM_ENDAT_INT_RDATA2UP: EDIM_ENDAT_RDATA2 registers update interrupt
      \arg        EDIM_ENDAT_INT_RDATA3UP: EDIM_ENDAT_RDATA3 registers update interrupt
      \arg        EDIM_ENDAT_INT_ERR2: error message 2 interrupt
      \arg        EDIM_ENDAT_INT_CRCADD1: CRC error for additional information 1 interrupt
      \arg        EDIM_ENDAT_INT_CRCADD2: CRC error for additional information 2 interrupt
      \arg        EDIM_ENDAT_INT_BUSY: BUSY bit in EnDat protocol set interrupt
      \arg        EDIM_ENDAT_INT_RM: RM bit in EnDat protocol set interrupt
      \arg        EDIM_ENDAT_INT_WRN: WRN bit in EnDat protocol set interrupt
      \arg        EDIM_ENDAT_INT_SPIKE: spike detection interrupt
      \arg        EDIM_ENDAT_INT_TO: frame transmission timeout interrupt
      \arg        EDIM_ENDAT_INT_TYPE3: type III error interrupt
      \arg        EDIM_ENDAT_INT_FIFOOVR: dma overrun error interrupt
      \arg        EDIM_ENDAT_INT_FIFOUNR: dma underrun error interrupt
      \arg        EDIM_ENDAT_INT_DMATO: dma request timeout interrupt
      \arg        EDIM_ENDAT_INT_DATACHK: all check have been performed and status is updated interrupt
    \param[out] none
    \retval     none
*/
void edim_endat_interrupt_enable(uint32_t interrupt)
{
    EDIM_ENDAT_INTEN |= (interrupt & EDIM_ENDAT_INTEN_MASK);
}

/*!
    \brief      disable the EnDat interrupt (API_ID(0x0026U))
    \param[in]  interrupt: specify which interrupt to enable
                one or more parameters can be selected which are shown as below:
      \arg        EDIM_ENDAT_INT_RDATAUP: EDIM_ENDAT_RDATA0 and EDIM_ENDAT_RDATA1 registers update interrupt
      \arg        EDIM_ENDAT_INT_ERR1: error message 1 interrupt
      \arg        EDIM_ENDAT_INT_CRC: CRC error for received data interrupt
      \arg        EDIM_ENDAT_INT_TYPE1: type I error interrupt
      \arg        EDIM_ENDAT_INT_TYPE2: type II error interrupt
      \arg        EDIM_ENDAT_INT_MRSADDR: MRS code or address  error interrupt enable
      \arg        EDIM_ENDAT_INT_RDATA2UP: EDIM_ENDAT_RDATA2 registers update interrupt
      \arg        EDIM_ENDAT_INT_RDATA3UP: EDIM_ENDAT_RDATA3 registers update interrupt
      \arg        EDIM_ENDAT_INT_ERR2: error message 2 interrupt
      \arg        EDIM_ENDAT_INT_CRCADD1: CRC error for additional information 1 interrupt
      \arg        EDIM_ENDAT_INT_CRCADD2: CRC error for additional information 2 interrupt
      \arg        EDIM_ENDAT_INT_BUSY: BUSY bit in EnDat protocol set interrupt
      \arg        EDIM_ENDAT_INT_RM: RM bit in EnDat protocol set interrupt
      \arg        EDIM_ENDAT_INT_WRN: WRN bit in EnDat protocol set interrupt
      \arg        EDIM_ENDAT_INT_SPIKE: spike detection interrupt
      \arg        EDIM_ENDAT_INT_TO: frame transmission timeout interrupt
      \arg        EDIM_ENDAT_INT_TYPE3: type III error interrupt
      \arg        EDIM_ENDAT_INT_FIFOOVR: dma overrun error interrupt
      \arg        EDIM_ENDAT_INT_FIFOUNR: dma underrun error interrupt
      \arg        EDIM_ENDAT_INT_DMATO: dma request timeout interrupt
      \arg        EDIM_ENDAT_INT_DATACHK: all check have been performed and status is updated interrupt
    \param[out] none
    \retval     none
*/
void edim_endat_interrupt_disable(uint32_t interrupt)
{
    EDIM_ENDAT_INTEN &= (~(interrupt & EDIM_ENDAT_INTEN_MASK));
}

/*!
    \brief      get EnDat flag (API_ID(0x0027U))
    \param[in]  flag: EDIM_ENDAT flag
                one or more parameters can be selected which are shown as below:
      \arg        EDIM_ENDAT_FLAG_RDATAUP: EDIM_ENDAT_RDATA0 and EDIM_ENDAT_RDATA1 registers update flag
      \arg        EDIM_ENDAT_FLAG_ERR1: error message 1 flag
      \arg        EDIM_ENDAT_FLAG_CRC: CRC error for received data flag
      \arg        EDIM_ENDAT_FLAG_TYPE1: type I error interrupt flag
      \arg        EDIM_ENDAT_FLAG_TYPE2: type II error interrupt flag
      \arg        EDIM_ENDAT_FLAG_MRSADDR: MRS or address error interrupt flag
      \arg        EDIM_ENDAT_FLAG_RDATA2UP: EDIM_ENDAT_RDATA2 registers update interrupt flag
      \arg        EDIM_ENDAT_FLAG_RDATA3UP: EDIM_ENDAT_RDATA3 registers update interrupt flag
      \arg        EDIM_ENDAT_FLAG_ERR2: error message 1 flag
      \arg        EDIM_ENDAT_FLAG_CRCADD1: CRC error for additional information 1 flag
      \arg        EDIM_ENDAT_FLAG_CRCADD2: CRC error for additional information 2 flag
      \arg        EDIM_ENDAT_FLAG_BUSY: BUSY bit in EnDat protocol
      \arg        EDIM_ENDAT_FLAG_RM: RM bit in EnDat protocol
      \arg        EDIM_ENDAT_FLAG_WRN: WRN bit in EnDat protocol
      \arg        EDIM_ENDAT_FLAG_SPIKE: spike detection flag
      \arg        EDIM_ENDAT_FLAG_TO: frame transmission timeout flag
      \arg        EDIM_ENDAT_FLAG_TYPE3: type III error interrupt flag
      \arg        EDIM_ENDAT_FLAG_DTC: propagation time compensation flag
      \arg        EDIM_ENDAT_FLAG_PTMC: propagation time measurement complete flag
      \arg        EDIM_ENDAT_FLAG_FIFOOVR: dma overrun error flag
      \arg        EDIM_ENDAT_FLAG_FIFOUNR: dma underrun error flag
      \arg        EDIM_ENDAT_FLAG_DMATO: dma request timeout flag
      \arg        EDIM_ENDAT_FLAG_NEXTRDY: next transmission ready flag
      \arg        EDIM_ENDAT_FLAG_DATACHK: all check have been performed and status is updated flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_endat_flag_get(uint32_t flag)
{
    FlagStatus return_val = RESET;
    if(RESET != (EDIM_ENDAT_STAT & flag)) {
        return_val = SET;
    } else {
        return_val = RESET;
    }
    return return_val;
}

/*!
    \brief      clear EnDat flag (API_ID(0x0028U))
    \param[in]  flag: EDIM_ENDAT flag
                one or more parameters can be selected which are shown as below:
      \arg        EDIM_ENDAT_FLAG_RDATAUP: EDIM_ENDAT_RDATA0 and EDIM_ENDAT_RDATA1 registers update flag
      \arg        EDIM_ENDAT_FLAG_ERR1: error message 1 flag
      \arg        EDIM_ENDAT_FLAG_CRC: CRC error for received data flag
      \arg        EDIM_ENDAT_FLAG_TYPE1: type I error interrupt flag
      \arg        EDIM_ENDAT_FLAG_TYPE2: type II error interrupt flag
      \arg        EDIM_ENDAT_FLAG_MRSADDR: MRS or address error interrupt flag
      \arg        EDIM_ENDAT_FLAG_RDATA2UP: EDIM_ENDAT_RDATA2 registers update interrupt flag
      \arg        EDIM_ENDAT_FLAG_RDATA3UP: EDIM_ENDAT_RDATA3 registers update interrupt flag
      \arg        EDIM_ENDAT_FLAG_ERR2: error message 1 flag
      \arg        EDIM_ENDAT_FLAG_CRCADD1: CRC error for additional information 1 flag
      \arg        EDIM_ENDAT_FLAG_CRCADD2: CRC error for additional information 2 flag
      \arg        EDIM_ENDAT_FLAG_BUSY: BUSY bit in EnDat protocol
      \arg        EDIM_ENDAT_FLAG_RM: RM bit in EnDat protocol
      \arg        EDIM_ENDAT_FLAG_WRN: WRN bit in EnDat protocol
      \arg        EDIM_ENDAT_FLAG_SPIKE: spike detection flag
      \arg        EDIM_ENDAT_FLAG_TO: frame transmission timeout flag
      \arg        EDIM_ENDAT_FLAG_TYPE3: type III error interrupt flag
      \arg        EDIM_ENDAT_FLAG_DTC: propagation time compensation flag
      \arg        EDIM_ENDAT_FLAG_PTMC: propagation time measurement complete flag
      \arg        EDIM_ENDAT_FLAG_FIFOOVR: dma overrun error flag
      \arg        EDIM_ENDAT_FLAG_FIFOUNR: dma underrun error flag
      \arg        EDIM_ENDAT_FLAG_DMATO: dma request timeout flag
      \arg        EDIM_ENDAT_FLAG_NEXTRDY: next transmission ready flag
      \arg        EDIM_ENDAT_FLAG_DATACHK: all check have been performed and status is updated flag
    \param[out] none
    \retval     none
*/
void edim_endat_flag_clear(uint32_t flag)
{
    EDIM_ENDAT_STAT = (flag & EDIM_ENDAT_FLAG_MASK);
}

/*!
    \brief      get EnDat interrupt flag (API_ID(0x0029U))
    \param[in]  int_flag: EDIM_ENDAT interrupt flag
                only one parameter can be selected which are shown as below:
      \arg        EDIM_ENDAT_INT_FLAG_RDATAUP: EDIM_ENDAT_RDATA0 and EDIM_ENDAT_RDATA1 registers update interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_ERR1: error message 1 interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_CRC: CRC error for received data interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_TYPE1: type I error interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_TYPE2: type II error interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_MRSADDR: MRS code or address  error interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_RDATA2UP: EDIM_ENDAT_RDATA2 registers update interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_RDATA3UP: EDIM_ENDAT_RDATA3 registers update interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_ERR2: error message 2 interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_CRCADD1: CRC error for additional information 1 interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_CRCADD2: CRC error for additional information 2 interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_BUSY: BUSY bit in EnDat protocol set interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_RM: RM bit in EnDat protocol set interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_WRN: WRN bit in EnDat protocol set interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_SPIKE: spike detection interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_TO: frame transmission timeout interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_TYPE3: type III error interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_FIFOOVR: dma overrun error interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_FIFOUNR: dma underrun error interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_DMATO: dma request timeout interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_DATACHK: all check have been performed and status is updated interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
    \Note       After the interrupt enable bit is cleared, if the hardware flag remains set, this API will still return RESET.
                Therefore, in an ISR or during the interrupt-disable flow, this API alone must not be relied upon to determine whether the flag should be cleared.
                The corresponding flag must be cleared according to the module-specific rules, and the NVIC-pending bit should also be cleared when necessary.
*/
FlagStatus edim_endat_interrupt_flag_get(edim_endat_interrupt_flag_enum int_flag)
{
    uint32_t ret1 = RESET;
    uint32_t ret2 = RESET;
    FlagStatus return_val = RESET;

    /* get the status of interrupt enable bit  */
    ret1 = (EDIM_ENDAT_REG_VAL(EDIM_ENDAT, int_flag) & BIT(EDIM_ENDAT_BIT_POS(int_flag)));
    /* get the status of interrupt flag */
    ret2 = (EDIM_ENDAT_REG_VAL2(EDIM_ENDAT, int_flag) & BIT(EDIM_ENDAT_BIT_POS2(int_flag)));
    if(EDIM_ENDAT_INT_FLAG_ERR2 == int_flag) {
        if(SET == ret2) {
            ret2 = RESET;
        } else {
            ret2 = SET;
        }
    }
    if(ret1 && ret2) {
        return_val = SET;
    } else {
        return_val = RESET;
    }
    return return_val;
}

/*!
    \brief      clear EnDat interrupt flag (API_ID(0x002AU))
    \param[in]  int_flag: specify which interrupt flag to clear
                only one parameter can be selected which are shown as below:
      \arg        EDIM_ENDAT_INT_FLAG_RDATAUP: EDIM_ENDAT_RDATA0 and EDIM_ENDAT_RDATA1 registers update interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_ERR1: error message 1 interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_CRC: CRC error for received data interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_TYPE1: type I error interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_TYPE2: type II error interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_MRSADDR: MRS code or address  error interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_RDATA2UP: EDIM_ENDAT_RDATA2 registers update interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_RDATA3UP: EDIM_ENDAT_RDATA3 registers update interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_ERR2: error message 2 interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_CRCADD1: CRC error for additional information 1 interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_CRCADD2: CRC error for additional information 2 interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_BUSY: BUSY bit in EnDat protocol set interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_RM: RM bit in EnDat protocol set interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_WRN: WRN bit in EnDat protocol set interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_SPIKE: spike detection interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_TO: frame transmission timeout interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_TYPE3: type III error interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_FIFOOVR: dma overrun error interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_FIFOUNR: dma underrun error interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_DMATO: dma request timeout interrupt flag
      \arg        EDIM_ENDAT_INT_FLAG_DATACHK: all check have been performed and status is updated interrupt flag
    \param[out] none
    \retval     none
*/
void edim_endat_interrupt_flag_clear(edim_endat_interrupt_flag_enum int_flag)
{
    EDIM_ENDAT_STAT = BIT(EDIM_ENDAT_BIT_POS2(int_flag));
}
