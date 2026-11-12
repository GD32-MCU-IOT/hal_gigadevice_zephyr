/*!
    \file    gd32h77x_78x.h
    \brief   general definitions for gd32h77x_78x
    
    \version 2026-11-09, V1.0.0, firmware for GD32H77x_78x
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

#ifndef GD32H77X_78X_H
#define GD32H77X_78X_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* GD32H77X_78X NVMC types */
#if defined(GD32H77EXW) || defined(GD32H77DXW) || defined(GD32H779XW) || \
    defined(GD32H78EXW) || defined(GD32H78DXW) || defined(GD32H789XW)
    #define GD32H77X_78X_XW
#elif defined(GD32H77EXP) || defined(GD32H77DXP) || defined(GD32H779XP) || \
      defined(GD32H78EXP) || defined(GD32H78DXP) || defined(GD32H789XP) || \
      defined(GD32H77RXP)
    #define GD32H77X_78X_XP
#elif defined(GD32H77EXI) || defined(GD32H77DXI) || defined(GD32H779XI) || \
      defined(GD32H78EXI) || defined(GD32H78DXI) || defined(GD32H789XI)
    #define GD32H77X_78X_XI
#endif

/* GD32H77X_78X with ESC module */
#if defined(GD32H77EXW) || defined(GD32H77EXP) || defined(GD32H77EXI) || \
    defined(GD32H78EXW) || defined(GD32H78EXP) || defined(GD32H78EXI) || \
    defined(GD32H77RXP)
    #define GD32H77X_78X_SUPPORT_ESC
#endif

/* GD32H77X_78X with DSI module */
#if defined(GD32H77DXW) || defined(GD32H77DXP) || defined(GD32H77DXI) || \
    defined(GD32H78DXW) || defined(GD32H78DXP) || defined(GD32H78DXI)
    #define GD32H77X_78X_SUPPORT_DSI
#endif

/* GD32H78X support 700MHz or 750MHz */
#if defined(GD32H78EXW) || defined(GD32H78EXP) || defined(GD32H78EXI) || \
    defined(GD32H78DXW) || defined(GD32H78DXP) || defined(GD32H78DXI) || \
    defined(GD32H789XW) || defined(GD32H789XP) || defined(GD32H789XI)
#if defined(GD32H78X_HIGH_PERFORMANCE_MODE)
    #define GD32H78X_SUPPORT_MAX_750M
#else
    #define GD32H78X_SUPPORT_MAX_700M
#endif
#endif

#if !defined (GD32H77EXW) && !defined (GD32H77DXW) && !defined (GD32H779XW) && \
    !defined (GD32H77EXP) && !defined (GD32H77DXP) && !defined (GD32H779XP) && \
    !defined (GD32H77EXI) && !defined (GD32H77DXI) && !defined (GD32H779XI) && \
    !defined (GD32H78EXW) && !defined (GD32H78DXW) && !defined (GD32H789XW) && \
    !defined (GD32H78EXP) && !defined (GD32H78DXP) && !defined (GD32H789XP) && \
    !defined (GD32H78EXI) && !defined (GD32H78DXI) && !defined (GD32H789XI) && \
    !defined(GD32H77RXP)
#error "Please select the target gd32h77x_78x device used in your application (in gd32h77x_78x.h file)"
#endif /* undefine GD32H77X_78X tip */

/* define value of high speed crystal oscillator (HXTAL) in Hz */
#if !defined  (HXTAL_VALUE)
#define HXTAL_VALUE    ((uint32_t)25000000)
#endif /* high speed crystal oscillator value */

/* define startup timeout value of high speed crystal oscillator (HXTAL) */
#if !defined  (HXTAL_STARTUP_TIMEOUT)
#define HXTAL_STARTUP_TIMEOUT   ((uint16_t)0x0FFFF)
#endif /* high speed crystal oscillator startup timeout */

/* define value of internal 64MHz RC oscillator (IRC64M) in Hz */
#if !defined  (IRC64M_VALUE) 
#define IRC64M_VALUE  ((uint32_t)64000000)
#endif /* internal 64MHz RC oscillator value */

/* define startup timeout value of internal 64MHz RC oscillator (IRC64M) */
#if !defined  (IRC64M_STARTUP_TIMEOUT)
#define IRC64M_STARTUP_TIMEOUT   ((uint32_t)0x0FFFFFFF)
#endif /* internal 64MHz RC oscillator startup timeout */

/* define value of Low Power Internal 4Mhz RC oscillator (LPIRC4M) in Hz */
#if !defined  (LPIRC4M_VALUE) 
#define LPIRC4M_VALUE  ((uint32_t)4000000)
#endif /* Low Power Internal 4Mhz RC oscillator value */

/* define startup timeout value of internal Low Power Internal 4Mhz RC oscillator (LPIRC4M) */
#if !defined  (LPIRC4M_STARTUP_TIMEOUT)
#define LPIRC4M_STARTUP_TIMEOUT   ((uint16_t)0x0500)
#endif /* Low Power Internal 4Mhz RC oscillator startup timeout */

/* define value of internal 48MHz RC oscillator (IRC48M) in Hz */
#if !defined  (IRC48M_VALUE) 
#define IRC48M_VALUE ((uint32_t)48000000)
#endif /* internal 48MHz RC oscillator value */

/* define startup timeout value of internal 48MHz RC oscillator (IRC48M) */
#if !defined  (IRC48M_STARTUP_TIMEOUT)
#define IRC48M_STARTUP_TIMEOUT   ((uint16_t)0x0500)
#endif /* internal 48MHz RC oscillator startup timeout */

/* define value of internal 32KHz RC oscillator(IRC32K) in Hz */
#if !defined  (IRC32K_VALUE) 
#define IRC32K_VALUE  ((uint32_t)32000)
#endif /* internal 32KHz RC oscillator value */

/* define startup timeout value of internal 32KHz RC oscillator (IRC32K) */
#if !defined  (IRC32K_STARTUP_TIMEOUT)
#define IRC32K_STARTUP_TIMEOUT   ((uint16_t)0x0500)
#endif /* internal 32KHz RC oscillator startup timeout */

/* define value of low speed crystal oscillator (LXTAL)in Hz */
#if !defined  (LXTAL_VALUE) 
#define LXTAL_VALUE  ((uint32_t)32768)
#endif /* low speed crystal oscillator value */

/* define startup timeout value of low speed crystal oscillator (LXTAL) */
#if !defined  (LXTAL_STARTUP_TIMEOUT)
#define LXTAL_STARTUP_TIMEOUT   ((uint32_t)0x0FFFFFFF)
#endif /* low speed crystal oscillator startup timeout */

/* GD32H77X_78X firmware library version number V1.0.0 */
#define __GD32H77X_78X_STDPERIPH_VERSION_MAIN   (0x01) /*!< [31:24] main version     */
#define __GD32H77X_78X_STDPERIPH_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version     */
#define __GD32H77X_78X_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version     */
#define __GD32H77X_78X_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __GD32H77X_78X_STDPERIPH_VERSION        ((__GD32H77X_78X_STDPERIPH_VERSION_MAIN << 24)\
                                            |(__GD32H77X_78X_STDPERIPH_VERSION_SUB1 << 16)\
                                            |(__GD32H77X_78X_STDPERIPH_VERSION_SUB2 << 8)\
                                            |(__GD32H77X_78X_STDPERIPH_VERSION_RC))

/* configuration of the Cortex-M7 processor and core peripherals                             */
#define __CM7_REV               0x0102U   /*!< Cortex-M7 revision r1p2                       */
#define __MPU_PRESENT             1       /*!< CM7 provides an MPU                           */
#define __NVIC_PRIO_BITS          4       /*!< CM7 uses 4 Bits for the Priority Levels       */
#define __Vendor_SysTickConfig    0       /*!< Set to 1 if different SysTick Config is used  */
#define __FPU_PRESENT             1       /*!< FPU present                                   */
#define __ICACHE_PRESENT          1       /*!< CM7 instruction cache present                 */
#define __DCACHE_PRESENT          1       /*!< CM7 data cache present                        */

/* define interrupt number */
typedef enum IRQn
{
    /* Cortex-M7 processor exceptions numbers */
    NonMaskableInt_IRQn             = -14,    /*!< 2 non maskable interrupt                                                             */
    HardFault_IRQn                  = -13,    /*!< 4 Cortex-M memory management interrupt                                               */
    MemoryManagement_IRQn           = -12,    /*!< 4 Cortex-M memory management interrupt                                               */
    BusFault_IRQn                   = -11,    /*!< 5 Cortex-M bus fault interrupt                                                       */
    UsageFault_IRQn                 = -10,    /*!< 6 Cortex-M usage fault interrupt                                                     */
    SVCall_IRQn                     = -5,     /*!< 11 Cortex-M sv call interrupt                                                        */
    DebugMonitor_IRQn               = -4,     /*!< 12 Cortex-M debug monitor interrupt                                                  */
    PendSV_IRQn                     = -2,     /*!< 14 Cortex-M pend sv interrupt                                                        */
    SysTick_IRQn                    = -1,     /*!< 15 Cortex-M system tick interrupt                                                    */
    /* interruput numbers */
    WWDGT_IRQn                      = 0 ,     /*!< WWDGT interrupt                                                                      */
    VAVD_LVD_VOVD_VUVD_IRQn         = 1 ,     /*!< VAVD / LVD / VOVD / VUVD through exti line detection interrupt                       */
    TAMPER_STAMP_LXTAL_IRQn         = 2 ,     /*!< RTC tamper and timestamp from EXTI interrupt, LXTAL clock stuck interrupt            */
    RTC_WKUP_IRQn                   = 3 ,     /*!< RTC wakeup from EXTI interrupt                                                       */
    NVMC_IRQn                       = 4 ,     /*!< NVMC global interrupt                                                                */
    RCU_IRQn                        = 5 ,     /*!< RCU global interrupt                                                                 */
    EXTI0_IRQn                      = 6 ,     /*!< EXTI line0 interrupt                                                                 */
    EXTI1_IRQn                      = 7 ,     /*!< EXTI line1 interrupt                                                                 */
    EXTI2_IRQn                      = 8 ,     /*!< EXTI line2 interrupt                                                                 */
    EXTI3_IRQn                      = 9 ,     /*!< EXTI line3 interrupt                                                                 */
    EXTI4_IRQn                      = 10,     /*!< EXTI line4 interrupt                                                                 */
    DMA0_Channel0_IRQn              = 11,     /*!< DMA0 channel0 global interrupt                                                       */
    DMA0_Channel1_IRQn              = 12,     /*!< DMA0 channel1 global interrupt                                                       */
    DMA0_Channel2_IRQn              = 13,     /*!< DMA0 channel2 global interrupt                                                       */
    DMA0_Channel3_IRQn              = 14,     /*!< DMA0 channel3 global interrupt                                                       */
    DMA0_Channel4_IRQn              = 15,     /*!< DMA0 channel4 global interrupt                                                       */
    DMA0_Channel5_IRQn              = 16,     /*!< DMA0 channel5 global interrupt                                                       */
    DMA0_Channel6_IRQn              = 17,     /*!< DMA0 channel6 global interrupt                                                       */
    ADC0_1_RDCM_IRQn                = 18,     /*!< ADC0 and ADC1 global interrupt, RDCM global interrupt                                */
    EXTI5_9_IRQn                    = 23,     /*!< EXTI line5-9 interrupt                                                               */
    TIMER0_BRK_IRQn                 = 24,     /*!< TIMER0 break interrupt                                                               */
    TIMER0_UP_IRQn                  = 25,     /*!< TIMER0 update interrupt                                                              */
    TIMER0_TRG_CMT_IRQn             = 26,     /*!< TIMER0 trigger and commutation interrupt                                             */
    TIMER0_Channel_IRQn             = 27,     /*!< TIMER0 capture compare interrupt                                                     */
    TIMER1_IRQn                     = 28,     /*!< TIMER1 global interrupt                                                              */
    TIMER2_IRQn                     = 29,     /*!< TIMER2 global interrupt                                                              */
    TIMER3_IRQn                     = 30,     /*!< TIMER3 global interrupt                                                              */
    I2C0_EV_IRQn                    = 31,     /*!< I2C0 event interrupt                                                                 */
    I2C0_ER_IRQn                    = 32,     /*!< I2C0 error interrupt                                                                 */
    I2C1_EV_IRQn                    = 33,     /*!< I2C1 event interrupt                                                                 */
    I2C1_ER_IRQn                    = 34,     /*!< I2C1 error interrupt                                                                 */
    SPI0_IRQn                       = 35,     /*!< SPI0 global interrupt                                                                */
    SPI1_IRQn                       = 36,     /*!< SPI1 global interrupt                                                                */
    USART0_IRQn                     = 37,     /*!< USART0 global and wakeup interrupt                                                   */
    USART1_IRQn                     = 38,     /*!< USART1 global and wakeup interrupt                                                   */
    USART2_IRQn                     = 39,     /*!< USART2 global and wakeup interrupt                                                   */
    EXTI10_15_IRQn                  = 40,     /*!< EXTI line10-15 interrupt                                                             */
    RTC_Alarm_IRQn                  = 41,     /*!< RTC alarm from EXTI interrupt                                                        */
    TIMER7_BRK_IRQn                 = 43,     /*!< TIMER7 break interrupt                                                               */
    TIMER7_UP_IRQn                  = 44,     /*!< TIMER7 update interrupt                                                              */
    TIMER7_TRG_CMT_IRQn             = 45,     /*!< TIMER7 trigger and commutation interrupt                                             */
    TIMER7_Channel_IRQn             = 46,     /*!< TIMER7 capture compare interrupt                                                     */
    DMA0_Channel7_IRQn              = 47,     /*!< DMA0 channel7 global interrupt                                                       */
    EXMC_IRQn                       = 48,     /*!< EXMC global interrupt                                                                */
    SDIO0_IRQn                      = 49,     /*!< SDIO0 global interrupt                                                               */
    TIMER4_IRQn                     = 50,     /*!< TIMER4 global interrupt                                                              */
    SPI2_IRQn                       = 51,     /*!< SPI2 global interrupt                                                                */
    UART3_IRQn                      = 52,     /*!< UART3 global interrupt                                                               */
    UART4_IRQn                      = 53,     /*!< UART4 global interrupt                                                               */
    TIMER5_DAC_UDR_IRQn             = 54,     /*!< TIMER5 global interrupt and DAC underrun error interrupt                             */
    TIMER6_IRQn                     = 55,     /*!< TIMER6 global interrupt                                                              */
    DMA1_Channel0_IRQn              = 56,     /*!< DMA1 channel0 global interrupt                                                       */
    DMA1_Channel1_IRQn              = 57,     /*!< DMA1 channel1 global interrupt                                                       */
    DMA1_Channel2_IRQn              = 58,     /*!< DMA1 channel2 global interrupt                                                       */
    DMA1_Channel3_IRQn              = 59,     /*!< DMA1 channel3 global interrupt                                                       */
    DMA1_Channel4_IRQn              = 60,     /*!< DMA1 channel4 global interrupt                                                       */
    ENET0_IRQn                      = 61,     /*!< ENET0 global interrupt                                                               */
    ENET0_WKUP_IRQn                 = 62,     /*!< ENET0 wakeup from EXTI interrupt                                                     */
    DMA1_Channel5_IRQn              = 68,     /*!< DMA1 channel5 global interrupt                                                       */
    DMA1_Channel6_IRQn              = 69,     /*!< DMA1 channel6 global interrupt                                                       */
    DMA1_Channel7_IRQn              = 70,     /*!< DMA1 channel7 global interrupt                                                       */
    USART5_IRQn                     = 71,     /*!< USART5 global and wakeup interrupt                                                   */
    I2C2_EV_IRQn                    = 72,     /*!< I2C2 event interrupt                                                                 */
    I2C2_ER_IRQn                    = 73,     /*!< I2C2 error interrupt                                                                 */
    USBHS0_EP1_OUT_IRQn             = 74,     /*!< USBHS0 endpoint 1 out interrupt                                                      */
    USBHS0_EP1_IN_IRQn              = 75,     /*!< USBHS0 endpoint 1 in interrupt                                                       */
    USBHS0_WKUP_IRQn                = 76,     /*!< USBHS0 wakeup from EXTI interrupt                                                    */
    USBHS0_IRQn                     = 77,     /*!< USBHS0 global interrupt                                                              */
    DCI_IRQn                        = 78,     /*!< DCI global interrupt                                                                 */
    CAU_IRQn                        = 79,     /*!< CAU global interrupt                                                                 */
    HAU_TRNG_IRQn                   = 80,     /*!< HAU and TRNG global interrupt                                                        */
    FPU_IRQn                        = 81,     /*!< FPU global interrupt                                                                 */
    UART6_IRQn                      = 82,     /*!< UART6 global interrupt                                                               */
    UART7_IRQn                      = 83,     /*!< UART7 global interrupt                                                               */
    SPI3_IRQn                       = 84,     /*!< SPI3 global interrupt                                                                */
    SPI4_IRQn                       = 85,     /*!< SPI4 global interrupt                                                                */
    SPI5_IRQn                       = 86,     /*!< SPI5 global interrupt                                                                */
    SAI0_IRQn                       = 87,     /*!< SAI0 global interrupt                                                                */
    TLI_IRQn                        = 88,     /*!< TLI global interrupt                                                                 */
    TLI_ER_IRQn                     = 89,     /*!< TLI error interrupt                                                                  */
    IPA_IRQn                        = 90,     /*!< IPA global interrupt                                                                 */
    SAI1_IRQn                       = 91,     /*!< SAI1 global interrupt                                                                */
    OSPI0_IRQn                      = 92,     /*!< OSPI0 global interrupt                                                               */
    I2C3_EV_IRQn                    = 95,     /*!< I2C3 event interrupt                                                                 */
    I2C3_ER_IRQn                    = 96,     /*!< I2C3 error interrupt                                                                 */
    RSPDIF_IRQn                     = 97,     /*!< RSPDIF global interrupt                                                              */
    DMAMUX_OVR_IRQn                 = 102,    /*!< DMAMUX overrun interrupt                                                             */
    HPDF_INT4_IRQn                  = 109,    /*!< HPDF global interrupt 4                                                              */
    HPDF_INT0_IRQn                  = 110,    /*!< HPDF global interrupt 0                                                              */
    HPDF_INT1_IRQn                  = 111,    /*!< HPDF global interrupt 1                                                              */
    HPDF_INT2_IRQn                  = 112,    /*!< HPDF global interrupt 2                                                              */
    HPDF_INT3_IRQn                  = 113,    /*!< HPDF global interrupt 3                                                              */
    SAI2_IRQn                       = 114,    /*!< SAI2 global interrupt                                                                */
    TIMER14_IRQn                    = 116,    /*!< TIMER14 global interrupt                                                             */
    TIMER15_IRQn                    = 117,    /*!< TIMER15 global interrupt                                                             */
    TIMER16_IRQn                    = 118,    /*!< TIMER16 global interrupt                                                             */
    MDIO_IRQn                       = 120,    /*!< MDIO global interrupt                                                                */
    MDMA_IRQn                       = 122,    /*!< MDMA global interrupt                                                                */
    SDIO1_IRQn                      = 124,    /*!< SDIO1 global interrupt                                                               */
    HWSEM_IRQn                      = 125,    /*!< HWSEM global interrupt                                                               */
    ADC2_IRQn                       = 127,    /*!< ADC2 global interrupt                                                                */
    CMP0_1_IRQn                     = 137,    /*!< CMP0 and CMP1 global interrupt, CMP0 and CMP1 through EXTI line detection interrupt  */
    CTC_IRQn                        = 144,    /*!< CTC interrupt                                                                        */
    RAMECCMU_IRQn                   = 145,    /*!< RAMECCMU global interrupt                                                            */
    SAI3_IRQn                       = 146,    /*!< SAI3 global interrupt                                                                */
    OSPI1_IRQn                      = 150,    /*!< OSPI1 global interrupt                                                               */
    RTDEC0_IRQn                     = 151,    /*!< RTDEC0 global interrupt                                                              */
    RTDEC1_IRQn                     = 152,    /*!< RTDEC1 global interrupt                                                              */
    FAC_IRQn                        = 153,    /*!< FAC global interrupt                                                                 */
    TMU_IRQn                        = 154,    /*!< TMU global interrupt                                                                 */
    FFT_IRQn                        = 155,    /*!< FFT global interrupt                                                                 */
    ESC_SYNC0_IRQn                  = 156,    /*!< ESC SYNC0 interrupt                                                                  */
    ESC_SYNC1_IRQn                  = 157,    /*!< ESC SYNC1 interrupt                                                                  */
    ESC_IRQn                        = 158,    /*!< ESC IRQ interrupt                                                                    */
    TIMER22_IRQn                    = 161,    /*!< TIMER22 global interrupt                                                             */
    TIMER23_IRQn                    = 162,    /*!< TIMER23 global interrupt                                                             */
    TIMER30_IRQn                    = 163,    /*!< TIMER30 global interrupt                                                             */
    TIMER31_IRQn                    = 164,    /*!< TIMER31 global interrupt                                                             */
    TIMER40_IRQn                    = 165,    /*!< TIMER40 global interrupt                                                             */
    TIMER41_IRQn                    = 166,    /*!< TIMER41 global interrupt                                                             */
    TIMER42_IRQn                    = 167,    /*!< TIMER42 global interrupt                                                             */
    TIMER43_IRQn                    = 168,    /*!< TIMER43 global interrupt                                                             */
    TIMER44_IRQn                    = 169,    /*!< TIMER44 global interrupt                                                             */
    TIMER50_IRQn                    = 170,    /*!< TIMER50 global interrupt                                                             */
    TIMER51_IRQn                    = 171,    /*!< TIMER51 global interrupt                                                             */
    USBHS1_EP1_OUT_IRQn             = 172,    /*!< USBHS1 endpoint 1 out interrupt                                                      */
    USBHS1_EP1_IN_IRQn              = 173,    /*!< USBHS1 endpoint 1 in interrupt                                                       */
    USBHS1_WKUP_IRQn                = 174,    /*!< USBHS1 wakeup from EXTI interrupt                                                    */
    USBHS1_IRQn                     = 175,    /*!< USBHS1 global interrupt                                                              */
    ENET1_IRQn                      = 176,    /*!< ENET1 global interrupt                                                               */
    ENET1_WKUP_IRQn                 = 177,    /*!< ENET1 wakeup from EXTI interrupt                                                     */
    CAN0_WKUP_IRQn                  = 179,    /*!< CAN0 wakeup through EXTI line detection interrupt                                    */
    CAN0_Message_IRQn               = 180,    /*!< CAN0 interrupt for message buffer                                                    */
    CAN0_Busoff_IRQn                = 181,    /*!< CAN0 interrupt for bus off / bus off done                                            */
    CAN0_Error_IRQn                 = 182,    /*!< CAN0 interrupt for error                                                             */
    CAN0_FastError_IRQn             = 183,    /*!< CAN0 interrupt for error in fast transmission                                        */
    CAN0_TEC_IRQn                   = 184,    /*!< CAN0 interrupt for transmit warning                                                  */
    CAN0_REC_IRQn                   = 185,    /*!< CAN0 interrupt for receive warning                                                   */
    CAN1_WKUP_IRQn                  = 186,    /*!< CAN1 wakeup through EXTI line detection interrupt                                    */
    CAN1_Message_IRQn               = 187,    /*!< CAN1 interrupt for message buffer                                                    */
    CAN1_Busoff_IRQn                = 188,    /*!< CAN1 interrupt for bus off / bus off done                                            */
    CAN1_Error_IRQn                 = 189,    /*!< CAN1 interrupt for error                                                             */
    CAN1_FastError_IRQn             = 190,    /*!< CAN1 interrupt for error in fast transmission                                        */
    CAN1_TEC_IRQn                   = 191,    /*!< CAN1 interrupt for transmit warning                                                  */
    CAN1_REC_IRQn                   = 192,    /*!< CAN1 interrupt for receive warning                                                   */
    CAN2_WKUP_IRQn                  = 193,    /*!< CAN2 wakeup through EXTI line detection interrupt                                    */
    CAN2_Message_IRQn               = 194,    /*!< CAN2 interrupt for message buffer                                                    */
    CAN2_Busoff_IRQn                = 195,    /*!< CAN2 interrupt for bus off / bus off done                                            */
    CAN2_Error_IRQn                 = 196,    /*!< CAN2 interrupt for error                                                             */
    CAN2_FastError_IRQn             = 197,    /*!< CAN2 interrupt for error in fast transmission                                        */
    CAN2_TEC_IRQn                   = 198,    /*!< CAN2 interrupt for transmit warning                                                  */
    CAN2_REC_IRQn                   = 199,    /*!< CAN2 interrupt for receive warning                                                   */
    OTP_IRQn                        = 200,    /*!< OTP global interrupt                                                                 */
    I2C0_WKUP_IRQn                  = 201,    /*!< I2C0 wakeup through EXTI line detection interrupt                                    */
    I2C1_WKUP_IRQn                  = 202,    /*!< I2C1 wakeup through EXTI line detection interrupt                                    */
    I2C2_WKUP_IRQn                  = 203,    /*!< I2C2 wakeup through EXTI line detection interrupt                                    */
    I2C3_WKUP_IRQn                  = 204,    /*!< I2C3 wakeup through EXTI line detection interrupt                                    */
    LPDTS_IRQn                      = 205,    /*!< LPDTS interrupt                                                                      */
    LPDTS_WKUP_IRQn                 = 206,    /*!< LPDTS wakeup through EXTI line detection interrupt                                   */
    TIMER0_DEC_IRQn                 = 207,    /*!< TIMER0 DEC interrupt                                                                 */
    TIMER7_DEC_IRQn                 = 208,    /*!< TIMER7 DEC interrupt                                                                 */
    TIMER1_DEC_IRQn                 = 209,    /*!< TIMER1 DEC interrupt                                                                 */
    TIMER2_DEC_IRQn                 = 210,    /*!< TIMER2 DEC interrupt                                                                 */
    TIMER3_DEC_IRQn                 = 211,    /*!< TIMER3 DEC interrupt                                                                 */
    TIMER4_DEC_IRQn                 = 212,    /*!< TIMER4 DEC interrupt                                                                 */
    TIMER22_DEC_IRQn                = 213,    /*!< TIMER22 DEC interrupt                                                                */
    TIMER23_DEC_IRQn                = 214,    /*!< TIMER23 DEC interrupt                                                                */
    TIMER30_DEC_IRQn                = 215,    /*!< TIMER30 DEC interrupt                                                                */
    TIMER31_DEC_IRQn                = 216,    /*!< TIMER31 DEC interrupt                                                                */
    CPU_DCACHE_ERR_IRQn             = 217,    /*!< CPU D-Cache error detection interrupt                                                */
    CPU_ICACHE_ERR_IRQn             = 218,    /*!< CPU I-Cache error detection interrupt                                                */
    VOVD_VUVD_FILTER_IRQn           = 219,    /*!< VOVD / VUVD interrupt after digital filtering interrupt                                 */
    TIMER0_Channel_BRK_IRQn         = 221,    /*!< TIMER0 channel break interrupt                                                       */
    TIMER7_Channel_BRK_IRQn         = 222,    /*!< TIMER7 channel break interrupt                                                       */
    DSI_IRQn                        = 223,    /*!< DSI global interrupt                                                                 */
    PKCAU_IRQn                      = 224,    /*!< PKCAU global interrupt                                                               */
    ESC_BRIDGE_IRQn                 = 225,    /*!< ESC internal interrupt                                                               */
    EDIM_IRQn                       = 226     /*!< EDIM global interrupt                                                                */
} IRQn_Type;

/* includes */
#include "core_cm7.h"
#include "system_gd32h77x_78x.h"
#include <stdint.h>
#ifdef FW_DEBUG_ERR_REPORT
#include "gd32h77x_78x_err_report.h"
#endif /* FW_DEBUG_ERR_REPORT */

/* enum definitions */
typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;
typedef enum {RESET = 0, SET = !RESET} FlagStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus;

/* bit operations */
#define REG64(addr)                  (*(volatile uint64_t *)(uint32_t)(addr))
#define REG32(addr)                  (*(volatile uint32_t *)(uint32_t)(addr))
#define REG16(addr)                  (*(volatile uint16_t *)(uint32_t)(addr))
#define REG8(addr)                   (*(volatile uint8_t *)(uint32_t)(addr))
#ifndef BIT
#define BIT(x)                       ((uint32_t)((uint32_t)0x01U << (x)))
#endif
#define BITS(start, end)             ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(end)))) 
#define GET_BITS(regval, start, end) (((regval) & BITS((start),(end))) >> (start))

/* main CNVM and SRAM memory map */
#define CNVM_BASE             ((uint32_t)0x08010000U)       /*!< CNVM base address                */
#define SRAM_BASE             ((uint32_t)0x24000000U)       /*!< SRAM base address                */

/* peripheral memory map */
#define APB1_BUS_BASE         ((uint32_t)0x40000000U)       /*!< APB1 base address                */
#define APB2_BUS_BASE         ((uint32_t)0x40010000U)       /*!< APB2 base address                */
#define APB3_BUS_BASE         ((uint32_t)0x50000000U)       /*!< APB3 base address                */
#define APB4_BUS_BASE         ((uint32_t)0x58000000U)       /*!< APB4 base address                */
#define AHB1_BUS_BASE         ((uint32_t)0x40020000U)       /*!< AHB1 base address                */
#define AHB2_BUS_BASE         ((uint32_t)0x48000000U)       /*!< AHB2 base address                */
#define AHB3_BUS_BASE         ((uint32_t)0x51000000U)       /*!< AHB3 base address                */
#define AHB4_BUS_BASE         ((uint32_t)0x58010000U)       /*!< AHB4 base address                */

/* advanced peripheral bus 1 memory map */
#define TIMER_BASE            (APB1_BUS_BASE + 0x00000000U) /*!< TIMER base address               */
#define SPI_BASE              (APB1_BUS_BASE + 0x00003800U) /*!< SPI base address                 */
#define RSPDIF_BASE           (APB1_BUS_BASE + 0x00004000U) /*!< RSPDIF base address              */
#define USART_BASE            (APB1_BUS_BASE + 0x00004400U) /*!< USART base address               */
#define I2C_BASE              (APB1_BUS_BASE + 0x00005400U) /*!< I2C base address                 */
#define DAC_BASE              (APB1_BUS_BASE + 0x00007400U) /*!< DAC base address                 */
#define CTC_BASE              (APB1_BUS_BASE + 0x00008400U) /*!< CTC base address                 */
#define MDIO_BASE             (APB1_BUS_BASE + 0x00009400U) /*!< MDIO base address                */
#define EDIM_BASE             (APB1_BUS_BASE + 0x0000C400U) /*!< EDIM base address                */

/* advanced peripheral bus 2 memory map */
#define ADC_BASE              (APB2_BUS_BASE + 0x00002400U) /*!< ADC base address                 */
#define SAI_BASE              (APB2_BUS_BASE + 0x00005800U) /*!< SAI base address                 */
#define RDCM_BASE             (APB2_BUS_BASE + 0x00006400U) /*!< RDCM base address                */
#define HPDF_BASE             (APB2_BUS_BASE + 0x00007000U) /*!< HPDF base address                */
#define TRIGSEL_BASE          (APB2_BUS_BASE + 0x00008400U) /*!< TRIGSEL base address             */
#define EDOUT_BASE            (APB2_BUS_BASE + 0x00008800U) /*!< EDOUT base address               */
#define CAN_BASE              (APB2_BUS_BASE + 0x0000A000U) /*!< CAN base address                 */

/* advanced peripheral bus 3 memory map */
#define TLI_BASE              (APB3_BUS_BASE + 0x00001000U) /*!< TLI base address                 */
#define WWDGT_BASE            (APB3_BUS_BASE + 0x00003000U) /*!< WWDGT base address               */

/* advanced peripheral bus 4 memory map */
#define EXTI_BASE             (APB4_BUS_BASE + 0x00000000U) /*!< EXTI base address                */
#define SYSCFG_BASE           (APB4_BUS_BASE + 0x00000400U) /*!< SYSCFG base address              */
#define CMP_BASE              (APB4_BUS_BASE + 0x00003800U) /*!< CMP base address                 */
#define VREF_BASE             (APB4_BUS_BASE + 0x00003C00U) /*!< VREF base address                */
#define RTC_BASE              (APB4_BUS_BASE + 0x00004000U) /*!< RTC base address                 */
#define FWDGT_BASE            (APB4_BUS_BASE + 0x00004800U) /*!< FWDGT base address               */
#define PMU_BASE              (APB4_BUS_BASE + 0x00005800U) /*!< PMU base address                 */
#define LPDTS_BASE            (APB4_BUS_BASE + 0x00006800U) /*!< LPDTS base address               */

/* advanced high performance bus 1 memory map */
#define DMA_BASE              (AHB1_BUS_BASE + 0x00000000U) /*!< DMA base address                 */
#define DMAMUX_BASE           (AHB1_BUS_BASE + 0x00000800U) /*!< DMAMUX base address              */
#define ENET_BASE             (AHB1_BUS_BASE + 0x00008000U) /*!< ENET base address                */
#define USBHS_BASE            (AHB1_BUS_BASE + 0x00020000U) /*!< USBHS base address               */

/* advanced high performance bus 2 memory map */
#define PKCAU_BASE            (AHB2_BUS_BASE + 0x00000000U) /*!< PKCAU base address               */
#define DCI_BASE              (AHB2_BUS_BASE + 0x00020000U) /*!< DCI base address                 */
#define GPSI_BASE             (AHB2_BUS_BASE + 0x00020200U) /*!< GPSI base address                */
#define CAU_BASE              (AHB2_BUS_BASE + 0x00021000U) /*!< CAU base address                 */
#define HAU_BASE              (AHB2_BUS_BASE + 0x00021400U) /*!< HAU base address                 */
#define TRNG_BASE             (AHB2_BUS_BASE + 0x00021800U) /*!< TRNG base address                */
#define SDIO_BASE             (AHB2_BUS_BASE + 0x00022400U) /*!< SDIO base address                */
#define CPDM_BASE             (AHB2_BUS_BASE + 0x00022800U) /*!< CPDM base address                */
#define RAMECCMU_BASE         (AHB2_BUS_BASE + 0x00023000U) /*!< RAMECCMU base address            */
#define FFT_BASE              (AHB2_BUS_BASE + 0x00024000U) /*!< FFT base address                 */
#define TMU_BASE              (AHB2_BUS_BASE + 0x00024400U) /*!< TMU base address                 */
#define FAC_BASE              (AHB2_BUS_BASE + 0x00024800U) /*!< FAC base address                 */

/* advanced high performance bus 3 memory map */
#define AXIM_BASE             (AHB3_BUS_BASE + 0x00000000U) /*!< AXIM base address                */
#define MDMA_BASE             (AHB3_BUS_BASE + 0x01000000U) /*!< MDMA base address                */
#define IPA_BASE              (AHB3_BUS_BASE + 0x01001000U) /*!< IPA base address                 */
#define NVMC_BASE             (AHB3_BUS_BASE + 0x01002000U) /*!< NVMC base address                */
#define DSI_BASE              (AHB3_BUS_BASE + 0x01003000U) /*!< MIPI DSI base address            */
#define EXMC_BASE             (AHB3_BUS_BASE + 0x01004000U) /*!< EXMC base address                */
#define OSPI_BASE             (AHB3_BUS_BASE + 0x01005000U) /*!< OSPI base address                */
#define OSPM_BASE             (AHB3_BUS_BASE + 0x0100B400U) /*!< OSPM base address                */
#define RTDEC_BASE            (AHB3_BUS_BASE + 0x0100B800U) /*!< RTDEC base address               */

/* advanced high performance bus 4 memory map */
#define GPIO_BASE             (AHB4_BUS_BASE + 0x00010000U) /*!< GPIO base address                */
#define RCU_BASE              (AHB4_BUS_BASE + 0x00014400U) /*!< RCU base address                 */
#define CRC_BASE              (AHB4_BUS_BASE + 0x00014C00U) /*!< CRC base address                 */
#define HWSEM_BASE            (AHB4_BUS_BASE + 0x00016400U) /*!< HWSEM base address               */
#define ESC_BASE              (0x5F000000U)                 /*!< ESC base address                 */

/* option byte and debug memory map */
#define OB_BASE               ((uint32_t)0x1FFFF800U)       /*!< OB base address                  */
#define DBG_BASE              ((uint32_t)0xE00E1000U)       /*!< DBG base address                 */

/* define marco USE_STDPERIPH_DRIVER */
#if !defined  USE_STDPERIPH_DRIVER
#define USE_STDPERIPH_DRIVER
#endif
#ifdef USE_STDPERIPH_DRIVER
#include "gd32h77x_78x_libopt.h"
#endif /* USE_STDPERIPH_DRIVER */

#ifdef __cplusplus
}
#endif

#endif /* GD32H77X_78X_H */
