/*!
    \file    gd32h77x_78x_edim_afmt.c
    \brief   EDIM AFMT driver

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

#include "gd32h77x_78x_edim_afmt.h"

/*!
    \brief      deinit EDIM_AFMT (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_afmt_deinit(void)
{
    rcu_periph_reset_enable(RCU_AFMTRST);
    rcu_periph_reset_disable(RCU_AFMTRST);
}

/*!
    \brief      initialize EDIM_AFMT init parameter struct with a default value (API_ID(0x0002U))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void edim_afmt_struct_para_init(edim_afmt_parameter_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(EDIM_AFMT_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        initpara->baud_rate = EDIM_AFMT_BAUD_2_5MBPS;
        initpara->t2 = EDIM_AFMT_T2_FACTOR(0);
    }
}

/*!
    \brief      initialize EDIM_AFMT (API_ID(0x0003U))
    \param[in]  init_struct: init parameter struct
                  baud_rate: baud rate for EDIM_AFMT,
                                EDIM_AFMT_BAUD_2_5MBPS, EDIM_AFMT_BAUD_4MBPS,
                                EDIM_AFMT_BAUD_6_67MBPS, EDIM_AFMT_BAUD_8MBPS,
                                EDIM_AFMT_BAUD_16MBPS
                  t2: T2 time factor, EDIM_AFMT_T2_FACTOR(n), n = 0~255

    \param[out] none
    \retval     none
*/
void edim_afmt_init(edim_afmt_parameter_struct *init_struct)
{
    uint32_t reg_tmp = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(EDIM_AFMT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg_tmp = EDIM_AFMT_CFG;
        reg_tmp &= (~(EDIM_AFMT_CFG_BAUD | EDIM_AFMT_CFG_T2FAC));
        reg_tmp |= ((init_struct->baud_rate & EDIM_AFMT_CFG_BAUD) | (init_struct->t2 & EDIM_AFMT_CFG_T2FAC));
        EDIM_AFMT_CFG = reg_tmp;
    }
}

/*!
    \brief      set EDIM_AFMT t2 time (API_ID(0x0004U))
    \param[in]  t2_fac: T2 time factor, t2 = 1us + t2_fac * 0.25us, t2_fac = 0~255
    \param[out] none
    \retval     none
*/
void edim_afmt_t2_config(uint32_t t2_fac)
{
    uint32_t reg_tmp;
    reg_tmp = EDIM_AFMT_CFG;
    reg_tmp &= (~EDIM_AFMT_CFG_T2FAC);
    reg_tmp |= EDIM_AFMT_T2_FACTOR(t2_fac);
    EDIM_AFMT_CFG = reg_tmp;
}

/*!
    \brief      configure EDIM_AFMT trigger mode (API_ID(0x0005U))
    \param[in]  mode: EDIM_AFMT trigger mode,
                only one parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_TRIGGER_SWT: transmission trigger is input from EDIM_AFMT_SWT
      \arg        EDIM_AFMT_TRIGGER_TRIGSEL: transmission trigger is input from TRIGSEL
    \param[out] none
    \retval     none
*/
void edim_afmt_trigger_mode_config(edim_afmt_trigger_enum mode)
{
    if(mode == EDIM_AFMT_TRIGGER_SWT) {
        EDIM_AFMT_TRGM &= (~EDIM_AFMT_TRGM_TRANSTSEL);
    } else {
        EDIM_AFMT_TRGM |= EDIM_AFMT_TRGM_TRANSTSEL;
    }
}

/*!
    \brief      configure A-format command to be sent (API_ID(0x0006U))
    \param[in]  mea: slave address id to be access,
                only one parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_ADDR(mea): mea = 0~7
    \param[in]  cc: slave command,
                only one parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_CMD_CC_INDABS40: Individual ABS full 40-bit data request
      \arg        EDIM_AFMT_CMD_CC_INDABSL24: Individual ABS lower 24-bit data request
      \arg        EDIM_AFMT_CMD_CC_INDABSU24: Individual ABS upper 24-bit data request
      \arg        EDIM_AFMT_CMD_CC_INDSTA: Individual Encoder status request
      \arg        EDIM_AFMT_CMD_CC_BRDABS40: Broadcast ABS full 40-bit data request
      \arg        EDIM_AFMT_CMD_CC_BRDABSL24: Broadcast ABS lower 24-bit data request
      \arg        EDIM_AFMT_CMD_CC_BRDABSU24: Broadcast ABS upper 24-bit data request
      \arg        EDIM_AFMT_CMD_CC_BRDSTA: Broadcast Encoder status request
      \arg        EDIM_AFMT_CMD_CC_INDSTACLR: Status flag clear request
      \arg        EDIM_AFMT_CMD_CC_MUTCLR: Multi-rotation data clear request
      \arg        EDIM_AFMT_CMD_CC_STAMUTCLR: Status and multi-rotation data clear requests
      \arg        EDIM_AFMT_CMD_CC_ADDSETI: Encoder address setting I
      \arg        EDIM_AFMT_CMD_CC_ABSRST: One-rotation data zero preset
      \arg        EDIM_AFMT_CMD_CC_MEMRD: Memory read request
      \arg        EDIM_AFMT_CMD_CC_MEMWR: Memory write request
      \arg        EDIM_AFMT_CMD_CC_TEMREQ: 10-bit temperature data request
      \arg        EDIM_AFMT_CMD_CC_IDRDI: ID code read I
      \arg        EDIM_AFMT_CMD_CC_IDRDII: ID code read II
      \arg        EDIM_AFMT_CMD_CC_IDWRI: ID code write I
      \arg        EDIM_AFMT_CMD_CC_IDWRII: ID code write II
      \arg        EDIM_AFMT_CMD_CC_ADDSETII: Encoder address setting II
      \arg        EDIM_AFMT_CMD_CC_INDABSL17: Individual ABS lower 17-bit data request
      \arg        EDIM_AFMT_CMD_CC_BRDABSL17: Broadcast ABS lower 17-bit data request
      \arg        EDIM_AFMT_CMD_CC_INDABSL24STA: Individual ABS lower 24-bit data and status requests
      \arg        EDIM_AFMT_CMD_CC_BRDABSL24STA: Broadcast ABS lower 24-bit data and status requests
      \arg        EDIM_AFMT_CMD_CC_INDABSL24TEM: Individual ABS lower 24-bit data and temperature requests
      \arg        EDIM_AFMT_CMD_CC_BRDABSL24TEM: Broadcast ABS lower 24-bit data and temperature requests
    \param[out] none
    \retval     none
*/
void edim_afmt_command(uint8_t mea, uint8_t cc)
{
    EDIM_AFMT_CMD = (EDIM_AFMT_ADDR(mea) | ((uint32_t)cc & EDIM_AFMT_CMD_CC));
}

/*!
    \brief      configure A-format command with eeprom memory access to be sent (API_ID(0x0007U))
    \param[in]  mea: slave id to be accessed,
                only one parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_ADDR(mea): mea = 0~7
    \param[in]  addr: slave eeprom address, 0~0xFF
    \param[in]  data: slave eeprom data to be sent, 0~0xFFFF
    \param[out] none
    \retval     none
*/
void edim_afmt_command_with_eeprom_write(uint8_t mea, uint8_t addr, uint16_t data)
{
    EDIM_AFMT_CMD = (EDIM_AFMT_ADDR(mea) | EDIM_AFMT_CMD_CC_MEMWR);
    EDIM_AFMT_EEPROM = EEPROM_EEPROMDATA(data) | EEPROM_EEPROMADDR(addr);
}

/*!
    \brief      configure A-format command with eeprom memory access to be received (API_ID(0x0008U))
    \param[in]  mea: slave id to be accessed,
                only one parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_ADDR(mea): mea = 0~7
    \param[in]  addr: slave eeprom address, 0~0xFF
    \param[out] none
    \retval     none
*/
void edim_afmt_command_with_eeprom_read(uint8_t mea, uint8_t addr)
{
    EDIM_AFMT_CMD = (EDIM_AFMT_ADDR(mea) | EDIM_AFMT_CMD_CC_MEMRD);
    EDIM_AFMT_EEPROM = EEPROM_EEPROMADDR(addr);
}

/*!
    \brief      configure A-format command with ID code to be sent (API_ID(0x0009U))
    \param[in]  mea: slave id to be accessed,
                only one parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_ADDR(mea): mea = 0~7
    \param[in]  cc: slave command,
                only one parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_CMD_CC_IDWRI: ID code write I
      \arg        EDIM_AFMT_CMD_CC_IDWRII: ID code write II
    \param[in]  id: 0~0xFFFFFF
    \param[out] none
    \retval     none
*/
void edim_afmt_command_with_id_write(uint8_t mea, uint8_t cc, uint32_t id)
{
    EDIM_AFMT_CMD = EDIM_AFMT_ADDR(mea) | ((uint32_t)cc & EDIM_AFMT_CMD_CC);
    EDIM_AFMT_IDCODE = (id & EDIM_AFMT_IDCODE_IDCODE);
}

/*!
    \brief      enable EDIM_AFMT software trigger (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_afmt_software_trigger(void)
{
    EDIM_AFMT_SWT |= EDIM_AFMT_SWT_SWTR;
}

/*!
    \brief      enable EDIM_AFMT DMA (API_ID(0x000BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_afmt_dma_enable(void)
{
    EDIM_AFMT_CFG |= EDIM_AFMT_CFG_DFEN;
}

/*!
    \brief      disable EDIM_AFMT DMA (API_ID(0x000CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_afmt_dma_disable(void)
{
    EDIM_AFMT_CFG &= (~EDIM_AFMT_CFG_DFEN);
}

/*!
    \brief      flush EDIM_AFMT DMA FIFO (API_ID(0x000DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_afmt_dma_flush(void)
{
    EDIM_AFMT_CFG |= EDIM_AFMT_CFG_FIFOFH;
}

/*!
    \brief      select EDIM_AFMT DMA FIFO data source (API_ID(0x000EU))
    \param[in]  reg_selected: DMA request and FIFO enable for EDIM_AFMT_ENCnRDATA0/1/2
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_CFG_DFEN0: EDIM_AFMT DMA request and FIFO enable for EDIM_AFMT_ENCnRDATA0 register
      \arg        EDIM_AFMT_CFG_DFEN1: EDIM_AFMT DMA request and FIFO enable for EDIM_AFMT_ENCnRDATA1 register
      \arg        EDIM_AFMT_CFG_DFEN2: EDIM_AFMT DMA request and FIFO enable for EDIM_AFMT_ENCnRDATA2 register
    \param[out] none
    \retval     none
*/
void edim_afmt_dma_select(uint32_t reg_selected)
{
    uint32_t reg_tmp;

    reg_tmp = EDIM_AFMT_CFG;
    reg_tmp &= (~(EDIM_AFMT_CFG_DFEN0 | EDIM_AFMT_CFG_DFEN1 | EDIM_AFMT_CFG_DFEN2));
    reg_tmp |= (reg_selected & (EDIM_AFMT_CFG_DFEN0 | EDIM_AFMT_CFG_DFEN1 | EDIM_AFMT_CFG_DFEN2));
    EDIM_AFMT_CFG = reg_tmp;
}

/*!
    \brief      read EDIM_AFMT RDATAx (API_ID(0x000FU))
    \param[in]  slv_n: AFMT_SLAVE number
                only one parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_SLAVE0: slave number0
      \arg        EDIM_AFMT_SLAVE1: slave number1
      \arg        EDIM_AFMT_SLAVE2: slave number2
      \arg        EDIM_AFMT_SLAVE3: slave number3
      \arg        EDIM_AFMT_SLAVE4: slave number4
      \arg        EDIM_AFMT_SLAVE5: slave number5
      \arg        EDIM_AFMT_SLAVE6: slave number6
      \arg        EDIM_AFMT_SLAVE7: slave number7
    \param[in]  data_n: AFMT_RDATA0/1/2
                only one parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_RDATA0: receive data0
      \arg        EDIM_AFMT_RDATA1: receive data1
      \arg        EDIM_AFMT_RDATA2: receive data2
    \param[out] none
    \retval     the received data value: 0~0xFFFFFFFF
*/
uint32_t edim_afmt_data_read(edim_afmt_slave_enum slv_n, edim_afmt_rdata_enum data_n)
{
    return EDIM_AFMT_ENCRDATA(data_n, slv_n);
}

/*!
    \brief      enable EDIM_AFMT interrupt (API_ID(0x0010U))
    \param[in]  interrupt: EDIM_AFMT interrupt
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_INT_EOC: end of communication interrupt
      \arg        EDIM_AFMT_INT_TOERR: timeout error interrupt
      \arg        EDIM_AFMT_INT_FIFOOVR: FIFO overrun error interrupt
      \arg        EDIM_AFMT_INT_FIFOUNR: FIFO underrun error interrupt
      \arg        EDIM_AFMT_INT_DMATO: DMA request timeout error interrupt
    \param[out] none
    \retval     none
*/
void edim_afmt_interrupt_enable(uint32_t interrupt)
{
    EDIM_AFMT_INTEN |= (interrupt & EDIM_AFMT_INTEN_MASK);
}

/*!
    \brief      disable EDIM_AFMT interrupt (API_ID(0x0011U))
    \param[in]  interrupt: EDIM_AFMT interrupt
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_INT_EOC: end of communication interrupt
      \arg        EDIM_AFMT_INT_TOERR: timeout error interrupt
      \arg        EDIM_AFMT_INT_FIFOOVR: FIFO overrun error interrupt
      \arg        EDIM_AFMT_INT_FIFOUNR: FIFO underrun error interrupt
      \arg        EDIM_AFMT_INT_DMATO: DMA request timeout error interrupt
    \param[out] none
    \retval     none
*/
void edim_afmt_interrupt_disable(uint32_t interrupt)
{
    EDIM_AFMT_INTEN &= (~(interrupt & EDIM_AFMT_INTEN_MASK));
}

/*!
    \brief      get EDIM_AFMT flag status (API_ID(0x0012U))
    \param[in]  flag: EDIM_AFMT flag
                only one parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_FLAG_CBUSY: communication busy flag
      \arg        EDIM_AFMT_FLAG_EOC: end of communication interrupt flag
      \arg        EDIM_AFMT_FLAG_TOERR: timeout error interrupt flag
      \arg        EDIM_AFMT_FLAG_FIFOOVR: FIFO overrun error interrupt flag
      \arg        EDIM_AFMT_FLAG_FIFOUNR: FIFO underrun error interrupt flag
      \arg        EDIM_AFMT_FLAG_DMATO: DMA request timeout error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_afmt_flag_get(uint32_t flag)
{
    FlagStatus return_val = RESET;
    if(RESET != (EDIM_AFMT_STAT & flag)) {
        return_val = SET;
    } else {
        return_val = RESET;
    }
    return return_val;
}

/*!
    \brief      clear EDIM_AFMT flag status (API_ID(0x0013U))
    \param[in]  flag: EDIM_AFMT flag
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_FLAG_TOERR: timeout error interrupt flag
      \arg        EDIM_AFMT_FLAG_FIFOOVR: FIFO overrun error interrupt flag
      \arg        EDIM_AFMT_FLAG_FIFOUNR: FIFO underrun error interrupt flag
      \arg        EDIM_AFMT_FLAG_DMATO: DMA request timeout error interrupt flag
    \param[out] none
    \retval     none
*/
void edim_afmt_flag_clear(uint32_t flag)
{
    EDIM_AFMT_STAT = (flag & EDIM_AFMT_FLAG_MASK);
}

/*!
    \brief      get EDIM_AFMT interrupt flag status (API_ID(0x0014U))
    \param[in]  int_flag: EDIM_AFMT interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_INT_FLAG_EOC: end of communication interrupt flag
      \arg        EDIM_AFMT_INT_FLAG_TOERR: timeout error interrupt flag
      \arg        EDIM_AFMT_INT_FLAG_FIFOOVR: FIFO overrun error interrupt flag
      \arg        EDIM_AFMT_INT_FLAG_FIFOUNR: FIFO underrun error interrupt flag
      \arg        EDIM_AFMT_INT_FLAG_DMATO: DMA request timeout error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
    \Note       After the interrupt enable bit is cleared, if the hardware flag remains set, this API will still return RESET.
                Therefore, in an ISR or during the interrupt-disable flow, this API alone must not be relied upon to determine whether the flag should be cleared.
                The corresponding flag must be cleared according to the module-specific rules, and the NVIC-pending bit should also be cleared when necessary.
*/
FlagStatus edim_afmt_interrupt_flag_get(edim_afmt_interrupt_flag_enum int_flag)
{
    uint32_t ret1 = RESET;
    uint32_t ret2 = RESET;
    FlagStatus return_val = RESET;

    /* get the status of interrupt enable */
    ret1 = (EDIM_AFMT_REG_VAL(EDIM_AFMT, int_flag) & BIT(EDIM_AFMT_BIT_POS(int_flag)));
    /* get the status of interrupt flag */
    ret2 = (EDIM_AFMT_REG_VAL2(EDIM_AFMT, int_flag) & BIT(EDIM_AFMT_BIT_POS2(int_flag)));

    if(EDIM_AFMT_INT_FLAG_EOC == int_flag) {
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
    \brief      clear EDIM_AFMT interrupt flag status (API_ID(0x0015U))
    \param[in]  int_flag: EDIM_AFMT interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        EDIM_AFMT_INT_FLAG_TOERR: timeout error interrupt flag
      \arg        EDIM_AFMT_INT_FLAG_FIFOOVR: FIFO overrun error interrupt flag
      \arg        EDIM_AFMT_INT_FLAG_FIFOUNR: FIFO underrun error interrupt flag
      \arg        EDIM_AFMT_INT_FLAG_DMATO: DMA request timeout error interrupt flag
    \param[out] none
    \retval     none
*/
void edim_afmt_interrupt_flag_clear(edim_afmt_interrupt_flag_enum int_flag)
{
    EDIM_AFMT_STAT = BIT(EDIM_AFMT_BIT_POS2(int_flag));
}
