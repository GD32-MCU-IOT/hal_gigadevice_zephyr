/*!
    \file  system_gd32h77x_78x.c
    \brief CMSIS Cortex-M7 Device Peripheral Access Layer Source File for
           gd32h77x_78x Device Series
*/

/*
 * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
 * Copyright (c) 2026, GigaDevice Semiconductor Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* This file refers the CMSIS standard, some adjustments are made according to GigaDevice chips */

#include "gd32h77x_78x.h"

/* system frequency define */
#define __IRC64M            (IRC64M_VALUE)           /* internal 64 MHz RC oscillator frequency */
#define __HXTAL             (HXTAL_VALUE)            /* high speed crystal oscillator frequency */
#define __LPIRC4M           (LPIRC4M_VALUE)          /* low power internal 4 MHz RC oscillator frequency */
#define __SYS_OSC_CLK       (__IRC64M)               /* main oscillator frequency */

#define VECT_TAB_OFFSET     (uint32_t)0x00           /* vector table base offset */
#define RCU_APB4EN_SYSCFG   (uint32_t)0x01           /* enable SYSCFG clk */

/* select a system clock by uncommenting the following line */
#if defined(GD32H78X_SUPPORT_MAX_750M)
//#define __SYSTEM_CLOCK_LPIRC4M                  (__LPIRC4M)
//#define __SYSTEM_CLOCK_IRC64M                   (__IRC64M)
//#define __SYSTEM_CLOCK_HXTAL                    (__HXTAL)
//#define __SYSTEM_CLOCK_200M_PLL0_HXTAL          (uint32_t)(200000000)
//#define __SYSTEM_CLOCK_400M_PLL0_HXTAL          (uint32_t)(400000000)
//#define __SYSTEM_CLOCK_480M_PLL0_IRC64M         (uint32_t)(480000000)
//#define __SYSTEM_CLOCK_480M_PLL0_HXTAL          (uint32_t)(480000000)
//#define __SYSTEM_CLOCK_600M_PLL0_IRC64M         (uint32_t)(600000000)
//#define __SYSTEM_CLOCK_600M_PLL0_HXTAL          (uint32_t)(600000000)
//#define __SYSTEM_CLOCK_700M_PLL0_IRC64M         (uint32_t)(700000000)
//#define __SYSTEM_CLOCK_700M_PLL0_HXTAL          (uint32_t)(700000000)
//#define __SYSTEM_CLOCK_750M_PLL0_IRC64M         (uint32_t)(750000000)
#define __SYSTEM_CLOCK_750M_PLL0_HXTAL          (uint32_t)(750000000)
#elif defined(GD32H78X_SUPPORT_MAX_700M)
//#define __SYSTEM_CLOCK_LPIRC4M                  (__LPIRC4M)
//#define __SYSTEM_CLOCK_IRC64M                   (__IRC64M)
//#define __SYSTEM_CLOCK_HXTAL                    (__HXTAL)
//#define __SYSTEM_CLOCK_200M_PLL0_HXTAL          (uint32_t)(200000000)
//#define __SYSTEM_CLOCK_400M_PLL0_HXTAL          (uint32_t)(400000000)
//#define __SYSTEM_CLOCK_480M_PLL0_IRC64M         (uint32_t)(480000000)
//#define __SYSTEM_CLOCK_480M_PLL0_HXTAL          (uint32_t)(480000000)
//#define __SYSTEM_CLOCK_600M_PLL0_IRC64M         (uint32_t)(600000000)
//#define __SYSTEM_CLOCK_600M_PLL0_HXTAL          (uint32_t)(600000000)
//#define __SYSTEM_CLOCK_700M_PLL0_IRC64M         (uint32_t)(700000000)
#define __SYSTEM_CLOCK_700M_PLL0_HXTAL          (uint32_t)(700000000)
#else
//#define __SYSTEM_CLOCK_LPIRC4M                  (__LPIRC4M)
//#define __SYSTEM_CLOCK_IRC64M                   (__IRC64M)
//#define __SYSTEM_CLOCK_HXTAL                    (__HXTAL)
//#define __SYSTEM_CLOCK_200M_PLL0_HXTAL          (uint32_t)(200000000)
//#define __SYSTEM_CLOCK_400M_PLL0_HXTAL          (uint32_t)(400000000)
//#define __SYSTEM_CLOCK_480M_PLL0_IRC64M         (uint32_t)(480000000)
//#define __SYSTEM_CLOCK_480M_PLL0_HXTAL          (uint32_t)(480000000)
//#define __SYSTEM_CLOCK_600M_PLL0_IRC64M         (uint32_t)(600000000)
#define __SYSTEM_CLOCK_600M_PLL0_HXTAL          (uint32_t)(600000000)
#endif /* GD32H78X_SUPPORT_MAX_750M */

/*
Note: the power mode need to match the mcu selection and external power supply circuit.
        for 100-pin/144-pin mcu, the power mode only supports PMU_BYPASS.
        for 176-pin mcu, the power mode supports PMU_DIRECT_SMPS_SUPPLY and PMU_BYPASS.
    according to the selected mcu and external power supply circuit to uncomment
the following macro SEL_PMU_SMPS_MODE.
*/
//#define SEL_PMU_SMPS_MODE   PMU_DIRECT_SMPS_SUPPLY
//#define SEL_PMU_SMPS_MODE   PMU_BYPASS

#define SEL_IRC64MDIV       0x00U
#define SEL_HXTAL           0x01U
#define SEL_LPIRC4M         0x02U
#define SEL_PLL0P           0x03U

#define PLL0PSC_REG_OFFSET   0U
#define PLL0N_REG_OFFSET     6U
#define PLL0P_REG_OFFSET     16U
#define PLL0Q_REG_OFFSET     0U
#define PLL0R_REG_OFFSET     24U

/* set the system clock frequency and declare the system clock configuration function */
#ifdef __SYSTEM_CLOCK_IRC64M
uint32_t SystemCoreClock = __SYSTEM_CLOCK_IRC64M;
static void system_clock_64m_irc64m(void);
#elif defined (__SYSTEM_CLOCK_480M_PLL0_IRC64M)
#define PLL0PSC              16U
#define PLL0N                (120U - 1U)
#define PLL0P                (1U - 1U)
#define PLL0Q                (2U - 1U)
#define PLL0R                (2U - 1U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_480M_PLL0_IRC64M;
static void system_clock_480m_irc64m(void);
#elif defined (__SYSTEM_CLOCK_600M_PLL0_IRC64M)
#define PLL0PSC              16U
#define PLL0N                (150U - 1U)
#define PLL0P                (1U - 1U)
#define PLL0Q                (2U - 1U)
#define PLL0R                (2U - 1U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_600M_PLL0_IRC64M;
static void system_clock_600m_irc64m(void);
#elif defined (__SYSTEM_CLOCK_700M_PLL0_IRC64M)
#define PLL0PSC              16U
#define PLL0N                (175U - 1U)
#define PLL0P                (1U - 1U)
#define PLL0Q                (2U - 1U)
#define PLL0R                (2U - 1U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_700M_PLL0_IRC64M;
static void system_clock_700m_irc64m(void);
#elif defined (__SYSTEM_CLOCK_750M_PLL0_IRC64M)
#define PLL0PSC              32U
#define PLL0N                (375U - 1U)
#define PLL0P                (1U - 1U)
#define PLL0Q                (2U - 1U)
#define PLL0R                (2U - 1U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_750M_PLL0_IRC64M;
static void system_clock_750m_irc64m(void);

#elif defined (__SYSTEM_CLOCK_LPIRC4M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_LPIRC4M;
static void system_clock_4m_lpirc4m(void);

#elif defined (__SYSTEM_CLOCK_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_HXTAL;
static void system_clock_hxtal(void);
#elif defined (__SYSTEM_CLOCK_200M_PLL0_HXTAL)
#define PLL0PSC              5U
#define PLL0N               (40U - 1U)
#define PLL0P               (1U - 1U)
#define PLL0Q               (2U - 1U)
#define PLL0R               (2U - 1U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_200M_PLL0_HXTAL;
static void system_clock_200m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_400M_PLL0_HXTAL)
#define PLL0PSC              5U
#define PLL0N               (80U - 1U)
#define PLL0P               (1U - 1U)
#define PLL0Q               (2U - 1U)
#define PLL0R               (2U - 1U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_400M_PLL0_HXTAL;
static void system_clock_400m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_480M_PLL0_HXTAL)
#define PLL0PSC              5U
#define PLL0N               (96U - 1U)
#define PLL0P               (1U - 1U)
#define PLL0Q               (2U - 1U)
#define PLL0R               (2U - 1U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_480M_PLL0_HXTAL;
static void system_clock_480m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_600M_PLL0_HXTAL)
#define PLL0PSC              5U
#define PLL0N                (120U - 1U)
#define PLL0P                (1U - 1U)
#define PLL0Q                (2U - 1U)
#define PLL0R                (2U - 1U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_600M_PLL0_HXTAL;
static void system_clock_600m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_700M_PLL0_HXTAL)
#define PLL0PSC              5U
#define PLL0N                (140U - 1U)
#define PLL0P                (1U - 1U)
#define PLL0Q                (2U - 1U)
#define PLL0R                (2U - 1U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_700M_PLL0_HXTAL;
static void system_clock_700m_hxtal(void);
#elif defined (__SYSTEM_CLOCK_750M_PLL0_HXTAL)
#define PLL0PSC              5U
#define PLL0N                (150U - 1U)
#define PLL0P                (1U - 1U)
#define PLL0Q                (2U - 1U)
#define PLL0R                (2U - 1U)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_750M_PLL0_HXTAL;
static void system_clock_750m_hxtal(void);
#endif /* __SYSTEM_CLOCK_IRC64M */

/* configure the system clock */
static void system_clock_config(void);

/*!
    \brief      setup the microcontroller system, initialize the system
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
void SystemInit(void)
{
    /* FPU settings */
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1U)
    /* set CP10 and CP11 Full Access */
    SCB->CPACR |= (uint32_t)((0x03U << 10U * 2U) | (0x03U << 11U * 2U));
#endif
    SCB_EnableDCache();
    SCB_DisableDCache();
    /* enable IRC64M */
    RCU_CTL |= RCU_CTL_IRC64MEN;
    while(0U == (RCU_CTL & RCU_CTL_IRC64MSTB)) {
    }

    RCU_CFG0 &= ~RCU_CFG0_SCS;

    /* reset RCU */
    /* reset HXTALEN, CKMEN, PLL0EN, PLL1EN, PLL2EN, PLLUSB0 and PLLUSB1 bits */
    RCU_CTL &= ~(RCU_CTL_HXTALEN | RCU_CTL_CKMEN | RCU_CTL_PLL0EN | RCU_CTL_PLL1EN | RCU_CTL_PLL2EN | RCU_CTL_HXTALBPS);
    RCU_ADDCTL1 &= ~(RCU_ADDCTL1_PLLUSBHS0EN | RCU_ADDCTL1_LPIRC4MEN);
    /* reset CFG0, CFG1, CFG2, CFG3 registers */
    RCU_CFG0 &= ~(RCU_CFG0_APB1PSC | RCU_CFG0_APB2PSC | RCU_CFG0_APB3PSC | RCU_CFG0_APB4PSC | RCU_CFG0_AHBPSC |
                  RCU_CFG0_I2C0SEL | RCU_CFG0_SCS | RCU_CFG0_RTCDIV);
    RCU_CFG1 &= ~(RCU_CFG1_HPDFSEL | RCU_CFG1_TIMERSEL | RCU_CFG1_PERSEL |
                  RCU_CFG1_RSPDIFSEL | RCU_CFG1_USART0SEL | RCU_CFG1_USART1SEL | RCU_CFG1_USART2SEL | RCU_CFG1_USART5SEL | RCU_CFG1_PLL2RDIV);
    RCU_CFG2 &= ~(RCU_CFG2_SAI2B1SEL | RCU_CFG2_SAI2B0SEL | RCU_CFG2_SAI1_3SEL | RCU_CFG2_SAI0SEL |
                  RCU_CFG2_CKOUT0SEL | RCU_CFG2_CKOUT1SEL | RCU_CFG2_CKOUT0DIV | RCU_CFG2_CKOUT1DIV);
    RCU_CFG3 &= ~(RCU_CFG3_ADC01SEL | RCU_CFG3_ADC2SEL | RCU_CFG3_SDIO1SEL
                  | RCU_CFG3_I2C3SEL | RCU_CFG3_I2C2SEL | RCU_CFG3_I2C1SEL);
    RCU_CFG4 &= ~(RCU_CFG4_EXMCSEL | RCU_CFG4_SDIO0SEL);
    RCU_CFG5 &= ~(RCU_CFG5_SPI0SEL | RCU_CFG5_SPI1SEL | RCU_CFG5_SPI2SEL |
                  RCU_CFG5_SPI3SEL | RCU_CFG5_SPI4SEL | RCU_CFG5_SPI5SEL);
    /* disable all interrupts */
    RCU_INT = 0x14FF0000U;
    RCU_ADDINT = 0x00700000U;
    /* reset all PLL parameter */
    RCU_PLL0 = 0x01002020U;
    RCU_PLL1 = 0x01012020U;
    RCU_PLL2 = 0x01012020U;
    RCU_PLLALL = 0x00000000U;
    RCU_PLLADDCTL = 0x00010101U;
    RCU_PLLUSBCFG = 0x00000000U;
    RCU_PLL0FRA = 0x00000000U;
    RCU_PLL1FRA = 0x00000000U;
    RCU_PLL2FRA = 0x00000000U;
    /* reset CFG6 register */
    RCU_CFG6 = 0x00000000U;
    /* reset CKFMCFG0 register */
    RCU_CKFMCFG0 = 0x00000000U;
    /* reset CKFMCFG1 register */
    RCU_CKFMCFG1 = 0x00000000U;
    /* reset CKFMCFG2 register */
    RCU_CKFMCFG2 = 0x00000000U;

#if (defined(GD32H78X_SUPPORT_MAX_750M))
    rcu_periph_clock_enable(RCU_PMU);
    /* power supply must be bypass mode and the external supply voltage is 0.97V */
    pmu_smps_supply_config(PMU_BYPASS);
#else
#if defined (SEL_PMU_SMPS_MODE)
    rcu_periph_clock_enable(RCU_PMU);
    /* power supply config */
    pmu_smps_supply_config(SEL_PMU_SMPS_MODE);
#endif
#endif

    /* configure system clock */
    system_clock_config();

    /* set Vcore undervoltage protection to 0.8 V */
    rcu_periph_clock_enable(RCU_PMU);
    pmu_uvd_disable();
    pmu_uvd_select(PMU_UVDT_0);
    pmu_core_pdr_enable();
    pmu_uvd_enable();
}

/*!
    \brief      configure the system clock
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_config(void)
{
#ifdef __SYSTEM_CLOCK_IRC64M
    system_clock_64m_irc64m();
#elif defined (__SYSTEM_CLOCK_480M_PLL0_IRC64M)
    system_clock_480m_irc64m();
#elif defined (__SYSTEM_CLOCK_600M_PLL0_IRC64M)
    system_clock_600m_irc64m();
#elif defined (__SYSTEM_CLOCK_700M_PLL0_IRC64M)
    system_clock_700m_irc64m();
#elif defined (__SYSTEM_CLOCK_750M_PLL0_IRC64M)
    system_clock_750m_irc64m();

#elif defined (__SYSTEM_CLOCK_LPIRC4M)
    system_clock_4m_lpirc4m();

#elif defined (__SYSTEM_CLOCK_HXTAL)
    system_clock_hxtal();
#elif defined (__SYSTEM_CLOCK_200M_PLL0_HXTAL)
    system_clock_200m_hxtal();
#elif defined (__SYSTEM_CLOCK_400M_PLL0_HXTAL)
    system_clock_400m_hxtal();
#elif defined (__SYSTEM_CLOCK_480M_PLL0_HXTAL)
    system_clock_480m_hxtal();
#elif defined (__SYSTEM_CLOCK_600M_PLL0_HXTAL)
    system_clock_600m_hxtal();
#elif defined (__SYSTEM_CLOCK_700M_PLL0_HXTAL)
    system_clock_700m_hxtal();
#elif defined (__SYSTEM_CLOCK_750M_PLL0_HXTAL)
    system_clock_750m_hxtal();
#endif /* __SYSTEM_CLOCK_IRC64M */
}

#ifdef __SYSTEM_CLOCK_IRC64M
/*!
    \brief      configure the system clock to 64M by IRC64M
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_64m_irc64m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* add wait state */
    NVMC_PERFCTL = (NVMC_PERFCTL & (~NVMC_PERFCTL_WSCNT)) | PERFCTL_WSCNT_1;
    /* enable IRC64M */
    RCU_CTL |= RCU_CTL_IRC64MEN;

    /* wait until IRC64M is stable or the startup time is longer than IRC64M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC64MSTB);
    } while((0U == stab_flag) && (IRC64M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC64MSTB)) {
        while(1) {
        }
    }

    /* AHB = SYSCLK / 1 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB4 = AHB / 1 */
    RCU_CFG0 |= RCU_APB4_CKAHB_DIV1;
    /* APB3 = AHB / 1 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV1;
    /* APB2 = AHB / 1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB / 1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    reg_temp = RCU_CFG0;
    /* select IRC64M as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_IRC64MDIV;
    RCU_CFG0 = reg_temp;

    /* wait until IRC64M is selected as system clock */
    while(RCU_SCSS_IRC64MDIV != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_480M_PLL0_IRC64M)
/*!
    \brief      configure the system clock to 480M by PLL0 which selects IRC64M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_480m_irc64m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* add wait state */
    NVMC_PERFCTL = (NVMC_PERFCTL & (~NVMC_PERFCTL_WSCNT)) | PERFCTL_WSCNT_4;

    /* enable IRC64M */
    RCU_CTL |= RCU_CTL_IRC64MEN;

    /* wait until IRC64M is stable or the startup time is longer than IRC64M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC64MSTB);
    } while((0U == stab_flag) && (IRC64M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC64MSTB)) {
        while(1) {
        }
    }

    /* IRC64M is already stable */
    /* AHB = SYSCLK / 2 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
    /* APB4 = AHB / 2 */
    RCU_CFG0 |= RCU_APB4_CKAHB_DIV2;
    /* APB3 = AHB / 2 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV2;
    /* APB2 = AHB / 1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB / 2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* PLL0 select IRC64MDIV, config PLL0 input and output range */
    RCU_PLLALL &= ~(RCU_PLLALL_PLLSEL | RCU_PLLALL_PLL0VCOSEL | RCU_PLLALL_PLL0RNG);
    RCU_PLLALL |= (RCU_PLLSRC_IRC64MDIV | RCU_PLL0RNG_4M_8M);

    /* PLL0P = IRC64MDIV / 16 * 120 / 1 = 480 MHz */
    RCU_PLL0 &= ~(RCU_PLL0_PLL0N | RCU_PLL0_PLL0PSC | RCU_PLL0_PLL0P | RCU_PLL0_PLL0R | RCU_PLL0_PLLSTBSRC);
    RCU_PLL0 |= ((PLL0N << PLL0N_REG_OFFSET) | (PLL0PSC << PLL0PSC_REG_OFFSET) | (PLL0P << PLL0P_REG_OFFSET) | (PLL0R << PLL0R_REG_OFFSET));
    RCU_PLLADDCTL &= ~(RCU_PLLADDCTL_PLL0Q);
    RCU_PLLADDCTL |= (PLL0Q << PLL0Q_REG_OFFSET);

    /* enable PLL0P, PLL0Q, PLL0R */
    RCU_PLLADDCTL |= RCU_PLLADDCTL_PLL0PEN | RCU_PLLADDCTL_PLL0QEN | RCU_PLLADDCTL_PLL0REN;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL0 as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_600M_PLL0_IRC64M)
/*!
    \brief      configure the system clock to 600M by PLL0 which selects IRC64M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_600m_irc64m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* add wait state */
    NVMC_PERFCTL = (NVMC_PERFCTL & (~NVMC_PERFCTL_WSCNT)) | PERFCTL_WSCNT_5;

    /* enable IRC64M */
    RCU_CTL |= RCU_CTL_IRC64MEN;

    /* wait until IRC64M is stable or the startup time is longer than IRC64M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC64MSTB);
    } while((0U == stab_flag) && (IRC64M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC64MSTB)) {
        while(1) {
        }
    }

    /* IRC64M is already stable */
    /* AHB = SYSCLK / 2 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
    /* APB4 = AHB / 2 */
    RCU_CFG0 |= RCU_APB4_CKAHB_DIV2;
    /* APB3 = AHB / 2 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV2;
    /* APB2 = AHB / 1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB / 2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* PLL0 select IRC64MDIV, config PLL0 input and output range */
    RCU_PLLALL &= ~(RCU_PLLALL_PLLSEL | RCU_PLLALL_PLL0VCOSEL | RCU_PLLALL_PLL0RNG);
    RCU_PLLALL |= (RCU_PLLSRC_IRC64MDIV | RCU_PLL0RNG_4M_8M);

    /* PLL0P = IRC64MDIV / 16 * 150 / 1 = 600 MHz */
    RCU_PLL0 &= ~(RCU_PLL0_PLL0N | RCU_PLL0_PLL0PSC | RCU_PLL0_PLL0P | RCU_PLL0_PLL0R | RCU_PLL0_PLLSTBSRC);
    RCU_PLL0 |= ((PLL0N << PLL0N_REG_OFFSET) | (PLL0PSC << PLL0PSC_REG_OFFSET) | (PLL0P << PLL0P_REG_OFFSET) | (PLL0R << PLL0R_REG_OFFSET));
    RCU_PLLADDCTL &= ~(RCU_PLLADDCTL_PLL0Q);
    RCU_PLLADDCTL |= (PLL0Q << PLL0Q_REG_OFFSET);

    /* enable PLL0P, PLL0Q, PLL0R */
    RCU_PLLADDCTL |= RCU_PLLADDCTL_PLL0PEN | RCU_PLLADDCTL_PLL0QEN | RCU_PLLADDCTL_PLL0REN;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL0 as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_700M_PLL0_IRC64M)
/*!
    \brief      configure the system clock to 700M by PLL0 which selects IRC64M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_700m_irc64m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* add wait state */
    NVMC_PERFCTL = (NVMC_PERFCTL & (~NVMC_PERFCTL_WSCNT)) | PERFCTL_WSCNT_6;

    /* enable IRC64M */
    RCU_CTL |= RCU_CTL_IRC64MEN;

    /* wait until IRC64M is stable or the startup time is longer than IRC64M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC64MSTB);
    } while((0U == stab_flag) && (IRC64M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC64MSTB)) {
        while(1) {
        }
    }

    /* IRC64M is already stable */
    /* AHB = SYSCLK / 2 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
    /* APB4 = AHB / 2 */
    RCU_CFG0 |= RCU_APB4_CKAHB_DIV2;
    /* APB3 = AHB / 2 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV2;
    /* APB2 = AHB / 1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB / 2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* PLL0 select IRC64MDIV, config PLL0 input and output range */
    RCU_PLLALL &= ~(RCU_PLLALL_PLLSEL | RCU_PLLALL_PLL0VCOSEL | RCU_PLLALL_PLL0RNG);
    RCU_PLLALL |= (RCU_PLLSRC_IRC64MDIV | RCU_PLL0RNG_4M_8M);

    /* PLL0P = IRC64MDIV / 16 * 175 / 1 = 700 MHz */
    RCU_PLL0 &= ~(RCU_PLL0_PLL0N | RCU_PLL0_PLL0PSC | RCU_PLL0_PLL0P | RCU_PLL0_PLL0R | RCU_PLL0_PLLSTBSRC);
    RCU_PLL0 |= ((PLL0N << PLL0N_REG_OFFSET) | (PLL0PSC << PLL0PSC_REG_OFFSET) | (PLL0P << PLL0P_REG_OFFSET) | (PLL0R << PLL0R_REG_OFFSET));
    RCU_PLLADDCTL &= ~(RCU_PLLADDCTL_PLL0Q);
    RCU_PLLADDCTL |= (PLL0Q << PLL0Q_REG_OFFSET);

    /* enable PLL0P, PLL0Q, PLL0R */
    RCU_PLLADDCTL |= RCU_PLLADDCTL_PLL0PEN | RCU_PLLADDCTL_PLL0QEN | RCU_PLLADDCTL_PLL0REN;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL0 as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_750M_PLL0_IRC64M)
/*!
    \brief      configure the system clock to 750M by PLL0 which selects IRC64M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_750m_irc64m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* add wait state */
    NVMC_PERFCTL = (NVMC_PERFCTL & (~NVMC_PERFCTL_WSCNT)) | PERFCTL_WSCNT_7;

    /* enable IRC64M */
    RCU_CTL |= RCU_CTL_IRC64MEN;

    /* wait until IRC64M is stable or the startup time is longer than IRC64M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_IRC64MSTB);
    } while((0U == stab_flag) && (IRC64M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_IRC64MSTB)) {
        while(1) {
        }
    }

    /* IRC64M is already stable */
    /* AHB = SYSCLK / 2 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
    /* APB4 = AHB / 2 */
    RCU_CFG0 |= RCU_APB4_CKAHB_DIV2;
    /* APB3 = AHB / 2 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV2;
    /* APB2 = AHB / 1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB / 2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* PLL0 select IRC64MDIV, config PLL0 input and output range */
    RCU_PLLALL &= ~(RCU_PLLALL_PLLSEL | RCU_PLLALL_PLL0VCOSEL | RCU_PLLALL_PLL0RNG);
    RCU_PLLALL |= (RCU_PLLSRC_IRC64MDIV | RCU_PLL0RNG_2M_4M);

    /* PLL0P = IRC64MDIV / 32 * 375 / 1 = 750 MHz */
    RCU_PLL0 &= ~(RCU_PLL0_PLL0N | RCU_PLL0_PLL0PSC | RCU_PLL0_PLL0P | RCU_PLL0_PLL0R | RCU_PLL0_PLLSTBSRC);
    RCU_PLL0 |= ((PLL0N << PLL0N_REG_OFFSET) | (PLL0PSC << PLL0PSC_REG_OFFSET) | (PLL0P << PLL0P_REG_OFFSET) | (PLL0R << PLL0R_REG_OFFSET));
    RCU_PLLADDCTL &= ~(RCU_PLLADDCTL_PLL0Q);
    RCU_PLLADDCTL |= (PLL0Q << PLL0Q_REG_OFFSET);

    /* enable PLL0P, PLL0Q, PLL0R */
    RCU_PLLADDCTL |= RCU_PLLADDCTL_PLL0PEN | RCU_PLLADDCTL_PLL0QEN | RCU_PLLADDCTL_PLL0REN;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL0 as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_LPIRC4M)
/*!
    \brief      configure the system clock to LPIRC4M
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_4m_lpirc4m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* add wait state */
    NVMC_PERFCTL = (NVMC_PERFCTL & (~NVMC_PERFCTL_WSCNT)) | PERFCTL_WSCNT_1;

    /* enable LPIRC4M */
    RCU_ADDCTL1 |= RCU_ADDCTL1_LPIRC4MEN;

    /* wait until LPIRC4M is stable or the startup time is longer than LPIRC4M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_ADDCTL1 & RCU_ADDCTL1_LPIRC4MSTB);
    } while((0U == stab_flag) && (LPIRC4M_STARTUP_TIMEOUT != timeout));
    /* if fail */
    if(0U == (RCU_ADDCTL1 & RCU_ADDCTL1_LPIRC4MSTB)) {
        while(1) {
        }
    }

    /* LPIRC4M is stable */
    /* AHB = SYSCLK / 1*/
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB4 = AHB / 1 */
    RCU_CFG0 |= RCU_APB4_CKAHB_DIV1;
    /* APB3 = AHB / 1 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV1;
    /* APB2 = AHB / 1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB / 1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    reg_temp = RCU_CFG0;
    /* select LPIRC4M as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_LPIRC4M;
    RCU_CFG0 = reg_temp;

    /* wait until LPIRC4M is selected as system clock */
    while(RCU_SCSS_LPIRC4M != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_HXTAL)
/*!
    \brief      configure the system clock to HXTAL
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* add wait state */
    NVMC_PERFCTL = (NVMC_PERFCTL & (~NVMC_PERFCTL_WSCNT)) | PERFCTL_WSCNT_1;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));
    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    /* HXTAL is stable */
    /* AHB = SYSCLK / 1*/
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB4 = AHB / 1 */
    RCU_CFG0 |= RCU_APB4_CKAHB_DIV1;
    /* APB3 = AHB / 1 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV1;
    /* APB2 = AHB / 1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB / 1 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    reg_temp = RCU_CFG0;
    /* select HXTAL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_HXTAL;
    RCU_CFG0 = reg_temp;

    /* wait until HXTAL is selected as system clock */
    while(RCU_SCSS_HXTAL != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_200M_PLL0_HXTAL)
/*!
    \brief      configure the system clock to 200M by PLL0 which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_200m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* add wait state */
    NVMC_PERFCTL = (NVMC_PERFCTL & (~NVMC_PERFCTL_WSCNT)) | PERFCTL_WSCNT_3;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));
    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    /* HXTAL is stable */
    /* AHB = SYSCLK / 1 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB4 = AHB / 2 */
    RCU_CFG0 |= RCU_APB4_CKAHB_DIV2;
    /* APB3 = AHB / 2 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV2;
    /* APB2 = AHB / 1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB / 2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* PLL0 select HXTAL, configure PLL0 input and output range */
    RCU_PLLALL &= ~(RCU_PLLALL_PLLSEL | RCU_PLLALL_PLL0VCOSEL | RCU_PLLALL_PLL0RNG);
    RCU_PLLALL |= (RCU_PLLSRC_HXTAL | RCU_PLL0RNG_4M_8M);

    /* PLL0P = HXTAL / 5 * 40 = 200 MHz */
    RCU_PLL0 &= ~(RCU_PLL0_PLL0N | RCU_PLL0_PLL0PSC | RCU_PLL0_PLL0P | RCU_PLL0_PLL0R | RCU_PLL0_PLLSTBSRC);
    RCU_PLL0 |= ((PLL0N << PLL0N_REG_OFFSET) | (PLL0PSC << PLL0PSC_REG_OFFSET) | (PLL0P << PLL0P_REG_OFFSET) | (PLL0R << PLL0R_REG_OFFSET));
    RCU_PLLADDCTL &= ~(RCU_PLLADDCTL_PLL0Q);
    RCU_PLLADDCTL |= (PLL0Q << PLL0Q_REG_OFFSET);

    /* enable PLL0P, PLL0Q, PLL0R */
    RCU_PLLADDCTL |= RCU_PLLADDCTL_PLL0PEN | RCU_PLLADDCTL_PLL0QEN | RCU_PLLADDCTL_PLL0REN;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL0 as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_400M_PLL0_HXTAL)
/*!
    \brief      configure the system clock to 400M by PLL0 which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_400m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* add wait state */
    NVMC_PERFCTL = (NVMC_PERFCTL & (~NVMC_PERFCTL_WSCNT)) | PERFCTL_WSCNT_3;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));
    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    /* HXTAL is stable */
    /* AHB = SYSCLK / 2 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
    /* APB4 = AHB / 2 */
    RCU_CFG0 |= RCU_APB4_CKAHB_DIV2;
    /* APB3 = AHB / 2 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV2;
    /* APB2 = AHB / 1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB / 2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* PLL0 select HXTAL, configure PLL0 input and output range */
    RCU_PLLALL &= ~(RCU_PLLALL_PLLSEL | RCU_PLLALL_PLL0VCOSEL | RCU_PLLALL_PLL0RNG);
    RCU_PLLALL |= (RCU_PLLSRC_HXTAL | RCU_PLL0RNG_4M_8M);

    /* PLL0P = HXTAL / 5 * 80 = 400 MHz */
    RCU_PLL0 &= ~(RCU_PLL0_PLL0N | RCU_PLL0_PLL0PSC | RCU_PLL0_PLL0P | RCU_PLL0_PLL0R | RCU_PLL0_PLLSTBSRC);
    RCU_PLL0 |= ((PLL0N << PLL0N_REG_OFFSET) | (PLL0PSC << PLL0PSC_REG_OFFSET) | (PLL0P << PLL0P_REG_OFFSET) | (PLL0R << PLL0R_REG_OFFSET));
    RCU_PLLADDCTL &= ~(RCU_PLLADDCTL_PLL0Q);
    RCU_PLLADDCTL |= (PLL0Q << PLL0Q_REG_OFFSET);

    /* enable PLL0P, PLL0Q, PLL0R */
    RCU_PLLADDCTL |= RCU_PLLADDCTL_PLL0PEN | RCU_PLLADDCTL_PLL0QEN | RCU_PLLADDCTL_PLL0REN;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL0 as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_480M_PLL0_HXTAL)
/*!
    \brief      configure the system clock to 480M by PLL0 which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_480m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* add wait state */
    NVMC_PERFCTL = (NVMC_PERFCTL & (~NVMC_PERFCTL_WSCNT)) | PERFCTL_WSCNT_4;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));
    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    /* HXTAL is stable */
    /* AHB = SYSCLK / 2 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
    /* APB4 = AHB / 2 */
    RCU_CFG0 |= RCU_APB4_CKAHB_DIV2;
    /* APB3 = AHB / 2 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV2;
    /* APB2 = AHB / 1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB / 2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* PLL select HXTAL, configure PLL0 input and output range */
    RCU_PLLALL &= ~(RCU_PLLALL_PLLSEL | RCU_PLLALL_PLL0VCOSEL | RCU_PLLALL_PLL0RNG);
    RCU_PLLALL |= (RCU_PLLSRC_HXTAL | RCU_PLL0RNG_4M_8M);

    /* PLL0P = HXTAL / 5 * 96 = 480 MHz */
    RCU_PLL0 &= ~(RCU_PLL0_PLL0N | RCU_PLL0_PLL0PSC | RCU_PLL0_PLL0P | RCU_PLL0_PLL0R | RCU_PLL0_PLLSTBSRC);
    RCU_PLL0 |= ((PLL0N << PLL0N_REG_OFFSET) | (PLL0PSC << PLL0PSC_REG_OFFSET) | (PLL0P << PLL0P_REG_OFFSET) | (PLL0R << PLL0R_REG_OFFSET));
    RCU_PLLADDCTL &= ~(RCU_PLLADDCTL_PLL0Q);
    RCU_PLLADDCTL |= (PLL0Q << PLL0Q_REG_OFFSET);

    /* enable PLL0P, PLL0Q, PLL0R */
    RCU_PLLADDCTL |= RCU_PLLADDCTL_PLL0PEN | RCU_PLLADDCTL_PLL0QEN | RCU_PLLADDCTL_PLL0REN;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL0 as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_600M_PLL0_HXTAL)
/*!
    \brief      configure the system clock to 600M by PLL0 which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_600m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* add wait state */
    NVMC_PERFCTL = (NVMC_PERFCTL & (~NVMC_PERFCTL_WSCNT)) | PERFCTL_WSCNT_5;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));
    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    /* HXTAL is stable */
    /* AHB = SYSCLK / 2 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
    /* APB4 = AHB / 2 */
    RCU_CFG0 |= RCU_APB4_CKAHB_DIV2;
    /* APB3 = AHB / 2 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV2;
    /* APB2 = AHB / 1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB / 2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* PLL select HXTAL, configure PLL0 input and output range */
    RCU_PLLALL &= ~(RCU_PLLALL_PLLSEL | RCU_PLLALL_PLL0VCOSEL | RCU_PLLALL_PLL0RNG);
    RCU_PLLALL |= (RCU_PLLSRC_HXTAL | RCU_PLL0RNG_4M_8M);

    /* PLL0P = HXTAL / 5 * 120 = 600 MHz */
    RCU_PLL0 &= ~(RCU_PLL0_PLL0N | RCU_PLL0_PLL0PSC | RCU_PLL0_PLL0P | RCU_PLL0_PLL0R | RCU_PLL0_PLLSTBSRC);
    RCU_PLL0 |= ((PLL0N << PLL0N_REG_OFFSET) | (PLL0PSC << PLL0PSC_REG_OFFSET) | (PLL0P << PLL0P_REG_OFFSET) | (PLL0R << PLL0R_REG_OFFSET));
    RCU_PLLADDCTL &= ~(RCU_PLLADDCTL_PLL0Q);
    RCU_PLLADDCTL |= (PLL0Q << PLL0Q_REG_OFFSET);

    /* enable PLL0P, PLL0Q, PLL0R */
    RCU_PLLADDCTL |= RCU_PLLADDCTL_PLL0PEN | RCU_PLLADDCTL_PLL0QEN | RCU_PLLADDCTL_PLL0REN;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL0 as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_700M_PLL0_HXTAL)
/*!
    \brief      configure the system clock to 700M by PLL0 which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_700m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* add wait state */
    NVMC_PERFCTL = (NVMC_PERFCTL & (~NVMC_PERFCTL_WSCNT)) | PERFCTL_WSCNT_6;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));
    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    /* HXTAL is stable */
    /* AHB = SYSCLK / 2 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
    /* APB4 = AHB / 2 */
    RCU_CFG0 |= RCU_APB4_CKAHB_DIV2;
    /* APB3 = AHB / 2 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV2;
    /* APB2 = AHB / 1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB / 2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* PLL select HXTAL, configure PLL0 input and output range */
    RCU_PLLALL &= ~(RCU_PLLALL_PLLSEL | RCU_PLLALL_PLL0VCOSEL | RCU_PLLALL_PLL0RNG);
    RCU_PLLALL |= (RCU_PLLSRC_HXTAL | RCU_PLL0RNG_4M_8M);

    /* PLL0P = HXTAL / 5 * 140 = 700 MHz */
    RCU_PLL0 &= ~(RCU_PLL0_PLL0N | RCU_PLL0_PLL0PSC | RCU_PLL0_PLL0P | RCU_PLL0_PLL0R | RCU_PLL0_PLLSTBSRC);
    RCU_PLL0 |= ((PLL0N << PLL0N_REG_OFFSET) | (PLL0PSC << PLL0PSC_REG_OFFSET) | (PLL0P << PLL0P_REG_OFFSET) | (PLL0R << PLL0R_REG_OFFSET));
    RCU_PLLADDCTL &= ~(RCU_PLLADDCTL_PLL0Q);
    RCU_PLLADDCTL |= (PLL0Q << PLL0Q_REG_OFFSET);

    /* enable PLL0P, PLL0Q, PLL0R */
    RCU_PLLADDCTL |= RCU_PLLADDCTL_PLL0PEN | RCU_PLLADDCTL_PLL0QEN | RCU_PLLADDCTL_PLL0REN;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL0 as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}

#elif defined (__SYSTEM_CLOCK_750M_PLL0_HXTAL)
/*!
    \brief      configure the system clock to 750M by PLL0 which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
    \note       This function contains scenarios leading to an infinite loop.
                Modify according to the user's actual usage scenarios.
*/
static void system_clock_750m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* add wait state */
    NVMC_PERFCTL = (NVMC_PERFCTL & (~NVMC_PERFCTL_WSCNT)) | PERFCTL_WSCNT_7;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));
    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    /* HXTAL is stable */
    /* AHB = SYSCLK / 2 */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV2;
    /* APB4 = AHB / 2 */
    RCU_CFG0 |= RCU_APB4_CKAHB_DIV2;
    /* APB3 = AHB / 2 */
    RCU_CFG0 |= RCU_APB3_CKAHB_DIV2;
    /* APB2 = AHB / 1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB / 2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* PLL select HXTAL, configure PLL0 input and output range */
    RCU_PLLALL &= ~(RCU_PLLALL_PLLSEL | RCU_PLLALL_PLL0VCOSEL | RCU_PLLALL_PLL0RNG);
    RCU_PLLALL |= (RCU_PLLSRC_HXTAL | RCU_PLL0RNG_4M_8M);

    /* PLL0P = HXTAL / 5 * 150 = 750 MHz */
    RCU_PLL0 &= ~(RCU_PLL0_PLL0N | RCU_PLL0_PLL0PSC | RCU_PLL0_PLL0P | RCU_PLL0_PLL0R | RCU_PLL0_PLLSTBSRC);
    RCU_PLL0 |= ((PLL0N << PLL0N_REG_OFFSET) | (PLL0PSC << PLL0PSC_REG_OFFSET) | (PLL0P << PLL0P_REG_OFFSET) | (PLL0R << PLL0R_REG_OFFSET));
    RCU_PLLADDCTL &= ~(RCU_PLLADDCTL_PLL0Q);
    RCU_PLLADDCTL |= (PLL0Q << PLL0Q_REG_OFFSET);

    /* enable PLL0P, PLL0Q, PLL0R */
    RCU_PLLADDCTL |= RCU_PLLADDCTL_PLL0PEN | RCU_PLLADDCTL_PLL0QEN | RCU_PLLADDCTL_PLL0REN;

    /* enable PLL0 */
    RCU_CTL |= RCU_CTL_PLL0EN;

    /* wait until PLL0 is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLL0STB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL0 as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL0P;
    RCU_CFG0 = reg_temp;

    /* wait until PLL0 is selected as system clock */
    while(RCU_SCSS_PLL0P != (RCU_CFG0 & RCU_CFG0_SCSS)) {
    }
}
#endif /* __SYSTEM_CLOCK_IRC64M */

/*!
    \brief      update the SystemCoreClock with current core clock retrieved from cpu registers
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SystemCoreClockUpdate(void)
{
    uint32_t sws = 0U;
    uint32_t irc64div = 0U;
    uint32_t pllpsc = 0U, plln = 0U, pllp = 0U, pllsel = 0U;

    sws = GET_BITS(RCU_CFG0, 2U, 3U);
    switch(sws) {
    /* IRC64M is selected as CK_SYS */
    case SEL_IRC64MDIV:
        irc64div = (1U << GET_BITS(RCU_ADDCTL1, 16U, 17U));
        SystemCoreClock = IRC64M_VALUE / irc64div;
        break;
    /* LPIRC4M is selected as CK_SYS */
    case SEL_LPIRC4M:
        SystemCoreClock = LPIRC4M_VALUE;
        break;
    /* HXTAL is selected as CK_SYS */
    case SEL_HXTAL:
        SystemCoreClock = HXTAL_VALUE;
        break;
    /* PLL0P is selected as CK_SYS */
    case SEL_PLL0P:
        /* get the value of PLL0PSC[0,5], PLL0N[6,14], PLL0P[16,22] */
        pllpsc = GET_BITS(RCU_PLL0, 0U, 5U);
        plln = GET_BITS(RCU_PLL0, 6U, 14U) + 1U;
        pllp = GET_BITS(RCU_PLL0, 16U, 22U) + 1U;

        /* PLL clock source selection, HXTAL or IRC64M_VALUE or LPIRC4M_VALUE */
        pllsel = GET_BITS(RCU_PLLALL, 16U, 17U);
        if(0U == pllsel) {
            irc64div = (1U << GET_BITS(RCU_ADDCTL1, 16U, 17U));
            SystemCoreClock = (IRC64M_VALUE / irc64div / pllpsc) * plln / pllp;
        } else if(1U == pllsel) {
            SystemCoreClock = (LPIRC4M_VALUE / pllpsc) * plln / pllp;
        } else {
            SystemCoreClock = (HXTAL_VALUE / pllpsc) * plln / pllp;
        }
        break;
    default:
        /* should not be here */
        break;
    }
}

#ifdef __FIRMWARE_VERSION_DEFINE
/*!
    \brief      get firmware version
    \param[in]  none
    \param[out] none
    \retval     firmware version
*/
uint32_t gd32h77x_78x_firmware_version_get(void)
{
    return (uint32_t)__GD32H77X_78X_STDPERIPH_VERSION;
}
#endif /* __FIRMWARE_VERSION_DEFINE */
