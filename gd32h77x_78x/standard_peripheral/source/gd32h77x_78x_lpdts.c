/*!
    \file    gd32h77x_78x_lpdts.c
    \brief   LPDTS driver

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

#include "gd32h77x_78x_lpdts.h"

/*!
    \brief      reset the LPDTS registers (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lpdts_deinit(void)
{
    rcu_periph_reset_enable(RCU_LPDTSRST);
    rcu_periph_reset_disable(RCU_LPDTSRST);
}

/*!
    \brief      initialize the LPDTS (API_ID(0x0002U))
    \param[in]  init_struct: the initialization data needed to initialize LPDTS_CFG
                  ref_clock: REF_PCLK, REF_LXTAL
                  trigger_input: NO_HARDWARE_TRIGGER, LPDTS_TRG
                  sampling_time: SPT_CLOCK_x(x=1..15)
    \param[out] none
    \retval     none
*/
void lpdts_init(lpdts_parameter_struct *init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(LPDTS_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } /* FW_DEBUG_ERR_REPORT */
#endif
    {
        uint32_t reg;
        /* configure the LPDTS_CFG */
        reg = LPDTS_CFG;
        reg &= ~(LPDTS_CFG_REFSEL | LPDTS_CFG_ITSEL | LPDTS_CFG_SPT);
        reg |= ((init_struct->ref_clock & LPDTS_CFG_REFSEL) |
                (init_struct->trigger_input & LPDTS_CFG_ITSEL) |
                (init_struct->sampling_time & LPDTS_CFG_SPT));
        LPDTS_CFG = reg;
    }
}

/*!
    \brief      initialize the parameters of LPDTS struct with the default values (API_ID(0x0003U))
    \param[in]  init_struct: the initialization data needed to initialize LPDTS
    \param[out] none
    \retval     none
*/
void lpdts_struct_para_init(lpdts_parameter_struct *init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(LPDTS_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else /* FW_DEBUG_ERR_REPORT */
#endif
    {
        /* set the struct with the default values */
        init_struct->ref_clock          = REF_PCLK;
        init_struct->trigger_input      = NO_HARDWARE_TRIGGER;
        init_struct->sampling_time      = SPT_CLOCK_15;
    }
}

/*!
    \brief      configure LPDTS high threshold value (API_ID(0x0004U))
    \param[in]  value: high threshold value(0~65535)
    \param[out] none
    \retval     none
*/
void lpdts_high_threshold_set(uint16_t value)
{
    uint32_t reg;
    /* configure the LPDTS_IT */
    reg = LPDTS_IT;
    reg &= ~LPDTS_IT_INTHT;
    reg |= (uint32_t)value << 16U;
    LPDTS_IT = reg;
}

/*!
    \brief      configure LPDTS low threshold value (API_ID(0x0005U))
    \param[in]  value: low threshold value(0~65535)
    \param[out] none
    \retval     none
*/
void lpdts_low_threshold_set(uint16_t value)
{
    uint32_t reg;
    /* configure the LPDTS_IT */
    reg = LPDTS_IT;
    reg &= ~LPDTS_IT_INTLT;
    reg |= (uint32_t)value;
    LPDTS_IT = reg;
}

/*!
    \brief      configure LPDTS reference clock selection (API_ID(0x0006U))
    \param[in]  source: reference clock source
                only one parameter can be selected which is shown as below:
      \arg        REF_PCLK: high speed reference clock (PCLK)
      \arg        REF_LXTAL: low speed reference clock (LXTAL)
    \param[out] none
    \retval     none
*/
void lpdts_ref_clock_source_config(uint32_t source)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LPDTS_REF_CLOCK_SOURCE(source)) {
        fw_debug_report_err(LPDTS_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
    } else /* FW_DEBUG_ERR_REPORT */
#endif
    {
        uint32_t reg;
        /* configure the LPDTS_CFG */
        reg = LPDTS_CFG;
        reg &= ~REF_LXTAL;
        reg |= source;
        LPDTS_CFG = reg;
    }
}

/*!
    \brief      enable LPDTS interrupt (API_ID(0x0007U))
    \param[in]  interrupt: the LPDTS interrupt
                one or more parameters can be selected which is shown as below:
      \arg        LPDTS_INT_EMIE
      \arg        LPDTS_INT_LTIE
      \arg        LPDTS_INT_HTIE
      \arg        LPDTS_INT_EMAIE
      \arg        LPDTS_INT_LTAIE
      \arg        LPDTS_INT_HTAIE
    \param[out] none
    \retval     none
*/
void lpdts_interrupt_enable(uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LPDTS_INTERRUPT(interrupt)) {
        fw_debug_report_err(LPDTS_MODULE_ID, API_ID(0x007U), ERR_PARAM_INVALID);
    } else /* FW_DEBUG_ERR_REPORT */
#endif
    {
        LPDTS_INTEN |= interrupt;
    }
}

/*!
    \brief      disable LPDTS interrupt (API_ID(0x0008U))
    \param[in]  interrupt: the LPDTS interrupt
                one or more parameters can be selected which is shown as below:
      \arg        LPDTS_INT_EMIE
      \arg        LPDTS_INT_LTIE
      \arg        LPDTS_INT_HTIE
      \arg        LPDTS_INT_EMAIE
      \arg        LPDTS_INT_LTAIE
      \arg        LPDTS_INT_HTAIE
    \param[out] none
    \retval     none
*/
void lpdts_interrupt_disable(uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LPDTS_INTERRUPT(interrupt)) {
        fw_debug_report_err(LPDTS_MODULE_ID, API_ID(0x008U), ERR_PARAM_INVALID);
    } else /* FW_DEBUG_ERR_REPORT */
#endif
    {
        LPDTS_INTEN &= ~interrupt;
    }
}

/*!
    \brief      get LPDTS flag (API_ID(0x0009U))
    \param[in]  flag: LPDTS ready/interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        LPDTS_FLAG_TSRF
      \arg        LPDTS_FLAG_EMIF
      \arg        LPDTS_FLAG_LTIF
      \arg        LPDTS_FLAG_HTIF
      \arg        LPDTS_FLAG_EMAIF
      \arg        LPDTS_FLAG_LTAIF
      \arg        LPDTS_FLAG_HTAIF
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus lpdts_flag_get(uint32_t flag)
{
    FlagStatus status = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LPDTS_FLAG_GET(flag)) {
        fw_debug_report_err(LPDTS_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    } else /* FW_DEBUG_ERR_REPORT */
#endif
    {
        if(LPDTS_STAT & flag) {
            status = SET;
        }
    }
    /* return the state of corresponding LPDTS flag */
    return status;
}

/*!
    \brief      clear the LPDTS flag (API_ID(0x000AU))
    \param[in]  flag: LPDTS flag
                only one parameter can be selected which is shown as below:
      \arg        LPDTS_FLAG_EMIF
      \arg        LPDTS_FLAG_LTIF
      \arg        LPDTS_FLAG_HTIF
      \arg        LPDTS_FLAG_EMAIF
      \arg        LPDTS_FLAG_LTAIF
      \arg        LPDTS_FLAG_HTAIF
    \param[out] none
    \retval     none
*/
void lpdts_flag_clear(uint32_t flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LPDTS_FLAG_CLEAR(flag)) {
        fw_debug_report_err(LPDTS_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else /* FW_DEBUG_ERR_REPORT */
#endif
    {
        /* clear the flags */
        LPDTS_INTC = flag;
    }
}

/*!
    \brief      enable LPDTS temperature sensor (API_ID(0x000BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lpdts_enable(void)
{
    LPDTS_CFG |= LPDTS_CFG_TSEN;
}

/*!
    \brief      disable LPDTS temperature sensor (API_ID(0x000CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lpdts_disable(void)
{
    LPDTS_CFG &= ~LPDTS_CFG_TSEN;
}

/*!
    \brief      enable LPDTS software trigger (API_ID(0x000DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lpdts_soft_trigger_enable(void)
{
    LPDTS_CFG |= LPDTS_CFG_TRGS;
}

/*!
    \brief      disable LPDTS software trigger (API_ID(0x000EU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lpdts_soft_trigger_disable(void)
{
    LPDTS_CFG &= ~LPDTS_CFG_TRGS;
}

/*!
    \brief      get temperature from LPDTS (API_ID(0x000FU))
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus lpdts_temperature_get(int32_t* temperature)
{
    uint32_t freq;
    uint32_t count;
    int32_t t0 = 0;
    uint32_t val;
    uint32_t t0_freq;
    uint32_t ramp_coeff;
    uint32_t reg_cfg;
    ErrStatus ret = SUCCESS;
    /* get the total number of samples */
    count = (LPDTS_DATA & LPDTS_DATA_COVAL);
    /* get LPDTS_CFG configuration */
    reg_cfg = LPDTS_CFG;

#ifdef FW_DEBUG_ERR_REPORT
    /* Check whether the denominator is 0 */
    if((reg_cfg & LPDTS_CFG_REFSEL) != LPDTS_CFG_REFSEL){
        if(NOT_LPDTS_LEGAL_DENOMINATOR(count)) {
            fw_debug_report_err(LPDTS_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
        }
    }
#endif
    
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(temperature)) {
            fw_debug_report_err(LPDTS_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
    }
#endif
    {
        if((reg_cfg & LPDTS_CFG_REFSEL) == LPDTS_CFG_REFSEL) {
            freq = (LXTAL_VALUE * count) / ((reg_cfg & LPDTS_CFG_SPT) >> 15U); /* On Hz */
        } else {
            freq = (2U * rcu_clock_freq_get(CK_APB1) / count) * ((reg_cfg & LPDTS_CFG_SPT) >> 16U) ; /* On Hz */
        }
        /* read factory settings */
        val = (LPDTS_SDATA & LPDTS_SDATA_VAL) >> 16U;
        if(val == 0U) {
            t0 = 25; /* 25 deg C */
        } else if(val == 1U){
            t0 = -40; /* -40 deg C */
        } else {
            ret = ERROR;
        }
        
        t0_freq = (LPDTS_SDATA & LPDTS_SDATA_FREQ) * 100U; /* Hz */
        ramp_coeff = LPDTS_RDATA & LPDTS_RDATA_RCVAL; /* HZ/deg C */
#ifdef FW_DEBUG_ERR_REPORT
        if(NOT_LPDTS_LEGAL_DENOMINATOR(ramp_coeff)) {
            fw_debug_report_err(LPDTS_MODULE_ID, API_ID(0x0021U), ERR_PARAM_INVALID);
        }
#endif
        /* figure out the temperature deg C */
        *temperature = t0 + (((int32_t)freq - (int32_t)t0_freq) / (int32_t)ramp_coeff);
    }
    return ret;
}
