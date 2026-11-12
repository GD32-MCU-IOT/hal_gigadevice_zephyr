/*!
    \file    gd32h77x_78x_edim_tfmt.c
    \brief   EDIM TFMT driver

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

#include "gd32h77x_78x_edim_tfmt.h"

/*!
    \brief      deinit EDIM_TFMT (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_tfmt_deinit(void)
{
    rcu_periph_reset_enable(RCU_TFMTRST);
    rcu_periph_reset_disable(RCU_TFMTRST);
}

/*!
    \brief      configure EDIM_TFMT trigger mode (API_ID(0x0002U))
    \param[in]  mode: EDIM_TFMT trigger mode,
                only one parameter can be selected which is shown as below:
      \arg        EDIM_TFMT_TRIGGER_SWT: transmission trigger is input from EDIM_TFMT_SWT
      \arg        EDIM_TFMT_TRIGGER_TRIGSEL: transmission trigger is input from TRIGSEL
    \param[out] none
    \retval     none
*/
void edim_tfmt_trigger_mode_config(edim_tfmt_trigger_enum mode)
{
    if(mode == EDIM_TFMT_TRIGGER_SWT) {
        EDIM_TFMT_CFG &= (~EDIM_TFMT_CFG_TRANSTSEL);
    } else {
        EDIM_TFMT_CFG |= EDIM_TFMT_CFG_TRANSTSEL;
    }
}

/*!
    \brief      configure EDIM_TFMT command to be sent (API_ID(0x0003U))
    \param[in]  cc: slave command,
                only one parameter can be selected which is shown as below:
      \arg        EDIM_TFMT_DATAID_CC_RDPOS: read absolute data in one revolution
      \arg        EDIM_TFMT_DATAID_CC_RDTURNS: read multi-turn data
      \arg        EDIM_TFMT_DATAID_CC_RDENID: read ENID
      \arg        EDIM_TFMT_DATAID_CC_RDALL: read all data
      \arg        EDIM_TFMT_DATAID_CC_WRROM: write EEPROM
      \arg        EDIM_TFMT_DATAID_CC_RSTERR: reset all errors
      \arg        EDIM_TFMT_DATAID_CC_RSTPOS: reset one revolution data
      \arg        EDIM_TFMT_DATAID_CC_RSTTURNSERR: reset multi-turn data and all errors
      \arg        EDIM_TFMT_DATAID_CC_RDROM: read EEPROM
    \param[out] none
    \retval     none
*/
void edim_tfmt_command(uint32_t cc)
{
    EDIM_TFMT_DATAID = ((uint32_t)cc & EDIM_TFMT_DATAID_CC);
}

/*!
    \brief      configure EDIM_TFMT command with eeprom write to be sent (API_ID(0x0004U))
    \param[in]  addr: slave eeprom address, 0~0xFF
    \param[in]  data: write slave eeprom data, 0~0xFF
    \param[out] none
    \retval     none
*/
void edim_tfmt_command_with_eeprom_write(uint8_t addr, uint8_t data)
{
    EDIM_TFMT_DATAID = EDIM_TFMT_DATAID_CC_WRROM;
    EDIM_TFMT_EEPROM = EEPROMDATA(data) | EEPROMADDR(addr);
}

/*!
    \brief      configure EDIM_TFMT command with EEPROM read to be sent (API_ID(0x0005U))
    \param[in]  addr: slave EEPROM address, 0~0xFF
    \param[out] none
    \retval     none
*/
void edim_tfmt_command_with_eeprom_read(uint8_t addr)
{
    EDIM_TFMT_DATAID = EDIM_TFMT_DATAID_CC_RDROM;
    EDIM_TFMT_EEPROM = EEPROMADDR(addr);
}

/*!
    \brief      enable EDIM_TFMT software trigger (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_tfmt_software_trigger(void)
{
    EDIM_TFMT_SWT |= EDIM_TFMT_SWT_SWTR;
}

/*!
    \brief      enable EDIM_TFMT DMA (API_ID(0x0007U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_tfmt_dma_enable(void)
{
    EDIM_TFMT_CFG |= EDIM_TFMT_CFG_DFEN;
}

/*!
    \brief      disable EDIM_TFMT DMA (API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_tfmt_dma_disable(void)
{
    EDIM_TFMT_CFG &= (~EDIM_TFMT_CFG_DFEN);
}

/*!
    \brief      flush EDIM_TFMT DMA FIFO (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_tfmt_dma_flush(void)
{
    EDIM_TFMT_CFG |= EDIM_TFMT_CFG_FIFOFH;
}

/*!
    \brief      select EDIM_TFMT DMA FIFO data source (API_ID(0x000AU))
    \param[in]  reg_selected: DMA request and FIFO enable for EDIM_TFMT_RDATA0/1/2/3
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_TFMT_CFG_DFEN0: DMA request and FIFO enable for EDIM_TFMT_RDATA0
      \arg        EDIM_TFMT_CFG_DFEN1: DMA request and FIFO enable for EDIM_TFMT_RDATA1
      \arg        EDIM_TFMT_CFG_DFEN2: DMA request and FIFO enable for EDIM_TFMT_RDATA2
      \arg        EDIM_TFMT_CFG_DFEN3: DMA request and FIFO enable for EDIM_TFMT_RDATA3
    \param[out] none
    \retval     none
*/
void edim_tfmt_dma_select(uint32_t reg_selected)
{
    uint32_t reg_tmp;

    reg_tmp = EDIM_TFMT_CFG;
    reg_tmp &= ~(EDIM_TFMT_CFG_DFEN0 | EDIM_TFMT_CFG_DFEN1 | EDIM_TFMT_CFG_DFEN2 | EDIM_TFMT_CFG_DFEN3);
    reg_tmp |= (reg_selected & (EDIM_TFMT_CFG_DFEN0 | EDIM_TFMT_CFG_DFEN1 | EDIM_TFMT_CFG_DFEN2 | EDIM_TFMT_CFG_DFEN3));
    EDIM_TFMT_CFG = reg_tmp;
}

/*!
    \brief      read EDIM_TFMT RDATAx (API_ID(0x000BU))
    \param[in]  data_n: EDIM_TFMT_RDATA0/1/2/3
                only one parameter can be selected which is shown as below:
      \arg        EDIM_TFMT_RDATA0: receive data0
      \arg        EDIM_TFMT_RDATA1: receive data1
      \arg        EDIM_TFMT_RDATA2: receive data2
      \arg        EDIM_TFMT_RDATA3: receive data3
    \param[out] none
    \retval     the received data value: 0~0xFFFFFFFF
*/
uint32_t edim_tfmt_data_read(edim_tfmt_rdata_enum data_n)
{
    return EDIM_TFMT_RDATA(data_n);
}

/*!
    \brief      configure EDIM_TFMT status update mode (API_ID(0x000CU))
    \param[in]  mode: status update mode
                only one parameter can be selected which is shown as below:
      \arg        EDIM_TFMT_STAT_DYNAMIC: EDIM_TFMT status dynamic update mode
      \arg        EDIM_TFMT_STAT_STATIC: EDIM_TFMT status static update mode
    \param[out] none
    \retval     none
*/
void edim_tfmt_status_update_mode_config(uint32_t mode)
{
    uint32_t reg_tmp;
    reg_tmp = EDIM_TFMT_STATUPMODE;
    reg_tmp &= ~(EDIM_TFMT_STATUPMODE_STATUPMODE);
    reg_tmp |= (mode & EDIM_TFMT_STATUPMODE_STATUPMODE);
    EDIM_TFMT_STATUPMODE = reg_tmp;
}

/*!
    \brief      enable EDIM_TFMT interrupt (API_ID(0x000DU))
    \param[in]  interrupt: EDIM_TFMT interrupt
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_TFMT_INT_EOC: end of communication interrupt
      \arg        EDIM_TFMT_INT_TOERR: timeout error interrupt
      \arg        EDIM_TFMT_INT_CRC: CRC error interrupt
      \arg        EDIM_TFMT_INT_SDEL: frame error in received frame interrupt
      \arg        EDIM_TFMT_INT_PCTL: parity error in received frame interrupt
      \arg        EDIM_TFMT_INT_CC: data ID error interrupt
      \arg        EDIM_TFMT_INT_EEPROMBUSY: EEPROM busy interrupt
      \arg        EDIM_TFMT_INT_DEL: frame error in request frame interrupt
      \arg        EDIM_TFMT_INT_PREQ: parity error in request frame interrupt
      \arg        EDIM_TFMT_INT_ALRM: alarm interrupt
      \arg        EDIM_TFMT_INT_CNT: counting error interrupt
      \arg        EDIM_TFMT_INT_FIFOOVR: FIFO overrun error interrupt
      \arg        EDIM_TFMT_INT_FIFOUNR: FIFO underrun error interrupt
      \arg        EDIM_TFMT_INT_DMATO: DMA request timeout error interrupt
    \param[out] none
    \retval     none
*/
void edim_tfmt_interrupt_enable(uint32_t interrupt)
{
    EDIM_TFMT_INTEN |= (interrupt & EDIM_TFMT_INTEN_MASK);
}

/*!
    \brief      disable EDIM_TFMT interrupt (API_ID(0x000EU))
    \param[in]  interrupt: EDIM_TFMT interrupt
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_TFMT_INT_EOC: end of communication interrupt
      \arg        EDIM_TFMT_INT_TOERR: timeout error interrupt
      \arg        EDIM_TFMT_INT_CRC: CRC error interrupt
      \arg        EDIM_TFMT_INT_SDEL: frame error in received frame interrupt
      \arg        EDIM_TFMT_INT_PCTL: parity error in received frame interrupt
      \arg        EDIM_TFMT_INT_CC: data ID error interrupt
      \arg        EDIM_TFMT_INT_EEPROMBUSY: EEPROM busy interrupt
      \arg        EDIM_TFMT_INT_DEL: frame error in request frame interrupt
      \arg        EDIM_TFMT_INT_PREQ: parity error in request frame interrupt
      \arg        EDIM_TFMT_INT_ALRM: alarm interrupt
      \arg        EDIM_TFMT_INT_CNT: counting error interrupt
      \arg        EDIM_TFMT_INT_FIFOOVR: FIFO overrun error interrupt
      \arg        EDIM_TFMT_INT_FIFOUNR: FIFO underrun error interrupt
      \arg        EDIM_TFMT_INT_DMATO: DMA request timeout error interrupt
    \param[out] none
    \retval     none
*/
void edim_tfmt_interrupt_disable(uint32_t interrupt)
{
    EDIM_TFMT_INTEN &= (~(interrupt & EDIM_TFMT_INTEN_MASK));
}

/*!
    \brief      get EDIM_TFMT flag status (API_ID(0x000FU))
    \param[in]  flag: EDIM_TFMT flag
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_TFMT_FLAG_EOC: end of communication flag
      \arg        EDIM_TFMT_FLAG_TBUSYF: transmit busy flag
      \arg        EDIM_TFMT_FLAG_RBUSYF: receive busy flag
      \arg        EDIM_TFMT_FLAG_TOERR: timeout error flag
      \arg        EDIM_TFMT_FLAG_CRC: CRC error flag
      \arg        EDIM_TFMT_FLAG_SDEL: frame error in received frame flag
      \arg        EDIM_TFMT_FLAG_PCTL: parity error in received frame flag
      \arg        EDIM_TFMT_FLAG_CC: data ID error flag
      \arg        EDIM_TFMT_FLAG_EEPROMBUSY: EEPROM busy flag
      \arg        EDIM_TFMT_FLAG_DEL: frame error in request frame flag
      \arg        EDIM_TFMT_FLAG_PREQ: parity error in request frame flag
      \arg        EDIM_TFMT_FLAG_ALRM: alarm flag
      \arg        EDIM_TFMT_FLAG_CNT: counting error flag
      \arg        EDIM_TFMT_FLAG_FIFOOVR: FIFO overrun error flag
      \arg        EDIM_TFMT_FLAG_FIFOUNR: FIFO underrun error flag
      \arg        EDIM_TFMT_FLAG_DMATO: DMA request timeout error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus edim_tfmt_flag_get(uint32_t flag)
{
    FlagStatus return_val = RESET;
    if(RESET != (EDIM_TFMT_STAT & flag)) {
        return_val = SET;
    } else {
        return_val = RESET;
    }
    return return_val;
}

/*!
    \brief      clear EDIM_TFMT flag status (API_ID(0x0010U))
    \param[in]  flag: EDIM_TFMT flag
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_TFMT_FLAG_TOERR: timeout error flag
      \arg        EDIM_TFMT_FLAG_CRC: CRC error flag
      \arg        EDIM_TFMT_FLAG_SDEL: frame error in received frame flag
      \arg        EDIM_TFMT_FLAG_PCTL: parity error in received frame flag
      \arg        EDIM_TFMT_FLAG_CC: data ID error flag
      \arg        EDIM_TFMT_FLAG_EEPROMBUSY: EEPROM busy flag
      \arg        EDIM_TFMT_FLAG_DEL: frame error in request frame flag
      \arg        EDIM_TFMT_FLAG_PREQ: parity error in request frame flag
      \arg        EDIM_TFMT_FLAG_ALRM: alarm flag
      \arg        EDIM_TFMT_FLAG_CNT: counting error flag
      \arg        EDIM_TFMT_FLAG_FIFOOVR: FIFO overrun error flag
      \arg        EDIM_TFMT_FLAG_FIFOUNR: FIFO underrun error flag
      \arg        EDIM_TFMT_FLAG_DMATO: DMA request timeout error flag
    \param[out] none
    \retval     none
*/
void edim_tfmt_flag_clear(uint32_t flag)
{
    EDIM_TFMT_STAT = (flag & EDIM_TFMT_FLAG_MASK);
}

/*!
    \brief      get EDIM_TFMT interrupt flag (API_ID(0x0011U))
    \param[in]  int_flag: EDIM_TFMT interrupt flag
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_TFMT_INT_FLAG_EOC: end of communication interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_TOERR: timeout error interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_CRC: CRC error interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_SDEL: frame error in received frame interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_PCTL: parity error in received frame interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_CC: data ID error interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_EEPROMBUSY: EEPROM busy interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_DEL: frame error in request frame interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_PREQ: parity error in request frame interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_ALRM: alarm interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_CNT: counting error interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_FIFOOVR: FIFO overrun error interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_FIFOUNR: FIFO underrun error interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_DMATO: DMA request timeout error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
    \Note       After the interrupt enable bit is cleared, if the hardware flag remains set, this API will still return RESET.
                Therefore, in an ISR or during the interrupt-disable flow, this API alone must not be relied upon to determine whether the flag should be cleared.
                The corresponding flag must be cleared according to the module-specific rules, and the NVIC-pending bit should also be cleared when necessary.
*/
FlagStatus edim_tfmt_interrupt_flag_get(edim_tfmt_interrupt_flag_enum int_flag)
{
    uint32_t ret1 = RESET;
    uint32_t ret2 = RESET;
    FlagStatus return_val = RESET;
    /* get the status of interrupt enable bit */
    ret1 = (EDIM_TFMT_REG_VAL(EDIM_TFMT, int_flag) & BIT(EDIM_TFMT_BIT_POS(int_flag)));
    /* get the status of interrupt flag */
    ret2 = (EDIM_TFMT_REG_VAL2(EDIM_TFMT, int_flag) & BIT(EDIM_TFMT_BIT_POS2(int_flag)));
    if(ret1 && ret2) {
        return_val = SET;
    } else {
        return_val = RESET;
    }
    return return_val;
}

/*!
    \brief      clear EDIM_TFMT interrupt flag (API_ID(0x0012U))
    \param[in]  int_flag: EDIM_TFMT interrupt flag
                one or more parameter can be selected which is shown as below:
      \arg        EDIM_TFMT_INT_FLAG_TOERR: timeout error interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_CRC: CRC error interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_SDEL: frame error in received frame interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_PCTL: parity error in received frame interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_CC: data ID error interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_EEPROMBUSY: EEPROM busy interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_DEL: frame error in request frame interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_PREQ: parity error in request frame interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_ALRM: alarm interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_CNT: counting error interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_FIFOOVR: FIFO overrun error interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_FIFOUNR: FIFO underrun error interrupt flag
      \arg        EDIM_TFMT_INT_FLAG_DMATO: DMA request timeout error interrupt flag
    \param[out] none
    \retval     none
*/
void edim_tfmt_interrupt_flag_clear(edim_tfmt_interrupt_flag_enum int_flag)
{
    EDIM_TFMT_STAT = BIT(EDIM_TFMT_BIT_POS2(int_flag));
}
