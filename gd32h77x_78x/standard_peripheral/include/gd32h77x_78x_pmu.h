/*!
    \file    gd32h77x_78x_pmu.h
    \brief   definitions for the PMU

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

#ifndef GD32H77X_78X_PMU_H
#define GD32H77X_78X_PMU_H

#include "gd32h77x_78x.h"

/* PMU definitions */
#define PMU                             PMU_BASE                            /*!< PMU base address */

/* registers definitions */
#define PMU_CTL0                        REG32((PMU) + 0x00000000U)          /*!< PMU control register 0 */
#define PMU_CS                          REG32((PMU) + 0x00000004U)          /*!< PMU control and status register */
#define PMU_CTL1                        REG32((PMU) + 0x00000008U)          /*!< PMU control register 1 */
#define PMU_CTL2                        REG32((PMU) + 0x0000000CU)          /*!< PMU control register 2 */
#define PMU_CTL3                        REG32((PMU) + 0x00000010U)          /*!< PMU control register 3 */
#define PMU_CTL4                        REG32((PMU) + 0x00000014U)          /*!< PMU control register 4 */
#define PMU_PAR                         REG32((PMU) + 0x00000018U)          /*!< PMU parameter register */

/* bits definitions */
/* PMU_CTL0 */
#define PMU_CTL0_COREPOROFFOUT          BIT(0)                              /*!< CORE POR OFF output */
#define PMU_CTL0_STBMOD                 BIT(1)                              /*!< standby mode */
#define PMU_CTL0_WURST                  BIT(2)                              /*!< wakeup flag reset */
#define PMU_CTL0_STBRST                 BIT(3)                              /*!< standby flag reset */
#define PMU_CTL0_LVDEN                  BIT(4)                              /*!< low voltage detector enable */
#define PMU_CTL0_LVDT                   BITS(5,7)                           /*!< low voltage detector threshold */
#define PMU_CTL0_BKPWEN                 BIT(8)                              /*!< backup domain write enable */
#define PMU_CTL0_COREPOROFFP            BIT(9)                              /*!< CORE POR OFF output polarity selection */
#define PMU_CTL0_COREPDREN              BIT(10)                             /*!< CORE PDR circuit enable signal */
#define PMU_CTL0_DSVOS                  BITS(14,15)                         /*!< Deep-sleep mode Vcore voltage scaling select */
#define PMU_CTL0_VAVDEN                 BIT(16)                             /*!< VDDA analog voltage detector enable */
#define PMU_CTL0_VAVDVC                 BITS(17,18)                         /*!< VDDA analog voltage detector level configure bits */
#define PMU_CTL0_VOVDEN                 BIT(19)                             /*!< Vcore voltage detector enable */
#define PMU_CTL0_VUVDEN                 BIT(24)                             /*!< Vcore under voltage detector enable */
#define PMU_CTL0_VOVDVC                 BITS(25,26)                         /*!< Vcore over voltage detector voltage level configure bits */
#define PMU_CTL0_VUVDVC                 BITS(27,28)                         /*!< Vcore under voltage detector voltage level configure bits */
#define PMU_CTL0_SRAM_MODE              BITS(29,30)                         /*!< Sram_mode in Deep-sleep */
#define PMU_CTL0_SRAM_PRDYN             BIT(31)                             /*!< Indicates if the device has entered Deep-sleep mode */

/* PMU_CS */
#define PMU_CS_WUF                      BIT(0)                              /*!< wakeup flag */
#define PMU_CS_STBF                     BIT(1)                              /*!< standby flag */
#define PMU_CS_LVDF                     BIT(2)                              /*!< low voltage detector status flag */
#define PMU_CS_UVDF                     BIT(3)                              /*!< Record the undervoltage reset of the Vcore */
#define PMU_CS_VUVDF0                   BIT(5)                              /*!< Vcore under voltage detector flag bit */
#define PMU_CS_VOVDF1                   BIT(6)                              /*!< Vcore over voltage detector flag bit after digital filter */
#define PMU_CS_VUVDF1                   BIT(7)                              /*!< Vcore under voltage detector flag bit after digital filter */
#define PMU_CS_WUPEN0                   BIT(8)                              /*!< wakeup pin0(PA0) enable */
#define PMU_CS_WUPEN1                   BIT(9)                              /*!< wakeup pin1(PA2) enable */
#define PMU_CS_WUPEN3                   BIT(11)                             /*!< wakeup pin3(PC13) enable */
#define PMU_CS_WUPEN5                   BIT(13)                             /*!< wakeup pin5(PC1) enable */
#define PMU_CS_VAVDF                    BIT(16)                             /*!< VDDA analog voltage detector voltage output on VDDA flag */
#define PMU_CS_VOVDF                    BIT(20)                             /*!< Vcore voltage detector flag */

/* PMU_CTL1 */
#define PMU_CTL1_BKPVSEN                BIT(0)                              /*!< Backup regulator enable */
#define PMU_CTL1_VBTMEN                 BIT(4)                              /*!< VBAT and temperature monitoring enable */
#define PMU_CTL1_BKPVSRF                BIT(16)                             /*!< Backup regulator ready */
#define PMU_CTL1_VBATLF                 BIT(20)                             /*!< VBAT level monitoring versus low threshold */
#define PMU_CTL1_VBATHF                 BIT(21)                             /*!< VBAT level monitoring versus high threshold */
#define PMU_CTL1_TEMPLF                 BIT(22)                             /*!< temperature level monitoring versus low threshold */
#define PMU_CTL1_TEMPHF                 BIT(23)                             /*!< temperature level monitoring versus high threshold */

/* PMU_CTL2 */
#define PMU_CTL2_VOVDO_DNF              BITS(0,7)                           /*!< VOVD analog output digital noise filter */
#define PMU_CTL2_VUVDO_DNF              BITS(8,15)                          /*!< VUVD analog output digital noise filter */

/* PMU_CTL3 */
#define PMU_CTL3_BYPASS                 BIT(0)                              /*!< power management unit bypass control bit */
#define PMU_CTL3_DVSEN                  BIT(2)                              /*!< SMPS step-down converter enable SDEN */
#define PMU_CTL3_MIPI_RDY_FALL          BIT(6)                              /*!< record the occurrence of undervoltage reset on VDD09DSI */
#define PMU_CTL3_VCRSEL                 BIT(8)                              /*!< VBAT battery charging resistor selection */
#define PMU_CTL3_VCEN                   BIT(9)                              /*!< VBAT battery charging enable */
#define PMU_CTL3_MIPI_PDR_LEV           BIT(10)                             /*!< MIPI_LDO VDD09DSI PDR threshold selection control signal */
#define PMU_CTL3_MIPI_PDR_EN            BIT(11)                             /*!< MIPI_LDO VDD09DSI PDR function enable signal */
#define PMU_CTL3_MIPISW                 BIT(17)                             /*!< Powers off the MIPI */
#define PMU_CTL3_PKCAUSW                BIT(18)                             /*!< Powers off the PKCAU */
#define PMU_CTL3_ESCSW                  BIT(19)                             /*!< Powers off the ETHC */
#define PMU_CTL3_MIPIHTF                BIT(20)                             /*!< Mipi power switch ack flag */
#define PMU_CTL3_MIPIHTEN               BIT(21)                             /*!< MIPI output isolation enable */
#define PMU_CTL3_PKCAUHTEN              BIT(22)                             /*!< PKCAU output isolation enable */
#define PMU_CTL3_ESCHTEN                BIT(23)                             /*!< ESC output isolation enable */
#define PMU_CTL3_VUSB33DEN              BIT(24)                             /*!< VDD33USB voltage level detector enable bit */
#define PMU_CTL3_USBSEN                 BIT(25)                             /*!< USB regulator enable */
#define PMU_CTL3_USB33RF                BIT(26)                             /*!< USB supply ready flag */
#define PMU_CTL3_MIPI_LDO_EN            BIT(27)                             /*!< MIPI_LDO enable signal */
#define PMU_CTL3_MIPI_LDO_BYP           BIT(28)                             /*!< MIPI_LDO BYPASS mode enable signal */
#define PMU_CTL3_MIPI_LDO_RDY           BIT(29)                             /*!< The MIPI_LDO output voltage ready signal */
#define PMU_CTL3_PKCAUHTF               BIT(30)                             /*!< PKCAU power switch ack flag */
#define PMU_CTL3_ESCHTF                 BIT(31)                             /*!< ESC power switch ack flag */

/* PMU_CTL4 */
#define PMU_CTL4_VC_VOS                 BITS(10,15)                         /*!< VCORE voltage level selection (10mV step) */
#define PMU_CTL4_MIPI_VC_VOS            BITS(26,31)                         /*!< MIPI VCORE_DS voltage level selection (10mV step) */

/* PMU_PAR */
#define PMU_PAR_PMU_CNT                 BITS(0,11)                          /*!< exit Deep-sleep mode wait time count configure bits */
#define PMU_PAR_TSW_IRCCNT              BITS(16,20)                         /*!< when enter Deep-sleep, switch to LPIRC4M / IRC64M (confirmed by DSPWUSSEL) clock. */

/* constants definitions */
/* PMU low voltage detector threshold definitions */
#define CTL0_LVDT(regval)               ((BITS(5,7) & ((uint32_t)(regval) << 5U)))
#define PMU_LVDT_0                      CTL0_LVDT(0)                        /*!< voltage threshold is 2.1V */
#define PMU_LVDT_1                      CTL0_LVDT(1)                        /*!< voltage threshold is 2.3V */
#define PMU_LVDT_2                      CTL0_LVDT(2)                        /*!< voltage threshold is 2.4V */
#define PMU_LVDT_3                      CTL0_LVDT(3)                        /*!< voltage threshold is 2.6V */
#define PMU_LVDT_4                      CTL0_LVDT(4)                        /*!< voltage threshold is 2.7V */
#define PMU_LVDT_5                      CTL0_LVDT(5)                        /*!< voltage threshold is 2.9V */
#define PMU_LVDT_6                      CTL0_LVDT(6)                        /*!< voltage threshold is 3.0V */
#define PMU_LVDT_7                      CTL0_LVDT(7)                        /*!< Input analog voltage on PB7 (compared with 0.8V) */

/* PMU Deep-sleep mode Vcore voltage scaling definitions */
#define CTL0_DSVOS(regval)              (BITS(14,15) & ((uint32_t)(regval) << 14U))
#define PMU_DSVOS_1                     CTL0_DSVOS(1)                       /*!< Deep-sleep mode Vcore voltage 0.7V */
#define PMU_DSVOS_2                     CTL0_DSVOS(2)                       /*!< Deep-sleep mode Vcore voltage 0.8V (default) */
#define PMU_DSVOS_3                     CTL0_DSVOS(3)                       /*!< Deep-sleep mode Vcore voltage 0.9V */

/* PMU analog voltage detector threshold definitions */
#define CTL0_VAVDVC(regval)             (BITS(17,18) & ((uint32_t)(regval) << 17U))
#define PMU_AVDT_0                      CTL0_VAVDVC(0)                      /*!< voltage threshold is 1.7V */
#define PMU_AVDT_1                      CTL0_VAVDVC(1)                      /*!< voltage threshold is 2.1V */
#define PMU_AVDT_2                      CTL0_VAVDVC(2)                      /*!< voltage threshold is 2.5V */
#define PMU_AVDT_3                      CTL0_VAVDVC(3)                      /*!< voltage threshold is 2.8V */

/* PMU over voltage detector threshold definitions */
#define CTL0_VOVDVC(regval)             (BITS(25,26) & ((uint32_t)(regval) << 25U))
#define PMU_OVDT_0                      CTL0_VOVDVC(0)                      /*!< Vcore over voltage threshold is 0.9V */
#define PMU_OVDT_1                      CTL0_VOVDVC(1)                      /*!< Vcore over voltage threshold is 1.0V */
#define PMU_OVDT_2                      CTL0_VOVDVC(2)                      /*!< Vcore over voltage threshold is 1.1V */
#define PMU_OVDT_3                      CTL0_VOVDVC(3)                      /*!< Vcore over voltage threshold is 1.2V */

/* PMU under voltage detector threshold definitions */
#define CTL0_VUVDVC(regval)             (BITS(27,28) & ((uint32_t)(regval) << 27U))
#define PMU_UVDT_0                      CTL0_VUVDVC(0)                      /*!< Vcore under voltage threshold is 0.8V */
#define PMU_UVDT_1                      CTL0_VUVDVC(1)                      /*!< Vcore under voltage threshold is 0.7V */
#define PMU_UVDT_2                      CTL0_VUVDVC(2)                      /*!< Vcore under voltage threshold is 0.6V */
#define PMU_UVDT_3                      CTL0_VUVDVC(3)                      /*!< Vcore under voltage threshold is 0.9V */

/* PMU CTL4 VC_VOS voltage level definitions */
#define CTL4_VC_VOS(regval)             (BITS(10,15) & ((uint32_t)(regval) << 10U))
#define PMU_VC_VOS(mv)                  CTL4_VC_VOS(((uint32_t)(mv) - 450U) / 10U)       /*!< Vcore voltage, mv = 520 ~ 1080, 10mV step */

/* PMU CTL4 MIPI_VC_VOS voltage level definitions */
#define CTL4_MIPI_VC_VOS(regval)        (BITS(26,31) & ((uint32_t)(regval) << 26U))
#define PMU_MIPI_VC_VOS(mv)             CTL4_MIPI_VC_VOS(((uint32_t)(mv) - 450U) / 10U)  /*!< VCORE_DSI voltage, mv = 520 ~ 1080, 10mV step */

/* PMU sram mode */
#define CTL0_SRAM_MODE(regval)          (BITS(29,30) & ((uint32_t)(regval) << 29U))
#define PMU_DISABLE                     CTL0_SRAM_MODE(0)                   /*!< disable */
#define PMU_PRECHARGE                   CTL0_SRAM_MODE(1)                   /*!< select precharge */
#define PMU_RETENTION                   CTL0_SRAM_MODE(2)                   /*!< select retention */

/* PMU VBAT battery charging resistor selection */
#define CTL3_VCRSEL(regval)             (BIT(8) & ((uint32_t)(regval) << 8U))
#define PMU_VCRSEL_5K                   CTL3_VCRSEL(0)                      /*!< 5 kOhms resistor is selected for charging VBAT battery */
#define PMU_VCRSEL_1P5K                 CTL3_VCRSEL(1)                      /*!< 1.5 kOhms resistor is selected for charging VBAT battery */

/* PMU flag definitions */
#define PMU_REGIDX_BIT(regidx, bitpos)  (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define PMU_REG_VAL(periph)             (REG32(PMU + ((uint32_t)(periph) >> 6U)))
#define PMU_BIT_POS(val)                ((uint32_t)(val) & 0x1FU)

#define PMU_CTL0_OFFSET                 (0x00000000U)                       /*!< PMU control register 0 offset */
#define PMU_CS_OFFSET                   (0x00000004U)                       /*!< PMU control and status register offset */
#define PMU_CTL1_OFFSET                 (0x00000008U)                       /*!< PMU control register 1 offset */
#define PMU_CTL2_OFFSET                 (0x0000000CU)                       /*!< PMU control register 2 offset */
#define PMU_CTL3_OFFSET                 (0x00000010U)                       /*!< PMU control register 3 offset */
#define PMU_CTL4_OFFSET                 (0x00000014U)                       /*!< PMU control register 4 offset */
#define PMU_PAR_OFFSET                  (0x00000018U)                       /*!< PMU parameter register offset */

#define PMU_FLAG_WAKEUP                 PMU_REGIDX_BIT(PMU_CS_OFFSET, 0)    /*!< wakeup flag */
#define PMU_FLAG_STANDBY                PMU_REGIDX_BIT(PMU_CS_OFFSET, 1)    /*!< standby flag */
#define PMU_FLAG_LVDF                   PMU_REGIDX_BIT(PMU_CS_OFFSET, 2)    /*!< low voltage detector status flag */
#define PMU_FLAG_UVDF                   PMU_REGIDX_BIT(PMU_CS_OFFSET, 3)    /*!< record the undervoltage reset of the Vcore */
#define PMU_FLAG_VUVDF0                 PMU_REGIDX_BIT(PMU_CS_OFFSET, 5)    /*!< Vcore under voltage detector flag bit */
#define PMU_FLAG_VOVDF1                 PMU_REGIDX_BIT(PMU_CS_OFFSET, 6)    /*!< Vcore over voltage detector flag bit after digital filter */
#define PMU_FLAG_VUVDF1                 PMU_REGIDX_BIT(PMU_CS_OFFSET, 7)    /*!< Vcore under voltage detector flag bit after digital filter */
#define PMU_FLAG_VAVDF                  PMU_REGIDX_BIT(PMU_CS_OFFSET, 16)   /*!< VDDA analog voltage detector voltage output on VDDA flag */
#define PMU_FLAG_VOVDF0                 PMU_REGIDX_BIT(PMU_CS_OFFSET, 20)   /*!< peripheral voltage on Vcore detector flag */
#define PMU_FLAG_PRDYN                  PMU_REGIDX_BIT(PMU_CTL0_OFFSET, 31) /*!< the internal memory instance power supplies are stable after returning from retention mode */
#define PMU_FLAG_BKPVSRF                PMU_REGIDX_BIT(PMU_CTL1_OFFSET, 16) /*!< backup voltage stabilizer ready flag */
#define PMU_FLAG_VBATLF                 PMU_REGIDX_BIT(PMU_CTL1_OFFSET, 20) /*!< VBAT level monitoring versus low threshold */
#define PMU_FLAG_VBATHF                 PMU_REGIDX_BIT(PMU_CTL1_OFFSET, 21) /*!< VBAT level monitoring versus high threshold */
#define PMU_FLAG_TEMPLF                 PMU_REGIDX_BIT(PMU_CTL1_OFFSET, 22) /*!< temperature level monitoring versus low threshold */
#define PMU_FLAG_TEMPHF                 PMU_REGIDX_BIT(PMU_CTL1_OFFSET, 23) /*!< temperature level monitoring versus high threshold */
#define PMU_FLAG_RDYFALLF               PMU_REGIDX_BIT(PMU_CTL3_OFFSET, 6)  /*!< record the occurrence of undervoltage reset on VDD09DSI */
#define PMU_FLAG_MIPIHTF                PMU_REGIDX_BIT(PMU_CTL3_OFFSET, 20) /*!< MIPI power switch ack flag */
#define PMU_FLAG_USB33RF                PMU_REGIDX_BIT(PMU_CTL3_OFFSET, 26) /*!< USB supply ready flag bit */
#define PMU_FLAG_RDYF                   PMU_REGIDX_BIT(PMU_CTL3_OFFSET, 29) /*!< the MIPI_LDO output voltage ready signal */
#define PMU_FLAG_PKCAUHTF               PMU_REGIDX_BIT(PMU_CTL3_OFFSET, 30) /*!< PKCAU power switch ack flag */
#define PMU_FLAG_ESCHTF                 PMU_REGIDX_BIT(PMU_CTL3_OFFSET, 31) /*!< ESC power switch ack flag */

/* PMU wakeup pin definitions */
#define PMU_WAKEUP_PIN0                 PMU_CS_WUPEN0                       /*!< wakeup pin 0 */
#define PMU_WAKEUP_PIN1                 PMU_CS_WUPEN1                       /*!< wakeup pin 1 */
#define PMU_WAKEUP_PIN3                 PMU_CS_WUPEN3                       /*!< wakeup pin 3 */
#define PMU_WAKEUP_PIN5                 PMU_CS_WUPEN5                       /*!< wakeup pin 5 */

/* PMU Vcore supply mode definitions */
#define PMU_DIRECT_SMPS_SUPPLY          PMU_CTL3_DVSEN                      /*!< Vcore domain is supplied from the SMPS step-down converter */
#define PMU_BYPASS                      PMU_CTL3_BYPASS                     /*!< SMPS disabled, Vcore domain is supplied from an external source */

/* PMU command constants definitions */
#define WFI_CMD                         ((uint8_t)0x00U)                    /*!< use WFI command */
#define WFE_CMD                         ((uint8_t)0x01U)                    /*!< use WFE command */

/* PMU PDR FALLING THRESHOLD0 definitions*/
#define PDR_FALLING_THRESHOLD0          ((uint8_t)0x00U)                    /*!< PDR falling threshold is 0.775V, POR rising threshold is 0.8V */
#define PDR_FALLING_THRESHOLD1          ((uint8_t)0x01U)                    /*!< PDR falling threshold is 0.675V, POR rising threshold is 0.7V */

#ifdef FW_DEBUG_ERR_REPORT
/* check enter Deep-sleep mode wait time */
#define NOT_PMU_ENTER_WAITTIME(wait_time)                (((uint32_t)(wait_time)) > 0x1FU)
/* check exit Deep-sleep mode wait time */
#define NOT_PMU_EXIT_WAITTIME(wait_time)                 (((uint32_t)(wait_time)) > 0xFFFU)
/* check PMU low voltage detector threshold */
#define NOT_PMU_LVD(lvdt_n)                              (((lvdt_n) != PMU_LVDT_0) && ((lvdt_n) != PMU_LVDT_1) && \
                                                          ((lvdt_n) != PMU_LVDT_2) && ((lvdt_n) != PMU_LVDT_3) && \
                                                          ((lvdt_n) != PMU_LVDT_4) && ((lvdt_n) != PMU_LVDT_5) && \
                                                          ((lvdt_n) != PMU_LVDT_6) && ((lvdt_n) != PMU_LVDT_7))
/* check PMU analog voltage detector threshold */
#define NOT_PMU_AVD(avd_n)                               (((avd_n) != PMU_AVDT_0) && ((avd_n) != PMU_AVDT_1) && \
                                                          ((avd_n) != PMU_AVDT_2) && ((avd_n) != PMU_AVDT_3))
/* check PMU over voltage detector threshold */
#define NOT_PMU_OVD(ovd_n)                               (((ovd_n) != PMU_OVDT_0) && ((ovd_n) != PMU_OVDT_1) && \
                                                          ((ovd_n) != PMU_OVDT_2) && ((ovd_n) != PMU_OVDT_3))
/* check PMU under voltage detector threshold */
#define NOT_PMU_UVD(uvd_n)                               (((uvd_n) != PMU_UVDT_0) && ((uvd_n) != PMU_UVDT_1) && \
                                                          ((uvd_n) != PMU_UVDT_2) && ((uvd_n) != PMU_UVDT_3))
/* check PMU Deep-sleep mode Vcore core voltage select */
#define NOT_PMU_DSVOS(dsvos)                             (((dsvos) != PMU_DSVOS_1) && ((dsvos) != PMU_DSVOS_2) &&\
                                                          ((dsvos) != PMU_DSVOS_3))
/* check PMU VBAT battery charging resistor selection */
#define NOT_PMU_VBAT(resistor)                           (((resistor) != PMU_VCRSEL_5K) && ((resistor) != PMU_VCRSEL_1P5K))
/* check PMU power supply */
#define NOT_PMU_SMPS_SUPPLY(smpsmode)                    (((smpsmode) != PMU_DIRECT_SMPS_SUPPLY) && ((smpsmode) != PMU_BYPASS))
/* check PMU sleep mode */
#define NOT_PMU_SLEEPMODE(sleepmodecmd)                  (((sleepmodecmd) != WFI_CMD) && ((sleepmodecmd) != WFE_CMD))
/* check PMU wakeup pin */
#define NOT_PMU_WAKEUP_PIN(wakeup_pin)                   (((wakeup_pin) != PMU_WAKEUP_PIN0) && ((wakeup_pin) != PMU_WAKEUP_PIN1) && \
                                                          ((wakeup_pin) != PMU_WAKEUP_PIN3) && ((wakeup_pin) != PMU_WAKEUP_PIN5))
/* check PMU flag state */
#define NOT_PMU_FLAG(flag)                               (((flag) != PMU_FLAG_WAKEUP) && ((flag) != PMU_FLAG_STANDBY) && \
                                                          ((flag) != PMU_FLAG_LVDF) && ((flag) != PMU_FLAG_UVDF) && \
                                                          ((flag) != PMU_FLAG_VUVDF0) && ((flag) != PMU_FLAG_VOVDF1) && \
                                                          ((flag) != PMU_FLAG_VUVDF1) && ((flag) != PMU_FLAG_VAVDF) && \
                                                          ((flag) != PMU_FLAG_VOVDF0)&& ((flag) != PMU_FLAG_BKPVSRF) && \
                                                          ((flag) != PMU_FLAG_MIPIHTF) && ((flag) != PMU_FLAG_TEMPLF) && \
                                                          ((flag) != PMU_FLAG_TEMPHF) && ((flag) != PMU_FLAG_ESCHTF) && \
                                                          ((flag) != PMU_FLAG_USB33RF) && ((flag) != PMU_FLAG_VBATLF) && \
                                                          ((flag) != PMU_FLAG_VBATHF) && ((flag) != PMU_FLAG_PKCAUHTF) && \
                                                          ((flag) != PMU_FLAG_PRDYN) && ((flag) != PMU_FLAG_RDYFALLF) && \
                                                          ((flag) != PMU_FLAG_RDYF))
/* check PMU reset flag state */
#define NOT_PMU_FLAG_RESET(flag_reset)                   (((flag_reset) != PMU_FLAG_WAKEUP) && ((flag_reset) != PMU_FLAG_STANDBY) && \
                                                          ((flag_reset) != PMU_FLAG_RDYFALLF))
/* check PMU sram mode */
#define NOT_SRAM_MODE(sram_mode)                         (((sram_mode) != PMU_DISABLE) && ((sram_mode) != PMU_PRECHARGE) && \
                                                          ((sram_mode) != PMU_RETENTION))
/* check output filter length */
#define NOT_PMU_FILTER_LENGTH(length)                    (((uint32_t)(length)) > 255U)
/* check PMU reset flag state */
#define NOT_PMU_THRESHOLD_VALUE(threshold_value)         (((threshold_value) != PDR_FALLING_THRESHOLD0) && ((threshold_value) != PDR_FALLING_THRESHOLD1))
/* check Vcore voltage level */
#define NOT_PMU_VC_VOS(level)                            (((uint32_t)(level) & ~PMU_CTL4_VC_VOS) != 0U)
/* check VCORE_DSI voltage level */
#define NOT_PMU_MIPI_VC_VOS(level)                       (((uint32_t)(level) & ~PMU_CTL4_MIPI_VC_VOS) != 0U)
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* reset PMU registers */
void pmu_deinit(void);
/* select low voltage detector threshold */
void pmu_lvd_select(uint32_t lvdt_n);
/* enable PMU lvd */
void pmu_lvd_enable(void);
/* disable PMU lvd */
void pmu_lvd_disable(void);
/* select analog voltage detector threshold */
void pmu_avd_select(uint32_t avdt_n);
/* enable PMU analog voltage detector */
void pmu_avd_enable(void);
/* disable PMU analog voltage detector */
void pmu_avd_disable(void);
/* select PMU Vcore over detector threshold */
void pmu_ovd_select(uint32_t ovdt_n);
/* enable PMU Vcore over voltage detector */
void pmu_ovd_enable(void);
/* disable PMU Vcore over voltage detector */
void pmu_ovd_disable(void);
/* select PMU Vcore under voltage detector threshold */
void pmu_uvd_select(uint32_t uvdt_n);
/* enable PMU Vcore under voltage detector */
void pmu_uvd_enable(void);
/* disable PMU Vcore under voltage detector */
void pmu_uvd_disable(void);
/* deep-sleep mode Vcore voltage select */
void pmu_dsvos_select(uint32_t dsvos);

/* PMU VBAT battery charging resistor selection */
void pmu_vbat_charging_select(uint32_t resistor);
/* enable VBAT battery charging */
void pmu_vbat_charging_enable(void);
/* disable VBAT battery charging */
void pmu_vbat_charging_disable(void);
/* enable VBAT and temperature monitoring */
void pmu_vbat_temp_monitor_enable(void);
/* disable VBAT and temperature monitoring */
void pmu_vbat_temp_monitor_disable(void);

/* USB regulator*/
/* enable USB regulator */
void pmu_usb_regulator_enable(void);
/* disable USB regulator */
void pmu_usb_regulator_disable(void);
/* enable VDD33USB voltage level detector */
void pmu_usb_voltage_detector_enable(void);
/* disable VDD33USB voltage level detector */
void pmu_usb_voltage_detector_disable(void);

/* enable pkcau power*/
void pmu_pkcau_power_enable(void);
/* disable pkcau power */
void pmu_pkcau_power_disable(void);
/* enable pkcau output isolation */
void pmu_pkcau_output_isolation_enable(void);
/* disable pkcau output isolation */
void pmu_pkcau_output_isolation_disable(void);

/* enable esc power */
void pmu_esc_power_enable(void);
/* disable esc power */
void pmu_esc_power_disable(void);
/* enable esc output isolation */
void pmu_esc_output_isolation_enable(void);
/* disable esc output isolation */
void pmu_esc_output_isolation_disable(void);

/* Vcore power supply configurations */
void pmu_smps_supply_config(uint32_t smpsmode);

/* set PMU mode */
/* enter sleep mode */
void pmu_to_sleepmode(uint8_t sleepmodecmd);
/* enter deepsleep mode */
void pmu_to_deepsleepmode(uint8_t deepsleepmodecmd);
/* enter standby mode */
void pmu_to_standbymode(void);
/* enable PMU wakeup pin */
void pmu_wakeup_pin_enable(uint32_t wakeup_pin);
/* disable PMU wakeup pin */
void pmu_wakeup_pin_disable(uint32_t wakeup_pin);

/* backup related functions */
/* enable backup domain write */
void pmu_backup_write_enable(void);
/* disable backup domain write */
void pmu_backup_write_disable(void);
/* enable backup voltage stabilizer */
void pmu_backup_voltage_stabilizer_enable(void);
/* disable backup voltage stabilizer */
void pmu_backup_voltage_stabilizer_disable(void);

/* configure IRC counter before enter Deep-sleep mode */
void pmu_enter_deepsleep_wait_time_config(uint32_t wait_time);
/* configure IRC counter before exit Deep-sleep mode */
void pmu_exit_deepsleep_wait_time_config(uint32_t wait_time);

/* enable CORE PDR circuit */
void pmu_core_pdr_enable(void);
/* disable CORE PDR circuit */
void pmu_core_pdr_disable(void);
/* enable CORE POR OFF output */
void pmu_core_por_off_enable(void);
/* disable CORE POR OFF output */
void pmu_core_por_off_disable(void);
/* enable CORE POR OFF output polarity negation */
void pmu_output_polarity_negation_enable(void);
/* disable CORE POR OFF output polarity negation */
void pmu_output_polarity_negation_disable(void);

/* sram mode in deep-sleep selection */
void pmu_sram_mode_selection(uint32_t sram_mode);
/* VUVD analog output filter length config */
void pmu_vuvd_output_config(uint32_t length);
/* VOVD analog output filter length config */
void pmu_vovd_output_config(uint32_t length);

/* enable MIPI LDO */
void pmu_mipi_ldo_enable(void);
/* disable MIPI LDO */
void pmu_mipi_ldo_disable(void);
/* enable MIPI power */
void pmu_mipi_power_enable(void);
/* disable MIPI power */
void pmu_mipi_power_disable(void);
/* enable MIPI output isolation */
void pmu_mipi_output_isolation_enable(void);
/* disable MIPI output isolation */
void pmu_mipi_output_isolation_disable(void);
/* enable MIPI LDO bypass */
void pmu_mipi_ldo_bypass_enable(void);
/* disable MIPI LDO bypass */
void pmu_mipi_ldo_bypass_disable(void);
/* MIPI LDO VDD09DSI PDR threshold selection */
void pmu_vdd09dsi_pdr_threshold_selection(uint8_t threshold_value);
/* enable MIPI LDO VDD09DSI PDR function */
void pmu_vdd09dsi_pdr_enable(void);
/* enable MIPI LDO VDD09DSI PDR function */
void pmu_vdd09dsi_pdr_disable(void);
/* set VC_VOS voltage level */
void pmu_vc_vos_set(uint32_t voltage_level);
/* set MIPI_VC_VOS voltage level */
void pmu_mipi_vc_vos_set(uint32_t voltage_level);

/* flag functions */
/* clear flag bit */
void pmu_flag_clear(uint32_t flag_reset);
/* get flag state */
FlagStatus pmu_flag_get(uint32_t flag);

#endif /* GD32H77X_78X_PMU_H */
