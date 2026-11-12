/*!
    \file    gd32h77x_78x_edim_biss.c
    \brief   EDIM BISSC driver

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

#include "gd32h77x_78x_edim_biss.h"

#define MAX_SLAVE_NUMBER          8U

/*!
    \brief      deinit EDIM_BISS (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_biss_deinit(void)
{
    rcu_periph_reset_enable(RCU_BISSRST);
    rcu_periph_reset_disable(RCU_BISSRST);
}

/*!
    \brief      initialize EDIM_BISS init parameter struct with a default value (API_ID(0x0002U))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void edim_biss_init_parameter_struct_para_init(edim_biss_init_parameter_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(EDIM_BISS_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        initpara->ma_force_control_level = EDIM_BISS_MA_NO_FORCE_CONTROL;
        initpara->ma_prescaler = 0U;
        initpara->n_slave = 0U;
        for(uint32_t cnt = 0U; cnt < 8U; cnt++) {
            initpara->slave_config[cnt].crc_init_value = 0U;
            initpara->slave_config[cnt].crc_poly = EDIM_BISS_SLAVE_CRC_NO_CRC;
            initpara->slave_config[cnt].data_length = 1U;
        }
    }
}

/*!
    \brief      initialize EDIM_BISS configuration (API_ID(0x0003U))
    \param[in]  init_struct: init parameter struct
                  ma_prescaler: prescaler value of the EDIM_BISS clock, fMA = fPCLK / (x + 1), x = 7~32767
                  ma_force_control_level: EDIM_BISS_MA_NO_FORCE_CONTROL,
                                          EDIM_BISS_MA_FORCE_LEVEL_LOW, EDIM_BISS_MA_FORCE_LEVEL_HIGH
                  n_slave: number of connected slave, 0~8
                  slave_config: pointer to slave configuration structure
                                data_length: length of process data in bits, 1~64
                                crc_poly: EDIM_BISS_SLAVE_CRC_NO_CRC, EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC3_0x0B,
                                          EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC4_0x13, EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC5_0x25,
                                          EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC6_0x43, EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC7_0x89,
                                          EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC8_0x12F, EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC16_0x190D9,
                                          EDIM_BISS_SLAVE_CRC_CUSTOM(x), x is a maximum of 8-bit crc polynomial and the lowest bit is 1
                                crc_init_value: initial value for crc calculation, 0~0xFFFF
    \param[out] none
    \retval     none
*/
void edim_biss_init(edim_biss_init_parameter_struct *init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(EDIM_BISS_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t reg_tmp;
        uint32_t cnt_slave;

        reg_tmp = EDIM_BISS_CCFG2;
        reg_tmp &= (~(EDIM_BISS_CCFG2_MAFRE | EDIM_BISS_CCFG2_MALVL | EDIM_BISS_CCFG2_MACSEL));
        reg_tmp |= ((CTL_MAFRE(init_struct->ma_prescaler) & EDIM_BISS_CCFG2_MAFRE) |
                    (init_struct->ma_force_control_level & (EDIM_BISS_CCFG2_MACSEL | EDIM_BISS_CCFG2_MALVL)));
        EDIM_BISS_CCFG2 = reg_tmp;

        if(init_struct->n_slave <= MAX_SLAVE_NUMBER) {
            for(cnt_slave = 0U; cnt_slave < init_struct->n_slave; cnt_slave++) {
                reg_tmp = (((init_struct->slave_config[cnt_slave].crc_init_value << 16U) & EDIM_BISS_SnPDTCFG_CRCIVAL) |
                           (init_struct->slave_config[cnt_slave].crc_poly & (EDIM_BISS_SnPDTCFG_CRCPOLY | EDIM_BISS_SnPDTCFG_CRCMSEL)) |
                           (((init_struct->slave_config[cnt_slave].data_length - 1U) << 0U) & EDIM_BISS_SnPDTCFG_PDLEN));


                EDIM_BISS_SnPDTCFG(cnt_slave) = reg_tmp;
            }
        }

        for(; cnt_slave < MAX_SLAVE_NUMBER; cnt_slave++) {
            EDIM_BISS_SnPDTCFG(cnt_slave) = 0U;
        }
    }
}

/*!
    \brief      initialize BiSS-C slave and clear rest of the slave (API_ID(0x0004U))
    \param[in]  n_slave: number of BiSS-C slave to be config, 0~8
    \param[in]  slave_config: pointer to all slave parameter's struct array, the array size should equal to n_slave
                  data_length: slave data length, x = 1~64
                  crc_poly: slave crc polynomial configuration,
                            EDIM_BISS_SLAVE_CRC_NO_CRC,
                            EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC3_0x0B,
                            EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC4_0x13,
                            EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC5_0x25,
                            EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC6_0x43,
                            EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC7_0x89,
                            EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC8_0x12F,
                            EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC16_0x190D9,
                            EDIM_BISS_SLAVE_CRC_CUSTOM(x), x is a maximum of 8-bit crc polynomial and the lowest bit is 1
                  crc_init_value: slave crc init value configuration, 0~0xFFFF
    \param[out] none
    \retval     none
*/
void edim_biss_slave_config(uint32_t n_slave, edim_biss_slave_parameter_struct slave_config[])
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(slave_config)) {
        fw_debug_report_err(EDIM_BISS_MODULE_ID, API_ID(0x0004U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t reg_tmp;
        uint32_t cnt_slave;

        if(n_slave <= MAX_SLAVE_NUMBER) {
            for(cnt_slave = 0U; cnt_slave < n_slave; cnt_slave++) {
                reg_tmp = (((slave_config[cnt_slave].crc_init_value << 16U) & EDIM_BISS_SnPDTCFG_CRCIVAL) |
                           (slave_config[cnt_slave].crc_poly & EDIM_BISS_SnPDTCFG_CRCPOLY) |
                           (((slave_config[cnt_slave].data_length - 1U) << 0U) & EDIM_BISS_SnPDTCFG_PDLEN));

                EDIM_BISS_SnPDTCFG(cnt_slave) = reg_tmp;
            }
        }
        for(; cnt_slave < MAX_SLAVE_NUMBER; cnt_slave++) {
            EDIM_BISS_SnPDTCFG(cnt_slave) = 0U;
        }
    }
}

/*!
    \brief      enable specified BiSS-C slave (API_ID(0x0005U))
    \param[in]  slave: the slave to be enabled
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_BISS_SLAVE0: slave id 0
      \arg        EDIM_BISS_SLAVE1: slave id 1
      \arg        EDIM_BISS_SLAVE2: slave id 2
      \arg        EDIM_BISS_SLAVE3: slave id 3
      \arg        EDIM_BISS_SLAVE4: slave id 4
      \arg        EDIM_BISS_SLAVE5: slave id 5
      \arg        EDIM_BISS_SLAVE6: slave id 6
      \arg        EDIM_BISS_SLAVE7: slave id 7
      \arg        EDIM_BISS_ALLSLAVE: all slaves
    \param[out] none
    \retval     none
*/
void edim_biss_slave_enable(uint32_t slave)
{
    uint32_t cnt_slave = 0U;
    for(cnt_slave = 0U; cnt_slave < MAX_SLAVE_NUMBER; cnt_slave++) {
        if(0U != (slave & (0x80U >> cnt_slave))) {
            EDIM_BISS_SnPDTCFG(cnt_slave) |= EDIM_BISS_SnPDTCFG_PDTEN;
        }
    }
}

/*!
    \brief      disable specified BiSS-C slave (API_ID(0x0006U))
    \param[in]  slave: the slave to be disable
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_BISS_SLAVE0: slave id 0
      \arg        EDIM_BISS_SLAVE1: slave id 1
      \arg        EDIM_BISS_SLAVE2: slave id 2
      \arg        EDIM_BISS_SLAVE3: slave id 3
      \arg        EDIM_BISS_SLAVE4: slave id 4
      \arg        EDIM_BISS_SLAVE5: slave id 5
      \arg        EDIM_BISS_SLAVE6: slave id 6
      \arg        EDIM_BISS_SLAVE7: slave id 7
      \arg        EDIM_BISS_ALLSLAVE: all slaves
    \param[out] none
    \retval     none
*/
void edim_biss_slave_disable(uint32_t slave)
{
    uint32_t cnt_slave = 0U;
    for(cnt_slave = 0U; cnt_slave < MAX_SLAVE_NUMBER; cnt_slave++) {
        if(0U != (slave & (0x80U >> cnt_slave))) {
            EDIM_BISS_SnPDTCFG(cnt_slave) &= (~EDIM_BISS_SnPDTCFG_PDTEN);
        }
    }
}

/*!
    \brief      send BiSS-C initialization sequence (API_ID(0x0007U))
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void edim_biss_initialization_sequence_config(ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        EDIM_BISS_CCFG2 |= EDIM_BISS_CCFG2_TINIT;
    } else {
        EDIM_BISS_CCFG2 &= (~EDIM_BISS_CCFG2_TINIT);
    }
}

/*!
    \brief      stop current BiSS-C communication (API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_biss_break(void)
{
    EDIM_BISS_CCFG2 |= EDIM_BISS_CCFG2_BRKDT;
}

/*!
    \brief      initialize EDIM_BISS control communication struct with a default value (API_ID(0x0009U))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void edim_biss_control_comm_struct_para_init(edim_biss_control_comm_struct *ctrl_comm_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(ctrl_comm_struct)) {
        fw_debug_report_err(EDIM_BISS_MODULE_ID, API_ID(0x0009U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ctrl_comm_struct->reg_addr = 0U;
        ctrl_comm_struct->reg_n_byte = 1U;
        ctrl_comm_struct->reg_r_w = EDIM_BISS_CCOMM_REG_READ;
        ctrl_comm_struct->slave_id = 0U;
        for(uint32_t cnt = 0U; cnt < 64U; cnt++) {
            ctrl_comm_struct->r_w_data[cnt] = 0U;
        }
    }
}

/*!
    \brief      configure BiSS-C register communication to be sent (API_ID(0x000AU))
    \param[in]  ctrl_comm_struct: control communication struct
                  reg_r_w: register communication mode,
                           EDIM_BISS_CCOMM_REG_READ, EDIM_BISS_CCOMM_REG_WRITE
                  slave_id: slave id to be accessed, 0~7
                  reg_addr: register start address, 0~0x7F
                  r_w_data: context array to be sent (when reg_r_w = EDIM_BISS_CCOMM_REG_WRITE),
                            r_w_data[] = 0, (don't care when reg_r_w = EDIM_BISS_CCOMM_REG_READ),
                  reg_n_byte: number of byte to be access, 1~64
    \param[out] none
    \retval     none
*/
void edim_biss_reg_access(edim_biss_control_comm_struct *ctrl_comm_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(ctrl_comm_struct)) {
        fw_debug_report_err(EDIM_BISS_MODULE_ID, API_ID(0x000AU), ERR_PARAM_POINTER);
    } else if(NOT_VALID_POINTER(ctrl_comm_struct->r_w_data)) {
        fw_debug_report_err(EDIM_BISS_MODULE_ID, API_ID(0x000AU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t reg_tmp;
        uint32_t reg_cnt;
        uint32_t reg_cnt_loop4;
        uint32_t reg_cnt_ccdata;

        reg_tmp = ((ctrl_comm_struct->reg_r_w & EDIM_BISS_CCFG0_REGWRSEL) |
                   CTLCOMMCFG0_REGADDR(ctrl_comm_struct->reg_addr) |
                   CTLCOMMCFG0_REGNUM(ctrl_comm_struct->reg_n_byte - 1U));
        EDIM_BISS_CCFG0 = reg_tmp;

        reg_tmp = EDIM_BISS_CCFG1;
        reg_tmp &= (~(EDIM_BISS_CCFG1_CTS | EDIM_BISS_CCFG1_CMD));
        reg_tmp |= (EDIM_BISS_CCFG1_CTS |
                    CTLCOMMCFG1_SLAVEID(ctrl_comm_struct->slave_id));
        EDIM_BISS_CCFG1 = reg_tmp;

        reg_tmp = 0U;
        if(EDIM_BISS_CCOMM_REG_WRITE == ctrl_comm_struct->reg_r_w) {
            for(reg_cnt_ccdata = 0U; reg_cnt_ccdata < 16U; reg_cnt_ccdata++) {
                EDIM_BISS_CCDATAx(reg_cnt_ccdata) = 0U;
            }
            for(reg_cnt = 0U; reg_cnt < ctrl_comm_struct->reg_n_byte; reg_cnt++) {
                reg_cnt_loop4 = reg_cnt % 4U;
                reg_tmp |= (uint32_t)((uint32_t)(ctrl_comm_struct->r_w_data[reg_cnt]) << (reg_cnt_loop4 * 8U));
                if(3U == reg_cnt_loop4) {
                    EDIM_BISS_CCDATAx((reg_cnt / 4U)) = reg_tmp;
                    reg_tmp = 0U;
                }
            }

            if(3U != reg_cnt_loop4) {
                EDIM_BISS_CCDATAx((reg_cnt / 4U)) = reg_tmp;
            }
        }
    }
}

/*!
    \brief      configure BiSS-C command communication to be sent (API_ID(0x000BU))
    \param[in]  slave_id: slave id to be accessed,
                when using BiSS Command frame, one or more parameter can be selected which is shown as below:
      \arg        EDIM_BISS_SLAVE0: slave id 0
      \arg        EDIM_BISS_SLAVE1: slave id 1
      \arg        EDIM_BISS_SLAVE2: slave id 2
      \arg        EDIM_BISS_SLAVE3: slave id 3
      \arg        EDIM_BISS_SLAVE4: slave id 4
      \arg        EDIM_BISS_SLAVE5: slave id 5
      \arg        EDIM_BISS_SLAVE6: slave id 6
      \arg        EDIM_BISS_SLAVE7: slave id 7
      \arg        EDIM_BISS_ALLSLAVE: all slaves
                when using broadcast BiSS command frame, only one parameter can be selected which is shown as below:
      \arg        EDIM_BISS_SLAVE_BROADCAST: broadcast slaves
    \param[in]  cmd_value: slave command,
                only one parameter can be selected which is shown as below:
      \arg        EDIM_BISS_CMD_CHECKIDA(cmd): after successful checking of the ID acknowledge bit, send BiSS command frame, cmd = 0~3
      \arg        EDIM_BISS_CMD_ALWAYSEXE(cmd): send BiSS command frame without IDA check, cmd = 0~3
    \param[out] none
    \retval     none
*/
void edim_biss_command(uint32_t slave_id, uint32_t cmd_value)
{
    uint32_t reg_tmp;

    reg_tmp = EDIM_BISS_CCFG1;
    reg_tmp &= (~(EDIM_BISS_CCFG1_CTS | EDIM_BISS_CCFG1_CMD));
    reg_tmp |= (cmd_value & EDIM_BISS_CCFG1_CMD);
    EDIM_BISS_CCFG1 = reg_tmp;

    EDIM_BISS_CCDATAx(0U) = slave_id;
}

/*!
    \brief      start a new BiSS-C frame with specified mode (API_ID(0x000CU))
    \param[in]  frame_config: slave id to be accessed,
                only one parameter can be selected which is shown as below:
      \arg        EDIM_BISS_STOP: no further frame will be sent
      \arg        EDIM_BISS_SEND_SINGLE_DATA_FRAME_WITH_CDM_1: it will send one frame with CDM = 1
      \arg        EDIM_BISS_SEND_SINGLE_DATA_FRAME_WITH_CDM_0: it will send one frame with CDM = 0
      \arg        EDIM_BISS_SEND_SINGLE_DATA_FRAME_WITH_CDM_INVERSE_CDS: it will send one frame with CDM equal to inversed CDS
      \arg        EDIM_BISS_SEND_SINGLE_CTRL_FRAME: it will send one frame with control communication
      \arg        EDIM_BISS_SEND_SINGLE_CTRL_REDUCED_FRAME: it will send a reduced frame with control communication
      \arg        EDIM_BISS_SEND_AUTO_DATA_FRAME_WITH_CDM_1: it will send frame with CDM = 1 in ADT mode
      \arg        EDIM_BISS_SEND_AUTO_DATA_FRAME_WITH_CDM_0: it will send frame with CDM = 0 in ADT mode
      \arg        EDIM_BISS_SEND_AUTO_DATA_FRAME_WITH_CDM_INVERSE_CDS: it will send frame with CDM equal to inversed CDS in ADT mode
      \arg        EDIM_BISS_SEND_AUTO_CTRL_FRAME: it will send frame with control communication in ADT mode
      \arg        EDIM_BISS_SEND_AUTO_CTRL_REDUCED_FRAME: it will send reduced frame with control communication in ADT mode
    \param[out] none
    \retval     none
*/
void edim_biss_send_frame(uint32_t frame_config)
{
    uint32_t reg_tmp;
    
    reg_tmp = EDIM_BISS_CCFG2;

    if(0U != (reg_tmp & EDIM_BISS_CCFG2_ADTEN)){
        if(0U != (reg_tmp & EDIM_BISS_CCFG2_FCTL)){
            reg_tmp &= ~(EDIM_BISS_CCFG2_ADTEN);
            while(RESET == edim_biss_flag_get(EDIM_BISS_FLAG_EOFT)){
            }
            while(RESET != edim_biss_flag_get(EDIM_BISS_FLAG_EOFT)){
            }
            EDIM_BISS_CCFG2 = reg_tmp;
            while(RESET == edim_biss_flag_get(EDIM_BISS_FLAG_EOFT)){
            }
        }
        else{
            reg_tmp &= ~(EDIM_BISS_CCFG2_ADTEN);
            EDIM_BISS_CCFG2 = reg_tmp;
        }
    }

    reg_tmp &= ~(EDIM_BISS_CCFG2_FCTL | EDIM_BISS_CCFG2_ADTEN);
    reg_tmp |= frame_config;
    EDIM_BISS_CCFG2 = reg_tmp;
}

/*!
    \brief      configure prescale value of automatic data transmission mode (API_ID(0x000DU))
    \param[in]  prescaler: prescale value for ADT mode
                only one parameter can be selected which is shown as below:
      \arg        EDIM_BISS_AUTO_DATA_TRANSMIT_RATE_MAX: automatic send new BiSS-C frame after last frame has been finished
      \arg        EDIM_BISS_AUTO_DATA_TRANSMIT_EXT_TRIGGER: automatic send new BiSS-C frame by external trigger
      \arg        EDIM_BISS_AUTO_DATA_TRANSMIT_RATE_DIV(x): automatic send new BiSS-C frame by predefined ADT frequency, x = 0x000006, 0x000008, ... ,0x200000 (even number)
    \param[out] none
    \retval     none
*/
void edim_biss_auto_transmission_config(uint32_t prescaler)
{
    EDIM_BISS_FREP = prescaler;
}

/*!
    \brief      store process data CRC value into EDIM_BISS_SnDATA0/1 (API_ID(0x000EU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_biss_store_crc_enable(void)
{
    EDIM_BISS_CCFG1 &= (~EDIM_BISS_CCFG1_CRCSEN);
}

/*!
    \brief      not store process data CRC value into EDIM_BISS_SnDATA0/1 (API_ID(0x000FU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_biss_store_crc_disable(void)
{
    EDIM_BISS_CCFG1 |= EDIM_BISS_CCFG1_CRCSEN;
}

/*!
    \brief      select ram bank number used for process data (API_ID(0x0010U))
    \param[in]  rambank_num: number of RAM banks, 1 or 2
    \param[out] none
    \retval     none
*/
void edim_biss_rambank_number_select(uint32_t rambank_num)
{
    if(1U == rambank_num) {
        EDIM_BISS_CCFG1 |= EDIM_BISS_CCFG1_RAMNUM;
    } else if(2U == rambank_num) {
        EDIM_BISS_CCFG1 &= (~EDIM_BISS_CCFG1_RAMNUM);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      enable automatic ram bank switching (API_ID(0x0011U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_biss_rambank_auto_switching_enable(void)
{
    EDIM_BISS_CCFG2 &= (~EDIM_BISS_CCFG2_RBSWDIS);
}

/*!
    \brief      disable automatic ram bank switching (API_ID(0x0012U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_biss_rambank_auto_switching_disable(void)
{
    EDIM_BISS_CCFG2 |= EDIM_BISS_CCFG2_RBSWDIS;
}

/*!
    \brief      force ram bank switching (API_ID(0x0013U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_biss_rambank_force_switching(void)
{
    if(RESET == (EDIM_BISS_CCFG2 & EDIM_BISS_CCFG2_RBSW)) {
        EDIM_BISS_CCFG2 |= EDIM_BISS_CCFG2_RBSW;
    } else {
        EDIM_BISS_CCFG2 &= (~EDIM_BISS_CCFG2_RBSW);
    }
}

/*!
    \brief      select MA signal level at the end of frame (API_ID(0x0014U))
    \param[in]  ma_level: MA signal level
                only one parameter can be selected which is shown as below:
      \arg        EDIM_BISS_MA_HIGH_END: after the slave timeout is detected on SL, MA changes to the digital high level
      \arg        EDIM_BISS_MA_MAINTAIN_END: MA maintains level until the next frame begins
    \param[out] none
    \retval     none
*/
void edim_biss_ma_end_level_select(uint32_t ma_level)
{
    uint32_t reg_tmp;

    reg_tmp = EDIM_BISS_CCFG1;
    reg_tmp &= (~EDIM_BISS_CCFG1_MASEL);
    reg_tmp |= (ma_level & EDIM_BISS_CCFG1_MASEL);
    EDIM_BISS_CCFG1 = reg_tmp;
}

/*!
    \brief      configure master clock prescaler for process data (API_ID(0x0015U))
    \param[in]  prescaler: prescaler value, x = 7~32767, fMA = fPCLK / (x + 1)
    \param[out] none
    \retval     none
*/
void edim_biss_ma_prescaler_config(uint32_t prescaler)
{
    uint32_t reg_tmp;
    
    reg_tmp = EDIM_BISS_CCFG2;
    reg_tmp &= (~EDIM_BISS_CCFG2_MAFRE);
    reg_tmp |= CTL_MAFRE(prescaler) & EDIM_BISS_CCFG2_MAFRE;
    EDIM_BISS_CCFG2 = reg_tmp;
}

/*!
    \brief      enable dma for BiSS-C slave data receive (API_ID(0x0016U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_biss_dma_enable(void)
{
    EDIM_BISS_DFCTL |= EDIM_BISS_DFCTL_DFEN;
}

/*!
    \brief      disable dma for BiSS-C slave data receive (API_ID(0x0017U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_biss_dma_disable(void)
{
    EDIM_BISS_DFCTL &= (~EDIM_BISS_DFCTL_DFEN);
}

/*!
    \brief      flush dma fifo (API_ID(0x0018U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_biss_dma_flush(void)
{
    EDIM_BISS_DFCTL |= EDIM_BISS_DFCTL_FIFOFH;
}

/*!
    \brief      select slave process data to be loaded into DMA FIFO (API_ID(0x0019U))
    \param[in]  reg_selected: select slave n data register,
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_BISS_DMA_SEL_SLV0_DATA0: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S0RDATA0 register
      \arg        EDIM_BISS_DMA_SEL_SLV0_DATA1: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S0RDATA1 register
      \arg        EDIM_BISS_DMA_SEL_SLV1_DATA0: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S1RDATA0 register
      \arg        EDIM_BISS_DMA_SEL_SLV1_DATA1: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S1RDATA1 register
      \arg        EDIM_BISS_DMA_SEL_SLV2_DATA0: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S2RDATA0 register
      \arg        EDIM_BISS_DMA_SEL_SLV2_DATA1: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S2RDATA1 register
      \arg        EDIM_BISS_DMA_SEL_SLV3_DATA0: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S3RDATA0 register
      \arg        EDIM_BISS_DMA_SEL_SLV3_DATA1: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S3RDATA1 register
      \arg        EDIM_BISS_DMA_SEL_SLV4_DATA0: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S4RDATA0 register
      \arg        EDIM_BISS_DMA_SEL_SLV4_DATA1: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S4RDATA1 register
      \arg        EDIM_BISS_DMA_SEL_SLV5_DATA0: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S5RDATA0 register
      \arg        EDIM_BISS_DMA_SEL_SLV5_DATA1: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S5RDATA1 register
      \arg        EDIM_BISS_DMA_SEL_SLV6_DATA0: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S6RDATA0 register
      \arg        EDIM_BISS_DMA_SEL_SLV6_DATA1: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S6RDATA1 register
      \arg        EDIM_BISS_DMA_SEL_SLV7_DATA0: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S7RDATA0 register
      \arg        EDIM_BISS_DMA_SEL_SLV7_DATA1: EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S7RDATA1 register
    \param[out] none
    \retval     none
*/
void edim_biss_dma_select(uint32_t reg_selected)
{
    uint32_t reg_tmp;

    reg_tmp = EDIM_BISS_DFCTL;
    reg_tmp &= (~(EDIM_BISS_DFCTL_DMA_DFEN));
    reg_tmp |= (reg_selected & EDIM_BISS_DFCTL_DMA_DFEN);
    EDIM_BISS_DFCTL = reg_tmp;
}

/*!
    \brief      read EDIM_BISS SnRDATA0/1 (API_ID(0x001AU))
    \param[in]  slave_id: slave id, 0~7
    \param[out] none
    \retval     the received data value: 0~0xFFFFFFFFFFFFFFFF
*/
uint64_t edim_biss_data_read(uint32_t slave_id)
{
    uint64_t reg1;
    uint64_t reg2;
    reg1 = (uint64_t)EDIM_BISS_SnDATA0(slave_id);
    reg2 = ((uint64_t)EDIM_BISS_SnDATA1(slave_id)) << 32U;
    return (reg1 | reg2);
}

/*!
    \brief      configure the count value from the BiSS frame's slave response ACK to the CDM timeout confirmation bit (API_ID(0x001BU))
    \param[in]  frame_cnt: frame count value, 0~0x1FFF
    \param[out] none
    \retval     none
*/
void edim_biss_frame_count_value_config(uint32_t frame_cnt)
{
    uint32_t reg_tmp;

    reg_tmp = EDIM_BISS_CNTINTEN;
    reg_tmp &= (~(EDIM_BISS_CNTINTEN_FCNT));
    reg_tmp |= ((frame_cnt << 16) & EDIM_BISS_CNTINTEN_FCNT);
    EDIM_BISS_CNTINTEN = reg_tmp;
}

/*!
    \brief      get the number of valid register from addressed slave in register communication (API_ID(0x001CU))
    \param[in]  none
    \param[out] none
    \retval     the valid register number: 0~0x3F
*/
uint8_t edim_biss_valid_reg_num_get(void)
{
    return (uint8_t)((EDIM_BISS_STAT0 & EDIM_BISS_STAT0_VREGNUM) >> 24);
}

/*!
    \brief      get the number of slaves in control communication (API_ID(0x001DU))
    \param[in]  none
    \param[out] none
    \retval     the slave number: 0~0x09
*/
uint8_t edim_biss_slave_num_get(void)
{
    return (uint8_t)((EDIM_BISS_STAT1 & EDIM_BISS_STAT1_SLNUM) >> 16);
}

/*!
    \brief      enable EDIM_BISS interrupt (API_ID(0x001EU))
    \param[in]  interrupt: EDIM_BISS interrupt
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_BISS_INT_EODTIE: end of data transmission interrupt enable
      \arg        EDIM_BISS_INT_CCERRIE: control communication error interrupt enable
      \arg        EDIM_BISS_INT_PDTERRIE: process data transmission error interrupt enable
      \arg        EDIM_BISS_INT_SERRIE: start bit error interrupt enable
      \arg        EDIM_BISS_INT_ADTERRIE: automatic data transmission error interrupt enable
      \arg        EDIM_BISS_INT_DMATOIE: DMA request timeout error interrupt enable
      \arg        EDIM_BISS_INT_FIFOUNRIE: FIFO underrun interrupt enable
      \arg        EDIM_BISS_INT_FIFOOVRIE: FIFO overrun interrupt enable
    \param[out] none
    \retval     none
*/
void edim_biss_interrupt_enable(uint32_t interrupt)
{
    EDIM_BISS_CNTINTEN |= (interrupt & EDIM_BISS_INTEN_MASK);
}

/*!
    \brief      disable EDIM_BISS interrupt (API_ID(0x001FU))
    \param[in]  interrupt: EDIM_BISS interrupt
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_BISS_INT_EODTIE: end of data transmission interrupt enable
      \arg        EDIM_BISS_INT_CCERRIE: control communication error interrupt enable
      \arg        EDIM_BISS_INT_PDTERRIE: process data transmission error interrupt enable
      \arg        EDIM_BISS_INT_SERRIE: start bit error interrupt enable
      \arg        EDIM_BISS_INT_ADTERRIE: automatic data transmission error interrupt enable
      \arg        EDIM_BISS_INT_DMATOIE: DMA request timeout error interrupt enable
      \arg        EDIM_BISS_INT_FIFOUNRIE: FIFO underrun interrupt enable
      \arg        EDIM_BISS_INT_FIFOOVRIE: FIFO overrun interrupt enable
    \param[out] none
    \retval     none
*/
void edim_biss_interrupt_disable(uint32_t interrupt)
{
    EDIM_BISS_CNTINTEN &= (~(interrupt & EDIM_BISS_INTEN_MASK));
}

/*!
    \brief      get EDIM_BISS flag (API_ID(0x0020U))
    \param[in]  flag: the EDIM_BISS flags
                only one parameter can be selected which is shown as below:
      \arg        EDIM_BISS_FLAG_EODT: data transmission finish flag
      \arg        EDIM_BISS_FLAG_EOFT: data transmission finish flag
      \arg        EDIM_BISS_FLAG_EOCC: control communication transmission finish flag
      \arg        EDIM_BISS_FLAG_CCERRN: no control communication transmission error flag
      \arg        EDIM_BISS_FLAG_PDTERRN: no data transmission error flag
      \arg        EDIM_BISS_FLAG_SERRN: no start bit error flag
      \arg        EDIM_BISS_FLAG_ADTERRN: no automatic data transmission error flag
      \arg        EDIM_BISS_FLAG_INERRN: no internal error flag
      \arg        EDIM_BISS_FLAG_SLAVE0_DATA_VALID: slave 0 data valid flag
      \arg        EDIM_BISS_FLAG_SLAVE1_DATA_VALID: slave 1 data valid flag
      \arg        EDIM_BISS_FLAG_SLAVE2_DATA_VALID: slave 2 data valid flag
      \arg        EDIM_BISS_FLAG_SLAVE3_DATA_VALID: slave 3 data valid flag
      \arg        EDIM_BISS_FLAG_SLAVE4_DATA_VALID: slave 4 data valid flag
      \arg        EDIM_BISS_FLAG_SLAVE5_DATA_VALID: slave 5 data valid flag
      \arg        EDIM_BISS_FLAG_SLAVE6_DATA_VALID: slave 6 data valid flag
      \arg        EDIM_BISS_FLAG_SLAVE7_DATA_VALID: slave 7 data valid flag
      \arg        EDIM_BISS_FLAG_CDS: current CDS value
      \arg        EDIM_BISS_FLAG_CDMTOF: CDM timeout complete flag
      \arg        EDIM_BISS_FLAG_SLIN: current SL line level
      \arg        EDIM_BISS_FLAG_CDSBU: current CDS value (backup)
      \arg        EDIM_BISS_FLAG_RBSWERR: ram bank error flag
      \arg        EDIM_BISS_FLAG_DMATO: DMA timeout error flag
      \arg        EDIM_BISS_FLAG_FIFOUNR: FIFO underrun error flag
      \arg        EDIM_BISS_FLAG_FIFOOVR: FIFO overrun error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_biss_flag_get(edim_biss_flag_enum flag)
{
    FlagStatus return_val = RESET;
    /* get the BiSS-C flag */
    if(RESET != (EDIM_BISS_REG_VAL(EDIM_BISS, (uint32_t)flag) & BIT(EDIM_BISS_BIT_POS(flag)))) {
        return_val = SET;
    } else {
        return_val = RESET;
    }
    return return_val;
}

/*!
    \brief      clear EDIM_BISS flag (API_ID(0x0021U))
    \param[in]  flag: the EDIM_BISS flags
                only one parameter can be selected which is shown as below:
      \arg        EDIM_BISS_FLAG_EODT: data transmission finish flag
      \arg        EDIM_BISS_FLAG_EOFT: data transmission finish flag
      \arg        EDIM_BISS_FLAG_EOCC: control communication transmission finish flag
      \arg        EDIM_BISS_FLAG_CCERRN: no control communication transmission error flag
      \arg        EDIM_BISS_FLAG_PDTERRN: no data transmission error flag
      \arg        EDIM_BISS_FLAG_SERRN: no start bit error flag
      \arg        EDIM_BISS_FLAG_ADTERRN: no automatic data transmission error flag
      \arg        EDIM_BISS_FLAG_SLAVE0_DATA_VALID: slave 0 data valid flag
      \arg        EDIM_BISS_FLAG_SLAVE1_DATA_VALID: slave 1 data valid flag
      \arg        EDIM_BISS_FLAG_SLAVE2_DATA_VALID: slave 2 data valid flag
      \arg        EDIM_BISS_FLAG_SLAVE3_DATA_VALID: slave 3 data valid flag
      \arg        EDIM_BISS_FLAG_SLAVE4_DATA_VALID: slave 4 data valid flag
      \arg        EDIM_BISS_FLAG_SLAVE5_DATA_VALID: slave 5 data valid flag
      \arg        EDIM_BISS_FLAG_SLAVE6_DATA_VALID: slave 6 data valid flag
      \arg        EDIM_BISS_FLAG_SLAVE7_DATA_VALID: slave 7 data valid flag
      \arg        EDIM_BISS_FLAG_CDS: current CDS value
      \arg        EDIM_BISS_FLAG_CDMTOF: CDM timeout complete flag
      \arg        EDIM_BISS_FLAG_SLIN: current SL line level
      \arg        EDIM_BISS_FLAG_CDSBU: current CDS value (backup)
      \arg        EDIM_BISS_FLAG_RBSWERR: ram bank error flag
      \arg        EDIM_BISS_FLAG_DMATO: DMA timeout error flag
      \arg        EDIM_BISS_FLAG_FIFOUNR: FIFO underrun error flag
      \arg        EDIM_BISS_FLAG_FIFOOVR: FIFO overrun error flag
    \param[out] none
    \retval     none
*/
void edim_biss_flag_clear(edim_biss_flag_enum flag)
{
    EDIM_BISS_REG_VAL(EDIM_BISS, (uint32_t)flag) = BIT(EDIM_BISS_BIT_POS(flag));
}

/*!
    \brief      get EDIM_BISS interrupt flag (API_ID(0x0022U))
    \param[in]  int_flag: the EDIM_BISS interrupt flags
                only one parameter can be selected which is shown as below:
      \arg        EDIM_BISS_INT_FLAG_EODT: data transmission finish interrupt flag
      \arg        EDIM_BISS_INT_FLAG_CCERR: control communication transmission error interrupt flag
      \arg        EDIM_BISS_INT_FLAG_PDTERR: data transmission error interrupt flag
      \arg        EDIM_BISS_INT_FLAG_SERR: start bit error interrupt flag
      \arg        EDIM_BISS_INT_FLAG_ADTERR: automatic data transmission error interrupt flag
      \arg        EDIM_BISS_INT_FLAG_DMATO: DMA timeout error interrupt flag
      \arg        EDIM_BISS_INT_FLAG_FIFOUNR: FIFO underrun error interrupt flag
      \arg        EDIM_BISS_INT_FLAG_FIFOOVR: FIFO overrun error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
    \Note       After the interrupt enable bit is cleared, if the hardware flag remains set, this API will still return RESET.
                Therefore, in an ISR or during the interrupt-disable flow, this API alone must not be relied upon to determine whether the flag should be cleared.
                The corresponding flag must be cleared according to the module-specific rules, and the NVIC-pending bit should also be cleared when necessary.
*/
FlagStatus edim_biss_interrupt_flag_get(edim_biss_interrupt_flag_enum int_flag)
{
    uint32_t ret1 = RESET;
    uint32_t ret2 = RESET;
    FlagStatus return_val = RESET;

    /* get the status of interrupt enable bit */
    ret1 = (EDIM_BISS_REG_VAL(EDIM_BISS, (uint32_t)int_flag) & BIT(EDIM_BISS_BIT_POS(int_flag)));
    /* get the status of interrupt flag */
    ret2 = (EDIM_BISS_REG_VAL2(EDIM_BISS, int_flag) & BIT(EDIM_BISS_BIT_POS2(int_flag)));

    if((EDIM_BISS_INT_FLAG_CCERR == int_flag) || (EDIM_BISS_INT_FLAG_PDTERR == int_flag) ||
       (EDIM_BISS_INT_FLAG_SERR == int_flag) || (EDIM_BISS_INT_FLAG_ADTERR == int_flag)) {
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
    \brief      clear EDIM_BISS interrupt flag (API_ID(0x0023U))
    \param[in]  int_flag: the EDIM_BISS interrupt flags
                only one parameter can be selected which is shown as below:
      \arg        EDIM_BISS_INT_FLAG_EODT: data transmission finish interrupt flag
      \arg        EDIM_BISS_INT_FLAG_CCERR: control communication transmission error interrupt flag
      \arg        EDIM_BISS_INT_FLAG_PDTERR: data transmission error interrupt flag
      \arg        EDIM_BISS_INT_FLAG_SERR: start bit error interrupt flag
      \arg        EDIM_BISS_INT_FLAG_ADTERR: automatic data transmission error interrupt flag
      \arg        EDIM_BISS_INT_FLAG_DMATO: DMA timeout error interrupt flag
      \arg        EDIM_BISS_INT_FLAG_FIFOUNR: FIFO underrun error interrupt flag
      \arg        EDIM_BISS_INT_FLAG_FIFOOVR: FIFO overrun error interrupt flag
    \param[out] none
    \retval     none
*/
void edim_biss_interrupt_flag_clear(edim_biss_interrupt_flag_enum int_flag)
{
    EDIM_BISS_REG_VAL2(EDIM_BISS, int_flag) = BIT(EDIM_BISS_BIT_POS2(int_flag));
}
