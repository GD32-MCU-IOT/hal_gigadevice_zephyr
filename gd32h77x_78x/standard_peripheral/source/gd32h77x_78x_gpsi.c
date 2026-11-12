/*!
    \file    gd32h77x_78x_gpsi.h
    \brief   definitions for the GPSI

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

#include "gd32h77x_78x_gpsi.h"

/*!
    \brief      gpsi deinit (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpsi_deinit(void)
{
    rcu_periph_reset_enable(RCU_DCIRST);
    rcu_periph_reset_disable(RCU_DCIRST);
}

/*!
    \brief      initialize the GPSI parameter structure with default values (API_ID(0x000EU))
    \param[in]  none
    \param[out] gpsi_struct: GPSI parameter initialization structure
    \retval     none
*/
void gpsi_struct_para_init(gpsi_parameter_struct *gpsi_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(gpsi_struct)) {
        fw_debug_report_err(GPSI_MODULE_ID, API_ID(0x000EU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* set the GPSI struct with the default values */
        gpsi_struct->data_direction = GPSI_RECEIVE_MODE;
        gpsi_struct->data_en_ready_config = GPSI_DE_RDY_DISABLE;
        gpsi_struct->clock_polarity = GPSI_FALLING_EDGE;
        gpsi_struct->de_polarity = GPSI_DEPOL_ACTIVE_LOW;
        gpsi_struct->rdy_polarity = GPSI_RDYPOL_ACTIVE_LOW;
        gpsi_struct->data_width = GPSI_8LINES;
    }
}

/*!
    \brief      initialize gpsi registers (API_ID(0x0002U))
    \param[in]  gpsi_struct: gpsi parameter initialization structure
                members of the structure and the member values are shown as below:
                data_direction: GPSI_RECEIVE_MODE, GPSI_TRANSMIT_MODE
                data_en_ready_config:GPSI_DE_RDY_DISABLE
                                     GPSI_RDY_ENABLE
                                     GPSI_DE_ENABLE
                                     GPSI_DE_RDY_ALT_ENABLE
                                     GPSI_MAP_RDY_BIDIR_ENABLE
                                     GPSI_RDY_MAP_ENABLE
                                     GPSI_DE_MAP_ENABLE
                                     GPSI_MAP_DE_BIDIR_ENABLE
                clock_polarity: GPSI_FALLING_EDGE, GPSI_RISING_EDGE
                de_polarity: GPSI_RDYPOL_ACTIVE_LOW, GPSI_RDYPOL_ACTIVE_HIGH
                rdy_polarity: GPSI_RDYPOL_ACTIVE_LOW, GPSI_RDYPOL_ACTIVE_HIGH
                data_width: GPSI_8LINES, GPSI_16LINES
    \param[out] none
    \retval     none
*/
void gpsi_init(gpsi_parameter_struct *gpsi_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(gpsi_struct)) {
        fw_debug_report_err(GPSI_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t reg = 0U;
        /* disable capture function and gpsi */
        GPSI_CTL &= ~GPSI_CTL_GPSIEN;
        reg = GPSI_CTL;
        reg &= ~(GPSI_CTL_CKPL | GPSI_CTL_DPL | GPSI_CTL_RPL | GPSI_CTL_SIGCFG | GPSI_CTL_DIRSEL | GPSI_CTL_GPSIF | GPSI_CTL_DMAEN);

        /* configure gpsi parameter */
        reg |= gpsi_struct->data_direction;
        reg |= gpsi_struct->data_en_ready_config;
        reg |= gpsi_struct->de_polarity;
        reg |= gpsi_struct->rdy_polarity;
        reg |= gpsi_struct->data_width;

        if((GPSI_TRANSMIT_MODE == gpsi_struct->data_direction)) {
            if((GPSI_FALLING_EDGE == gpsi_struct->clock_polarity)) {
                reg |= GPSI_CTL_CKPL;
            } else {
                reg &= ~GPSI_CTL_CKPL;
            }
        }else{
            if((GPSI_RISING_EDGE == gpsi_struct->clock_polarity)) {
                reg |= GPSI_CTL_CKPL;
            } else {
                reg &= ~GPSI_CTL_CKPL;
            }
        }
        GPSI_CTL = reg;
    }
}

/*!
    \brief      select captured data width (API_ID(0x0003U))
    \param[in]  buswidth: GPSI data transmit width
                only one parameter can be selected which is shown as below:
      \arg        GPSI_8LINES: Interface captures 8-bit data on every parallel data clock
      \arg        GPSI_16LINES: Interface captures 16-bit data on every parallel data clock
    \param[out] none
    \retval     none
*/
void gpsi_buswidth_config(uint32_t buswidth)
{
    GPSI_CTL &= ~GPSI_CTL_GPSIF;
    GPSI_CTL |= (uint32_t)buswidth;
}

/*!
    \brief      enable gpsi function (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpsi_enable(void)
{
    GPSI_CTL |= GPSI_CTL_GPSIEN;
}

/*!
    \brief      disable gpsi function (API_ID(0x0005U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpsi_disable(void)
{
    GPSI_CTL &= ~GPSI_CTL_GPSIEN;
}

/*!
    \brief      read gpsi data register (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     data
*/
uint32_t gpsi_data_read(void)
{
    return GPSI_DATA;
}

/*!
    \brief      gpsi dma transfers enable (API_ID(0x0007U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpsi_dma_enable(void)
{
    GPSI_CTL |= GPSI_CTL_DMAEN;
}

/*!
    \brief      gpsi dma transfers disable (API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpsi_dma_disable(void)
{
    GPSI_CTL &= ~GPSI_CTL_DMAEN;
}

/*!
    \brief      get specified flag (API_ID(0x0009U))
    \param[in]  flag: specify which flag to get
                only one parameter can be selected which is shown as below:
      \arg        GPSI_STAT_4BRF: FIFO is ready to transfer four bytes.
      \arg        GPSI_STAT_1BRF: FIFO is ready to transfer one byte.
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus gpsi_flag_get(uint32_t flag)
{
    FlagStatus reval = RESET;
    uint32_t stat = 0U;
    stat = GPSI_STAT;

    if(flag & stat) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      enable specified gpsi interrupt (API_ID(0x000AU))
    \param[in]  interrupt: specify which interrupt to enable
                only one parameter can be selected which is shown as below:
      \arg        GPSI_INTEN_OUIE: Data buffer overrun or underrun interrupt enable
    \param[out] none
    \retval     none
*/
void gpsi_interrupt_enable(uint32_t interrupt)
{
    GPSI_INTEN |= interrupt;
}

/*!
    \brief      disable specified gpsi interrupt (API_ID(0x000BU))
    \param[in]  interrupt: specify which interrupt to disable
                one or more parameter can be selected which is shown as below:
      \arg        GPSI_INTEN_OUIE: Data buffer overrun or underrun interrupt disable
    \param[out] none
    \retval     none
*/
void gpsi_interrupt_disable(uint32_t interrupt)
{
    GPSI_INTEN &= ~interrupt;
}

/*!
    \brief      get specified interrupt flag (API_ID(0x000CU))
    \param[in]  int_flag: specify which flag to get
                only one parameter can be selected which is shown as below:
      \arg        GPSI_INTF_OUIF: Data buffer overrun or underrun interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus gpsi_interrupt_flag_get(uint32_t int_flag)
{
    FlagStatus reval = RESET;

    if(RESET == (GPSI_INTF & int_flag)) {
        reval = RESET;
    } else {
        reval = SET;
    }
    return reval;
}

/*!
    \brief      clear specified interrupt flag (API_ID(0x000DU))
    \param[in]  int_flag: specify which flag to clear
                only one parameter can be selected which is shown as below:
      \arg        GPSI_INTC_OUFC: Data buffer overrun or underrun interrupt flag clear
    \param[out] none
    \retval     none
*/
void gpsi_interrupt_flag_clear(uint32_t int_flag)
{
    GPSI_INTC |= int_flag;
}
