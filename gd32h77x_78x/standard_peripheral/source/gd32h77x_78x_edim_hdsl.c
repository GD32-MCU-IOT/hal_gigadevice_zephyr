/*!
    \file    gd32h77x_78x_edim_hdsl.c
    \brief   EDIM HDSL driver

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

#include "gd32h77x_78x_edim_hdsl.h"

#define EDIM_HDSL_EVENT_S_MASK             ((uint8_t)0x7FU)

/*!
    \brief      deinit EDIM_HDSL (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_hdsl_deinit(void)
{
    rcu_periph_reset_enable(RCU_HDSLRST);
    rcu_periph_reset_disable(RCU_HDSLRST);
}

/*!
    \brief      initialize EDIM_HDSL (API_ID(0x0002U))
    \param[in]  es: external synchronization,
                0x00,position sampling during free running at the shortest cycle time
                others: position sampling with the SYNC input synchronized. es determines the number of position samplings carried out in one SYNC cycle.
    \param[in]  sync_polarity: sync edge selection
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_SYNC_LEADING: the SYNC leading edge is used
      \arg        EDIM_HDSL_SYNC_TRAILING: the SYNC trailing edge is used
    \param[in]  acc_err_cnt: position error count threshold, 0~0x1F
    \param[out] none
    \retval     none
*/
void edim_hdsl_init(uint8_t es, uint8_t sync_polarity, uint8_t acc_err_cnt)
{
    EDIM_HDSL_SYNC_CTRL = es;
    EDIM_HDSL_SYS_CTRL &= (uint8_t)(~EDIM_HDSL_SYS_CTRL_SPOL);
    EDIM_HDSL_SYS_CTRL |= (uint8_t)sync_polarity;
    EDIM_HDSL_ACC_ERR_CNT = acc_err_cnt;

}

/*!
    \brief      activation of the output (API_ID(0x0003U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_hdsl_output_enable(void)
{
    EDIM_HDSL_SYS_CTRL |= (uint8_t)EDIM_HDSL_SYS_CTRL_OEN;
}

/*!
    \brief      unactivation of the output (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_hdsl_output_disable(void)
{
    EDIM_HDSL_SYS_CTRL &= (uint8_t)(~EDIM_HDSL_SYS_CTRL_OEN);

}

/*!
    \brief      test drive interface (API_ID(0x0005U))
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void edim_hdsl_test_drive_interface(ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        EDIM_HDSL_SYS_CTRL |= (uint8_t)EDIM_HDSL_SYS_CTRL_LOOP;
    } else {
        EDIM_HDSL_SYS_CTRL &= (uint8_t)(~EDIM_HDSL_SYS_CTRL_LOOP);
    }
}

/*!
    \brief      reset pipeline FIFO (API_ID(0x0006U))
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void edim_hdsl_pipeline_fifo_reset(ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        EDIM_HDSL_SYS_CTRL |= (uint8_t)EDIM_HDSL_SYS_CTRL_FRST;
    } else {
        EDIM_HDSL_SYS_CTRL &= (uint8_t)(~EDIM_HDSL_SYS_CTRL_FRST);
    }
}

/*!
    \brief      reset message (API_ID(0x0007U))
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void edim_hdsl_message_reset(ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        EDIM_HDSL_SYS_CTRL |= (uint8_t)EDIM_HDSL_SYS_CTRL_MRST;
    } else {
        EDIM_HDSL_SYS_CTRL &= (uint8_t)(~EDIM_HDSL_SYS_CTRL_MRST);
    }
}

/*!
    \brief      reset protocol status (API_ID(0x0008U))
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void edim_hdsl_protocol_reset(ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        EDIM_HDSL_SYS_CTRL |= (uint8_t)EDIM_HDSL_SYS_CTRL_PRST;
    } else {
        EDIM_HDSL_SYS_CTRL &= (uint8_t)(~EDIM_HDSL_SYS_CTRL_PRST);
    }
}

/*!
    \brief      get quality monitoring bits (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     quality monitoring(QM): 0~0x0F
*/
uint8_t edim_hdsl_quality_monitoring_get(void)
{
    return (uint8_t)(EDIM_HDSL_MASTER_QM & EDIM_HDSL_MASTER_QM_QM);
}

/*!
    \brief      get DSL protocol connection status (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     DSL protocol connection: SET or RESET
*/
FlagStatus edim_hdsl_protocol_connection_status_get(void)
{
    FlagStatus reval = RESET;
    if(0U == (EDIM_HDSL_MASTER_QM & EDIM_HDSL_MASTER_QM_LINK)) {
        reval = RESET;
    } else {
        reval = SET;
    }
    return reval;
}

/*!
    \brief      get edges in cable signal (API_ID(0x000BU))
    \param[in]  none
    \param[out] none
    \retval     identification of edges in the cable signal: 0~0x0F
*/
uint8_t edim_hdsl_cable_signal_edge_get(void)
{
    return EDIM_HDSL_EDGES;
}

/*!
    \brief      get cable delay (API_ID(0x000CU))
    \param[in]  none
    \param[out] none
    \retval     4-bit value for cable delay: 0~0x09
*/
uint8_t edim_hdsl_cable_delay_get(void)
{
    return (uint8_t)(EDIM_HDSL_DELAY & EDIM_HDSL_DELAY_CBLDLY);
}

/*!
    \brief      get received signal strength (API_ID(0x000DU))
    \param[in]  none
    \param[out] none
    \retval     4-bit value for received signal strength: 0~0x0C
*/
uint8_t edim_hdsl_received_signal_strength_get(void)
{
    return (uint8_t)((EDIM_HDSL_DELAY & EDIM_HDSL_DELAY_RSSI) >> 4);
}


/*!
    \brief      version information (API_ID(0x000EU))
    \param[in]  none
    \param[out] none
    \retval     version number: 0~0xFF
*/
uint8_t edim_hdsl_version_get(void)
{
    return EDIM_HDSL_VERSION;
}

/*!
    \brief      get encoder ID information (API_ID(0x000FU))
    \param[in]  none
    \param[out] none
    \retval     encoder ID: 0~0xFFFFFFFF
*/
uint32_t edim_hdsl_encoder_id_get(void)
{
    uint32_t enc_id;
    /* get Encoder ID */
    enc_id = ((uint32_t)EDIM_HDSL_ENC_ID2 & 0x7FU);
    enc_id = ((uint32_t)EDIM_HDSL_ENC_ID1 | (enc_id << 8U));
    enc_id = ((uint32_t)EDIM_HDSL_ENC_ID0 | (enc_id << 8U));
    return enc_id;

}

/*!
    \brief      get fast position (API_ID(0x0010U))
    \param[in]  none
    \param[out] none
    \retval     fast position: 0~0xFFFFFFFFFFFFFFFF
*/
uint64_t edim_hdsl_position_read(void)
{
    uint64_t pos;
    pos = EDIM_HDSL_POS4;
    pos = EDIM_HDSL_POS3 | (pos << 8);
    pos = EDIM_HDSL_POS2 | (pos << 8);
    pos = EDIM_HDSL_POS1 | (pos << 8);
    pos = EDIM_HDSL_POS0 | (pos << 8);
    return pos;
}

/*!
    \brief      get safe position (API_ID(0x0011U))
    \param[in]  none
    \param[out] none
    \retval     safe position: 0~0xFFFFFFFFFFFFFFFF
*/
uint64_t edim_hdsl_vposition_read(void)
{
    uint64_t vpos;
    vpos = EDIM_HDSL_VPOS4;
    vpos = EDIM_HDSL_VPOS3 | (vpos << 8);
    vpos = EDIM_HDSL_VPOS2 | (vpos << 8);
    vpos = EDIM_HDSL_VPOS1 | (vpos << 8);
    vpos = EDIM_HDSL_VPOS0 | (vpos << 8);
    return vpos;
}

/*!
    \brief      get safe position value from safe channel 2 (API_ID(0x0012U))
    \param[in]  none
    \param[out] none
    \retval     safe position: 0~0xFFFFFFFFFFFFFFFF
*/
uint64_t edim_hdsl_vposition2_read(void)
{
    uint64_t vpos;
    vpos = EDIM_HDSL_VPOS24;
    vpos = EDIM_HDSL_VPOS23 | (vpos << 8);
    vpos = EDIM_HDSL_VPOS22 | (vpos << 8);
    vpos = EDIM_HDSL_VPOS21 | (vpos << 8);
    vpos = EDIM_HDSL_VPOS20 | (vpos << 8);
    return vpos;
}

/*!
    \brief      get speed (API_ID(0x0013U))
    \param[in]  none
    \param[out] none
    \retval     speed: 0~0xFFFFFF
*/
uint32_t edim_hdsl_speed_read(void)
{
    uint32_t vel;
    vel = EDIM_HDSL_VEL2;
    vel = EDIM_HDSL_VEL1 | (vel << 8);
    vel = EDIM_HDSL_VEL0 | (vel << 8);
    return vel;
}

/*!
    \brief      get mirror status summary flag (API_ID(0x0014U))
    \param[in]  none
    \param[out] none
    \retval     Status summary flag: 0~0xFF
*/
uint8_t edim_hdsl_mirror_status_sum_flag_get(void)
{
    return EDIM_HDSL_MIR_SUM;
}

/*!
    \brief      write parameter channel buffer (API_ID(0x0015U))
    \param[in]  data: parameter channel buffer to be sent,8 bytes
    \param[out] none
    \retval     none
*/
void edim_hdsl_long_message_write(uint64_t data)
{
    EDIM_HDSL_PC_BUFFER0 = (uint8_t)data;
    EDIM_HDSL_PC_BUFFER1 = (uint8_t)(data >> 8);
    EDIM_HDSL_PC_BUFFER2 = (uint8_t)(data >> 16);
    EDIM_HDSL_PC_BUFFER3 = (uint8_t)(data >> 24);
    EDIM_HDSL_PC_BUFFER4 = (uint8_t)(data >> 32);
    EDIM_HDSL_PC_BUFFER5 = (uint8_t)(data >> 40);
    EDIM_HDSL_PC_BUFFER6 = (uint8_t)(data >> 48);
    EDIM_HDSL_PC_BUFFER7 = (uint8_t)(data >> 56);
}

/*!
    \brief      read the answer to a long message in parameter channel buffer (API_ID(0x0016U))
    \param[in]  none
    \param[out] none
    \retval     answer to a long message: 0~0xFFFFFFFFFFFFFFFF
*/
uint64_t edim_hdsl_long_message_read(void)
{
    uint64_t data;
    data = EDIM_HDSL_PC_BUFFER7;
    data = EDIM_HDSL_PC_BUFFER6 | (data << 8);
    data = EDIM_HDSL_PC_BUFFER5 | (data << 8);
    data = EDIM_HDSL_PC_BUFFER4 | (data << 8);
    data = EDIM_HDSL_PC_BUFFER3 | (data << 8);
    data = EDIM_HDSL_PC_BUFFER2 | (data << 8);
    data = EDIM_HDSL_PC_BUFFER1 | (data << 8);
    data = EDIM_HDSL_PC_BUFFER0 | (data << 8);
    return data;
}

/*!
    \brief      read errors in encoder resources arising from the previous "long message" operation (API_ID(0x0017U))
    \param[in]  none
    \param[out] none
    \retval     long message errors: 0~0xFFFF
*/
uint16_t edim_hdsl_long_message_error_read(void)
{
    uint16_t data;
    data = (uint16_t)EDIM_HDSL_PC_BUFFER1;
    data = (uint16_t)EDIM_HDSL_PC_BUFFER0 | ((uint16_t)(data << 8));
    return data;
}

/*!
    \brief      initialize EDIM_HDSL long message address struct with a default value (API_ID(0x0018U))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void edim_hdsl_long_message_addr_init_struct_para_init(edim_hdsl_long_msg_addr_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(EDIM_HDSL_MODULE_ID, API_ID(0x0018U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        initpara->direction = EDIM_HDSL_LONG_MSG_WRITE;
        initpara->d_i_mode = EDIM_HDSL_LONG_MSG_DIRECT;
        initpara->laddh = 0U;
        initpara->laddl = 0U;
        initpara->ladd_off_h = 0U;
        initpara->ladd_off_l = 0U;
        initpara->len = (uint8_t)EDIM_HDSL_LONG_MSG_LEN_0;
        initpara->offset = EDIM_HDSL_LONG_MSG_WITHOUT_OFFSET;
    }
}

/*!
    \brief      long message send address initialization (API_ID(0x0019U))
    \param[in]  msg_addr_struct: the data needed to be sent
                  direction: EDIM_HDSL_LONG_MSG_WRITE, EDIM_HDSL_LONG_MSG_READ
                  offset: EDIM_HDSL_LONG_MSG_WITHOUT_OFFSET, EDIM_HDSL_LONG_MSG_OFFSET
                  d_i_mode: EDIM_HDSL_LONG_MSG_DIRECT, EDIM_HDSL_LONG_MSG_INDIRECT
                  len: EDIM_HDSL_LONG_MSG_LEN_0, EDIM_HDSL_LONG_MSG_LEN_2, EDIM_HDSL_LONG_MSG_LEN_4, EDIM_HDSL_LONG_MSG_LEN_8
                  laddh: long message address, bit 9 to bit 8
                  laddl: long message address, bit 7 to bit 0
                  ladd_off_l: long message offset value, bit 7 to bit 0
                  ladd_off_h: long message offset value, bit 14 to bit 8
    \param[out] none
    \retval     none
*/
void edim_hdsl_long_message_addr_init(edim_hdsl_long_msg_addr_struct *msg_addr_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(msg_addr_struct)) {
        fw_debug_report_err(EDIM_HDSL_MODULE_ID, API_ID(0x0019U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure long message send address */
        EDIM_HDSL_PC_ADD_H &= (uint8_t)(~(EDIM_HDSL_PC_ADD_H_LADDH | EDIM_HDSL_PC_ADD_H_LLEN | EDIM_HDSL_PC_ADD_H_LIND | EDIM_HDSL_PC_ADD_H_LOFF |
                             EDIM_HDSL_PC_ADD_H_LRW));
        EDIM_HDSL_PC_ADD_H |= (uint8_t)((msg_addr_struct->direction & EDIM_HDSL_PC_ADD_H_LRW) | (msg_addr_struct->d_i_mode & EDIM_HDSL_PC_ADD_H_LIND) |
                           (msg_addr_struct->len & EDIM_HDSL_PC_ADD_H_LLEN) | (msg_addr_struct->offset & EDIM_HDSL_PC_ADD_H_LOFF) |
                           (msg_addr_struct->laddh & EDIM_HDSL_PC_ADD_H_LADDH));
        EDIM_HDSL_PC_ADD_L = msg_addr_struct->laddl;
        EDIM_HDSL_PC_OFF_H = (msg_addr_struct->ladd_off_h | 0x80U);
        EDIM_HDSL_PC_OFF_L = msg_addr_struct->ladd_off_l;
    }
}

/*!
    \brief      long message error flag get (API_ID(0x001AU))
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_hdsl_long_message_error_flag_get(void)
{
    FlagStatus reval = RESET;
    if(RESET != (EDIM_HDSL_PC_ADD_H & EDIM_HDSL_PC_ADD_H_LOFF)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      configure long message addressing offset mode (API_ID(0x001BU))
    \param[in]  mode: long message addressing offset mode
                EDIM_HDSL_LONG_MSG_WITHOUT_OFFSET: long message addressing without offset
                EDIM_HDSL_LONG_MSG_OFFSET: long message addressing with offset
    \param[out] none
    \retval     none
*/
void edim_hdsl_long_message_addr_offset_mode_config(uint8_t mode)
{
    if(EDIM_HDSL_LONG_MSG_WITHOUT_OFFSET == mode) {
        EDIM_HDSL_PC_ADD_H &= (uint8_t)(~EDIM_HDSL_PC_ADD_H_LOFF);
    } else if(EDIM_HDSL_LONG_MSG_OFFSET == mode) {
        EDIM_HDSL_PC_ADD_H |= (uint8_t)(EDIM_HDSL_PC_ADD_H_LOFF);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure long message read / write mode (API_ID(0x001CU))
    \param[in]  mode: long message read / write mode
                EDIM_HDSL_LONG_MSG_WRITE: long message write mode
                EDIM_HDSL_LONG_MSG_READ: long message read mode
    \param[out] none
    \retval     none
*/
void edim_hdsl_long_message_read_write_mode_config(uint8_t mode)
{
    if(EDIM_HDSL_LONG_MSG_WRITE == mode) {
        EDIM_HDSL_PC_ADD_H &= (uint8_t)(~EDIM_HDSL_PC_ADD_H_LRW);
    } else if(EDIM_HDSL_LONG_MSG_READ == mode) {
        EDIM_HDSL_PC_ADD_H |= (uint8_t)(EDIM_HDSL_PC_ADD_H_LRW);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure long message addressing direction mode (API_ID(0x001DU))
    \param[in]  mode: long message addressing direction mode
                EDIM_HDSL_LONG_MSG_DIRECT: long message direct addressing
                EDIM_HDSL_LONG_MSG_INDIRECT: long message indirect addressing
    \param[out] none
    \retval     none
*/
void edim_hdsl_long_message_addr_direction_config(uint8_t mode)
{
    if(EDIM_HDSL_LONG_MSG_DIRECT == mode) {
        EDIM_HDSL_PC_ADD_H &= (uint8_t)(~EDIM_HDSL_PC_ADD_H_LIND);
    } else if(EDIM_HDSL_LONG_MSG_INDIRECT == mode) {
        EDIM_HDSL_PC_ADD_H |= (uint8_t)(EDIM_HDSL_PC_ADD_H_LIND);
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure long message data length (API_ID(0x001EU))
    \param[in]  length: long message data length
                EDIM_HDSL_LONG_MSG_LEN_0: no data
                EDIM_HDSL_LONG_MSG_LEN_2: data length is 2 bytes
                EDIM_HDSL_LONG_MSG_LEN_4: data length is 4 bytes
                EDIM_HDSL_LONG_MSG_LEN_8: data length is 8 bytes
    \param[out] none
    \retval     none
*/
void edim_hdsl_long_message_data_length_config(uint8_t length)
{
    EDIM_HDSL_PC_ADD_H &= (uint8_t)(~EDIM_HDSL_PC_ADD_H_LLEN);
    EDIM_HDSL_PC_ADD_H |= (uint8_t)(length & EDIM_HDSL_PC_ADD_H_LLEN);
}

/*!
    \brief      configure long message address (API_ID(0x001FU))
    \param[in]  laddh: long message address, bit 9 to bit 8
    \param[in]  laddl: long message address, bit 7 to bit 0
    \param[out] none
    \retval     none
*/
void edim_hdsl_long_message_addr_config(uint8_t laddh, uint8_t laddl)
{
    EDIM_HDSL_PC_ADD_H &= (uint8_t)(~EDIM_HDSL_PC_ADD_H_LADDH);
    EDIM_HDSL_PC_ADD_H |= (uint8_t)(laddh & EDIM_HDSL_PC_ADD_H_LADDH);
    EDIM_HDSL_PC_ADD_L = laddl;
}

/*!
    \brief      configure long message address offset (API_ID(0x0020U))
    \param[in]  ladd_off_h: long message offset value, bit 14 to bit 8 
    \param[in]  ladd_off_l: long message offset value, bit 7 to bit 0
    \param[out] none
    \retval     none
*/
void edim_hdsl_long_message_addr_offset_config(uint8_t ladd_off_h, uint8_t ladd_off_l)
{
    EDIM_HDSL_PC_OFF_H = (ladd_off_h | 0x80U);
    EDIM_HDSL_PC_OFF_L = ladd_off_l;
}

/*!
    \brief      start "long message" transaction (API_ID(0x0021U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_hdsl_long_message_transaction_start(void)
{
    EDIM_HDSL_PC_CTRL |= (uint8_t)EDIM_HDSL_PC_CTRL_LSTA;
}

/*!
    \brief      get sensorhub channel flag (API_ID(0x0022U))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_SENSORHUB_FLAG_PSCI: Indication for special characters in the SensorHub Channel
      \arg        EDIM_HDSL_SENSORHUB_FLAG_PERR: Coding error of the bits in the SensorHub Channel
      \arg        EDIM_HDSL_SENSORHUB_FLAG_PEMP: The SensorHub channel buffer is empty
      \arg        EDIM_HDSL_SENSORHUB_FLAG_POVR: SensorHub Channel overflow

    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_hdsl_sensorhub_channel_flag_get(uint32_t flag)
{
    FlagStatus reval = RESET;
    if(RESET != (EDIM_HDSL_PIPE_S & flag)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      read sensorhub channel data (API_ID(0x0023U))
    \param[in]  none
    \param[out] none
    \retval     8 bit value of the FIFO buffer for SensorHub Channel data: 0~0xFF
*/
uint8_t edim_hdsl_sensorhub_channel_data_read(void)
{
    return EDIM_HDSL_PIPE_D;
}

/*!
    \brief      read short message mirror data (API_ID(0x0024U))
    \param[in]  none
    \param[out] none
    \retval     8-bit value of the requested mirror register: 0~0xFF
*/
uint8_t edim_hdsl_short_message_mirror_data_read(void)
{
    return EDIM_HDSL_PC_DATA;
}

/*!
    \brief      read position error count (API_ID(0x0025U))
    \param[in]  none
    \param[out] none
    \retval     5-bit value of count of transmitted fast position values with consecutive transmission errors: 0~0x1F
*/
uint8_t edim_hdsl_position_error_count_read(void)
{
    return (uint8_t)(EDIM_HDSL_ACC_ERR_CNT & EDIM_HDSL_ACC_ERR_CNT_CNT);
}

/*!
    \brief      configure fast position acceleration boundary (API_ID(0x0026U))
    \param[in]  mantissa: mantissa of fast position acceleration boundary, 0~0x3F, |accmax| = mantissa * resolution
    \param[in]  resolution: resolution of fast position acceleration boundary, 0~0x03
                EDIM_HDSL_MAXACC_RES_256: resolution is 256
                EDIM_HDSL_MAXACC_RES_64: resolution is 64
                EDIM_HDSL_MAXACC_RES_16: resolution is 16
                EDIM_HDSL_MAXACC_RES_4: resolution is 4
    \param[out] none
    \retval     none
*/
void edim_hdsl_fast_position_acc_boundary_config(uint8_t mantissa, uint8_t resolution)
{
    EDIM_HDSL_MAXACC = (uint8_t)(((uint8_t)(resolution << 6) & EDIM_HDSL_MAXACC_RES) | (uint8_t)(mantissa & EDIM_HDSL_MAXACC_MNT));
}

/*!
    \brief      configure fast position estimator deviation threshold (API_ID(0x0027U))
    \param[in]  threshold: estimator deviation threshold, 0~0xFFFF
    \param[out] none
    \retval     none
*/
void edim_hdsl_fast_position_estimator_deviation_threshold_config(uint16_t threshold)
{
    EDIM_HDSL_MAXDEV_L = (uint8_t)(threshold);
    EDIM_HDSL_MAXDEV_H = (uint8_t)(threshold >> 8);
}

/*!
    \brief      read fast position estimator deviation (API_ID(0x0028U))
    \param[in]  none
    \param[out] none
    \retval     max estimator deviation: 0~0xFFFF
*/
uint16_t edim_hdsl_fast_position_estimator_deviation_read(void)
{
    uint16_t reval = 0U;
    reval = EDIM_HDSL_MAXDEV_H;
    reval = (uint16_t)(EDIM_HDSL_MAXDEV_L | (uint16_t)(reval << 8));
    return reval;
}

/*!
    \brief      read dummy (API_ID(0x0029U))
    \param[in]  none
    \param[out] none
    \retval     dummy: 0~0xFF
*/
uint8_t edim_hdsl_dummy_read(void)
{
    return EDIM_HDSL_DUMMY;
}

/*!
    \brief      access slave mirror system errors, events, and warnings from the DSL encoder (API_ID(0x002AU))
    \param[in]  reg_idx: MIR_ST(reg_idx) need to be accessed, 0-7
    \param[out] none
    \retval     MIR_ST: 0~0xFF, this value is invalid
*/
uint8_t edim_hdsl_mirror_status_flag_access(uint8_t reg_idx)
{
    return EDIM_HDSL_MIR_ST(reg_idx);
}

/*!
    \brief      clear slave mirror system errors, events, and warnings from the DSL encoder (API_ID(0x002BU))
    \param[in]  reg_idx: MIR_ST(reg_idx) need to be cleared, 0-7
    \param[out] none
    \retval     none
*/
void edim_hdsl_mirror_status_flag_clear(uint8_t reg_idx)
{
    EDIM_HDSL_MIR_ST(reg_idx) &= (uint8_t)(~EDIM_HDSL_MIR_ST_MIRST);
}

/*!
    \brief      get edges in safe channel 1 cable signal (API_ID(0x002CU))
    \param[in]  none
    \param[out] none
    \retval     identification of edges in the cable signal: 0~0x0F
*/
uint8_t edim_hdsl_safe_channel1_cable_signal_edge_get(void)
{
    return EDIM_HDSL_SAFE_EDGES;
}

/*!
    \brief      get safe channel 1 cable delay (API_ID(0x002DU))
    \param[in]  none
    \param[out] none
    \retval     4-bit value for cable delay: 0~0x09
*/
uint8_t edim_hdsl_safe_channel1_cable_delay_get(void)
{
    return (uint8_t)(EDIM_HDSL_SAFE_DELAY & EDIM_HDSL_DELAY_CBLDLY);
}

/*!
    \brief      get received safe channel 1 signal strength (API_ID(0x002EU))
    \param[in]  none
    \param[out] none
    \retval     4-bit value for received signal strength: 0~0x0C
*/
uint8_t edim_hdsl_received_safe_channel1_signal_strength_get(void)
{
    return (uint8_t)((EDIM_HDSL_SAFE_DELAY & EDIM_HDSL_DELAY_RSSI) >> 4);
}


/*!
    \brief      safe channel 1 version information (API_ID(0x002FU))
    \param[in]  none
    \param[out] none
    \retval     version number: 0~0xFF
*/
uint8_t edim_hdsl_safe_channel1_version_get(void)
{
    return EDIM_HDSL_SAFE_VERSION;
}

/*!
    \brief      get safe channel 1 encoder ID information (API_ID(0x0030U))
    \param[in]  none
    \param[out] none
    \retval     encoder ID: 0~0xFFFFFFFF
*/
uint32_t edim_hdsl_safe_channel1_encoder_id_get(void)
{
    uint32_t enc_id;
    /* get Encoder ID */
    enc_id = EDIM_HDSL_SAFE_ENC_ID2 & 0x7FU;
    enc_id = EDIM_HDSL_SAFE_ENC_ID1 | (uint32_t)(enc_id << 8U);
    enc_id = EDIM_HDSL_SAFE_ENC_ID0 | (uint32_t)(enc_id << 8U);
    return enc_id;
}

/*!
    \brief      read safe channel 1 position crc (API_ID(0x0031U))
    \param[in]  none
    \param[out] none
    \retval     crc of the safe channel 1: 0~0xFFFF
*/
uint16_t edim_hdsl_safe_channel1_position_crc_read(void)
{
    uint16_t crc;
    /* get Encoder ID */
    crc = (uint16_t)EDIM_HDSL_VPOSCRC_H;
    crc = (uint16_t)EDIM_HDSL_VPOSCRC_L | (uint16_t)(crc << 8);
    return crc;
}

/*!
    \brief      reset message for the safety-related application (API_ID(0x0032U))
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void edim_hdsl_safe_message_reset(ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        EDIM_HDSL_SAFE_CTRL |= (uint8_t)EDIM_HDSL_SAFE_CTRL_MRST;
    } else {
        EDIM_HDSL_SAFE_CTRL &= (uint8_t)(~EDIM_HDSL_SAFE_CTRL_MRST);
    }
}

/*!
    \brief      reset protocol status for the safety-related application (API_ID(0x0033U))
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void edim_hdsl_safe_protocol_reset(ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        EDIM_HDSL_SAFE_CTRL |= (uint8_t)EDIM_HDSL_SAFE_CTRL_PRST;
    } else {
        EDIM_HDSL_SAFE_CTRL &= (uint8_t)(~EDIM_HDSL_SAFE_CTRL_PRST);
    }
}

/*!
    \brief      get safe status summary flag (API_ID(0x0034U))
    \param[in]  none
    \param[out] none
    \retval     Status summary flag: 0~0xFF
*/
uint8_t edim_hdsl_safe_status_sum_flag_get(void)
{
    return EDIM_HDSL_SAFE_SUM;
}

/*!
    \brief      read parameter channel short message (API_ID(0x0035U))
    \param[in]  none
    \param[out] none
    \retval     short message: 0~0xFF
*/
uint8_t edim_hdsl_short_message_read(void)
{
    return EDIM_HDSL_S_PC_DATA;
}

/*!
    \brief      access slave system errors, events, and warnings from the DSL encoder (API_ID(0x0036U))
    \param[in]  reg_idx: ENC_ST(reg_idx) need to be accessed, 0-7
    \param[out] none
    \retval     ENC_ST: 0~0xFF, this value is invalid
*/
uint8_t edim_hdsl_encoder_status_flag_access(uint8_t reg_idx)
{
    return EDIM_HDSL_ENC_ST(reg_idx);
}

/*!
    \brief      clear slave system errors, events, and warnings from the DSL encoder (API_ID(0x0037U))
    \param[in]  reg_idx: ENC_ST(reg_idx) need to be cleared, 0-7
    \param[out] none
    \retval     none
*/
void edim_hdsl_encoder_status_flag_clear(uint8_t reg_idx)
{
    EDIM_HDSL_ENC_ST(reg_idx) &= (uint8_t)(~EDIM_HDSL_ENC_ST_ENCST);
}

/*!
    \brief      read slave RSSI (API_ID(0x0038U))
    \param[in]  none
    \param[out] none
    \retval     slave RSSI: 0~0x07
*/
uint8_t edim_hdsl_slave_rssi_read(void)
{
    return (EDIM_HDSL_SRSSI & 0x07U);
}

/*!
    \brief      configure slave mail (API_ID(0x0039U))
    \param[in]  mail: slave mail, 0~0xFF
    \param[out] none
    \retval     none
*/
void edim_hdsl_slave_mail_config(uint8_t mail)
{
    EDIM_HDSL_MAIL = mail;
}

/*!
    \brief      configure slave ping (API_ID(0x003AU))
    \param[in]  ping: slave ping, 0~0xFF
    \param[out] none
    \retval     none
*/
void edim_hdsl_slave_ping_write(uint8_t ping)
{
    EDIM_HDSL_PING = ping;
}

/*!
    \brief      read slave ping (API_ID(0x003BU))
    \param[in]  none
    \param[out] none
    \retval     ping: 0~0xFF
*/
uint8_t edim_hdsl_slave_ping_read(void)
{
    uint8_t ping = 0U;
    ping = EDIM_HDSL_PING;
    return ping;
}

/*!
    \brief      get safe channel 2 version information (API_ID(0x003CU))
    \param[in]  none
    \param[out] none
    \retval     version number: 0~0xFF
*/
uint8_t edim_hdsl_safe_channel2_version_get(void)
{
    return EDIM_HDSL_VERSION2;
}

/*!
    \brief      safe channel 2 version information (API_ID(0x003DU))
    \param[in]  none
    \param[out] none
    \retval     designation of the safe channel 2 channel: 0~0xFF
*/
uint8_t edim_hdsl_safe_channel2_encoder_id_get(void)
{
    return EDIM_HDSL_ENC2_ID;
}

/*!
    \brief      read EDIM_HDSL safe channel 2 fixed bit pattern (API_ID(0x003EU))
    \param[in]  none
    \param[out] none
    \retval     fixed bit pattern: 0~0x1F
*/
uint8_t edim_hdsl_safe_channel2_fix_bit_read(void)
{
    return (uint8_t)(EDIM_HDSL_STATUS2 & EDIM_HDSL_STATUS2_FIX2);
}

/*!
    \brief      read safe channel 2 position CRC (API_ID(0x003FU))
    \param[in]  none
    \param[out] none
    \retval     CRC of the safe channel 2: 0~0xFFFF
*/
uint16_t edim_hdsl_safe_channel2_position_crc_read(void)
{
    uint16_t crc;
    /* get Encoder ID */
    crc = (uint16_t)EDIM_HDSL_VPOSCRC2_H;
    crc = (uint16_t)EDIM_HDSL_VPOSCRC2_L | (uint16_t)(crc << 8);
    return crc;
}

/*!
    \brief      read dummy2 (API_ID(0x0040U))
    \param[in]  none
    \param[out] none
    \retval     dummy2: 0~0xFF
*/
uint8_t edim_hdsl_dummy2_read(void)
{
    return EDIM_HDSL_DUMMY2;
}

/*!
    \brief      configure hdsl unit0 endian mode (API_ID(0x0041U))
    \param[in]  mode: endian mode
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_ENDIAN_MODE_BIG: big endian
      \arg        EDIM_HDSL_ENDIAN_MODE_LITTLE: little endian
    \param[out] none
    \retval     none
*/
void edim_hdsl_endian_mode_config(uint8_t mode)
{
    if(EDIM_HDSL_ENDIAN_MODE_BIG == mode) {
        EDIM_HDSL_CTL &= (~(EDIM_HDSL_CTL_ENDIAN));
    } else if(EDIM_HDSL_ENDIAN_MODE_LITTLE == mode) {
        EDIM_HDSL_CTL |= EDIM_HDSL_CTL_ENDIAN;
    } else {

    }
}

/*!
    \brief      select hdsl unit0 interface (API_ID(0x0042U))
    \param[in]  channel: hdsl channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_DRIVE: hdsl unit0 drive
      \arg        EDIM_HDSL_SAFE_CHANNEL1: hdsl unit0 safe channel 1
      \arg        EDIM_HDSL_SAFE_CHANNEL2: hdsl unit0 safe channel 2
    \param[in]  mode: interface mode
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_BUS_INTERFACE: internal bus interface
      \arg        EDIM_HDSL_SPI_INTERFACE: spi interface
    \param[out] none
    \retval     none
*/
void edim_hdsl_interface_select(uint8_t channel, uint8_t mode)
{
    if(EDIM_HDSL_DRIVE == channel) {
        if(EDIM_HDSL_BUS_INTERFACE == mode) {
            EDIM_HDSL_CTL &= (~EDIM_HDSL_CTL_DSEL);
        } else if(EDIM_HDSL_SPI_INTERFACE == mode) {
            EDIM_HDSL_CTL |= EDIM_HDSL_CTL_DSEL;
        } else {

        }
    } else if(EDIM_HDSL_SAFE_CHANNEL1 == channel) {
        if(EDIM_HDSL_BUS_INTERFACE == mode) {
            EDIM_HDSL_CTL &= (~EDIM_HDSL_CTL_SSEL1);
        } else if(EDIM_HDSL_SPI_INTERFACE == mode) {
            EDIM_HDSL_CTL |= EDIM_HDSL_CTL_SSEL1;
        } else {

        }
    } else if(EDIM_HDSL_SAFE_CHANNEL2 == channel) {
        if(EDIM_HDSL_BUS_INTERFACE == mode) {
            EDIM_HDSL_CTL |= EDIM_HDSL_CTL_SSEL2;
        } else if(EDIM_HDSL_SPI_INTERFACE == mode) {
            EDIM_HDSL_CTL &= (~EDIM_HDSL_CTL_SSEL2);
        } else {

        }
    } else {

    }
}

/*!
    \brief      configure hdsl position sampling resolution lock (API_ID(0x0043U))
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_hdsl_position_sampling_resolution_lock_get(void)
{
    FlagStatus reval = RESET;
    if(RESET != (EDIM_HDSL_SYNLK & EDIM_HDSL_SYNLK_SYNLK)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      configure hdsl POSTX interrupt source (API_ID(0x0044U))
    \param[in]  source: POSTX interrupt source
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_POSTX_SRC_01: when POSTX=2'b01
      \arg        EDIM_HDSL_POSTX_SRC_10: when POSTX=2'b10
      \arg        EDIM_HDSL_POSTX_SRC_11: when POSTX=2'b11
      \arg        EDIM_HDSL_POSTX_SRC_01_10_11: when POSTX = 2'b01, 2'b10, 2'b11
      \arg        EDIM_HDSL_POSTX_SRC_00_TO_01: when POSTX transfer from 2'b00 to 2'b01
      \arg        EDIM_HDSL_POSTX_SRC_00_TO_10: when POSTX transfer from 2'b00 to 2'b10
      \arg        EDIM_HDSL_POSTX_SRC_00_TO_01_10: when POSTX transfer from 2'b00 to 2'b01 or 2'b10
      \arg        EDIM_HDSL_POSTX_SRC_01_TO_10: when POSTX transfer from 2'b01 to 2'b10
      \arg        EDIM_HDSL_POSTX_SRC_10_TO_11: when POSTX transfer from 2'b10 to 2'b11
      \arg        EDIM_HDSL_POSTX_SRC_CHANGES: when POSTX changes
    \param[out] none
    \retval     none
*/
void edim_hdsl_postx_interrupt_source_select(uint32_t source)
{
    uint32_t reg_tmp;
    reg_tmp = EDIM_HDSL_INTEN;
    reg_tmp &= (~EDIM_HDSL_INTEN_INTSRC);
    reg_tmp |= (source & EDIM_HDSL_INTEN_INTSRC);
    EDIM_HDSL_INTEN = reg_tmp;
}

/*!
    \brief      enable POSTX interrupt (API_ID(0x0045U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_hdsl_postx_interrupt_enable(void)
{
    EDIM_HDSL_INTEN |= EDIM_HDSL_INTEN_POSTXIE;
}

/*!
    \brief      disable POSTX interrupt (API_ID(0x0046U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_hdsl_postx_interrupt_disable(void)
{
    EDIM_HDSL_INTEN &= (~EDIM_HDSL_INTEN_POSTXIE);
}

/*!
    \brief      enable safe channel 1 global interrupt (API_ID(0x0047U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_hdsl_safe_channel1_global_interrupt_enable(void)
{
    EDIM_HDSL_INTEN |= EDIM_HDSL_INTEN_INTSIE;
}

/*!
    \brief      disable safe channel 1 global interrupt (API_ID(0x0048U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_hdsl_safe_channel1_global_interrupt_disable(void)
{
    EDIM_HDSL_INTEN &= (~EDIM_HDSL_INTEN_INTSIE);
}

/*!
    \brief      get EDIM_HDSL online d flag (API_ID(0x0049U))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_ONLINE_D_FLAG_FREL: channel status for long message
      \arg        EDIM_HDSL_ONLINE_D_FLAG_QMLW: quality monitoring at low level
      \arg        EDIM_HDSL_ONLINE_D_FLAG_ANS: incorrect answer detected
      \arg        EDIM_HDSL_ONLINE_D_FLAG_MIN: acknowledgment of message Initialization
      \arg        EDIM_HDSL_ONLINE_D_FLAG_PRST: protocol reset
      \arg        EDIM_HDSL_ONLINE_D_FLAG_DTE: deviation threshold error
      \arg        EDIM_HDSL_ONLINE_D_FLAG_POS: estimator turned on
      \arg        EDIM_HDSL_ONLINE_D_FLAG_SUM: summary byte
      \arg        EDIM_HDSL_ONLINE_D_FLAG_INT: status of the interrupt signal
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_hdsl_online_d_flag_get(uint32_t flag)
{
    FlagStatus reval = RESET;
    if(RESET != (EDIM_HDSL_ONLINE_STATUS_D & flag)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      get online d position transmission status (API_ID(0x004AU))
    \param[in]  none
    \param[out] none
    \retval     position transmission status: 0~0x03
*/
uint8_t edim_hdsl_online_d_position_transmission_status_get(void)
{
    return (uint8_t)((EDIM_HDSL_ONLINE_STATUS_D & EDIM_HDSL_ONLINE_STATUS_D_POSTX) >> 6U);
}

/*!
    \brief      get EDIM_HDSL online 1 flag (API_ID(0x004BU))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_ONLINE_1_FLAG_FRES: channel Status for the short message
      \arg        EDIM_HDSL_ONLINE_1_FLAG_QMLW: quality monitoring at low level
      \arg        EDIM_HDSL_ONLINE_1_FLAG_MIN: acknowledgment of message Initialization
      \arg        EDIM_HDSL_ONLINE_1_FLAG_PRST: protocol reset
      \arg        EDIM_HDSL_ONLINE_1_FLAG_VPOS: safe Position Invalid
      \arg        EDIM_HDSL_ONLINE_1_FLAG_SCE: CRC Error on the Safe Channel
      \arg        EDIM_HDSL_ONLINE_1_FLAG_SSUM: safe summary bit
      \arg        EDIM_HDSL_ONLINE_1_FLAG_SINT: status of the interrupt signal
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_hdsl_online_1_flag_get(uint32_t flag)
{
    FlagStatus reval = RESET;
    if(RESET != (EDIM_HDSL_ONLINE_STATUS_1 & flag)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      get online 1 position transmission status (API_ID(0x004CU))
    \param[in]  none
    \param[out] none
    \retval     position transmission status: 0~0x03
*/
uint8_t edim_hdsl_online_1_position_transmission_status_get(void)
{
    return (uint8_t)((EDIM_HDSL_ONLINE_STATUS_1 & EDIM_HDSL_ONLINE_STATUS_1_POSTX) >> 6U);
}

/*!
    \brief      get EDIM_HDSL online 2 flag (API_ID(0x004DU))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_ONLINE_2_FLAG_QMLW: quality monitoring at low level
      \arg        EDIM_HDSL_ONLINE_2_FLAG_PRST: protocol reset
      \arg        EDIM_HDSL_ONLINE_2_FLAG_VPOS2: safe Position 2 Invalid
      \arg        EDIM_HDSL_ONLINE_2_FLAG_SCE2: transmission Error Channel 2
      \arg        EDIM_HDSL_ONLINE_2_FLAG_SSUM2: summary byte Channel 2
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_hdsl_online_2_flag_get(uint32_t flag)
{
    FlagStatus reval = RESET;
    if(RESET != (EDIM_HDSL_ONLINE_STATUS_2 & flag)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      get online 2 position transmission status (API_ID(0x004EU))
    \param[in]  none
    \param[out] none
    \retval     position transmission status: 0~0x03
*/
uint8_t edim_hdsl_online_2_position_transmission_status_get(void)
{
    return (uint8_t)((EDIM_HDSL_ONLINE_STATUS_2 & EDIM_HDSL_ONLINE_STATUS_2_POSTX) >> 6U);
}



/*!
    \brief      get EDIM_HDSL flag (API_ID(0x004FU))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_FLAG_PRST: protocol reset warning
      \arg        EDIM_HDSL_FLAG_DTE: estimator deviation threshold error
      \arg        EDIM_HDSL_FLAG_POS: estimator turned on
      \arg        EDIM_HDSL_FLAG_SUM: remote event monitoring
      \arg        EDIM_HDSL_FLAG_INT: interrupt status
      \arg        EDIM_HDSL_FLAG_FREL: channel free for "long message"
      \arg        EDIM_HDSL_FLAG_QMLW: quality monitoring low-value warning
      \arg        EDIM_HDSL_FLAG_ANS: error answer to "long message"
      \arg        EDIM_HDSL_FLAG_MIN: message initialization
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_hdsl_flag_get(uint32_t flag)
{
    uint32_t status_reg;
    uint32_t reg1;
    uint32_t reg2;
    FlagStatus reval;
    reg1 = (uint32_t)EDIM_HDSL_EVENT_L;
    reg2 = ((uint32_t)EDIM_HDSL_EVENT_H) << 8U;
    status_reg = (reg1 | reg2);

    if(RESET != (status_reg & flag)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;

}

/*!
    \brief      clear EDIM_HDSL flag (API_ID(0x0050U))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_FLAG_PRST: protocol reset warning
      \arg        EDIM_HDSL_FLAG_DTE: estimator deviation threshold error
      \arg        EDIM_HDSL_FLAG_POS: estimator turned on
      \arg        EDIM_HDSL_FLAG_SUM: remote event monitoring
      \arg        EDIM_HDSL_FLAG_FREL: channel free for "long message"
      \arg        EDIM_HDSL_FLAG_QMLW: quality monitoring low-value warning
      \arg        EDIM_HDSL_FLAG_MIN: message initialization
    \param[out] none
    \retval     none
*/
void edim_hdsl_flag_clear(uint32_t flag)
{
    if((flag & 0xFFU) != 0U) {
        EDIM_HDSL_EVENT_L &= (uint8_t)(~(flag & EDIM_HDSL_FLAG_MASK));
    } else {
        EDIM_HDSL_EVENT_H &= (uint8_t)(~((flag & EDIM_HDSL_FLAG_MASK) >> 8));
    }
}

/*!
    \brief      enable EDIM_HDSL interrupt (API_ID(0x0051U))
    \param[in]  interrupt: specify which interrupt to enable
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_INT_PRST: protocol reset warning
      \arg        EDIM_HDSL_INT_DTE: estimator deviation threshold error
      \arg        EDIM_HDSL_INT_POS: estimator turned on
      \arg        EDIM_HDSL_INT_SUM: remote event monitoring
      \arg        EDIM_HDSL_INT_FREL: channel free for "long message"
      \arg        EDIM_HDSL_INT_QMLW: quality monitoring low-value warning
      \arg        EDIM_HDSL_INT_ANS: error answer to "long message"
      \arg        EDIM_HDSL_INT_MIN: message initialization
    \param[out] none
    \retval     none
*/
void edim_hdsl_interrupt_enable(uint32_t interrupt)
{
    if((interrupt & 0xFFU) != 0U) {
        EDIM_HDSL_MASK_L |= (uint8_t)(interrupt & EDIM_HDSL_INTEN_MASK);
    } else {
        EDIM_HDSL_MASK_H |= (uint8_t)((interrupt & EDIM_HDSL_INTEN_MASK) >> 8);
    }
}

/*!
    \brief      disable EDIM_HDSL interrupt (API_ID(0x0052U))
    \param[in]  interrupt: specify which interrupt to enable
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_INT_PRST: protocol reset warning
      \arg        EDIM_HDSL_INT_DTE: estimator deviation threshold error
      \arg        EDIM_HDSL_INT_POS: estimator turned on
      \arg        EDIM_HDSL_INT_SUM: remote event monitoring
      \arg        EDIM_HDSL_INT_FREL: channel free for "long message"
      \arg        EDIM_HDSL_INT_QMLW: quality monitoring low-value warning
      \arg        EDIM_HDSL_INT_ANS: error answer to "long message"
      \arg        EDIM_HDSL_INT_MIN: message initialization
    \param[out] none
    \retval     none
*/
void edim_hdsl_interrupt_disable(uint32_t interrupt)
{
    if((interrupt & 0xFFU) != 0U) {
        EDIM_HDSL_MASK_L &= (uint8_t)(~(interrupt & EDIM_HDSL_INTEN_MASK));
    } else {
        EDIM_HDSL_MASK_H &= (uint8_t)(~((interrupt & EDIM_HDSL_INTEN_MASK) >> 8));
    }
}

/*!
    \brief      enable mirror sum bit set the sum event monitoring in the EVENT_H register and the interrupt signal (API_ID(0x0053U))
    \param[in]  flag: mirror sum event
                one and more parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_MASK_SUM_0: mask for status summary bit 0
      \arg        EDIM_HDSL_MASK_SUM_1: mask for status summary bit 1
      \arg        EDIM_HDSL_MASK_SUM_2: mask for status summary bit 2
      \arg        EDIM_HDSL_MASK_SUM_3: mask for status summary bit 3
      \arg        EDIM_HDSL_MASK_SUM_4: mask for status summary bit 4
      \arg        EDIM_HDSL_MASK_SUM_5: mask for status summary bit 5
      \arg        EDIM_HDSL_MASK_SUM_6: mask for status summary bit 6
      \arg        EDIM_HDSL_MASK_SUM_7: mask for status summary bit 7
    \param[out] none
    \retval     none
*/
void edim_hdsl_mir_sum_event_enable(uint32_t flag)
{
    EDIM_HDSL_MASK_SUM |= (uint8_t)flag;
}

/*!
    \brief      disable mirror sum bit set the sum event monitoring in the EVENT_H register and the interrupt signal (API_ID(0x0054U))
    \param[in]  flag: mirror sum event
                one and more parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_MASK_SUM_0: mask for status summary bit 0
      \arg        EDIM_HDSL_MASK_SUM_1: mask for status summary bit 1
      \arg        EDIM_HDSL_MASK_SUM_2: mask for status summary bit 2
      \arg        EDIM_HDSL_MASK_SUM_3: mask for status summary bit 3
      \arg        EDIM_HDSL_MASK_SUM_4: mask for status summary bit 4
      \arg        EDIM_HDSL_MASK_SUM_5: mask for status summary bit 5
      \arg        EDIM_HDSL_MASK_SUM_6: mask for status summary bit 6
      \arg        EDIM_HDSL_MASK_SUM_7: mask for status summary bit 7
    \param[out] none
    \retval     none
*/
void edim_hdsl_mir_sum_event_disable(uint32_t flag)
{
    EDIM_HDSL_MASK_SUM &= (uint8_t)(~flag);
}

/*!
    \brief      get EDIM_HDSL interrupt event flag (API_ID(0x0055U))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_INT_FLAG_PRST: protocol reset warning
      \arg        EDIM_HDSL_INT_FLAG_DTE: estimator deviation threshold error
      \arg        EDIM_HDSL_INT_FLAG_POS: estimator turned on
      \arg        EDIM_HDSL_INT_FLAG_SUM: remote event monitoring
      \arg        EDIM_HDSL_INT_FLAG_FREL: channel free for "long message"
      \arg        EDIM_HDSL_INT_FLAG_QMLW: quality monitoring low-value warning
      \arg        EDIM_HDSL_INT_FLAG_ANS: error answer to "long message"
      \arg        EDIM_HDSL_INT_FLAG_MIN: message initialization
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_hdsl_interrupt_flag_get(uint32_t flag)
{
    uint32_t val1 = 0U;
    uint32_t reg_tmp1 = 0U;
    FlagStatus reval;
    reg_tmp1 = (uint32_t)EDIM_HDSL_EVENT_L;
    reg_tmp1 |= (((uint32_t)EDIM_HDSL_EVENT_H) << 8U);
    val1 = reg_tmp1 & flag;
    if(RESET != val1) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      clear EDIM_HDSL interrupt event flag (API_ID(0x0056U))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_INT_FLAG_PRST: protocol reset warning
      \arg        EDIM_HDSL_INT_FLAG_DTE: estimator deviation threshold error
      \arg        EDIM_HDSL_INT_FLAG_POS: estimator turned on
      \arg        EDIM_HDSL_INT_FLAG_SUM: remote event monitoring
      \arg        EDIM_HDSL_INT_FLAG_FREL: channel free for "long message"
      \arg        EDIM_HDSL_INT_FLAG_QMLW: quality monitoring low-value warning
      \arg        EDIM_HDSL_INT_FLAG_ANS: error answer to "long message"
      \arg        EDIM_HDSL_INT_FLAG_MIN: message initialization
    \param[out] none
    \retval     none
*/
void edim_hdsl_interrupt_flag_clear(uint32_t flag)
{
    if((flag & 0xFFU) != 0U) {
        EDIM_HDSL_EVENT_L &= (uint8_t)(~(flag & EDIM_HDSL_INT_FLAG_MASK));
    } else {
        EDIM_HDSL_EVENT_H &= (uint8_t)(~((flag & EDIM_HDSL_INT_FLAG_MASK) >> 8));
    }
}

/*!
    \brief      get EDIM_HDSL safe channel 1 event flag (API_ID(0x0057U))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_SAFE_FLAG_FRES: channel free for "short message"
      \arg        EDIM_HDSL_SAFE_FLAG_MIN: message initialization
      \arg        EDIM_HDSL_SAFE_FLAG_PRST: protocol reset warning
      \arg        EDIM_HDSL_SAFE_FLAG_QMLW: quality monitoring low-value warning
      \arg        EDIM_HDSL_SAFE_FLAG_VPOS: safe position error
      \arg        EDIM_HDSL_SAFE_FLAG_SCE: error on the Safe Channel
      \arg        EDIM_HDSL_SAFE_FLAG_SSUM: remote event monitoring
      \arg        EDIM_HDSL_SAFE_FLAG_SINT: safe interrupt status
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_hdsl_safe_channel1_flag_get(uint8_t flag)
{
    uint8_t status_reg;
    FlagStatus reval;
    status_reg = EDIM_HDSL_EVENT_S;

    if(RESET != (status_reg & flag)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;

}

/*!
    \brief      clear EDIM_HDSL safe channel 1 event flag (API_ID(0x0058U))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_SAFE_FLAG_FRES: channel free for "short message"
      \arg        EDIM_HDSL_SAFE_FLAG_MIN: message initialization
      \arg        EDIM_HDSL_SAFE_FLAG_PRST: protocol reset warning
      \arg        EDIM_HDSL_SAFE_FLAG_QMLW: quality monitoring low-value warning
      \arg        EDIM_HDSL_SAFE_FLAG_VPOS: safe position error
      \arg        EDIM_HDSL_SAFE_FLAG_SCE: error on the Safe Channel
      \arg        EDIM_HDSL_SAFE_FLAG_SSUM: remote event monitoring
    \param[out] none
    \retval     none
*/
void edim_hdsl_safe_channel1_flag_clear(uint8_t flag)
{
    EDIM_HDSL_EVENT_S &= ((uint8_t)(~((uint32_t)flag & (uint32_t)EDIM_HDSL_EVENT_S_MASK)));
}

/*!
    \brief      enable EDIM_HDSL safe channel 1 interrupt (API_ID(0x0059U))
    \param[in]  interrupt: specify which interrupt to enable
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_SAFE_INT_FRES: interrupt enable for channel free for "short message"
      \arg        EDIM_HDSL_SAFE_INT_MIN:  interrupt enable for message initialization
      \arg        EDIM_HDSL_SAFE_INT_PRST: interrupt enable for protocol reset warning
      \arg        EDIM_HDSL_SAFE_INT_QMLW: interrupt enable for quality monitoring low-value warning
      \arg        EDIM_HDSL_SAFE_INT_VPOS: interrupt enable for safe position error
      \arg        EDIM_HDSL_SAFE_INT_SCE:  interrupt enable for error on the Safe Channel
      \arg        EDIM_HDSL_SAFE_INT_SSUM: interrupt enable for remote event monitoring
    \param[out] none
    \retval     none
*/
void edim_hdsl_safe_channel1_interrupt_enable(uint8_t interrupt)
{
    EDIM_HDSL_MASK_S |= interrupt;
}

/*!
    \brief      disable EDIM_HDSL safe channel 1 interrupt (API_ID(0x005AU))
    \param[in]  interrupt: specify which interrupt to enable
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_SAFE_INT_FRES: interrupt enable for channel free for "short message"
      \arg        EDIM_HDSL_SAFE_INT_MIN:  interrupt enable for message initialization
      \arg        EDIM_HDSL_SAFE_INT_PRST: interrupt enable for protocol reset warning
      \arg        EDIM_HDSL_SAFE_INT_QMLW: interrupt enable for quality monitoring low-value warning
      \arg        EDIM_HDSL_SAFE_INT_VPOS: interrupt enable for safe position error
      \arg        EDIM_HDSL_SAFE_INT_SCE:  interrupt enable for error on the Safe Channel
      \arg        EDIM_HDSL_SAFE_INT_SSUM: interrupt enable for remote event monitoring
    \param[out] none
    \retval     none
*/
void edim_hdsl_safe_channel1_interrupt_disable(uint8_t interrupt)
{
    EDIM_HDSL_MASK_S &= ((uint8_t)(~(uint32_t)interrupt));
}

/*!
    \brief      get EDIM_HDSL safe channel 1 interrupt event flag (API_ID(0x005BU))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_SAFE_INT_FLAG_FRES: channel free for "short message"
      \arg        EDIM_HDSL_SAFE_INT_FLAG_MIN: message initialization
      \arg        EDIM_HDSL_SAFE_INT_FLAG_PRST: protocol reset warning
      \arg        EDIM_HDSL_SAFE_INT_FLAG_QMLW: quality monitoring low-value warning
      \arg        EDIM_HDSL_SAFE_INT_FLAG_VPOS: safe position error
      \arg        EDIM_HDSL_SAFE_INT_FLAG_SCE: error on the Safe Channel
      \arg        EDIM_HDSL_SAFE_INT_FLAG_SSUM: remote event monitoring
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_hdsl_safe_channel1_interrupt_flag_get(uint8_t flag)
{
    FlagStatus reval;
    if(RESET != (EDIM_HDSL_EVENT_S & flag)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      clear EDIM_HDSL safe channel 1 event flag (API_ID(0x005CU))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_SAFE_INT_FLAG_FRES: channel free for "short message"
      \arg        EDIM_HDSL_SAFE_INT_FLAG_MIN: message initialization
      \arg        EDIM_HDSL_SAFE_INT_FLAG_PRST: protocol reset warning
      \arg        EDIM_HDSL_SAFE_INT_FLAG_QMLW: quality monitoring low-value warning
      \arg        EDIM_HDSL_SAFE_INT_FLAG_VPOS: safe position error
      \arg        EDIM_HDSL_SAFE_INT_FLAG_SCE: error on the Safe Channel
      \arg        EDIM_HDSL_SAFE_INT_FLAG_SSUM: remote event monitoring
    \param[out] none
    \retval     none
*/
void edim_hdsl_safe_channel1_interrupt_flag_clear(uint8_t flag)
{
    EDIM_HDSL_EVENT_S &= ((uint8_t)(~((uint32_t)flag & (uint32_t)EDIM_HDSL_EVENT_S_MASK)));
}

/*!
    \brief      get EDIM_HDSL safe channel 2 flag (API_ID(0x005DU))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_HDSL_SAFE2_FLAG_ERR: safe Channel 2 position Error
      \arg        EDIM_HDSL_SAFE2_FLAG_TEST: safe Channel 2 test
      \arg        EDIM_HDSL_SAFE2_FLAG_TOG: safe Channel 2 toggle
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_hdsl_safe_channel2_flag_get(uint8_t flag)
{
    FlagStatus reval = RESET;
    if(RESET != (EDIM_HDSL_STATUS2 & flag)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}
