/*!
    \file    gd32h77x_78x_edim_biss.h
    \brief   definitions for the EDIM_BISS

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

#ifndef GD32H77X_78X_EDIM_BISS_H
#define GD32H77X_78X_EDIM_BISS_H

#include "gd32h77x_78x.h"

/* peripheral definitions */
/* peripheral base addresses */
#define EDIM_BISS                           (EDIM_BASE + 0x00000C00U)

/* registers definitions */
#define EDIM_BISS_SnDATA0(n)                REG32((EDIM_BISS) + 0x00000000U + (0x08U * (n)))    /*!< EDIM_BISS slave n data register 0 */
#define EDIM_BISS_SnDATA1(n)                REG32((EDIM_BISS) + 0x00000004U + (0x08U * (n)))    /*!< EDIM_BISS slave n data register 1 */
#define EDIM_BISS_CCDATAx(n)                REG32((EDIM_BISS) + 0x00000080U + (0x04U * (n)))    /*!< EDIM_BISS control communication data n register */
#define EDIM_BISS_SnPDTCFG(n)               REG32((EDIM_BISS) + 0x000000C0U + (0x04U * (n)))    /*!< EDIM_BISS slave n process data transmission configuration register */
#define EDIM_BISS_CCFG0                     REG32((EDIM_BISS) + 0x000000E0U)                    /*!< EDIM_BISS communication configuration register 0 */
#define EDIM_BISS_CCFG1                     REG32((EDIM_BISS) + 0x000000E4U)                    /*!< EDIM_BISS communication configuration register 1 */
#define EDIM_BISS_FREP                      REG32((EDIM_BISS) + 0x000000E8U)                    /*!< EDIM_BISS frame repetition register */
#define EDIM_BISS_CNTINTEN                  REG32((EDIM_BISS) + 0x000000ECU)                    /*!< EDIM_BISS counter and interrupt enable register */
#define EDIM_BISS_STAT0                     REG32((EDIM_BISS) + 0x000000F0U)                    /*!< EDIM_BISS status register 0 */
#define EDIM_BISS_CCFG2                     REG32((EDIM_BISS) + 0x000000F4U)                    /*!< EDIM_BISS communication configuration register 2 */
#define EDIM_BISS_STAT1                     REG32((EDIM_BISS) + 0x000000F8U)                    /*!< EDIM_BISS status register 1 */
#define EDIM_BISS_DFCTL                     REG32((EDIM_BISS) + 0x000000FCU)                    /*!< EDIM_BISS DMA and FIFO control register */
#define EDIM_BISS_FIFODATA                  REG32((EDIM_BISS) + 0x00000200U)                    /*!< EDIM_BISS FIFO data register */

/* bits definitions */
/* EDIM_BISS_SnDATA0 */
#define EDIM_BISS_SnDATA0_DATAL             BITS(0,31)                           /*!< EDIM_BISS low double word process data of slave n */

/* EDIM_BISS_SnDATA1 */
#define EDIM_BISS_SnDATA1_DATAH             BITS(0,31)                           /*!< EDIM_BISS high double word process data of slave n */

/* EDIM_BISS_CCDATAx */
#define EDIM_BISS_CCDATAx_CCDATA            BITS(0,31)                           /*!< EDIM_BISS control communication data */

/* EDIM_BISS_SnPDTCFG */
#define EDIM_BISS_SnPDTCFG_PDLEN            BITS(0,5)                            /*!< EDIM_BISS process data length */
#define EDIM_BISS_SnPDTCFG_PDTEN            BIT(6)                               /*!< EDIM_BISS process data transmission enable */
#define EDIM_BISS_SnPDTCFG_CRCPOLY          BITS(8,14)                           /*!< EDIM_BISS CRC polynomial */
#define EDIM_BISS_SnPDTCFG_CRCMSEL          BIT(15)                              /*!< EDIM_BISS CRC mode selection */
#define EDIM_BISS_SnPDTCFG_CRCIVAL          BITS(16,31)                          /*!< EDIM_BISS CRC initial value */

/* EDIM_BISS_CCFG0 */
#define EDIM_BISS_CCFG0_REGADDR             BITS(16,22)                         /*!< EDIM_BISS register communication start address */
#define EDIM_BISS_CCFG0_REGWRSEL            BIT(23)                             /*!< EDIM_BISS register communication write/read mode selection */
#define EDIM_BISS_CCFG0_REGNUM              BITS(24,29)                         /*!< EDIM_BISS the number of consecutive communication registers in register communication mode */

/* EDIM_BISS_CCFG1 */
#define EDIM_BISS_CCFG1_MASEL               BIT(8)                              /*!< EDIM_BISS MA signal level selection at the end of frame*/
#define EDIM_BISS_CCFG1_CMD                 BITS(11,13)                         /*!< EDIM_BISS command */
#define EDIM_BISS_CCFG1_CMD_IDACHK          BIT(11)                             /*!< EDIM_BISS ID acknowledge bit trigger command */
#define EDIM_BISS_CCFG1_CTS                 BIT(15)                             /*!< EDIM_BISS command communication mode selection */
#define EDIM_BISS_CCFG1_RAMNUM              BIT(24)                             /*!< EDIM_BISS number of RAM banks used for process data */
#define EDIM_BISS_CCFG1_CRCSEN              BIT(25)                             /*!< EDIM_BISS CRC storage enable */

/* EDIM_BISS_FREP */
#define EDIM_BISS_FREP_FREP                 BITS(0,19)                          /*!< EDIM_BISS frame automatic repetition rate */

/* EDIM_BISS_CNTINTEN */
#define EDIM_BISS_CNTINTEN_EODTIE           BIT(1)                              /*!< EDIM_BISS end of data transfer interrupt enable */
#define EDIM_BISS_CNTINTEN_CCERRIE          BIT(2)                              /*!< EDIM_BISS communication control error interrupt enable */
#define EDIM_BISS_CNTINTEN_PDTERRIE         BIT(3)                              /*!< EDIM_BISS process data transmission error interrupt enable */
#define EDIM_BISS_CNTINTEN_SERRIE           BIT(4)                              /*!< EDIM_BISS start bit error interrupt enable */
#define EDIM_BISS_CNTINTEN_ADTERRIE         BIT(5)                              /*!< EDIM_BISS automatic data transmission error interrupt enable */
#define EDIM_BISS_CNTINTEN_DMATOIE          BIT(7)                              /*!< EDIM_BISS DMA request timeout interrupt enable */
#define EDIM_BISS_CNTINTEN_FIFOUNRIE        BIT(8)                              /*!< EDIM_BISS FIFO underrun interrupt enable */
#define EDIM_BISS_CNTINTEN_FIFOOVRIE        BIT(9)                              /*!< EDIM_BISS FIFO overrun interrupt enable */
#define EDIM_BISS_CNTINTEN_FCNT             BITS(16,28)                         /*!< EDIM_BISS the count value from the BiSS frame's slave response ACK to the CDM timeout confirmation bit */

/* EDIM_BISS_STAT0 */
#define EDIM_BISS_STAT0_EODT                BIT(0)                              /*!< EDIM_BISS end of data transmission flag */
#define EDIM_BISS_STAT0_EOFT                BIT(1)                              /*!< EDIM_BISS end of frame transmission flag */
#define EDIM_BISS_STAT0_EOCC                BIT(2)                              /*!< EDIM_BISS end of control communication flag */
#define EDIM_BISS_STAT0_CCERRIF             BIT(3)                              /*!< EDIM_BISS control communication error flag */
#define EDIM_BISS_STAT0_PDTERRIF            BIT(4)                              /*!< EDIM_BISS process data transmission error flag */
#define EDIM_BISS_STAT0_SERRIF              BIT(5)                              /*!< EDIM_BISS start bit error interrupt flag */
#define EDIM_BISS_STAT0_ADTERRIF            BIT(6)                              /*!< EDIM_BISS automatic data transmission error interrupt flag */
#define EDIM_BISS_STAT0_INERRF              BIT(7)                              /*!< EDIM_BISS internal error flag */
#define EDIM_BISS_STAT0_SLVF                BITS(8,23)                          /*!< EDIM_BISS slave n data validity flags */
#define EDIM_BISS_STAT0_VREGNUM             BITS(24,29)                         /*!< EDIM_BISS number of valid register from addressed slave in register communication */
#define EDIM_BISS_STAT0_CDS                 BIT(30)                             /*!< EDIM_BISS CDS bit */
#define EDIM_BISS_STAT0_CDMTOF              BIT(31)                             /*!< EDIM_BISS CDM timeout completion flag */

/* EDIM_BISS_CCFG2 */
#define EDIM_BISS_CCFG2_ADTEN               BIT(0)                              /*!< EDIM_BISS automatic data transmission enable */
#define EDIM_BISS_CCFG2_FCTL                BITS(1,3)                           /*!< EDIM_BISS frame control */
#define EDIM_BISS_CCFG2_TINIT               BIT(4)                              /*!< EDIM_BISS transmit BiSS initialization sequence */
#define EDIM_BISS_CCFG2_RBSW                BIT(5)                              /*!< EDIM_BISS RAM bank force switching */
#define EDIM_BISS_CCFG2_RBSWDIS             BIT(6)                              /*!< EDIM_BISS RAM bank automatic switching disable */
#define EDIM_BISS_CCFG2_BRKDT               BIT(7)                              /*!< EDIM_BISS break data transmission */
#define EDIM_BISS_CCFG2_MACSEL              BIT(12)                             /*!< EDIM_BISS MA line level control source selection */
#define EDIM_BISS_CCFG2_MALVL               BIT(13)                             /*!< EDIM_BISS MA line force level */
#define EDIM_BISS_CCFG2_MAFRE               BITS(14,28)                         /*!< EDIM_BISS process data master clock frequency fMA */

/* EDIM_BISS_STAT1 */
#define EDIM_BISS_STAT1_SLINSTAT            BIT(0)                               /*!< EDIM_BISS SL line input level state */
#define EDIM_BISS_STAT1_CDSBU               BIT(1)                               /*!< EDIM_BISS CDS bit backup */
#define EDIM_BISS_STAT1_SLNUM               BITS(16,19)                          /*!< EDIM_BISS number of slaves in control communication */
#define EDIM_BISS_STAT1_RBSWERRF            BIT(24)                              /*!< EDIM_BISS RAM bank switching error flag */
#define EDIM_BISS_STAT1_DMATOIF             BIT(25)                              /*!< EDIM_BISS DMA request timeout error interrupt flag */
#define EDIM_BISS_STAT1_FIFOUNRIF           BIT(26)                              /*!< EDIM_BISS FIFO underrun interrupt flag */
#define EDIM_BISS_STAT1_FIFOOVRIF           BIT(27)                              /*!< EDIM_BISS FIFO overrun interrupt flag */
#define EDIM_BISS_STAT1_EODTIF              BIT(28)                              /*!< EDIM_BISS end of data transmission interrupt flag */

/* EDIM_BISS_DFCTL */
#define EDIM_BISS_DFCTL_DFEN                BIT(0)                              /*!< EDIM_BISS DMA request and FIFO enable */
#define EDIM_BISS_DFCTL_FIFOFH              BIT(1)                              /*!< EDIM_BISS FIFO flush */
#define EDIM_BISS_DFCTL_DMA_DFEN            BITS(16, 31)                        /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_SxRDATAy register */
#define EDIM_BISS_DFCTL_DFEN0               BIT(16)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S0RDATA0 register */
#define EDIM_BISS_DFCTL_DFEN1               BIT(17)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S0RDATA1 register */
#define EDIM_BISS_DFCTL_DFEN2               BIT(18)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S1RDATA0 register */
#define EDIM_BISS_DFCTL_DFEN3               BIT(19)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S1RDATA1 register */
#define EDIM_BISS_DFCTL_DFEN4               BIT(20)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S2RDATA0 register */
#define EDIM_BISS_DFCTL_DFEN5               BIT(21)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S2RDATA1 register */
#define EDIM_BISS_DFCTL_DFEN6               BIT(22)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S3RDATA0 register */
#define EDIM_BISS_DFCTL_DFEN7               BIT(23)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S3RDATA1 register */
#define EDIM_BISS_DFCTL_DFEN8               BIT(24)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S4RDATA0 register */
#define EDIM_BISS_DFCTL_DFEN9               BIT(25)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S4RDATA1 register */
#define EDIM_BISS_DFCTL_DFEN10              BIT(26)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S5RDATA0 register */
#define EDIM_BISS_DFCTL_DFEN11              BIT(27)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S5RDATA1 register */
#define EDIM_BISS_DFCTL_DFEN12              BIT(28)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S6RDATA0 register */
#define EDIM_BISS_DFCTL_DFEN13              BIT(29)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S6RDATA1 register */
#define EDIM_BISS_DFCTL_DFEN14              BIT(30)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S7RDATA0 register */
#define EDIM_BISS_DFCTL_DFEN15              BIT(31)                             /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S7RDATA1 register */

/* EDIM_BISS_FIFODATA */
#define EDIM_BISS_FIFODATA_FIFODATA         BITS(0,31)                          /*!< EDIM_BISS FIFO data from EDIM_BISS_SnDATA0/1 (n = 0��7) registers */

/* EDIM_BISS interrupt enable or disable */
#define EDIM_BISS_INTEN_MASK                    ((uint32_t)0x000003BEU)
#define EDIM_BISS_INT_EODTIE                    EDIM_BISS_CNTINTEN_EODTIE                 /*!< EDIM_BISS end of data transmission interrupt enable */
#define EDIM_BISS_INT_CCERRIE                   EDIM_BISS_CNTINTEN_CCERRIE                /*!< EDIM_BISS control communication error interrupt enable */
#define EDIM_BISS_INT_PDTERRIE                  EDIM_BISS_CNTINTEN_PDTERRIE               /*!< EDIM_BISS process data transmission error interrupt enable */
#define EDIM_BISS_INT_SERRIE                    EDIM_BISS_CNTINTEN_SERRIE                 /*!< EDIM_BISS start bit error interrupt enable */
#define EDIM_BISS_INT_ADTERRIE                  EDIM_BISS_CNTINTEN_ADTERRIE               /*!< EDIM_BISS automatic data transmission error interrupt enable */
#define EDIM_BISS_INT_DMATOIE                   EDIM_BISS_CNTINTEN_DMATOIE                /*!< EDIM_BISS DMA request timeout error interrupt enable */
#define EDIM_BISS_INT_FIFOUNRIE                 EDIM_BISS_CNTINTEN_FIFOUNRIE              /*!< EDIM_BISS FIFO underrun interrupt enable */
#define EDIM_BISS_INT_FIFOOVRIE                 EDIM_BISS_CNTINTEN_FIFOOVRIE              /*!< EDIM_BISS FIFO overrun interrupt enable */

/* define the EDIM_BISS bit position and its register index offset */
#define EDIM_BISS_REGIDX_BIT(regidx, bitpos)   (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define EDIM_BISS_REG_VAL(edim_periph, offset)              (REG32((edim_periph) + ((uint32_t)((offset) & 0x0000FFFFU) >> 6)))
#define EDIM_BISS_BIT_POS(val)                 ((uint32_t)(val) & 0x0000001FU)
#define EDIM_BISS_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                                   | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define EDIM_BISS_REG_VAL2(edim_periph, offset)               (REG32((edim_periph) + ((uint32_t)(offset) >> 22)))
#define EDIM_BISS_BIT_POS2(val)                  (((uint32_t)(val) & 0x001F0000U) >> 16)

/* register offset */
#define EDIM_BISS_CNTINTEN_REG_OFFSET               ((uint32_t)0x000000ECU)                     /*!< EDIM_BISS_CNTINTEN register offset */
#define EDIM_BISS_STAT0_REG_OFFSET                  ((uint32_t)0x000000F0U)                     /*!< EDIM_BISS status register 0 offset */
#define EDIM_BISS_STAT1_REG_OFFSET                  ((uint32_t)0x000000F8U)                     /*!< EDIM_BISS status register 1 offset */

/* EDIM_BISS interrupt flag */
typedef enum {
    EDIM_BISS_INT_FLAG_EODT        = EDIM_BISS_REGIDX_BIT2(EDIM_BISS_CNTINTEN_REG_OFFSET, 1U, EDIM_BISS_STAT1_REG_OFFSET, 28U),         /*!< EDIM_BISS end of data transmission interrupt flag */
    EDIM_BISS_INT_FLAG_CCERR       = EDIM_BISS_REGIDX_BIT2(EDIM_BISS_CNTINTEN_REG_OFFSET, 2U, EDIM_BISS_STAT0_REG_OFFSET, 3U),          /*!< EDIM_BISS control communication error interrupt flag */
    EDIM_BISS_INT_FLAG_PDTERR      = EDIM_BISS_REGIDX_BIT2(EDIM_BISS_CNTINTEN_REG_OFFSET, 3U, EDIM_BISS_STAT0_REG_OFFSET, 4U),          /*!< EDIM_BISS process data transmission error interrupt flag */
    EDIM_BISS_INT_FLAG_SERR        = EDIM_BISS_REGIDX_BIT2(EDIM_BISS_CNTINTEN_REG_OFFSET, 4U, EDIM_BISS_STAT0_REG_OFFSET, 5U),          /*!< EDIM_BISS start bit error interrupt flag */
    EDIM_BISS_INT_FLAG_ADTERR      = EDIM_BISS_REGIDX_BIT2(EDIM_BISS_CNTINTEN_REG_OFFSET, 5U, EDIM_BISS_STAT0_REG_OFFSET, 6U),          /*!< EDIM_BISS automatic data transmission error interrupt flag */
    EDIM_BISS_INT_FLAG_DMATO       = EDIM_BISS_REGIDX_BIT2(EDIM_BISS_CNTINTEN_REG_OFFSET, 7U, EDIM_BISS_STAT1_REG_OFFSET, 25U),         /*!< EDIM_BISS DMA request timeout error interrupt flag */
    EDIM_BISS_INT_FLAG_FIFOUNR     = EDIM_BISS_REGIDX_BIT2(EDIM_BISS_CNTINTEN_REG_OFFSET, 8U, EDIM_BISS_STAT1_REG_OFFSET, 26U),         /*!< EDIM_BISS FIFO underrun error interrupt flag */
    EDIM_BISS_INT_FLAG_FIFOOVR     = EDIM_BISS_REGIDX_BIT2(EDIM_BISS_CNTINTEN_REG_OFFSET, 9U, EDIM_BISS_STAT1_REG_OFFSET, 27U),         /*!< EDIM_BISS FIFO overrun error interrupt flag */
} edim_biss_interrupt_flag_enum;

/* EDIM_BISS flags */
typedef enum {
    EDIM_BISS_FLAG_EODT                = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 0U),          /*!< EDIM_BISS end of data transmission flag */
    EDIM_BISS_FLAG_EOFT                = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 1U),          /*!< EDIM_BISS end of frame transmission flag */
    EDIM_BISS_FLAG_EOCC                = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 2U),          /*!< EDIM_BISS end of control communication flag */
    EDIM_BISS_FLAG_CCERRN              = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 3U),          /*!< EDIM_BISS no control communication error interrupt flag */
    EDIM_BISS_FLAG_PDTERRN             = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 4U),          /*!< EDIM_BISS no process data transmission error interrupt flag */
    EDIM_BISS_FLAG_SERRN               = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 5U),          /*!< EDIM_BISS no start bit error interrupt flag in register communication */
    EDIM_BISS_FLAG_ADTERRN             = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 6U),          /*!< EDIM_BISS no automatic data transmission error interrupt flag */
    EDIM_BISS_FLAG_INERRN              = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 7U),          /*!< EDIM_BISS no internal error flag*/
    EDIM_BISS_FLAG_SLAVE0_DATA_VALID   = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 9U),          /*!< EDIM_BISS slave 0 data validity flag */
    EDIM_BISS_FLAG_SLAVE1_DATA_VALID   = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 11U),         /*!< EDIM_BISS slave 1 data validity flag */
    EDIM_BISS_FLAG_SLAVE2_DATA_VALID   = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 13U),         /*!< EDIM_BISS slave 2 data validity flag */
    EDIM_BISS_FLAG_SLAVE3_DATA_VALID   = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 15U),         /*!< EDIM_BISS slave 3 data validity flag */
    EDIM_BISS_FLAG_SLAVE4_DATA_VALID   = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 17U),         /*!< EDIM_BISS slave 4 data validity flag */
    EDIM_BISS_FLAG_SLAVE5_DATA_VALID   = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 19U),         /*!< EDIM_BISS slave 5 data validity flag */
    EDIM_BISS_FLAG_SLAVE6_DATA_VALID   = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 21U),         /*!< EDIM_BISS slave 6 data validity flag */
    EDIM_BISS_FLAG_SLAVE7_DATA_VALID   = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 23U),         /*!< EDIM_BISS slave 7 data validity flag */
    EDIM_BISS_FLAG_CDS                 = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 30U),         /*!< EDIM_BISS CDS bit sent by slave */
    EDIM_BISS_FLAG_CDMTOF              = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT0_REG_OFFSET, 31U),         /*!< EDIM_BISS CDM timeout completion flag in control communication */
    EDIM_BISS_FLAG_SLIN                = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT1_REG_OFFSET, 0U),          /*!< EDIM_BISS SL line input level state */
    EDIM_BISS_FLAG_CDSBU               = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT1_REG_OFFSET, 1U),          /*!< EDIM_BISS CDS bit backup */
    EDIM_BISS_FLAG_RBSWERR             = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT1_REG_OFFSET, 24U),         /*!< EDIM_BISS RAM bank switching error flag */
    EDIM_BISS_FLAG_DMATO               = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT1_REG_OFFSET, 25U),         /*!< EDIM_BISS DMA request timeout error interrupt flag */
    EDIM_BISS_FLAG_FIFOUNR             = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT1_REG_OFFSET, 26U),         /*!< EDIM_BISS FIFO underrun error interrupt flag */
    EDIM_BISS_FLAG_FIFOOVR             = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT1_REG_OFFSET, 27U),         /*!< EDIM_BISS FIFO overrun error interrupt flag */
    EDIM_BISS_FLAG_EODTIF              = EDIM_BISS_REGIDX_BIT(EDIM_BISS_STAT1_REG_OFFSET, 28U),         /*!< EDIM_BISS end of data transmission interrupt flag */
} edim_biss_flag_enum;

/* constants definitions */
/* EDIM_BiSS slave parameter struct definitions */
typedef struct
{   
    uint32_t data_length;                                                       /*!< length of process data in bits */
    uint32_t crc_poly;                                                          /*!< crc polynomial used for error checking */
    uint32_t crc_init_value;                                                    /*!< initial value for crc calculation */
} edim_biss_slave_parameter_struct;

/* EDIM_BiSS parameter struct definitions */
typedef struct
{   
    uint32_t ma_prescaler;                                                      /*!< master clock prescaler for automatic data transmission */
    uint32_t ma_force_control_level;                                            /*!< force control level for MA signal */
    uint32_t n_slave;                                                           /*!< number of slaves connected */
    edim_biss_slave_parameter_struct slave_config[8];                           /*!< array to slave configuration structure */
} edim_biss_init_parameter_struct;

/* EDIM_BiSS control communication struct definitions */
typedef struct
{   
    uint32_t reg_r_w;                                                           /*!< register read/write mode */
    uint32_t slave_id;                                                          /*!< id of the slave to communicate with */
    uint32_t reg_addr;                                                          /*!< address of the register to access */ 
    uint8_t r_w_data[64];                                                       /*!< data array to write to the register /read from the register */
    uint32_t reg_n_byte;                                                        /*!< number of bytes to read/write */
} edim_biss_control_comm_struct;

#define EDIM_BISS_CCOMM_REG_READ                          0U                             /*!< EDIM_BISS control communication register read */
#define EDIM_BISS_CCOMM_REG_WRITE                         EDIM_BISS_CCFG0_REGWRSEL       /*!< EDIM_BISS control communication register write */
#define EDIM_BISS_CCOMM_CMD                               EDIM_BISS_CCFG1_CTS            /*!< EDIM_BISS control communication mode selection */

#define EDIM_BISS_MA_NO_FORCE_CONTROL                     0U                                                    /*!< EDIM_BISS MA no force control */
#define EDIM_BISS_MA_FORCE_LEVEL_LOW                      EDIM_BISS_CCFG2_MACSEL                                /*!< EDIM_BISS MA force low */
#define EDIM_BISS_MA_FORCE_LEVEL_HIGH                     (EDIM_BISS_CCFG2_MACSEL | EDIM_BISS_CCFG2_MALVL)      /*!< EDIM_BISS MA force high */

#define EDIM_BISS_DMASEL_SLVn_DATAm(n, m)                 BIT((16U) + ((n) << 1U) + (m))

typedef enum{
    EDIM_BISS_SLAVE_BROADCAST   = 0x00,                                                     /*!< EDIM_BISS broadcast mode */
    EDIM_BISS_SLAVE7            = 0x01,                                                     /*!< EDIM_BISS slave 7 */
    EDIM_BISS_SLAVE6            = 0x02,                                                     /*!< EDIM_BISS slave 6 */
    EDIM_BISS_SLAVE5            = 0x04,                                                     /*!< EDIM_BISS slave 5 */
    EDIM_BISS_SLAVE4            = 0x08,                                                     /*!< EDIM_BISS slave 4 */
    EDIM_BISS_SLAVE3            = 0x10,                                                     /*!< EDIM_BISS slave 3 */
    EDIM_BISS_SLAVE2            = 0x20,                                                     /*!< EDIM_BISS slave 2 */
    EDIM_BISS_SLAVE1            = 0x40,                                                     /*!< EDIM_BISS slave 1 */
    EDIM_BISS_SLAVE0            = 0x80,                                                     /*!< EDIM_BISS slave 0 */
    EDIM_BISS_ALLSLAVE          = 0xFF,                                                     /*!< EDIM_BISS all slave */
} edim_biss_slave_enum;

/* EDIM_BISS master frame automatic repetition rate  */
#define MACFG_FREP(regval)                                   (BITS(0, 19) & ((uint32_t)(regval) << 0))
#define EDIM_BISS_AUTO_DATA_TRANSMIT_RATE_MAX                 MACFG_FREP(0)                  /*!< the highest frame rate for automatically restarting the next frame */
#define EDIM_BISS_AUTO_DATA_TRANSMIT_EXT_TRIGGER              MACFG_FREP(1)                  /*!< the master requires a trigger signal to restart the next frame */
#define EDIM_BISS_AUTO_DATA_TRANSMIT_RATE_DIV(x)              MACFG_FREP(((x) >> 1U) - 1U)   /*!< fPCLK / x */

/* EDIM_BISS process data master clock frequency */
#define CTL_MAFRE(regval)                                    (BITS(14, 28) & ((uint32_t)(regval) << 14))

/* EDIM_BISS register communication start address */
#define CTLCOMMCFG0_REGADDR(regval)                          (BITS(16, 22) & ((uint32_t)(regval) << 16))

/* EDIM_BISS the number of consecutive communication registers in register communication mode */
#define CTLCOMMCFG0_REGNUM(regval)                           (BITS(24, 29) & ((uint32_t)(regval) << 24))

/* EDIM_BISS register communication slave address */
#define CTLCOMMCFG1_SLAVEID(regval)                          (BITS(11, 13) & ((uint32_t)(regval) << 11))

/* EDIM_BISS command selection for BiSS command */
#define CTLCOMMCFG1_CMD(regval)                              (BITS(12, 13) & ((uint32_t)(regval) << 12))
#define EDIM_BISS_CMD_CHECKIDA(cmd)                          (CTLCOMMCFG1_CMD(cmd) | EDIM_BISS_CCFG1_CMD_IDACHK)   /*!< after successful checking of the ID acknowledge bit */
#define EDIM_BISS_CMD_ALWAYSEXE(cmd)                         (CTLCOMMCFG1_CMD(cmd))                                /*!< BiSS commands execute immediately */

/* EDIM_BISS MA signal level at the end of frame */
#define EDIM_BISS_MA_HIGH_END                                ((uint32_t)0x00000000U)                               /*!< after the slave timeout is detected on SL, MA changes to the digital high level */
#define EDIM_BISS_MA_MAINTAIN_END                            EDIM_BISS_CCFG1_MASEL                                 /*!< MA maintains level until the next frame begins */

/* EDIM_BISS crc polynomial */
#define SLVnCFG_CRCPOLY(regval)                              (BITS(8, 14) & ((uint32_t)(regval) << 8))
#define EDIM_BISS_SLAVE_CRC_NO_CRC                           (SLVnCFG_CRCPOLY(0x00))                               /*!< CRC verification is disabled. */
#define EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC3_0x0B             (SLVnCFG_CRCPOLY(0x03))                               /*!< CRC polynomial is 0x0B */
#define EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC4_0x13             (SLVnCFG_CRCPOLY(0x04))                               /*!< CRC polynomial is 0x13 */
#define EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC5_0x25             (SLVnCFG_CRCPOLY(0x05))                               /*!< CRC polynomial is 0x25 */
#define EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC6_0x43             (SLVnCFG_CRCPOLY(0x06))                               /*!< CRC polynomial is 0x43 */
#define EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC7_0x89             (SLVnCFG_CRCPOLY(0x07))                               /*!< CRC polynomial is 0x89 */
#define EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC8_0x12F            (SLVnCFG_CRCPOLY(0x08))                               /*!< CRC polynomial is 0x12F */
#define EDIM_BISS_SLAVE_CRC_PREDEFINED_CRC16_0x190D9         (SLVnCFG_CRCPOLY(0x10))                               /*!< CRC polynomial is 0x190D9 */
#define EDIM_BISS_SLAVE_CRC_CUSTOM(x)                        (EDIM_BISS_SnPDTCFG_CRCMSEL | SLVnCFG_CRCPOLY(((x) & 0xFF) >> 1))    /*!< individual CRC polynomial */

/* EDIM_BISS process data length */
#define SLVnCFG_PDLEN(regval)                                (BITS(0, 5) & ((uint32_t)(regval) << 0))
#define EDIM_BISS_SLAVE_DATALENGTH(x)                        (SLVnCFG_PDLEN(((x) - 1) & 0x3F))                       /*!< process data bit length is x */

/* EDIM_BISS frame control */
#define CTL_FCTL(regval)                                             (BITS(1, 3) & ((uint32_t)(regval) << 1))
#define EDIM_BISS_STOP                                               0U                                            /*!< no frame transmission */
#define EDIM_BISS_SEND_SINGLE_DATA_FRAME_WITH_CDM_1                  CTL_FCTL(1)                                   /*!< trigger one frame with CDM = 1 */
#define EDIM_BISS_SEND_SINGLE_DATA_FRAME_WITH_CDM_0                  CTL_FCTL(2)                                   /*!< trigger one frame with CDM = 0 */
#define EDIM_BISS_SEND_SINGLE_DATA_FRAME_WITH_CDM_INVERSE_CDS        CTL_FCTL(3)                                   /*!< trigger one frame with CDM being the inverse of CDS */
#define EDIM_BISS_SEND_SINGLE_CTRL_FRAME                             CTL_FCTL(4)                                   /*!< trigger one frame with control communication */
#define EDIM_BISS_SEND_SINGLE_CTRL_REDUCED_FRAME                     CTL_FCTL(7)                                   /*!< trigger one reduced frame with control communication */
#define EDIM_BISS_SEND_AUTO_DATA_FRAME_WITH_CDM_1                    (EDIM_BISS_CCFG2_ADTEN | CTL_FCTL(1))         /*!< next frame with CDM = 1 */
#define EDIM_BISS_SEND_AUTO_DATA_FRAME_WITH_CDM_0                    (EDIM_BISS_CCFG2_ADTEN | CTL_FCTL(2))         /*!< next frame with CDM = 0 */
#define EDIM_BISS_SEND_AUTO_DATA_FRAME_WITH_CDM_INVERSE_CDS          (EDIM_BISS_CCFG2_ADTEN | CTL_FCTL(3))         /*!< next frame with CDM being the inverse of CDS */
#define EDIM_BISS_SEND_AUTO_CTRL_FRAME                               (EDIM_BISS_CCFG2_ADTEN | CTL_FCTL(4))         /*!< next frame with control communication */
#define EDIM_BISS_SEND_AUTO_CTRL_REDUCED_FRAME                       (EDIM_BISS_CCFG2_ADTEN | CTL_FCTL(7))         /*!< next reduced frame with control communication */

/* EDIM_BISS DMA request and FIFO control */
#define EDIM_BISS_DMA_SEL_SLV0_DATA0                                 EDIM_BISS_DFCTL_DFEN0                         /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S0RDATA0 register */
#define EDIM_BISS_DMA_SEL_SLV0_DATA1                                 EDIM_BISS_DFCTL_DFEN1                         /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S0RDATA1 register */
#define EDIM_BISS_DMA_SEL_SLV1_DATA0                                 EDIM_BISS_DFCTL_DFEN2                         /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S1RDATA0 register */
#define EDIM_BISS_DMA_SEL_SLV1_DATA1                                 EDIM_BISS_DFCTL_DFEN3                         /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S1RDATA1 register */
#define EDIM_BISS_DMA_SEL_SLV2_DATA0                                 EDIM_BISS_DFCTL_DFEN4                         /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S2RDATA0 register */
#define EDIM_BISS_DMA_SEL_SLV2_DATA1                                 EDIM_BISS_DFCTL_DFEN5                         /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S2RDATA1 register */
#define EDIM_BISS_DMA_SEL_SLV3_DATA0                                 EDIM_BISS_DFCTL_DFEN6                         /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S3RDATA0 register */
#define EDIM_BISS_DMA_SEL_SLV3_DATA1                                 EDIM_BISS_DFCTL_DFEN7                         /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S3RDATA1 register */
#define EDIM_BISS_DMA_SEL_SLV4_DATA0                                 EDIM_BISS_DFCTL_DFEN8                         /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S4RDATA0 register */
#define EDIM_BISS_DMA_SEL_SLV4_DATA1                                 EDIM_BISS_DFCTL_DFEN9                         /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S4RDATA1 register */
#define EDIM_BISS_DMA_SEL_SLV5_DATA0                                 EDIM_BISS_DFCTL_DFEN10                        /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S5RDATA0 register */
#define EDIM_BISS_DMA_SEL_SLV5_DATA1                                 EDIM_BISS_DFCTL_DFEN11                        /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S5RDATA1 register */
#define EDIM_BISS_DMA_SEL_SLV6_DATA0                                 EDIM_BISS_DFCTL_DFEN12                        /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S6RDATA0 register */
#define EDIM_BISS_DMA_SEL_SLV6_DATA1                                 EDIM_BISS_DFCTL_DFEN13                        /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S6RDATA1 register */
#define EDIM_BISS_DMA_SEL_SLV7_DATA0                                 EDIM_BISS_DFCTL_DFEN14                        /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S7RDATA0 register */
#define EDIM_BISS_DMA_SEL_SLV7_DATA1                                 EDIM_BISS_DFCTL_DFEN15                        /*!< EDIM_BISS DMA request and FIFO enable for EDIM_BISS_S7RDATA1 register */

/* function declarations */
/* initialization functions */
/* reset EDIM_BISS */
void edim_biss_deinit(void);
/* initialize EDIM_BISS init parameter struct with a default value */
void edim_biss_init_parameter_struct_para_init(edim_biss_init_parameter_struct *initpara);
/* initialize BiSS-C config */
void edim_biss_init(edim_biss_init_parameter_struct* init_struct);
/* initialize BiSS-C slave and clear rest of the slave */
void edim_biss_slave_config(uint32_t n_slave, edim_biss_slave_parameter_struct slave_config[]);
/* enable specified BiSS-C slave */
void edim_biss_slave_enable(uint32_t slave);
/* disable specified BiSS-C slave */
void edim_biss_slave_disable(uint32_t slave);
/* send BiSS-C initialization sequence */
void edim_biss_initialization_sequence_config(ControlStatus newvalue);
/* stop current BiSS-C communication */
void edim_biss_break(void);
/*initialize EDIM_BISS control communication struct with a default value */
void edim_biss_control_comm_struct_para_init(edim_biss_control_comm_struct *ctrl_comm_struct);
/* configure BiSS-C register communication to be sent */
void edim_biss_reg_access(edim_biss_control_comm_struct* ctrl_comm_struct);
/* configure BiSS-C command communication to be sent */
void edim_biss_command(uint32_t slave_id, uint32_t cmd_value);
/* start a new BiSS-C frame with specified mode */
void edim_biss_send_frame(uint32_t frame_config);
/* configure prescale value of automatic data transmission mode */
void edim_biss_auto_transmission_config(uint32_t prescaler);
/* store process data CRC value into EDIM_BISS_SnDATA0/1 */
void edim_biss_store_crc_enable(void);
/* not store process data CRC value into EDIM_BISS_SnDATA0/1 */
void edim_biss_store_crc_disable(void);
/* select ram bank number used for process data */
void edim_biss_rambank_number_select(uint32_t rambank_num);
/* enable automatic ram bank switching */
void edim_biss_rambank_auto_switching_enable(void);
/* disable automatic ram bank switching */
void edim_biss_rambank_auto_switching_disable(void);
/* force ram bank switching */
void edim_biss_rambank_force_switching(void);
/* select MA signal level at the end of frame */
void edim_biss_ma_end_level_select(uint32_t ma_level);
/* configure master clock prescaler for process data */
void edim_biss_ma_prescaler_config(uint32_t prescaler);
/* enable dma for BiSS-C slave data receive */
void edim_biss_dma_enable(void);
/* disable dma for BiSS-C slave data receive */
void edim_biss_dma_disable(void);
/* flush dma fifo */
void edim_biss_dma_flush(void);
/* select slave process data to be load into DMA fifo */
void edim_biss_dma_select(uint32_t reg_selected);
/* read EDIM_BISS SnRDATA0/1 */
uint64_t edim_biss_data_read(uint32_t slave_id);
/* configure the count value from the BiSS frame's slave response ACK to the CDM timeout confirmation bit */
void edim_biss_frame_count_value_config(uint32_t frame_cnt);
/* get the number of valid register from addressed slave in register communication */
uint8_t edim_biss_valid_reg_num_get(void);
/* get the number of slaves in control communication */
uint8_t edim_biss_slave_num_get(void);
/* enable EDIM_BISS interrupt */
void edim_biss_interrupt_enable(uint32_t interrupt);
/* disable EDIM_BISS interrupt */
void edim_biss_interrupt_disable(uint32_t interrupt);
/* get EDIM_BISS interrupt flag */
FlagStatus edim_biss_interrupt_flag_get(edim_biss_interrupt_flag_enum int_flag);
/* clear EDIM_BISS interrupt flag */
void edim_biss_interrupt_flag_clear(edim_biss_interrupt_flag_enum int_flag);
/* get EDIM_BISS flag */
FlagStatus edim_biss_flag_get(edim_biss_flag_enum flag);
/* clear EDIM_BISS flag */
void edim_biss_flag_clear(edim_biss_flag_enum flag);

#endif /* GD32H77X_78X_EDIM_BISS_H */
