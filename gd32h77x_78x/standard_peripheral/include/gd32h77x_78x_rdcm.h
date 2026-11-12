/*!
    \file    gd32h77x_78x_rdcm.h
    \brief   definitions for the RDCM

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

#ifndef GD32H77X_78X_RDCM_H
#define GD32H77X_78X_RDCM_H

#include "gd32h77x_78x.h"

/* RDCM definitions */
#define RDCM                             RDCM_BASE                                 /*!< RDCM base address */

/* registers definitions */
#define RDCM_CS                          REG32((RDCM) + 0x00000000U)               /*!< control and status register*/
#define RDCM_CTL                         REG32((RDCM) + 0x00000004U)               /*!< control register */
#define RDCM_EXCFG0                      REG32((RDCM) + 0x00000008U)               /*!< excitor configuration register 0 */
#define RDCM_EXCFG1                      REG32((RDCM) + 0x0000000CU)               /*!< excitor configuration register 1 */
#define RDCM_HFCFG0                      REG32((RDCM) + 0x00000010U)               /*!< high pass filter configuration register 0 */
#define RDCM_HFCFG1                      REG32((RDCM) + 0x00000014U)               /*!< high pass filter configuration register 1 */
#define RDCM_RFMCFG0                     REG32((RDCM) + 0x00000018U)               /*!< reference frequency mixer configuration register 0 */
#define RDCM_RFMCFG1                     REG32((RDCM) + 0x0000001CU)               /*!< reference frequency mixer configuration register 1 */
#define RDCM_ZTCFG0                      REG32((RDCM) + 0x00000020U)               /*!< zero crossing threshold configuration register 0 */
#define RDCM_ZTCFG1                      REG32((RDCM) + 0x00000024U)               /*!< zero crossing threshold configuration register 1 */
#define RDCM_MCACFG                      REG32((RDCM) + 0x00000028U)               /*!< mismatch counter average configuration register */
#define RDCM_DEMCFG                      REG32((RDCM) + 0x0000002CU)               /*!< demodulator configuration register */
#define RDCM_CSGCFG0                     REG32((RDCM) + 0x00000030U)               /*!< CIC3 shift and gain configuration register 0 */
#define RDCM_CSGCFG1                     REG32((RDCM) + 0x00000034U)               /*!< CIC3 shift and gain configuration register 1 */
#define RDCM_CICCFG0                     REG32((RDCM) + 0x00000038U)               /*!< CIC3 configuration register 0 */
#define RDCM_CICCFG1                     REG32((RDCM) + 0x0000003CU)               /*!< CIC3 configuration register 1 */
#define RDCM_CDCNT                       REG32((RDCM) + 0x00000040U)               /*!< CIC3 decimation counter register */
#define RDCM_NPMCFG                      REG32((RDCM) + 0x00000044U)               /*!< nonorthogonal phase mismatch configuration register */
#define RDCM_TRKGAINCFG                  REG32((RDCM) + 0x00000048U)               /*!< tracking gain configuration register */
#define RDCM_TRKINTCFG                   REG32((RDCM) + 0x0000004CU)               /*!< tracking integrator gain configuration register */
#define RDCM_TRKCMPCFG                   REG32((RDCM) + 0x00000050U)               /*!< tracking compensation configuration register */
#define RDCM_VSFCFG                      REG32((RDCM) + 0x00000054U)               /*!< velocity smooth filter configuration register */
#define RDCM_HFDATA                      REG32((RDCM) + 0x00000058U)               /*!< high pass filter data register */
#define RDCM_RFMDATA                     REG32((RDCM) + 0x0000005CU)               /*!< reference frequency mixer data register */
#define RDCM_DEMDATA                     REG32((RDCM) + 0x00000060U)               /*!< demodulator data register */
#define RDCM_TRKDATA                     REG32((RDCM) + 0x00000064U)               /*!< tracking data register */
#define RDCM_MONDATA                     REG32((RDCM) + 0x00000068U)               /*!< monitor data register */
#define RDCM_TSCTL                       REG32((RDCM) + 0x0000006CU)               /*!< timestamp control register */
#define RDCM_TSDATA                      REG32((RDCM) + 0x00000070U)               /*!< timestamp data register */
#define RDCM_FIFOCS                      REG32((RDCM) + 0x00000074U)               /*!< FIFO control and status register */
#define RDCM_FIFODATA                    REG32((RDCM) + 0x00000078U)               /*!< FIFO data register */
#define RDCM_ETHCFG0                     REG32((RDCM) + 0x0000007CU)               /*!< envelope threshold configuration register 0 */
#define RDCM_ETHCFG1                     REG32((RDCM) + 0x00000080U)               /*!< envelope threshold configuration register 1 */
#define RDCM_MTHCFG                      REG32((RDCM) + 0x00000084U)               /*!< monitor signal threshold configuration register */
#define RDCM_TRKERRTHCFG                 REG32((RDCM) + 0x00000088U)               /*!< tracking error signal threshold configuration register */
#define RDCM_THCNT                       REG32((RDCM) + 0x0000008CU)               /*!< RDCM tracking threshold match counter register */
#define RDCM_SIMDI                       REG32((RDCM) + 0x00000100U)               /*!< RDCM software data input register */
#define RDCM_DISWSEL                     REG32((RDCM) + 0x00000104U)               /*!< RDCM data input software selection register */
#define RDCM_PWMCFG                      REG32((RDCM) + 0x00000108U)               /*!< RDCM PWM configuration register */
#define RDCM_POSDATA                     REG32((RDCM) + 0x0000010CU)               /*!< RDCM position data register */
#define RDCM_VELDATA                     REG32((RDCM) + 0x00000110U)               /*!< RDCM velocity data register */

/* bits definitions */
/* RDCM_CS */
#define RDCM_CS_RDCMEN                   BIT(0)                                    /*!< RDCM module enable */
#define RDCM_CS_CALSEL                   BITS(1,2)                                 /*!< RDCM main chain calculation event selection */
#define RDCM_CS_GATEVSEL                 BITS(3,4)                                 /*!< result valid trigger gate selection */
#define RDCM_CS_TRKERRTHMS               BITS(5,6)                                 /*!< tracking error signal threshold mode selection */
#define RDCM_CS_TRKERRTHMIE              BIT(7)                                    /*!< track error signal threshold match interrupt enable */
#define RDCM_CS_MTHIE                    BIT(8)                                    /*!< monitor signal threshold match interrupt enable */
#define RDCM_CS_QETHMIE                  BIT(9)                                    /*!< Q channel envelope signal threshold match interrupt enable */
#define RDCM_CS_IETHMIE                  BIT(10)                                   /*!< I channel envelope signal threshold match interrupt enable */
#define RDCM_CS_QZCDIE                   BIT(11)                                   /*!< Q channel zero crossing detection valid interrupt enable */
#define RDCM_CS_IZCDIE                   BIT(12)                                   /*!< I channel zero crossing detection valid interrupt enable */
#define RDCM_CS_TSCAPIE                  BIT(13)                                   /*!< timestamp counter capture valid interrupt enable */
#define RDCM_CS_OVIE                     BIT(14)                                   /*!< RDC-DMA transfer overflow interrupt enable */
#define RDCM_CS_RESDIE                   BIT(15)                                   /*!< result valid (result update or result FIFO level) interrupt enable */
#define RDCM_CS_MTHMS                    BITS(17,18)                               /*!< monitor signal mode selection */
#define RDCM_CS_QETHMS                   BITS(19,20)                               /*!< Q channel envelope signal threshold mode selection */
#define RDCM_CS_IETHMS                   BITS(21,22)                               /*!< I channel envelope signal threshold mode selection */
#define RDCM_CS_TRKERRTHMIF              BIT(23)                                   /*!< track error signal threshold match interrupt flag */
#define RDCM_CS_MTHMIF                   BIT(24)                                   /*!< monitor signal threshold match interrupt flag */
#define RDCM_CS_QETHMIF                  BIT(25)                                   /*!< Q channel envelope signal threshold match interrupt flag */
#define RDCM_CS_IETHMIF                  BIT(26)                                   /*!< I channel envelope signal threshold match interrupt flag */
#define RDCM_CS_QZCDIF                   BIT(27)                                   /*!< Q channel zero crossing detection interrupt flag */
#define RDCM_CS_IZCDIF                   BIT(28)                                   /*!< I channel zero crossing detection interrupt flag */
#define RDCM_CS_TSCAPIF                  BIT(29)                                   /*!< timestamp counter capture interrupt flag */
#define RDCM_CS_OVIF                     BIT(30)                                   /*!< DMA transfer data register overflow interrupt flag */
#define RDCM_CS_RESDIF                   BIT(31)                                   /*!< result data interrupt flag */

/* RDCM_CTL */
#define RDCM_CTL_IRFMEN                  BIT(0)                                    /*!< I channel reference frequency mixer enable */
#define RDCM_CTL_IDEMEN                  BIT(1)                                    /*!< I channel demodulator enable */
#define RDCM_CTL_IDEMRST                 BIT(2)                                    /*!< I channel demodulator reset */
#define RDCM_CTL_IZCDMS                  BITS(3,4)                                 /*!< zero crossing detection mode selection */
#define RDCM_CTL_CALETM                  BITS(5,6)                                 /*!< external trigger mode for RDC main chain calculation (HF filter, demodulator, tracking loop) */
#define RDCM_CTL_TSCAPETM                BITS(7,8)                                 /*!< external trigger mode for timestamp counter capture */
#define RDCM_CTL_TRKERRTHMEN             BIT(9)                                    /*!< track error signal threshold match function enable */
#define RDCM_CTL_MTHMEN                  BIT(10)                                   /*!< monitor signal threshold match function enable */
#define RDCM_CTL_QETHMEN                 BIT(11)                                   /*!< Q channel envelope signal threshold match function enable */
#define RDCM_CTL_IETHMEN                 BIT(12)                                   /*!< I channel envelope signal threshold match function enable */
#define RDCM_CTL_TSCAPEN                 BIT(13)                                   /*!< timestamp counter capture function enable */
#define RDCM_CTL_FIFOEN                  BIT(14)                                   /*!< result FIFO enable */
#define RDCM_CTL_OVDEN                   BIT(15)                                   /*!< RDC-DMA transfer overflow function enable */
#define RDCM_CTL_QRFMEN                  BIT(16)                                   /*!< Q channel reference frequency mixer enable */
#define RDCM_CTL_QDEMEN                  BIT(17)                                   /*!< Q channel demodulator enable */
#define RDCM_CTL_QDEMRST                 BIT(18)                                   /*!< Q channel demodulator reset */
#define RDCM_CTL_QZCDMS                  BITS(19,20)                               /*!< zero crossing detection mode selection in Q channel */
#define RDCM_CTL_NCOETM                  BITS(22,23)                               /*!< external trigger mode for all NCOs(excitor, I/Q reference frequency mixer) calculation */
#define RDCM_CTL_NCORST                  BIT(24)                                   /*!< reset the phase of all NCOs (excitor and I/Q reference frequency mixer) to the initial setting phase */
#define RDCM_CTL_EXCEN                   BIT(25)                                   /*!< sinusoidal exciter enable */
#define RDCM_CTL_TRKEN                   BIT(26)                                   /*!< track loop enable */
#define RDCM_CTL_RESDSEL                 BITS(27,29)                               /*!< result data register selection */
#define RDCM_CTL_DDSM                    BIT(30)                                   /*!< DMA disable mode */
#define RDCM_CTL_DMAEN                   BIT(31)                                   /*!< DMA request enable */

/* RDCM_EXCFG0 */
#define RDCM_EXCFG0_FEXC                 BITS(0,13)                                /*!< frequency of the exciter */
#define RDCM_EXCFG0_PEXC                 BITS(16,29)                               /*!< initial phase of the exciter */

/* RDCM_EXCFG1 */
#define RDCM_EXCFG1_AEXC                 BITS(0,12)                                /*!< amplitude of the exciter */
#define RDCM_EXCFG1_NCODIV               BITS(16,29)                               /*!< NCO(excitor,I/Q reference frequency mixer) calculation frequency division factor */

/* RDCM_HFCFG0 */
#define RDCM_HFCFG0_IOFFSET              BITS(0,14)                                /*!< I channel offset factor */
#define RDCM_HFCFG0_IHFM                 BITS(16,18)                               /*!< I channel high-pass (offset compensation) filter mode */

/* RDCM_HFCFG1 */
#define RDCM_HFCFG1_QOFFSET              BITS(0,14)                                /*!< Q channel offset factor */
#define RDCM_HFCFG1_QHFM                 BITS(16,18)                               /*!< Q channel high-pass (offset compensation) filter mode */

/* RDCM_RFMCFG0 */
#define RDCM_RFMCFG0_IPHASE              BITS(0,13)                                /*!< initial phase of the I channel reference frequency mixer */
#define RDCM_RFMCFG0_IFRE                BITS(16,29)                               /*!< the frequency control word of the I channel reference frequency mixer */

/* RDCM_RFMCFG1 */
#define RDCM_RFMCFG1_QPHASE              BITS(0,13)                                /*!< initial phase of the Q channel reference frequency mixer */
#define RDCM_RFMCFG1_QFRE                BITS(16,29)                               /*!< the frequency control word of the Q channel reference frequency mixer */

/* RDCM_ZTCFG0 */
#define RDCM_ZTCFG0_IZCTH                BITS(0,13)                                /*!< the threshold of mismatch counter value in zero crossing detection of I channel */
#define RDCM_ZTCFG0_QZCTH                BITS(16,29)                               /*!< the threshold of mismatch counter value in zero crossing detection of Q channel */

/* RDCM_ZTCFG1 */
#define RDCM_ZTCFG1_IZTVAR               BITS(0,13)                                /*!< the threshold variation range of mismatch counter value in zero crossing detection of I channel */
#define RDCM_ZTCFG1_QZTVAR               BITS(16,29)                               /*!< the threshold variation range of mismatch counter value in zero crossing detection of Q channel */

/* RDCM_MCACFG */
#define RDCM_MCACFG_IAVEM                BITS(0,3)                                 /*!< the mismatch counter average factor of I channel */
#define RDCM_MCACFG_QAVEM                BITS(16,19)                               /*!< the mismatch counter average factor of Q channel */

/* RDCM_DEMCFG */
#define RDCM_DEMCFG_IFIR0EN              BIT(0)                                    /*!< I channel FIR0 filter enable */
#define RDCM_DEMCFG_IFIR1EN              BIT(1)                                    /*!< I channel FIR1 filter enable */
#define RDCM_DEMCFG_IFIR1DEC             BIT(2)                                    /*!< I channel FIR1 filter decimation rate */
#define RDCM_DEMCFG_ICIC3EN              BIT(3)                                    /*!< I channel CIC3 filter enable */
#define RDCM_DEMCFG_QFIR0EN              BIT(16)                                   /*!< Q channel FIR0 filter enable */
#define RDCM_DEMCFG_QFIR1EN              BIT(17)                                   /*!< Q channel FIR1 filter enable */
#define RDCM_DEMCFG_QFIR1DEC             BIT(18)                                   /*!< Q channel FIR1 filter decimation rate */
#define RDCM_DEMCFG_QCIC3EN              BIT(19)                                   /*!< Q channel CIC3 filter enable */

/* RDCM_CSGCFG0 */
#define RDCM_CSGCFG0_IGAIN               BITS(0,12)                                /*!< I channel gain factor */
#define RDCM_CSGCFG0_ICICSHIFT           BITS(16,21)                               /*!< I channel output shift */

/* RDCM_CSGCFG1 */
#define RDCM_CSGCFG1_QGAIN               BITS(0,12)                                /*!< Q channel gain factor */
#define RDCM_CSGCFG1_QCICSHIFT           BITS(16,21)                               /*!< Q channel output shift */

/* RDCM_CICCFG0 */
#define RDCM_CICCFG0_ICICDFAC            BITS(0,8)                                 /*!< I channel CIC3 filter decimation factor */
#define RDCM_CICCFG0_ICICSVAL            BITS(16,24)                               /*!< I channel CIC3 filter decimation counter load value */

/* RDCM_CICCFG1 */
#define RDCM_CICCFG1_QCICDFAC            BITS(0,8)                                 /*!< Q channel CIC3 filter decimation factor */
#define RDCM_CICCFG1_QCICSVAL            BITS(16,24)                               /*!< Q channel CIC3 filter decimation counter load value */

/* RDCM_CDCNT */
#define RDCM_CDCNT_ICICDCNT              BITS(0,8)                                 /*!< I channel CIC filter decimation counter */
#define RDCM_CDCNT_QCICDCNT              BITS(16,24)                               /*!< Q channel CIC3 filter decimation counter */

/* RDCM_NPMCFG */
#define RDCM_NPMCFG_XFAC                 BITS(0,15)                                /*!< Q channel nonorthogonal phase mismatch compensation factor X */
#define RDCM_NPMCFG_YFAC                 BITS(16,31)                               /*!< Q channel nonorthogonal phase mismatch compensation factor Y */

/* RDCM_TRKGAINCFG */
#define RDCM_TRKGAINCFG_TRKERRGAIN       BITS(0,28)                                /*!< the error acceleration gain factor */

/* RDCM_TRKINTCFG */
#define RDCM_TRKINTCFG_VINTGAIN          BITS(0,4)                                 /*!< the velocity gain factor of integrator */
#define RDCM_TRKINTCFG_PINTGAIN          BITS(16,20)                               /*!< the position gain factor of integrator */

/* RDCM_TRKCMPCFG */
#define RDCM_TRKCMPCFG_POLE              BITS(0,14)                                /*!< the pole of compensation filter */
#define RDCM_TRKCMPCFG_ZERO              BITS(16,30)                               /*!< the zero of compensation filter */

/* RDCM_VSFCFG */
#define RDCM_VSFCFG_VSFM                 BITS(0,3)                                 /*!< the velocity smooth filter mode in tracking loop */

/* RDCM_HFDATA */
#define RDCM_HFDATA_IHFDATA              BITS(0,15)                                /*!< data output from I channel high pass filter */
#define RDCM_HFDATA_QHFDATA              BITS(16,31)                               /*!< data output from Q channel high pass filter */

/* RDCM_RFMDATA */
#define RDCM_RFMDATA_IRFMDATA            BITS(0,15)                                /*!< data output from I channel reference frequency mixer */
#define RDCM_RFMDATA_QRFMDATA            BITS(16,31)                               /*!< data output from Q channel reference frequency mixer */

/* RDCM_DEMDATA */
#define RDCM_DEMDATA_IDEMDATA            BITS(0,15)                                /*!< data output from I channel phase sensitive demodulator */
#define RDCM_DEMDATA_QDEMDATA            BITS(16,31)                               /*!< data output from Q channel phase sensitive demodulator */

/* RDCM_TRKDATA */
#define RDCM_TRKDATA_VELOCITY            BITS(0,15)                                /*!< velocity data */
#define RDCM_TRKDATA_POSITION            BITS(16,31)                               /*!< position data */

/* RDCM_MONDATA */
#define RDCM_MONDATA_TRKERRDATA          BITS(0,15)                                /*!< tracking error signal data */
#define RDCM_MONDATA_MONDATA             BITS(16,31)                               /*!< monitor signal data */

/* RDCM_TSCTL */
#define RDCM_TSCTL_TSCNT                 BITS(0,15)                                /*!< timestamp counter value */
#define RDCM_TSCTL_TSCLK                 BITS(16,17)                               /*!< timestamp counter clock selection */

/* RDCM_TSDATA */
#define RDCM_TSDATA_TSVAL                BITS(0,15)                                /*!< the most recent captured timestamp value */
#define RDCM_TSDATA_TSTRGF               BIT(31)                                   /*!< timestamp information valid flag */

/* RDCM_FIFOCS */
#define RDCM_FIFOCS_FIFOESEL             BITS(0,1)                                 /*!< FIFO result event selection */
#define RDCM_FIFOCS_FIFOFH               BIT(2)                                    /*!< FIFO reset */
#define RDCM_FIFOCS_FIFONUM              BITS(16,18)                               /*!< FIFO valid data number */
#define RDCM_FIFOCS_RERRF                BIT(19)                                   /*!< read error flag */
#define RDCM_FIFOCS_WERRF                BIT(20)                                   /*!< write error flag */

/* RDCM_FIFODATA */
#define RDCM_FIFODATA_FIFODATA           BITS(0,31)                                /*!< FIFO read data */

/* RDCM_ETHCFG0 */
#define RDCM_ETHCFG0_IETHL               BITS(0,14)                                /*!< lower threshold for envelope signal of I channel */
#define RDCM_ETHCFG0_IETHU               BITS(16,30)                               /*!< upper threshold for envelope signal of I channel */

/* RDCM_ETHCFG1 */
#define RDCM_ETHCFG1_QETHL               BITS(0,14)                                /*!< lower threshold for envelope signal of Q channel */
#define RDCM_ETHCFG1_QETHU               BITS(16,30)                               /*!< upper threshold for envelope signal of Q channel */

/* RDCM_MTHCFG */
#define RDCM_MTHCFG_MTHL                 BITS(0,14)                                /*!< lower threshold for monitor signal */
#define RDCM_MTHCFG_MTHU                 BITS(16,30)                               /*!< upper threshold for monitor signal */

/* RDCM_TRKERRTHCFG */
#define RDCM_TRKERRTHCFG_TRKERRTHL       BITS(0,14)                                /*!< lower threshold for tracking error signal */
#define RDCM_TRKERRTHCFG_TRKERRTHU       BITS(16,30)                               /*!< upper threshold for tracking error signal */

/* RDCM_THCNT */
#define RDCM_THCNT_TRKERRTHCNT           BITS(0,13)                                /*!< the tracking error signal threshold match counter value */
#define RDCM_THCNT_MTHCNT                BITS(16,29)                               /*!< the monitor signal threshold match counter value */

/* RDCM_SIMDI */
#define RDCM_SIMDI_ISIMDI                BITS(0,13)                                /*!< software I channel data input */
#define RDCM_SIMDI_QSIMDI                BITS(16,29)                               /*!< software Q channel data input */

/* RDCM_DISWSEL */
#define RDCM_DISWSEL_DISEL               BIT(0)                                    /*!< RDC data software selection */
#define RDCM_DISWSEL_ISIGNSEL            BIT(1)                                    /*!< I channel RDC frequency mixer reference sign source selection */
#define RDCM_DISWSEL_QSIGNSEL            BIT(17)                                   /*!< Q channel RDC frequency mixer reference sign source selection */

/* RDCM_PWMCFG */
#define RDCM_PWMCFG_PWMGAIN              BITS(0,13)                                /*!< gain adjust config for PWM value (PWMVAL) */
#define RDCM_PWMCFG_PWMOFFSET            BITS(16,29)                               /*!< PWM offset adjust config for PWM value (PWMVAL) */
#define RDCM_PWMCFG_BREVM                BIT(30)                                   /*!< bit-reversed mode for PWM value (PWMVAL) */
#define RDCM_PWMCFG_PWMEN                BIT(31)                                   /*!< PWM waveform generator enable */

/* RDCM_POSDATA */
#define RDCM_POSDATA_POSITION            BITS(0,15)                                /*!< position data */

/* RDCM_VELDATA */
#define RDCM_VELDATA_VELOCITY            BITS(0,15)                                /*!< velocity data */

/* constants definitions */
/* RDCM main chain calculation event selection */
#define CALSEL(regval)                  (BITS(1,2) & ((uint32_t)(regval) << 1))
#define RDCM_CALSEL_ADC0                CALSEL(0)                                  /*!< ADC0 end of conversion event */
#define RDCM_CALSEL_ADC1                CALSEL(1)                                  /*!< ADC1 end of conversion event */
#define RDCM_CALSEL_ADC0_OR_ADC1        CALSEL(2)                                  /*!< ADC0 or ADC1 end of conversion event */
#define RDCM_CALSEL_EXTERNAL_TRIGGER    CALSEL(3)                                  /*!< external trigger from TRIGSEL for RDC main chain calculation */

/* gate signal valid selection */
#define GATEVSEL(regval)                (BITS(3,4) & ((uint32_t)(regval) << 3))
#define RDCM_GATEVSEL_ALWAYS_VALID      GATEVSEL(0)                                /*!< always valid */
#define RDCM_GATEVSEL_HIGH_VALID        GATEVSEL(1)                                /*!< valid level is high */
#define RDCM_GATEVSEL_LOW_VALID         GATEVSEL(2)                                /*!< valid level is low */

/* tracking error signal threshold mode selection */
#define TRKERRTHMS(regval)              (BITS(5,6) & ((uint32_t)(regval) << 5))
#define RDCM_TRKERRTHMS_RANGE           TRKERRTHMS(0)                              /*!< TRKERRTHL[14:0] < tracking error signal value < TRKERRTHU[14:0] */
#define RDCM_TRKERRTHMS_OUT_RANGE       TRKERRTHMS(1)                              /*!< tracking error signal value < TRKERRTHL[14:0] or TRKERRTHU[14:0] < tracking error signal value */
#define RDCM_TRKERRTHMS_GREATER         TRKERRTHMS(2)                              /*!< TRKERRTHL[14:0] < tracking error signal value */
#define RDCM_TRKERRTHMS_LESS            TRKERRTHMS(3)                              /*!< TRKERRTHL[14:0] > tracking error signal value */

/* I channel envelope signal threshold mode selection */
#define IETHMS(regval)                  (BITS(21,22) & ((uint32_t)(regval) << 21))
#define RDCM_IETHMS_RANGE               IETHMS(0)                                  /*!< IETHL[14:0] < I channel envelope signal value < IETHU[14:0] */
#define RDCM_IETHMS_OUT_RANGE           IETHMS(1)                                  /*!< I channel envelope signal value < IETHL[14:0] or IETHU[14:0] < I channel envelope signal value */
#define RDCM_IETHMS_GREATER             IETHMS(2)                                  /*!< IETHL[14:0] < I channel envelope signal value */
#define RDCM_IETHMS_LESS                IETHMS(3)                                  /*!< IETHL[14:0] > I channel envelope signal value */

/* Q channel envelope signal threshold mode selection */
#define QETHMS(regval)                  (BITS(19,20) & ((uint32_t)(regval) << 19))
#define RDCM_QETHMS_RANGE               QETHMS(0)                                  /*!< QETHL[14:0] < Q channel envelope signal value < QETHU[14:0] */
#define RDCM_QETHMS_OUT_RANGE           QETHMS(1)                                  /*!< Q channel envelope signal value < QETHL[14:0] or QETHU[14:0] < Q channel envelope signal value */
#define RDCM_QETHMS_GREATER             QETHMS(2)                                  /*!< QETHL[14:0] < Q channel envelope signal value */
#define RDCM_QETHMS_LESS                QETHMS(3)                                  /*!< QETHL[14:0] > Q channel envelope signal value */

/* monitor signal mode selection */
#define MTHMS(regval)                   (BITS(17,18) & ((uint32_t)(regval) << 17))
#define RDCM_MTHMS_RANGE                MTHMS(0)                                   /*!< MTHL[14:0] < monitor signal value < MTHU[14:0] */
#define RDCM_MTHMS_OUT_RANGE            MTHMS(1)                                   /*!< monitor signal value < MTHL[14:0] or MTHU[14:0] < monitor signal value */
#define RDCM_MTHMS_LESS                 MTHMS(2)                                   /*!< MTHL[14:0] > monitor signal vibration value */
#define RDCM_MTHMS_GREATER              MTHMS(3)                                   /*!< MTHL[14:0] < monitor signal vibration value */

/* RDCM result data register selection */
#define RESDSEL(regval)                 (BITS(27,29) & ((uint32_t)(regval) << 27))
#define RDCM_RESDSEL_TRKDATA            RESDSEL(0)                                 /*!< RDCM_TRKDATA */
#define RDCM_RESDSEL_HFDATA             RESDSEL(1)                                 /*!< RDCM_HFDATA */
#define RDCM_RESDSEL_RFMDATA            RESDSEL(2)                                 /*!< RDCM_RFMDATA */
#define RDCM_RESDSEL_DEMDATA            RESDSEL(3)                                 /*!< RDCM_DEMDATA */
#define RDCM_RESDSEL_MONDATA            RESDSEL(4)                                 /*!< RDCM_MONDATA */
#define RDCM_RESDSEL_POSDATA            RESDSEL(5)                                 /*!< RDCM_POSDATA */
#define RDCM_RESDSEL_VELDATA            RESDSEL(6)                                 /*!< RDCM_VELDATA */

/* zero crossing detection mode selection in I channel */
#define IZCDMS(regval)                  (BITS(3,4) & ((uint32_t)(regval) << 3))
#define RDCM_IZCDMS_DISABLE             IZCDMS(0)                                  /*!< zero crossing detection is disabled (manual reference frequency mixer phase adjust) */
#define RDCM_IZCDMS_POSITIVE            IZCDMS(1)                                  /*!< positive zero crossing detection mode (only for calibration) */
#define RDCM_IZCDMS_NEGATIVE            IZCDMS(2)                                  /*!< negative zero crossing detection mode (only for calibration) */
#define RDCM_IZCDMS_BOTH                IZCDMS(3)                                  /*!< both positive and negative zero crossing detection mode (automatic reference frequency mixer phase adjust) */

/* zero crossing detection mode selection in Q channel */
#define QZCDMS(regval)                  (BITS(19,20) & ((uint32_t)(regval) << 19))
#define RDCM_QZCDMS_DISABLE             QZCDMS(0)                                  /*!< zero crossing detection is disabled (manual reference frequency mixer phase adjust) */
#define RDCM_QZCDMS_POSITIVE            QZCDMS(1)                                  /*!< positive zero crossing detection mode (only for calibration) */
#define RDCM_QZCDMS_NEGATIVE            QZCDMS(2)                                  /*!< negative zero crossing detection mode (only for calibration) */
#define RDCM_QZCDMS_BOTH                QZCDMS(3)                                  /*!< both positive and negative zero crossing detection mode (automatic reference frequency mixer phase adjust) */

/* external trigger mode for timestamp counter capture */
#define TSCAPETM(regval)                (BITS(7,8) & ((uint32_t)(regval) << 7))
#define RDCM_TSCAPETM_DISABLE           TSCAPETM(0)                                /*!< disable trigger for timestamp counter capture */
#define RDCM_TSCAPETM_RISING            TSCAPETM(1)                                /*!< rising edge of external trigger for timestamp counter capture */
#define RDCM_TSCAPETM_FALLING           TSCAPETM(2)                                /*!< falling edge of external trigger for timestamp counter capture */
#define RDCM_TSCAPETM_BOTH              TSCAPETM(3)                                /*!< rising and falling edge of external trigger for timestamp counter capture */

/* external trigger mode for all NCOs calculation */
#define NCOETM(regval)                  (BITS(22,23) & ((uint32_t)(regval) << 22))
#define RDCM_NCOETM_DIVISION            NCOETM(0)                                  /*!< calculation according to the NCO division of CK_RDCM */
#define RDCM_NCOETM_RISING              NCOETM(1)                                  /*!< rising edge of external trigger for all NCOs calculation */
#define RDCM_NCOETM_FALLING             NCOETM(2)                                  /*!< falling edge of external trigger for all NCOs calculation */
#define RDCM_NCOETM_BOTH                NCOETM(3)                                  /*!< rising and falling edge of external trigger for all NCOs calculation */

/* external trigger mode for RDCM main chain calculation */
#define CALETM(regval)                  (BITS(5,6) & ((uint32_t)(regval) << 5))
#define RDCM_CALETM_DISABLE             CALETM(0)                                  /*!< disable trigger for RDCM main chain calculation */
#define RDCM_CALETM_RISING              CALETM(1)                                  /*!< rising edge of external trigger for RDCM main chain calculation */
#define RDCM_CALETM_FALLING             CALETM(2)                                  /*!< falling edge of external trigger for RDCM main chain calculation */
#define RDCM_CALETM_BOTH                CALETM(3)                                  /*!< rising and falling edge of external trigger for RDCM main chain calculation */

/* I channel high-pass filter mode */
#define IHFM(regval)                    (BITS(16,18) & ((uint32_t)(regval) << 16))
#define RDCM_IHFM_DISABLE               IHFM(0)                                    /*!< offset compensation filter disabled */
#define RDCM_IHFM_RATE1                 IHFM(1)                                    /*!< enable offset compensation filter, set cutoff frequency to rate 1 */
#define RDCM_IHFM_RATE2                 IHFM(2)                                    /*!< enable offset compensation filter, set cutoff frequency to rate 2 */
#define RDCM_IHFM_RATE3                 IHFM(3)                                    /*!< enable offset compensation filter, set cutoff frequency to rate 3 */
#define RDCM_IHFM_RATE4                 IHFM(4)                                    /*!< enable offset compensation filter, set cutoff frequency to rate 4 */
#define RDCM_IHFM_RATE5                 IHFM(5)                                    /*!< enable offset compensation filter, set cutoff frequency to rate 5 */
#define RDCM_IHFM_RATE6                 IHFM(6)                                    /*!< enable offset compensation filter, set cutoff frequency to rate 6 */
#define RDCM_IHFM_RATE7                 IHFM(7)                                    /*!< enable offset compensation filter, set cutoff frequency to rate 7 */

/* Q channel high-pass filter mode */
#define QHFM(regval)                    (BITS(16,18) & ((uint32_t)(regval) << 16))
#define RDCM_QHFM_DISABLE               QHFM(0)                                    /*!< offset compensation filter disabled */
#define RDCM_QHFM_RATE1                 QHFM(1)                                    /*!< enable offset compensation filter, set cutoff frequency to rate 1 */
#define RDCM_QHFM_RATE2                 QHFM(2)                                    /*!< enable offset compensation filter, set cutoff frequency to rate 2 */
#define RDCM_QHFM_RATE3                 QHFM(3)                                    /*!< enable offset compensation filter, set cutoff frequency to rate 3 */
#define RDCM_QHFM_RATE4                 QHFM(4)                                    /*!< enable offset compensation filter, set cutoff frequency to rate 4 */
#define RDCM_QHFM_RATE5                 QHFM(5)                                    /*!< enable offset compensation filter, set cutoff frequency to rate 5 */
#define RDCM_QHFM_RATE6                 QHFM(6)                                    /*!< enable offset compensation filter, set cutoff frequency to rate 6 */
#define RDCM_QHFM_RATE7                 QHFM(7)                                    /*!< enable offset compensation filter, set cutoff frequency to rate 7 */

/* timestamp counter clock selection */
#define TSCLK(regval)                   (BITS(16,17) & ((uint32_t)(regval) << 16))
#define RDCM_TSCLK_DIV1                 TSCLK(0)                                   /*!< fTS = fRDCM */
#define RDCM_TSCLK_DIV2                 TSCLK(1)                                   /*!< fTS = fRDCM / 2 */
#define RDCM_TSCLK_DIV4                 TSCLK(2)                                   /*!< fTS = fRDCM / 4 */
#define RDCM_TSCLK_DIV8                 TSCLK(3)                                   /*!< fTS = fRDCM / 8 */

/* FIFO result event selection */
#define FIFOESEL(regval)                (BITS(0,1) & ((uint32_t)(regval)))
#define RDCM_FIFOESEL_1VALUE            FIFOESEL(0)                                /*!< generate result data event when FIFO contains 1 value */
#define RDCM_FIFOESEL_2VALUE            FIFOESEL(1)                                /*!< generate result data event when FIFO contains 2 values */
#define RDCM_FIFOESEL_3VALUE            FIFOESEL(2)                                /*!< generate result data event when FIFO contains 3 values */
#define RDCM_FIFOESEL_4VALUE            FIFOESEL(3)                                /*!< generate result data event when FIFO contains 4 values */

/* RDCM DMA disable mode */
#define RDCM_DDSM_AFTER_TRANSFER        ((uint32_t)0x00000000U)                    /*!< the DMA engine is disabled after the end of transfer signal from DMA controller is detected */
#define RDCM_DDSM_REQUEST_ENABLED       ((uint32_t)0x40000000U)                    /*!< when DMAEN=1, the DMA issues a request according to result data transfer setting */

/* RDCM FIFO flush */
#define RDCM_FIFO_FLUSH                 BIT(2)                                     /*!< remove all values from result FIFO */

/* RDCM data input selection */
#define RDCM_DISEL_ADC                  ((uint32_t)0x00000000U)                    /*!< RDCM I/Q channel calculation use ADC conversion data */
#define RDCM_DISEL_SIMULATION           ((uint32_t)0x00000001U)                    /*!< RDCM I/Q channel calculation use ISIMDI[13:0] and QSIMDI[13:0] */

/* RDCM I/Q channel frequency mixer reference sign source selection */
#define RDCM_ISIGNSEL_INTERNAL          ((uint32_t)0x00000000U)                    /*!< use on-chip excitor sign as I channel RDCM frequency mixer reference */
#define RDCM_ISIGNSEL_EXTERNAL          ((uint32_t)0x00000002U)                    /*!< use external excitor sign signal pin input as I channel RDCM frequency mixer reference */
#define RDCM_QSIGNSEL_INTERNAL          ((uint32_t)0x00000000U)                    /*!< use on-chip excitor sign as Q channel RDCM frequency mixer reference */
#define RDCM_QSIGNSEL_EXTERNAL          ((uint32_t)0x00020000U)                    /*!< use external excitor sign signal pin input as Q channel RDCM frequency mixer reference */

/* RDCM PWM bit-reversed mode */
#define RDCM_BREVM_NORMAL               ((uint32_t)0x00000000U)                    /*!< normal mode for PWM value */
#define RDCM_BREVM_BIT_REVERSED         ((uint32_t)0x40000000U)                    /*!< bit-reversed mode for PWM value */

#define RDCM_EXC_DISABLE                ((uint32_t)0x00000000U)
#define RDCM_EXC_ENABLE                 ((uint32_t)0x02000000U)

#define RDCM_PWM_DISABLE                ((uint32_t)0x00000000U)
#define RDCM_PWM_ENABLE                 ((uint32_t)0x80000000U)

#define RDCM_RFM_DISABLE                ((uint32_t)0x00000000U)
#define RDCM_RFM_ENABLE                 ((uint32_t)0x00000001U)

#define RDCM_DEM_DISABLE                ((uint32_t)0x00000000U)
#define RDCM_DEM_ENABLE                 ((uint32_t)0x00000002U)

#define RDCM_FIR0_DISABLE               ((uint32_t)0x00000000U)
#define RDCM_FIR0_ENABLE                ((uint32_t)0x00000001U)

#define RDCM_FIR1_DISABLE               ((uint32_t)0x00000000U)
#define RDCM_FIR1_ENABLE                ((uint32_t)0x00000002U)

#define RDCM_CIC3_DISABLE               ((uint32_t)0x00000000U)
#define RDCM_CIC3_ENABLE                ((uint32_t)0x00000008U)

#define RDCM_FIR1_DEC_2                 ((uint32_t)0x00000000U)
#define RDCM_FIR1_DEC_1                 ((uint32_t)0x00000004U)

#define RDCM_TRK_DISABLE                ((uint32_t)0x00000000U)
#define RDCM_TRK_ENABLE                 ((uint32_t)0x04000000U)

#define RDCM_CHANNEL_I                  ((uint32_t)0x00000000U)
#define RDCM_CHANNEL_Q                  ((uint32_t)0x00000001U)

/* RDCM interrupt enable or disable */
#define RDCM_INTEN_MASK                 ((uint32_t)0x0000FF80U)
#define RDCM_INT_TRKERRTHM              RDCM_CS_TRKERRTHMIE                          /*!< track error signal threshold match interrupt enable */
#define RDCM_INT_MTH                    RDCM_CS_MTHIE                                /*!< monitor signal threshold match interrupt enable */
#define RDCM_INT_QETHM                  RDCM_CS_QETHMIE                              /*!< Q channel envelope signal threshold match interrupt enable */
#define RDCM_INT_IETHM                  RDCM_CS_IETHMIE                              /*!< I channel envelope signal threshold match interrupt enable */
#define RDCM_INT_QZCD                   RDCM_CS_QZCDIE                               /*!< Q channel zero crossing detection valid interrupt enable */
#define RDCM_INT_IZCD                   RDCM_CS_IZCDIE                               /*!< I channel zero crossing detection valid interrupt enable */
#define RDCM_INT_TSCAP                  RDCM_CS_TSCAPIE                              /*!< timestamp counter capture valid interrupt enable */
#define RDCM_INT_DMAOV                  RDCM_CS_OVIE                                 /*!< RDC-DMA transfer overflow interrupt enable */
#define RDCM_INT_RESDATA                RDCM_CS_RESDIE                               /*!< result valid (Result update or result fifo level) interrupt enable */

/* RDCM interrupt flag */
#define RDCM_INT_FLAG_MASK              ((uint32_t)0xFF800000U)
#define RDCM_INT_FLAG_TRKERRTHM         RDCM_CS_TRKERRTHMIF                          /*!< track error signal threshold match interrupt flag */
#define RDCM_INT_FLAG_MTH               RDCM_CS_MTHMIF                               /*!< monitor signal threshold match interrupt flag */
#define RDCM_INT_FLAG_QETHM             RDCM_CS_QETHMIF                              /*!< Q channel envelope signal threshold match interrupt flag */
#define RDCM_INT_FLAG_IETHM             RDCM_CS_IETHMIF                              /*!< I channel envelope signal threshold match interrupt flag */
#define RDCM_INT_FLAG_QZCD              RDCM_CS_QZCDIF                               /*!< Q channel zero crossing detection interrupt flag */
#define RDCM_INT_FLAG_IZCD              RDCM_CS_IZCDIF                               /*!< I channel zero crossing detection interrupt flag */
#define RDCM_INT_FLAG_TSCAP             RDCM_CS_TSCAPIF                              /*!< timestamp counter capture interrupt flag */
#define RDCM_INT_FLAG_DMAOV             RDCM_CS_OVIF                                 /*!< DMA transfer data register overflow interrupt flag */
#define RDCM_INT_FLAG_RESDATA           RDCM_CS_RESDIF                               /*!< result data interrupt flag */

/* RDCM flag */
/* define the RDCM  bit position and its register index offset */
#define RDCM_REG_VAL(offset)              (REG32((RDCM_BASE) + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define RDCM_BIT_POS(val)                 ((uint32_t)(val) & 0x0000001FU)
#define RDCM_REGIDX_BIT(regidx, bitpos)   (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))

#define RDCM_CS_OFFSET                  ((uint32_t)0x00000000U)
#define RDCM_TSDATA_OFFSET              ((uint32_t)0x00000070U)
#define RDCM_FIFOCS_OFFSET              ((uint32_t)0x00000074U)


typedef enum {
    RDCM_FLAG_TRKERRTHM = RDCM_REGIDX_BIT(RDCM_CS_OFFSET, 23U),                      /*!< track error signal threshold match interrupt flag */
    RDCM_FLAG_MTH = RDCM_REGIDX_BIT(RDCM_CS_OFFSET, 24U),                            /*!< monitor signal threshold match interrupt flag */
    RDCM_FLAG_QETHM = RDCM_REGIDX_BIT(RDCM_CS_OFFSET, 25U),                          /*!< Q channel envelope signal threshold match interrupt flag */
    RDCM_FLAG_IETHM = RDCM_REGIDX_BIT(RDCM_CS_OFFSET, 26U),                          /*!< I channel envelope signal threshold match interrupt flag */
    RDCM_FLAG_QZCD = RDCM_REGIDX_BIT(RDCM_CS_OFFSET, 27U),                           /*!< Q channel zero crossing detection interrupt flag */
    RDCM_FLAG_IZCD = RDCM_REGIDX_BIT(RDCM_CS_OFFSET, 28U),                           /*!< I channel zero crossing detection interrupt flag */
    RDCM_FLAG_TSCAP = RDCM_REGIDX_BIT(RDCM_CS_OFFSET, 29U),                          /*!< timestamp counter capture interrupt flag */
    RDCM_FLAG_DMAOV = RDCM_REGIDX_BIT(RDCM_CS_OFFSET, 30U),                          /*!< DMA transfer data register overflow interrupt flag */
    RDCM_FLAG_RESDATA = RDCM_REGIDX_BIT(RDCM_CS_OFFSET, 31U),                        /*!< result data interrupt flag */
    RDCM_FLAG_TSTRG = RDCM_REGIDX_BIT(RDCM_TSDATA_OFFSET, 31U),                      /*!< timestamp trigger flag */
    RDCM_FLAG_RERR = RDCM_REGIDX_BIT(RDCM_FIFOCS_OFFSET, 19U),                       /*!< FIFO read error flag */
    RDCM_FLAG_WERR = RDCM_REGIDX_BIT(RDCM_FIFOCS_OFFSET, 20U),                       /*!< FIFO write error flag */
}rdcm_flag_enum;

/* RDCM trigger parameter struct definitions */
typedef struct
{
    uint32_t nco_trigger_sel;                                                        /*!< NCOs trigger selection */
    uint32_t cal_trigger_sel;                                                        /*!< RDCM main chain calculation event selection */
    uint32_t cal_trigger_edge;                                                       /*!< external trigger mode for RDCM main chain calculation */
}rdcm_trigger_parameter_struct;

/* RDCM excitor output parameter struct definitions */
typedef struct
{
    uint32_t exc_en;                                                                 /*!< excitor enable */
    uint32_t exc_fre;                                                                /*!< excitor frequency factor */
    uint32_t exc_div;                                                                /*!< excitor calculation frequency division */
    uint32_t exc_phase;                                                              /*!< excitor initial phase factor */
    uint32_t exc_amp;                                                                /*!< excitor amplitude */
}rdcm_excitor_output_parameter_struct;

/* RDCM reference frequency mixer parameter struct definitions */
typedef struct
{
    uint32_t i_rfm_en;                                                               /*!< reference frequency mixer enable */
    uint32_t i_zc_mode;                                                              /*!< zero-crossing mode */
    uint32_t i_hf_mode;                                                              /*!< high pass filter mode */
    uint32_t i_rfm_fre;                                                              /*!< the frequency control word of the I channel reference frequency mixer */
    uint32_t i_rfm_phase;                                                            /*!< initial phase of the I channel reference frequency mixer */
    uint32_t i_zc_th;                                                                /*!< the threshold of mismatch counter value in zero crossing detection */
    uint32_t i_zc_th_var;                                                            /*!< the threshold variation range of mismatch counter value in zero crossing detection */
    uint32_t i_average;                                                              /*!< the mismatch counter average factor */
    uint32_t q_rfm_en;                                                               /*!< reference frequency mixer enable */
    uint32_t q_zc_mode;                                                              /*!< zero-crossing mode */
    uint32_t q_hf_mode;                                                              /*!< high pass filter mode */
    uint32_t q_rfm_fre;                                                              /*!< the frequency control word of the Q channel reference frequency mixer */
    uint32_t q_rfm_phase;                                                            /*!< initial phase of the Q channel reference frequency mixer */
    uint32_t q_zc_th;                                                                /*!< the threshold of mismatch counter value in zero crossing detection */
    uint32_t q_zc_th_var;                                                            /*!< the threshold variation range of mismatch counter value in zero crossing detection */
    uint32_t q_average;                                                              /*!< the mismatch counter average factor */
}rdcm_rfm_parameter_struct;

/* RDCM demodulator parameter struct definitions */
typedef struct
{
    uint32_t i_dem_en;                                                               /*!< I channel demodulator enable */
    uint32_t i_fir0_en;                                                              /*!< I channel FIR0 filter enable */
    uint32_t i_fir1_en;                                                              /*!< I channel FIR1 filter enable */
    uint32_t i_fir1_dec;                                                             /*!< I channel FIR1 filter decimation rate */
    uint32_t i_cic3_en;                                                              /*!< I channel CIC3 filter enable */
    uint32_t i_cic3_shift;                                                           /*!< I channel output shift */
    uint32_t i_cic3_gain;                                                            /*!< I channel gain factor */
    uint32_t i_cic3_dec;                                                             /*!< I channel CIC filter decimation factor */
    uint32_t i_cic3_val;                                                             /*!< I channel CIC filter start value */
    uint32_t q_dem_en;                                                               /*!< Q channel demodulator enable */
    uint32_t q_fir0_en;                                                              /*!< Q channel FIR0 filter enable */
    uint32_t q_fir1_en;                                                              /*!< Q channel FIR1 filter enable */
    uint32_t q_fir1_dec;                                                             /*!< Q channel FIR1 filter decimation rate */
    uint32_t q_cic3_en;                                                              /*!< Q channel CIC3 filter enable */
    uint32_t q_cic3_shift;                                                           /*!< Q channel output shift */
    uint32_t q_cic3_gain;                                                            /*!< Q channel gain factor */
    uint32_t q_cic3_dec;                                                             /*!< Q channel CIC filter decimation factor */
    uint32_t q_cic3_val;                                                             /*!< Q channel CIC filter start value */
}rdcm_demodulator_parameter_struct;

/* RDCM track loop parameter struct definitions */
typedef struct
{
    uint32_t trk_en;                                                                 /*!< track loop enable */
    uint32_t npm_x;                                                                  /*!< Q channel nonorthogonal phase mismatch compensation factor X */
    uint32_t npm_y;                                                                  /*!< Q channel nonorthogonal phase mismatch compensation factor Y */
    uint32_t trk_gain;                                                               /*!< the error acceleration gain factor */
    uint32_t position_int_gain;                                                      /*!< the position gain factor of integrator */
    uint32_t velocity_int_gain;                                                      /*!< the velocity gain factor of integrator */
    uint32_t trk_cmp_zero;                                                           /*!< the zero of compensation filter */
    uint32_t trk_cmp_pole;                                                           /*!< the pole of compensation filter */
    uint32_t velocity_smooth_factor;                                                 /*!< velocity smooth filter mode in tracking loop */
}rdcm_track_loop_parameter_struct;

/* RDCM pwm parameter struct definitions */
typedef struct
{
    uint32_t pwm_en;                                                                 /*!< PWM waveform generator enable */
    uint32_t bit_reverse;                                                            /*!< bit-reversed mode for PWM value */
    uint32_t pwm_offset;                                                             /*!< PWM offset for PWM value */
    uint32_t pwm_gain;                                                               /*!< PWM gain for PWM value */
}rdcm_pwm_parameter_struct;

/* function declarations */
/* initialization functions */
/* reset RDCM */
void rdcm_deinit(void);
/* RDCM trigger functions */
/* initialize RDCM trigger parameter struct with a default value */
void rdcm_trigger_parameter_struct_para_init(rdcm_trigger_parameter_struct *initpara);
/* configure RDCM trigger function */
void rdcm_trigger_config(rdcm_trigger_parameter_struct* trigger_para);

/* RDCM excitor functions */
/* initialize RDCM excitor output parameter struct with a default value */
void rdcm_excitor_output_parameter_struct_para_init(rdcm_excitor_output_parameter_struct *initpara);
/* configure RDCM excitor output function */
void rdcm_excitor_output_config(rdcm_excitor_output_parameter_struct* exc_outputpara);
/* initialize RDCM excitor pwm parameter struct with a default value */
void rdcm_pwm_parameter_struct_para_init(rdcm_pwm_parameter_struct *initpara);
/* configure RDCM excitor pwm function */
void rdcm_excitor_pwm_config(rdcm_pwm_parameter_struct* pwm_para);
/* enable RDCM excitor */
void rdcm_excitor_enable(void);
/* disable RDCM excitor */
void rdcm_excitor_disable(void);

/* RDCM reference frequency mixer functions */
/* initialize RDCM reference frequency mixer parameter struct with a default value */
void rdcm_rfm_parameter_struct_para_init(rdcm_rfm_parameter_struct *initpara);
/* configure RDCM reference frequency mixer function */
void rdcm_reference_frequency_mixer_config(rdcm_rfm_parameter_struct* rfm_para);
/* enable RDCM reference frequency mixer */
void rdcm_reference_frequency_mixer_enable(void);
/* disable RDCM reference frequency mixer */
void rdcm_reference_frequency_mixer_disable(void);

/* RDCM demodulator functions */
/* initialize RDCM demodulator parameter struct with a default value */
void rdcm_demodulator_parameter_struct_para_init(rdcm_demodulator_parameter_struct *initpara);
/* configure RDCM demodulator function */
void rdcm_demodulator_config(rdcm_demodulator_parameter_struct* dem_para);
/* enable RDCM demodulator */
void rdcm_demodulator_enable(void);
/* disable RDCM demodulator */
void rdcm_demodulator_disable(void);
/* reset demodulator */
void rdcm_demodulator_reset(uint32_t channel);

/* RDCM track loop functions */
/* initialize RDCM track loop parameter struct with a default value */
void rdcm_track_loop_parameter_struct_para_init(rdcm_track_loop_parameter_struct *initpara);
/* configure RDCM track loop function */
void rdcm_track_loop_config(rdcm_track_loop_parameter_struct* trackloop_para);
/* enable RDCM track loop */
void rdcm_track_loop_enable(void);
/* disable RDCM track loop */
void rdcm_track_loop_disable(void);

/* RDCM basic functions */
/* enable RDCM */
void rdcm_enable(void);
/* disable RDCM */
void rdcm_disable(void);

/* RDCM DMA functions */
/* enable RDCM DMA */
void rdcm_dma_enable(void);
/* disable RDCM DMA */
void rdcm_dma_disable(void);
/* selection RDCM result data register */
void rdcm_result_data_reg_sel(uint32_t reg_sel);
/* configure RDCM DMA engine issues requests according to the RESDIF bit */
void rdcm_dma_request_after_last_enable(void);
/* configure RDCM DMA engine is disabled after the end of transfer signal from DMA controller is detected */
void rdcm_dma_request_after_last_disable(void);
/* enable RDCM dma overflow detection */
void rdcm_dma_overflow_detection_enable(void);
/* disable RDCM dma overflow detection */
void rdcm_dma_overflow_detection_disable(void);

/* RDCM NCO phase functions */
/* reset the phase of all NCOs (Excitor and I/Q reference frequency mixer) to the initial setting phase */
void rdcm_excitor_rfm_phase_reset(void);

/* RDCM timestamp functions */
/* enable timestamp counter capture */
void rdcm_timestamp_counter_capture_enable(void);
/* disable timestamp counter capture */
void rdcm_timestamp_counter_capture_disable(void);
/* configure timestamp trigger mode */
void rdcm_timestamp_trigger_mode_config(uint32_t mode);
/* configure timestamp counter clock */
void rdcm_timestamp_counter_clock_config(uint32_t clock);
/* read timestamp counter value */
uint16_t rdcm_timestamp_counter_value_read(void);
/* read the most recent captured timestamp value */
uint16_t rdcm_timestamp_capture_value_read(void);

/* RDCM FIFO functions */
/* enable result data fifo */
void rdcm_result_data_fifo_enable(void);
/* disable result data fifo */
void rdcm_result_data_fifo_disable(void);
/* configure FIFO result event */
void rdcm_fifo_result_event_config(uint32_t event);
/* flush result data fifo */
void rdcm_result_data_fifo_flush(void);
/* read FIFO valid data number */
uint8_t rdcm_fifo_valid_num_read(void);
/* read FIFO data */
uint32_t rdcm_fifo_data_read(void);

/* RDCM threshold match functions */
/* enable RDCM envelope signal threshold match */
void rdcm_envelope_signal_threshold_match_enable(uint32_t channel);
/* disable RDCM envelope signal threshold match */
void rdcm_envelope_signal_threshold_match_disable(uint32_t channel);
/* enable RDCM monitor signal threshold match */
void rdcm_monitor_signal_threshold_match_enable(void);
/* disable RDCM monitor signal threshold match */
void rdcm_monitor_signal_threshold_match_disable(void);
/* enable RDCM track error signal threshold match */
void rdcm_track_error_signal_threshold_match_enable(void);
/* disable RDCM track error signal threshold match */
void rdcm_track_error_signal_threshold_match_disable(void);
/* configure RDCM envelope signal threshold match mode */
void rdcm_envelope_signal_threshold_match_mode_config(uint32_t i_mode, uint32_t q_mode);
/* configure RDCM monitor signal threshold match mode */
void rdcm_monitor_signal_threshold_match_mode_config(uint32_t mode);
/* configure RDCM track error signal threshold match mode */
void rdcm_track_error_signal_threshold_match_mode_config(uint32_t mode);
/* configure RDCM envelope signal threshold */
void rdcm_envelope_signal_threshold_config(uint32_t channel, int32_t upper, int32_t lower);
/* configure RDCM monitor signal threshold */
void rdcm_monitor_signal_threshold_config(int32_t upper, int32_t lower);
/* configure RDCM track error signal threshold */
void rdcm_track_error_signal_threshold_config(int32_t upper, int32_t lower);
/* configure RDCM track error signal threshold match counter value */
void rdcm_track_error_signal_threshold_match_counter_config(uint32_t cnt);
/* configure RDCM monitor signal threshold match counter value */
void rdcm_monitor_signal_threshold_match_counter_config(uint32_t cnt);

/* gate signal configuration */
/* configure gate signal (timestamp trigger) valid level */
void rdcm_gate_signal_valid_level_config(uint32_t level);

/* channel data configuration */
/* configure I/Q channel data offset */
void rdcm_channel_data_offset_config(uint32_t channel, int32_t offset);
/* read I/Q channel CIC3 decimation counter */
uint16_t rdcm_cic3_decimation_counter_read(uint32_t channel);
/* read I/Q channel high pass filter data */
int16_t rdcm_high_pass_filter_data_read(uint32_t channel);
/* read I/Q channel reference frequency mixer data */
int16_t rdcm_reference_frequency_mixer_data_read(uint32_t channel);
/* read I/Q channel demodulator data */
int16_t rdcm_demodulator_data_read(uint32_t channel);

/* RDCM data read functions */
/* read track loop velocity data */
int16_t rdcm_track_velocity_data_read(void);
/* read track loop position data */
int16_t rdcm_track_position_data_read(void);
/* read track error signal data */
int16_t rdcm_track_error_signal_data_read(void);
/* read monitor signal data */
int16_t rdcm_monitor_signal_data_read(void);
/* read position data */
int16_t rdcm_position_read(void);
/* read velocity data */
int16_t rdcm_velocity_read(void);

/* RDCM simulation functions */
/* configure simulation I/Q channel data */
void rdcm_simulation_data_config(uint32_t i_data, uint32_t q_data);
/* configure reference frequency mixer sign data input source */
void rdcm_rfm_sign_input_source_config(uint32_t i_source, uint32_t q_source);
/* configure channel data input source */
void rdcm_channel_data_input_source_config(uint32_t source);

/* RDCM flag and interrupt functions */
/* get RDCM flag */
FlagStatus rdcm_flag_get(rdcm_flag_enum flag);
/* clear RDCM flag */
void rdcm_flag_clear(rdcm_flag_enum flag);
/* enable RDCM interrupt */
void rdcm_interrupt_enable(uint32_t interrupt);
/* disable RDCM interrupt */
void rdcm_interrupt_disable(uint32_t interrupt);
/* get RDCM interrupt flag */
FlagStatus rdcm_interrupt_flag_get(uint32_t flag);
/* clear RDCM interrupt flag */
void rdcm_interrupt_flag_clear(uint32_t flag);

#endif /* GD32H77X_78X_RDCM_H */