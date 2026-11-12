/*!
    \file    gd32h77x_78x_adc.c
    \brief   ADC driver

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

#include "gd32h77x_78x_adc.h"

/* discontinuous mode macro */
#define ADC_CHANNEL_LENGTH_SUBTRACT_ONE            ((uint8_t)1U)

/* ADC routine channel macro */
#define ADC_ROUTINE_CHANNEL_RANK_ONE               ((uint8_t)1U)
#define ADC_ROUTINE_CHANNEL_RANK_THREE             ((uint8_t)3U)
#define ADC_ROUTINE_CHANNEL_RANK_FIVE              ((uint8_t)5U)
#define ADC_ROUTINE_CHANNEL_RANK_SEVEN             ((uint8_t)7U)
#define ADC_ROUTINE_CHANNEL_RANK_NINE              ((uint8_t)9U)
#define ADC_ROUTINE_CHANNEL_RANK_ELEVEN            ((uint8_t)11U)
#define ADC_ROUTINE_CHANNEL_RANK_THIRTEEN          ((uint8_t)13U)
#define ADC_ROUTINE_CHANNEL_RANK_FIFTEEN           ((uint8_t)15U)
#define ADC_ROUTINE_CHANNEL_RANK_SIXTEEN           ((uint8_t)16U)
#define ADC_ROUTINE_CHANNEL_SHIFT_LENGTH           ((uint8_t)16U)

/* ADC inserted channel macro */
#define ADC_INSERTED_CHANNEL_RANK_ONE              ((uint8_t)1U)
#define ADC_INSERTED_CHANNEL_RANK_THREE            ((uint8_t)3U)
#define ADC_INSERTED_CHANNEL_RANK_FOUR             ((uint8_t)4U)
#define ADC_INSERTED_CHANNEL_SHIFT_LENGTH          ((uint8_t)16U)

/* ADC inserted channel offset macro */
#define ADC_OFFSET_LENGTH                          ((uint8_t)3U)
#define ADC_OFFSET_SHIFT_LENGTH                    ((uint8_t)4U)

/* ADC IOFF0 reg offset address macro */
#define ADC_IOFF0_OFFSET                           ((uint32_t)0x0000000CU)

/* ADC init parameter mask */
#define ADC_CHANNEL_INTERNAL_MASK                  ((uint32_t)0x82800000U)
#define ADC_LATCH_DATA_MASK                        ((uint32_t)0x00000003U)
#define ADC_FLAG_MASK                              ((uint32_t)0xC000007FU)
#define ADC_INT_MASK                               ((uint32_t)0xCC0000E0U)
#define ADC_INT_FLAG_MASK                          ((uint32_t)0xC0000067U)

/*!
    \brief      reset ADC (API_ID(0x0001U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_deinit(uint32_t adc_periph)
{
    switch(adc_periph) {
    case ADC0:
        rcu_periph_reset_enable(RCU_ADC0RST);
        rcu_periph_reset_disable(RCU_ADC0RST);
        break;
    case ADC1:
        rcu_periph_reset_enable(RCU_ADC1RST);
        rcu_periph_reset_disable(RCU_ADC1RST);
        break;
    case ADC2:
        rcu_periph_reset_enable(RCU_ADC2RST);
        rcu_periph_reset_disable(RCU_ADC2RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      configure the ADC clock (API_ID(0x0002U))
    \param[in]  adc_periph: ADCx, x=0,2
    \param[in]  prescaler: configure ADCs prescaler ratio
                only one parameter can be selected which is shown as below:
      \arg        ADC_CLK_SYNC_HCLK_DIV2: ADC sync clock mode HCLK div2
      \arg        ADC_CLK_SYNC_HCLK_DIV4: ADC sync clock mode HCLK div4
      \arg        ADC_CLK_SYNC_HCLK_DIV6: ADC sync clock mode HCLK div6
      \arg        ADC_CLK_SYNC_HCLK_DIV8: ADC sync clock mode HCLK div8
      \arg        ADC_CLK_SYNC_HCLK_DIV10: ADC sync clock mode HCLK div10
      \arg        ADC_CLK_SYNC_HCLK_DIV12: ADC sync clock mode HCLK div12
      \arg        ADC_CLK_SYNC_HCLK_DIV14: ADC sync clock mode HCLK div14
      \arg        ADC_CLK_SYNC_HCLK_DIV16: ADC sync clock mode HCLK div16
      \arg        ADC_CLK_ASYNC_DIV1: ADC async clock mode div1
      \arg        ADC_CLK_ASYNC_DIV2: ADC async clock mode div2
      \arg        ADC_CLK_ASYNC_DIV4: ADC async clock mode div4
      \arg        ADC_CLK_ASYNC_DIV6: ADC async clock mode div6
      \arg        ADC_CLK_ASYNC_DIV8: ADC async clock mode div8
      \arg        ADC_CLK_ASYNC_DIV10: ADC async clock mode div10
      \arg        ADC_CLK_ASYNC_DIV12: ADC async clock mode div12
      \arg        ADC_CLK_ASYNC_DIV16: ADC async clock mode div16
      \arg        ADC_CLK_ASYNC_DIV32: ADC async clock mode div32
      \arg        ADC_CLK_ASYNC_DIV64: ADC async clock mode div64
      \arg        ADC_CLK_ASYNC_DIV128: ADC async clock mode div128
      \arg        ADC_CLK_ASYNC_DIV256: ADC async clock mode div256
    \param[out] none
    \retval     none
*/
void adc_clock_config(uint32_t adc_periph, uint32_t prescaler)
{
    if(ADC2 == adc_periph) {
        ADC_SYNCCTL(ADC2) &= ~((uint32_t)(ADC_SYNCCTL_ADCCK | ADC_SYNCCTL_ADCSCK));
        ADC_SYNCCTL(ADC2) |= (uint32_t)(prescaler & (ADC_SYNCCTL_ADCCK | ADC_SYNCCTL_ADCSCK));
    } else {
        if(0U == (RCU_APB2EN & RCU_APB2EN_ADC0EN)){
            rcu_periph_clock_enable(RCU_ADC0);
        }else{
            /* illegal parameters */
        }
        ADC_SYNCCTL(ADC0) &= ~((uint32_t)(ADC_SYNCCTL_ADCCK | ADC_SYNCCTL_ADCSCK));
        ADC_SYNCCTL(ADC0) |= (uint32_t)(prescaler & (ADC_SYNCCTL_ADCCK | ADC_SYNCCTL_ADCSCK));
    }
}

/*!
    \brief      enable or disable ADC special function (API_ID(0x0003U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  function: the function to config
                one or more parameters can be selected which is shown as below:
      \arg        ADC_SCAN_MODE: scan mode select
      \arg        ADC_INSERTED_CHANNEL_AUTO: inserted sequence convert automatically
      \arg        ADC_CONTINUOUS_MODE: continuous mode select
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_special_function_config(uint32_t adc_periph, uint32_t function, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        if(RESET != (function & ADC_SCAN_MODE)) {
            /* enable scan mode */
            ADC_CTL0(adc_periph) |= (uint32_t)ADC_SCAN_MODE;
        }
        if(RESET != (function & ADC_INSERTED_CHANNEL_AUTO)) {
            /* enable inserted sequence convert automatically */
            ADC_CTL0(adc_periph) |= (uint32_t)ADC_INSERTED_CHANNEL_AUTO;
        }
        if(RESET != (function & ADC_CONTINUOUS_MODE)) {
            /* enable continuous mode */
            ADC_CTL1(adc_periph) |= (uint32_t)ADC_CONTINUOUS_MODE;
        }
    } else {
        if(RESET != (function & ADC_SCAN_MODE)) {
            /* disable scan mode */
            ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_SCAN_MODE);
        }
        if(RESET != (function & ADC_INSERTED_CHANNEL_AUTO)) {
            /* disable inserted sequence convert automatically */
            ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_INSERTED_CHANNEL_AUTO);
        }
        if(RESET != (function & ADC_CONTINUOUS_MODE)) {
            /* disable continuous mode */
            ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CONTINUOUS_MODE);
        }
    }
}

/*!
    \brief      configure ADC data alignment (API_ID(0x0004U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  data_alignment: data alignment select
                only one parameter can be selected which is shown as below:
      \arg        ADC_DATAALIGN_RIGHT: LSB alignment
      \arg        ADC_DATAALIGN_LEFT: MSB alignment
    \param[out] none
    \retval     none
*/
void adc_data_alignment_config(uint32_t adc_periph, uint32_t data_alignment)
{
    if(ADC_DATAALIGN_RIGHT == data_alignment) {
        /* LSB alignment */
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_DAL);
    } else if(ADC_DATAALIGN_LEFT == data_alignment) {
        /* MSB alignment */
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_DAL;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      enable ADC interface (API_ID(0x0005U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_enable(uint32_t adc_periph)
{
    if(RESET == (ADC_CTL1(adc_periph) & ADC_CTL1_ADCON)) {
        /* enable ADC */
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_ADCON;
    }
}

/*!
    \brief      disable ADC interface (API_ID(0x0006U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_disable(uint32_t adc_periph)
{
    /* disable ADC */
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ADCON);
}

/*!
    \brief      configure ADC calibration number (API_ID(0x0007U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  clb_num: calibration number
                only one parameter can be selected which is shown as below:
      \arg        ADC_CALIBRATION_NUM1: calibrate once
      \arg        ADC_CALIBRATION_NUM3: calibrate 3 times
      \arg        ADC_CALIBRATION_NUM7: calibrate 7 times
      \arg        ADC_CALIBRATION_NUM15: calibrate 15 times
      \arg        ADC_CALIBRATION_NUM31: calibrate 31 times, only supported in 14bit-ADC
    \param[out] none
    \retval     none
*/
void adc_calibration_number(uint32_t adc_periph, uint32_t clb_num)
{
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_CALNUM);
    ADC_CTL1(adc_periph) |= (uint32_t)(clb_num & ADC_CTL1_CALNUM);
}

/*!
    \brief      ADC calibration and reset calibration (API_ID(0x0008U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
void adc_calibration_enable(uint32_t adc_periph)
{
    /* reset the selected ADC calibration registers */
    ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_RSTCLB;
    /* check the RSTCLB bit state */
    while(RESET != (ADC_CTL1(adc_periph) & ADC_CTL1_RSTCLB)) {
    }
    /* enable ADC calibration process */
    ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_CLB;
    /* check the CLB bit state */
    while(RESET != (ADC_CTL1(adc_periph) & ADC_CTL1_CLB)) {
    }
}

/*!
    \brief      configure ADC resolution (API_ID(0x0009U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  resolution: ADC resolution
                only one parameter can be selected which is shown as below:
      \arg        ADC_RESOLUTION_14B: 14-bit ADC resolution, only supported in 14bit-ADC
      \arg        ADC_RESOLUTION_12B: 12-bit ADC resolution
      \arg        ADC_RESOLUTION_10B: 10-bit ADC resolution
      \arg        ADC_RESOLUTION_8B: 8-bit ADC resolution
      \arg        ADC_RESOLUTION_6B: 6-bit ADC resolution, only supported in 12bit-ADC
    \param[out] none
    \retval     none
*/
void adc_resolution_config(uint32_t adc_periph, uint32_t resolution)
{
    if(ADC2 == adc_periph) {
        if(ADC_RESOLUTION_14B == resolution) {
            /* illegal parameters */
        } else {
            ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_DRES);
            ADC_CTL0(adc_periph) |= (uint32_t)CTL0_DRES(resolution - 1U);
        }
    } else {
        if(ADC_RESOLUTION_6B == resolution) {
            /* illegal parameters */
        } else {
            ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_DRES);
            ADC_CTL0(adc_periph) |= (uint32_t)CTL0_DRES(resolution);
        }
    }
}

/*!
    \brief      enable or disable ADC internal channels (API_ID(0x000AU))
    \param[in]  adc_periph: ADCx, x=2
    \param[in]  internal_channel: the internal channels
                one or more parameters can be selected which is shown as below:
      \arg        ADC_CHANNEL_INTERNAL_TEMPSENSOR: temperature sensor channel
      \arg        ADC_CHANNEL_INTERNAL_VBAT: vbat channel
      \arg        ADC_CHANNEL_INTERNAL_HP_TEMPSENSOR: high-precision temperature sensor channel
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_internal_channel_config(uint32_t adc_periph, uint32_t internal_channel, ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        ADC_CTL1(adc_periph) |= (uint32_t)(internal_channel & ADC_CHANNEL_INTERNAL_MASK);
    } else {
        ADC_CTL1(adc_periph) &= ~((uint32_t)(internal_channel & ADC_CHANNEL_INTERNAL_MASK));
    }
}

/*!
    \brief      enable routine or inserted channel DMA request (API_ID(0x000BU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[out] none
    \retval     none
*/
void adc_dma_mode_enable(uint32_t adc_periph, uint8_t adc_sequence)
{
    /* enable routine channel DMA request */
    if(RESET != (adc_sequence & ADC_ROUTINE_CHANNEL)) {
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_RDMA;
    }
    /* enable inserted channel DMA request */
    if(RESET != (adc_sequence & ADC_INSERTED_CHANNEL)) {
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_IDMA;
    }
}

/*!
    \brief      disable routine or inserted channel DMA request (API_ID(0x000CU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[out] none
    \retval     none
*/
void adc_dma_mode_disable(uint32_t adc_periph, uint8_t adc_sequence)
{
    /* disable routine channel DMA request */
    if(RESET != (adc_sequence & ADC_ROUTINE_CHANNEL)) {
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_RDMA);
    }
    /* disable inserted channel DMA request */
    if(RESET != (adc_sequence & ADC_INSERTED_CHANNEL)) {
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_IDMA);
    }
}

/*!
    \brief      when DMA=1, the DMA engine issues a request at end of each routine or inserted conversion (API_ID(0x000DU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[out] none
    \retval     none
*/
void adc_dma_request_after_last_enable(uint32_t adc_periph, uint8_t adc_sequence)
{
    /* enable routine channel DMA engine issues a request at end of each sequence conversion */
    if(RESET != (adc_sequence & ADC_ROUTINE_CHANNEL)) {
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_RDDM;
    }
    /* enable inserted channel DMA engine issues a request at end of each sequence conversion */
    if(RESET != (adc_sequence & ADC_INSERTED_CHANNEL)) {
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_IDDM;
    }
}

/*!
    \brief      the DMA engine is disabled after the end of transfer signal from DMA controller is detected (API_ID(0x000EU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[out] none
    \retval     none
*/
void adc_dma_request_after_last_disable(uint32_t adc_periph, uint8_t adc_sequence)
{
    /* disable routine channel DMA engine issues a request at end of each sequence conversion */
    if(RESET != (adc_sequence & ADC_ROUTINE_CHANNEL)) {
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_RDDM);
    }
    /* disable inserted channel DMA engine issues a request at end of each sequence conversion */
    if(RESET != (adc_sequence & ADC_INSERTED_CHANNEL)) {
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_IDDM);
    }
}

/*!
    \brief      enable hpdf mode (API_ID(0x000FU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_hpdf_mode_enable(uint32_t adc_periph)
{
    /* enable hpdf mode */
    ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_HPDFCFG;
}

/*!
    \brief      disable hpdf mode (API_ID(0x0010U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_hpdf_mode_disable(uint32_t adc_periph)
{
    /* disable hpdf mode */
    ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_HPDFCFG);
}

/*!
    \brief      configure ADC discontinuous mode (API_ID(0x0011U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
      \arg        ADC_CHANNEL_DISCON_DISABLE: disable discontinuous mode of routine & inserted channel
    \param[in]  length: number of conversions in discontinuous mode, the number can be 1..8
                        for routine channel, the number has no effect for inserted channel
    \param[out] none
    \retval     none
*/
void adc_discontinuous_mode_config(uint32_t adc_periph, uint8_t adc_sequence, uint32_t length)
{
    /* disable discontinuous mode of routine & inserted channel */
    ADC_CTL0(adc_periph) &= ~((uint32_t)(ADC_CTL0_DISRC | ADC_CTL0_DISIC));
    switch(adc_sequence) {
    case ADC_ROUTINE_CHANNEL:
        if((length <= 8U) && (length >= 1U)) {
            /* configure the number of conversions in discontinuous mode */
            ADC_CTL0(adc_periph) &= ~((uint32_t)ADC_CTL0_DISNUM);
            ADC_CTL0(adc_periph) |= CTL0_DISNUM((uint32_t)(length - ADC_CHANNEL_LENGTH_SUBTRACT_ONE));
            /* enable routine sequence discontinuous mode */
            ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_DISRC;
        } else {
            /* illegal parameters */
        }
        break;
    case ADC_INSERTED_CHANNEL:
        /* enable inserted sequence discontinuous mode */
        ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_DISIC;
        break;
    case ADC_CHANNEL_DISCON_DISABLE:
    /* disable discontinuous mode of routine & inserted channel */
    default:
        break;
    }
}

/*!
    \brief      configure the length of routine sequence or inserted sequence (API_ID(0x0012U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[in]  length: the length of the channel
                        routine channel 1-16
                        inserted channel 1-4
    \param[out] none
    \retval     none
*/
void adc_channel_length_config(uint32_t adc_periph, uint8_t adc_sequence, uint32_t length)
{
    switch(adc_sequence) {
    case ADC_ROUTINE_CHANNEL:
        if((length >= 1U) && (length <= 16U)) {
            ADC_RSQ0(adc_periph) &= ~((uint32_t)ADC_RSQ0_RL);
            ADC_RSQ0(adc_periph) |= RSQ0_RL((uint32_t)(length - ADC_CHANNEL_LENGTH_SUBTRACT_ONE));
        }
        break;
    case ADC_INSERTED_CHANNEL:
        if((length >= 1U) && (length <= 4U)) {
            ADC_ISQ0(adc_periph) &= ~((uint32_t)ADC_ISQ0_IL);
            ADC_ISQ0(adc_periph) |= ISQ0_IL((uint32_t)(length - ADC_CHANNEL_LENGTH_SUBTRACT_ONE));
        }
        break;
    default:
        break;
    }
}

/*!
    \brief      configure ADC routine channel (API_ID(0x0013U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  rank: the routine sequence rank,this parameter must be between 0 to 15
    \param[in]  adc_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x(x=0..21): ADC Channelx
    \param[in]  sample_time: the sample time value, 0..807
    \param[out] none
    \retval     none
*/
void adc_routine_channel_config(uint32_t adc_periph, uint8_t rank, uint8_t adc_channel,
                                uint32_t sample_time)
{
    uint32_t rsq;

    /* configure ADC routine sequence */
    if(rank < ADC_ROUTINE_CHANNEL_RANK_ONE) {
        /* the routine sequence rank is smaller than one */
        rsq = ADC_RSQ8(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH * rank)));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | (adc_channel & ADC_RSQX_RSQN)) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                rank));
        ADC_RSQ8(adc_periph) = rsq;
    } else if(rank < ADC_ROUTINE_CHANNEL_RANK_THREE) {
        /* the routine sequence rank is smaller than three */
        rsq = ADC_RSQ7(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                            (rank - ADC_ROUTINE_CHANNEL_RANK_ONE))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | (adc_channel & ADC_RSQX_RSQN)) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                (rank - ADC_ROUTINE_CHANNEL_RANK_ONE)));
        ADC_RSQ7(adc_periph) = rsq;
    } else if(rank < ADC_ROUTINE_CHANNEL_RANK_FIVE) {
        /* the routine sequence rank is smaller than five */
        rsq = ADC_RSQ6(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                            (rank - ADC_ROUTINE_CHANNEL_RANK_THREE))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | (adc_channel & ADC_RSQX_RSQN)) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                (rank - ADC_ROUTINE_CHANNEL_RANK_THREE)));
        ADC_RSQ6(adc_periph) = rsq;
    } else if(rank < ADC_ROUTINE_CHANNEL_RANK_SEVEN) {
        /* the routine sequence rank is smaller than seven */
        rsq = ADC_RSQ5(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                            (rank - ADC_ROUTINE_CHANNEL_RANK_FIVE))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | (adc_channel & ADC_RSQX_RSQN)) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                (rank - ADC_ROUTINE_CHANNEL_RANK_FIVE)));
        ADC_RSQ5(adc_periph) = rsq;
    } else if(rank < ADC_ROUTINE_CHANNEL_RANK_NINE) {
        /* the routine sequence rank is smaller than nine */
        rsq = ADC_RSQ4(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                            (rank - ADC_ROUTINE_CHANNEL_RANK_SEVEN))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | (adc_channel & ADC_RSQX_RSQN)) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                (rank - ADC_ROUTINE_CHANNEL_RANK_SEVEN)));
        ADC_RSQ4(adc_periph) = rsq;
    } else if(rank < ADC_ROUTINE_CHANNEL_RANK_ELEVEN) {
        /* the routine sequence rank is smaller than eleven */
        rsq = ADC_RSQ3(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                            (rank - ADC_ROUTINE_CHANNEL_RANK_NINE))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | (adc_channel & ADC_RSQX_RSQN)) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                (rank - ADC_ROUTINE_CHANNEL_RANK_NINE)));
        ADC_RSQ3(adc_periph) = rsq;
    } else if(rank < ADC_ROUTINE_CHANNEL_RANK_THIRTEEN) {
        /* the routine sequence rank is smaller than thirteen */
        rsq = ADC_RSQ2(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                            (rank - ADC_ROUTINE_CHANNEL_RANK_ELEVEN))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | (adc_channel & ADC_RSQX_RSQN)) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                (rank - ADC_ROUTINE_CHANNEL_RANK_ELEVEN)));
        ADC_RSQ2(adc_periph) = rsq;
    } else if(rank < ADC_ROUTINE_CHANNEL_RANK_FIFTEEN) {
        /* the routine sequence rank is smaller than fifteen */
        rsq = ADC_RSQ1(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                            (rank - ADC_ROUTINE_CHANNEL_RANK_THIRTEEN))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | (adc_channel & ADC_RSQX_RSQN)) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                (rank - ADC_ROUTINE_CHANNEL_RANK_THIRTEEN)));
        ADC_RSQ1(adc_periph) = rsq;
    } else if(rank < ADC_ROUTINE_CHANNEL_RANK_SIXTEEN) {
        /* the routine sequence rank is smaller than sixteen */
        rsq = ADC_RSQ0(adc_periph);
        rsq &= ~((uint32_t)((ADC_RSQX_RSMPN | ADC_RSQX_RSQN) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                            (rank - ADC_ROUTINE_CHANNEL_RANK_FIFTEEN))));
        rsq |= ((uint32_t)(SQX_SMP(sample_time) | (adc_channel & ADC_RSQX_RSQN)) << (ADC_ROUTINE_CHANNEL_SHIFT_LENGTH *
                (rank - ADC_ROUTINE_CHANNEL_RANK_FIFTEEN)));
        ADC_RSQ0(adc_periph) = rsq;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure ADC inserted channel (API_ID(0x0014U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  rank: the inserted sequence rank,this parameter must be between 0 to 3
    \param[in]  adc_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x(x=0..21): ADC Channelx
    \param[in]  sample_time: The sample time value, 0..807
    \param[out] none
    \retval     none
*/
void adc_inserted_channel_config(uint32_t adc_periph, uint8_t rank, uint8_t adc_channel,
                                 uint32_t sample_time)
{
    uint8_t inserted_length, rankx;
    uint32_t isq;

    /* get inserted sequence length */
    inserted_length = (uint8_t)GET_BITS(ADC_ISQ0(adc_periph), 20U, 21U);
    rankx = ADC_OFFSET_LENGTH - inserted_length + rank;

    /* configure ADC inserted sequence */
    if(rankx < ADC_INSERTED_CHANNEL_RANK_ONE) {
        /* the inserted sequence sequence rank is smaller than one */
        isq = ADC_ISQ2(adc_periph);
        isq &= ~((uint32_t)((ADC_ISQX_ISMPN | ADC_ISQX_ISQN) << (ADC_INSERTED_CHANNEL_SHIFT_LENGTH *
                            rankx)));
        isq |= ((uint32_t)(SQX_SMP(sample_time) | (adc_channel & ADC_ISQX_ISQN)) << (ADC_INSERTED_CHANNEL_SHIFT_LENGTH *
                rankx));
        ADC_ISQ2(adc_periph) = isq;
    } else if(rankx < ADC_INSERTED_CHANNEL_RANK_THREE) {
        /* the inserted sequence sequence rank is smaller than three */
        isq = ADC_ISQ1(adc_periph);
        isq &= ~((uint32_t)((ADC_ISQX_ISMPN | ADC_ISQX_ISQN) << (ADC_INSERTED_CHANNEL_SHIFT_LENGTH *
                            (rankx - ADC_INSERTED_CHANNEL_RANK_ONE))));
        isq |= ((uint32_t)(SQX_SMP(sample_time) | (adc_channel & ADC_ISQX_ISQN)) << (ADC_INSERTED_CHANNEL_SHIFT_LENGTH *
                (rankx - ADC_INSERTED_CHANNEL_RANK_ONE)));
        ADC_ISQ1(adc_periph) = isq;
    } else if(rankx < ADC_INSERTED_CHANNEL_RANK_FOUR) {
        /* the inserted sequence sequence rank is smaller than four */
        isq = ADC_ISQ0(adc_periph);
        isq &= ~((uint32_t)((ADC_ISQX_ISMPN | ADC_ISQX_ISQN) << (ADC_INSERTED_CHANNEL_SHIFT_LENGTH *
                            (rankx - ADC_INSERTED_CHANNEL_RANK_THREE))));
        isq |= ((uint32_t)(SQX_SMP(sample_time) | (adc_channel & ADC_ISQX_ISQN)) << (ADC_INSERTED_CHANNEL_SHIFT_LENGTH *
                (rankx - ADC_INSERTED_CHANNEL_RANK_THREE)));
        ADC_ISQ0(adc_periph) = isq;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      configure ADC latch_data source (API_ID(0x0015U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  latch_data : latch channel select
                only one parameter can be selected which is shown as below:
      \arg        ADC_LATCH_DATA_0: latch channel0
      \arg        ADC_LATCH_DATA_1: latch channel1
      \arg        ADC_LATCH_DATA_2: latch channel2
      \arg        ADC_LATCH_DATA_3: latch channel3
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[in]  rank: the routine or inserted sequence rank, 0~15 for routine sequence, 0~3 for inserted sequence
    \param[out] none
    \retval     none
    \note       this function can only be called when ADCON = 0
*/
void adc_latch_data_source_config(uint32_t adc_periph, uint32_t latch_data, uint32_t adc_sequence,
                                  uint8_t rank)
{
    uint32_t adc_ldctl;
    adc_ldctl = ADC_LDCTL(adc_periph);
    adc_ldctl &= ~((ADC_LDCTL_COVSELx | ADC_LDCTL_SEQSELx) << (24U - (latch_data & ADC_LATCH_DATA_MASK) * 8U));

    if(ADC_ROUTINE_CHANNEL == adc_sequence) {
        adc_ldctl |= ADC_LDCTL_SEQSELx << (24U - (latch_data & ADC_LATCH_DATA_MASK) * 8U);
    }

    adc_ldctl |= (rank & ADC_LDCTL_COVSELx) << (24U - (latch_data & ADC_LATCH_DATA_MASK) * 8U);
    ADC_LDCTL(adc_periph) = adc_ldctl;
}

/*!
    \brief      configure ADC inserted channel offset (API_ID(0x0016U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  inserted_channel : insert channel select
                only one parameter can be selected which is shown as below:
      \arg        ADC_INSERTED_CHANNEL_0: inserted channel0
      \arg        ADC_INSERTED_CHANNEL_1: inserted channel1
      \arg        ADC_INSERTED_CHANNEL_2: inserted channel2
      \arg        ADC_INSERTED_CHANNEL_3: inserted channel3
    \param[in]  offset : the offset data, 0..0xFFFFFF for 14bit-ADC, 0..0xFFF for 12bit-ADC
    \param[out] none
    \retval     none
*/
void adc_inserted_channel_offset_config(uint32_t adc_periph, uint8_t inserted_channel,
                                        uint32_t offset)
{
    uint8_t inserted_length;
    uint32_t num = 0U;

    inserted_length = (uint8_t)GET_BITS(ADC_ISQ0(adc_periph), 20U, 21U);
    num = ((uint32_t)ADC_OFFSET_LENGTH - ((uint32_t)inserted_length - (uint32_t)inserted_channel));

    if(num <= ADC_OFFSET_LENGTH) {
        /* calculate the offset of the register */
        num = num * ADC_OFFSET_SHIFT_LENGTH;
        /* configure the offset of the selected channels */
        REG32((adc_periph) + ADC_IOFF0_OFFSET + num) = IOFFX_IOFF((uint32_t)offset);
    }
}

/*!
    \brief      configure differential mode for ADC channel (API_ID(0x0017U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_channel: the channel use differential mode
                one or more parameters can be selected which is shown as below:
      \arg        ADC_DIFFERENTIAL_MODE_CHANNEL_x(x=0..21), ADC_DIFFERENTIAL_MODE_CHANNEL_ALL: ADC channel for differential mode
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_channel_differential_mode_config(uint32_t adc_periph, uint32_t adc_channel,
        ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        ADC_DIFCTL(adc_periph) |= (uint32_t)adc_channel;
    } else {
        ADC_DIFCTL(adc_periph) &= ~((uint32_t)adc_channel);
    }
}

/*!
    \brief      enable ADC external trigger (API_ID(0x0018U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[in]  trigger_mode: external trigger mode
                only one parameter can be selected which is shown as below:
      \arg        EXTERNAL_TRIGGER_DISABLE: external trigger disable
      \arg        EXTERNAL_TRIGGER_RISING: rising edge of external trigger
      \arg        EXTERNAL_TRIGGER_FALLING: falling edge of external trigger
      \arg        EXTERNAL_TRIGGER_RISING_FALLING: rising and falling edge of external trigger
    \param[out] none
    \retval     none
*/
void adc_external_trigger_config(uint32_t adc_periph, uint8_t adc_sequence,
                                 uint32_t trigger_mode)
{
    switch(adc_sequence) {
    case ADC_ROUTINE_CHANNEL:
        /* configure ADC routine sequence external trigger mode */
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ETMRC);
        ADC_CTL1(adc_periph) |= (uint32_t)CTL1_ETMRC(trigger_mode);
        break;
    case ADC_INSERTED_CHANNEL:
        /* configure ADC inserted sequence external trigger mode */
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_ETMIC);
        ADC_CTL1(adc_periph) |= (uint32_t)CTL1_ETMIC(trigger_mode);
        break;
    default:
        break;
    }
}

/*!
    \brief      enable ADC software trigger (API_ID(0x0019U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
    \param[out] none
    \retval     none
*/
void adc_software_trigger_enable(uint32_t adc_periph, uint8_t adc_sequence)
{
    /* enable routine channel software trigger */
    if(RESET != (adc_sequence & ADC_ROUTINE_CHANNEL)) {
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_SWRCST;
    }
    /* enable inserted sequence software trigger */
    if(RESET != (adc_sequence & ADC_INSERTED_CHANNEL)) {
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_SWICST;
    }
}

/*!
    \brief      configure end of conversion mode (API_ID(0x001AU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  end_selection: end of conversion mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_EORC_SET_SEQUENCE: only at the end of a sequence of routine conversions, the EORC bit is set. Overflow detection is disabled unless DMA=1.
      \arg        ADC_EORC_SET_CONVERSION: at the end of each routine conversion, the EORC bit is set. Overflow is detected automatically.
    \param[out] none
    \retval     none
*/
void adc_end_of_conversion_config(uint32_t adc_periph, uint32_t end_selection)
{
    if(ADC_EORC_SET_SEQUENCE == end_selection) {
        /* only at the end of a sequence of routine conversions, the EORC bit is set */
        ADC_CTL1(adc_periph) &= ~((uint32_t)ADC_CTL1_EORCM);
    } else if(ADC_EORC_SET_CONVERSION == end_selection) {
        /* at the end of each routine conversion, the EORC bit is set. Overflow is detected automatically */
        ADC_CTL1(adc_periph) |= (uint32_t)ADC_CTL1_EORCM;
    } else {
        /* illegal parameters */
    }
}

/*!
    \brief      read ADC routine data register (API_ID(0x001BU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     the conversion value
*/
uint32_t adc_routine_data_read(uint32_t adc_periph)
{
    return (uint32_t)(ADC_RDATA(adc_periph));
}

/*!
    \brief      read ADC inserted sequence data register (API_ID(0x001CU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     the conversion value
*/
uint32_t adc_inserted_data_read(uint32_t adc_periph)
{
    return (uint32_t)(ADC_IDATA(adc_periph));
}

/*!
    \brief      read ADC latch data register (API_ID(0x001DU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  latch_data : latch channel select
                only one parameter can be selected which is shown as below:
      \arg        ADC_LATCH_DATA_0: latch data register 0
      \arg        ADC_LATCH_DATA_1: latch data register 1
      \arg        ADC_LATCH_DATA_2: latch data register 2
      \arg        ADC_LATCH_DATA_3: latch data register 3
    \param[out] none
    \retval     the conversion value
*/
uint32_t adc_latch_data_read(uint32_t adc_periph, uint8_t latch_data)
{
    uint32_t ldata;
    /* read the data of the selected channel */
    switch(latch_data) {
    case ADC_LATCH_DATA_0:
        /* read the data of latch data 0 */
        ldata = ADC_LDATA0(adc_periph);
        break;
    case ADC_LATCH_DATA_1:
        /* read the data of latch data 1 */
        ldata = ADC_LDATA1(adc_periph);
        break;
    case ADC_LATCH_DATA_2:
        /* read the data of latch data 2 */
        ldata = ADC_LDATA2(adc_periph);
        break;
    case ADC_LATCH_DATA_3:
        /* read the data of latch data 3 */
        ldata = ADC_LDATA3(adc_periph);
        break;
    default:
        ldata = 0U;
        break;
    }
    return (uint32_t)ldata;
}

/*!
    \brief      configure ADC analog watchdog 0 single channel (API_ID(0x001EU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_x: ADC Channelx(x=0..21)
    \param[out] none
    \retval     none
*/
void adc_watchdog0_single_channel_enable(uint32_t adc_periph, uint8_t adc_channel)
{
    ADC_CTL0(adc_periph) &= ~((uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC |
                                         ADC_CTL0_WD0CHSEL));

    ADC_CTL0(adc_periph) |= (uint32_t)(adc_channel & ADC_CTL0_WD0CHSEL);
    ADC_CTL0(adc_periph) |= (uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC);
}

/*!
    \brief      configure ADC analog watchdog 0 group channel (API_ID(0x001FU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  adc_sequence: the sequence use analog watchdog 0
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_CHANNEL: routine sequence
      \arg        ADC_INSERTED_CHANNEL: inserted sequence
      \arg        ADC_ROUTINE_INSERTED_CHANNEL: both routine and inserted sequence
    \param[out] none
    \retval     none
*/
void adc_watchdog0_group_channel_enable(uint32_t adc_periph, uint8_t adc_sequence)
{
    ADC_CTL0(adc_periph) &= ~((uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC));
    /* select the sequence */
    switch(adc_sequence) {
    case ADC_ROUTINE_CHANNEL:
        ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_RWD0EN;
        break;
    case ADC_INSERTED_CHANNEL:
        ADC_CTL0(adc_periph) |= (uint32_t)ADC_CTL0_IWD0EN;
        break;
    case ADC_ROUTINE_INSERTED_CHANNEL:
        ADC_CTL0(adc_periph) |= (uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN);
        break;
    default:
        break;
    }
}

/*!
    \brief      disable ADC analog watchdog 0 (API_ID(0x0020U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_watchdog0_disable(uint32_t adc_periph)
{
    ADC_CTL0(adc_periph) &= ~((uint32_t)(ADC_CTL0_RWD0EN | ADC_CTL0_IWD0EN | ADC_CTL0_WD0SC |
                                         ADC_CTL0_WD0CHSEL));
}

/*!
    \brief      configure ADC analog watchdog 1 channel (API_ID(0x0021U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  selection_channel: the channel use analog watchdog 1
                one or more parameters can be selected which is shown as below:
      \arg        ADC_AWD1_2_SELECTION_CHANNEL_x, ADC_AWD1_2_SELECTION_CHANNEL_ALL: ADC channel analog watchdog 1/2 selection
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_watchdog1_channel_config(uint32_t adc_periph, uint32_t selection_channel,
                                  ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        ADC_WD1SR(adc_periph) |= (uint32_t)selection_channel;
    } else {
        ADC_WD1SR(adc_periph) &= ~((uint32_t)selection_channel);
    }
}

/*!
    \brief      configure ADC analog watchdog 2 channel (API_ID(0x0022U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  selection_channel: the channel use analog watchdog 2
                one or more parameters can be selected which is shown as below:
      \arg        ADC_AWD1_2_SELECTION_CHANNEL_x, ADC_AWD1_2_SELECTION_CHANNEL_ALL: ADC channel analog watchdog 1/2 selection
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_watchdog2_channel_config(uint32_t adc_periph, uint32_t selection_channel,
                                  ControlStatus newvalue)
{
    if(ENABLE == newvalue) {
        ADC_WD2SR(adc_periph) |= (uint32_t)selection_channel;
    } else {
        ADC_WD2SR(adc_periph) &= ~((uint32_t)selection_channel);
    }
}

/*!
    \brief      disable ADC analog watchdog 1 (API_ID(0x0023U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_watchdog1_disable(uint32_t adc_periph)
{
    ADC_WD1SR(adc_periph) &= ~((uint32_t)ADC_WD1SR_AWD1CS);
}

/*!
    \brief      disable ADC analog watchdog 2 (API_ID(0x0024U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_watchdog2_disable(uint32_t adc_periph)
{
    ADC_WD2SR(adc_periph) &= ~((uint32_t)ADC_WD2SR_AWD2CS);
}

/*!
    \brief      configure ADC analog watchdog 0 threshold (API_ID(0x0025U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  low_threshold: analog watchdog 0 low threshold, 0..0xFFFFFF for 14bit-ADC, 0..0xFFF for 12bit-ADC
    \param[in]  high_threshold: analog watchdog 0 high threshold, 0..0xFFFFFF for 14bit-ADC, 0..0xFFF for 12bit-ADC
    \param[out] none
    \retval     none
*/
void adc_watchdog0_threshold_config(uint32_t adc_periph, uint32_t low_threshold,
                                    uint32_t high_threshold)
{
    ADC_WDLT0(adc_periph) = (uint32_t)WDLT0_WDLT0(low_threshold);
    ADC_WDHT0(adc_periph) = (uint32_t)WDHT0_WDHT0(high_threshold);
}

/*!
    \brief      configure ADC analog watchdog 1 threshold (API_ID(0x0026U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  low_threshold: analog watchdog 1 low threshold, 0..0xFFFFFF for 14bit-ADC, 0..0xFF for 12bit-ADC
    \param[in]  high_threshold: analog watchdog 1 high threshold, 0..0xFFFFFF for 14bit-ADC, 0..0xFF for 12bit-ADC
    \param[out] none
    \retval     none
*/
void adc_watchdog1_threshold_config(uint32_t adc_periph, uint32_t low_threshold,
                                    uint32_t high_threshold)
{
    ADC_WDLT1(adc_periph) = (uint32_t)WDLT1_WDLT1(low_threshold);
    ADC_WDHT1(adc_periph) = (uint32_t)WDHT1_WDHT1(high_threshold);
}

/*!
    \brief      configure ADC analog watchdog 2 threshold (API_ID(0x0027U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  low_threshold: analog watchdog 2 low threshold, 0..0xFFFFFF for 14bit-ADC, 0..0xFF for 12bit-ADC
    \param[in]  high_threshold: analog watchdog 2 high threshold, 0..0xFFFFFF for 14bit-ADC, 0..0xFF for 12bit-ADC
    \param[out] none
    \retval     none
*/
void adc_watchdog2_threshold_config(uint32_t adc_periph, uint32_t low_threshold,
                                    uint32_t high_threshold)
{
    ADC_WDLT2(adc_periph) = (uint32_t)WDLT2_WDLT2(low_threshold);
    ADC_WDHT2(adc_periph) = (uint32_t)WDHT2_WDHT2(high_threshold);
}

/*!
    \brief      configure ADC oversample mode (API_ID(0x0028U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  mode: ADC oversampling mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_OVERSAMPLING_ALL_CONVERT: all oversampled conversions for a channel are done consecutively after a trigger
      \arg        ADC_OVERSAMPLING_ONE_CONVERT: each oversampled conversion for a channel needs a trigger
    \param[in]  shift: ADC oversampling shift
                only one parameter can be selected which is shown as below:
      \arg        ADC_OVERSAMPLING_SHIFT_NONE: no oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_1B: 1-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_2B: 2-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_3B: 3-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_4B: 4-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_5B: 5-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_6B: 6-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_7B: 7-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_8B: 8-bit oversampling shift
      \arg        ADC_OVERSAMPLING_SHIFT_9B: 9-bit oversampling shift, only supported in 14bit-ADC
      \arg        ADC_OVERSAMPLING_SHIFT_10B: 10-bit oversampling shift, only supported in 14bit-ADC
      \arg        ADC_OVERSAMPLING_SHIFT_11B: 11-bit oversampling shift, only supported in 14bit-ADC
    \param[in]  ratio: ADC oversampling ratio, 0..1023 for 14bit-ADC, 0..255 for 12bit-ADC
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_config(uint32_t adc_periph, uint32_t mode, uint32_t shift, uint16_t ratio)
{
    if(ADC_OVERSAMPLING_ALL_CONVERT == mode) {
        /* all oversampled conversions for a channel are done consecutively after a trigger */
        ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)ADC_OVSAMPCTL_TOVS);
    } else if(ADC_OVERSAMPLING_ONE_CONVERT == mode) {
        /* each oversampled conversion for a channel needs a trigger */
        ADC_OVSAMPCTL(adc_periph) |= (uint32_t)ADC_OVSAMPCTL_TOVS;
    } else {
        /* illegal parameters */
    }
    /* configure the shift and ratio */
    ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)(ADC_OVSAMPCTL_OVSR | ADC_OVSAMPCTL_OVSS));
    ADC_OVSAMPCTL(adc_periph) |= ((uint32_t)(shift & ADC_OVSAMPCTL_OVSS) | (uint32_t)OVSCR_OVSR(ratio));
}

/*!
    \brief      enable ADC oversample mode (API_ID(0x0029U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_enable(uint32_t adc_periph)
{
    ADC_OVSAMPCTL(adc_periph) |= (uint32_t)ADC_OVSAMPCTL_OVSEN;
}

/*!
    \brief      disable ADC oversample mode (API_ID(0x002AU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[out] none
    \retval     none
*/
void adc_oversample_mode_disable(uint32_t adc_periph)
{
    ADC_OVSAMPCTL(adc_periph) &= ~((uint32_t)ADC_OVSAMPCTL_OVSEN);
}

/*!
    \brief      get the ADC flag bits (API_ID(0x002BU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  flag: the adc flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_FLAG_WDE0: analog watchdog 0 event flag
      \arg        ADC_FLAG_EORC: end of routine sequence conversion flag
      \arg        ADC_FLAG_EOIC: end of inserted sequence conversion flag
      \arg        ADC_FLAG_STIC: start flag of inserted sequence
      \arg        ADC_FLAG_STRC: start flag of routine sequence
      \arg        ADC_FLAG_ROVF: routine data register overflow flag
      \arg        ADC_FLAG_WDE1: analog watchdog 1 event flag
      \arg        ADC_FLAG_WDE2: analog watchdog 2 event flag
      \arg        ADC_FLAG_IOVF: inserted data register overflow flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_flag_get(uint32_t adc_periph, uint32_t flag)
{
    FlagStatus reval = RESET;
    if(0U != (ADC_STAT(adc_periph) & flag)) {
        reval = SET;
    }
    return reval;
}

/*!
    \brief      clear the ADC flag bits (API_ID(0x002CU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  flag: the adc flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_FLAG_WDE0: analog watchdog 0 event flag
      \arg        ADC_FLAG_EORC: end of routine sequence conversion flag
      \arg        ADC_FLAG_EOIC: end of inserted sequence conversion flag
      \arg        ADC_FLAG_STIC: start flag of inserted sequence
      \arg        ADC_FLAG_STRC: start flag of routine sequence
      \arg        ADC_FLAG_ROVF: routine data register overflow flag
      \arg        ADC_FLAG_WDE1: analog watchdog 1 event flag
      \arg        ADC_FLAG_WDE2: analog watchdog 2 event flag
      \arg        ADC_FLAG_IOVF: inserted data register overflow flag
    \param[out] none
    \retval     none
*/
void adc_flag_clear(uint32_t adc_periph, uint32_t flag)
{
    ADC_STAT(adc_periph) = ~((uint32_t)flag & ADC_FLAG_MASK);
}

/*!
    \brief      enable ADC interrupt (API_ID(0x002DU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  interrupt: the adc interrupt
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_WDE0: analog watchdog 0 interrupt
      \arg        ADC_INT_EORC: end of routine sequence conversion interrupt
      \arg        ADC_INT_EOIC: end of inserted sequence conversion interrupt
      \arg        ADC_INT_ROVF: routine data register overflow interrupt
      \arg        ADC_INT_WDE1: analog watchdog 1 interrupt
      \arg        ADC_INT_WDE2: analog watchdog 2 interrupt
      \arg        ADC_INT_IOVF: inserted data register overflow interrupt
    \param[out] none
    \retval     none
*/
void adc_interrupt_enable(uint32_t adc_periph, uint32_t interrupt)
{
    ADC_CTL0(adc_periph) |= (uint32_t)(interrupt & ADC_INT_MASK);
}

/*!
    \brief      disable ADC interrupt (API_ID(0x002EU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  interrupt: the adc interrupt
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_WDE0: analog watchdog 0 interrupt
      \arg        ADC_INT_EORC: end of routine sequence conversion interrupt
      \arg        ADC_INT_EOIC: end of inserted sequence conversion interrupt
      \arg        ADC_INT_ROVF: routine data register overflow interrupt
      \arg        ADC_INT_WDE1: analog watchdog 1 interrupt
      \arg        ADC_INT_WDE2: analog watchdog 2 interrupt
      \arg        ADC_INT_IOVF: inserted data register overflow interrupt
    \param[out] none
    \retval     none
*/
void adc_interrupt_disable(uint32_t adc_periph, uint32_t interrupt)
{
    ADC_CTL0(adc_periph) &= ~(uint32_t)(interrupt & ADC_INT_MASK);
}

/*!
    \brief      get the ADC interrupt bits (API_ID(0x002FU))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  int_flag: the adc interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_FLAG_WDE0: analog watchdog 0 interrupt flag
      \arg        ADC_INT_FLAG_EORC: end of routine sequence conversion interrupt flag
      \arg        ADC_INT_FLAG_EOIC: end of inserted sequence conversion interrupt flag
      \arg        ADC_INT_FLAG_ROVF: routine data register overflow interrupt flag
      \arg        ADC_INT_FLAG_WDE1: analog watchdog 1 interrupt flag
      \arg        ADC_INT_FLAG_WDE2: analog watchdog 2 interrupt flag
      \arg        ADC_INT_FLAG_IOVF: inserted data register overflow interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
    \Note       After the interrupt enable bit is cleared, if the hardware flag remains set, this API will still return RESET.
                Therefore, in an ISR or during the interrupt-disable flow, this API alone must not be relied upon to determine whether the flag should be cleared.
                The corresponding flag must be cleared according to the module-specific rules, and the NVIC-pending bit should also be cleared when necessary.    
*/
FlagStatus adc_interrupt_flag_get(uint32_t adc_periph, uint32_t int_flag)
{
    FlagStatus reval = RESET;
    uint32_t state;
    /* check the interrupt bits */
    switch(int_flag) {
    case ADC_INT_FLAG_WDE0:
        /* get the ADC analog watchdog 0 interrupt bits */
        state = ADC_STAT(adc_periph) & ADC_STAT_WDE0;
        if((ADC_CTL0(adc_periph) & ADC_CTL0_WDE0IE) && state) {
            reval = SET;
        }
        break;
    case ADC_INT_FLAG_EORC:
        /* get the ADC end of routine sequence conversion interrupt bits */
        state = ADC_STAT(adc_periph) & ADC_STAT_EORC;
        if((ADC_CTL0(adc_periph) & ADC_CTL0_EORCIE) && state) {
            reval = SET;
        }
        break;
    case ADC_INT_FLAG_EOIC:
        /* get the ADC end of inserted sequence conversion interrupt bits */
        state = ADC_STAT(adc_periph) & ADC_STAT_EOIC;
        if((ADC_CTL0(adc_periph) & ADC_CTL0_EOICIE) && state) {
            reval = SET;
        }
        break;
    case ADC_INT_FLAG_ROVF:
        /* get the ADC routine data register overflow interrupt bits */
        state = ADC_STAT(adc_periph) & ADC_STAT_ROVF;
        if((ADC_CTL0(adc_periph) & ADC_CTL0_ROVFIE) && state) {
            reval = SET;
        }
        break;
    case ADC_INT_FLAG_WDE1:
        /* get the ADC analog watchdog 1 interrupt bits */
        state = ADC_STAT(adc_periph) & ADC_STAT_WDE1;
        if((ADC_CTL0(adc_periph) & ADC_CTL0_WDE1IE) && state) {
            reval = SET;
        }
        break;
    case ADC_INT_FLAG_WDE2:
        /* get the ADC analog watchdog 2 interrupt bits */
        state = ADC_STAT(adc_periph) & ADC_STAT_WDE2;
        if((ADC_CTL0(adc_periph) & ADC_CTL0_WDE2IE) && state) {
            reval = SET;
        }
        break;
    case ADC_INT_FLAG_IOVF:
        /* get the ADC inserted data register overflow interrupt bits */
        state = ADC_STAT(adc_periph) & ADC_STAT_IOVF;
        if((ADC_CTL0(adc_periph) & ADC_CTL0_IOVFIE) && state) {
            reval = SET;
        }
        break;
    default:
        break;
    }
    return reval;
}

/*!
    \brief      clear the ADC flag (API_ID(0x0030U))
    \param[in]  adc_periph: ADCx, x=0,1,2
    \param[in]  int_flag: the adc interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_FLAG_WDE0: analog watchdog 0 interrupt flag
      \arg        ADC_INT_FLAG_EORC: end of routine sequence conversion interrupt flag
      \arg        ADC_INT_FLAG_EOIC: end of inserted sequence conversion interrupt flag
      \arg        ADC_INT_FLAG_ROVF: routine data register overflow interrupt flag
      \arg        ADC_INT_FLAG_WDE1: analog watchdog 1 interrupt flag
      \arg        ADC_INT_FLAG_WDE2: analog watchdog 2 interrupt flag
      \arg        ADC_INT_FLAG_IOVF: inserted data register overflow interrupt flag
    \param[out] none
    \retval     none
*/
void adc_interrupt_flag_clear(uint32_t adc_periph, uint32_t int_flag)
{
    ADC_STAT(adc_periph) = ~((uint32_t)(int_flag & ADC_INT_FLAG_MASK));
}

/*!
    \brief      configure the ADC sync mode (API_ID(0x0031U))
    \param[in]  sync_mode: ADC sync mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_SYNC_MODE_INDEPENDENT: all the ADCs work independently
      \arg        ADC_DUAL_ROUTINE_PARALLEL_INSERTED_PARALLEL: ADC0/1 work in combined routine parallel & inserted parallel mode, ADC2 works independently
      \arg        ADC_DUAL_ROUTINE_PARALLEL_INSERTED_ROTATION: ADC0/1 work in combined routine parallel & trigger rotation mode, ADC2 works independently
      \arg        ADC_DUAL_INSERTED_PARALLEL: ADC0/1 work in inserted parallel mode, ADC2 works independently
      \arg        ADC_DUAL_ROUTINE_PARALLEL: ADC0/1 work in routine parallel mode, ADC2 works independently
      \arg        ADC_DUAL_ROUTINE_FOLLOW_UP: ADC0/1 work in follow-up mode, ADC2 works independently
      \arg        ADC_DUAL_INSERTED_TRIGGER_ROTATION: ADC0/1 work in trigger rotation mode, ADC2 works independently
    \param[out] none
    \retval     none
*/
void adc_sync_mode_config(uint32_t sync_mode)
{
    ADC_SYNCCTL(ADC0) &= ~((uint32_t)ADC_SYNCCTL_SYNCM);
    ADC_SYNCCTL(ADC0) |= (uint32_t)(sync_mode & ADC_SYNCCTL_SYNCM);
}

/*!
    \brief      configure the delay between 2 sampling phases in ADC sync modes (API_ID(0x0032U))
    \param[in]  sample_delay:  the delay between 2 sampling phases in ADC sync modes
                only one parameter can be selected which is shown as below:
      \arg        ADC_SYNC_DELAY_xCYCLE: x=5..20,the delay between 2 sampling phases in ADC sync modes is x ADC clock cycles
    \param[out] none
    \retval     none
*/
void adc_sync_delay_config(uint32_t sample_delay)
{
    ADC_SYNCCTL(ADC0) &= ~((uint32_t)ADC_SYNCCTL_SYNCDLY);
    ADC_SYNCCTL(ADC0) |= (uint32_t)(sample_delay & ADC_SYNCCTL_SYNCDLY);
}

/*!
    \brief      configure ADC sync DMA mode selection (API_ID(0x0033U))
    \param[in]  dma_mode:  ADC sync DMA mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_SYNC_DMA_DISABLE: ADC sync DMA disabled
      \arg        ADC_SYNC_DMA_MODE0: ADC sync DMA mode 0
      \arg        ADC_SYNC_DMA_MODE1: ADC sync DMA mode 1
    \param[out] none
    \retval     none
*/
void adc_sync_dma_config(uint32_t dma_mode)
{
    ADC_SYNCCTL(ADC0) &= ~((uint32_t)ADC_SYNCCTL_SYNCDMA);
    ADC_SYNCCTL(ADC0) |= (uint32_t)(dma_mode & ADC_SYNCCTL_SYNCDMA);
}

/*!
    \brief      configure ADC sync DMA engine issues requests according to the SYNCDMA bits (API_ID(0x0034U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_sync_dma_request_after_last_enable(void)
{
    ADC_SYNCCTL(ADC0) |= (uint32_t)ADC_SYNCCTL_SYNCDDM;
}

/*!
    \brief      configure ADC sync DMA engine is disabled after the end of transfer signal from DMA controller is detected (API_ID(0x0035U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void adc_sync_dma_request_after_last_disable(void)
{
    ADC_SYNCCTL(ADC0) &= ~((uint32_t)ADC_SYNCCTL_SYNCDDM);
}

/*!
    \brief      read ADC sync master adc routine data register 0  (API_ID(0x0036U))
    \param[in]  none
    \param[out] none
    \retval     sync routine data 0
*/
uint32_t adc_sync_master_adc_routine_data0_read(void)
{
    return (uint32_t)(ADC_SYNCDATA0 & ADC_SYNCDATA0_SYNCDATA0);
}

/*!
    \brief      read ADC sync slave adc routine data register 0 (API_ID(0x0037U))
    \param[in]  none
    \param[out] none
    \retval     sync routine data 0
*/
uint32_t adc_sync_slave_adc_routine_data0_read(void)
{
    return (uint32_t)(ADC_SYNCDATA0 & ADC_SYNCDATA0_SYNCDATA1) >> 16;
}

/*!
    \brief      read ADC sync routine data register 1 (API_ID(0x0038U))
    \param[in]  none
    \param[out] none
    \retval     sync routine data 1
*/
uint32_t adc_sync_routine_data1_read(void)
{
    return (uint32_t)ADC_SYNCDATA1;
}
