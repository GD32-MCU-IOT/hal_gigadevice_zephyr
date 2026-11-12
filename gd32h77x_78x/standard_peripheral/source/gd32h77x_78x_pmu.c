/*!
    \file    gd32h77x_78x_pmu.c
    \brief   PMU driver

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

#include "gd32h77x_78x_pmu.h"

/* PMU register bit offset */
#define PAR_TSW_IRCCNT_OFFSET               ((uint32_t)0x00000010U)               /*!< bit offset of TSW_IRCCNT in PMU_PAR */

/*!
    \brief      reset PMU register (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_deinit(void)
{
    /* reset PMU */
    rcu_periph_reset_enable(RCU_PMURST);
    rcu_periph_reset_disable(RCU_PMURST);
}

/*!
    \brief      select low voltage detector threshold (API_ID(0x0002U))
    \param[in]  lvdt_n:
                only one parameter can be selected which is shown as below:
      \arg        PMU_LVDT_0: voltage threshold is 2.1V
      \arg        PMU_LVDT_1: voltage threshold is 2.3V
      \arg        PMU_LVDT_2: voltage threshold is 2.4V
      \arg        PMU_LVDT_3: voltage threshold is 2.6V
      \arg        PMU_LVDT_4: voltage threshold is 2.7V
      \arg        PMU_LVDT_5: voltage threshold is 2.9V
      \arg        PMU_LVDT_6: voltage threshold is 3.0V
      \arg        PMU_LVDT_7: input analog voltage on PB7 (compared with 0.8V)
    \param[out] none
    \retval     none
*/
void pmu_lvd_select(uint32_t lvdt_n)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_LVD(lvdt_n)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t temp;
        temp = PMU_CTL0;
        /* clear LVDT bits */
        temp &= ~PMU_CTL0_LVDT;
        /* set LVDT bits according to lvdt_n */
        temp |= lvdt_n;
        PMU_CTL0 = temp;
    }
}

/*!
    \brief      enable PMU lvd (API_ID(0x0003U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_lvd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_LVDEN;
}

/*!
    \brief      disable PMU lvd (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_lvd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_LVDEN;
}

/*!
    \brief      select analog voltage detector threshold (API_ID(0x0005U))
    \param[in]  avdt_n:
                only one parameter can be selected which is shown as below:
      \arg        PMU_AVDT_0: voltage threshold is 1.7V
      \arg        PMU_AVDT_1: voltage threshold is 2.1V
      \arg        PMU_AVDT_2: voltage threshold is 2.5V
      \arg        PMU_AVDT_3: voltage threshold is 2.8V
    \param[out] none
    \retval     none
*/
void pmu_avd_select(uint32_t avdt_n)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_AVD(avdt_n)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t temp;
        temp = PMU_CTL0;
        /* clear VAVDVC bits */
        temp &= ~PMU_CTL0_VAVDVC;
        /* set VAVDVC bits according to avdt_n */
        temp |= avdt_n;
        PMU_CTL0 = temp;
    }
}

/*!
    \brief      enable PMU analog voltage detector (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_avd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_VAVDEN;
}

/*!
    \brief      disable PMU analog voltage detector (API_ID(0x0007U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_avd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_VAVDEN;
}

/*!
    \brief      select PMU Vcore over voltage detector threshold (API_ID(0x0008U))
    \param[in]  ovdt_n:
                only one parameter can be selected which is shown as below:
      \arg        PMU_OVDT_0: voltage threshold is 0.9V
      \arg        PMU_OVDT_1: voltage threshold is 1.0V
      \arg        PMU_OVDT_2: voltage threshold is 1.1V
      \arg        PMU_OVDT_3: voltage threshold is 1.2V
    \param[out] none
    \retval     none
*/
void pmu_ovd_select(uint32_t ovdt_n)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_OVD(ovdt_n)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0008U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t temp;
        temp = PMU_CTL0;
        /* clear VOVDVC bits */
        temp &= ~PMU_CTL0_VOVDVC;
        /* set VAVDVC bits according to avdt_n */
        temp |= ovdt_n;
        PMU_CTL0 = temp;
    }
}

/*!
    \brief      enable PMU Vcore over voltage detector (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_ovd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_VOVDEN;
}

/*!
    \brief      disable PMU Vcore over voltage detector (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_ovd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_VOVDEN;
}

/*!
    \brief      select PMU Vcore under voltage detector threshold (API_ID(0x000BU))
    \param[in]  uvdt_n:
                only one parameter can be selected which is shown as below:
      \arg        PMU_UVDT_0: voltage threshold is 0.8V (upper 0.825V, lower 0.8V)
      \arg        PMU_UVDT_1: voltage threshold is 0.7V (upper 0.725V, lower 0.7V)
      \arg        PMU_UVDT_2: voltage threshold is 0.6V (upper 0.675V, lower 0.65V)
      \arg        PMU_UVDT_3: voltage threshold is 0.9V (upper 0.9V, lower 0.875V)
    \param[out] none
    \retval     none
*/
void pmu_uvd_select(uint32_t uvdt_n)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_UVD(uvdt_n)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t temp;
        temp = PMU_CTL0;
        /* clear VAVDVC bits */
        temp &= ~PMU_CTL0_VUVDVC;
        /* set VAVDVC bits according to avdt_n */
        temp |= uvdt_n;
        PMU_CTL0 = temp;
    }
}

/*!
    \brief      enable PMU Vcore under voltage detector (API_ID(0x000CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_uvd_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_VUVDEN;
}

/*!
    \brief      disable PMU Vcore under voltage detector (API_ID(0x000DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_uvd_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_VUVDEN;
}

/*!
    \brief      select Deep-sleep mode Vcore voltage (API_ID(0x000EU))
    \param[in]  dsvos:
                only one parameter can be selected which is shown as below:
      \arg        PMU_DSVOS_1: Deep-sleep mode Vcore voltage 0.7V
      \arg        PMU_DSVOS_2: Deep-sleep mode Vcore voltage 0.8V
      \arg        PMU_DSVOS_3: Deep-sleep mode Vcore voltage 0.9V
    \param[out] none
    \retval     none
*/
void pmu_dsvos_select(uint32_t dsvos)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_DSVOS(dsvos)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x000EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t temp;
        temp = PMU_CTL0;
        temp &= ~PMU_CTL0_DSVOS;
        temp |= dsvos;
        PMU_CTL0 = temp;
    }
}

/*!
    \brief      select PMU VBAT battery charging resistor (API_ID(0x000FU))
    \param[in]  resistor:
                only one parameter can be selected which is shown as below:
      \arg        PMU_VCRSEL_5K: 5 kOhms resistor is selected for charing VBAT battery
      \arg        PMU_VCRSEL_1P5K: 1.5 kOhms resistor is selected for charing VBAT battery
    \param[out] none
    \retval     none
*/
void pmu_vbat_charging_select(uint32_t resistor)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_VBAT(resistor)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        PMU_CTL3 &= ~PMU_CTL3_VCRSEL;
        PMU_CTL3 |= resistor;
    }
}

/*!
    \brief      enable VBAT battery charging (API_ID(0x0010U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vbat_charging_enable(void)
{
    PMU_CTL3 |= PMU_CTL3_VCEN;
}

/*!
    \brief      disable VBAT battery charging (API_ID(0x0011U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vbat_charging_disable(void)
{
    PMU_CTL3 &= ~PMU_CTL3_VCEN;
}

/*!
    \brief      enable VBAT and temperature monitoring (API_ID(0x0012U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vbat_temp_monitor_enable(void)
{
    PMU_CTL1 |= PMU_CTL1_VBTMEN;
}

/*!
    \brief      disable VBAT and temperature monitoring (API_ID(0x0013U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vbat_temp_monitor_disable(void)
{
    PMU_CTL1 &= ~PMU_CTL1_VBTMEN;
}

/*!
    \brief      enable USB regulator (API_ID(0x0014U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_usb_regulator_enable(void)
{
    PMU_CTL3 |= PMU_CTL3_USBSEN;
}

/*!
    \brief      disable USB regulator (API_ID(0x0015U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_usb_regulator_disable(void)
{
    PMU_CTL3 &= ~PMU_CTL3_USBSEN;
}

/*!
    \brief      enable VDD33USB voltage level detector (API_ID(0x0016U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_usb_voltage_detector_enable(void)
{
    PMU_CTL3 |= PMU_CTL3_VUSB33DEN;
}

/*!
    \brief      disable VDD33USB voltage level detector (API_ID(0x0017U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_usb_voltage_detector_disable(void)
{
    PMU_CTL3 &= ~PMU_CTL3_VUSB33DEN;
}

/*!
    \brief      enable pkcau power (API_ID(0x0018U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_pkcau_power_enable(void)
{
    PMU_CTL3 |= PMU_CTL3_PKCAUSW;
}

/*!
    \brief      disable pkcau power (API_ID(0x0019U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_pkcau_power_disable(void)
{
    PMU_CTL3 &= ~PMU_CTL3_PKCAUSW;
}

/*!
    \brief      enable pkcau output isolation (API_ID(0x001AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_pkcau_output_isolation_enable(void)
{
    PMU_CTL3 |= PMU_CTL3_PKCAUHTEN;
}

/*!
    \brief      disable pkcau output isolation (API_ID(0x001BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_pkcau_output_isolation_disable(void)
{
    PMU_CTL3 &= ~PMU_CTL3_PKCAUHTEN;
}

/*!
    \brief      enable esc power (API_ID(0x001CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_esc_power_enable(void)
{
    PMU_CTL3 |= PMU_CTL3_ESCSW;
}

/*!
    \brief      disable esc power (API_ID(0x001DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_esc_power_disable(void)
{
    PMU_CTL3 &= ~PMU_CTL3_ESCSW;
}

/*!
    \brief      enable esc output isolation (API_ID(0x001EU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_esc_output_isolation_enable(void)
{
    PMU_CTL3 |= PMU_CTL3_ESCHTEN;
}

/*!
    \brief      disable esc output isolation (API_ID(0x001FU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_esc_output_isolation_disable(void)
{
    PMU_CTL3 &= ~PMU_CTL3_ESCHTEN;
}

/*!
    \brief      configure Vcore power supply (API_ID(0x0020U))
    \param[in]  smpsmode:
                only one parameter can be selected which is shown as below:
      \arg        PMU_DIRECT_SMPS_SUPPLY: Vcore supplied from SMPS step-down converter
      \arg        PMU_BYPASS: SMPS disabled, Vcore supplied externally
    \param[out] none
    \retval     none
*/
void pmu_smps_supply_config(uint32_t smpsmode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_SMPS_SUPPLY(smpsmode)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0020U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t temp;
        temp = PMU_CTL3;
        temp &= ~(PMU_CTL3_DVSEN |  PMU_CTL3_BYPASS);
        temp |= smpsmode;
        PMU_CTL3 = temp;
    }
}

/*!
    \brief      enter sleep mode (API_ID(0x0021U))
    \param[in]  sleepmodecmd:
                only one parameter can be selected which is shown as below:
      \arg        WFI_CMD: use WFI command
      \arg        WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_sleepmode(uint8_t sleepmodecmd)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_SLEEPMODE(sleepmodecmd)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0021U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* clear sleepdeep bit of Cortex-M7 system control register */
        SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

        /* select WFI or WFE command to enter sleep mode */
        if(WFI_CMD == sleepmodecmd) {
            __WFI();
        } else {
            __SEV();
            __WFE();
            __WFE();
        }
    }
}

/*!
    \brief      enter deepsleep mode (API_ID(0x0022U))
    \param[in]  deepsleepmodecmd:
                only one parameter can be selected which is shown as below:
      \arg        WFI_CMD: use WFI command
      \arg        WFE_CMD: use WFE command
    \param[out] none
    \retval     none
*/
void pmu_to_deepsleepmode(uint8_t deepsleepmodecmd)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_SLEEPMODE(deepsleepmodecmd)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0022U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* clear standby mode */
        PMU_CTL0 &= ~((uint32_t)(PMU_CTL0_STBMOD));

        /* set sleepdeep bit of Cortex-M7 system control register */
        SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

        /* select WFI or WFE command to enter deepsleep mode */
        if(WFI_CMD == deepsleepmodecmd) {
            __WFI();
        } else {
            __SEV();
            __WFE();
            __WFE();
        }
        /* reset sleepdeep bit of Cortex-M7 system control register */
        SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
    }
}

/*!
    \brief      enter standby mode (API_ID(0x0023U))
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
void pmu_to_standbymode(void)
{
    /* set stbmod bit */
    PMU_CTL0 |= PMU_CTL0_STBMOD;

    /* reset wakeup flag */
    PMU_CTL0 |= PMU_CTL0_WURST;

    /* set sleepdeep bit of Cortex-M7 system control register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    REG32(0xE000E010U) &= 0x00010004U;
    REG32(0xE000E180U) = 0xFF87FFFFU;
    REG32(0xE000E184U) = 0x7FFFFBFFU;
    REG32(0xE000E188U) = 0x9FFFFFF0U;
    REG32(0xE000E18CU) = 0xB577E043U;
    REG32(0xE000E190U) = 0x7FC70200U;
    REG32(0xE000E194U) = 0xFFFBFFFEU;
    REG32(0xE000E198U) = 0xEFFFFFFFU;
    REG32(0xE000E19CU) = 0x00000007U;

    /* enter standby mode */
    __WFI();
}

/*!
    \brief      enable wakeup pin (API_ID(0x0024U))
    \param[in]  wakeup_pin:
                one or more parameters can be selected which are shown as below:
      \arg        PMU_WAKEUP_PIN0: WKUP Pin 0
      \arg        PMU_WAKEUP_PIN1: WKUP Pin 1
      \arg        PMU_WAKEUP_PIN3: WKUP Pin 3
      \arg        PMU_WAKEUP_PIN5: WKUP Pin 5
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_enable(uint32_t wakeup_pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_WAKEUP_PIN(wakeup_pin)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0024U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        PMU_CS |= wakeup_pin;
    }
}

/*!
    \brief      disable wakeup pin (API_ID(0x0025U))
    \param[in]  wakeup_pin:
                one or more parameters can be selected which are shown as below:
      \arg        PMU_WAKEUP_PIN0: WKUP Pin 0
      \arg        PMU_WAKEUP_PIN1: WKUP Pin 1
      \arg        PMU_WAKEUP_PIN3: WKUP Pin 3
      \arg        PMU_WAKEUP_PIN5: WKUP Pin 5
    \param[out] none
    \retval     none
*/
void pmu_wakeup_pin_disable(uint32_t wakeup_pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_WAKEUP_PIN(wakeup_pin)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0025U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        PMU_CS &= ~(wakeup_pin);
    }
}

/*!
    \brief      enable backup domain write (API_ID(0x0026U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_BKPWEN;
}

/*!
    \brief      disable backup domain write (API_ID(0x0027U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_BKPWEN;
}

/*!
    \brief      enable backup voltage stabilizer (API_ID(0x0028U))
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
void pmu_backup_voltage_stabilizer_enable(void)
{
    PMU_CTL1 |= PMU_CTL1_BKPVSEN;
    while(RESET == (PMU_CTL1 & PMU_CTL1_BKPVSRF)) {
    }
}

/*!
    \brief      disable backup voltage stabilizer (API_ID(0x0029U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_voltage_stabilizer_disable(void)
{
    PMU_CTL1 &= ~PMU_CTL1_BKPVSEN;
}

/*!
    \brief      configure IRC counter before enter Deep-sleep mode (API_ID(0x002AU))
    \param[in]  wait_time: 0x0~0x1F, IRC counter before enter Deep-sleep mode
    \param[out] none
    \retval     none
*/
void pmu_enter_deepsleep_wait_time_config(uint32_t wait_time)
{
    /* check parameter */
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_ENTER_WAITTIME(wait_time)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x002AU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        uint32_t temp;
        temp = PMU_PAR;
        temp &= ~PMU_PAR_TSW_IRCCNT;
        temp |= (uint32_t)(wait_time << PAR_TSW_IRCCNT_OFFSET);
        PMU_PAR = temp;
    }
}

/*!
    \brief      configure IRC counter before exit Deep-sleep mode (API_ID(0x002BU))
    \param[in]  wait_time: 0x0~0xFFF, IRC counter before exit Deep-sleep mode
    \param[out] none
    \retval     none
*/
void pmu_exit_deepsleep_wait_time_config(uint32_t wait_time)
{
    /* check parameter */
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_EXIT_WAITTIME(wait_time)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x002BU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        uint32_t temp;
        temp = PMU_PAR;
        temp &= ~PMU_PAR_PMU_CNT;
        temp |= (uint32_t)(wait_time);
        PMU_PAR = temp;
    }
}

/*!
    \brief      enable CORE PDR circuit (API_ID(0x002CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_core_pdr_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_COREPDREN;
}

/*!
    \brief      disable CORE PDR circuit (API_ID(0x002DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_core_pdr_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_COREPDREN;
}

/*!
    \brief      enable CORE POR OFF output (API_ID(0x002EU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_core_por_off_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_COREPOROFFOUT;
}

/*!
    \brief      disable CORE POR OFF output (API_ID(0x002FU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_core_por_off_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_COREPOROFFOUT;
}

/*!
    \brief      enable CORE POR OFF output polarity negation (API_ID(0x0030U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_output_polarity_negation_enable(void)
{
    PMU_CTL0 |= PMU_CTL0_COREPOROFFP;
}

/*!
    \brief      disable CORE POR OFF output polarity negation (API_ID(0x0031U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_output_polarity_negation_disable(void)
{
    PMU_CTL0 &= ~PMU_CTL0_COREPOROFFP;
}

/*!
    \brief      select sram mode in deep-sleep (API_ID(0x0032U))
    \param[in]  sram_mode:
                only one parameter can be selected which is shown as below:
      \arg        PMU_DISABLE: disable
      \arg        PMU_PRECHARGE: select precharge
      \arg        PMU_RETENTION: select retention
    \param[out] none
    \retval     none
*/
void pmu_sram_mode_selection(uint32_t sram_mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SRAM_MODE(sram_mode)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0032U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        PMU_CTL0 &= ~PMU_CTL0_SRAM_MODE;
        PMU_CTL0 |= (sram_mode & PMU_CTL0_SRAM_MODE);
    }
}

/*!
    \brief      configure VUVD analog output filter length (API_ID(0x0033U))
    \param[in]  length: 0~255, filter length is configured as length*1024*Tpclk4
    \param[out] none
    \retval     none
*/
void pmu_vuvd_output_config(uint32_t length)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_FILTER_LENGTH(length)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0033U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t temp = (length & 0xFFU) << 8;
        PMU_CTL2 &= ~PMU_CTL2_VUVDO_DNF;
        PMU_CTL2 |= temp;
    }
}

/*!
    \brief      configure VOVD analog output filter length (API_ID(0x0034U))
    \param[in]  length: 0~255, filter length is configured as length*1024*Tpclk4
    \param[out] none
    \retval     none
*/
void pmu_vovd_output_config(uint32_t length)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_FILTER_LENGTH(length)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0034U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        PMU_CTL2 &= ~PMU_CTL2_VOVDO_DNF;
        PMU_CTL2 |= (length & 0xFFU);
    }
}

/*!
    \brief      enable MIPI LDO (API_ID(0x0035U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_mipi_ldo_enable(void)
{
    PMU_CTL3 |= PMU_CTL3_MIPI_LDO_EN;
}

/*!
    \brief      disable MIPI LDO (API_ID(0x0036U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_mipi_ldo_disable(void)
{
    PMU_CTL3 &= ~PMU_CTL3_MIPI_LDO_EN;
}

/*!
    \brief      enable MIPI power (API_ID(0x0037U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_mipi_power_enable(void)
{
    PMU_CTL3 |= PMU_CTL3_MIPISW;
}

/*!
    \brief      disable MIPI power (API_ID(0x0038U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_mipi_power_disable(void)
{
    PMU_CTL3 &= ~PMU_CTL3_MIPISW;
}

/*!
    \brief      enable MIPI output isolation (API_ID(0x0039U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_mipi_output_isolation_enable(void)
{
    PMU_CTL3 |= PMU_CTL3_MIPIHTEN;
}

/*!
    \brief      disable MIPI output isolation (API_ID(0x003AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_mipi_output_isolation_disable(void)
{
    PMU_CTL3 &= ~PMU_CTL3_MIPIHTEN;
}

/*!
    \brief      enable MIPI LDO bypass (API_ID(0x003BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_mipi_ldo_bypass_enable(void)
{
    PMU_CTL3 |= PMU_CTL3_MIPI_LDO_BYP;
}

/*!
    \brief      disable MIPI LDO bypass (API_ID(0x003CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_mipi_ldo_bypass_disable(void)
{
    PMU_CTL3 &= ~PMU_CTL3_MIPI_LDO_BYP;
}

/*!
    \brief      select MIPI LDO VDD09DSI PDR threshold (API_ID(0x003DU))
    \param[in]  threshold_value:
                only one parameter can be selected which is shown as below:
      \arg        PDR_FALLING_THRESHOLD0: PDR falling threshold is 0.775V, POR rising threshold is 0.8V
      \arg        PDR_FALLING_THRESHOLD1: PDR falling threshold is 0.675V, POR rising threshold is 0.7V
    \param[out] none
    \retval     none
*/
void pmu_vdd09dsi_pdr_threshold_selection(uint8_t threshold_value)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_THRESHOLD_VALUE(threshold_value)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x003DU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(threshold_value == PDR_FALLING_THRESHOLD0) {
            PMU_CTL3 &= ~PMU_CTL3_MIPI_PDR_LEV;
        } else {
            PMU_CTL3 |= PMU_CTL3_MIPI_PDR_LEV;
        }
    }
}

/*!
    \brief      enable MIPI LDO VDD09DSI PDR function (API_ID(0x003EU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vdd09dsi_pdr_enable(void)
{
    PMU_CTL3 |= PMU_CTL3_MIPI_PDR_EN;
}

/*!
    \brief      disable MIPI LDO VDD09DSI PDR function (API_ID(0x003FU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_vdd09dsi_pdr_disable(void)
{
    PMU_CTL3 &= ~PMU_CTL3_MIPI_PDR_EN;
}

/*!
    \brief      set VC_VOS voltage level (API_ID(0x0040U))
    \param[in]  voltage_level: Vcore voltage level, takes effect only when SYSCFG_PMCFG1 VOSCFGEN is set
      \arg        PMU_VC_VOS(mv): Vcore voltage mv millivolt, mv = 520 ~ 1080, 10mV step (e.g. PMU_VC_VOS(970) for 0.97V)
    \param[out] none
    \retval     none
*/
void pmu_vc_vos_set(uint32_t voltage_level)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_VC_VOS(voltage_level)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0040U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* check if VOSCFGEN bit is enabled */
        if(SYSCFG_PMCFG1 & SYSCFG_PMCFG1_VOSCFGEN) {
            uint32_t temp;
            temp = PMU_CTL4;
            temp &= ~PMU_CTL4_VC_VOS;
            temp |= voltage_level;
            PMU_CTL4 = temp;
        }
    }
}

/*!
    \brief      set MIPI_VC_VOS voltage level (API_ID(0x0041U))
    \param[in]  voltage_level: VCORE_DSI voltage level, takes effect only when SYSCFG_PMCFG1 VOSCFGEN is set
      \arg        PMU_MIPI_VC_VOS(mv): VCORE_DSI voltage mv millivolt, mv = 520 ~ 1080, 10mV step (e.g. PMU_MIPI_VC_VOS(900) for 0.90V)
    \param[out] none
    \retval     none
*/
void pmu_mipi_vc_vos_set(uint32_t voltage_level)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_MIPI_VC_VOS(voltage_level)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0041U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* check if VOSCFGEN bit is enabled */
        if(SYSCFG_PMCFG1 & SYSCFG_PMCFG1_VOSCFGEN) {
            uint32_t temp;
            temp = PMU_CTL4;
            temp &= ~PMU_CTL4_MIPI_VC_VOS;
            temp |= voltage_level;
            PMU_CTL4 = temp;
        }
    }
}

/*!
    \brief      clear flag bit (API_ID(0x0042U))
    \param[in]  flag_reset:
                only one parameter can be selected which is shown as below:
      \arg        PMU_FLAG_WAKEUP: wakeup flag
      \arg        PMU_FLAG_STANDBY: standby flag
      \arg        PMU_FLAG_RDYFALLF: record the occurrence of undervoltage reset on VDD09DSI
    \param[out] none
    \retval     none
*/
void pmu_flag_clear(uint32_t flag_reset)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_FLAG_RESET(flag_reset)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0042U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(flag_reset) {
        case PMU_FLAG_WAKEUP:
            PMU_CTL0 |= PMU_CTL0_WURST;
            break;
        case PMU_FLAG_STANDBY:
            PMU_CTL0 |= PMU_CTL0_STBRST;
            break;
        case PMU_FLAG_RDYFALLF:
            PMU_CTL3 |= PMU_CTL3_MIPI_RDY_FALL;
            break;
        default:
            /* Do nothing or add error handling */
            break;
        }
    }
}

/*!
    \brief      get flag state (API_ID(0x0043U))
    \param[in]  flag:
                only one parameter can be selected which is shown as below:
      \arg        PMU_FLAG_WAKEUP: wakeup flag
      \arg        PMU_FLAG_STANDBY: standby flag
      \arg        PMU_FLAG_LVDF: low voltage detector status flag
      \arg        PMU_FLAG_UVDF: record the undervoltage reset of the Vcore
      \arg        PMU_FLAG_VUVDF0: Vcore under voltage detector flag bit
      \arg        PMU_FLAG_VOVDF1: Vcore over voltage detector flag bit after digital filter
      \arg        PMU_FLAG_VUVDF1: Vcore under voltage detector flag bit after digital filter
      \arg        PMU_FLAG_VAVDF: VDDA analog voltage detector voltage output on VDDA flag
      \arg        PMU_FLAG_VOVDF0: peripheral voltage on Vcore detector flag
      \arg        PMU_FLAG_PRDYN: the internal memory instance power supplies are stable after returning from retention mode
      \arg        PMU_FLAG_BKPVSRF: backup voltage stabilizer ready flag
      \arg        PMU_FLAG_VBATLF: VBAT level monitoring versus low threshold
      \arg        PMU_FLAG_VBATHF: VBAT level monitoring versus high threshold
      \arg        PMU_FLAG_TEMPLF: temperature level monitoring versus low threshold
      \arg        PMU_FLAG_TEMPHF: temperature level monitoring versus high threshold
      \arg        PMU_FLAG_RDYFALLF: record the occurrence of undervoltage reset on VDD09DSI
      \arg        PMU_FLAG_MIPIHTF: MIPI power switch ack flag
      \arg        PMU_FLAG_USB33RF: USB supply ready flag bit
      \arg        PMU_FLAG_RDYF: the MIPI_LDO output voltage ready signal
      \arg        PMU_FLAG_PKCAUHTF: PKCAU power switch ack flag
      \arg        PMU_FLAG_ESCHTF: ESC power switch ack flag
    \param[out] none
    \retval     FlagStatus SET or RESET
*/
FlagStatus pmu_flag_get(uint32_t flag)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_FLAG(flag)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0043U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {

        if(PMU_REG_VAL(flag) & BIT(PMU_BIT_POS(flag))) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    return reval;
}
