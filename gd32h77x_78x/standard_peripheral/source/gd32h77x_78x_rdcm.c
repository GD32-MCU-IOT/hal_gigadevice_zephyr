/*!
    \file    gd32h77x_78x_rdcm.c
    \brief   RDCM driver

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

#include "gd32h77x_78x_rdcm.h"

/*!
    \brief      deinit RDCM (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_deinit(void)
{
    rcu_periph_reset_enable(RCU_RDCMRST);
    rcu_periph_reset_disable(RCU_RDCMRST);
}

/*!
    \brief      initialize RDCM trigger parameter struct with a default value (API_ID(0x0002U))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void rdcm_trigger_parameter_struct_para_init(rdcm_trigger_parameter_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(RDCM_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        initpara->nco_trigger_sel   = RDCM_NCOETM_DIVISION;
        initpara->cal_trigger_sel   = RDCM_CALSEL_ADC0;
        initpara->cal_trigger_edge  = RDCM_CALETM_DISABLE;
    }
}

/*!
    \brief      configure RDCM trigger function (API_ID(0x0003U))
    \param[in]  trigger_para: RDCM trigger parameter struct
                nco_trigger_sel: RDCM_NCOETM_DIVISION, RDCM_NCOETM_RISING
                                 RDCM_NCOETM_FALLING, RDCM_NCOETM_BOTH
                cal_trigger_sel: RDCM_CALSEL_ADC0, RDCM_CALSEL_ADC1,
                                 RDCM_CALSEL_ADC0_OR_ADC1, RDCM_CALSEL_EXTERNAL_TRIGGER
                cal_trigger_edge: RDCM_CALETM_DISABLE, RDCM_CALETM_RISING
                                  RDCM_CALETM_FALLING, RDCM_CALETM_BOTH
    \param[out] none
    \retval     none
*/
void rdcm_trigger_config(rdcm_trigger_parameter_struct *trigger_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(trigger_para)) {
        fw_debug_report_err(RDCM_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure main chain trigger source */
        RDCM_CS &= (~RDCM_CS_CALSEL);
        RDCM_CS |= (trigger_para->cal_trigger_sel & RDCM_CS_CALSEL);

        /* configure excitor and main chain trigger edge */
        RDCM_CTL &= (~(RDCM_CTL_CALETM | RDCM_CTL_NCOETM));
        RDCM_CTL |= ((trigger_para->cal_trigger_edge & RDCM_CTL_CALETM) | (trigger_para->nco_trigger_sel & RDCM_CTL_NCOETM));
    }
}

/*!
    \brief      initialize RDCM excitor output parameter struct with a default value (API_ID(0x0004U))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void rdcm_excitor_output_parameter_struct_para_init(rdcm_excitor_output_parameter_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(RDCM_MODULE_ID, API_ID(0x0004U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        initpara->exc_en     = RDCM_EXC_DISABLE;
        initpara->exc_fre    = 0U;
        initpara->exc_div    = 0U;
        initpara->exc_phase  = 0U;
        initpara->exc_amp    = 0U;
    }
}

/*!
    \brief      configure RDCM excitor output function (API_ID(0x0005U))
    \param[in]  exc_outputpara: RDCM excitor output parameter struct
                exc_en: RDCM_EXC_ENABLE, RDCM_EXC_DISABLE
                exc_fre: frequency of the exciter, 0~0x3FFF
                exc_div: NCO calculation frequency division factor, 0~0x3FFF
                exc_phase: initial phase of the exciter, 0~0x3FFF
                exc_amp: amplitude of the exciter, 0~0x1FFF
    \param[out] none
    \retval     none
*/
void rdcm_excitor_output_config(rdcm_excitor_output_parameter_struct *exc_outputpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(exc_outputpara)) {
        fw_debug_report_err(RDCM_MODULE_ID, API_ID(0x0005U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* disable excitor output */
        RDCM_CTL &= (~RDCM_CTL_EXCEN);

        /* configure excitor output phase and frequency */
        RDCM_EXCFG0 &= (~(RDCM_EXCFG0_FEXC | RDCM_EXCFG0_PEXC));
        RDCM_EXCFG0 |= ((exc_outputpara->exc_fre & RDCM_EXCFG0_FEXC) | ((exc_outputpara->exc_phase << 16U) & RDCM_EXCFG0_PEXC));

        /* configure excitor output amplitude and nco calculation frequency division */
        RDCM_EXCFG1 &= (~(RDCM_EXCFG1_AEXC | RDCM_EXCFG1_NCODIV));
        RDCM_EXCFG1 |= ((exc_outputpara->exc_amp & RDCM_EXCFG1_AEXC) | ((exc_outputpara->exc_div << 16U) & RDCM_EXCFG1_NCODIV));

        /* configure excitor output enable */
        RDCM_CTL |= (exc_outputpara->exc_en & RDCM_CTL_EXCEN);
    }
}

/*!
    \brief      initialize RDCM excitor pwm parameter struct with a default value (API_ID(0x0006U))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void rdcm_pwm_parameter_struct_para_init(rdcm_pwm_parameter_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(RDCM_MODULE_ID, API_ID(0x0006U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        initpara->pwm_en      = RDCM_PWM_DISABLE;
        initpara->bit_reverse = RDCM_BREVM_NORMAL;
        initpara->pwm_gain    = 0U;
        initpara->pwm_offset  = 0U;
    }
}

/*!
    \brief      configure RDCM excitor pwm function (API_ID(0x0007U))
    \param[in]  pwm_para: RDCM pwm parameter struct
                pwm_en: RDCM_PWM_ENABLE, RDCM_PWM_DISABLE
                bit_reverse: RDCM_BREVM_NORMAL, RDCM_BREVM_BIT_REVERSED
                pwm_offset: PWM offset for PWM value, 0~0x3FFF
                pwm_gain: PWM gain for PWM value, 0~0x3FFF
    \param[out] none
    \retval     none
*/
void rdcm_excitor_pwm_config(rdcm_pwm_parameter_struct *pwm_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(pwm_para)) {
        fw_debug_report_err(RDCM_MODULE_ID, API_ID(0x0007U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* disable pwm output */
        RDCM_PWMCFG &= (~RDCM_PWMCFG_PWMEN);

        /* configure pwm bit-reversed mode */
        RDCM_PWMCFG &= (~RDCM_PWMCFG_BREVM);
        RDCM_PWMCFG |= (pwm_para->bit_reverse & RDCM_PWMCFG_BREVM);

        /* configure pwm offset and gain */
        RDCM_PWMCFG &= (~(RDCM_PWMCFG_PWMOFFSET | RDCM_PWMCFG_PWMGAIN));
        RDCM_PWMCFG |= ((pwm_para->pwm_gain & RDCM_PWMCFG_PWMGAIN) | ((pwm_para->pwm_offset << 16U) & RDCM_PWMCFG_PWMOFFSET));

        /* configure pwm output enable */
        RDCM_PWMCFG |= (pwm_para->pwm_en & RDCM_PWMCFG_PWMEN);
    }
}

/*!
    \brief      initialize RDCM reference frequency mixer parameter struct with a default value (API_ID(0x0008U))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void rdcm_rfm_parameter_struct_para_init(rdcm_rfm_parameter_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(RDCM_MODULE_ID, API_ID(0x0008U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        initpara->i_rfm_en    = RDCM_RFM_DISABLE;
        initpara->i_zc_mode   = RDCM_IZCDMS_DISABLE;
        initpara->i_hf_mode   = 0U;
        initpara->i_rfm_fre   = 0U;
        initpara->i_rfm_phase = 0U;
        initpara->i_zc_th     = 0U;
        initpara->i_zc_th_var = 0U;
        initpara->i_average   = 0U;
        initpara->q_rfm_en    = RDCM_RFM_DISABLE;
        initpara->q_zc_mode   = RDCM_QZCDMS_DISABLE;
        initpara->q_hf_mode   = 0U;
        initpara->q_rfm_fre   = 0U;
        initpara->q_rfm_phase = 0U;
        initpara->q_zc_th     = 0U;
        initpara->q_zc_th_var = 0U;
        initpara->q_average   = 0U;
    }
}

/*!
    \brief      configure RDCM reference frequency mixer function (API_ID(0x0009U))
    \param[in]  rfm_para: RDCM reference frequency mixer parameter struct
                i_rfm_en: RDCM_RFM_DISABLE, RDCM_RFM_ENABLE
                i_zc_mode: RDCM_IZCDMS_DISABLE, RDCM_IZCDMS_POSITIVE, RDCM_IZCDMS_NEGATIVE, RDCM_IZCDMS_BOTH
                i_hf_mode: RDCM_IHFM_DISABLE, RDCM_IHFM_RATEn, n = 1~7
                i_rfm_fre: the frequency control word of the I channel reference frequency mixer, 0~0x3FFF
                i_rfm_phase: initial phase of the I channel reference frequency mixer, 0~0x3FFF
                i_zc_th: the threshold of mismatch counter value in zero crossing detection, 0~0x3FFF
                i_zc_th_var: the threshold variation range of mismatch counter value in zero crossing detection, 0~0x3FFF
                i_average: the mismatch counter average factor, 0~0xF
                q_rfm_en: RDCM_RFM_DISABLE, RDCM_RFM_ENABLE
                q_zc_mode: RDCM_QZCDMS_DISABLE, RDCM_QZCDMS_POSITIVE, RDCM_QZCDMS_NEGATIVE, RDCM_QZCDMS_BOTH
                q_hf_mode: RDCM_QHFM_DISABLE, RDCM_QHFM_RATEn, n = 1~7
                q_rfm_fre: the frequency control word of the Q channel reference frequency mixer, 0~0x3FFF
                q_rfm_phase: initial phase of the Q channel reference frequency mixer, 0~0x3FFF
                q_zc_th: the threshold of mismatch counter value in zero crossing detection, 0~0x3FFF
                q_zc_th_var: the threshold variation range of mismatch counter value in zero crossing detection, 0~0x3FFF
                q_average: the mismatch counter average factor, 0~0xF
    \param[out] none
    \retval     none
*/
void rdcm_reference_frequency_mixer_config(rdcm_rfm_parameter_struct *rfm_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(rfm_para)) {
        fw_debug_report_err(RDCM_MODULE_ID, API_ID(0x0009U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* I channel configuration */
        /* disable reference frequency mixer */
        RDCM_CTL &= (~RDCM_CTL_IRFMEN);

        /* zero crossing detection mode selection */
        RDCM_CTL &= (~RDCM_CTL_IZCDMS);
        RDCM_CTL |= ((rfm_para->i_zc_mode) & RDCM_CTL_IZCDMS);

        /* high pass filter mode selection */
        RDCM_HFCFG0 &= (~RDCM_HFCFG0_IHFM);
        RDCM_HFCFG0 |= ((rfm_para->i_hf_mode) & RDCM_HFCFG0_IHFM);

        /* reference frequency mixer frequency and initial phase */
        RDCM_RFMCFG0 &= (~RDCM_RFMCFG0_IFRE);
        RDCM_RFMCFG0 |= ((rfm_para->i_rfm_fre << 16U) & RDCM_RFMCFG0_IFRE);
        RDCM_RFMCFG0 &= (~RDCM_RFMCFG0_IPHASE);
        RDCM_RFMCFG0 |= (rfm_para->i_rfm_phase & RDCM_RFMCFG0_IPHASE);

        /* zero crossing detection threshold and variation range */
        RDCM_ZTCFG0 &= (~RDCM_ZTCFG0_IZCTH);
        RDCM_ZTCFG0 |= (rfm_para->i_zc_th & RDCM_ZTCFG0_IZCTH);
        RDCM_ZTCFG1 &= (~RDCM_ZTCFG1_IZTVAR);
        RDCM_ZTCFG1 |= (rfm_para->i_zc_th_var & RDCM_ZTCFG1_IZTVAR);

        /* mismatch counter average factor */
        RDCM_MCACFG &= (~RDCM_MCACFG_IAVEM);
        RDCM_MCACFG |= (rfm_para->i_average & RDCM_MCACFG_IAVEM);

        /* Q channel configuration */
        /* disable reference frequency mixer */
        RDCM_CTL &= (~RDCM_CTL_QRFMEN);

        /* zero crossing detection mode selection */
        RDCM_CTL &= (~RDCM_CTL_QZCDMS);
        RDCM_CTL |= ((rfm_para->q_zc_mode) & RDCM_CTL_QZCDMS);

        /* high pass filter mode selection */
        RDCM_HFCFG1 &= (~RDCM_HFCFG1_QHFM);
        RDCM_HFCFG1 |= ((rfm_para->q_hf_mode)& RDCM_HFCFG1_QHFM);

        /* reference frequency mixer frequency and initial phase */
        RDCM_RFMCFG1 &= (~RDCM_RFMCFG1_QFRE);
        RDCM_RFMCFG1 |= ((rfm_para->q_rfm_fre << 16U) & RDCM_RFMCFG1_QFRE);
        RDCM_RFMCFG1 &= (~RDCM_RFMCFG1_QPHASE);
        RDCM_RFMCFG1 |= (rfm_para->q_rfm_phase & RDCM_RFMCFG1_QPHASE);

        /* zero crossing detection threshold and variation range */
        RDCM_ZTCFG0 &= (~RDCM_ZTCFG0_QZCTH);
        RDCM_ZTCFG0 |= ((rfm_para->q_zc_th << 16U) & RDCM_ZTCFG0_QZCTH);
        RDCM_ZTCFG1 &= (~RDCM_ZTCFG1_QZTVAR);
        RDCM_ZTCFG1 |= ((rfm_para->q_zc_th_var << 16U) & RDCM_ZTCFG1_QZTVAR);

        /* mismatch counter average factor */
        RDCM_MCACFG &= (~RDCM_MCACFG_QAVEM);
        RDCM_MCACFG |= ((rfm_para->q_average << 16U) & RDCM_MCACFG_QAVEM);

        /* configure reference frequency mixer enable */
        RDCM_CTL |= (rfm_para->i_rfm_en & RDCM_CTL_IRFMEN);
        RDCM_CTL |= ((rfm_para->q_rfm_en << 16U) & RDCM_CTL_QRFMEN);
    }
}

/*!
    \brief      initialize RDCM demodulator parameter struct with a default value (API_ID(0x000AU))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void rdcm_demodulator_parameter_struct_para_init(rdcm_demodulator_parameter_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(RDCM_MODULE_ID, API_ID(0x000AU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        initpara->i_dem_en     = RDCM_DEM_DISABLE;
        initpara->i_fir0_en    = RDCM_FIR0_DISABLE;
        initpara->i_fir1_en    = RDCM_FIR1_DISABLE;
        initpara->i_fir1_dec   = RDCM_FIR1_DEC_2;
        initpara->i_cic3_en    = RDCM_CIC3_DISABLE;
        initpara->i_cic3_shift = 0U;
        initpara->i_cic3_gain  = 0x1000U;
        initpara->i_cic3_dec   = 0U;
        initpara->i_cic3_val   = 0U;
        initpara->q_dem_en     = RDCM_DEM_DISABLE;
        initpara->q_fir0_en    = RDCM_FIR0_DISABLE;
        initpara->q_fir1_en    = RDCM_FIR1_DISABLE;
        initpara->q_fir1_dec   = RDCM_FIR1_DEC_2;
        initpara->q_cic3_en    = RDCM_CIC3_DISABLE;
        initpara->q_cic3_shift = 0U;
        initpara->q_cic3_gain  = 0x1000U;
        initpara->q_cic3_dec   = 0U;
        initpara->q_cic3_val   = 0U;
    }
}

/*!
    \brief      configure RDCM demodulator function (API_ID(0x000BU))
    \param[in]  dem_para: RDCM demodulator parameter struct
                i_dem_en: RDCM_DEM_DISABLE, RDCM_DEM_ENABLE
                i_fir0_en: RDCM_FIR0_DISABLE, RDCM_FIR0_ENABLE
                i_fir1_en: RDCM_FIR1_DISABLE, RDCM_FIR1_ENABLE
                i_fir1_dec: RDCM_FIR1_DEC_2, RDCM_FIR1_DEC_1
                i_cic3_en: RDCM_CIC3_DISABLE, RDCM_CIC3_ENABLE
                i_cic3_shift: I channel output shift, 0~0x29
                i_cic3_gain: I channel gain factor, 0~0x1FFF
                i_cic3_dec: I channel CIC filter decimation factor, 0~0x1FF
                i_cic3_val: I channel CIC filter start value, 0~0x1FF
                q_dem_en: RDCM_DEM_DISABLE, RDCM_DEM_ENABLE
                q_fir0_en: RDCM_FIR0_DISABLE, RDCM_FIR0_ENABLE
                q_fir1_en: RDCM_FIR1_DISABLE, RDCM_FIR1_ENABLE
                q_fir1_dec: RDCM_FIR1_DEC_2, RDCM_FIR1_DEC_1
                q_cic3_en: RDCM_CIC3_DISABLE, RDCM_CIC3_ENABLE
                q_cic3_shift: Q channel output shift, 0~0x29
                q_cic3_gain: Q channel gain factor, 0~0x1FFF
                q_cic3_dec: Q channel CIC filter decimation factor, 0~0x1FF
                q_cic3_val: Q channel CIC filter start value, 0~0x1FF
    \param[out] none
    \retval     none
*/
void rdcm_demodulator_config(rdcm_demodulator_parameter_struct *dem_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(dem_para)) {
        fw_debug_report_err(RDCM_MODULE_ID, API_ID(0x000BU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* I channel configuration */
        /* disable demodulator */
        RDCM_CTL &= (~RDCM_CTL_IDEMEN);

        /* disable filter */
        RDCM_DEMCFG &= (~(RDCM_DEMCFG_IFIR0EN | RDCM_DEMCFG_IFIR1EN | RDCM_DEMCFG_ICIC3EN));

        /* FIR1 decimation rate configuration */
        RDCM_DEMCFG &= (~RDCM_DEMCFG_IFIR1DEC);
        RDCM_DEMCFG |= (dem_para->i_fir1_dec & RDCM_DEMCFG_IFIR1DEC);

        /* CIC3 filter decimation rate and start value configuration */
        RDCM_CICCFG0 &= (~RDCM_CICCFG0_ICICDFAC);
        RDCM_CICCFG0 |= (dem_para->i_cic3_dec & RDCM_CICCFG0_ICICDFAC);
        RDCM_CICCFG0 &= (~RDCM_CICCFG0_ICICSVAL);
        RDCM_CICCFG0 |= ((dem_para->i_cic3_val << 16U) & RDCM_CICCFG0_ICICSVAL);

        /* CIC3 filter output shift and gain factor configuration */
        RDCM_CSGCFG0 &= (~RDCM_CSGCFG0_IGAIN);
        RDCM_CSGCFG0 |= (dem_para->i_cic3_gain & RDCM_CSGCFG0_IGAIN);
        RDCM_CSGCFG0 &= (~RDCM_CSGCFG0_ICICSHIFT);
        RDCM_CSGCFG0 |= ((dem_para->i_cic3_shift << 16U) & RDCM_CSGCFG0_ICICSHIFT);

        /* Q channel configuration */
        /* disable demodulator */
        RDCM_CTL &= (~RDCM_CTL_QDEMEN);

        /* disable filter  */
        RDCM_DEMCFG &= (~(RDCM_DEMCFG_QFIR0EN | RDCM_DEMCFG_QFIR1EN | RDCM_DEMCFG_QCIC3EN));

        /* FIR1 decimation rate configuration */
        RDCM_DEMCFG &= (~RDCM_DEMCFG_QFIR1DEC);
        RDCM_DEMCFG |= ((dem_para->q_fir1_dec << 16U) & RDCM_DEMCFG_QFIR1DEC);

        /* CIC3 filter decimation rate and start value configuration */
        RDCM_CICCFG1 &= (~RDCM_CICCFG1_QCICDFAC);
        RDCM_CICCFG1 |= (dem_para->q_cic3_dec & RDCM_CICCFG1_QCICDFAC);
        RDCM_CICCFG1 &= (~RDCM_CICCFG1_QCICSVAL);
        RDCM_CICCFG1 |= ((dem_para->q_cic3_val << 16U) & RDCM_CICCFG1_QCICSVAL);

        /* CIC3 filter output shift and gain factor configuration */
        RDCM_CSGCFG1 &= (~RDCM_CSGCFG1_QGAIN);
        RDCM_CSGCFG1 |= (dem_para->q_cic3_gain & RDCM_CSGCFG1_QGAIN);
        RDCM_CSGCFG1 &= (~RDCM_CSGCFG1_QCICSHIFT);
        RDCM_CSGCFG1 |= ((dem_para->q_cic3_shift << 16U) & RDCM_CSGCFG1_QCICSHIFT);

        /* configure demodulator and filter enable */
        RDCM_CTL |= (dem_para->i_dem_en & RDCM_CTL_IDEMEN);
        RDCM_DEMCFG |= ((dem_para->i_fir0_en & RDCM_DEMCFG_IFIR0EN) | (dem_para->i_fir1_en & RDCM_DEMCFG_IFIR1EN) |
                        (dem_para->i_cic3_en & RDCM_DEMCFG_ICIC3EN));
        RDCM_CTL |= ((dem_para->q_dem_en << 16) & RDCM_CTL_QDEMEN);
        RDCM_DEMCFG |= (((dem_para->q_fir0_en << 16U) & RDCM_DEMCFG_QFIR0EN) | ((dem_para->q_fir1_en << 16U) & RDCM_DEMCFG_QFIR1EN) |
                        ((dem_para->q_cic3_en << 16U) & RDCM_DEMCFG_QCIC3EN));
    }
}

/*!
    \brief      initialize RDCM track loop parameter struct with a default value (API_ID(0x000CU))
    \param[in]  initpara: init parameter struct
    \param[out] none
    \retval     none
*/
void rdcm_track_loop_parameter_struct_para_init(rdcm_track_loop_parameter_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(RDCM_MODULE_ID, API_ID(0x000CU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the init parameter struct member with the default value */
        initpara->trk_en                 = RDCM_TRK_DISABLE;
        initpara->npm_x                  = 0x4000U;
        initpara->npm_y                  = 0U;
        initpara->trk_gain               = 0x1394FF16U;
        initpara->position_int_gain      = 0x18U;
        initpara->velocity_int_gain      = 0x18U;
        initpara->trk_cmp_zero           = 0x3FFEU;
        initpara->trk_cmp_pole           = 0x3FE7U;
        initpara->velocity_smooth_factor = 0U;
    }
}

/*!
    \brief      configure RDCM track loop function (API_ID(0x000DU))
    \param[in]  trackloop_para: RDCM track loop parameter struct
                trk_en: RDCM_TRK_DISABLE, RDCM_TRK_ENABLE
                npm_x: Q channel nonorthogonal phase mismatch compensation factor X, 0~0xFFFF
                npm_y: Q channel nonorthogonal phase mismatch compensation factor Y, 0~0xFFFF
                trk_gain: the error acceleration gain factor, 0~0x1FFFFFF
                position_int_gain: the position gain factor of integrator, 0~0x1F
                velocity_int_gain: the velocity gain factor of integrator, 0~0x1F
                trk_cmp_zero: The zero of compensation filter, 0~0x7FFF
                trk_cmp_pole: The pole of compensation filter, 0~0x7FFF
                velocity_smooth_factor: the velocity smooth filter mode in tracking loop, 0~0xF
    \param[out] none
    \retval     none
*/
void rdcm_track_loop_config(rdcm_track_loop_parameter_struct *trackloop_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(trackloop_para)) {
        fw_debug_report_err(RDCM_MODULE_ID, API_ID(0x000DU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* disable track loop */
        RDCM_CTL &= (~RDCM_CTL_TRKEN);

        /* nonorthogonal phase mismatch compensation factor configuration */
        RDCM_NPMCFG &= (~(RDCM_NPMCFG_XFAC | RDCM_NPMCFG_YFAC));
        RDCM_NPMCFG |= ((trackloop_para->npm_x & RDCM_NPMCFG_XFAC) | ((trackloop_para->npm_y << 16U) & RDCM_NPMCFG_YFAC));

        /* track loop gain configuration */
        RDCM_TRKGAINCFG &= (~RDCM_TRKGAINCFG_TRKERRGAIN);
        RDCM_TRKGAINCFG |= (trackloop_para->trk_gain & RDCM_TRKGAINCFG_TRKERRGAIN);

        /* track loop integrator configuration */
        RDCM_TRKINTCFG &= (~(RDCM_TRKINTCFG_VINTGAIN | RDCM_TRKINTCFG_PINTGAIN));
        RDCM_TRKINTCFG |= ((trackloop_para->velocity_int_gain & RDCM_TRKINTCFG_VINTGAIN) |
                           ((trackloop_para->position_int_gain << 16U) & RDCM_TRKINTCFG_PINTGAIN));

        /* track loop compensation filter configuration */
        RDCM_TRKCMPCFG &= (~(RDCM_TRKCMPCFG_POLE | RDCM_TRKCMPCFG_ZERO));
        RDCM_TRKCMPCFG |= ((trackloop_para->trk_cmp_pole & RDCM_TRKCMPCFG_POLE) |
                           ((trackloop_para->trk_cmp_zero << 16U) & RDCM_TRKCMPCFG_ZERO));

        /* velocity smooth fiter configuration */
        RDCM_VSFCFG &= (~RDCM_VSFCFG_VSFM);
        RDCM_VSFCFG |= (trackloop_para->velocity_smooth_factor & RDCM_VSFCFG_VSFM);

        /* configure track loop enable */
        RDCM_CTL |= (trackloop_para->trk_en & RDCM_CTL_TRKEN);
    }
}

/*!
    \brief      enable RDCM (API_ID(0x000EU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_enable(void)
{
    RDCM_CS |= RDCM_CS_RDCMEN;
}

/*!
    \brief      disable RDCM (API_ID(0x000FU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_disable(void)
{
    RDCM_CS &= (~RDCM_CS_RDCMEN);
}

/*!
    \brief      enable RDCM reference frequency mixer (API_ID(0x0010U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_reference_frequency_mixer_enable(void)
{
    RDCM_CTL |= (RDCM_CTL_IRFMEN | RDCM_CTL_QRFMEN);
}

/*!
    \brief      disable RDCM reference frequency mixer (API_ID(0x0011U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_reference_frequency_mixer_disable(void)
{
    RDCM_CTL &= (~(RDCM_CTL_IRFMEN | RDCM_CTL_QRFMEN));
}

/*!
    \brief      enable RDCM demodulator (API_ID(0x0012U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_demodulator_enable(void)
{
    RDCM_CTL |= (RDCM_CTL_IDEMEN | RDCM_CTL_QDEMEN);
}

/*!
    \brief      disable RDCM demodulator (API_ID(0x0013U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_demodulator_disable(void)
{
    RDCM_CTL &= (~(RDCM_CTL_IDEMEN | RDCM_CTL_QDEMEN));
}

/*!
    \brief      enable RDCM excitor (API_ID(0x0014U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_excitor_enable(void)
{
    RDCM_CTL |= RDCM_CTL_EXCEN;
}

/*!
    \brief      disable RDCM excitor (API_ID(0x0015U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_excitor_disable(void)
{
    RDCM_CTL &= (~RDCM_CTL_EXCEN);
}

/*!
    \brief      enable RDCM track loop (API_ID(0x0016U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_track_loop_enable(void)
{
    RDCM_CTL |= RDCM_CTL_TRKEN;
}

/*!
    \brief      disable RDCM track loop (API_ID(0x0017U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_track_loop_disable(void)
{
    RDCM_CTL &= (~RDCM_CTL_TRKEN);
}

/*!
    \brief      enable RDCM DMA (API_ID(0x0018U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_dma_enable(void)
{
    RDCM_CTL |= RDCM_CTL_DMAEN;
}

/*!
    \brief      disable RDCM DMA (API_ID(0x0019U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_dma_disable(void)
{
    RDCM_CTL &= (~RDCM_CTL_DMAEN);
}

/*!
    \brief      select RDCM result data register (API_ID(0x001AU))
    \param[in]  reg_sel: result data register
                only one parameter can be selected which is shown as below:
      \arg        RDCM_RESDSEL_TRKDATA: RDCM_TRKDATA
      \arg        RDCM_RESDSEL_HFDATA : RDCM_HFDATA
      \arg        RDCM_RESDSEL_RFMDATA: RDCM_RFMDATA
      \arg        RDCM_RESDSEL_DEMDATA: RDCM_DEMDATA
      \arg        RDCM_RESDSEL_MONDATA: RDCM_MONDATA
      \arg        RDCM_RESDSEL_POSDATA: RDCM_POSDATA
      \arg        RDCM_RESDSEL_VELDATA: RDCM_VELDATA
    \param[out] none
    \retval     none
*/
void rdcm_result_data_reg_sel(uint32_t reg_sel)
{
    RDCM_CTL &= (~RDCM_CTL_RESDSEL);
    RDCM_CTL |= (reg_sel & RDCM_CTL_RESDSEL);
}

/*!
    \brief      configure RDCM DMA engine issues requests according to the RESDIF bit (API_ID(0x001BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_dma_request_after_last_enable(void)
{
    RDCM_CTL |= RDCM_CTL_DDSM;
}

/*!
    \brief      configure RDCM DMA engine is disabled after the end of transfer signal from DMA controller is detected (API_ID(0x001CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_dma_request_after_last_disable(void)
{
    RDCM_CTL &= (~RDCM_CTL_DDSM);
}

/*!
    \brief      reset the phase of all NCOs (Exciter and I/Q reference frequency mixer) to the initial setting phase (API_ID(0x001DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_excitor_rfm_phase_reset(void)
{
    RDCM_CTL |= RDCM_CTL_NCORST;
}

/*!
    \brief      reset demodulator (API_ID(0x001EU))
    \param[in]  channel: RDCM I/Q channel
                only one parameter can be selected which is shown as below:
      \arg        RDCM_CHANNEL_I: I channel
      \arg        RDCM_CHANNEL_Q: Q channel
    \param[out] none
    \retval     none
*/
void rdcm_demodulator_reset(uint32_t channel)
{
    if(RDCM_CHANNEL_I == channel) {
        RDCM_CTL |= RDCM_CTL_IDEMRST;
    } else if(RDCM_CHANNEL_Q == channel) {
        RDCM_CTL |= RDCM_CTL_QDEMRST;
    } else {

    }
}

/*!
    \brief      enable timestamp counter capture (API_ID(0x001FU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_timestamp_counter_capture_enable(void)
{
    RDCM_CTL |= RDCM_CTL_TSCAPEN;
}

/*!
    \brief      disable timestamp counter capture (API_ID(0x0020U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_timestamp_counter_capture_disable(void)
{
    RDCM_CTL &= (~RDCM_CTL_TSCAPEN);
}

/*!
    \brief      configure timestamp trigger mode (API_ID(0x0021U))
    \param[in]  mode: external trigger mode
      \arg        RDCM_TSCAPETM_DISABLE: disable trigger for timestamp counter capture
      \arg        RDCM_TSCAPETM_RISING : rising edge of external trigger for timestamp counter capture
      \arg        RDCM_TSCAPETM_FALLING: falling edge of external trigger for timestamp counter capture
      \arg        RDCM_TSCAPETM_BOTH   : rising and falling edge of external trigger for timestamp counter capture
    \param[out] none
    \retval     none
*/
void rdcm_timestamp_trigger_mode_config(uint32_t mode)
{
    RDCM_CTL &= (~RDCM_CTL_TSCAPETM);
    RDCM_CTL |= (mode & RDCM_CTL_TSCAPETM);
}

/*!
    \brief      configure timestamp counter clock (API_ID(0x0022U))
    \param[in]  clock: timestamp counter clock
      \arg        RDCM_TSCLK_DIV1: fTS = fRDCM
      \arg        RDCM_TSCLK_DIV2: fTS = fRDCM / 2
      \arg        RDCM_TSCLK_DIV4: fTS = fRDCM / 4
      \arg        RDCM_TSCLK_DIV8: fTS = fRDCM / 8
    \param[out] none
    \retval     none
*/
void rdcm_timestamp_counter_clock_config(uint32_t clock)
{
    RDCM_TSCTL &= (~RDCM_TSCTL_TSCLK);
    RDCM_TSCTL |= (clock & RDCM_TSCTL_TSCLK);
}

/*!
    \brief      enable result data fifo (API_ID(0x0023U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_result_data_fifo_enable(void)
{
    RDCM_CTL |= RDCM_CTL_FIFOEN;
}

/*!
    \brief      disable result data fifo (API_ID(0x0024U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_result_data_fifo_disable(void)
{
    RDCM_CTL &= (~RDCM_CTL_FIFOEN);
}

/*!
    \brief      configure FIFO result event (API_ID(0x0025U))
    \param[in]  event: FIFO result event
      \arg        RDCM_FIFOESEL_1VALUE: generate result data event when FIFO contains 1 value
      \arg        RDCM_FIFOESEL_2VALUE: generate result data event when FIFO contains 2 values
      \arg        RDCM_FIFOESEL_3VALUE: generate result data event when FIFO contains 3 values
      \arg        RDCM_FIFOESEL_4VALUE: generate result data event when FIFO contains 4 values
    \param[out] none
    \retval     none
*/
void rdcm_fifo_result_event_config(uint32_t event)
{
    RDCM_FIFOCS &= (~RDCM_FIFOCS_FIFOESEL);
    RDCM_FIFOCS |= (event & RDCM_FIFOCS_FIFOESEL);
}

/*!
    \brief      flush result data fifo (API_ID(0x0026U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_result_data_fifo_flush(void)
{
    RDCM_FIFOCS |= RDCM_FIFOCS_FIFOFH;
}

/*!
    \brief      enable RDCM envelope signal threshold match (API_ID(0x0027U))
    \param[in]  channel: RDCM I/Q channel
                only one parameter can be selected which is shown as below:
      \arg        RDCM_CHANNEL_I: I channel
      \arg        RDCM_CHANNEL_Q: Q channel
    \param[out] none
    \retval     none
*/
void rdcm_envelope_signal_threshold_match_enable(uint32_t channel)
{
    if(RDCM_CHANNEL_I == channel) {
        RDCM_CTL |= RDCM_CTL_IETHMEN;
    } else if(RDCM_CHANNEL_Q == channel) {
        RDCM_CTL |= RDCM_CTL_QETHMEN;
    } else {

    }
}

/*!
    \brief      disable RDCM envelope signal threshold match (API_ID(0x0028U))
    \param[in]  channel: RDCM I/Q channel
                only one parameter can be selected which is shown as below:
      \arg        RDCM_CHANNEL_I: I channel
      \arg        RDCM_CHANNEL_Q: Q channel
    \param[out] none
    \retval     none
*/
void rdcm_envelope_signal_threshold_match_disable(uint32_t channel)
{
    if(RDCM_CHANNEL_I == channel) {
        RDCM_CTL &= (~RDCM_CTL_IETHMEN);
    } else if(RDCM_CHANNEL_Q == channel) {
        RDCM_CTL &= (~RDCM_CTL_QETHMEN);
    } else {

    }
}

/*!
    \brief      enable RDCM monitor signal threshold match (API_ID(0x0029U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_monitor_signal_threshold_match_enable(void)
{
    RDCM_CTL |= RDCM_CTL_MTHMEN;
}

/*!
    \brief      disable RDCM monitor signal threshold match (API_ID(0x002AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_monitor_signal_threshold_match_disable(void)
{
    RDCM_CTL &= (~RDCM_CTL_MTHMEN);
}

/*!
    \brief      enable RDCM track error signal threshold match (API_ID(0x002BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_track_error_signal_threshold_match_enable(void)
{
    RDCM_CTL |= RDCM_CTL_TRKERRTHMEN;
}

/*!
    \brief      disable RDCM track error signal threshold match (API_ID(0x002CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_track_error_signal_threshold_match_disable(void)
{
    RDCM_CTL &= (~RDCM_CTL_TRKERRTHMEN);
}

/*!
    \brief      configure RDCM envelope signal threshold match mode (API_ID(0x002DU))
    \param[in]  i_mode: RDCM I channel threshold match mode
                only one parameter can be selected which is shown as below:
      \arg        RDCM_IETHMS_RANGE: IETHL[14:0] < I channel envelope signal value < IETHU[14:0
      \arg        RDCM_IETHMS_OUT_RANGE: I channel envelope signal value < IETHL[14:0] or IETHU[14:0] < I channel envelope signal value
      \arg        RDCM_IETHMS_GREATER: IETHL[14:0] < I channel envelope signal value
      \arg        RDCM_IETHMS_LESS: IETHL[14:0] > I channel envelope signal value
    \param[in]  q_mode: RDCM Q channel threshold match mode
                only one parameter can be selected which is shown as below:
      \arg        RDCM_QETHMS_RANGE: QETHL[14:0] < Q channel envelope signal value < QETHU[14:0
      \arg        RDCM_QETHMS_OUT_RANGE: Q channel envelope signal value < QETHL[14:0] or QETHU[14:0] < Q channel envelope signal value
      \arg        RDCM_QETHMS_GREATER: QETHL[14:0] < Q channel envelope signal value
      \arg        RDCM_QETHMS_LESS: QETHL[14:0] > Q channel envelope signal value
    \param[out] none
    \retval     none
*/
void rdcm_envelope_signal_threshold_match_mode_config(uint32_t i_mode, uint32_t q_mode)
{
    RDCM_CS &= (~(RDCM_CS_IETHMS | RDCM_CS_QETHMS));
    RDCM_CS |= ((i_mode & RDCM_CS_IETHMS) | (q_mode & RDCM_CS_QETHMS));
}

/*!
    \brief      configure RDCM monitor signal threshold match mode (API_ID(0x002EU))
    \param[in]  mode: RDCM monitor signal threshold match mode
                only one parameter can be selected which is shown as below:
      \arg       RDCM_MTHMS_RANGE: MTHL[14:0] < monitor signal value < MTHU[14:0]
      \arg       RDCM_MTHMS_OUT_RANGE: monitor signal value < MTHL[14:0] or MTHU[14:0] < monitor signal value
      \arg       RDCM_MTHMS_LESS: MTHL[14:0] > monitor signal vibration value
      \arg       RDCM_MTHMS_GREATER: MTHL[14:0] < monitor signal vibration value
    \param[out] none
    \retval     none
*/
void rdcm_monitor_signal_threshold_match_mode_config(uint32_t mode)
{
    RDCM_CS &= (~RDCM_CS_MTHMS);
    RDCM_CS |= (mode & RDCM_CS_MTHMS);
}

/*!
    \brief      configure RDCM track error signal threshold match mode (API_ID(0x002FU))
    \param[in]  mode: RDCM track error signal threshold match mode
                only one parameter can be selected which is shown as below:
      \arg       RDCM_TRKERRTHMS_RANGE: TRKERRTHL[14:0] < tracking error signal value < TRKERRTHU[14:0]
      \arg       RDCM_TRKERRTHMS_OUT_RANGE: tracking error signal value < TRKERRTHL[14:0] or TRKERRTHU[14:0] < tracking error signal value
      \arg       RDCM_TRKERRTHMS_GREATER: TRKERRTHL[14:0] < tracking error signal value
      \arg       RDCM_TRKERRTHMS_LESS: TRKERRTHL[14:0] > tracking error signal value
    \param[out] none
    \retval     none
*/
void rdcm_track_error_signal_threshold_match_mode_config(uint32_t mode)
{
    RDCM_CS &= (~RDCM_CS_TRKERRTHMS);
    RDCM_CS |= (mode & RDCM_CS_TRKERRTHMS);
}

/*!
    \brief      configure RDCM envelope signal threshold (API_ID(0x0030U))
    \param[in]  channel: RDCM I/Q channel
                only one parameter can be selected which is shown as below:
      \arg        RDCM_CHANNEL_I: I channel
      \arg        RDCM_CHANNEL_Q: Q channel
    \param[in]  upper: upper threshold, -16384 ~ 16383
    \param[in]  lower: lower threshold, -16384 ~ 16383
    \param[out] none
    \retval     none
*/
void rdcm_envelope_signal_threshold_config(uint32_t channel, int32_t upper, int32_t lower)
{
    if(RDCM_CHANNEL_I == channel) {
        RDCM_ETHCFG0 = ((((uint32_t)upper << 16U) & RDCM_ETHCFG0_IETHU) | ((uint32_t)lower & RDCM_ETHCFG0_IETHL));
    } else if(RDCM_CHANNEL_Q == channel) {
        RDCM_ETHCFG1 = ((((uint32_t)upper << 16U) & RDCM_ETHCFG1_QETHU) | ((uint32_t)lower & RDCM_ETHCFG1_QETHL));
    } else {

    }
}

/*!
    \brief      configure RDCM monitor signal threshold (API_ID(0x0031U))
    \param[in]  upper: upper threshold, -16384 ~ 16383
    \param[in]  lower: lower threshold, -16384 ~ 16383
    \param[out] none
    \retval     none
*/
void rdcm_monitor_signal_threshold_config(int32_t upper, int32_t lower)
{
    RDCM_MTHCFG = ((((uint32_t)upper << 16U) & RDCM_MTHCFG_MTHU) | ((uint32_t)lower & RDCM_MTHCFG_MTHL));
}

/*!
    \brief      configure RDCM track error signal threshold (API_ID(0x0032U))
    \param[in]  upper: upper threshold, -16384 ~ 16383
    \param[in]  lower: lower threshold, -16384 ~ 16383
    \param[out] none
    \retval     none
*/
void rdcm_track_error_signal_threshold_config(int32_t upper, int32_t lower)
{
    RDCM_TRKERRTHCFG = ((((uint32_t)upper << 16U) & RDCM_TRKERRTHCFG_TRKERRTHU) | ((uint32_t)lower & RDCM_TRKERRTHCFG_TRKERRTHL));
}

/*!
    \brief      configure RDCM track error signal threshold match counter value (API_ID(0x0033U))
    \param[in]  cnt: the tracking error signal threshold match counter value, 0~0x3FFF
    \param[out] none
    \retval     none
*/
void rdcm_track_error_signal_threshold_match_counter_config(uint32_t cnt)
{
    RDCM_THCNT &= (~RDCM_THCNT_TRKERRTHCNT);
    RDCM_THCNT |= (cnt & RDCM_THCNT_TRKERRTHCNT);
}

/*!
    \brief      configure RDCM monitor signal threshold match counter value (API_ID(0x0034U))
    \param[in]  cnt: the monitor signal threshold match counter value, 0~0x3FFF
    \param[out] none
    \retval     none
*/
void rdcm_monitor_signal_threshold_match_counter_config(uint32_t cnt)
{
    RDCM_THCNT &= (~RDCM_THCNT_MTHCNT);
    RDCM_THCNT |= ((cnt << 16U) & RDCM_THCNT_MTHCNT);
}

/*!
    \brief      enable RDCM dma overflow detection (API_ID(0x0035U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_dma_overflow_detection_enable(void)
{
    RDCM_CTL |= RDCM_CTL_OVDEN;
}

/*!
    \brief      disable RDCM dma overflow detection (API_ID(0x0036U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rdcm_dma_overflow_detection_disable(void)
{
    RDCM_CTL &= (~RDCM_CTL_OVDEN);
}

/*!
    \brief      configure gate signal (timestamp trigger) valid level (API_ID(0x0037U))
    \param[in]  level: gate signal valid level
                only one parameter can be selected which is shown as below:
      \arg        RDCM_GATEVSEL_ALWAYS_VALID: always valid
      \arg        RDCM_GATEVSEL_HIGH_VALID: valid level is high
      \arg        RDCM_GATEVSEL_LOW_VALID: valid level is low
    \param[out] none
    \retval     none
*/
void rdcm_gate_signal_valid_level_config(uint32_t level)
{
    RDCM_CS &= (~RDCM_CS_GATEVSEL);
    RDCM_CS |= (level & RDCM_CS_GATEVSEL);
}

/*!
    \brief      configure I/Q channel data offset (API_ID(0x0038U))
    \param[in]  channel: RDCM I/Q channel
                only one parameter can be selected which is shown as below:
      \arg        RDCM_CHANNEL_I: I channel
      \arg        RDCM_CHANNEL_Q: Q channel
    \param[in]  offset: I/Q channel offset, -16384 ~ 16383
    \param[out] none
    \retval     none
*/
void rdcm_channel_data_offset_config(uint32_t channel, int32_t offset)
{
    if(RDCM_CHANNEL_I == channel) {
        RDCM_HFCFG0 &= (~RDCM_HFCFG0_IOFFSET);
        RDCM_HFCFG0 |= ((uint32_t)offset & RDCM_HFCFG0_IOFFSET);
    } else if(RDCM_CHANNEL_Q == channel) {
        RDCM_HFCFG1 &= (~RDCM_HFCFG1_QOFFSET);
        RDCM_HFCFG1 |= ((uint32_t)offset & RDCM_HFCFG1_QOFFSET);
    } else {

    }
}

/*!
    \brief      read I/Q channel CIC3 decimation counter (API_ID(0x0039U))
    \param[in]  channel: RDCM I/Q channel
                only one parameter can be selected which is shown as below:
      \arg        RDCM_CHANNEL_I: I channel
      \arg        RDCM_CHANNEL_Q: Q channel
    \param[out] none
    \retval     I/Q CIC3 decimation counter value: 0~0x1FF
*/
uint16_t rdcm_cic3_decimation_counter_read(uint32_t channel)
{
    uint16_t reval = 0U;
    if(RDCM_CHANNEL_I == channel) {
        reval = (uint16_t)(RDCM_CDCNT & RDCM_CDCNT_ICICDCNT);
    } else if(RDCM_CHANNEL_Q == channel) {
        reval = (uint16_t)((RDCM_CDCNT & RDCM_CDCNT_QCICDCNT) >> 16U);
    } else {

    }
    return reval;
}

/*!
    \brief      read I/Q channel high pass filter data (API_ID(0x003AU))
    \param[in]  channel: RDCM I/Q channel
                only one parameter can be selected which is shown as below:
      \arg        RDCM_CHANNEL_I: I channel
      \arg        RDCM_CHANNEL_Q: Q channel
    \param[out] none
    \retval     I/Q high pass filter output data: -32768 ~ 32767
*/
int16_t rdcm_high_pass_filter_data_read(uint32_t channel)
{
    int16_t reval = 0;
    if(RDCM_CHANNEL_I == channel) {
        reval = (int16_t)((uint16_t)(RDCM_HFDATA & RDCM_HFDATA_IHFDATA));
    } else if(RDCM_CHANNEL_Q == channel) {
        reval = (int16_t)((uint16_t)((RDCM_HFDATA & RDCM_HFDATA_QHFDATA) >> 16U));
    } else {

    }
    return reval;
}

/*!
    \brief      read I/Q channel reference frequency mixer data (API_ID(0x003BU))
    \param[in]  channel: RDCM I/Q channel
                only one parameter can be selected which is shown as below:
      \arg        RDCM_CHANNEL_I: I channel
      \arg        RDCM_CHANNEL_Q: Q channel
    \param[out] none
    \retval     I/Q channel reference frequency mixer output data: -32768 ~ 32767
*/
int16_t rdcm_reference_frequency_mixer_data_read(uint32_t channel)
{
    int16_t reval = 0;
    if(RDCM_CHANNEL_I == channel) {
        reval = (int16_t)((uint16_t)(RDCM_RFMDATA & RDCM_RFMDATA_IRFMDATA));
    } else if(RDCM_CHANNEL_Q == channel) {
        reval = (int16_t)((uint16_t)((RDCM_RFMDATA & RDCM_RFMDATA_QRFMDATA) >> 16U));
    } else {

    }
    return reval;
}

/*!
    \brief      read I/Q channel demodulator data (API_ID(0x003CU))
    \param[in]  channel: RDCM I/Q channel
                only one parameter can be selected which is shown as below:
      \arg        RDCM_CHANNEL_I: I channel
      \arg        RDCM_CHANNEL_Q: Q channel
    \param[out] none
    \retval     I/Q channel demodulator output data: -32768 ~ 32767
*/
int16_t rdcm_demodulator_data_read(uint32_t channel)
{
    int16_t reval = 0;
    if(RDCM_CHANNEL_I == channel) {
        reval = (int16_t)((uint16_t)(RDCM_DEMDATA & RDCM_DEMDATA_IDEMDATA));
    } else if(RDCM_CHANNEL_Q == channel) {
        reval = (int16_t)((uint16_t)((RDCM_DEMDATA & RDCM_DEMDATA_QDEMDATA) >> 16U));
    } else {

    }
    return reval;
}

/*!
    \brief      read track loop velocity data (API_ID(0x003DU))
    \param[in]  none
    \param[out] none
    \retval     track loop velocity data: -32768 ~ 32767
*/
int16_t rdcm_track_velocity_data_read(void)
{
    int16_t reval = 0;
    reval = (int16_t)((uint16_t)(RDCM_TRKDATA & RDCM_TRKDATA_VELOCITY));
    return reval;
}

/*!
    \brief      read track loop position data (API_ID(0x003EU))
    \param[in]  none
    \param[out] none
    \retval     track loop position data: -32768 ~ 32767
*/
int16_t rdcm_track_position_data_read(void)
{
    int16_t reval = 0;
    reval = (int16_t)((uint16_t)((RDCM_TRKDATA & RDCM_TRKDATA_POSITION) >> 16U));
    return reval;
}

/*!
    \brief      read track error signal data (API_ID(0x003FU))
    \param[in]  none
    \param[out] none
    \retval     track error signal data: -32768 ~ 32767
*/
int16_t rdcm_track_error_signal_data_read(void)
{
    int16_t reval = 0;
    reval = (int16_t)((uint16_t)(RDCM_MONDATA & RDCM_MONDATA_TRKERRDATA));
    return reval;
}

/*!
    \brief      read monitor signal data (API_ID(0x0040U))
    \param[in]  none
    \param[out] none
    \retval     monitor signal data: -32768 ~ 32767
*/
int16_t rdcm_monitor_signal_data_read(void)
{
    int16_t reval = 0;
    reval = (int16_t)((uint16_t)((RDCM_MONDATA & RDCM_MONDATA_MONDATA) >> 16U));
    return reval;
}

/*!
    \brief      read timestamp counter value (API_ID(0x0041U))
    \param[in]  none
    \param[out] none
    \retval     timestamp counter value: 0~0xFFFF
*/
uint16_t rdcm_timestamp_counter_value_read(void)
{
    uint16_t reval = 0U;
    reval = (uint16_t)(RDCM_TSCTL & RDCM_TSCTL_TSCNT);
    return reval;
}

/*!
    \brief      read the most recent captured timestamp value (API_ID(0x0042U))
    \param[in]  none
    \param[out] none
    \retval     the most recent captured timestamp value: 0~0xFFFF
*/
uint16_t rdcm_timestamp_capture_value_read(void)
{
    uint16_t reval = 0U;
    reval = (uint16_t)(RDCM_TSDATA & RDCM_TSDATA_TSVAL);
    return reval;
}

/*!
    \brief      read FIFO valid data number (API_ID(0x0043U))
    \param[in]  none
    \param[out] none
    \retval     FIFO valid data number: 0~0x04
*/
uint8_t rdcm_fifo_valid_num_read(void)
{
    uint8_t reval = 0U;
    reval = (uint8_t)((RDCM_FIFOCS & RDCM_FIFOCS_FIFONUM) >> 16U);
    return reval;
}

/*!
    \brief      read FIFO data (API_ID(0x0044U))
    \param[in]  none
    \param[out] none
    \retval     FIFO data: 0~0xFFFFFFFF
*/
uint32_t rdcm_fifo_data_read(void)
{
    return RDCM_FIFODATA;
}

/*!
    \brief      configure simulation I/Q channel data (API_ID(0x0045U))
    \param[in]  i_data: I channel simulation data, 0~0x3FFF
    \param[in]  q_data: Q channel simulation data, 0~0x3FFF
    \param[out] none
    \retval     none
*/
void rdcm_simulation_data_config(uint32_t i_data, uint32_t q_data)
{
    RDCM_SIMDI = ((i_data & RDCM_SIMDI_ISIMDI) | ((q_data << 16U) & RDCM_SIMDI_QSIMDI));
}

/*!
    \brief      configure reference frequency mixer sign data input source (API_ID(0x0046U))
    \param[in]  i_source: I channel RDCM frequency mixer reference sign source
                only one parameter can be selected which is shown as below:
      \arg        RDCM_ISIGNSEL_INTERNAL: use on-chip excitor sign as I channel RDCM frequency mixer reference
      \arg        RDCM_ISIGNSEL_EXTERNAL: use external excitor sign signal pin input as I channel RDCM frequency mixer reference
    \param[in]  q_source: Q channel RDCM frequency mixer reference sign source
                only one parameter can be selected which is shown as below:
      \arg        RDCM_QSIGNSEL_INTERNAL: use on-chip excitor sign as Q channel RDCM frequency mixer reference
      \arg        RDCM_QSIGNSEL_EXTERNAL: use external excitor sign signal pin input as Q channel RDCM frequency mixer reference
    \param[out] none
    \retval     none
*/
void rdcm_rfm_sign_input_source_config(uint32_t i_source, uint32_t q_source)
{
    RDCM_DISWSEL &= (~(RDCM_DISWSEL_ISIGNSEL | RDCM_DISWSEL_QSIGNSEL));
    RDCM_DISWSEL |= (i_source & RDCM_DISWSEL_ISIGNSEL);
    RDCM_DISWSEL |= (q_source & RDCM_DISWSEL_QSIGNSEL);
}

/*!
    \brief      configure channel data input source (API_ID(0x0047U))
    \param[in]  source: I/Q channel data input source
                only one parameter can be selected which is shown as below:
      \arg        RDCM_DISEL_ADC: RDCM I/Q channel calculation use ADC conversion data
      \arg        RDCM_DISEL_SIMULATION: RDCM I/Q channel calculation use ISIMDI[13:0] and QSIMDI[13:0]
    \param[out] none
    \retval     none
*/
void rdcm_channel_data_input_source_config(uint32_t source)
{
    RDCM_DISWSEL &= (~RDCM_DISWSEL_DISEL);
    RDCM_DISWSEL |= (source & RDCM_DISWSEL_DISEL);
}

/*!
    \brief      read position data (API_ID(0x0048U))
    \param[in]  none
    \param[out] none
    \retval     position data: -32768 ~ 32767
*/
int16_t rdcm_position_read(void)
{
    return (int16_t)RDCM_POSDATA;
}

/*!
    \brief      read velocity data (API_ID(0x0049U))
    \param[in]  none
    \param[out] none
    \retval     velocity data: -32768 ~ 32767
*/
int16_t rdcm_velocity_read(void)
{
    return (int16_t)RDCM_VELDATA;
}

/*!
    \brief      enable RDCM interrupt (API_ID(0x004AU))
    \param[in]  interrupt: RDCM interrupt
                one or more parameter can be selected which is shown as below:
      \arg        RDCM_INT_TRKERRTHM: Track error signal threshold match interrupt enable
      \arg        RDCM_INT_MTH: Monitor signal threshold match interrupt enable
      \arg        RDCM_INT_QETHM: Q channel envelope signal threshold match interrupt enable
      \arg        RDCM_INT_IETHM: I channel envelope signal threshold match interrupt enable
      \arg        RDCM_INT_QZCD: Q channel zero crossing detection valid interrupt enable
      \arg        RDCM_INT_IZCD: I channel zero crossing detection valid interrupt enable
      \arg        RDCM_INT_TSCAP: Timestamp counter capture valid interrupt enable
      \arg        RDCM_INT_DMAOV: RDC-DMA transfer overflow interrupt enable
      \arg        RDCM_INT_RESDATA: Result valid (Result update or result fifo level) interrupt enable
    \param[out] none
    \retval     none
*/
void rdcm_interrupt_enable(uint32_t interrupt)
{
    RDCM_CS |= (interrupt & RDCM_INTEN_MASK);
}

/*!
    \brief      disable RDCM interrupt (API_ID(0x004BU))
    \param[in]  interrupt: RDCM interrupt
                one or more parameter can be selected which is shown as below:
      \arg        RDCM_INT_TRKERRTHM: Track error signal threshold match interrupt enable
      \arg        RDCM_INT_MTH: Monitor signal threshold match interrupt enable
      \arg        RDCM_INT_QETHM: Q channel envelope signal threshold match interrupt enable
      \arg        RDCM_INT_IETHM: I channel envelope signal threshold match interrupt enable
      \arg        RDCM_INT_QZCD: Q channel zero crossing detection valid interrupt enable
      \arg        RDCM_INT_IZCD: I channel zero crossing detection valid interrupt enable
      \arg        RDCM_INT_TSCAP: Timestamp counter capture valid interrupt enable
      \arg        RDCM_INT_DMAOV: RDC-DMA transfer overflow interrupt enable
      \arg        RDCM_INT_RESDATA: Result valid (Result update or result fifo level) interrupt enable
    \param[out] none
    \retval     none
*/
void rdcm_interrupt_disable(uint32_t interrupt)
{
    RDCM_CS &= (~(interrupt & RDCM_INTEN_MASK));
}

/*!
    \brief      get RDCM interrupt flag (API_ID(0x004CU))
    \param[in]  flag: the RDCM interrupt flag bits
                only one parameter can be selected which is shown as below:
      \arg        RDCM_INT_FLAG_TRKERRTHM: Track error signal threshold match interrupt flag
      \arg        RDCM_INT_FLAG_MTH: Monitor signal threshold match interrupt flag
      \arg        RDCM_INT_FLAG_QETHM: Q channel envelope signal threshold match interrupt flag
      \arg        RDCM_INT_FLAG_IETHM: I channel envelope signal threshold match interrupt flag
      \arg        RDCM_INT_FLAG_QZCD: Q channel zero crossing detection interrupt flag
      \arg        RDCM_INT_FLAG_IZCD: I channel zero crossing detection interrupt flag
      \arg        RDCM_INT_FLAG_TSCAP: Timestamp counter capture interrupt flag
      \arg        RDCM_INT_FLAG_DMAOV: DMA transfer data register overflow interrupt flag
      \arg        RDCM_INT_FLAG_RESDATA: Result data interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
    \Note       After the interrupt enable bit is cleared, if the hardware flag remains set, this API will still return RESET.
                Therefore, in an ISR or during the interrupt-disable flow, this API alone must not be relied upon to determine whether the flag should be cleared.
                The corresponding flag must be cleared according to the module-specific rules, and the NVIC-pending bit should also be cleared when necessary.
*/
FlagStatus rdcm_interrupt_flag_get(uint32_t flag)
{
    uint32_t val;
    FlagStatus retval;
    val = (RDCM_CS & flag);
    if((RESET != (RDCM_CS & (flag >> 16U))) && (RESET != val)) {
        retval = SET;
    } else {
        retval = RESET;
    }
    return retval;
}

/*!
    \brief      clear RDCM interrupt flag (API_ID(0x004DU))
    \param[in]  flag: the RDCM interrupt flag bits
                only one parameter can be selected which is shown as below:
      \arg        RDCM_INT_FLAG_TRKERRTHM: Track error signal threshold match interrupt flag
      \arg        RDCM_INT_FLAG_MTH: Monitor signal threshold match interrupt flag
      \arg        RDCM_INT_FLAG_QETHM: Q channel envelope signal threshold match interrupt flag
      \arg        RDCM_INT_FLAG_IETHM: I channel envelope signal threshold match interrupt flag
      \arg        RDCM_INT_FLAG_QZCD: Q channel zero crossing detection interrupt flag
      \arg        RDCM_INT_FLAG_IZCD: I channel zero crossing detection interrupt flag
      \arg        RDCM_INT_FLAG_TSCAP: Timestamp counter capture interrupt flag
      \arg        RDCM_INT_FLAG_DMAOV: DMA transfer data register overflow interrupt flag
      \arg        RDCM_INT_FLAG_RESDATA: Result data interrupt flag
    \param[out] none
    \retval     none
*/
void rdcm_interrupt_flag_clear(uint32_t flag)
{
    RDCM_CS &= (~(flag & RDCM_INT_FLAG_MASK));
}

/*!
    \brief      get RDCM flag (API_ID(0x004EU))
    \param[in]  flag: the RDCM flag bits
                only one parameter can be selected which is shown as below:
      \arg        RDCM_FLAG_TRKERRTHM: Track error signal threshold match interrupt flag
      \arg        RDCM_FLAG_MTH: Monitor signal threshold match interrupt flag
      \arg        RDCM_FLAG_QETHM: Q channel envelope signal threshold match interrupt flag
      \arg        RDCM_FLAG_IETHM: I channel envelope signal threshold match interrupt flag
      \arg        RDCM_FLAG_QZCD: Q channel zero crossing detection interrupt flag
      \arg        RDCM_FLAG_IZCD: I channel zero crossing detection interrupt flag
      \arg        RDCM_FLAG_TSCAP: Timestamp counter capture interrupt flag
      \arg        RDCM_FLAG_DMAOV: DMA transfer data register overflow interrupt flag
      \arg        RDCM_FLAG_RESDATA: Result data interrupt flag
      \arg        RDCM_FLAG_TSTRG: timestamp trigger flag
      \arg        RDCM_FLAG_RERR: FIFO read error flag
      \arg        RDCM_FLAG_WERR: FIFO write error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
    \Note       If the TSDATA register has been read previously, reading the TSTRGF flag will return RESET.
*/
FlagStatus rdcm_flag_get(rdcm_flag_enum flag)
{
    uint32_t val;
    FlagStatus reval = RESET;
    val = (RDCM_REG_VAL(flag) & BIT(RDCM_BIT_POS(flag)));
    if(RESET != val) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      clear RDCM flag (API_ID(0x004FU))
    \param[in]  flag: the RDCM flag bits
                only one parameter can be selected which is shown as below:
      \arg        RDCM_FLAG_TRKERRTHM: Track error signal threshold match interrupt flag
      \arg        RDCM_FLAG_MTH: Monitor signal threshold match interrupt flag
      \arg        RDCM_FLAG_QETHM: Q channel envelope signal threshold match interrupt flag
      \arg        RDCM_FLAG_IETHM: I channel envelope signal threshold match interrupt flag
      \arg        RDCM_FLAG_QZCD: Q channel zero crossing detection interrupt flag
      \arg        RDCM_FLAG_IZCD: I channel zero crossing detection interrupt flag
      \arg        RDCM_FLAG_TSCAP: Timestamp counter capture interrupt flag
      \arg        RDCM_FLAG_DMAOV: DMA transfer data register overflow interrupt flag
      \arg        RDCM_FLAG_RESDATA: Result data interrupt flag
      \arg        RDCM_FLAG_TSTRG: timestamp trigger flag
      \arg        RDCM_FLAG_RERR: FIFO read error flag
      \arg        RDCM_FLAG_WERR: FIFO write error flag
    \param[out] none
    \retval     none
*/
void rdcm_flag_clear(rdcm_flag_enum flag)
{
    RDCM_REG_VAL(flag) &= (~(BIT(RDCM_BIT_POS(flag))));
}
