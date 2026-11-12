/*!
\file    gd32h77x_78x_syscfg.h
\brief   definitions for the SYSCFG

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

#ifndef GD32H77X_78X_SYSCFG_H
#define GD32H77X_78X_SYSCFG_H

#include "gd32h77x_78x.h"

/* SYSCFG definitions */
#define SYSCFG                              SYSCFG_BASE                                 /*!< SYSCFG base address */

/* registers definitions */
#define SYSCFG_PMCFG0                       REG32(SYSCFG + 0x00000004U)                 /*!< SYSCFG peripheral mode configuration register 0 */
#define SYSCFG_EXTISS0                      REG32(SYSCFG + 0x00000008U)                 /*!< EXTI sources selection register 0 */
#define SYSCFG_EXTISS1                      REG32(SYSCFG + 0x0000000CU)                 /*!< EXTI sources selection register 1 */
#define SYSCFG_EXTISS2                      REG32(SYSCFG + 0x00000010U)                 /*!< EXTI sources selection register 2 */
#define SYSCFG_EXTISS3                      REG32(SYSCFG + 0x00000014U)                 /*!< EXTI sources selection register 3 */
#define SYSCFG_LKCTL                        REG32(SYSCFG + 0x00000018U)                 /*!< SYSCFG lock control register */
#define SYSCFG_BUSTO                        REG32(SYSCFG + 0x0000001CU)                 /*!< Bus timeout enable control */
#define SYSCFG_CPSCTL                       REG32(SYSCFG + 0x00000020U)                 /*!< I/O compensation control register */
#define SYSCFG_CPSCCCFG                     REG32(SYSCFG + 0x00000028U)                 /*!< I/O compensation cell code configuration */
#define SYSCFG_TIMERCISEL0                  REG32(SYSCFG + 0x00000034U)                 /*!< Timer input selection register 0 */
#define SYSCFG_TIMERCISEL1                  REG32(SYSCFG + 0x00000038U)                 /*!< Timer input selection register 1 */
#define SYSCFG_TIMERCISEL3                  REG32(SYSCFG + 0x00000040U)                 /*!< Timer input selection register 3 */
#define SYSCFG_TIMERCISEL4                  REG32(SYSCFG + 0x00000044U)                 /*!< Timer input selection register 4 */
#define SYSCFG_TIMERCISEL5                  REG32(SYSCFG + 0x00000048U)                 /*!< Timer input selection register 5 */
#define SYSCFG_TIMERCISEL6                  REG32(SYSCFG + 0x0000004CU)                 /*!< Timer input selection register 6 */
#define SYSCFG_CPUICAC                      REG32(SYSCFG + 0x00000054U)                 /*!< CPU icache error status register */
#define SYSCFG_CPUDCAC                      REG32(SYSCFG + 0x00000058U)                 /*!< CPU dcache error status register */
#define SYSCFG_CFPUINTEN                    REG32(SYSCFG + 0x0000005CU)                 /*!< CACHE and FPU interrupt enable register */
#define SYSCFG_SRAMCFG0                     REG32(SYSCFG + 0x00000064U)                 /*!< SRAM configuration register 0*/
#define SYSCFG_BUSTOSTAT                    REG32(SYSCFG + 0x00000068U)                 /*!< Bus timeout status register */
#define SYSCFG_ESCCFG0                      REG32(SYSCFG + 0x0000006CU)                 /*!< ESC configuration register 0 */
#define SYSCFG_ESCCFG1                      REG32(SYSCFG + 0x00000070U)                 /*!< ESC configuration register 1 */
#define SYSCFG_ESCCFG2                      REG32(SYSCFG + 0x00000074U)                 /*!< ESC configuration register 2 */
#define SYSCFG_PMCFG1                       REG32(SYSCFG + 0x00000204U)                 /*!< SYSCFG peripheral mode configuration register 1 */
#define SYSCFG_USERCFG                      REG32(SYSCFG + 0x00000300U)                 /*!< User configuration register */

/* SYSCFG_PMCFG0 bits definitions */
#define SYSCFG_PMCFG0_I2C0FMPEN              BIT(0)                                     /*!< I2C0 fast mode plus enable */
#define SYSCFG_PMCFG0_I2C1FMPEN              BIT(1)                                     /*!< I2C1 fast mode plus enable */
#define SYSCFG_PMCFG0_I2C2FMPEN              BIT(2)                                     /*!< I2C2 fast mode plus enable */
#define SYSCFG_PMCFG0_I2C3FMPEN              BIT(3)                                     /*!< I2C3 fast mode plus enable */
#define SYSCFG_PMCFG0_PB6FMPEN               BIT(4)                                     /*!< I2C fast mode plus on PB6 pin enable */
#define SYSCFG_PMCFG0_PB7FMPEN               BIT(5)                                     /*!< I2C fast mode plus on PB7 pin enable */
#define SYSCFG_PMCFG0_PB8FMPEN               BIT(6)                                     /*!< I2C fast mode plus on PB8 pin enable */
#define SYSCFG_PMCFG0_PB9FMPEN               BIT(7)                                     /*!< I2C fast mode plus on PB9 pin enable */
#define SYSCFG_PMCFG0_ENET1_PHY_SEL          BIT(22)                                    /*!< Ethernet1 PHY interface selection */
#define SYSCFG_PMCFG0_ENET0_PHY_SEL          BIT(23)                                    /*!< Ethernet0 PHY interface selection */
#define SYSCFG_PMCFG0_PA0SWON                BIT(24)                                    /*!< PA0 switch open */
#define SYSCFG_PMCFG0_PA1SWON                BIT(25)                                    /*!< PA1 switch open */
#define SYSCFG_PMCFG0_PC2SWON                BIT(26)                                    /*!< PC2 switch open */
#define SYSCFG_PMCFG0_PC3SWON                BIT(27)                                    /*!< PC3 switch open */
#define SYSCFG_PMCFG0_IO_SEL_G0              BITS(28,30)                                /*!< Coder group 0 IO select */

/* SYSCFG_EXTISS0 bits definitions */
#define SYSCFG_EXTISS0_EXTI0_SS             BITS(0,3)                                   /*!< EXTI 0 configuration */
#define SYSCFG_EXTISS0_EXTI1_SS             BITS(4,7)                                   /*!< EXTI 1 configuration */
#define SYSCFG_EXTISS0_EXTI2_SS             BITS(8,11)                                  /*!< EXTI 2 configuration */
#define SYSCFG_EXTISS0_EXTI3_SS             BITS(12,15)                                 /*!< EXTI 3 configuration */

/* SYSCFG_EXTISS1 bits definitions */
#define SYSCFG_EXTISS1_EXTI4_SS             BITS(0,3)                                   /*!< EXTI 4 configuration */
#define SYSCFG_EXTISS1_EXTI5_SS             BITS(4,7)                                   /*!< EXTI 5 configuration */
#define SYSCFG_EXTISS1_EXTI6_SS             BITS(8,11)                                  /*!< EXTI 6 configuration */
#define SYSCFG_EXTISS1_EXTI7_SS             BITS(12,15)                                 /*!< EXTI 7 configuration */

/* SYSCFG_EXTISS2 bits definitions */
#define SYSCFG_EXTISS2_EXTI8_SS             BITS(0,3)                                   /*!< EXTI 8 configuration */
#define SYSCFG_EXTISS2_EXTI9_SS             BITS(4,7)                                   /*!< EXTI 9 configuration */
#define SYSCFG_EXTISS2_EXTI10_SS            BITS(8,11)                                  /*!< EXTI 10 configuration */
#define SYSCFG_EXTISS2_EXTI11_SS            BITS(12,15)                                 /*!< EXTI 11 configuration */

/* SYSCFG_EXTISS3 bits definitions */
#define SYSCFG_EXTISS3_EXTI12_SS            BITS(0,3)                                   /*!< EXTI 12 configuration */
#define SYSCFG_EXTISS3_EXTI13_SS            BITS(4,7)                                   /*!< EXTI 13 configuration */
#define SYSCFG_EXTISS3_EXTI14_SS            BITS(8,11)                                  /*!< EXTI 14 configuration */
#define SYSCFG_EXTISS3_EXTI15_SS            BITS(12,15)                                 /*!< EXTI 15 configuration */

/* SYSCFG_LKCTL bits definitions */
#define SYSCFG_LKCTL_LVD_LOCK               BIT(2)                                      /*!< programmable voltage detector lockup */
#define SYSCFG_LKCTL_CPU_LOCK               BIT(6)                                      /*!< CPU lockup */
#define SYSCFG_LKCTL_BKPRAM_LOCK            BIT(7)                                      /*!< Region 2 backup SRAM ECC double error lockup */
#define SYSCFG_LKCTL_SRAM1_LOCK             BIT(11)                                     /*!< Region 1 SRAM1 ECC double error lockup */
#define SYSCFG_LKCTL_SRAM0_LOCK             BIT(12)                                     /*!< Region 1 SRAM0 ECC double error lockup */
#define SYSCFG_LKCTL_DTCM_LOCK              BIT(13)                                     /*!< Region 0 DTCM ECC double error lock */
#define SYSCFG_LKCTL_ITCM_LOCK              BIT(14)                                     /*!< Region 0 ITCM-RAM ECC double error lock */
#define SYSCFG_LKCTL_AXIRAM_LOCK            BIT(15)                                     /*!< Region 0 AXI-SRAM ECC double error lock */

/* Bus Timeout bits definitions */
#define SYSCFG_BUSTO_SDIO0BUS               BIT(0)                                      /*!< SDIO0 BUS Timeout enable */
#define SYSCFG_BUSTO_CPUBUS                 BIT(1)                                      /*!< CPU BUS Timeout enable */
#define SYSCFG_BUSTO_TLIBUS                 BIT(2)                                      /*!< TLI BUS Timeout enable */
#define SYSCFG_BUSTO_MDMABUS                BIT(3)                                      /*!< MDMA BUS Timeout enable */
#define SYSCFG_BUSTO_IPABUS                 BIT(4)                                      /*!< IPA BUS Timeout enable */
#define SYSCFG_BUSTO_CPUAHBPBUS             BIT(5)                                      /*!< CPU AHBP BUS Timeout enable */
#define SYSCFG_BUSTO_DMA0MEMBUS             BIT(6)                                      /*!< DMA0 mem BUS Timeout enable */
#define SYSCFG_BUSTO_DMA0PERIPHBUS          BIT(7)                                      /*!< DMA0 per BUS Timeout enable */
#define SYSCFG_BUSTO_DMA1MEMBUS             BIT(8)                                      /*!< DMA1 mem BUS Timeout enable */
#define SYSCFG_BUSTO_DMA1PERIPHBUS          BIT(9)                                      /*!< DMA1 per BUS Timeout enable */
#define SYSCFG_BUSTO_ENET0BUS               BIT(10)                                     /*!< ENET0 BUS Timeout enable */
#define SYSCFG_BUSTO_ENET1BUS               BIT(11)                                     /*!< ENET1 BUS Timeout enable */
#define SYSCFG_BUSTO_SDIO1BUS               BIT(12)                                     /*!< SDIO1 BUS Timeout enable */
#define SYSCFG_BUSTO_USBHS0BUS              BIT(13)                                     /*!< USBHS0 BUS Timeout enable */
#define SYSCFG_BUSTO_USBHS1BUS              BIT(14)                                     /*!< USBHS1 BUS Timeout enable */
#define SYSCFG_BUSTO_FFTBUS                 BIT(15)                                     /*!< FFT BUS Timeout enable */
#define SYSCFG_BUSTO_ESCBUS                 BIT(16)                                     /*!< ETHERCAT BUS Timeout enable */

/* SYSCFG_CPSCTL bits definitions */
#define SYSCFG_CPSCTL_CPS_EN                BIT(0)                                      /*!< I/O compensation cell enable */
#define SYSCFG_CPSCTL_CPS_RDY               BIT(8)                                      /*!< Compensation cell ready flag */
#define SYSCFG_CPSCTL_IOSPDOP               BIT(16)                                     /*!< I/O speed optimization, high-speed at low-voltage */
#define SYSCFG_CPSCTL_IOLV                  BIT(23)                                     /*!< I/O in low voltage state */

/* SYSCFG_CPSCCCFG bits definitions */
#define SYSCFG_CPSCCCFG_NCPSCC              BITS(0,3)                                   /*!< NMOS compensation cell code */
#define SYSCFG_CPSCCCFG_PCPSCC              BITS(4,7)                                   /*!< PMOS compensation cell code */

/* SYSCFG_TIMERCISEL0 bits definitions */
#define SYSCFG_TIMER7_CI0_SEL               BIT(0)                                      /*!< Selects TIMER7_CI0 input */
#define SYSCFG_TIMER0_CI0_SEL               BIT(16)                                     /*!< Selects TIMER0_CI0 input */

/* SYSCFG_TIMERCISEL1 bits definitions */
#define SYSCFG_TIMER2_CI0_SEL               BITS(0,1)                                   /*!< Selects TIMER2_CI0 input */
#define SYSCFG_TIMER1_CI3_SEL               BITS(28,29)                                 /*!< Selects TIMER1_CI3 input */

/* SYSCFG_TIMERCISEL3 bits definitions */
#define SYSCFG_TIMER22_CI3_SEL              BITS(28,29)                                 /*!< Selects TIMER22_CI3 input */

/* SYSCFG_TIMERCISEL4 bits definitions */
#define SYSCFG_TIMER31_CI0_SEL              BITS(0,1)                                   /*!< Selects TIMER31_CI0 input */
#define SYSCFG_TIMER30_CI0_SEL              BITS(16,17)                                 /*!< Selects TIMER30_CI0 input */

/* SYSCFG_TIMERCISEL5 bits definitions */
#define SYSCFG_TIMER14_CI0_SEL              BITS(0,2)                                   /*!< Selects TIMER14_CI0 input */
#define SYSCFG_TIMER14_CI1_SEL              BITS(4,5)                                   /*!< Selects TIMER14_CI1 input */
#define SYSCFG_TIMER40_CI0_SEL              BITS(8,10)                                  /*!< Selects TIMER40_CI0 input */
#define SYSCFG_TIMER40_CI1_SEL              BITS(12,13)                                 /*!< Selects TIMER40_CI1 input */
#define SYSCFG_TIMER41_CI0_SEL              BITS(16,18)                                 /*!< Selects TIMER41_CI0 input */
#define SYSCFG_TIMER41_CI1_SEL              BITS(20,21)                                 /*!< Selects TIMER41_CI1 input */
#define SYSCFG_TIMER42_CI0_SEL              BITS(24,26)                                 /*!< Selects TIMER42_CI0 input */
#define SYSCFG_TIMER42_CI1_SEL              BITS(28,29)                                 /*!< Selects TIMER42_CI1 input */

/* SYSCFG_TIMERCISEL6 bits definitions */
#define SYSCFG_TIMER15_CI0_SEL              BITS(0,1)                                   /*!< Selects TIMER15_CI0 input */
#define SYSCFG_TIMER16_CI0_SEL              BITS(4,5)                                   /*!< Selects TIMER16_CI0 input */
#define SYSCFG_TIMER43_CI0_SEL              BITS(8,10)                                  /*!< Selects TIMER43_CI0 input */
#define SYSCFG_TIMER43_CI1_SEL              BITS(12,13)                                 /*!< Selects TIMER43_CI1 input */
#define SYSCFG_TIMER44_CI0_SEL              BITS(16,18)                                 /*!< Selects TIMER44_CI0 input */
#define SYSCFG_TIMER44_CI1_SEL              BITS(20,21)                                 /*!< Selects TIMER44_CI1 input */

/* CPU ICACHE error status bits definitions */
#define SYSCFG_CPUICAC_CPU_ICERR            BITS(6,27)                                  /*!< CPU ICACHE error bank information */
#define SYSCFG_CPUICAC_CPU_ICDET            BITS(28,31)                                 /*!< CPU ICACHE error detection information */

/* CPU DCACHE error status bits definitions */
#define SYSCFG_CPUDCAC_CPU_DCERR            BITS(6,27)                                  /*!< CPU DCACHE error bank information */
#define SYSCFG_CPUDCAC_CPU_DCDET            BITS(28,31)                                 /*!< CPU DCACHE error detection information */

/* CACHE and Floating point unit interrupts enable bits */
#define SYSCFG_CFPUINTEN_IOPIE              BIT(0)                                      /*!< Invalid operation Interrupt enable */
#define SYSCFG_CFPUINTEN_DZIE               BIT(1)                                      /*!< Divide-by-zero interrupt enable */
#define SYSCFG_CFPUINTEN_UFIE               BIT(2)                                      /*!< Underflow interrupt enable */
#define SYSCFG_CFPUINTEN_OVFIE              BIT(3)                                      /*!< Overflow interrupt enable */
#define SYSCFG_CFPUINTEN_IDIE               BIT(4)                                      /*!< Input abnormal interrupt enable */
#define SYSCFG_CFPUINTEN_IXIE               BIT(5)                                      /*!< Inexact interrupt enable */
#define SYSCFG_CFPUINTEN_CPU_DCDETIE        BITS(6,9)                                   /*!< CPU DCACHE error bank information int enable */
#define SYSCFG_CFPUINTEN_CPU_ICDETIE        BITS(10,13)                                 /*!< CPU ICACHE error detection information int enable */

/* SRAM configuration register 0 */
#define SYSCFG_SRAMCFG0_SECURE_SRAM_SIZE    BITS(0,1)                                   /*!< size of secure sram */

/* Bus Timeout status definitions */
#define SYSCFG_BUSTOSTAT_SDIO0BUSTOF        BIT(0)                                      /*!< SDIO0 BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_CPUBUSTOF          BIT(1)                                      /*!< CPU BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_TLIBUSTOF          BIT(2)                                      /*!< TLI BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_MDMABUSTOF         BIT(3)                                      /*!< MDMA BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_IPABUSTOF          BIT(4)                                      /*!< IPA BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_CPUAHBPBUSTOF      BIT(5)                                      /*!< CPU AHBP BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_DMA0MEMBUSTOF      BIT(6)                                      /*!< DMA0 mem BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_DMA0PERIPHBUSTOF   BIT(7)                                      /*!< DMA0 per BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_DMA1MEMBUSTOF      BIT(8)                                      /*!< DMA1 mem BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_DMA1PERIPHBUSTOF   BIT(9)                                      /*!< DMA1 per BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_ENET0BUSTOF        BIT(10)                                     /*!< ENET0 BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_ENET1BUSTOF        BIT(11)                                     /*!< ENET1 BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_SDIO1BUSTOF        BIT(12)                                     /*!< SDIO1 BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_USBHS0BUSTOF       BIT(13)                                     /*!< USBHS0 BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_USBHS1BUSTOF       BIT(14)                                     /*!< USBHS1 BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_FFTBUSTOF          BIT(15)                                     /*!< FFT BUS Timeout flag */
#define SYSCFG_BUSTOSTAT_ESCBUSTOF          BIT(16)                                     /*!< ETHERCAT BUS Timeout flag */

/* EtherCat configuration register 0 */
#define SYSCFG_ESCCFG0_ESC_EEPROM           BIT(0)                                      /*!< EtherCat EEPROM configuration */
#define SYSCFG_ESCCFG0_RMIITX_S0_VAL        BITS(1,2)                                   /*!< EtherCat tx_shift value of RMII SHIFT0 */
#define SYSCFG_ESCCFG0_RMIITX_S1_VAL        BITS(3,4)                                   /*!< EtherCat tx_shift value of RMII SHIFT1 */
#define SYSCFG_ESCCFG0_LINKACTLED0_POLSEL   BIT(7)                                      /*!< EtherCat link_act_led0 signal output active polarity selection */
#define SYSCFG_ESCCFG0_LINKACTLED1_POLSEL   BIT(8)                                      /*!< EtherCat link_act_led1 signal output active polarity selection */
#define SYSCFG_ESCCFG0_LINKACTLED2_POLSEL   BIT(9)                                      /*!< EtherCat link_act_led2 signal output active polarity selection */
#define SYSCFG_ESCCFG0_LEDRUN_POLSEL        BIT(10)                                     /*!< EtherCat led_run signal output active polarity selection */
#define SYSCFG_ESCCFG0_LEDERR_POLSEL        BIT(11)                                     /*!< EtherCat led_err signal output active polarity selection */
#define SYSCFG_ESCCFG0_RMII_S1              BITS(12,14)                                 /*!< EtherCat Clock compensation phase setting in RMII mode */
#define SYSCFG_ESCCFG0_RSTOUT_POLSEL        BIT(15)                                     /*!< EtherCat Reset_out signal output active polarity selection */
#define SYSCFG_ESCCFG0_NLINK0_POLSEL        BIT(16)                                     /*!< EtherCat NLINK0 signal input level polarity selection bits */
#define SYSCFG_ESCCFG0_NLINK1_POLSEL        BIT(17)                                     /*!< EtherCat NLINK1 signal input level polarity selection bits */
#define SYSCFG_ESCCFG0_NLINK2_POLSEL        BIT(18)                                     /*!< EtherCat NLINK2 signal input level polarity selection bits */
#define SYSCFG_ESCCFG0_SHIFTSTEN            BIT(19)                                     /*!< EtherCat Whether to enable the latch function of tx_shift */
#define SYSCFG_ESCCFG0_EEPROMSZ             BIT(20)                                     /*!< EtherCat Internal EEPROM capacity of ESC */
#define SYSCFG_ESCCFG0_PHY_OFFSETSEL        BIT(21)                                     /*!< EtherCat Whether to enable the PHY address offset function of ESC */
#define SYSCFG_ESCCFG0_PHY_OFFSET           BITS(22,26)                                 /*!< EtherCat PHY address offset */
#define SYSCFG_ESCCFG0_RMII_S0              BITS(27,29)                                 /*!< EtherCat Clock compensation phase setting in RMII mode */
#define SYSCFG_ESCCFG0_RMIIEN               BIT(30)                                     /*!< EtherCat RMII port enable */
#define SYSCFG_ESCCFG0_SMPS_DRIVE           BIT(31)                                     /*!< EtherCat SMPS_DRIVE's drive capability */

/* EtherCat configuration register 1 */
#define SYSCFG_ESCCFG1_ESC_SRAM             BITS(0,31)                                  /*!< EtherCat SRAM configuration bits */

/* EtherCat configuration register 2 */
#define SYSCFG_ESCCFG2_RST_OUT_CNT          BITS(0,31)                                  /*!< EtherCat number of clock cycles for which reset_out is held */

/* TIMER trigger selection register */
#define SYSCFG_TIMERCFG_TSCFG0              BITS(0,4)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG1              BITS(5,9)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG2              BITS(10,14)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG3              BITS(16,20)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG4              BITS(21,25)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG5              BITS(26,30)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG6              BITS(0,4)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG7              BITS(5,9)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG8              BITS(10,14)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG9              BITS(16,20)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG10             BITS(21,25)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG11             BITS(26,30)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG12             BITS(0,4)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG13             BITS(5,9)                                   /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG14             BITS(10,14)                                 /*!< TIMER trigger selection */
#define SYSCFG_TIMERCFG_TSCFG15             BITS(16,20)                                 /*!< TIMER trigger selection */

/* SYSCFG_PMCFG1 bits definitions */
#define SYSCFG_PMCFG1_STBOEN                BIT(0)                                      /*!< standby flag output from PC13 enable */
#define SYSCFG_PMCFG1_VOSCFGEN              BIT(1)                                      /*!< VOS configuration enable */
#define SYSCFG_PMCFG1_IO_SEL_G1             BITS(2,4)                                   /*!< Coder group 1 IO select */
#define SYSCFG_PMCFG1_CK_EXMC_DIS           BIT(5)                                      /*!< CK_EXMC clock disable */

/* SYSCFG_USERCFG bits definitions */
#define SYSCFG_USERCFG_BOR_TH               BITS(0,1)                                   /*!< BOR threshold status bits */
#define SYSCFG_USERCFG_BOOT_SEL             BIT(2)                                      /*!< BOOT selection */
#define SYSCFG_USERCFG_BOOT_MODE            BITS(4,6)                                   /*!< BOOT mode */

/* constants definitions */
/* I2Cx fast mode plus enable definitions */
#define SYSCFG_I2C0_FMP                     SYSCFG_PMCFG0_I2C0FMPEN                     /*!< I2C0 fast mode plus */
#define SYSCFG_I2C1_FMP                     SYSCFG_PMCFG0_I2C1FMPEN                     /*!< I2C1 fast mode plus */
#define SYSCFG_I2C2_FMP                     SYSCFG_PMCFG0_I2C2FMPEN                     /*!< I2C2 fast mode plus */
#define SYSCFG_I2C3_FMP                     SYSCFG_PMCFG0_I2C3FMPEN                     /*!< I2C3 fast mode plus */
#define SYSCFG_I2C_FMP_PB6                  SYSCFG_PMCFG0_PB6FMPEN                      /*!< I2C fast mode plus on PB6 pin */
#define SYSCFG_I2C_FMP_PB7                  SYSCFG_PMCFG0_PB7FMPEN                      /*!< I2C fast mode plus on PB7 pin */
#define SYSCFG_I2C_FMP_PB8                  SYSCFG_PMCFG0_PB8FMPEN                      /*!< I2C fast mode plus on PB8 pin */
#define SYSCFG_I2C_FMP_PB9                  SYSCFG_PMCFG0_PB9FMPEN                      /*!< I2C fast mode plus on PB9 pin */

/* pin analog switch definitions */
#define SYSCFG_PA0_ANALOG_SWITCH            SYSCFG_PMCFG0_PA0SWON                        /*!< PA0 analog switch */
#define SYSCFG_PA1_ANALOG_SWITCH            SYSCFG_PMCFG0_PA1SWON                        /*!< PA1 analog switch */
#define SYSCFG_PC2_ANALOG_SWITCH            SYSCFG_PMCFG0_PC2SWON                        /*!< PC2 analog switch */
#define SYSCFG_PC3_ANALOG_SWITCH            SYSCFG_PMCFG0_PC3SWON                        /*!< PC3 analog switch */
/* Ethernet PHY Mode definitions */
#define SYSCFG_ENET_PHY_MII                 ((uint32_t)0x00000000U)                     /*!< Ethernet PHY MII interface */
#define SYSCFG_ENET_PHY_RMII                ((uint32_t)0x00000001U)                     /*!< Ethernet PHY RMII interface */

/* Coder IO select */
#define SYSCFG_CODER_GROUP0                 ((uint32_t)0x0000001CU)                     /*!< coder IO group 0 */
#define SYSCFG_CODER_GROUP1                 ((uint32_t)0x00000002U)                     /*!< coder IO group 1 */

/* Coder IO select */
#define SYSCFG_CODER_IO_AFMT                ((uint32_t)0x00000000U)                     /*!< connect to AFMT IO */
#define SYSCFG_CODER_IO_TFMT                ((uint32_t)0x00000001U)                     /*!< connect to TFMT IO */
#define SYSCFG_CODER_IO_ENDAT               ((uint32_t)0x00000002U)                     /*!< connect to Endat IO */
#define SYSCFG_CODER_IO_BISS_C              ((uint32_t)0x00000003U)                     /*!< connect to BISS-C IO */
#define SYSCFG_CODER_IO_HDSL                ((uint32_t)0x00000005U)                     /*!< connect to HDSL IO */
#define SYSCFG_CODER_IO_NOT_CONNECTED       ((uint32_t)0x00000004U)                     /*!< not connected */

/* Ethernet 0 PHY interface selection */
#define ENET0_MEDIA_INTERFACE(regval)       (SYSCFG_PMCFG0_ENET0_PHY_SEL & ((uint32_t)(regval) << 23U))
/* Ethernet 1 PHY interface selection */
#define ENET1_MEDIA_INTERFACE(regval)       (SYSCFG_PMCFG0_ENET1_PHY_SEL & ((uint32_t)(regval) << 22U))

/* EXTI source select definitions */
#define EXTISS0                             ((uint8_t)0x00U)                            /*!< EXTI source select register 0 */
#define EXTISS1                             ((uint8_t)0x01U)                            /*!< EXTI source select register 1 */
#define EXTISS2                             ((uint8_t)0x02U)                            /*!< EXTI source select register 2 */
#define EXTISS3                             ((uint8_t)0x03U)                            /*!< EXTI source select register 3 */

/* EXTI source select mask bits definition */
#define EXTI_SS_MASK                        BITS(0,3)                                   /*!< EXTI source select mask */

/* EXTI source select jumping step definition */
#define EXTI_SS_JSTEP                       ((uint8_t)(0x04U))                          /*!< EXTI source select jumping step */

/* EXTI source select moving step definition */
#define EXTI_SS_MSTEP(pin)                  (EXTI_SS_JSTEP * ((pin) % EXTI_SS_JSTEP))   /*!< EXTI source select moving step */

/* EXTI source port definitions */
#define EXTI_SOURCE_GPIOA                   ((uint8_t)0x00U)                            /*!< EXTI GPIOA configuration */
#define EXTI_SOURCE_GPIOB                   ((uint8_t)0x01U)                            /*!< EXTI GPIOB configuration */
#define EXTI_SOURCE_GPIOC                   ((uint8_t)0x02U)                            /*!< EXTI GPIOC configuration */
#define EXTI_SOURCE_GPIOD                   ((uint8_t)0x03U)                            /*!< EXTI GPIOD configuration */
#define EXTI_SOURCE_GPIOE                   ((uint8_t)0x04U)                            /*!< EXTI GPIOE configuration */
#define EXTI_SOURCE_GPIOF                   ((uint8_t)0x05U)                            /*!< EXTI GPIOF configuration */
#define EXTI_SOURCE_GPIOG                   ((uint8_t)0x06U)                            /*!< EXTI GPIOG configuration */
#define EXTI_SOURCE_GPIOH                   ((uint8_t)0x07U)                            /*!< EXTI GPIOH configuration */
#define EXTI_SOURCE_GPIOJ                   ((uint8_t)0x09U)                            /*!< EXTI GPIOJ configuration */
#define EXTI_SOURCE_GPIOK                   ((uint8_t)0x0AU)                            /*!< EXTI GPIOK configuration */

/* EXTI source pin definitions */
#define EXTI_SOURCE_PIN0                    ((uint8_t)0x00U)                            /*!< EXTI GPIO pin0 configuration */
#define EXTI_SOURCE_PIN1                    ((uint8_t)0x01U)                            /*!< EXTI GPIO pin1 configuration */
#define EXTI_SOURCE_PIN2                    ((uint8_t)0x02U)                            /*!< EXTI GPIO pin2 configuration */
#define EXTI_SOURCE_PIN3                    ((uint8_t)0x03U)                            /*!< EXTI GPIO pin3 configuration */
#define EXTI_SOURCE_PIN4                    ((uint8_t)0x04U)                            /*!< EXTI GPIO pin4 configuration */
#define EXTI_SOURCE_PIN5                    ((uint8_t)0x05U)                            /*!< EXTI GPIO pin5 configuration */
#define EXTI_SOURCE_PIN6                    ((uint8_t)0x06U)                            /*!< EXTI GPIO pin6 configuration */
#define EXTI_SOURCE_PIN7                    ((uint8_t)0x07U)                            /*!< EXTI GPIO pin7 configuration */
#define EXTI_SOURCE_PIN8                    ((uint8_t)0x08U)                            /*!< EXTI GPIO pin8 configuration */
#define EXTI_SOURCE_PIN9                    ((uint8_t)0x09U)                            /*!< EXTI GPIO pin9 configuration */
#define EXTI_SOURCE_PIN10                   ((uint8_t)0x0AU)                            /*!< EXTI GPIO pin10 configuration */
#define EXTI_SOURCE_PIN11                   ((uint8_t)0x0BU)                            /*!< EXTI GPIO pin11 configuration */
#define EXTI_SOURCE_PIN12                   ((uint8_t)0x0CU)                            /*!< EXTI GPIO pin12 configuration */
#define EXTI_SOURCE_PIN13                   ((uint8_t)0x0DU)                            /*!< EXTI GPIO pin13 configuration */
#define EXTI_SOURCE_PIN14                   ((uint8_t)0x0EU)                            /*!< EXTI GPIO pin14 configuration */
#define EXTI_SOURCE_PIN15                   ((uint8_t)0x0FU)                            /*!< EXTI GPIO pin15 configuration */

/* MOS mode definitions */
#define PMOS_COMPENSATION                   ((uint8_t)0x00U)                            /*!< PMOS compensation */
#define NMOS_COMPENSATION                   ((uint8_t)0x01U)                            /*!< NMOS compensation */

/* timer input select definition */
#define TIMERCISEL0                         ((uint8_t)0x00U)                            /*!< TIMER input select register 0 */
#define TIMERCISEL1                         ((uint8_t)0x01U)                            /*!< TIMER input select register 1 */
#define TIMERCISEL3                         ((uint8_t)0x03U)                            /*!< TIMER input select register 3 */
#define TIMERCISEL4                         ((uint8_t)0x04U)                            /*!< TIMER input select register 4 */
#define TIMERCISEL5                         ((uint8_t)0x05U)                            /*!< TIMER input select register 5 */
#define TIMERCISEL6                         ((uint8_t)0x06U)                            /*!< TIMER input select register 6 */

/* define the timer bit position and its register index offset */
#define TIMER_REGIDX_BIT(regidx, bitpos, value)   (((uint32_t)(regidx) << 24U) | (uint32_t)((bitpos) << 16U)\
        | ((uint32_t)(value)))
#define TIMER_REG_INDEX(val)                (((uint32_t)(val) & 0xFF000000U) >> 24U)
#define TIMER_BIT_POS(val)                  (((uint32_t)(val) & 0x00FF0000U) >> 16U)
#define TIMER_SEL_VAL(val)                  ((uint32_t)(val) & 0x000000FFU)

/* TIMERx channel input select definitions */
typedef enum {
    TIMER7_CI0_INPUT_TIMER7_CH0         = TIMER_REGIDX_BIT(TIMERCISEL0, 0U, 0U),        /*!< select TIMER7 CH0 as TIMER7 CI0 */
    TIMER7_CI0_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 0U, 1U),        /*!< select CMP1 output as TIMER7 CI0 */
    TIMER0_CI0_INPUT_TIMER0_CH0         = TIMER_REGIDX_BIT(TIMERCISEL0, 16U, 0U),       /*!< select TIMER0 CH0 as TIMER0 CI0 */
    TIMER0_CI0_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL0, 16U, 1U),       /*!< select CMP0 output as TIMER0 CI0 */
    TIMER2_CI0_INPUT_TIMER2_CH0         = TIMER_REGIDX_BIT(TIMERCISEL1, 0U, 0U),        /*!< select TIMER2 CH0 as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL1, 0U, 1U),        /*!< select CMP0 as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL1, 0U, 2U),        /*!< select CMP1 as TIMER2 CI0 */
    TIMER2_CI0_INPUT_CMP0_OR_CMP1_OUT   = TIMER_REGIDX_BIT(TIMERCISEL1, 0U, 3U),        /*!< select CMP0 or CMP1 as TIMER2 CI0 */
    TIMER1_CI3_INPUT_TIMER1_CH3         = TIMER_REGIDX_BIT(TIMERCISEL1, 28U, 0U),       /*!< select TIMER1 CH3 as TIMER1 CI3 */
    TIMER1_CI3_INPUT_CMP0_OUT           = TIMER_REGIDX_BIT(TIMERCISEL1, 28U, 1U),       /*!< select CMP0 output as TIMER1 CI3 */
    TIMER1_CI3_INPUT_CMP1_OUT           = TIMER_REGIDX_BIT(TIMERCISEL1, 28U, 2U),       /*!< select CMP1 output as TIMER1 CI3 */
    TIMER1_CI3_INPUT_CMP0_OR_CMP1_OUT   = TIMER_REGIDX_BIT(TIMERCISEL1, 28U, 3U),       /*!< select CMP0 or CMP1 output as TIMER1 CI3 */
    TIMER22_CI3_INPUT_TIMER22_CH3       = TIMER_REGIDX_BIT(TIMERCISEL3, 28U, 0U),       /*!< select TIMER22 CH3 as TIMER22 CI3 */
    TIMER22_CI3_INPUT_CMP0_OUT          = TIMER_REGIDX_BIT(TIMERCISEL3, 28U, 1U),       /*!< select CMP0 output as TIMER22 CI3 */
    TIMER22_CI3_INPUT_CMP1_OUT          = TIMER_REGIDX_BIT(TIMERCISEL3, 28U, 2U),       /*!< select CMP1 output as TIMER22 CI3 */
    TIMER22_CI3_INPUT_CMP0_OR_CMP1_OUT  = TIMER_REGIDX_BIT(TIMERCISEL3, 28U, 3U),       /*!< select CMP0 or CMP1 output as TIMER22 CI3 */
    TIMER31_CI0_INPUT_TIMER31_CH0       = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 0U),        /*!< select TIMER31 CH0 as TIMER31 CI0 */
    TIMER31_CI0_INPUT_CMP0_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 1U),        /*!< select CMP0 output as TIMER31 CI0 */
    TIMER31_CI0_INPUT_CMP1_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 2U),        /*!< select CMP1 output as TIMER31 CI0 */
    TIMER31_CI0_INPUT_CMP0_OR_CMP1_OUT  = TIMER_REGIDX_BIT(TIMERCISEL4, 0U, 3U),        /*!< select CMP0 or CMP1 output as TIMER31 CI0 */
    TIMER30_CI0_INPUT_TIMER30_CH0       = TIMER_REGIDX_BIT(TIMERCISEL4, 16U, 0U),       /*!< select TIMER30 CH0 as TIMER30 CI0 */
    TIMER30_CI0_INPUT_CMP0_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 16U, 1U),       /*!< select CMP0 output as TIMER30 CI0 */
    TIMER30_CI0_INPUT_CMP1_OUT          = TIMER_REGIDX_BIT(TIMERCISEL4, 16U, 2U),       /*!< select CMP1 output as TIMER30 CI0 */
    TIMER30_CI0_INPUT_CMP0_OR_CMP1_OUT  = TIMER_REGIDX_BIT(TIMERCISEL4, 16U, 3U),       /*!< select CMP0 or CMP1 output as TIMER30 CI0 */
    TIMER14_CI0_INPUT_TIMER14_CH0       = TIMER_REGIDX_BIT(TIMERCISEL5, 0U, 0U),        /*!< select TIMER14 CH0 as TIMER14 CI0 */
    TIMER14_CI0_INPUT_TIMER1_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 0U, 1U),        /*!< select TIMER1 CH0 as TIMER14 CI0 */
    TIMER14_CI0_INPUT_TIMER2_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 0U, 2U),        /*!< select TIMER2 CH0 as TIMER14 CI0 */
    TIMER14_CI0_INPUT_TIMER3_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 0U, 3U),        /*!< select TIMER3 CH0 as TIMER14 CI0 */
    TIMER14_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL5, 0U, 4U),        /*!< select LXTAL as TIMER14 CI0 */
    TIMER14_CI0_INPUT_LPIRC4M           = TIMER_REGIDX_BIT(TIMERCISEL5, 0U, 5U),        /*!< select LPIRC4M as TIMER14 CI0 */
    TIMER14_CI0_INPUT_CKOUT1            = TIMER_REGIDX_BIT(TIMERCISEL5, 0U, 6U),        /*!< select CKOUT1 as TIMER14 CI0 */
    TIMER14_CI1_INPUT_TIMER14_CH1       = TIMER_REGIDX_BIT(TIMERCISEL5, 4U, 0U),        /*!< select TIMER14 CH1 as TIMER14 CI1 */
    TIMER14_CI1_INPUT_TIMER1_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 4U, 1U),        /*!< select TIMER1 CH1 as TIMER14 CI1 */
    TIMER14_CI1_INPUT_TIMER2_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 4U, 2U),        /*!< select TIMER2 CH1 as TIMER14 CI1 */
    TIMER14_CI1_INPUT_TIMER3_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 4U, 3U),        /*!< select TIMER3 CH1 as TIMER14 CI1 */
    TIMER40_CI0_INPUT_TIMER40_CH0       = TIMER_REGIDX_BIT(TIMERCISEL5, 8U, 0U),        /*!< select TIMER40 CH0 as TIMER40 CI0 */
    TIMER40_CI0_INPUT_TIMER2_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 8U, 1U),        /*!< select TIMER2 CH0 as TIMER40 CI0 */
    TIMER40_CI0_INPUT_TIMER3_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 8U, 2U),        /*!< select TIMER3 CH0 as TIMER40 CI0 */
    TIMER40_CI0_INPUT_TIMER4_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 8U, 3U),        /*!< select TIMER4 CH0 as TIMER40 CI0 */
    TIMER40_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL5, 8U, 4U),        /*!< select LXTAL as TIMER40 CI0 */
    TIMER40_CI0_INPUT_LPIRC4M           = TIMER_REGIDX_BIT(TIMERCISEL5, 8U, 5U),        /*!< select LPIRC4M as TIMER40 CI0 */
    TIMER40_CI0_INPUT_CKOUT1            = TIMER_REGIDX_BIT(TIMERCISEL5, 8U, 6U),        /*!< select CKOUT1 as TIMER40 CI0 */
    TIMER40_CI1_INPUT_TIMER40_CH1       = TIMER_REGIDX_BIT(TIMERCISEL5, 12U, 0U),       /*!< select TIMER40 CH1 as TIMER40 CI1 */
    TIMER40_CI1_INPUT_TIMER2_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 12U, 1U),       /*!< select TIMER2 CH1 as TIMER40 CI1 */
    TIMER40_CI1_INPUT_TIMER3_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 12U, 2U),       /*!< select TIMER3 CH1 as TIMER40 CI1 */
    TIMER40_CI1_INPUT_TIMER4_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 12U, 3U),       /*!< select TIMER4 CH1 as TIMER40 CI1 */
    TIMER41_CI0_INPUT_TIMER41_CH0       = TIMER_REGIDX_BIT(TIMERCISEL5, 16U, 0U),       /*!< select TIMER41 CH0 as TIMER41 CI0 */
    TIMER41_CI0_INPUT_TIMER3_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 16U, 1U),       /*!< select TIMER3 CH0 as TIMER41 CI0 */
    TIMER41_CI0_INPUT_TIMER4_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 16U, 2U),       /*!< select TIMER4 CH0 as TIMER41 CI0 */
    TIMER41_CI0_INPUT_TIMER22_CH0       = TIMER_REGIDX_BIT(TIMERCISEL5, 16U, 3U),       /*!< select TIMER22 CH0 as TIMER41 CI0 */
    TIMER41_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL5, 16U, 4U),       /*!< select LXTAL as TIMER41 CI0 */
    TIMER41_CI0_INPUT_LPIRC4M           = TIMER_REGIDX_BIT(TIMERCISEL5, 16U, 5U),       /*!< select LPIRC4M as TIMER41 CI0 */
    TIMER41_CI0_INPUT_CKOUT1            = TIMER_REGIDX_BIT(TIMERCISEL5, 16U, 6U),       /*!< select CKOUT1 as TIMER41 CI0 */
    TIMER41_CI1_INPUT_TIMER41_CH1       = TIMER_REGIDX_BIT(TIMERCISEL5, 20U, 0U),       /*!< select TIMER41 CH1 as TIMER41 CI1 */
    TIMER41_CI1_INPUT_TIMER3_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 20U, 1U),       /*!< select TIMER3 CH1 as TIMER41 CI1 */
    TIMER41_CI1_INPUT_TIMER4_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 20U, 2U),       /*!< select TIMER4 CH1 as TIMER41 CI1 */
    TIMER41_CI1_INPUT_TIMER22_CH1       = TIMER_REGIDX_BIT(TIMERCISEL5, 20U, 3U),       /*!< select TIMER22 CH1 as TIMER41 CI1 */
    TIMER42_CI0_INPUT_TIMER42_CH0       = TIMER_REGIDX_BIT(TIMERCISEL5, 24U, 0U),       /*!< select TIMER42 CH0 as TIMER42 CI0 */
    TIMER42_CI0_INPUT_TIMER4_CH0        = TIMER_REGIDX_BIT(TIMERCISEL5, 24U, 1U),       /*!< select TIMER4 CH0 as TIMER42 CI0 */
    TIMER42_CI0_INPUT_TIMER22_CH0       = TIMER_REGIDX_BIT(TIMERCISEL5, 24U, 2U),       /*!< select TIMER22 CH0 as TIMER42 CI0 */
    TIMER42_CI0_INPUT_TIMER23_CH0       = TIMER_REGIDX_BIT(TIMERCISEL5, 24U, 3U),       /*!< select TIMER23 CH0 as TIMER42 CI0 */
    TIMER42_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL5, 24U, 4U),       /*!< select LXTAL as TIMER42 CI0 */
    TIMER42_CI0_INPUT_LPIRC4M           = TIMER_REGIDX_BIT(TIMERCISEL5, 24U, 5U),       /*!< select LPIRC4M as TIMER42 CI0 */
    TIMER42_CI0_INPUT_CKOUT1            = TIMER_REGIDX_BIT(TIMERCISEL5, 24U, 6U),       /*!< select CKOUT1 as TIMER42 CI0 */
    TIMER42_CI1_INPUT_TIMER42_CH1       = TIMER_REGIDX_BIT(TIMERCISEL5, 28U, 0U),       /*!< select TIMER42 CH1 as TIMER42 CI1 */
    TIMER42_CI1_INPUT_TIMER4_CH1        = TIMER_REGIDX_BIT(TIMERCISEL5, 28U, 1U),       /*!< select TIMER4 CH1 as TIMER42 CI1 */
    TIMER42_CI1_INPUT_TIMER22_CH1       = TIMER_REGIDX_BIT(TIMERCISEL5, 28U, 2U),       /*!< select TIMER22 CH1 as TIMER42 CI1 */
    TIMER42_CI1_INPUT_TIMER23_CH1       = TIMER_REGIDX_BIT(TIMERCISEL5, 28U, 3U),       /*!< select TIMER23 CH1 as TIMER42 CI1 */
    TIMER15_CI0_INPUT_TIMER15_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 0U, 0U),        /*!< select TIMER15 CH0 as TIMER15 CI0 */
    TIMER15_CI0_INPUT_IRC32K            = TIMER_REGIDX_BIT(TIMERCISEL6, 0U, 1U),        /*!< select IRC32K as TIMER15 CI0 */
    TIMER15_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL6, 0U, 2U),        /*!< select LXTAL as TIMER15 CI0 */
    TIMER15_CI0_INPUT_WKUP_IT           = TIMER_REGIDX_BIT(TIMERCISEL6, 0U, 3U),        /*!< select WKUP IT as TIMER15 CI0 */
    TIMER16_CI0_INPUT_TIMER16_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 4U, 0U),        /*!< select TIMER16 CH0 as TIMER16 CI0 */
    TIMER16_CI0_INPUT_RSPDIF            = TIMER_REGIDX_BIT(TIMERCISEL6, 4U, 1U),        /*!< select RSPDIF FS as TIMER16 CI0 */
    TIMER16_CI0_INPUT_HXTAL_RTCDIV      = TIMER_REGIDX_BIT(TIMERCISEL6, 4U, 2U),        /*!< select HXTAL/RTCDIV 1M as TIMER16 CI0 */
    TIMER16_CI0_INPUT_CKOUT0            = TIMER_REGIDX_BIT(TIMERCISEL6, 4U, 3U),        /*!< select CKOUT0 as TIMER16 CI0 */
    TIMER43_CI0_INPUT_TIMER43_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 8U, 0U),        /*!< select TIMER43 CH0 as TIMER43 CI0 */
    TIMER43_CI0_INPUT_TIMER22_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 8U, 1U),        /*!< select TIMER22 CH0 as TIMER43 CI0 */
    TIMER43_CI0_INPUT_TIMER23_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 8U, 2U),        /*!< select TIMER23 CH0 as TIMER43 CI0 */
    TIMER43_CI0_INPUT_TIMER30_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 8U, 3U),        /*!< select TIMER30 CH0 as TIMER43 CI0 */
    TIMER43_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL6, 8U, 4U),        /*!< select LXTAL as TIMER43 CI0 */
    TIMER43_CI0_INPUT_LPIRC4M           = TIMER_REGIDX_BIT(TIMERCISEL6, 8U, 5U),        /*!< select LPIRC4M as TIMER43 CI0 */
    TIMER43_CI0_INPUT_CKOUT1            = TIMER_REGIDX_BIT(TIMERCISEL6, 8U, 6U),        /*!< select CKOUT1 as TIMER43 CI0 */
    TIMER43_CI1_INPUT_TIMER43_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 12U, 0U),       /*!< select TIMER43 CH1 as TIMER43 CI1 */
    TIMER43_CI1_INPUT_TIMER22_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 12U, 1U),       /*!< select TIMER22 CH1 as TIMER43 CI1 */
    TIMER43_CI1_INPUT_TIMER23_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 12U, 2U),       /*!< select TIMER23 CH1 as TIMER43 CI1 */
    TIMER43_CI1_INPUT_TIMER30_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 12U, 3U),       /*!< select TIMER30 CH1 as TIMER43 CI1 */
    TIMER44_CI0_INPUT_TIMER44_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 16U, 0U),       /*!< select TIMER44 CH0 as TIMER44 CI0 */
    TIMER44_CI0_INPUT_TIMER23_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 16U, 1U),       /*!< select TIMER23 CH0 as TIMER44 CI0 */
    TIMER44_CI0_INPUT_TIMER30_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 16U, 2U),       /*!< select TIMER30 CH0 as TIMER44 CI0 */
    TIMER44_CI0_INPUT_TIMER31_CH0       = TIMER_REGIDX_BIT(TIMERCISEL6, 16U, 3U),       /*!< select TIMER31 CH0 as TIMER44 CI0 */
    TIMER44_CI0_INPUT_LXTAL             = TIMER_REGIDX_BIT(TIMERCISEL6, 16U, 4U),       /*!< select LXTAL as TIMER44 CI0 */
    TIMER44_CI0_INPUT_LPIRC4M           = TIMER_REGIDX_BIT(TIMERCISEL6, 16U, 5U),       /*!< select LPIRC4M as TIMER44 CI0 */
    TIMER44_CI0_INPUT_CKOUT1            = TIMER_REGIDX_BIT(TIMERCISEL6, 16U, 6U),       /*!< select CKOUT1 as TIMER44 CI0 */
    TIMER44_CI1_INPUT_TIMER44_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 20U, 0U),       /*!< select TIMER44 CH1 as TIMER44 CI1 */
    TIMER44_CI1_INPUT_TIMER23_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 20U, 1U),       /*!< select TIMER23 CH1 as TIMER44 CI1 */
    TIMER44_CI1_INPUT_TIMER30_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 20U, 2U),       /*!< select TIMER30 CH1 as TIMER44 CI1 */
    TIMER44_CI1_INPUT_TIMER31_CH1       = TIMER_REGIDX_BIT(TIMERCISEL6, 20U, 3U),       /*!< select TIMER31 CH1 as TIMER44 CI1 */
} timer_channel_input_enum;

/* timer tigger source select definition */
#define TIMER_SMCFG_TRGSEL_NONE             ((uint8_t)0x00U)                            /*!< trigger input is none */
#define TIMER_SMCFG_TRGSEL_ITI0             ((uint8_t)0x01U)                            /*!< internal trigger 0 */
#define TIMER_SMCFG_TRGSEL_ITI1             ((uint8_t)0x02U)                            /*!< internal trigger 1 */
#define TIMER_SMCFG_TRGSEL_ITI2             ((uint8_t)0x03U)                            /*!< internal trigger 2 */
#define TIMER_SMCFG_TRGSEL_ITI3             ((uint8_t)0x04U)                            /*!< internal trigger 3 */
#define TIMER_SMCFG_TRGSEL_CI0F_ED          ((uint8_t)0x05U)                            /*!< TI0 edge detector */
#define TIMER_SMCFG_TRGSEL_CI0FE0           ((uint8_t)0x06U)                            /*!< filtered TIMER input 0 */
#define TIMER_SMCFG_TRGSEL_CI1FE1           ((uint8_t)0x07U)                            /*!< filtered TIMER input 1 */
#define TIMER_SMCFG_TRGSEL_ETIFP            ((uint8_t)0x08U)                            /*!< external trigger */
#define TIMER_SMCFG_TRGSEL_CI2FE2           ((uint8_t)0x09U)                            /*!< filtered TIMER input 2 */
#define TIMER_SMCFG_TRGSEL_CI3FE3           ((uint8_t)0x0AU)                            /*!< filtered TIMER input 3 */
#define TIMER_SMCFG_TRGSEL_MCI0FEM0         ((uint8_t)0x0BU)                            /*!< filtered output of multi mode channel 0 */
#define TIMER_SMCFG_TRGSEL_MCI1FEM1         ((uint8_t)0x0CU)                            /*!< filtered output of multi mode channel 1 */
#define TIMER_SMCFG_TRGSEL_MCI2FEM2         ((uint8_t)0x0DU)                            /*!< filtered output of multi mode channel 2 */
#define TIMER_SMCFG_TRGSEL_MCI3FEM3         ((uint8_t)0x0EU)                            /*!< filtered output of multi mode channel 3 */
#define TIMER_SMCFG_TRGSEL_ITI12            ((uint8_t)0x11U)                            /*!< internal trigger input 12 */
#define TIMER_SMCFG_TRGSEL_ITI13            ((uint8_t)0x12U)                            /*!< internal trigger input 13 */
#define TIMER_SMCFG_TRGSEL_ITI14            ((uint8_t)0x13U)                            /*!< internal trigger input 14 */
#define TIMER_L0_SMCFG_TRGSEL_ITI4          ((uint8_t)0x09U)                            /*!< internal trigger 4 for General-L0 timer */
#define TIMER_L0_SMCFG_TRGSEL_ITI5          ((uint8_t)0x0AU)                            /*!< internal trigger 5 for General-L0 timer */
#define TIMER_L0_SMCFG_TRGSEL_ITI7          ((uint8_t)0x0CU)                            /*!< internal trigger 7 for General-L0 timer */
#define TIMER_L0_SMCFG_TRGSEL_ITI9          ((uint8_t)0x0EU)                            /*!< internal trigger 9 for General-L0 timer */
#define TIMER_L0_SMCFG_TRGSEL_ITI10         ((uint8_t)0x0FU)                            /*!< internal trigger 10 for General-L0 timer */
#define TIMER_L0_SMCFG_TRGSEL_ITI11         ((uint8_t)0x10U)                            /*!< internal trigger 11 for General-L0 timer */

/* timer tigger mode select definition */
#define TIMER_QUAD_DECODER_MODE0            ((uint8_t)0x00U)                            /*!< quadrature decoder mode 0 */
#define TIMER_QUAD_DECODER_MODE1            ((uint8_t)0x01U)                            /*!< quadrature decoder mode 1 */
#define TIMER_QUAD_DECODER_MODE2            ((uint8_t)0x02U)                            /*!< quadrature decoder mode 2 */
#define TIMER_SLAVE_MODE_RESTART            ((uint8_t)0x03U)                            /*!< restart mode */
#define TIMER_SLAVE_MODE_PAUSE              ((uint8_t)0x04U)                            /*!< pause mode */
#define TIMER_SLAVE_MODE_EVENT              ((uint8_t)0x05U)                            /*!< event mode */
#define TIMER_SLAVE_MODE_EXTERNAL0          ((uint8_t)0x06U)                            /*!< external clock mode 0 */
#define TIMER_SLAVE_MODE_RESTART_EVENT      ((uint8_t)0x07U)                            /*!< restart + event mode */
#define TIMER_NONQUAD_DECODER_MODE0         ((uint8_t)0x09U)                            /*!< non-quadrature decoder mode 0 */
#define TIMER_NONQUAD_DECODER_MODE1         ((uint8_t)0x0AU)                            /*!< non-quadrature decoder mode 1 */
#define TIMER_NONQUAD_DECODER_MODE2         ((uint8_t)0x0BU)                            /*!< non-quadrature decoder mode 2 */
#define TIMER_NONQUAD_DECODER_MODE3         ((uint8_t)0x0CU)                            /*!< non-quadrature decoder mode 3 */
#define TIMER_QUAD_DECODER_MODE3            ((uint8_t)0x0DU)                            /*!< quadrature decoder mode 3 */
#define TIMER_QUAD_DECODER_MODE4            ((uint8_t)0x0EU)                            /*!< quadrature decoder mode 4 */
#define TIMER_SLAVE_MODE_DISABLE            ((uint8_t)0x0FU)                            /*!< slave mode disable */

#define SYSCFG_TIMERCFG0(syscfg_timerx)     REG32(SYSCFG + 0x100U + (syscfg_timerx) * 0x0CU)/*!< TIMERx configuration register */
#define SYSCFG_TIMERCFG1(syscfg_timerx)     REG32(SYSCFG + 0x104U + (syscfg_timerx) * 0x0CU)/*!< TIMERx configuration register */
#define SYSCFG_TIMERCFG2(syscfg_timerx)     REG32(SYSCFG + 0x108U + (syscfg_timerx) * 0x0CU)/*!< TIMERx configuration register */

#define SYSCFG_TIMER0                       ((uint8_t)0x00U)                            /*!< SYSCFG TIMER0 */
#define SYSCFG_TIMER1                       ((uint8_t)0x01U)                            /*!< SYSCFG TIMER1 */
#define SYSCFG_TIMER2                       ((uint8_t)0x02U)                            /*!< SYSCFG TIMER2 */
#define SYSCFG_TIMER3                       ((uint8_t)0x03U)                            /*!< SYSCFG TIMER3 */
#define SYSCFG_TIMER4                       ((uint8_t)0x04U)                            /*!< SYSCFG TIMER4 */
#define SYSCFG_TIMER7                       ((uint8_t)0x05U)                            /*!< SYSCFG TIMER7 */
#define SYSCFG_TIMER14                      ((uint8_t)0x06U)                            /*!< SYSCFG TIMER14 */
#define SYSCFG_TIMER22                      ((uint8_t)0x07U)                            /*!< SYSCFG TIMER22 */
#define SYSCFG_TIMER23                      ((uint8_t)0x08U)                            /*!< SYSCFG TIMER23 */
#define SYSCFG_TIMER30                      ((uint8_t)0x09U)                            /*!< SYSCFG TIMER30 */
#define SYSCFG_TIMER31                      ((uint8_t)0x0AU)                            /*!< SYSCFG TIMER31 */
#define SYSCFG_TIMER40                      ((uint8_t)0x0BU)                            /*!< SYSCFG TIMER40 */
#define SYSCFG_TIMER41                      ((uint8_t)0x0CU)                            /*!< SYSCFG TIMER41 */
#define SYSCFG_TIMER42                      ((uint8_t)0x0DU)                            /*!< SYSCFG TIMER42 */
#define SYSCFG_TIMER43                      ((uint8_t)0x0EU)                            /*!< SYSCFG TIMER43 */
#define SYSCFG_TIMER44                      ((uint8_t)0x0FU)                            /*!< SYSCFG TIMER44 */

/* TIMER input select mask bits definition */
#define TIMER_IS_MASK                       BITS(0,3)                                   /*!< TIMER source select mask */

/* CACHE mode definitions */
#define ICACHE_STATUS                       ((uint32_t)0x00000000U)                     /*!< select ICACHE */
#define DCACHE_STATUS                       ((uint32_t)0x00000001U)                     /*!< select DCACHE */

/* CACHE status definitions */
#define CPU_CACHE_ERROR_DETECTION           ((uint32_t)0x00000000U)                     /*!< select detection information */
#define CPU_CACHE_ERROR_BANK                ((uint32_t)0x00000001U)                     /*!< select error information */

/* Secure SRAM size definition */
#define SECURE_SRAM_SIZE_0KB                ((uint32_t)0x00000000U)                     /*!< secure SRAM size is 0KB */
#define SECURE_SRAM_SIZE_32KB               ((uint32_t)0x00000001U)                     /*!< secure SRAM size is 32KB */
#define SECURE_SRAM_SIZE_64KB               ((uint32_t)0x00000002U)                     /*!< secure SRAM size is 64KB */
#define SECURE_SRAM_SIZE_128KB              ((uint32_t)0x00000003U)                     /*!< secure SRAM size is 128KB */

/* I/O compensation cell enable/disable */
#define SYSCFG_IO_COMPENSATION_ENABLE       ((uint32_t)0x00000001U)                     /*!< I/O compensation cell enable */
#define SYSCFG_IO_COMPENSATION_DISABLE      ((uint32_t)0x00000000U)                     /*!< I/O compensation cell disable */

/* module lockup */
#define SYSCFG_LVD_LOCKUP                   SYSCFG_LKCTL_LVD_LOCK                       /*!< LVD signal connected */
#define SYSCFG_CPU_LOCKUP                   SYSCFG_LKCTL_CPU_LOCK                       /*!< CPU lockup signal connected */
#define SYSCFG_BKPRAM_LOCKUP                SYSCFG_LKCTL_BKPRAM_LOCK                    /*!< Region 2 backup SRAM ECC double error signal connected */
#define SYSCFG_SRAM1_LOCKUP                 SYSCFG_LKCTL_SRAM1_LOCK                     /*!< Region 1 SRAM1 ECC double error signal connected */
#define SYSCFG_SRAM0_LOCKUP                 SYSCFG_LKCTL_SRAM0_LOCK                     /*!< Region 1 SRAM0 ECC double error signal connected */
#define SYSCFG_DTCM_LOCKUP                  SYSCFG_LKCTL_DTCM_LOCK                      /*!< Region 0 DTCM ECC double error signal connected */
#define SYSCFG_ITCM_LOCKUP                  SYSCFG_LKCTL_ITCM_LOCK                      /*!< Region 0 ITCM-RAM ECC double error signal connected */
#define SYSCFG_AXIRAM_LOCKUP                SYSCFG_LKCTL_AXIRAM_LOCK                    /*!< Region 0 AXI-SRAM ECC double error signal connected */

/* SYSCFG compensation flag definitions */
#define SYSCFG_FLAG_IO_LOW_VOLTAGE          SYSCFG_CPSCTL_IOLV                          /*!< I/O in low voltage state flag, product supply voltage is working below 2.5V */
#define SYSCFG_FLAG_COMPENSATION_READY      SYSCFG_CPSCTL_CPS_RDY                       /*!< I/O compensation cell ready flag */

/* SYSCFG interrupt definitions */
#define SYSCFG_INT_INEXACT                  SYSCFG_CFPUINTEN_IXIE                       /*!< inexact interrupt */
#define SYSCFG_INT_INPUT_ABNORMAL           SYSCFG_CFPUINTEN_IDIE                       /*!< input abnormal interrupt */
#define SYSCFG_INT_OVERFLOW                 SYSCFG_CFPUINTEN_OVFIE                      /*!< overflow interrupt */
#define SYSCFG_INT_UNDERFLOW                SYSCFG_CFPUINTEN_UFIE                       /*!< underflow interrupt */
#define SYSCFG_INT_DIV0                     SYSCFG_CFPUINTEN_DZIE                       /*!< divide-by-zero interrupt */
#define SYSCFG_INT_INVALID_OPERATION        SYSCFG_CFPUINTEN_IOPIE                      /*!< invalid operation interrupt */
#define SYSCFG_INT_CPU_DCDET                SYSCFG_CFPUINTEN_CPU_DCDETIE                /*!< CPU DCACHE error bank information interrupt */
#define SYSCFG_INT_CPU_ICDET                SYSCFG_CFPUINTEN_CPU_ICDETIE                /*!< CPU ICACHE error detection information interrupt */

/* BOOT modes definitions */
#define BOOT_SRAM                           ((uint32_t)0x00000000U)                     /*!< BOOT from SRAM (ITCM/DTCM/RAM shared/AXI SRAM) */
#define BOOT_SECURITY                       ((uint32_t)0x00000001U)                     /*!< BOOT from Security */
#define BOOT_SYSTEM                         ((uint32_t)0x00000002U)                     /*!< BOOT_SYS (BootLoader) */
#define BOOT_USER                           ((uint32_t)0x00000003U)                     /*!< BOOT_USER (NVMC / OSPI0/1) */

/* BOR threshold level definitions */
#define BOR_OFF                             ((uint32_t)0x00000000U)                     /*!< no BOR function */
#define BOR_THRESHOLD_VAL1                  ((uint32_t)0x00000001U)                     /*!< BOR threshold value 1 */
#define BOR_THRESHOLD_VAL2                  ((uint32_t)0x00000002U)                     /*!< BOR threshold value 2 */
#define BOR_THRESHOLD_VAL3                  ((uint32_t)0x00000003U)                     /*!< BOR threshold value 3 */

/* EtherCat internal eeprom size polarity select definition */
#define ESC_INTERNAL_EEPROM_SIZE1           ((uint32_t)0x00000000U)                     /*!< Select internal EEPROM size is 1k~15k bit */
#define ESC_INTERNAL_EEPROM_SIZE2           SYSCFG_ESCCFG0_EEPROMSZ                     /*!< Select internal EEPROM size is 16k~4M bit */

/* EtherCat linkactled0 polarity select definition */
#define ESC_LINKACTLED0_POL_LOW             ((uint32_t)0x00000000U)                     /*!< EtherCat linkactled0 output 0 */
#define ESC_LINKACTLED0_POL_HIGH            SYSCFG_ESCCFG0_LINKACTLED0_POLSEL           /*!< EtherCat linkactled0 output 1 */

/* EtherCat linkactled1 polarity select definition */
#define ESC_LINKACTLED1_POL_LOW             ((uint32_t)0x00000000U)                     /*!< EtherCat linkactled1 output 0 */
#define ESC_LINKACTLED1_POL_HIGH            SYSCFG_ESCCFG0_LINKACTLED1_POLSEL           /*!< EtherCat linkactled1 output 1 */

/* EtherCat linkactled2 polarity select definition */
#define ESC_LINKACTLED2_POL_LOW             ((uint32_t)0x00000000U)                     /*!< EtherCat linkactled2 output 0 */
#define ESC_LINKACTLED2_POL_HIGH            SYSCFG_ESCCFG0_LINKACTLED2_POLSEL           /*!< EtherCat linkactled2 output 1 */

/* EtherCat led_err polarity select definition */
#define ESC_LEDERR_POL_LOW                  ((uint32_t)0x00000000U)                     /*!< EtherCat lederr output 0 */
#define ESC_LEDERR_POL_HIGH                 SYSCFG_ESCCFG0_LEDERR_POLSEL                /*!< EtherCat lederr output 1 */

/* EtherCat led_run polarity select definition */
#define ESC_LEDRUN_POL_LOW                  ((uint32_t)0x00000000U)                     /*!< EtherCat ledrun output 0 */
#define ESC_LEDRUN_POL_HIGH                 SYSCFG_ESCCFG0_LEDRUN_POLSEL                /*!< EtherCat ledrun output 1 */

/* EtherCat reset_out polarity select definition */
#define ESC_RSTOUT_POL_HIGH                 ((uint32_t)0x00000000U)                     /*!< EtherCat reset_out output 1 */
#define ESC_RSTOUT_POL_LOW                  SYSCFG_ESCCFG0_RSTOUT_POLSEL                /*!< EtherCat reset_out output 0 */

/* EtherCat LINK0 polarity select definition */
#define ESC_LINK0_POL_HIGH                  ((uint32_t)0x00000000U)                     /*!< EtherCat LINK0 output 1 */
#define ESC_LINK0_POL_LOW                   SYSCFG_ESCCFG0_NLINK0_POLSEL                /*!< EtherCat LINK0 output 0 */

/* EtherCat LINK1 polarity select definition */
#define ESC_LINK1_POL_HIGH                  ((uint32_t)0x00000000U)                     /*!< EtherCat LINK1 output 1 */
#define ESC_LINK1_POL_LOW                   SYSCFG_ESCCFG0_NLINK1_POLSEL                /*!< EtherCat LINK1 output 0 */

/* EtherCat LINK2 polarity select definition */
#define ESC_LINK2_POL_HIGH                  ((uint32_t)0x00000000U)                     /*!< EtherCat LINK2 output 1 */
#define ESC_LINK2_POL_LOW                   SYSCFG_ESCCFG0_NLINK2_POLSEL                /*!< EtherCat LINK2 output 0 */

/* EtherCat port0 phy address select definition */
#define ESC_PHY_ADDRESS_OFFSET_0            ((uint32_t)0x00000000U)                     /*!< port0 phy address offset is 0 */
#define ESC_PHY_ADDRESS_OFFSET_16           SYSCFG_ESCCFG0_PHY_OFFSETSEL                /*!< port0 phy address offset is 16 */

/* EtherCat mii or rmii select definition */
#define ESC_MII                             ((uint32_t)0x00000000U)                     /*!< esc mii */
#define ESC_RMII                            SYSCFG_ESCCFG0_RMIIEN                       /*!< esc rmii */

/* EtherCat SMPS_DRIVE's drive capability definition */
#define ESC_SMPS_DRIVE_CAP_NORMAL           ((uint32_t)0x00000000U)                     /*!< Drive capability is normal */
#define ESC_SMPS_DRIVE_CAP_REDUCED          SYSCFG_ESCCFG0_SMPS_DRIVE                   /*!< Drive capability is reduced */

/* rmii0 txshift0 selection */
#define RMII0_TXSHIFT0(regval)              (BITS(1,2)&((uint32_t)(regval)<<1))
#define ESC_RMII0_TXSHIFT0_0NS              RMII0_TXSHIFT0(0)                           /*!< rmii0 txshift value is 0ns */
#define ESC_RMII0_TXSHIFT0_10NS             RMII0_TXSHIFT0(1)                           /*!< rmii0 txshift value is 10ns */
#define ESC_RMII0_TXSHIFT0_20NS             RMII0_TXSHIFT0(2)                           /*!< rmii0 txshift value is 20ns */
#define ESC_RMII0_TXSHIFT0_30NS             RMII0_TXSHIFT0(3)                           /*!< rmii0 txshift value is 30ns */

/* rmii1 txshift1 selection */
#define RMII1_TXSHIFT1(regval)              (BITS(3,4)&((uint32_t)(regval)<<3))
#define ESC_RMII1_TXSHIFT1_0NS              RMII1_TXSHIFT1(0)                           /*!< rmii1 txshift value is 0ns */
#define ESC_RMII1_TXSHIFT1_10NS             RMII1_TXSHIFT1(1)                           /*!< rmii1 txshift value is 10ns */
#define ESC_RMII1_TXSHIFT1_20NS             RMII1_TXSHIFT1(2)                           /*!< rmii1 txshift value is 20ns */
#define ESC_RMII1_TXSHIFT1_30NS             RMII1_TXSHIFT1(3)                           /*!< rmii1 txshift value is 30ns */

/* rmii0 shift0 selection */
#define RMII0_SHIFT0(regval)                (BITS(27,29)&((uint32_t)(regval)<<27))
#define ESC_RMII0_SHIFT0_0                  RMII0_SHIFT0(0)                             /*!< rmii0 phase compensation value is 0ns */
#define ESC_RMII0_SHIFT0_1                  RMII0_SHIFT0(1)                             /*!< rmii0 phase compensation value is 2.5ns */
#define ESC_RMII0_SHIFT0_2                  RMII0_SHIFT0(2)                             /*!< rmii0 phase compensation value is 5ns */
#define ESC_RMII0_SHIFT0_3                  RMII0_SHIFT0(3)                             /*!< rmii0 phase compensation value is 7.5ns */
#define ESC_RMII0_SHIFT0_4                  RMII0_SHIFT0(4)                             /*!< rmii0 phase compensation value is 10ns */
#define ESC_RMII0_SHIFT0_5                  RMII0_SHIFT0(5)                             /*!< rmii0 phase compensation value is 12.5ns */
#define ESC_RMII0_SHIFT0_6                  RMII0_SHIFT0(6)                             /*!< rmii0 phase compensation value is 15ns */
#define ESC_RMII0_SHIFT0_7                  RMII0_SHIFT0(7)                             /*!< rmii0 phase compensation value is 17.5ns */

/* rmii1 shift1 selection */
#define RMII1_SHIFT1(regval)                (BITS(12,14)&((uint32_t)(regval)<<12))
#define ESC_RMII1_SHIFT1_0                  RMII1_SHIFT1(0)                             /*!< rmii1 phase compensation value is 0ns */
#define ESC_RMII1_SHIFT1_1                  RMII1_SHIFT1(1)                             /*!< rmii1 phase compensation value is 2.5ns */
#define ESC_RMII1_SHIFT1_2                  RMII1_SHIFT1(2)                             /*!< rmii1 phase compensation value is 5ns */
#define ESC_RMII1_SHIFT1_3                  RMII1_SHIFT1(3)                             /*!< rmii1 phase compensation value is 7.5ns */
#define ESC_RMII1_SHIFT1_4                  RMII1_SHIFT1(4)                             /*!< rmii1 phase compensation value is 10ns */
#define ESC_RMII1_SHIFT1_5                  RMII1_SHIFT1(5)                             /*!< rmii1 phase compensation value is 12.5ns */
#define ESC_RMII1_SHIFT1_6                  RMII1_SHIFT1(6)                             /*!< rmii1 phase compensation value is 15ns */
#define ESC_RMII1_SHIFT1_7                  RMII1_SHIFT1(7)                             /*!< rmii1 phase compensation value is 17.5ns */

/* port0 phy address value */
#define PHY_ADDRESS_OFFSET(regval)         (BITS(22,26)&((uint32_t)(regval)<<22))


/* function declarations */
/* initialization functions */
/* reset the SYSCFG registers */
void syscfg_deinit(void);

/* peripheral SYSCFG configuration functions */
/* enable I2Cx(x=0,1,2,3) fast mode plus or I2C fast mode plus PBx(x=6,7,8,9) */
void syscfg_i2c_fast_mode_plus_enable(uint32_t i2c_fmp);
/* disable I2Cx(x=0,1,2,3) fast mode plus or I2C fast mode plus PBx(x=6,7,8,9) */
void syscfg_i2c_fast_mode_plus_disable(uint32_t i2c_fmp);
/* open analog switch (Pxy_C and Pxy are separated pads) */
void syscfg_analog_switch_enable(uint32_t gpio_answ);
/* close analog switch (Pxy_C and Pxy are connected through the analog switch) */
void syscfg_analog_switch_disable(uint32_t gpio_answ);
/* configure the PHY interface for the Ethernet MAC */
void syscfg_enet_phy_interface_config(uint32_t ethernet, uint32_t phy_interface);
/* configure the GPIO pin as EXTI line */
void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin);
/* enable module lockup function (function can be disabled by system reset) */
void syscfg_lockup_enable(uint32_t lockup);
/* select timer channel input source */
void syscfg_timer_input_source_select(timer_channel_input_enum timer_input);

/* Coder IO configuration functions */
/* select coder IO */
void syscfg_coder_io_select(uint32_t io_group, uint32_t coder_io);

/* enable VOS configurability */
void syscfg_vos_config_enable(void);
/* disable VOS configurability */
void syscfg_vos_config_disable(void);

/* enable standby flag output from PC13 */
void syscfg_standby_flag_output_enable(void);
/* disable standby flag output from PC13 */
void syscfg_standby_flag_output_disable(void);

/* enable CK_EXMC clock */
void syscfg_ck_exmc_enable(void);
/* disable CK_EXMC clock */
void syscfg_ck_exmc_disable(void);

/* configure bus timeout */
void syscfg_bus_timeout_config(uint32_t periph, ControlStatus enable);

/* Ethercat configuration functions */
/* set Ethercat internal EEPROM address */
void syscfg_esc_internal_eeprom_set(uint32_t size, uint32_t address);
/* select EtherCat external EEPROM */
void syscfg_esc_external_eeprom_sel(void);
/* enable Ethercat mii txshift pin strap */
void syscfg_esc_mii_txshift_pin_enable(void);
/* disable Ethercat mii txshift pin strap */
void syscfg_esc_mii_txshift_pin_disable(void);
/* set Ethercat rmii1 mode tx_shift and rmii0_shift */
void syscfg_esc_rmii0_mode_shift_set(uint32_t txshift0, uint32_t rmii0_shift0);
/* set Ethercat rmii1 mode tx_shift and rmii1_shift */
void syscfg_esc_rmii1_mode_shift_set(uint32_t txshift1, uint32_t rmii1_shift1);
/* select Ethercat linkactled output polarity */
void syscfg_esc_linkactled_pol_sel(uint32_t linkactled0, uint32_t linkactled1, uint32_t linkactled2);
/*select Ethercat lederr output polarity */
void syscfg_esc_lederr_pol_sel(uint32_t lederr);
/* select Ethercat ledrun output polarity */
void syscfg_esc_ledrun_pol_sel(uint32_t ledrun);
/* set Ethercat reset_out output polarity and count of clock cycles */
void syscfg_esc_resetout_set(uint32_t rstout_pol, uint32_t rstout_cnt);
/* select Ethercat linkactled output polarity */
void syscfg_esc_link_pol_sel(uint32_t link0, uint32_t link1, uint32_t link2);
/* select Ethercat mii or rmii */
void syscfg_esc_mii_rmii_sel(uint32_t mii_rmii_sel);
/* configure Ethercat SMPS_DRIVE's drive capability */
void syscfg_esc_smps_drive_config(uint32_t drive_cap);
/* set Ethercat port0 phy address offset */
void syscfg_esc_phyaddress_offset_set(uint32_t phyadd_offset_sel, uint32_t offset_value);

/* I/O compensation cell functions */
/* configure the I/O compensation cell */
void syscfg_io_compensation_config(uint32_t syscfg_cps);
/* enable I/O speed optimization, high-speed at low-voltage */
void syscfg_io_low_voltage_speed_optimization_enable(void);
/* disable I/O speed optimization, high-speed at low-voltage */
void syscfg_io_low_voltage_speed_optimization_disable(void);
/* set P/N MOS compensation value */
void syscfg_pnmos_compensation_code_set(uint32_t mos, uint32_t code);

/* secure and boot functions */
/* set secure SRAM size */
void syscfg_secure_sram_size_set(uint32_t size);
/* get secure SRAM size */
uint32_t syscfg_secure_sram_size_get(void);
/* get BOOT mode */
uint32_t syscfg_bootmode_get(void);

/* flag and interrupt functions */
/* enable SYSCFG interrupt */
void syscfg_interrupt_enable(uint32_t interrupt);
/* disable SYSCFG interrupt */
void syscfg_interrupt_disable(uint32_t interrupt);
/* get bus timeout flag status */
FlagStatus syscfg_bus_timeout_flag_get(uint32_t flag);
/* get compensation cell flags */
FlagStatus syscfg_compensation_flag_get(uint32_t cps_flag);
/* get ICACHE or DCACHE status */
uint32_t syscfg_cpu_cache_status_get(uint32_t cache, uint32_t status);
/* get brownout reset threshold level */
uint32_t syscfg_brownout_reset_threshold_level_get(void);

#endif /* GD32H77X_78X_SYSCFG_H */
