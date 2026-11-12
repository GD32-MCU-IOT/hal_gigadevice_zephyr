/*!
    \file    gd32h77x_78x_dsi.h
    \brief   definitions for the DSI

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

#ifndef GD32H77X_78X_DSI_H
#define GD32H77X_78X_DSI_H

#include "gd32h77x_78x.h"

/* peripheral definitions */
#define DSI                           DSI_BASE                   /*!< DSI base address */

/* registers definitions */
#define DSI_DEVRDY                    REG32((DSI) + 0x00000000U) /*!< DSI Host device ready register */
#define DSI_INTSTAT0                  REG32((DSI) + 0x00000004U) /*!< DSI Host interrupt status register0 */
#define DSI_INTEN0                    REG32((DSI) + 0x00000008U) /*!< DSI Host interrupt enable register0 */
#define DSI_FUNCPRG                   REG32((DSI) + 0x0000000CU) /*!< DSI Host function program register */
#define DSI_HSTXTO                    REG32((DSI) + 0x00000010U) /*!< DSI Host high speed transmission timeout register */
#define DSI_LPRXTO                    REG32((DSI) + 0x00000014U) /*!< DSI Host low power reception timeout register */
#define DSI_TATO                      REG32((DSI) + 0x00000018U) /*!< DSI Host turn around timeout register */
#define DSI_DEVRSTTM                  REG32((DSI) + 0x0000001CU) /*!< DSI Host device reset timer register */
#define DSI_DPIRES                    REG32((DSI) + 0x00000020U) /*!< DSI Host DPI resolution register */
#define DSI_DCSWC                     REG32((DSI) + 0x00000024U) /*!< DSI Host DCS word count register */
#define DSI_HSACFG                    REG32((DSI) + 0x00000028U) /*!< DSI Host horizontal sync active count configuration register */
#define DSI_HBPCFG                    REG32((DSI) + 0x0000002CU) /*!< DSI Host horizontal back porch count configuration register */
#define DSI_HFPCFG                    REG32((DSI) + 0x00000030U) /*!< DSI Host horizontal front porch count configuration register */
#define DSI_HACFG                     REG32((DSI) + 0x00000034U) /*!< DSI Host horizontal active area count configuration register */
#define DSI_VSACFG                    REG32((DSI) + 0x00000038U) /*!< DSI Host vertical sync active count configuration register */
#define DSI_VBPCFG                    REG32((DSI) + 0x0000003CU) /*!< DSI Host vertical back porch count configuration register */
#define DSI_VFPCFG                    REG32((DSI) + 0x00000040U) /*!< DSI Host vertical front porch count configuration register */
#define DSI_DLCFG                     REG32((DSI) + 0x00000044U) /*!< DSI Host data lane high low switch count configuration register */
#define DSI_DPICTL                    REG32((DSI) + 0x00000048U) /*!< DSI Host DPI control register */
#define DSI_DPHY_PLLLK                REG32((DSI) + 0x0000004CU) /*!< DSI Host Dphy PLL lock count register */
#define DSI_INITCFG                   REG32((DSI) + 0x00000050U) /*!< DSI Host initialization count configuration register */
#define DSI_MAXRPKTCTL                REG32((DSI) + 0x00000054U) /*!< DSI Host maximum return packet control register */
#define DSI_VMFMT                     REG32((DSI) + 0x00000058U) /*!< DSI Host Video mode format register */
#define DSI_CKEOTCTL                  REG32((DSI) + 0x0000005CU) /*!< DSI Host clock EOT control register */
#define DSI_PLCTL                     REG32((DSI) + 0x00000060U) /*!< DSI Host polarity control register */
#define DSI_CKLSWCFG                  REG32((DSI) + 0x00000064U) /*!< DSI Host clock lane switching configuration register */
#define DSI_LPBCLKCFG                 REG32((DSI) + 0x00000068U) /*!< DSI Host low power byte clock configuration register */
#define DSI_DPHY_PCFG                 REG32((DSI) + 0x0000006CU) /*!< DSI Host Dphy parameter configuration register */
#define DSI_DPHY_CLTMPCFG             REG32((DSI) + 0x00000070U) /*!< DSI Host Dphy clock lane timing parameter configuration register */
#define DSI_DPHY_RSTENDFE             REG32((DSI) + 0x00000074U) /*!< DSI Host Dphy reset enable to DFE register */
#define DSI_DPHY_TRIMCTL0             REG32((DSI) + 0x00000078U) /*!< DSI Host Dphy trim control register 0 */
#define DSI_DPHY_TRIMCTL1             REG32((DSI) + 0x0000007CU) /*!< DSI Host Dphy trim control register 1 */
#define DSI_DPHY_TRIMCTL2             REG32((DSI) + 0x00000080U) /*!< DSI Host Dphy trim control register 2 */
#define DSI_DSKCTL                    REG32((DSI) + 0x00000088U) /*!< DSI Host deskew control register */
#define DSI_DSKTM                     REG32((DSI) + 0x0000008CU) /*!< DSI Host periodic deskew timer register */
#define DSI_DSKSTAT                   REG32((DSI) + 0x00000090U) /*!< DSI Host deskew status register */
#define DSI_EARCTL                    REG32((DSI) + 0x00000098U) /*!< DSI Host error auto recovery control register */
#define DSI_MIPIDIRDPISTAT            REG32((DSI) + 0x0000009CU) /*!< DSI Host MIPI direction and DPI status register */
#define DSI_PLSWAP                    REG32((DSI) + 0x000000A0U) /*!< DSI Host Polarity Swap register */
#define DSI_FMCTL                     REG32((DSI) + 0x000000A4U) /*!< DSI Host frequency mode control register */
#define DSI_TXDTWCFG                  REG32((DSI) + 0x000000B0U) /*!< DSI Host Tx data width configuration register */
#define DSI_LPCTL                     REG32((DSI) + 0x000000F8U) /*!< DSI Host LP control register */
#define DSI_LPDATA                    REG32((DSI) + 0x000000FCU) /*!< DSI Host LP data register */
#define DSI_HSCTL                     REG32((DSI) + 0x00000100U) /*!< DSI Host HS control register */
#define DSI_HSDATA                    REG32((DSI) + 0x00000104U) /*!< DSI Host HS data register */
#define DSI_FIFOSTAT                  REG32((DSI) + 0x00000108U) /*!< DSI Host FIFO status register */
#define DSI_INTSTAT1                  REG32((DSI) + 0x0000010CU) /*!< DSI Host interrupt status register1 */
#define DSI_WCTL                      REG32((DSI) + 0x00000200U) /*!< DSI Wrapper control register */
#define DSI_WINTEN                    REG32((DSI) + 0x00000204U) /*!< DSI Wrapper interrupt enable register */
#define DSI_WINTSTAT                  REG32((DSI) + 0x00000208U) /*!< DSI Wrapper interrupt and status register */
#define DSI_WINTC                     REG32((DSI) + 0x0000020CU) /*!< DSI Wrapper interrupt flag clear register */
#define DSI_WRGBDF                    REG32((DSI) + 0x00000210U) /*!< DSI Wrapper RGB data format register */
#define DSI_WCMDDS                    REG32((DSI) + 0x00000220U) /*!< DSI Wrapper command mode data source register */
#define DSI_WDMARCTL                  REG32((DSI) + 0x00000224U) /*!< DSI Wrapper DMA request control register */
#define DSI_WWMS_WCTL                 REG32((DSI) + 0x00000230U) /*!< DSI Wrapper WMS write control register */
#define DSI_WWMS_INTMSK               REG32((DSI) + 0x00000234U) /*!< DSI Wrapper WMS interrupt mask register */
#define DSI_WWMS_HEAD                 REG32((DSI) + 0x00000238U) /*!< DSI Wrapper WMS header message register */
#define DSI_WWMS_SIZE                 REG32((DSI) + 0x0000023CU) /*!< DSI Wrapper WMS size control register */
#define DSI_WWMS_STAT0                REG32((DSI) + 0x00000240U) /*!< DSI Wrapper WMS status register 0 */
#define DSI_WWMS_STAT1                REG32((DSI) + 0x00000244U) /*!< DSI Wrapper WMS status register 1 */
#define DSI_INTEN1                    REG32((DSI) + 0x00000250U) /*!< DSI Host interrupt enable register 1 */

/* bits definitions */
/* DSI_DEVRDY */
#define DSI_DEVRDY_DEVRDY             BIT(0)              /*!< device ready */
#define DSI_DEVRDY_ULPS_STATE         BITS(1,2)           /*!< inform entire DSI host to enter ultra low power state(ULPS) */
#define DSI_DEVRDY_BUS_POSS           BIT(3)              /*!< display bus possession */

/* DSI_INTSTAT0 */
#define DSI_INTSTAT0_RXSOTE           BIT(0)              /*!< Rx sot error */
#define DSI_INTSTAT0_RXSOTSYNCE       BIT(1)              /*!< Rx sot sync error */
#define DSI_INTSTAT0_RXEOTSYNCE       BIT(2)              /*!< Rx eot sync error */
#define DSI_INTSTAT0_RXESCMEE         BIT(3)              /*!< Rx escape mode entry error */
#define DSI_INTSTAT0_RXLPTXSYNCE      BIT(4)              /*!< Rx LP tx sync error */
#define DSI_INTSTAT0_RXPTOE           BIT(5)              /*!< Rx peripheral timeout error */
#define DSI_INTSTAT0_RXFCTLE          BIT(6)              /*!< RxFalse control error */
#define DSI_INTSTAT0_RXECCSE          BIT(7)              /*!< Rx ECC single bit error */
#define DSI_INTSTAT0_RXECCME          BIT(8)              /*!< Rx ECC multi-bit error */
#define DSI_INTSTAT0_RXCHKE           BIT(9)              /*!< Rx checksum error */
#define DSI_INTSTAT0_RXDSIDTNR        BIT(10)             /*!< Rx DSI data type not recognized */
#define DSI_INTSTAT0_RXDSIVCIDINV     BIT(11)             /*!< Rx DSI virtual channel ID invalid */
#define DSI_INTSTAT0_TXFCTLE          BIT(12)             /*!< Tx false control error */
#define DSI_INTSTAT0_TXECCSE          BIT(13)             /*!< Tx ECC single bit error */
#define DSI_INTSTAT0_TXECCME          BIT(14)             /*!< Tx ECC multi-bit error */
#define DSI_INTSTAT0_TXCHKE           BIT(15)             /*!< Tx checksum(CRC) error */
#define DSI_INTSTAT0_TXDSIDTNR        BIT(16)             /*!< Tx DSI data type not recognized */
#define DSI_INTSTAT0_TXDSIVCIDINV     BIT(17)             /*!< Tx DSI virtual channel ID invalid */
#define DSI_INTSTAT0_HCONT            BIT(18)             /*!< high contention */
#define DSI_INTSTAT0_LCONT            BIT(19)             /*!< low contention */
#define DSI_INTSTAT0_FIFOE            BIT(20)             /*!< FIFO empty */
#define DSI_INTSTAT0_HSTXTO           BIT(21)             /*!< HS Tx timeout */
#define DSI_INTSTAT0_LPRXTO           BIT(22)             /*!< LP Rx timeout */
#define DSI_INTSTAT0_TAACKTO          BIT(23)             /*!< turn around ack timeout */
#define DSI_INTSTAT0_ACKNE            BIT(24)             /*!< ACK with no error */
#define DSI_INTSTAT0_RXINVTXCE        BIT(25)             /*!< Rx invalid transmission count error */
#define DSI_INTSTAT0_RXDSIPV          BIT(26)             /*!< Rx DSI protocol violation */
#define DSI_INTSTAT0_SPKTCMDS         BIT(27)             /*!< special packet command sent */
#define DSI_INTSTAT0_INIT_DONE        BIT(28)             /*!< DSI initialization is done */
#define DSI_INTSTAT0_RXCONTDET        BIT(29)             /*!< Rx contention detected */
#define DSI_INTSTAT0_DPILTO           BIT(30)             /*!< DPI line timeout */
#define DSI_INTSTAT0_DPIPE            BIT(31)             /*!< DPI program error */

/* DSI_INTEN0 */
#define DSI_INTEN0_RXSOTEIE           BIT(0)              /*!< Rx sot error interrupt enable */
#define DSI_INTEN0_RXSOTSYNCEIE       BIT(1)              /*!< Rx sot sync error interrupt enable */
#define DSI_INTEN0_RXEOTSYNCEIE       BIT(2)              /*!< Rx eot sync error interrupt enable */
#define DSI_INTEN0_RXESCMEEIE         BIT(3)              /*!< Rx escape mode entry error interrupt enable */
#define DSI_INTEN0_RXLPTXSYNCEIE      BIT(4)              /*!< Rx LP tx sync error interrupt enable */
#define DSI_INTEN0_RXPTOEIE           BIT(5)              /*!< Rx peripheral timeout error interrupt enable */
#define DSI_INTEN0_RXFCTLEIE          BIT(6)              /*!< RxFalse control error interrupt enable */
#define DSI_INTEN0_RXECCSEIE          BIT(7)              /*!< Rx ECC single bit error interrupt enable */
#define DSI_INTEN0_RXECCMEIE          BIT(8)              /*!< Rx ECC multi-bit error interrupt enable */
#define DSI_INTEN0_RXCHKEIE           BIT(9)              /*!< Rx checksum error interrupt enable */
#define DSI_INTEN0_RXDSIDTNRIE        BIT(10)             /*!< Rx DSI data type not recognized interrupt enable */
#define DSI_INTEN0_RXDSIVCIDINVIE     BIT(11)             /*!< Rx DSI virtual channel ID invalid interrupt enable */
#define DSI_INTEN0_TXFCTLEIE          BIT(12)             /*!< Tx false control error interrupt enable */
#define DSI_INTEN0_TXECCSEIE          BIT(13)             /*!< Tx ECC single bit error interrupt enable */
#define DSI_INTEN0_TXECCMEIE          BIT(14)             /*!< Tx ECC multi-bit error interrupt enable */
#define DSI_INTEN0_TXCHKEIE           BIT(15)             /*!< Tx checksum(CRC) error interrupt enable */
#define DSI_INTEN0_TXDSIDTNRIE        BIT(16)             /*!< Tx DSI data type not recognized interrupt enable */
#define DSI_INTEN0_TXDSIVCIDINVIE     BIT(17)             /*!< Tx DSI virtual channel ID invalid interrupt enable */
#define DSI_INTEN0_HCONTIE            BIT(18)             /*!< high contention interrupt enable */
#define DSI_INTEN0_LCONTIE            BIT(19)             /*!< low contention interrupt enable */
#define DSI_INTEN0_FIFOEIE            BIT(20)             /*!< FIFO empty interrupt enable */
#define DSI_INTEN0_HSTXTOIE           BIT(21)             /*!< HS Tx timeout interrupt enable */
#define DSI_INTEN0_LPRXTOIE           BIT(22)             /*!< LP Rx timeout interrupt enable */
#define DSI_INTEN0_TAACKTOIE          BIT(23)             /*!< turn around ack timeout interrupt enable */
#define DSI_INTEN0_ACKNEIE            BIT(24)             /*!< ACK with no error interrupt enable */
#define DSI_INTEN0_RXINVTXCEIE        BIT(25)             /*!< Rx invalid transmission count error interrupt enable */
#define DSI_INTEN0_RXDSIPVIE          BIT(26)             /*!< Rx DSI protocol violation interrupt enable */
#define DSI_INTEN0_SPKTCMDSIE         BIT(27)             /*!< special packet command sent interrupt enable */
#define DSI_INTEN0_INIT_DONEIE        BIT(28)             /*!< DSI initialization is done interrupt enable */
#define DSI_INTEN0_RXCONTDETIE        BIT(29)             /*!< Rx contention detected interrupt enable */
#define DSI_INTEN0_DPILTOIE           BIT(30)             /*!< Enable DPI line timeout interrupt enable */
#define DSI_INTEN0_DPIPEIE            BIT(31)             /*!< DPI program error interrupt enable */

/* DSI_FUNCPRG */
#define DSI_FUNCPRG_DTLANE_PRG        BITS(0,2)           /*!< number of data lanes */
#define DSI_FUNCPRG_VCHNUMVM          BITS(3,4)           /*!< virtual channel number for video mode */
#define DSI_FUNCPRG_VCHNUMCM          BITS(5,6)           /*!< virtual channel number for command mode */
#define DSI_FUNCPRG_SFMTVM            BITS(7,9)           /*!< supported color format for video mode */
#define DSI_FUNCPRG_SDTWCM            BITS(13,15)         /*!< supported data width in command mode */

/* DSI_HSTXTO */
#define DSI_HSTXTO_HSTXTOCNT          BITS(0,23)          /*!< high speed transmission timeout counter */

/* DSI_LPRXTO */
#define DSI_LPRXTO_LPRXTOCNT          BITS(0,23)          /*!< low power reception timeout counter */

/* DSI_TATO */
#define DSI_TATO_TATO                 BITS(0,5)           /*!< turn around timeout */

/* DSI_DEVRSTTM */
#define DSI_DEVRSTTM_DEVRTSTTM        BITS(0,15)          /*!< device reset timer */

/* DSI_DPIRES */
#define DSI_DPIRES_DPIRES             BITS(0,31)          /*!< DPI resolution */

/* DSI_DCSWC */
#define DSI_DCSWC_DCSWC               BITS(0,15)          /*!< DCS/Generic word count values need to be written before DCS or Generic long write */

/* DSI_HSACFG */
#define DSI_HSACFG_HSACNT             BITS(0,15)          /*!< horizontal sync active count */

/* DSI_HBPCFG */
#define DSI_HBPCFG_HBPCNT             BITS(0,15)          /*!< horizontal back porch count value */

/* DSI_HFPCFG */
#define DSI_HFPCFG_HFPCNT             BITS(0,15)          /*!< horizontal front porch count value */

/* DSI_HACFG */
#define DSI_HACFG_HACNT               BITS(0,15)          /*!< horizontal active area count,that is the time for active horizontal address */

/* DSI_VSACFG */
#define DSI_VSACFG_VSACNT             BITS(0,15)          /*!< vertical sync active count value */

/* DSI_VBPCFG */
#define DSI_VBPCFG_VBPCNT             BITS(0,15)          /*!< vertical back porch count value */

/* DSI_VFPCFG */
#define DSI_VFPCFG_VFPCNT             BITS(0,15)          /*!< vertical front porch count value */

/* DSI_DLCFG */
#define DSI_DLCFG_DLCFG               BITS(0,15)          /*!< switch count of HS to LP or LP to HS for data lane */

/* DSI_DPICTL */
#define DSI_DPICTL_SD                 BIT(0)              /*!< shut down(0x01) command is packetized for the DPI's virtual channel */
#define DSI_DPICTL_TON                BIT(1)              /*!< turn ON (0x02) command is packetized for the DPI's virtual channel */
#define DSI_DPICTL_CMON               BIT(2)              /*!< color mode ON(0x04) command is packetized for the DPI's virtual channel */
#define DSI_DPICTL_CMOFF              BIT(3)              /*!< color mode OFF(0x08) command is packetized for the DPI's virtual channel */

/* DSI_DPHY_PLLLK */
#define DSI_DPHY_PLLLK_PLLCNTVAL      BITS(0,15)          /*!< PLL counter value in terms of low power clock */

/* DSI_INITCFG */
#define DSI_INITCFG_INITCNT           BITS(0,15)          /*!< counter value in terms of low power clock to initialize the DSI Host IP that drives a stop state on the mipi's D-PHY bus */

/* DSI_MAXRPKTCTL */
#define DSI_MAXRPKTCTL_MAXRPKTSZ      BITS(0,10)          /*!< maximum return packet size in bytes */
#define DSI_MAXRPKTCTL_HS_LP          BIT(15)             /*!< indicates the data transfer type */

/* DSI_VMFMT */
#define DSI_VMFMT_VMFMT               BITS(0,1)           /*!< video mode format */

/* DSI_CKEOTCTL */
#define DSI_CKEOTCTL_EOTDIS           BIT(0)              /*!< disable EOT packet(EoTp) transmission */
#define DSI_CKEOTCTL_CKSTOP           BIT(1)              /*!< enable clock stopping feature */
#define DSI_CKEOTCTL_VBTADIS          BIT(2)              /*!< disable video BTA */

/* DSI_PLCTL */
#define DSI_PLCTL_PL                  BITS(0,3)           /*!< polarity */

/* DSI_CKLSWCFG */
#define DSI_CKLSWCFG_HSLPSW           BITS(0,15)          /*!< HS to LP switching counter for clock lane */
#define DSI_CKLSWCFG_LPHSSW           BITS(16,31)         /*!< LP to HS switching counter for clock lane */

/* DSI_LPBCLKCFG */
#define DSI_LPBCLKCFG_LPBYTECLK       BITS(0,15)          /*!< LP clock equivalence in terms of byte clock */

/* DSI_DPHY_PCFG */
#define DSI_DPHY_PCFG_HS_PREP         BITS(0,7)           /*!< HS preparation time(THS-PREPARE) */
#define DSI_DPHY_PCFG_HS_ZERO         BITS(8,15)          /*!< HS drive zero time(THS-ZERO) */
#define DSI_DPHY_PCFG_HS_TRAIL        BITS(16,23)         /*!< HS trail time(THS-TRAIL) */
#define DSI_DPHY_PCFG_HS_EXIT         BITS(24,31)         /*!< HS exit time(THS-EXIT) */

/* DSI_DPHY_CLTMPCFG */
#define DSI_DPHY_CLTMPCFG_CLK_PREP    BITS(0,7)           /*!< CLK preparation time(TCLK-PREPARE) */
#define DSI_DPHY_CLTMPCFG_CLK_ZERO    BITS(8,15)          /*!< CLK drive zero time(TCLK-ZERO) */
#define DSI_DPHY_CLTMPCFG_CLK_TRAIL   BITS(16,23)         /*!< CLK trail time(TCLK-TRAIL) */
#define DSI_DPHY_CLTMPCFG_CLK_EXIT    BITS(24,31)         /*!< CLK exit time(TCLK-EXIT) */

/* DSI_DPHY_RSTENDFE */
#define DSI_DPHY_RSTENDFE_RSTENDFE    BIT(0)              /*!< reset (enable) to the digital front end(DFE) */

/* DSI_DPHY_TRIMCTL0 */
#define DSI_DPHY_TRIMCTL0_TRIM_FF_BYPASS            BIT(0)              /*!< used to bypass the LPTX signals sampling done by the reference clock */
#define DSI_DPHY_TRIMCTL0_TRIM_FF_BYPASSC           BIT(1)              /*!< used to bypass the LPTX signals sampling done by the reference clock */
#define DSI_DPHY_TRIMCTL0_TRIM_LP_SLEWRATE          BITS(2,3)           /*!< adjust the LP transmit signal slew rate */
#define DSI_DPHY_TRIMCTL0_TX_HS_DRV                 BITS(4,5)           /*!< adjust the HS driver impedance */
#define DSI_DPHY_TRIMCTL0_TX_HS_SLEW                BITS(6,7)           /*!< adjust the HS transmit signal slew rate */
#define DSI_DPHY_TRIMCTL0_TX_BCLK_POL_SEL           BIT(8)              /*!< select the TX byte clock polarity */
#define DSI_DPHY_TRIMCTL0_LP_DC_TEST_EN             BIT(9)              /*!< enable LP transmitter DC test */
#define DSI_DPHY_TRIMCTL0_HS_DC_TEST_EN             BIT(10)             /*!< enable HS transmitter DC test */
#define DSI_DPHY_TRIMCTL0_DC_TEST_DATA              BIT(11)             /*!< LP or HS data to transmit out when anyone of the DC test is enabled */
#define DSI_DPHY_TRIMCTL0_VBG_SEL                   BIT(12)             /*!< select the PVT independent bandgap voltage */
#define DSI_DPHY_TRIMCTL0_BG_TRIM                   BITS(13,14)         /*!< adjust bandgap reference voltage */
#define DSI_DPHY_TRIMCTL0_CD_HIGH_750MV_TRIM        BITS(15,16)         /*!< adjust CD reference high voltage */
#define DSI_DPHY_TRIMCTL0_CD_LOW_325MV_TRIM         BITS(17,18)         /*!< adjust CD reference low voltage */
#define DSI_DPHY_TRIMCTL0_LP_LDO_REF_725MV_TRIM     BITS(19,20)         /*!< adjust LP LDO reference voltage */
#define DSI_DPHY_TRIMCTL0_LPRX_REF_650MV_TRIM       BITS(21,22)         /*!< adjust LP RX reference voltage */
#define DSI_DPHY_TRIMCTL0_PLL_CP_LDO_900MV_TRIM     BITS(23,24)         /*!< adjust PLL CP LDO reference voltage */
#define DSI_DPHY_TRIMCTL0_TX_PREDRV_REF_400MV_TRIM  BITS(25,26)         /*!< adjust HS TX pre-driver LDO reference voltage */
#define DSI_DPHY_TRIMCTL0_TX_VMD_REF_400MV_TRIM     BITS(27,29)         /*!< adjust HS TX common mode voltage */
#define DSI_DPHY_TRIMCTL0_LPLDOPD_IN                BIT(30)             /*!< external LP LDO power down */
#define DSI_DPHY_TRIMCTL0_LPLDOPD_SEL               BIT(31)             /*!< LP LDO power down selection */

/* DSI_DPHY_TRIMCTL1 */
#define DSI_DPHY_TRIMCTL1_CNTB                      BIT(0)              /*!< reference CNTA[5:0] */
#define DSI_DPHY_TRIMCTL1_CNTA                      BITS(1,6)           /*!< PLL divider ratio used in counter */
#define DSI_DPHY_TRIMCTL1_EXT_RSTB_EN               BIT(7)              /*!< enable external active-low reset */
#define DSI_DPHY_TRIMCTL1_EXT_RSTB                  BIT(8)              /*!< external active-low reset */
#define DSI_DPHY_TRIMCTL1_RES                       BITS(9,11)          /*!< LPF resistor selection */
#define DSI_DPHY_TRIMCTL1_BW_RES_SEL                BIT(12)             /*!< PLL LPF resistor selection */
#define DSI_DPHY_TRIMCTL1_PLL_STCKSEL               BITS(13,14)         /*!< control to select a clock from PLL to test */
#define DSI_DPHY_TRIMCTL1_TSTODBY4                  BIT(15)             /*!< control to select clock DIvide by 4 or clock divide by 8 as output */
#define DSI_DPHY_TRIMCTL1_REFCLK_DLY                BITS(16,17)         /*!< programmable escape clock delay in AFE to capture the LP data driven by the DFE */
#define DSI_DPHY_TRIMCTL1_BYPASS_LPTX_PU_LOGIC      BIT(18)             /*!< LP11 initialization bypass signal for data lanes */
#define DSI_DPHY_TRIMCTL1_BYPASS_LPTX_PU_LOGIC_CK   BIT(19)             /*!< LP11 initialization bypass signal for clock lane */
#define DSI_DPHY_TRIMCTL1_CDPD0                     BIT(20)             /*!< contention detection block power down signal */
#define DSI_DPHY_TRIMCTL1_RXLANE_POLARITY_SWAP0     BIT(21)             /*!< control to swap the polarity of the RX output */
#define DSI_DPHY_TRIMCTL1_LPRX_GLITCH_FILT_BYPASS   BIT(22)             /*!< LPXOR clock glitch filter bypass enable */
#define DSI_DPHY_TRIMCTL1_LPXORCLK_DLY              BITS(23,24)         /*!< programmable delay in LP XOR clock */
#define DSI_DPHY_TRIMCTL1_PLL_CP_CT_TRIM            BITS(25,26)         /*!< programmable PLL charge pump current */
#define DSI_DPHY_TRIMCTL1_PLL_SUPPLY_SEL            BIT(27)             /*!< PLL CP supply voltage selection */
#define DSI_DPHY_TRIMCTL1_TRIM_DIS_ULPS_LP00        BIT(28)             /*!< disable weak pull-down resistor added in mipi data lanes */
#define DSI_DPHY_TRIMCTL1_TRIM_DIS_ULPS_LP00_CK     BIT(29)             /*!< disable weak pull-down resistor added in mipi clock lane */
#define DSI_DPHY_TRIMCTL1_TRIM_AFE_OFF_ULPS         BIT(30)             /*!< enable to power off all AFE blocks in ULPS */
#define DSI_DPHY_TRIMCTL1_ESCAPE_CLK_SEL            BIT(31)             /*!< it is used to select the reference clock */

/* DSI_DPHY_TRIMCTL2 */
#define DSI_DPHY_TRIMCTL2_TRIM_LPRX_BYPASS_EN       BIT(0)              /*!< control to overwrite LP RX enable */
#define DSI_DPHY_TRIMCTL2_TRIM_LPRX_D0              BIT(1)              /*!< control to overwrite LP RX data */
#define DSI_DPHY_TRIMCTL2_TRIM_HSTX_BYPASS_EN       BIT(2)              /*!< control to overwrite HS TX enable */
#define DSI_DPHY_TRIMCTL2_TRIM_HSTX_CK              BIT(3)              /*!< control to overwrite HS TX data of clock lane */
#define DSI_DPHY_TRIMCTL2_TRIM_HSTX_D0              BIT(4)              /*!< control to overwrite HS TX data of data lane0 */
#define DSI_DPHY_TRIMCTL2_TRIM_HSTX_D1              BIT(5)              /*!< control to overwrite HS TX data of data lane1 */
#define DSI_DPHY_TRIMCTL2_TRIM_LPTX_BYPASS_EN       BIT(6)              /*!< control to overwrite LP TX enable */
#define DSI_DPHY_TRIMCTL2_TRIM_LPTX_CK              BIT(7)              /*!< control to overwrite LP TX data of clock lane */
#define DSI_DPHY_TRIMCTL2_TRIM_LPTX_D0              BIT(8)              /*!< control to overwrite LP TX data of data lane0 */
#define DSI_DPHY_TRIMCTL2_TRIM_LPTX_D1              BIT(9)              /*!< control to overwrite LP TX data of data lane1 */
#define DSI_DPHY_TRIMCTL2_SYS_RESET_N_INT           BIT(17)             /*!< optional system reset signal */
#define DSI_DPHY_TRIMCTL2_LANE0_EN                  BIT(18)             /*!< lane enable control for lane0 */
#define DSI_DPHY_TRIMCTL2_LANE1_EN                  BIT(19)             /*!< lane enable control for lane1 */
#define DSI_DPHY_TRIMCTL2_DPHY_MUX_CFG              BIT(20)             /*!< lane swap configuration bit */
#define DSI_DPHY_TRIMCTL2_PSWP0                     BIT(21)             /*!< data lane 0 polarity swap enable */
#define DSI_DPHY_TRIMCTL2_PSWP1                     BIT(22)             /*!< data lane 1 polarity swap enable */
#define DSI_DPHY_TRIMCTL2_CPSWP                     BIT(23)             /*!< clock lane polarity swap enable */
#define DSI_DPHY_TRIMCTL2_V2IPD                     BIT(24)             /*!< force bias circuits power down if PDR is set 1 */
#define DSI_DPHY_TRIMCTL2_BGPD                      BIT(25)             /*!< force bandgap circuits power down if PDR is set 1 */
#define DSI_DPHY_TRIMCTL2_HSTX_LDO_PD               BIT(26)             /*!< force high speed driver LDO circuits power down */
#define DSI_DPHY_TRIMCTL2_PLLPD                     BIT(27)             /*!< force PLL circuits power down if PDR is set 1 */
#define DSI_DPHY_TRIMCTL2_TRIM_PLL_LOCK             BIT(28)             /*!< force PLL lock detect high */
#define DSI_DPHY_TRIMCTL2_PDR                       BIT(29)             /*!< power down control */

/* DSI_DSKCTL */
#define DSI_DSKCTL_DSKCALIB              BITS(0,1)           /*!< deskew calibration */
#define DSI_DSKCTL_DSKDUR                BITS(2,17)          /*!< deskew duration */

/* DSI_DSKTM */
#define DSI_DSKTM_DSKTM                  BITS(0,15)          /*!< periodic deskew timer */

/* DSI_DSKSTAT */
#define DSI_DSKSTAT_DSKIP                BIT(0)              /*!< deskew calibration is in progress */

/* DSI_EARCTL */
#define DSI_EARCTL_ECC_MUL_ERR_CLR       BIT(0)              /*!< ecc_mul_err_clr error recovery action is taken immediately by DSI TX */
#define DSI_EARCTL_INVLD_DT_CLR          BIT(1)              /*!< invld_dt_clr error recovery action is taken immediately by DSI TX */
#define DSI_EARCTL_HI_CONT_CLR           BIT(2)              /*!< hi_cont_clr error recovery action is taken immediately by DSI TX */
#define DSI_EARCTL_LO_CONT_CLR           BIT(3)              /*!< lo_cont_clr error recovery action is taken immediately by DSI TX */
#define DSI_EARCTL_HS_RX_TO_CLR          BIT(4)              /*!< hs_rx_timeout_clr error recovery action is taken immediately by DSI TX */
#define DSI_EARCTL_LP_RX_TO_CLR          BIT(5)              /*!< lp_rx_timeout_clr error recovery action is taken immediately by DSI TX */

/* DSI_MIPIDIRDPISTAT */
#define DSI_MIPIDIRDPISTAT_MIPI_DIR      BIT(0)              /*!< MIPI bus direction */
#define DSI_MIPIDIRDPISTAT_DPI_HI        BIT(15)             /*!< DPI line time is greater or DSI line time is greater */
#define DSI_MIPIDIRDPISTAT_DPI_DIFF      BITS(16,31)         /*!< the difference in one line time between DPI and DSI */

/* DSI_PLSWAP */
#define DSI_PLSWAP_VSPL                  BIT(0)              /*!< vsync polarity */
#define DSI_PLSWAP_HSPL                  BIT(1)              /*!< hsync polarity */
#define DSI_PLSWAP_SDPL                  BIT(2)              /*!< shutdown polarity */
#define DSI_PLSWAP_CMPL                  BIT(3)              /*!< color mode polarity */

/* DSI_FMCTL */
#define DSI_FMCTL_FREQMOD                BIT(0)              /*!< frequency mode */

/* DSI_TXDTWCFG */
#define DSI_TXDTWCFG_TXDTWIDTH           BITS(0,7)           /*!< Tx data width hs */

/* DSI_LPCTL */
#define DSI_LPCTL_DTTYPE                 BITS(0,5)           /*!< data type */
#define DSI_LPCTL_VCH                    BITS(6,7)           /*!< virtual channel */
#define DSI_LPCTL_WORDCNT                BITS(8,23)          /*!< word count */

/* DSI_LPDATA */
#define DSI_LPDATA_LPDATA                BITS(0,31)          /*!< data used for Generic/ DCS data transfers in low power mode */

/* DSI_HSCTL */
#define DSI_HSCTL_DTTYPE                 BITS(0,5)           /*!< data type */
#define DSI_HSCTL_VCH                    BITS(6,7)           /*!< virtual channel */
#define DSI_HSCTL_WORDCNT                BITS(8,23)          /*!< word count */

/* DSI_HSDATA */
#define DSI_HSDATA_HSDATA                BITS(0,31)          /*!< data used for Generic/ DCS data transfers in high-speed mode */

/* DSI_FIFOSTAT */
#define DSI_FIFOSTAT_HSDTFIFOF           BIT(0)              /*!< HS Generic/DCS data FIFO full */
#define DSI_FIFOSTAT_HSDTFIFOHE          BIT(1)              /*!< HS Generic/DCS data FIFO half empty */
#define DSI_FIFOSTAT_HSDTFIFOE           BIT(2)              /*!< HS Generic/DCS data FIFO empty */
#define DSI_FIFOSTAT_LPDTFIFOF           BIT(8)              /*!< LP Generic/DCS data FIFO full */
#define DSI_FIFOSTAT_LPDTFIFOHE          BIT(9)              /*!< LP Generic/DCS data FIFO half empty */
#define DSI_FIFOSTAT_LPDTFIFOE           BIT(10)             /*!< LP Generic/DCS data FIFO empty */
#define DSI_FIFOSTAT_HSCTLFIFOF          BIT(16)             /*!< HS Generic/DCS control FIFO full */
#define DSI_FIFOSTAT_HSCTLFIFOHE         BIT(17)             /*!< HS Generic/DCS control FIFO half empty */
#define DSI_FIFOSTAT_HSCTLFIFOE          BIT(18)             /*!< HS Generic/DCS control FIFO empty */
#define DSI_FIFOSTAT_LPCTLFIFOF          BIT(24)             /*!< LP Generic/DCS control FIFO full */
#define DSI_FIFOSTAT_LPCTLFIFOHE         BIT(25)             /*!< LP Generic/DCS control FIFO half empty */
#define DSI_FIFOSTAT_LPCTLFIFOE          BIT(26)             /*!< LP Generic/DCS control FIFO empty */

/* DSI_INTSTAT1 */
#define DSI_INTSTAT1_HSDTFIFOFIF         BIT(0)              /*!< HS Generic/DCS data FIFO full */
#define DSI_INTSTAT1_LPDTFIFOFIF         BIT(1)              /*!< LP Generic/DCS data FIFO full */
#define DSI_INTSTAT1_LPCTLFIFOFIF        BIT(2)              /*!< LP Generic/DCS control FIFO full */
#define DSI_INTSTAT1_HSCTLFIFOFIF        BIT(3)              /*!< HS Generic/DCS control FIFO full */
#define DSI_INTSTAT1_RDDTAIF             BIT(4)              /*!< LP Generic/DCS read data available */
#define DSI_INTSTAT1_TETGIF              BIT(5)              /*!< tearing effect(TE) trigger message received */

/* DSI_WCTL */
#define DSI_WCTL_TEPOL                   BIT(3)              /*!< TE pin polarity */
#define DSI_WCTL_TLIDMA                  BIT(4)              /*!< TLI DMA mode */
#define DSI_WCTL_TESRC                   BIT(5)              /*!< tearing effect (TE) source */
#define DSI_WCTL_ARM                     BIT(6)              /*!< automatic refresh mode */
#define DSI_WCTL_RBUF                    BIT(7)              /*!< refresh cmd fifo buffer */
#define DSI_WCTL_ARBUF                   BIT(8)              /*!< hardware auto refresh cmd fifo buffer enable */

/* DSI_WINTEN */
#define DSI_WINTEN_TEIE                  BIT(0)              /*!< tearing effect interrupt enable */
#define DSI_WINTEN_PLLLKIE               BIT(1)              /*!< PLL lock interrupt enable */
#define DSI_WINTEN_PLLULKIE              BIT(2)              /*!< PLL unlock interrupt enable */

/* DSI_WINTSTAT */
#define DSI_WINTSTAT_TEIF                BIT(0)              /*!< tearing effect interrupt flag */
#define DSI_WINTSTAT_PLLLKIF             BIT(1)              /*!< PLL lock interrupt flag */
#define DSI_WINTSTAT_PLLULKIF            BIT(2)              /*!< PLL unlock interrupt flag */
#define DSI_WINTSTAT_PLLLKS              BIT(3)              /*!< PLL lock status */

/* DSI_WINTC */
#define DSI_WINTC_TEIC                   BIT(0)              /*!< tearing effect interrupt flag clear */
#define DSI_WINTC_PLLLKIC                BIT(1)              /*!< PLL lock interrupt flag clear */
#define DSI_WINTC_PLLULKIC               BIT(2)              /*!< PLL unlock interrupt flag clear */

/* DSI_WRGBDF */
#define DSI_WRGBDF_TLI_DF                BITS(0,2)           /*!< TLI data format select */

/* DSI_WCMDDS */
#define DSI_WCMDDS_HSCMDDS               BIT(0)              /*!< command mode high speed fifo write data source */
#define DSI_WCMDDS_LPCMDDS               BIT(1)              /*!< command mode low power fifo write data source */

/* DSI_WDMARCTL */
#define DSI_WDMARCTL_DMASRC              BITS(4,6)           /*!< DMA request source select */

/* DSI_WWMS_WCTL */
#define DSI_WWMS_WCTL_WMS_EN             BIT(0)              /*!< write memory split packet enable */
#define DSI_WWMS_WCTL_WMS_MODE           BIT(1)              /*!< WMS function used for different modes */
#define DSI_WWMS_WCTL_WMS_END            BIT(4)              /*!< write memory split packet end flag */

/* DSI_WWMS_INTMSK */
#define DSI_WWMS_INTMSK_WMS_ENDMSK       BIT(4)              /*!< WMS_END flag interrupt signal mask */

/* DSI_WWMS_HEAD */
#define DSI_WWMS_HEAD_FIRST_HEAD         BITS(0,7)           /*!< first split packet head message */
#define DSI_WWMS_HEAD_SECOND_HEAD        BITS(8,15)          /*!< secondary split packet head message */
#define DSI_WWMS_HEAD_LONG_DCS_CMD       BITS(16,23)         /*!< long packet DCS command */

/* DSI_WWMS_SIZE */
#define DSI_WWMS_SIZE_PKT_LEN            BITS(0,7)           /*!< divide the DMA into the length of each packet, in the number of words */
#define DSI_WWMS_SIZE_SUM_LEN            BITS(8,31)          /*!< the total number of words to be transferred by a single DMA trigger */

/* DSI_WWMS_STAT0 */
#define DSI_WWMS_STAT0_PKT_NUM           BITS(0,15)          /*!< current number of packets transferred */

/* DSI_WWMS_STAT1 */
#define DSI_WWMS_STAT1_SUM_CNT           BITS(0,23)          /*!< current count of transferred words */

/* DSI_INTEN1 */
#define DSI_INTEN1_HSDTFIFOFIE           BIT(1)              /*!< HS Generic/DCS data FIFO full interrupt enable */
#define DSI_INTEN1_LPDTFIFOFIE           BIT(2)              /*!< LP Generic/DCS data FIFO full interrupt enable */
#define DSI_INTEN1_LPCTLFIFOFIE          BIT(3)              /*!< LP Generic/DCS control FIFO full interrupt enable */
#define DSI_INTEN1_HSCTLFIFOFIE          BIT(4)              /*!< HS Generic/DCS control FIFO full interrupt enable */
#define DSI_INTEN1_RDDTAIE               BIT(5)              /*!< LP Generic/DCS read data available interrupt enable */
#define DSI_INTEN1_TETGIE                BIT(6)              /*!< tearing effect(TE) trigger message received interrupt enable */

/* constants definitions */
/* define the DSI bit position and its register index offset */
#define DSI_REGIDX_BIT(regidx, bitpos)    (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define DSI_REG_VAL(dsix, offset)         (REG32((dsix) + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define DSI_BIT_POS(val)                  ((uint32_t)(val) & 0x0000001FU)
#define DSI_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                           | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define DSI_REG_VAL2(dsix, offset)       (REG32((dsix) + ((uint32_t)(offset) >> 22)))
#define DSI_BIT_POS2(val)                (((uint32_t)(val) & 0x001F0000U) >> 16)

/* register offset */
#define DSI_DEVRDY_REG_OFFSET              0x00000000U           /*!< device ready register offset */
#define DSI_INTSTAT0_REG_OFFSET            0x00000004U           /*!< interrupt status register 0 offset */
#define DSI_INTEN0_REG_OFFSET              0x00000008U           /*!< interrupt enable register 0 offset */
#define DSI_FUNCPRG_REG_OFFSET             0x0000000CU           /*!< function program register offset */
#define DSI_HSTXTO_REG_OFFSET              0x00000010U           /*!< high speed transmission timeout register offset */
#define DSI_LPRXTO_REG_OFFSET              0x00000014U           /*!< low power reception timeout register offset */
#define DSI_TATO_REG_OFFSET                0x00000018U           /*!< turn around timeout register offset */
#define DSI_DEVRSTTM_REG_OFFSET            0x0000001CU           /*!< device reset timer register offset */
#define DSI_DPIRES_REG_OFFSET              0x00000020U           /*!< DPI resolution register offset */
#define DSI_DCSWC_REG_OFFSET               0x00000024U           /*!< DCS word count register offset */
#define DSI_HSACFG_REG_OFFSET              0x00000028U           /*!< horizontal sync active count configuration register offset */
#define DSI_HBPCFG_REG_OFFSET              0x0000002CU           /*!< horizontal back porch count configuration register offset */
#define DSI_HFPCFG_REG_OFFSET              0x00000030U           /*!< horizontal front porch count configuration register offset */
#define DSI_HACFG_REG_OFFSET               0x00000034U           /*!< horizontal active area count configuration register offset */
#define DSI_VSACFG_REG_OFFSET              0x00000038U           /*!< vertical sync active count configuration register offset */
#define DSI_VBPCFG_REG_OFFSET              0x0000003CU           /*!< vertical back porch count configuration register offset */
#define DSI_VFPCFG_REG_OFFSET              0x00000040U           /*!< vertical front porch count configuration register offset */
#define DSI_DLCFG_REG_OFFSET               0x00000044U           /*!< data lane high low switch count configuration register offset */
#define DSI_DPICTL_REG_OFFSET              0x00000048U           /*!< DPI control register offset */
#define DSI_DPHY_PLLLK_REG_OFFSET          0x0000004CU           /*!< Dphy PLL lock count register offset */
#define DSI_INITCFG_REG_OFFSET             0x00000050U           /*!< initialization count configuration register offset */
#define DSI_MAXRPKTCTL_REG_OFFSET          0x00000054U           /*!< maximum return packet control register offset */
#define DSI_VMFMT_REG_OFFSET               0x00000058U           /*!< video mode format register offset */
#define DSI_CKEOTCTL_REG_OFFSET            0x0000005CU           /*!< clock EOT control register offset */
#define DSI_PLCTL_REG_OFFSET               0x00000060U           /*!< polarity control register offset */
#define DSI_CKLSWCFG_REG_OFFSET            0x00000064U           /*!< clock lane switching configuration register offset */
#define DSI_LPBCLKCFG_REG_OFFSET           0x00000068U           /*!< low power byte clock configuration register offset */
#define DSI_DPHY_PCFG_REG_OFFSET           0x0000006CU           /*!< Dphy parameter configuration register offset */
#define DSI_DPHY_CLTMPCFG_REG_OFFSET       0x00000070U           /*!< Dphy clock lane timing parameter configuration register offset */
#define DSI_DPHY_RSTENDFE_REG_OFFSET       0x00000074U           /*!< Dphy reset enable to DFE register offset */
#define DSI_DPHY_TRIMCTL0_REG_OFFSET       0x00000078U           /*!< Dphy trim control register 0 offset */
#define DSI_DPHY_TRIMCTL1_REG_OFFSET       0x0000007CU           /*!< Dphy trim control register 1 offset */
#define DSI_DPHY_TRIMCTL2_REG_OFFSET       0x00000080U           /*!< Dphy trim control register 2 offset */
#define DSI_DSKCTL_REG_OFFSET              0x00000088U           /*!< deskew control register offset */
#define DSI_DSKTM_REG_OFFSET               0x0000008CU           /*!< periodic deskew timer register offset */
#define DSI_DSKSTAT_REG_OFFSET             0x00000090U           /*!< deskew status register offset */
#define DSI_EARCTL_REG_OFFSET              0x00000098U           /*!< error auto recovery control register offset */
#define DSI_MIPIDIRDPISTAT_REG_OFFSET      0x0000009CU           /*!< MIPI direction and DPI status register offset */
#define DSI_PLSWAP_REG_OFFSET              0x000000A0U           /*!< polarity swap register offset */
#define DSI_FMCTL_REG_OFFSET               0x000000A4U           /*!< frequency mode control register offset */
#define DSI_TXDTWCFG_REG_OFFSET            0x000000B0U           /*!< Tx data width configuration register offset */
#define DSI_LPCTL_REG_OFFSET               0x000000F8U           /*!< LP control register offset */
#define DSI_LPDATA_REG_OFFSET              0x000000FCU           /*!< LP data register offset */
#define DSI_HSCTL_REG_OFFSET               0x00000100U           /*!< HS control register offset */
#define DSI_HSDATA_REG_OFFSET              0x00000104U           /*!< HS data register offset */
#define DSI_FIFOSTAT_REG_OFFSET            0x00000108U           /*!< FIFO status register offset */
#define DSI_INTSTAT1_REG_OFFSET            0x0000010CU           /*!< interrupt status register1 offset */
#define DSI_WCTL_REG_OFFSET                0x00000200U           /*!< wrapper control register offset */
#define DSI_WINTEN_REG_OFFSET              0x00000204U           /*!< wrapper interrupt enable register offset */
#define DSI_WINTSTAT_REG_OFFSET            0x00000208U           /*!< wrapper interrupt and status register offset */
#define DSI_WINTC_REG_OFFSET               0x0000020CU           /*!< wrapper interrupt flag clear register offset */
#define DSI_WRGBDF_REG_OFFSET              0x00000210U           /*!< wrapper RGB data format register offset */
#define DSI_WCMDDS_REG_OFFSET              0x00000220U           /*!< wrapper command mode data source register offset */
#define DSI_WDMARCTL_REG_OFFSET            0x00000224U           /*!< wrapper DMA request control register offset */
#define DSI_WWMS_WCTL_REG_OFFSET           0x00000230U           /*!< wrapper WMS write control register offset */
#define DSI_WWMS_INTMSK_REG_OFFSET         0x00000234U           /*!< wrapper WMS interrupt mask register offset */
#define DSI_WWMS_HEAD_REG_OFFSET           0x00000238U           /*!< wrapper WMS header message register offset */
#define DSI_WWMS_SIZE_REG_OFFSET           0x0000023CU           /*!< wrapper WMS size control register offset */
#define DSI_WWMS_STAT0_REG_OFFSET          0x00000240U           /*!< wrapper WMS status register 0 offset */
#define DSI_WWMS_STAT1_REG_OFFSET          0x00000244U           /*!< wrapper WMS status register 1 offset */
#define DSI_INTEN1_REG_OFFSET              0x00000250U           /*!< interrupt enable register 1 offset */

/* device ready */
#define DSI_DEVICE_NOT_READY               0x00000000U           /*!< not ready */
#define DSI_DEVICE_READY                   DSI_DEVRDY_DEVRDY     /*!< ready */

/* ULPS state */
#define DSI_ULPS_STATE(regval)             (BITS(1,2) & ((uint32_t)(regval) << 1))
#define DSI_ULPS_NORMAL_OPERATION          DSI_ULPS_STATE(0)     /*!< normal operation */
#define DSI_ULPS_EXIT_MODE                 DSI_ULPS_STATE(1)     /*!< ultra low power EXIT mode */
#define DSI_ULPS_POWER_SAVING_MODE         DSI_ULPS_STATE(2)     /*!< ultra low power [POWER SAVING] mode */

/* display bus possession */
#define DSI_BUS_POSSESSION_STOP            0x00000000U           /*!< stop the display bus possession of the DSI receive */
#define DSI_BUS_POSSESSION_RECEIVE         DSI_DEVRDY_BUS_POSS   /*!< inform that DSI receiver has to be given bus possession for receiving the tearing effect trigger message */

/* data lanes number */
#define DSI_DTLANE_PRG(regval)             (BITS(0,2) & ((uint32_t)(regval)))
#define DSI_DATA_LANE_ONE                  DSI_DTLANE_PRG(1)                     /*!< one data lane */
#define DSI_DATA_LANE_TWO                  DSI_DTLANE_PRG(2)                     /*!< two data lane */

/* virtual channel number for video mode or command mode */
#define DSI_VIRTUAL_CHANNEL_0              0x00000000U                           /*!< virtual channel 0 */
#define DSI_VIRTUAL_CHANNEL_1              0x00000001U                           /*!< virtual channel 1 */
#define DSI_VIRTUAL_CHANNEL_2              0x00000002U                           /*!< virtual channel 2 */
#define DSI_VIRTUAL_CHANNEL_3              0x00000003U                           /*!< virtual channel 3 */

/* supported color format for video mode */
#define DSI_SFMTVM(regval)                 (BITS(7,9) & ((uint32_t)(regval) << 7))
#define DSI_VIDEO_MODE_DISABLE             DSI_SFMTVM(0)                         /*!< Video mode is not supported */
#define DSI_VIDEO_MODE_FMT_RGB565          DSI_SFMTVM(1)                         /*!< RGB565 or 16-bit format */
#define DSI_VIDEO_MODE_FMT_RGB666          DSI_SFMTVM(2)                         /*!< RGB666 or 18-bit format */
#define DSI_VIDEO_MODE_FMT_RGB666LP        DSI_SFMTVM(3)                         /*!< RGB666 loosely packed format */
#define DSI_VIDEO_MODE_FMT_RGB888          DSI_SFMTVM(4)                         /*!< RGB888 or 24-bit format */

typedef enum {
    DSI_VIDEO_MODE                         = 0x0U,                               /*!< Video mode */
    DSI_COMMAND_MODE                       = 0x4U,                               /*!< Command mode */
} dsi_mode_enum;

/* supported data width in command mode */
#define DSI_SDTWCM(regval)                 (BITS(13,15) & ((uint32_t)(regval) << 13))
#define DSI_CMD_MODE_DTW_8BIT              DSI_SDTWCM(0)                         /*!< 8-bit data width */
#define DSI_CMD_MODE_DTW_16BIT             DSI_SDTWCM(1)                         /*!< 16-bit data width */
#define DSI_CMD_MODE_DTW_24BIT             DSI_SDTWCM(2)                         /*!< 24-bit data width */

/* indicates the data transfer type */
#define DSI_TRANSFER_HS                    0x00000000U                           /*!< high-speed transfer */
#define DSI_TRANSFER_LP                    DSI_MAXRPKTCTL_HS_LP                  /*!< low-power transfer */

/* DSI polarity selections */
#define DSI_POLARITY(regval)               (BITS(0,3) & ((uint32_t)(regval)))
#define DSI_VSYNC_POLARITY                 DSI_POLARITY(0)                       /*!< vsync */
#define DSI_HSYNC_POLARITY                 DSI_POLARITY(1)                       /*!< hsync */
#define DSI_SHUTDOWN_POLARITY              DSI_POLARITY(2)                       /*!< shutdown */
#define DSI_COLOR_MODE_POLARITY            DSI_POLARITY(3)                       /*!< color mode */

/* DSI polarity swap selections */
#define DSI_VSYNC_POLARITY_SWAP            DSI_PLSWAP_VSPL                       /*!< vsync polarity swap */
#define DSI_HSYNC_POLARITY_SWAP            DSI_PLSWAP_HSPL                       /*!< hsync polarity swap */
#define DSI_SHUTDOWN_POLARITY_SWAP         DSI_PLSWAP_SDPL                       /*!< shutdown polarity swap */
#define DSI_COLORMODE_POLARITY_SWAP        DSI_PLSWAP_CMPL                       /*!< color mode polarity swap */

/* DSI deskew calibration selections */
#define DSI_DSKCTL_CALIB(regval)           (BITS(0,1) & ((uint32_t)(regval)))
#define DSI_DESKEW_DISABLE                 DSI_DSKCTL_CALIB(0)                   /*!< deskew calibration disable */
#define DSI_INIT_DESKEW_ENABLE             DSI_DSKCTL_CALIB(1)                   /*!< init deskew calibration enable */
#define DSI_PERIODIC_DESKEW_ENABLE         DSI_DSKCTL_CALIB(2)                   /*!< periodic deskew calibration enable */

/* DSI WMS mode selections */
#define DSI_WMS_MODE_HS                    0x00000000U                           /*!< WMS HS mode */
#define DSI_WMS_MODE_LP                    DSI_WWMS_WCTL_WMS_MODE                /*!< WMS LP mode */

/* DSI RGB data format */
#define DSI_WRGBDF_FORMAT(regval)          (BITS(0,2) & ((uint32_t)(regval)))
#define DSI_TLI_DATA_FORMAT_RGB565         DSI_WRGBDF_FORMAT(1)                  /*!< RGB565 format */
#define DSI_TLI_DATA_RGB888                DSI_WRGBDF_FORMAT(0)                  /*!< RGB888 format */
#define DSI_TLI_DATA_RGB888_TO_RGB666      DSI_WRGBDF_FORMAT(2)                  /*!< RGB888 to RGB666 format */
#define DSI_TLI_DATA_RGB565_TO_RGB666      DSI_WRGBDF_FORMAT(3)                  /*!< RGB565 to RGB666 format */

/* DSI tearing effect source */
#define DSI_TE_EXTERNAL_PIN                DSI_WCTL_TESRC                        /*!< external TE source */
#define DSI_TE_DSI_LINK                    0x00000000U                           /*!< DSI packet TE source */

/* DSI TLI DMA mode */
#define DSI_TLI_DMA_MODE_DISABLE           0x00000000U                           /*!< DMA mode disable, DMA used by TLI */
#define DSI_TLI_DMA_MODE_ENABLE            DSI_WCTL_TLIDMA                       /*!< DMA mode enable, DMA used by DSI */

/* DSI TE pin polarity*/
#define DSI_TE_POL_RISING_EDGE             0x00000000U                           /*!< TE pin polarity is rising edge */
#define DSI_TE_POL_FALLING_EDGE            DSI_WCTL_TEPOL                        /*!< TE pin polarity is falling edge */

/* DSI wrapper command mode data source */
#define DSI_HS_DATASRC_HSDATA              0x00000000U                           /*!< From DSI_HSDATA(0x104) */
#define DSI_HS_DATASRC_TLI_DMA             DSI_WCMDDS_HSCMDDS                    /*!< From TLI DMA */
#define DSI_LP_DATASRC_LPDATA              0x00000000U                           /*!< From DSI_LPDATA(0xFC) */
#define DSI_LP_DATASRC_TLI_DMA             DSI_WCMDDS_LPCMDDS                    /*!< From TLI DMA */

/* DSI error auto recovery */
#define DSI_ERR_AUTO_REC_ECC_MUL           DSI_EARCTL_ECC_MUL_ERR_CLR            /*!< ECC multiple error recovery */
#define DSI_ERR_AUTO_REC_INVLD_DT          DSI_EARCTL_INVLD_DT_CLR               /*!< invalid data error recovery */
#define DSI_ERR_AUTO_REC_HI_CONT           DSI_EARCTL_HI_CONT_CLR                /*!< high continuity error recovery */
#define DSI_ERR_AUTO_REC_LO_CONT           DSI_EARCTL_LO_CONT_CLR                /*!< low continuity error recovery */
#define DSI_ERR_AUTO_REC_HS_RX_TO          DSI_EARCTL_HS_RX_TO_CLR               /*!< HS RX timeout error recovery */
#define DSI_ERR_AUTO_REC_LP_RX_TO          DSI_EARCTL_LP_RX_TO_CLR               /*!< LP RX timeout error recovery */

/* frequency mode */
#define DDR_FREQ_LT_200MHZ                 0x00000000U                           /*!< DDR freq < 200MHz */
#define DDR_FREQ_GT_EQ_200MHZ              DSI_FMCTL_FREQMOD                     /*!< DDR freq >= 200MHz */

/* FIFO status */
#define DSI_DATA_FIFO_STAT_HS_FULL         DSI_FIFOSTAT_HSDTFIFOF                /*!< HS Generic/DCS data FIFO full */
#define DSI_DATA_FIFO_STAT_HS_HALF_EMPTY   DSI_FIFOSTAT_HSDTFIFOHE               /*!< HS Generic/DCS data FIFO half empty */
#define DSI_DATA_FIFO_STAT_HS_EMPTY        DSI_FIFOSTAT_HSDTFIFOE                /*!< HS Generic/DCS data FIFO empty */
#define DSI_DATA_FIFO_STAT_LP_FULL         DSI_FIFOSTAT_LPDTFIFOF                /*!< LP Generic/DCS data FIFO full */
#define DSI_DATA_FIFO_STAT_LP_HALF_EMPTY   DSI_FIFOSTAT_LPDTFIFOHE               /*!< LP Generic/DCS data FIFO half empty */
#define DSI_DATA_FIFO_STAT_LP_EMPTY        DSI_FIFOSTAT_LPDTFIFOE                /*!< LP Generic/DCS data FIFO empty */
#define DSI_CTRL_FIFO_STAT_HS_FULL         DSI_FIFOSTAT_HSCTLFIFOF               /*!< HS Generic/DCS control FIFO full */
#define DSI_CTRL_FIFO_STAT_HS_HALF_EMPTY   DSI_FIFOSTAT_HSCTLFIFOHE              /*!< HS Generic/DCS control FIFO half empty */
#define DSI_CTRL_FIFO_STAT_HS_EMPTY        DSI_FIFOSTAT_HSCTLFIFOE               /*!< HS Generic/DCS control FIFO empty */
#define DSI_CTRL_FIFO_STAT_LP_FULL         DSI_FIFOSTAT_LPCTLFIFOF               /*!< LP Generic/DCS control FIFO full */
#define DSI_CTRL_FIFO_STAT_LP_HALF_EMPTY   DSI_FIFOSTAT_LPCTLFIFOHE              /*!< LP Generic/DCS control FIFO half empty */
#define DSI_CTRL_FIFO_STAT_LP_EMPTY        DSI_FIFOSTAT_LPCTLFIFOE               /*!< LP Generic/DCS control FIFO empty */

/* wrapper hardware auto refresh cmd FIFO buffer enable */
#define DSI_AUTO_REFRESH_BUF_DISABLE       0x00000000U                           /*!< No auto-refresh of cmd FIFO */
#define DSI_AUTO_REFRESH_BUF_ENABLE        DSI_WCTL_ARBUF                        /*!< Auto-refresh cmd FIFO */

/* wrapper automatic refresh mode */
#define DSI_AUTO_REFRESH_MODE_DISABLE      0x00000000U                           /*!< Automatic refresh mode disable */
#define DSI_AUTO_REFRESH_MODE_ENABLE       DSI_WCTL_ARM                          /*!< Automatic refresh mode enable */

/* wrapper DMA request source select */
#define DSI_REQDMASRC(regval)              (BITS(4,6) & ((uint32_t)(regval) << 4))
#define DSI_DMA_REQ_SRC_HSDTFIFOHE         DSI_REQDMASRC(0)                      /*!< DMA request source select HSDTFIFOHE */
#define DSI_DMA_REQ_SRC_HSDTFIFOE          DSI_REQDMASRC(1)                      /*!< DMA request source select HSDTFIFOE */
#define DSI_DMA_REQ_SRC_HSDTFIFOF_INV      DSI_REQDMASRC(2)                      /*!< DMA request source select ~HSDTFIFOF */
#define DSI_DMA_REQ_SRC_LPDTFIFOHE         DSI_REQDMASRC(4)                      /*!< DMA request source select LPDTFIFOHE */
#define DSI_DMA_REQ_SRC_LPDTFIFOE          DSI_REQDMASRC(5)                      /*!< DMA request source select LPDTFIFOE */
#define DSI_DMA_REQ_SRC_LPDTFIFOF_INV      DSI_REQDMASRC(6)                      /*!< DMA request source select ~LPDTFIFOF */

/* video mode format */
#define DSI_VMFMT_VMFMT_SEL(regval)        (BITS(0,1) & ((uint32_t)(regval)))
#define DSI_VIDEO_MODE_FORMAT_NONE         DSI_VMFMT_VMFMT_SEL(0)                /*!< none video mode format */
#define DSI_NON_BURST_MODE_SYNC_PULSE      DSI_VMFMT_VMFMT_SEL(1)                /*!< non burst mode with sync pulse */
#define DSI_NON_BURST_MODE_SYNC_EVENTS     DSI_VMFMT_VMFMT_SEL(2)                /*!< non burst mode with sync events */
#define DSI_BURST_MODE                     DSI_VMFMT_VMFMT_SEL(3)                /*!< burst mode */

/* structure definitions */
/* DSI DPHY parameter configuration structure */
typedef struct {
    uint8_t hs_prepare;                /*!< HS preparation time (THS-PREPARE) */
    uint8_t hs_zero;                   /*!< HS drive zero time (THS-ZERO) */
    uint8_t hs_trail;                  /*!< HS trail time (THS-TRAIL) */
    uint8_t hs_exit;                   /*!< HS exit time (THS-EXIT) */
    uint8_t clk_prepare;               /*!< CLK preparation time (TCLK-PREPARE) */
    uint8_t clk_zero;                  /*!< CLK drive zero time (TCLK-ZERO) */
    uint8_t clk_trail;                 /*!< CLK trail time (TCLK-TRAIL) */
    uint8_t clk_exit;                  /*!< CLK exit time (TCLK-EXIT) */
} dsi_dphy_parameter_struct;

/* DSI timing parameters structure */
typedef struct {
    uint32_t hs_to_count;              /*!< high-speed transmission timeout counter */
    uint32_t lp_rx_to_count;           /*!< low-power reception timeout counter */
    uint8_t ta_to_count;               /*!< turn-around timeout counter */
    uint8_t dphy_pll_count;            /*!< DPhy PLL counter */
    uint16_t device_reset_timer;       /*!< device reset timer value */
    uint16_t lp_bcm_count;             /*!< low-power byte clock mode counter */
    uint16_t hs_switch_count;          /*!< HS to LP and LP to HS switch count */
    uint16_t clk_hs_lp_switch_count;   /*!< clock lane HS to LP switch count */
    uint16_t clk_lp_hs_switch_count;   /*!< clock lane LP to HS switch count */
    uint16_t init_count;               /*!< DPHY initialization counter */
} dsi_timing_parameter_struct;

/* DSI initialization structure */
typedef struct {
    uint32_t lane_count;               /*!< number of active data lanes */
    dsi_mode_enum mode_type;           /*!< mode type, video mode or command mode */
    uint32_t video_mode_format;        /*!< video mode format for video mode */
    uint32_t color_format;             /*!< color format for video mode */
    uint32_t data_width;               /*!< data width for command mode */
    uint32_t cmd_size;                 /*!< DSI command size */
    uint32_t virtual_channel;          /*!< virtual channel ID */
    uint32_t polarity;                 /*!< polarity configuration */
} dsi_init_parameter_struct;

/* DSI timing parameters structure */
typedef struct {
    uint16_t hsa_count;                /*!< horizontal sync active count */
    uint16_t hbp_count;                /*!< horizontal back porch count */
    uint16_t hfp_count;                /*!< horizontal front porch count */
    uint16_t hac_count;                /*!< horizontal active count */
    uint16_t vsa_count;                /*!< vertical sync active count */
    uint16_t vbp_count;                /*!< vertical back porch count */
    uint16_t vfp_count;                /*!< vertical front porch count */
} dsi_hv_count_struct;

/* DSI WMS parameters structure */
typedef struct {
    uint32_t wms_mode;                 /*!< WMS mode */
    uint8_t first_packet_header;       /*!< first split packet head */
    uint8_t second_packet_header;      /*!< secondary split packet head */
    uint8_t dcs_command;               /*!< long packet DCS command */
    uint8_t packet_length;             /*!< packet length in words */
    uint32_t total_length;             /*!< total number of words to be transferred */
} dsi_wms_parameter_struct;

/* enumerations definitions */
/* DSI command list definitions */
typedef enum {
    DSI_CMD_SHUT_DOWN             = DSI_DPICTL_SD,       /*!< DPI shutdown (0x01) command */
    DSI_CMD_TURN_ON               = DSI_DPICTL_TON,      /*!< DPI turn on (0x02) command */
    DSI_CMD_COLOR_MODE_ON         = DSI_DPICTL_CMON,     /*!< color mode on (0x04) command */
    DSI_CMD_COLOR_MODE_OFF        = DSI_DPICTL_CMOFF     /*!< color mode off (0x08) command */
} dsi_command_enum;

/* DSI flags */
typedef enum {
    /* flags in INTSTAT0 register */
    DSI_FLAG_RXSOTE     = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 0U),        /*!< Rx Sot Error flag */
    DSI_FLAG_RXSOTSYNCE = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 1U),        /*!< Rx Sot Sync Error flag */
    DSI_FLAG_RXEOTSYNCE = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 2U),        /*!< Rx Eot sync Error flag */
    DSI_FLAG_RXESCMEE   = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 3U),        /*!< Rx Escape Mode Entry Error flag */
    DSI_FLAG_RXLPTXSYNCE = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 4U),       /*!< Rx LP tx sync error flag */
    DSI_FLAG_RXPTOE     = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 5U),        /*!< Rx Peripheral timeout Error flag */
    DSI_FLAG_RXFCTLE    = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 6U),        /*!< Rx False Control Error flag */
    DSI_FLAG_RXECCSE    = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 7U),        /*!< Rx ECC single bit error flag */
    DSI_FLAG_RXECCME    = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 8U),        /*!< Rx ECC multi-bit error flag */
    DSI_FLAG_RXCHKE     = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 9U),        /*!< Rx checksum error flag */
    DSI_FLAG_RXDSIDTNR   = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 10U),      /*!< Rx DSI data type not recognized flag */
    DSI_FLAG_RXDSIVCIDINV = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 11U),     /*!< Rx DSI virtual channel ID invalid flag */
    DSI_FLAG_TXFCTLE    = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 12U),       /*!< Tx False Control Error flag */
    DSI_FLAG_TXECCSE    = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 13U),       /*!< Tx ECC single bit error flag */
    DSI_FLAG_TXECCME    = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 14U),       /*!< Tx ECC multi-bit error flag */
    DSI_FLAG_TXCHKE     = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 15U),       /*!< Tx checksum(CRC) error flag */
    DSI_FLAG_TXDSIDTNR  = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 16U),       /*!< Tx DSI data type not recognized flag */
    DSI_FLAG_TXDSIVCIDINV = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 17U),     /*!< Tx DSI virtual channel ID invalid flag */
    DSI_FLAG_HCONT      = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 18U),       /*!< high contention flag */
    DSI_FLAG_LCONT      = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 19U),       /*!< low contention flag */
    DSI_FLAG_FIFOE      = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 20U),       /*!< FIFO empty flag */
    DSI_FLAG_HSTXTO     = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 21U),       /*!< HS Tx timeout flag */
    DSI_FLAG_LPRXTO     = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 22U),       /*!< LP Rx timeout flag */
    DSI_FLAG_TAACKTO    = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 23U),       /*!< turn around ack timeout flag */
    DSI_FLAG_ACKNE      = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 24U),       /*!< ACK with No error flag */
    DSI_FLAG_RXINVTXCE  = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 25U),       /*!< Rx Invalid transmission count error flag */
    DSI_FLAG_RXDSIPV    = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 26U),       /*!< Rx DSI protocol violation flag */
    DSI_FLAG_SPKTCMDS   = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 27U),       /*!< special packet command sent flag */
    DSI_FLAG_INIT_DONE  = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 28U),       /*!< DSI initialization is done flag */
    DSI_FLAG_RXCONTDET  = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 29U),       /*!< Rx Contention Detected flag */
    DSI_FLAG_DPILTO     = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 30U),       /*!< dpi line timeout flag */
    DSI_FLAG_DPIPE      = DSI_REGIDX_BIT(DSI_INTSTAT0_REG_OFFSET, 31U),       /*!< dpi program error flag */
    /* flags in INTSTAT1 register */
    DSI_FLAG_HSDTFIFOF  = DSI_REGIDX_BIT(DSI_INTSTAT1_REG_OFFSET, 0U),        /*!< HS Generic/DCS data FIFO full flag */
    DSI_FLAG_LPDTFIFOF  = DSI_REGIDX_BIT(DSI_INTSTAT1_REG_OFFSET, 1U),        /*!< LP Generic/DCS data FIFO full flag */
    DSI_FLAG_LPCTLFIFOF = DSI_REGIDX_BIT(DSI_INTSTAT1_REG_OFFSET, 2U),        /*!< LP Generic/DCS control FIFO full flag */
    DSI_FLAG_HSCTLFIFOF = DSI_REGIDX_BIT(DSI_INTSTAT1_REG_OFFSET, 3U),        /*!< HS Generic/DCS control FIFO full flag */
    DSI_FLAG_RDDTA      = DSI_REGIDX_BIT(DSI_INTSTAT1_REG_OFFSET, 4U),        /*!< LP Generic/DCS read data available flag */
    DSI_FLAG_TETG       = DSI_REGIDX_BIT(DSI_INTSTAT1_REG_OFFSET, 5U),        /*!< tearing effect(TE) trigger message received flag */
} dsi_flag_enum;

/* DSI interrupt flags */
typedef enum {
    /* interrupt flags in INTSTAT0 register */
    DSI_INT_FLAG_RXSOTE         = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 0U, DSI_INTSTAT0_REG_OFFSET, 0U),       /*!< Rx Sot Error interrupt flag */
    DSI_INT_FLAG_RXSOTSYNCE     = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 1U, DSI_INTSTAT0_REG_OFFSET, 1U),       /*!< Rx Sot Sync Error interrupt flag */
    DSI_INT_FLAG_RXEOTSYNCE     = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 2U, DSI_INTSTAT0_REG_OFFSET, 2U),       /*!< Rx Eot sync Error interrupt flag */
    DSI_INT_FLAG_RXESCMEE       = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 3U, DSI_INTSTAT0_REG_OFFSET, 3U),       /*!< Rx Escape Mode Entry Error interrupt flag */
    DSI_INT_FLAG_RXLPTXSYNCE    = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 4U, DSI_INTSTAT0_REG_OFFSET, 4U),       /*!< Rx LP tx sync error interrupt flag */
    DSI_INT_FLAG_RXPTOE         = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 5U, DSI_INTSTAT0_REG_OFFSET, 5U),       /*!< Rx Peripheral timeout Error interrupt flag */
    DSI_INT_FLAG_RXFCTLE        = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 6U, DSI_INTSTAT0_REG_OFFSET, 6U),       /*!< RxFalse Control Error interrupt flag */
    DSI_INT_FLAG_RXECCSE        = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 7U, DSI_INTSTAT0_REG_OFFSET, 7U),       /*!< Rx ECC single bit error interrupt flag */
    DSI_INT_FLAG_RXECCME        = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 8U, DSI_INTSTAT0_REG_OFFSET, 8U),       /*!< Rx ECC multi-bit error interrupt flag */
    DSI_INT_FLAG_RXCHKE         = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 9U, DSI_INTSTAT0_REG_OFFSET, 9U),       /*!< Rx checksum error interrupt flag */
    DSI_INT_FLAG_RXDSIDTNR      = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 10U, DSI_INTSTAT0_REG_OFFSET, 10U),     /*!< Rx DSI data type not recognized interrupt flag */
    DSI_INT_FLAG_RXDSIVCIDINV   = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 11U, DSI_INTSTAT0_REG_OFFSET, 11U),     /*!< Rx DSI virtual channel ID invalid interrupt flag */
    DSI_INT_FLAG_TXFCTLE        = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 12U, DSI_INTSTAT0_REG_OFFSET, 12U),     /*!< Tx False Control Error interrupt flag */
    DSI_INT_FLAG_TXECCSE        = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 13U, DSI_INTSTAT0_REG_OFFSET, 13U),     /*!< Tx ECC single bit error interrupt flag */
    DSI_INT_FLAG_TXECCME        = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 14U, DSI_INTSTAT0_REG_OFFSET, 14U),     /*!< Tx ECC multi-bit error interrupt flag */
    DSI_INT_FLAG_TXCHKE         = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 15U, DSI_INTSTAT0_REG_OFFSET, 15U),     /*!< Tx checksum(CRC) error interrupt flag */
    DSI_INT_FLAG_TXDSIDTNR      = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 16U, DSI_INTSTAT0_REG_OFFSET, 16U),     /*!< Tx DSI data type not recognized interrupt flag */
    DSI_INT_FLAG_TXDSIVCIDINV   = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 17U, DSI_INTSTAT0_REG_OFFSET, 17U),     /*!< Tx DSI virtual channel ID invalid interrupt flag */
    DSI_INT_FLAG_HCONT          = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 18U, DSI_INTSTAT0_REG_OFFSET, 18U),     /*!< high contention interrupt flag */
    DSI_INT_FLAG_LCONT          = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 19U, DSI_INTSTAT0_REG_OFFSET, 19U),     /*!< low contention interrupt flag */
    DSI_INT_FLAG_FIFOE          = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 20U, DSI_INTSTAT0_REG_OFFSET, 20U),     /*!< FIFO empty interrupt flag */
    DSI_INT_FLAG_HSTXTO         = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 21U, DSI_INTSTAT0_REG_OFFSET, 21U),     /*!< HS Tx timeout interrupt flag */
    DSI_INT_FLAG_LPRXTO         = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 22U, DSI_INTSTAT0_REG_OFFSET, 22U),     /*!< LP Rx timeout interrupt flag */
    DSI_INT_FLAG_TAACKTO        = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 23U, DSI_INTSTAT0_REG_OFFSET, 23U),     /*!< turn around ack timeout interrupt flag */
    DSI_INT_FLAG_ACKNE          = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 24U, DSI_INTSTAT0_REG_OFFSET, 24U),     /*!< ACK with No error interrupt flag */
    DSI_INT_FLAG_RXINVTXCE      = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 25U, DSI_INTSTAT0_REG_OFFSET, 25U),     /*!< Rx Invalid transmission count error interrupt flag */
    DSI_INT_FLAG_RXDSIPV        = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 26U, DSI_INTSTAT0_REG_OFFSET, 26U),     /*!< Rx DSI protocol violation interrupt flag */
    DSI_INT_FLAG_SPKTCMDS       = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 27U, DSI_INTSTAT0_REG_OFFSET, 27U),     /*!< special packet command sent interrupt flag */
    DSI_INT_FLAG_INIT_DONE      = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 28U, DSI_INTSTAT0_REG_OFFSET, 28U),     /*!< DSI initialization is done interrupt flag */
    DSI_INT_FLAG_RXCONTDET      = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 29U, DSI_INTSTAT0_REG_OFFSET, 29U),     /*!< Rx Contention Detected interrupt flag */
    DSI_INT_FLAG_DPILTO         = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 30U, DSI_INTSTAT0_REG_OFFSET, 30U),     /*!< DPI line timeout interrupt flag */
    DSI_INT_FLAG_DPIPE          = DSI_REGIDX_BIT2(DSI_INTEN0_REG_OFFSET, 31U, DSI_INTSTAT0_REG_OFFSET, 31U),     /*!< DPI program error interrupt flag */
    /* flags in INTSTAT1 register */
    DSI_INT_FLAG_HSDTFIFOF      = DSI_REGIDX_BIT(DSI_INTSTAT1_REG_OFFSET, 0U),                                   /*!< HS Generic/DCS data FIFO full flag */
    DSI_INT_FLAG_LPDTFIFOF      = DSI_REGIDX_BIT(DSI_INTSTAT1_REG_OFFSET, 1U),                                   /*!< LP Generic/DCS data FIFO full flag */
    DSI_INT_FLAG_LPCTLFIFOF     = DSI_REGIDX_BIT(DSI_INTSTAT1_REG_OFFSET, 2U),                                   /*!< LP Generic/DCS control FIFO full flag */
    DSI_INT_FLAG_HSCTLFIFOF     = DSI_REGIDX_BIT(DSI_INTSTAT1_REG_OFFSET, 3U),                                   /*!< HS Generic/DCS control FIFO full flag */
    DSI_INT_FLAG_RDDTA          = DSI_REGIDX_BIT(DSI_INTSTAT1_REG_OFFSET, 4U),                                   /*!< LP Generic/DCS read data available flag */
    DSI_INT_FLAG_TETG           = DSI_REGIDX_BIT(DSI_INTSTAT1_REG_OFFSET, 5U),                                   /*!< tearing effect(TE) trigger message received flag */
} dsi_int_flag_enum;

/* DSI interrupts */
typedef enum {
    /* interrupts in INTEN0 register */
    DSI_INT_RXSOTE              = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 0U),       /*!< Rx Sot Error interrupt */
    DSI_INT_RXSOTSYNCE          = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 1U),       /*!< Rx Sot Sync Error interrupt */
    DSI_INT_RXEOTSYNCE          = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 2U),       /*!< Rx Eot sync Error interrupt */
    DSI_INT_RXESCMEE            = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 3U),       /*!< Rx Escape Mode Entry Error interrupt */
    DSI_INT_RXLPTXSYNCE         = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 4U),       /*!< Rx LP tx sync error interrupt */
    DSI_INT_RXPTOE              = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 5U),       /*!< Rx Peripheral timeout Error interrupt */
    DSI_INT_RXFCTLE             = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 6U),       /*!< RxFalse Control Error interrupt */
    DSI_INT_RXECCSE             = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 7U),       /*!< Rx ECC single bit error interrupt */
    DSI_INT_RXECCME             = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 8U),       /*!< Rx ECC multi-bit error interrupt */
    DSI_INT_RXCHKE              = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 9U),       /*!< Rx checksum error interrupt */
    DSI_INT_RXDSIDTNR           = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 10U),      /*!< Rx DSI data type not recognized interrupt */
    DSI_INT_RXDSIVCIDINV        = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 11U),      /*!< Rx DSI virtual channel ID invalid interrupt */
    DSI_INT_TXFCTLE             = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 12U),      /*!< Tx False Control Error interrupt */
    DSI_INT_TXECCSE             = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 13U),      /*!< Tx ECC single bit error interrupt */
    DSI_INT_TXECCME             = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 14U),      /*!< Tx ECC multi-bit error interrupt */
    DSI_INT_TXCHKE              = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 15U),      /*!< Tx checksum(CRC) error interrupt */
    DSI_INT_TXDSIDTNR           = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 16U),      /*!< Tx DSI data type not recognized interrupt */
    DSI_INT_TXDSIVCIDINV        = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 17U),      /*!< Tx DSI virtual channel ID invalid interrupt */
    DSI_INT_HCONT               = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 18U),      /*!< high contention interrupt */
    DSI_INT_LCONT               = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 19U),      /*!< low contention interrupt */
    DSI_INT_FIFOE               = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 20U),      /*!< FIFO empty interrupt */
    DSI_INT_HSTXTO              = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 21U),      /*!< HS Tx timeout interrupt */
    DSI_INT_LPRXTO              = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 22U),      /*!< LP Rx timeout interrupt */
    DSI_INT_TAACKTO             = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 23U),      /*!< turn around ack timeout interrupt */
    DSI_INT_ACKNE               = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 24U),      /*!< ACK with No error interrupt */
    DSI_INT_RXINVTXCE           = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 25U),      /*!< Rx Invalid transmission count error interrupt */
    DSI_INT_RXDSIPV             = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 26U),      /*!< Rx DSI protocol violation interrupt */
    DSI_INT_SPKTCMDS            = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 27U),      /*!< special packet command sent interrupt */
    DSI_INT_INIT_DONE           = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 28U),      /*!< DSI initialization is done interrupt */
    DSI_INT_RXCONTDET           = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 29U),      /*!< Rx Contention Detected interrupt */
    DSI_INT_DPILTO              = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 30U),      /*!< DPI line timeout interrupt */
    DSI_INT_DPIPE               = DSI_REGIDX_BIT(DSI_INTEN0_REG_OFFSET, 31U),      /*!< DPI program error interrupt */
    /* interrupts in INTEN1 register */
    DSI_INT_HSDTFIFOF           = DSI_REGIDX_BIT(DSI_INTEN1_REG_OFFSET, 1U),       /*!< HS Generic/DCS data FIFO full interrupt */
    DSI_INT_LPDTFIFOF           = DSI_REGIDX_BIT(DSI_INTEN1_REG_OFFSET, 2U),       /*!< LP Generic/DCS data FIFO full interrupt */
    DSI_INT_LPCTLFIFOF          = DSI_REGIDX_BIT(DSI_INTEN1_REG_OFFSET, 3U),       /*!< LP Generic/DCS control FIFO full interrupt */
    DSI_INT_HSCTLFIFOF          = DSI_REGIDX_BIT(DSI_INTEN1_REG_OFFSET, 4U),       /*!< HS Generic/DCS control FIFO full interrupt */
    DSI_INT_RDDTA               = DSI_REGIDX_BIT(DSI_INTEN1_REG_OFFSET, 5U),       /*!< LP Generic/DCS read data available interrupt */
    DSI_INT_TETG                = DSI_REGIDX_BIT(DSI_INTEN1_REG_OFFSET, 6U),       /*!< tearing effect(TE) trigger message received interrupt */
} dsi_int_enum;

/* DSI wrapper flags */
typedef enum {
    /* flags in WINTSTAT register */
    DSI_FLAG_TE                 = DSI_REGIDX_BIT(DSI_WINTSTAT_REG_OFFSET, 0U),     /*!< tearing effect flag */
    DSI_FLAG_PLL_LOCK           = DSI_REGIDX_BIT(DSI_WINTSTAT_REG_OFFSET, 1U),     /*!< PLL lock flag */
    DSI_FLAG_PLL_UNLOCK         = DSI_REGIDX_BIT(DSI_WINTSTAT_REG_OFFSET, 2U),     /*!< PLL unlock flag */
    DSI_FLAG_PLL_LOCK_STAT      = DSI_REGIDX_BIT(DSI_WINTSTAT_REG_OFFSET, 3U),     /*!< PLL lock status */
    /* flags in WWMS_WCTL register */
    DSI_FLAG_WMS_END            = DSI_REGIDX_BIT(DSI_WWMS_WCTL_REG_OFFSET, 4U)     /*!< write memory split packet end flag */
} dsi_wrapper_flag_enum;

/* DSI wrapper interrupt flags */
typedef enum {
    /* interrupt flags in WINTSTAT register */
    DSI_INT_FLAG_TE             = DSI_REGIDX_BIT(DSI_WINTSTAT_REG_OFFSET, 0U),     /*!< tearing effect flag */
    DSI_INT_FLAG_PLL_LOCK       = DSI_REGIDX_BIT(DSI_WINTSTAT_REG_OFFSET, 1U),     /*!< PLL lock flag */
    DSI_INT_FLAG_PLL_UNLOCK     = DSI_REGIDX_BIT(DSI_WINTSTAT_REG_OFFSET, 2U),     /*!< PLL unlock flag */
    DSI_INT_FLAG_PLL_LOCK_STAT  = DSI_REGIDX_BIT(DSI_WINTSTAT_REG_OFFSET, 3U),     /*!< PLL lock status */
    /* interrupt flags in WWMS_INTMSK register */
    DSI_INT_FLAG_WMS_END        = DSI_REGIDX_BIT(DSI_WWMS_WCTL_REG_OFFSET, 4U)     /*!< write memory split packet end flag */
} dsi_wrapper_int_flag_enum;

/* DSI wrapper interrupt flags */
typedef enum {
    /* interrupt flags in WINTSTAT register */
    DSI_INT_FLAG_TE_CLR         = DSI_REGIDX_BIT(DSI_WINTC_REG_OFFSET, 0U),        /*!< tearing effect flag clear */
    DSI_INT_FLAG_PLL_LOCK_CLR   = DSI_REGIDX_BIT(DSI_WINTC_REG_OFFSET, 1U),        /*!< PLL lock flag clear */
    DSI_INT_FLAG_PLL_UNLOCK_CLR = DSI_REGIDX_BIT(DSI_WINTC_REG_OFFSET, 2U),        /*!< PLL unlock flag clear */
    DSI_INT_FLAG_WMS_END_CLR    = DSI_REGIDX_BIT(DSI_WWMS_WCTL_REG_OFFSET, 4U)     /*!< write memory split packet end flag */
} dsi_wrapper_int_flag_clr_enum;

/* DSI wrapper interrupts */
typedef enum {
    /* interrupts in WINTEN register */
    DSI_INT_TE                  = DSI_REGIDX_BIT(DSI_WINTEN_REG_OFFSET, 0U),       /*!< tearing effect interrupt */
    DSI_INT_PLL_LOCK            = DSI_REGIDX_BIT(DSI_WINTEN_REG_OFFSET, 1U),       /*!< PLL lock interrupt */
    DSI_INT_PLL_UNLOCK          = DSI_REGIDX_BIT(DSI_WINTEN_REG_OFFSET, 2U),       /*!< PLL unlock interrupt */
    DSI_INT_WMS_END_MSK         = DSI_REGIDX_BIT(DSI_WWMS_INTMSK_REG_OFFSET, 4U)   /*!< write memory split packet WMS_END flag interrupt signal mask */
} dsi_wrapper_int_enum;


/* function declarations */
/* DSI deinitialization and initialization functions */
/* deinitialize DSI registers */
void dsi_deinit(void);
/* initialize the DSI_Init structure with the default values */
void dsi_init_struct_para_init(dsi_init_parameter_struct *dsi_init_struct);
/* initialize the DSI host according to the specified parameters in the dsi_init_struct */
void dsi_init(dsi_init_parameter_struct *dsi_init_struct);
/* set the DSI host device ready state */
void dsi_device_ready_set(uint32_t ready_state);
/* set the ULPS state */
void dsi_ulps_mode_set(uint32_t ulps_mode);
/* control display bus possession */
void dsi_display_bus_possession_set(uint32_t bus_pos);
/* configure the DSI low power byte clock */
void dsi_lp_byte_clk_config(uint16_t byte_clk);

/* DSI horizontal and vertical configuration functions */
/* initialize DSI horizontal and vertical count structure with the default values */
void dsi_hv_count_struct_para_init(dsi_hv_count_struct *hv_count);
/* configure the DSI for video mode with complete timing parameters  */
void dsi_hv_count_config(dsi_hv_count_struct *hv_count);
/* configure horizontal sync active count */
void dsi_horizontal_sync_active_count_set(uint16_t count);
/* configure horizontal back porch count */
void dsi_horizontal_back_porch_count_set(uint16_t count);
/* configure horizontal front porch count */
void dsi_horizontal_front_porch_count_set(uint16_t count);
/* configure horizontal active area count */
void dsi_horizontal_active_count_set(uint16_t count);
/* configure vertical sync active count */
void dsi_vertical_sync_active_count_set(uint16_t count);
/* configure vertical back porch count */
void dsi_vertical_back_porch_count_set(uint16_t count);
/* configure vertical front porch count */
void dsi_vertical_front_porch_count_set(uint16_t count);

/* DSI DPI control functions */
/* enable DSI command is packetized for the DPI’s virtual channel */
void dsi_cmd_pkt_dpi_vchannel_enable(dsi_command_enum cmd);
/* disable DSI command is packetized for the DPI’s virtual channel */
void dsi_cmd_pkt_dpi_vchannel_disable(dsi_command_enum cmd);
/* set DPI resolution */
void dsi_dpi_resolution_set(uint16_t hor_resolution, uint16_t ver_resolution);

/* DSI timeout configuration functions */
/* initialize DSI timing parameters structure with default values */
void dsi_timing_struct_para_init(dsi_timing_parameter_struct *timing_struct);
/* configure all timing parameters */
void dsi_timing_config(dsi_timing_parameter_struct *timing_struct);
/* configure high speed transmission timeout counter */
void dsi_hs_tx_timeout_set(uint32_t timeout);
/* configure low power reception timeout counter */
void dsi_lp_rx_timeout_set(uint32_t timeout);
/* configure turn-around timeout */
void dsi_turnaround_timeout_set(uint8_t timeout);
/* configure device reset timer */
void dsi_device_reset_timer_set(uint16_t timer);

/* DSI function program configuration functions */
/* configure DSI initialization counter */
void dsi_init_counter_set(uint16_t counter);
/* set the number of data lanes */
void dsi_data_lanes_number_set(uint32_t number);
/* set virtual channel for video mode */
void dsi_video_mode_virtual_channel_set(uint32_t virtual_channel);
/* set the video mode format */
void dsi_video_mode_format_set(uint8_t video_mode);
/* set virtual channel for command mode */
void dsi_command_mode_virtual_channel_set(uint32_t virtual_channel);
/* set color format for video mode */
void dsi_video_mode_color_format_set(uint32_t color_format);
/* set data width for command mode */
void dsi_command_mode_data_width_set(uint32_t data_width);
/* configure maximum return packet size and data transfer type */
void dsi_max_return_packet_config(uint16_t hplp, uint16_t size);

/* DSI polarity configuration functions */
/* set DSI polarity */
void dsi_polarity_set(uint32_t polarity);
/* swap DSI polarity to active high */
void dsi_polarity_swap_high(uint32_t polarity);
/* swap DSI polarity to active low */
void dsi_polarity_swap_low(uint32_t polarity);

/* DSI EOT and clock configuration functions */
/* enable EOT packet transmission */
void dsi_eot_transmission_enable(void);
/* disable EOT packet transmission */
void dsi_eot_transmission_disable(void);
/* enable clock stopping feature */
void dsi_clock_stopping_enable(void);
/* disable clock stopping feature */
void dsi_clock_stopping_disable(void);
/* enable video BTA  */
void dsi_video_bta_enable(void);
/* disable video BTA */
void dsi_video_bta_disable(void);

/* DSI data lane and clock lane switching functions */
/* configure HS to LP switching counter for clock lane */
void dsi_clk_hs_to_lp_switch_count_set(uint16_t count);
/* configure LP to HS switching counter for clock lane */
void dsi_clk_lp_to_hs_switch_count_set(uint16_t count);
/* configure data lane switching counter */
void dsi_data_lane_switch_count_set(uint16_t count);

/* DSI DPHY configuration functions */
/* initialize DSI DPHY parameter structure with default values */
void dsi_dphy_struct_para_init(dsi_dphy_parameter_struct *dphy_struct);
/* configure the DPHY parameters */
void dsi_dphy_config(dsi_dphy_parameter_struct *dphy_struct);
/* configure the PLL counter value */
void dsi_dphy_pll_counter_set(uint16_t counter_value);
/* set HS preparation time */
void dsi_dphy_hs_prepare_time_set(uint8_t hs_prepare);
/* set HS zero time */
void dsi_dphy_hs_zero_time_set(uint8_t hs_zero);
/* set HS trail time */
void dsi_dphy_hs_trail_time_set(uint8_t hs_trail);
/* set HS exit time */
void dsi_dphy_hs_exit_time_set(uint8_t hs_exit);
/* set clock preparation time */
void dsi_dphy_clk_prepare_time_set(uint8_t clk_prepare);
/* set clock zero time */
void dsi_dphy_clk_zero_time_set(uint8_t clk_zero);
/* set clock trail time */
void dsi_dphy_clk_trail_time_set(uint8_t clk_trail);
/* set clock exit time */
void dsi_dphy_clk_exit_time_set(uint8_t clk_exit);
/* enable control reset to the digital front end */
void dsi_dphy_dfe_reset_enable(void);
/* disable control reset to the digital front end */
void dsi_dphy_dfe_reset_disable(void);
/* configure DPHY trim settings */
void dsi_dphy_trim_config(uint32_t trim0, uint32_t trim1, uint32_t trim2);

/* DSI DPHY trim functions */
/* set specific DPHY trim control 0 parameter */
void dsi_dphy_trim_control0_set(uint32_t value);
/* set specific DPHY trim control 1 parameter */
void dsi_dphy_trim_control1_set(uint32_t value);
/* set specific DPHY trim control 2 parameter */
void dsi_dphy_trim_control2_set(uint32_t value);

/* DSI deskew configuration functions */
/* enable/disable deskew calibration */
void dsi_deskew_calibration_config(uint32_t state);
/* set deskew duration */
void dsi_deskew_duration_set(uint16_t duration);
/* set deskew periodic timer */
void dsi_deskew_timer_set(uint16_t period);
/* get deskew calibration in progress status */
FlagStatus dsi_deskew_in_progress_status_get(void);

/* DSI error recovery and MIPI direction, DPI status functions */
/* enable error auto recovery options */
void dsi_error_auto_recovery_enable(uint32_t recovery_options);
/* disable error auto recovery options */
void dsi_error_auto_recovery_disable(uint32_t recovery_options);
/* get difference in one line time between DPI and DSI */
uint16_t dsi_dpi_difference_get(void);
/* get DPI line time is greater or DSI line time is greater */
uint32_t dsi_dpi_line_time_status_get(void);
/* get MIPI BUS direction */
uint32_t dsi_mipi_bus_direction_get(void);

/* DSI frequency mode functions */
/* set DDR frequency mode */
void dsi_ddr_freq_mode_set(uint32_t freq_mode);
/* set TX data width */
void dsi_tx_data_width_set(uint8_t width);

/* DSI command mode data functions */
/* set LP control parameters */
void dsi_lp_control_set(uint8_t data_type, uint8_t virtual_channel, uint32_t word_count);
/* set HS control parameters */
void dsi_hs_control_set(uint8_t data_type, uint8_t virtual_channel, uint32_t word_count);
/* write data to LP data register */
void dsi_lp_data_write(uint32_t data);
/* read data to LP data register */
uint32_t dsi_lp_data_read(void);
/* write data to HS data register */
void dsi_hs_data_write(uint32_t data);
/* read data to HS data register */
uint32_t dsi_hs_data_read(void);
/* set DCS word count */
void dsi_dcs_word_count_set(uint16_t count);
/* select high-speed or low-power mode for the next transmission packet */
void dsi_transfer_mode_set(uint32_t mode);

/* DSI wrapper configuration functions */
/* set TE polarity */
void dsi_wrapper_te_polarity_set(uint32_t polarity);
/* enable or disable TLI DMA mode */
void dsi_wrapper_tli_dma_mode_config(uint32_t tli_dma);
/* set TE source */
void dsi_wrapper_te_source_set(uint32_t source);
/* enable or disable automatic refresh mode */
void dsi_wrapper_auto_refresh_mode_config(uint32_t auto_ref_mod);
/* refresh command FIFO buffer */
void dsi_wrapper_cmd_fifo_buffer_refresh(void);
/* enable or disable hardware auto refresh cmd buffer */
void dsi_wrapper_auto_refresh_buffer_config(uint32_t auto_ref_buf);
/* set RGB data format */
void dsi_wrapper_rgb_format_set(uint32_t format);

/* DSI wrapper command mode data source functions */
/* select HS command mode data source */
void dsi_wrapper_hs_cmd_data_source_set(uint32_t source);
/* select LP command mode data source */
void dsi_wrapper_lp_cmd_data_source_set(uint32_t source);

/* DSI wrapper DMA control functions */
/* select the DMA request source for command mode data */
void dsi_dma_request_source_select(uint32_t source);

/* DSI wrapper WMS configuration functions */
/* initialize DSI WMS structure with default values */
void dsi_wms_struct_para_init(dsi_wms_parameter_struct *wms_struct);
/* configure the DSI wrapper WMS parameters */
void dsi_wms_config(dsi_wms_parameter_struct *wms_struct);
/* enable WMS function */
void dsi_wrapper_wms_enable(void);
/* set WMS mode */
void dsi_wrapper_wms_mode_set(uint32_t mode);
/* check if WMS end flag is set */
FlagStatus dsi_wrapper_wms_end_flag_get(void);
/* mask or unmask the WMS end interrupt */
void dsi_wrapper_wms_end_interrupt_mask(FlagStatus state);
/* set WMS header messages */
void dsi_wrapper_wms_header_set(uint8_t first_header, uint8_t second_header, uint8_t dcs_cmd);
/* set WMS packet length and total length */
void dsi_wrapper_wms_size_set(uint8_t packet_length, uint32_t total_length);
/* get WMS packet number */
uint16_t dsi_wrapper_wms_packet_number_get(void);
/* get WMS sum count */
uint32_t dsi_wrapper_wms_sum_count_get(void);

/* flag and interrupt functions */
/* check the status of specific FIFO */
FlagStatus dsi_fifo_status_get(uint32_t fifo_stat);
/* get DSI specific flag status */
FlagStatus dsi_flag_get(dsi_flag_enum flag);
/* enable DSI specific interrupt */
void dsi_interrupt_enable(dsi_int_enum interrupt);
/* disable DSI specific interrupt */
void dsi_interrupt_disable(dsi_int_enum interrupt);
/* get DSI specific interrupt flag status */
FlagStatus dsi_interrupt_flag_get(dsi_int_flag_enum int_flag);
/* clear DSI specific interrupt flag */
void dsi_interrupt_flag_clear(dsi_int_flag_enum int_flag);
/* get DSI wrapper specific flag status */
FlagStatus dsi_wrapper_flag_get(dsi_wrapper_flag_enum flag);
/* enable DSI wrapper specific interrupt */
void dsi_wrapper_interrupt_enable(dsi_wrapper_int_enum interrupt);
/* disable DSI wrapper specific interrupt */
void dsi_wrapper_interrupt_disable(dsi_wrapper_int_enum interrupt);
/* get DSI wrapper specific interrupt flag status */
FlagStatus dsi_wrapper_interrupt_flag_get(dsi_wrapper_int_flag_enum int_flag);
/* clear DSI wrapper specific interrupt flag  */
void dsi_wrapper_interrupt_flag_clear(dsi_wrapper_int_flag_clr_enum int_flag);

#endif /* GD32H77X_78X_DSI_H */
