/*!
    \file    gd32h77x_78x_edim_endat.h
    \brief   definitions for the EDIM ENDAT

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

#ifndef GD32H77X_78X_EDIM_ENDAT_H
#define GD32H77X_78X_EDIM_ENDAT_H

#include "gd32h77x_78x.h"

/* EnDat definitions */
#define EDIM_ENDAT                          (EDIM_BASE + 0x00000800U)                 /*!< EDIM_ENDAT base address */

/* registers definitions */
#define EDIM_ENDAT_CMD                      REG32((EDIM_ENDAT) + 0x00000000U)         /*!< EnDat command */
#define EDIM_ENDAT_RDATA0                   REG32((EDIM_ENDAT) + 0x00000004U)         /*!< EnDat received data register 0 */
#define EDIM_ENDAT_RDATA1                   REG32((EDIM_ENDAT) + 0x00000008U)         /*!< EnDat received data register 1 */
#define EDIM_ENDAT_RDATA2                   REG32((EDIM_ENDAT) + 0x0000000CU)         /*!< EnDat received data register 2 */
#define EDIM_ENDAT_RDATA3                   REG32((EDIM_ENDAT) + 0x00000010U)         /*!< EnDat received data register 3 */
#define EDIM_ENDAT_CFG0                     REG32((EDIM_ENDAT) + 0x00000014U)         /*!< EnDat configuration register 0 */
#define EDIM_ENDAT_CFG1                     REG32((EDIM_ENDAT) + 0x00000018U)         /*!< EnDat configuration register 1 */
#define EDIM_ENDAT_STAT                     REG32((EDIM_ENDAT) + 0x0000001CU)         /*!< EnDat status register */
#define EDIM_ENDAT_INTEN                    REG32((EDIM_ENDAT) + 0x00000020U)         /*!< EnDat interrupt enable register */
#define EDIM_ENDAT_SWT                      REG32((EDIM_ENDAT) + 0x00000024U)         /*!< EnDat software trigger register */
#define EDIM_ENDAT_FIFODATA                 REG32((EDIM_ENDAT) + 0x00000128U)         /*!< EnDat FIFO data register */
#define EDIM_ENDAT_STATUPMODE               REG32((EDIM_ENDAT) + 0x00000200U)         /*!< EnDat status update mode register */

/* bits definitions */
/* EDIM_ENDAT_CMD */
#define EDIM_ENDAT_CMD_CDATA                BITS(0,15)                           /*!< EnDat communication mode code */
#define EDIM_ENDAT_CMD_MEMADDR              BITS(16,23)                          /*!< Memory range selection, address and port address of encoder */
#define EDIM_ENDAT_CMD_CMD                  BITS(24,29)                          /*!< Encoder receive communication data of instruction or parameters */

/* EDIM_ENDAT_RDATA0 */
#define EDIM_ENDAT_RDATA0_RDATAL            BITS(0,31)                           /*!< Received data from encoder, low 32bit part */

/* EDIM_ENDAT_RDATA1 */
#define EDIM_ENDAT_RDATA1_RDATAH            BITS(0,15)                           /*!< Received data from encoder, high 16bit part */
#define EDIM_ENDAT_RDATA1_CRC               BITS(16,20)                          /*!< CRC for Received data from encoder */
#define EDIM_ENDAT_RDATA1_F1                BIT(21)                              /*!< The safety-relevant error bit (F1) in the received data */
#define EDIM_ENDAT_RDATA1_INVF2             BIT(22)                              /*!< The inverse of the safety-relevant error bit (F2) in the received data */
       
/* EDIM_ENDAT_RDATA2 */     
#define EDIM_ENDAT_RDATA2_DATAADD2          BITS(0,15)                           /*!< data from received additional info 2 */
#define EDIM_ENDAT_RDATA2_MRSADD2           BITS(16,23)                          /*!< MRS code from received additional info 2 */
#define EDIM_ENDAT_RDATA2_CRCADD2           BITS(24,28)                          /*!< CRC from received additional info 2 */
   
/* EDIM_ENDAT_RDATA3 */ 
#define EDIM_ENDAT_RDATA3_DATAADD1          BITS(0,15)                           /*!< data from received additional info 1 */
#define EDIM_ENDAT_RDATA3_MRSADD1           BITS(16,23)                          /*!< MRS code from received additional info 1 */
#define EDIM_ENDAT_RDATA3_CRCADD1           BITS(24,28)                          /*!< CRC from received additional info 1 */
       
/* EDIM_ENDAT_CFG0 */     
#define EDIM_ENDAT_CFG0_HWTRGEN             BIT(0)                               /*!< hardware trigger enable */
#define EDIM_ENDAT_CFG0_DCSEL               BIT(1)                               /*!< data update condition selection */
#define EDIM_ENDAT_CFG0_CTNCLK              BIT(2)                               /*!< continuous clock mode */
#define EDIM_ENDAT_CFG0_DFEN                BIT(3)                               /*!< dma enable */
#define EDIM_ENDAT_CFG0_TCLK                BITS(4,7)                            /*!< transmission clock rate for EnDat */
#define EDIM_ENDAT_CFG0_DATALEN             BITS(8,13)                           /*!< EnDat slave data length */
#define EDIM_ENDAT_CFG0_RSTMSEL             BIT(14)                              /*!< status register reset condition selection */
#define EDIM_ENDAT_CFG0_AUTORST             BIT(15)                              /*!< status register automatic reset enable */
#define EDIM_ENDAT_CFG0_PTIME               BITS(16,23)                          /*!< measured cable propagation time */
#define EDIM_ENDAT_CFG0_PDTCEN              BIT(24)                              /*!< cable propagation time compensation enable */
#define EDIM_ENDAT_CFG0_DFEN_MASK           BITS(25,28)                          /*!< DMA fifo enable mask */
#define EDIM_ENDAT_CFG0_DFEN0               BIT(25)                              /*!< auto load RDATA0 to DMA fifo enable */ 
#define EDIM_ENDAT_CFG0_DFEN1               BIT(26)                              /*!< auto load RDATA1 to DMA fifo enable */
#define EDIM_ENDAT_CFG0_DFEN2               BIT(27)                              /*!< auto load RDATA2 to DMA fifo enable */
#define EDIM_ENDAT_CFG0_DFEN3               BIT(28)                              /*!< auto load RDATA3 to DMA fifo enable */
#define EDIM_ENDAT_CFG0_SWRST               BIT(29)                              /*!< EnDat software reset bit */
#define EDIM_ENDAT_CFG0_FIFOFH              BIT(30)                              /*!< EnDat dma fifo flush bit */
       
/* EDIM_ENDAT_CFG1 */     
#define EDIM_ENDAT_CFG1_PERIOD              BITS(0,7)                            /*!< internal timer trigger period */
#define EDIM_ENDAT_CFG1_PERIOD_7            BIT(7)                               /*!< internal timer trigger period bit7 */
#define EDIM_ENDAT_CFG1_TOTH                BITS(8,15)                           /*!< frame transmission timeout threshold */
#define EDIM_ENDAT_CFG1_TOTH_7              BIT(15)                              /*!< frame transmission timeout threshold bit7 */
#define EDIM_ENDAT_CFG1_RCVTIME3            BITS(16,18)                          /*!< Recovery time III */
#define EDIM_ENDAT_CFG1_FLT                 BITS(19,21)                          /*!< digital filter for data input interface from encoder */
#define EDIM_ENDAT_CFG1_HWTRGDELAY          BITS(24,31)                          /*!< hardware trigger delay */
       
/* EDIM_ENDAT_STAT */       
#define EDIM_ENDAT_STAT_RDATAUPIF           BIT(0)                               /*!< EDIM_ENDAT_RDATA0 and EDIM_ENDAT_RDATA1 registers update interrupt flag */
#define EDIM_ENDAT_STAT_ERR1MIF             BIT(1)                               /*!< error message 1 bit */
#define EDIM_ENDAT_STAT_CRCIF               BIT(2)                               /*!< CRC error for received data */
#define EDIM_ENDAT_STAT_TYPE1IF             BIT(3)                               /*!< type I error interrupt flag */
#define EDIM_ENDAT_STAT_TYPE2IF             BIT(4)                               /*!< type II error interrupt flag */
#define EDIM_ENDAT_STAT_MRSADDRIF           BIT(5)                               /*!< MRS or address error interrupt flag */
#define EDIM_ENDAT_STAT_RDATA2UPIF          BIT(8)                               /*!< EDIM_ENDAT_RDATA2 registers update interrupt flag */
#define EDIM_ENDAT_STAT_RDATA3UPIF          BIT(9)                               /*!< EDIM_ENDAT_RDATA3 registers update interrupt flag */
#define EDIM_ENDAT_STAT_ERR2MIF             BIT(10)                              /*!< error message 2 bit */
#define EDIM_ENDAT_STAT_CRCADD1IF           BIT(11)                              /*!< CRC error for additional info 1 */
#define EDIM_ENDAT_STAT_CRCADD2IF           BIT(12)                              /*!< CRC error for additional info 2 */
#define EDIM_ENDAT_STAT_BUSYMIF             BIT(13)                              /*!< BUSY bit in EnDat protocol */
#define EDIM_ENDAT_STAT_RMMIF               BIT(14)                              /*!< RM bit in EnDat protocol */
#define EDIM_ENDAT_STAT_WRNMIF              BIT(15)                              /*!< WRNM bit in EnDat protocol */
#define EDIM_ENDAT_STAT_SPKIF               BIT(16)                              /*!< spike detection flag */
#define EDIM_ENDAT_STAT_TOIF                BIT(17)                              /*!< frame transmission timeout flag */
#define EDIM_ENDAT_STAT_TYPE3IF             BIT(18)                              /*!< type III error interrupt flag */
#define EDIM_ENDAT_STAT_DTCF                BIT(22)                              /*!< propagation time compensation flag */
#define EDIM_ENDAT_STAT_PTMCF               BIT(23)                              /*!< propagation time measurement complete flag */
#define EDIM_ENDAT_STAT_FIFOOVRIF           BIT(24)                              /*!< dma overrun error flag */
#define EDIM_ENDAT_STAT_FIFOUNRIF           BIT(25)                              /*!< dma underrun error flag */
#define EDIM_ENDAT_STAT_DMATOIF             BIT(26)                              /*!< dma request timeout flag */
#define EDIM_ENDAT_STAT_NEXTRDYF            BIT(30)                              /*!< next transmission ready flag */
#define EDIM_ENDAT_STAT_DATACHKIF           BIT(31)                              /*!< all check have been performed and status is updated */

/* EDIM_ENDAT_INTEN */       
#define EDIM_ENDAT_INTEN_RDATAUPIE          BIT(0)                               /*!< EDIM_ENDAT_RDATA0 and EDIM_ENDAT_RDATA1 registers update interrupt enable */
#define EDIM_ENDAT_INTEN_ERR1IE             BIT(1)                               /*!< error message 1 interrupt enable */
#define EDIM_ENDAT_INTEN_CRCIE              BIT(2)                               /*!< CRC error for received data interrupt enable */
#define EDIM_ENDAT_INTEN_TYPE1IE            BIT(3)                               /*!< type I error interrupt enable */
#define EDIM_ENDAT_INTEN_TYPE2IE            BIT(4)                               /*!< type II error interrupt enable */
#define EDIM_ENDAT_INTEN_MRSADDRIE          BIT(5)                               /*!< MRS code or address  error interrupt enable*/
#define EDIM_ENDAT_INTEN_RDATA2UPIE         BIT(8)                               /*!< EDIM_ENDAT_RDATA2 registers update interrupt enable */
#define EDIM_ENDAT_INTEN_RDATA3UPIE         BIT(9)                               /*!< EDIM_ENDAT_RDATA3 registers update interrupt enable */
#define EDIM_ENDAT_INTEN_ERR2IE             BIT(10)                              /*!< error message 2 interrupt enable */
#define EDIM_ENDAT_INTEN_CRCADD1IE          BIT(11)                              /*!< CRC error for additional info 1 interrupt enable */
#define EDIM_ENDAT_INTEN_CRCADD2IE          BIT(12)                              /*!< CRC error for additional info 2 interrupt enable */
#define EDIM_ENDAT_INTEN_BUSYIE             BIT(13)                              /*!< BUSY bit in EnDat protocol set interrupt enable */
#define EDIM_ENDAT_INTEN_RMIE               BIT(14)                              /*!< RM bit in EnDat protocol set interrupt enable */
#define EDIM_ENDAT_INTEN_WRNIE              BIT(15)                              /*!< WRN bit in EnDat protocol set interrupt enable */
#define EDIM_ENDAT_INTEN_SPKIE              BIT(16)                              /*!< spike detection interrupt enable */
#define EDIM_ENDAT_INTEN_TOIE               BIT(17)                              /*!< frame transmission timeout interrupt enable */
#define EDIM_ENDAT_INTEN_TYPE3IE            BIT(18)                              /*!< type III error interrupt enable */
#define EDIM_ENDAT_INTEN_FIFOOVRIE          BIT(24)                              /*!< dma overrun error interrupt enable */
#define EDIM_ENDAT_INTEN_FIFOUNRIE          BIT(25)                              /*!< dma underrun error interrupt enable */
#define EDIM_ENDAT_INTEN_DMATOIE            BIT(26)                              /*!< dma request timeout interrupt enable */
#define EDIM_ENDAT_INTEN_DATACHKIE          BIT(31)                              /*!< all check have been performed and status is updated interrupt enable */

/* EDIM_ENDAT_SWT */       
#define EDIM_ENDAT_SWT_SWTR                 BIT(0)                               /*!< data transmission software trigger */

/* EDIM_ENDAT_FIFODATA */
#define EDIM_ENDAT_FIFODATA_FIFODATA        BITS(0,31)                           /*!< EDIM_ENDAT FIFO data from EDIM_ENDAT_RDATAx registers */

/* EDIM_ENDAT_STATUPMODE */
#define EDIM_ENDAT_STATUPMODE_BUSYMIFMODE   BIT(0)                               /*!< EDIM_ENDAT BUSYMIF status bit update mode from EDIM_ENDAT_STATUPMODE registers */
#define EDIM_ENDAT_STATUPMODE_RMMIFMODE     BIT(1)                               /*!< EDIM_ENDAT RMMIF status bit update mode from EDIM_ENDAT_STATUPMODE registers */
#define EDIM_ENDAT_STATUPMODE_WRNMIFMODE    BIT(2)                               /*!< EDIM_ENDAT WRNMIF status bit update mode from EDIM_ENDAT_STATUPMODE registers */

/* EDIM_ENDAT interrupt enable or disable */
#define EDIM_ENDAT_INTEN_MASK               ((uint32_t)0x8707FF3FU)
#define EDIM_ENDAT_INT_RDATAUP              EDIM_ENDAT_INTEN_RDATAUPIE           /*!< EDIM_ENDAT_RDATA0 and EDIM_ENDAT_RDATA1 registers update interrupt */
#define EDIM_ENDAT_INT_ERR1                 EDIM_ENDAT_INTEN_ERR1IE              /*!< error message 1 interrupt */
#define EDIM_ENDAT_INT_CRC                  EDIM_ENDAT_INTEN_CRCIE               /*!< CRC error for received data interrupt */
#define EDIM_ENDAT_INT_TYPE1                EDIM_ENDAT_INTEN_TYPE1IE             /*!< type I error interrupt */
#define EDIM_ENDAT_INT_TYPE2                EDIM_ENDAT_INTEN_TYPE2IE             /*!< type II error interrupt */
#define EDIM_ENDAT_INT_MRSADDR              EDIM_ENDAT_INTEN_MRSADDRIE           /*!< MRS code or address  error interrupt enable*/
#define EDIM_ENDAT_INT_RDATA2UP             EDIM_ENDAT_INTEN_RDATA2UPIE          /*!< EDIM_ENDAT_RDATA2 registers update interrupt */
#define EDIM_ENDAT_INT_RDATA3UP             EDIM_ENDAT_INTEN_RDATA3UPIE          /*!< EDIM_ENDAT_RDATA3 registers update interrupt */
#define EDIM_ENDAT_INT_ERR2                 EDIM_ENDAT_INTEN_ERR2IE              /*!< error message 2 interrupt */
#define EDIM_ENDAT_INT_CRCADD1              EDIM_ENDAT_INTEN_CRCADD1IE           /*!< CRC error for additional information 1 interrupt */
#define EDIM_ENDAT_INT_CRCADD2              EDIM_ENDAT_INTEN_CRCADD2IE           /*!< CRC error for additional information 2 interrupt */
#define EDIM_ENDAT_INT_BUSY                 EDIM_ENDAT_INTEN_BUSYIE              /*!< BUSY bit in EnDat protocol set interrupt */
#define EDIM_ENDAT_INT_RM                   EDIM_ENDAT_INTEN_RMIE                /*!< RM bit in EnDat protocol set interrupt */
#define EDIM_ENDAT_INT_WRN                  EDIM_ENDAT_INTEN_WRNIE               /*!< WRN bit in EnDat protocol set interrupt */
#define EDIM_ENDAT_INT_SPIKE                EDIM_ENDAT_INTEN_SPKIE               /*!< spike detection interrupt */
#define EDIM_ENDAT_INT_TO                   EDIM_ENDAT_INTEN_TOIE                /*!< frame transmission timeout interrupt */
#define EDIM_ENDAT_INT_TYPE3                EDIM_ENDAT_INTEN_TYPE3IE             /*!< type III error interrupt */
#define EDIM_ENDAT_INT_FIFOOVR              EDIM_ENDAT_INTEN_FIFOOVRIE           /*!< dma overrun error interrupt */
#define EDIM_ENDAT_INT_FIFOUNR              EDIM_ENDAT_INTEN_FIFOUNRIE           /*!< dma underrun error interrupt */
#define EDIM_ENDAT_INT_DMATO                EDIM_ENDAT_INTEN_DMATOIE             /*!< dma request timeout interrupt */
#define EDIM_ENDAT_INT_DATACHK              EDIM_ENDAT_INTEN_DATACHKIE           /*!< all check have been performed and status is updated interrupt */

/* define the EDIM_ENDAT  bit position and its register index offset */
#define EDIM_ENDAT_REG_VAL(edim_periph, offset)                    (REG32((edim_periph) + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define EDIM_ENDAT_BIT_POS(val)                                    ((uint32_t)(val) & 0x0000001FU)
#define EDIM_ENDAT_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                                  | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define EDIM_ENDAT_REG_VAL2(edim_periph, offset)                   (REG32((edim_periph) + ((uint32_t)(offset) >> 22)))
#define EDIM_ENDAT_BIT_POS2(val)                                   (((uint32_t)(val) & 0x001F0000U) >> 16)

/* EDIM_ENDAT register offset */
#define EDIM_ENDAT_STAT_REG_OFFSET           ((uint32_t)0x0000001CU)                          /*!< EDIM_ENDAT STAT register offset */
#define EDIM_ENDAT_INTEN_REG_OFFSET          ((uint32_t)0x00000020U)                          /*!< EDIM_ENDAT INTEN register offset */

/* EDIM_ENDAT interrupt flag */
typedef enum {
    EDIM_ENDAT_INT_FLAG_RDATAUP  = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 0U, EDIM_ENDAT_STAT_REG_OFFSET, 0U),    /*!< EDIM_ENDAT_RDATA0 and EDIM_ENDAT_RADTA1 registers update interrupt flag */
    EDIM_ENDAT_INT_FLAG_ERR1     = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 1U, EDIM_ENDAT_STAT_REG_OFFSET, 1U),    /*!< error message 1 interrupt flag */
    EDIM_ENDAT_INT_FLAG_CRC      = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 2U, EDIM_ENDAT_STAT_REG_OFFSET, 2U),    /*!< CRC error for received data interrupt flag */
    EDIM_ENDAT_INT_FLAG_TYPE1    = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 3U, EDIM_ENDAT_STAT_REG_OFFSET, 3U),    /*!< type I error interrupt flag */
    EDIM_ENDAT_INT_FLAG_TYPE2    = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 4U, EDIM_ENDAT_STAT_REG_OFFSET, 4U),    /*!< type II error interrupt flag */
    EDIM_ENDAT_INT_FLAG_MRSADDR  = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 5U, EDIM_ENDAT_STAT_REG_OFFSET, 5U),    /*!< MRS code or address  error interrupt enable*/
    EDIM_ENDAT_INT_FLAG_RDATA2UP = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 8U, EDIM_ENDAT_STAT_REG_OFFSET, 8U),    /*!< EDIM_ENDAT_RDATA2 registers update interrupt flag */
    EDIM_ENDAT_INT_FLAG_RDATA3UP = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 9U, EDIM_ENDAT_STAT_REG_OFFSET, 9U),    /*!< EDIM_ENDAT_RDATA3 registers update interrupt flag */
    EDIM_ENDAT_INT_FLAG_ERR2     = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 10U, EDIM_ENDAT_STAT_REG_OFFSET, 10U),  /*!< error message 2 interrupt flag */
    EDIM_ENDAT_INT_FLAG_CRCADD1  = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 11U, EDIM_ENDAT_STAT_REG_OFFSET, 11U),  /*!< CRC error for additional information 1 interrupt flag */
    EDIM_ENDAT_INT_FLAG_CRCADD2  = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 12U, EDIM_ENDAT_STAT_REG_OFFSET, 12U),  /*!< CRC error for additional information 2 interrupt flag */
    EDIM_ENDAT_INT_FLAG_BUSY     = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 13U, EDIM_ENDAT_STAT_REG_OFFSET, 13U),  /*!< BUSY bit in EnDat protocol set interrupt flag */
    EDIM_ENDAT_INT_FLAG_RM       = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 14U, EDIM_ENDAT_STAT_REG_OFFSET, 14U),  /*!< RM bit in EnDat protocol set interrupt flag */
    EDIM_ENDAT_INT_FLAG_WRN      = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 15U, EDIM_ENDAT_STAT_REG_OFFSET, 15U),  /*!< WRN bit in EnDat protocol set interrupt flag */
    EDIM_ENDAT_INT_FLAG_SPIKE    = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 16U, EDIM_ENDAT_STAT_REG_OFFSET, 16U),  /*!< spike detection interrupt flag */
    EDIM_ENDAT_INT_FLAG_TO       = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 17U, EDIM_ENDAT_STAT_REG_OFFSET, 17U),  /*!< frame transmission timeout interrupt flag */
    EDIM_ENDAT_INT_FLAG_TYPE3    = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 18U, EDIM_ENDAT_STAT_REG_OFFSET, 18U),  /*!< type III error interrupt flag */
    EDIM_ENDAT_INT_FLAG_FIFOOVR  = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 24U, EDIM_ENDAT_STAT_REG_OFFSET, 24U),  /*!< dma overrun error interrupt flag */
    EDIM_ENDAT_INT_FLAG_FIFOUNR  = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 25U, EDIM_ENDAT_STAT_REG_OFFSET, 25U),  /*!< dma underrun error interrupt flag */
    EDIM_ENDAT_INT_FLAG_DMATO    = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 26U, EDIM_ENDAT_STAT_REG_OFFSET, 26U),  /*!< dma request timeout interrupt flag */
    EDIM_ENDAT_INT_FLAG_DATACHK  = EDIM_ENDAT_REGIDX_BIT2(EDIM_ENDAT_INTEN_REG_OFFSET, 31U, EDIM_ENDAT_STAT_REG_OFFSET, 31U),  /*!< all check have been performed and status is updated interrupt flag */
} edim_endat_interrupt_flag_enum;

/* EDIM_ENDAT flag */
#define EDIM_ENDAT_FLAG_MASK                ((uint32_t)0xC7C7FF3FU)
#define EDIM_ENDAT_FLAG_RDATAUP             EDIM_ENDAT_STAT_RDATAUPIF            /*!< EDIM_ENDAT_RDATA0 and EDIM_ENDAT_RDATA1 registers update flag */
#define EDIM_ENDAT_FLAG_ERR1                EDIM_ENDAT_STAT_ERR1MIF              /*!< error message 1 flag */
#define EDIM_ENDAT_FLAG_CRC                 EDIM_ENDAT_STAT_CRCIF                /*!< CRC error for received data flag */
#define EDIM_ENDAT_FLAG_TYPE1               EDIM_ENDAT_STAT_TYPE1IF              /*!< type I error interrupt flag */
#define EDIM_ENDAT_FLAG_TYPE2               EDIM_ENDAT_STAT_TYPE2IF              /*!< type II error interrupt flag */
#define EDIM_ENDAT_FLAG_MRSADDR             EDIM_ENDAT_STAT_MRSADDRIF            /*!< MRS or address error interrupt flag */
#define EDIM_ENDAT_FLAG_RDATA2UP            EDIM_ENDAT_STAT_RDATA2UPIF           /*!< EDIM_ENDAT_RDATA2 registers update interrupt flag */
#define EDIM_ENDAT_FLAG_RDATA3UP            EDIM_ENDAT_STAT_RDATA3UPIF           /*!< EDIM_ENDAT_RDATA3 registers update interrupt flag */
#define EDIM_ENDAT_FLAG_ERR2                EDIM_ENDAT_STAT_ERR2MIF              /*!< error message 2 flag */
#define EDIM_ENDAT_FLAG_CRCADD1             EDIM_ENDAT_STAT_CRCADD1IF            /*!< CRC error for additional information 1 flag */
#define EDIM_ENDAT_FLAG_CRCADD2             EDIM_ENDAT_STAT_CRCADD2IF            /*!< CRC error for additional information 2 flag */
#define EDIM_ENDAT_FLAG_BUSY                EDIM_ENDAT_STAT_BUSYMIF              /*!< BUSY bit in EnDat protocol */
#define EDIM_ENDAT_FLAG_RM                  EDIM_ENDAT_STAT_RMMIF                /*!< RM bit in EnDat protocol */
#define EDIM_ENDAT_FLAG_WRN                 EDIM_ENDAT_STAT_WRNMIF               /*!< WRN bit in EnDat protocol */
#define EDIM_ENDAT_FLAG_SPIKE               EDIM_ENDAT_STAT_SPKIF                /*!< spike detection flag */
#define EDIM_ENDAT_FLAG_TO                  EDIM_ENDAT_STAT_TOIF                 /*!< frame transmission timeout flag */
#define EDIM_ENDAT_FLAG_TYPE3               EDIM_ENDAT_STAT_TYPE3IF              /*!< type III error interrupt flag */
#define EDIM_ENDAT_FLAG_DTC                 EDIM_ENDAT_STAT_DTCF                 /*!< propagation time compensation flag */
#define EDIM_ENDAT_FLAG_PTMC                EDIM_ENDAT_STAT_PTMCF                /*!< propagation time measurement complete flag */
#define EDIM_ENDAT_FLAG_FIFOOVR             EDIM_ENDAT_STAT_FIFOOVRIF            /*!< dma overrun error flag */
#define EDIM_ENDAT_FLAG_FIFOUNR             EDIM_ENDAT_STAT_FIFOUNRIF            /*!< dma underrun error flag */
#define EDIM_ENDAT_FLAG_DMATO               EDIM_ENDAT_STAT_DMATOIF              /*!< dma request timeout flag */
#define EDIM_ENDAT_FLAG_NEXTRDY             EDIM_ENDAT_STAT_NEXTRDYF             /*!< next transmission ready flag */
#define EDIM_ENDAT_FLAG_DATACHK             EDIM_ENDAT_STAT_DATACHKIF            /*!< all check have been performed and status is updated flag */

/* constants definitions */
/* EnDat  parameter struct definitions */
typedef struct
{   
    uint32_t clk_rate;                                                      /*!< configure transmission clock rate */
    uint32_t recovery_time;                                                 /*!< configure recovery time III */
    uint32_t filter;                                                        /*!< configure digital filter cycle width */
    uint32_t watchdog_value;                                                /*!< configure timeout length */
}edim_endat_parameter_struct;

typedef struct
{   
    uint8_t crc;                                                            /*!< CRC value from additional info */
    uint8_t mrs_addr;                                                       /*!< MRS code or address from additional info */
    uint16_t data;                                                          /*!< data from additional info */
}edim_endat_additional_info_struct;

#define EDIM_ENDAT_MODE_GET_POS                             ((uint8_t)0x07)        /*!< Encoder to send position values */
#define EDIM_ENDAT_MODE_SEND_POS_ADD_INFO_SELECT_MEM_AREA   ((uint8_t)0x09)        /*!< Encoder to send position values with additional information and selection of memory area or of the additional information  */
#define EDIM_ENDAT_MODE_SELECT_MEM_AREA                     ((uint8_t)0x0E)        /*!< Selection of memory area  */
#define EDIM_ENDAT_MODE_RECEIVE_COMM_CMD                    ((uint8_t)0x12)        /*!< Encoder to receive communication command */
#define EDIM_ENDAT_MODE_SEND_TEST_VALUE                     ((uint8_t)0x15)        /*!< Encoder to send test values  */
#define EDIM_ENDAT_MODE_SEND_POS_ADD_INFO_RECEIVE_PARA      ((uint8_t)0x1B)        /*!< Encoder to send position values with additional information and receive parameters */
#define EDIM_ENDAT_MODE_RECEIVE_PARA                        ((uint8_t)0x1C)        /*!< Encoder to receive parameters */
#define EDIM_ENDAT_MODE_SEND_PARA                           ((uint8_t)0x23)        /*!< Encoder to send parameters  */
#define EDIM_ENDAT_MODE_SEND_POS_ADD_INFO_PARA              ((uint8_t)0x24)        /*!< Encoder to send position values with additional information and send parameters */
#define EDIM_ENDAT_MODE_RECEIVE_RESET                       ((uint8_t)0x2A)        /*!< Encoder to receive reset */
#define EDIM_ENDAT_MODE_SEND_POS_ADD_INFO_RECEIVE_ERR_RESET ((uint8_t)0x2D)        /*!< Encoder to send position values with additional information and receive error reset */
#define EDIM_ENDAT_MODE_RECEIVE_TEST_CMD                    ((uint8_t)0x31)        /*!< Encoder to receive test command  */
#define EDIM_ENDAT_MODE_SEND_POS_ADD_INFO_RECEIVE_TEST_CMD  ((uint8_t)0x36)        /*!< Encoder to send position values with additional information and receive test command */
#define EDIM_ENDAT_MODE_SEND_POS_ADD_INFO                   ((uint8_t)0x38)        /*!< Encoder to send position values with additional information */

/* EnDat transmission clock rate */
#define CFG0_TCLK(regval)                                   (BITS(4, 7) & ((uint32_t)(regval) << 4))
#define EDIM_ENDAT_TCLK_16_67MHz                            CFG0_TCLK(0)                         /*!< EnDat transmission clock 16.67MHz */
#define EDIM_ENDAT_TCLK_8_33MHz                             CFG0_TCLK(6)                         /*!< EnDat transmission clock 8.33MHz */
#define EDIM_ENDAT_TCLK_4_16MHz                             CFG0_TCLK(11)                        /*!< EnDat transmission clock 4.16MHz */
#define EDIM_ENDAT_TCLK_2MHz                                CFG0_TCLK(12)                        /*!< EnDat transmission clock 2MHz */
#define EDIM_ENDAT_TCLK_1MHz                                CFG0_TCLK(13)                        /*!< EnDat transmission clock 1MHz */
#define EDIM_ENDAT_TCLK_200KHz                              CFG0_TCLK(14)                        /*!< EnDat transmission clock 200KHz */
#define EDIM_ENDAT_TCLK_100KHz                              CFG0_TCLK(15)                        /*!< EnDat transmission clock 100KHz */

/* EnDat position data length */
#define CFG0_DWLG(regval)                                   (BITS(8, 13) & ((uint32_t)(regval) << 8))
#define EDIM_ENDAT_DWLG_nBIT(n)                             CFG0_DWLG(n)                         /*!< encoder data length */

/* EnDat reset moment selection */
#define CFG0_RSTMSEL(regval)                                (BIT(14) & ((uint32_t)(regval) << 14))
#define EDIM_ENDAT_RESET_MOMENT_ANY                         CFG0_RSTMSEL(0)                      /*!< The EDIM_ENDAT_STAT register can be reset by software at any time */
#define EDIM_ENDAT_RESET_MOMENT_UPDATE                      CFG0_RSTMSEL(1)                      /*!< The EDIM_ENDAT_STAT register must be reset by software after EDIM_ENDAT_STAT register is fully updated */

/* EnDat internal timer period time step */
#define EDIM_ENDAT_PERIOD_STEP_2us                          ((uint32_t)0x00000000U)              /*!< configure internal timer step length 2us */
#define EDIM_ENDAT_PERIOD_STEP_200us                        EDIM_ENDAT_CFG1_PERIOD_7             /*!< configure internal timer step length 200us */

/* EnDat internal timer period time */
#define CFG1_PERIOD(regval)                                 (BITS(0, 6) & ((uint32_t)(regval) << 0))
#define EDIM_ENDAT_PERIOD_DISABLE                           CFG1_PERIOD(0)                                   /*!< disable internal timer */
#define EDIM_ENDAT_PERIOD_n_2us(n)                          CFG1_PERIOD(n)                                   /*!< configure internal timer trigger period as n * 2us */
#define EDIM_ENDAT_PERIOD_n_200us(n)                        (CFG1_PERIOD(n) | EDIM_ENDAT_CFG1_PERIOD_7)      /*!< configure internal timer trigger period as n * 200us */

/* EnDat continuous mode */
#define EDIM_ENDAT_CONTINUOUS_DISABLE                       ((uint32_t)0x00000000U)              /*!< continuous clock disable */
#define EDIM_ENDAT_CONTINUOUS_ENABLE                        EDIM_ENDAT_CFG0_CTNCLK               /*!< continuous clock enable */

/* EnDat frame transmission timeout threshold step length */
#define EDIM_ENDAT_TOTH_STEP_2us                            ((uint32_t)0x00000000U)              /*!< configure frame transmission timeout threshold step length 2us */
#define EDIM_ENDAT_TOTH_STEP_200us                          EDIM_ENDAT_CFG1_TOTH_7               /*!< configure frame transmission timeout threshold step length 200us */

/* EnDat frame transmission timeout threshold */
#define CFG1_TOTH(regval)                                   (BITS(8, 14) & ((uint32_t)(regval) << 8))
#define EDIM_ENDAT_TOTH_STOP                                CFG1_TOTH(0)                                     /*!< disable timeout detection */
#define EDIM_ENDAT_TOTH_n_2us(n)                            CFG1_TOTH(n)                                     /*!< configure timeout threshold as n * 2us */
#define EDIM_ENDAT_TOTH_n_200us(n)                          (CFG1_TOTH(n) | EDIM_ENDAT_CFG1_TOTH_7)          /*!< configure timeout threshold as n * 200us */

/* EnDat recovery timer III */
#define CFG1_RCVTIME(regval)                                (BITS(16, 18) & ((uint32_t)(regval) << 16))
#define EDIM_ENDAT_RECOVERY_III_1_2_TCLK                    CFG1_RCVTIME(0)                      /*!< recovery time III 1/2 Tclk */
#define EDIM_ENDAT_RECOVERY_III_0_5us                       CFG1_RCVTIME(1)                      /*!< recovery time III 0.5us */
#define EDIM_ENDAT_RECOVERY_III_1us                         CFG1_RCVTIME(2)                      /*!< recovery time III 1us */
#define EDIM_ENDAT_RECOVERY_III_1_5us                       CFG1_RCVTIME(3)                      /*!< recovery time III 1.5us */
#define EDIM_ENDAT_RECOVERY_III_2us                         CFG1_RCVTIME(4)                      /*!< recovery time III 2us */
#define EDIM_ENDAT_RECOVERY_III_4us                         CFG1_RCVTIME(5)                      /*!< recovery time III 4us */
#define EDIM_ENDAT_RECOVERY_III_8us                         CFG1_RCVTIME(6)                      /*!< recovery time III 8us */
#define EDIM_ENDAT_RECOVERY_III_10us                        CFG1_RCVTIME(7)                      /*!< recovery time III 10us */

/* EnDat digital filter */
#define CFG1_FILTER(regval)                                 (BITS(19, 21) & ((uint32_t)(regval) << 19))
#define EDIM_ENDAT_FILTER_DISABLE                           CFG1_FILTER(0)                       /*!< disable digital filter for data input*/
#define EDIM_ENDAT_FILTER_3CYCLE                            CFG1_FILTER(1)                       /*!< digital filter for data input 3 cycles */
#define EDIM_ENDAT_FILTER_4CYCLE                            CFG1_FILTER(2)                       /*!< digital filter for data input 4 cycles */
#define EDIM_ENDAT_FILTER_5CYCLE                            CFG1_FILTER(3)                       /*!< digital filter for data input 5 cycles */
#define EDIM_ENDAT_FILTER_6CYCLE                            CFG1_FILTER(4)                       /*!< digital filter for data input 6 cycles */
#define EDIM_ENDAT_FILTER_10CYCLE                           CFG1_FILTER(5)                       /*!< digital filter for data input 10 cycles */
#define EDIM_ENDAT_FILTER_20CYCLE                           CFG1_FILTER(6)                       /*!< digital filter for data input 20 cycles */
#define EDIM_ENDAT_FILTER_40CYCLE                           CFG1_FILTER(7)                       /*!< digital filter for data input 40 cycles */

/* EnDat hardware trigger */
#define CFG1_HWTRGDLY(regval)                               (BITS(24, 31) & ((uint32_t)(regval) << 24))
#define EDIM_ENDAT_HWTRGDLY_DISABLE                         CFG1_HWTRGDLY(0)                     /*!< disable hardware trigger delay */
#define EDIM_ENDAT_HWTRGDLY_nCYCLE(n)                       CFG1_HWTRGDLY(n)                     /*!< hardware trigger delay n * EnDat cycles */

/* EnDat DMA enable */
#define EDIM_ENDAT_DMA_SEL_RDATA0                           EDIM_ENDAT_CFG0_DFEN0                /*!< select to load RDATA0 into DMA FIFO */
#define EDIM_ENDAT_DMA_SEL_RDATA1                           EDIM_ENDAT_CFG0_DFEN1                /*!< select to load RDATA1 into DMA FIFO */
#define EDIM_ENDAT_DMA_SEL_RDATA2                           EDIM_ENDAT_CFG0_DFEN2                /*!< select to load RDATA2 into DMA FIFO */
#define EDIM_ENDAT_DMA_SEL_RDATA3                           EDIM_ENDAT_CFG0_DFEN3                /*!< select to load RDATA3 into DMA FIFO */

/* Endat status update mode */
#define EDIM_ENDAT_STAT_DYNAMIC                             (uint32_t)(0x00000000U)              /*!< EDIM_ENDAT status dynamic update mode */
#define EDIM_ENDAT_STAT_STATIC                              (uint32_t)(0x00000001U)              /*!< EDIM_ENDAT status static update mode */

/* function declarations */
/* EDIM_ENDAT initialization functions */
/* reset EDIM_ENDAT */
void edim_endat_deinit(void);
/* initialize EDIM_ENDAT parameter struct with a default value */
void edim_endat_parameter_struct_para_init(edim_endat_parameter_struct *initpara);
/* initialize EnDat config */
void edim_endat_init(edim_endat_parameter_struct* init_struct);
/* configure EnDat slave data length */
void edim_endat_data_length(uint32_t clk_pulse);
/* enable EnDat auto reset */
void edim_endat_auto_reset_enable(void);
/* disable EnDat auto reset */
void edim_endat_auto_reset_disable(void);
/* enable EnDat continue clock */
void edim_endat_continue_clock_enable(void);
/* disable EnDat continue clock */
void edim_endat_continue_clock_disable(void);
/* enable unconditional data update */
void edim_endat_update_unconditional_data_enable(void);
/* disable unconditional data update */
void edim_endat_update_unconditional_data_disable(void);
/* enable cable propagation compensation for EnDat */
void edim_endat_cable_propagation_compensation_enable(void);
/* disable cable propagation compensation for EnDat */
void edim_endat_cable_propagation_compensation_disable(void);
/* write cable propagation time for EnDat */
void edim_endat_cable_propagation_time_write(uint8_t time);
/* read cable propagation time for EnDat */
uint8_t edim_endat_cable_propagation_time_read(void);
/* configure reset moment for EnDat */
void edim_endat_reset_moment_select(uint32_t moment);

/* EDIM_ENDAT communication functions */
/* configure EnDat command */
void edim_endat_command(uint32_t mode, uint32_t mrs_addr, uint32_t para);
/* start a frame transmit by software */
void edim_endat_data_transmission_software_trigger(void);
/* reset all registers of EnDat by software */
void edim_endat_software_reset(void);
/* configure EnDat hardware trigger */
void edim_endat_hardware_trigger_config(EventStatus newstatus);
/* configure EnDat hardware trigger delay */
void edim_endat_hardware_trigger_delay_config(uint32_t delay);
/* configure EnDat internal timer trigger period */
void edim_endat_internal_timer_trigger_period_config(uint32_t period);
/* enable EnDat DMA */
void edim_endat_dma_enable(void);
/* disable EnDat DMA */
void edim_endat_dma_disable(void);
/* flush EnDat DMA FIFO */
void edim_endat_dma_flush(void);
/* select EnDat data to DMA FIFO */
void edim_endat_dma_select(uint32_t reg_selected);
/* read EnDat slave data with low 32bit */
uint32_t edim_endat_data_low_read(void);
/* read EnDat encoder data */
uint64_t edim_endat_data_read(void);
/* read EnDat CRC bit in the received data */
uint8_t edim_endat_crc_of_data_read(void);
/* read EnDat F1 bit in the received data */
uint8_t edim_endat_f1_of_data_read(void);
/* read EnDat inverse of F2 bit in the received data */
uint8_t edim_endat_inverse_f2_of_data_read(void);
/* read EnDat encoder data from additional information 1 */
uint16_t edim_endat_additional_info_1_data_read(void);
/* read EnDat encoder data from additional information 2 */
uint16_t edim_endat_additional_info_2_data_read(void);
/* initialize EDIM_ENDAT additional information struct with a default value */
void edim_endat_additional_info_struct_para_init(edim_endat_additional_info_struct *initpara);
/* read entire EnDat encoder additional information 1 */
void edim_endat_additional_info_1_read(edim_endat_additional_info_struct* add_info);
/* read entire EnDat encoder additional information 2 */
void edim_endat_additional_info_2_read(edim_endat_additional_info_struct* add_info);

/* EnDat interrupt and flag */
/* configure EDIM_ENDAT status update mode */
void edim_endat_status_update_mode_config(uint32_t flag, uint32_t mode);
/* enable the EnDat interrupt */
void edim_endat_interrupt_enable(uint32_t interrupt);
/* disable the EnDat interrupt */
void edim_endat_interrupt_disable(uint32_t interrupt);
/* get EnDat flag */
FlagStatus edim_endat_flag_get(uint32_t flag);
/* clear EnDat flag */
void edim_endat_flag_clear(uint32_t flag);
/* get EnDat interrupt flag */
FlagStatus edim_endat_interrupt_flag_get(edim_endat_interrupt_flag_enum int_flag);
/* clear EnDat interrupt flag */
void edim_endat_interrupt_flag_clear(edim_endat_interrupt_flag_enum int_flag);

#endif /* GD32H77X_78X_EDIM_ENDAT_H */
