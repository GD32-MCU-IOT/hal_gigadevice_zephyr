/*!
    \file    gd32h77x_78x_edim_tfmt.h
    \brief   definitions for the EDIM_TFMT

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

#ifndef GD32H77X_78X_EDIM_TFMT_H
#define GD32H77X_78X_EDIM_TFMT_H

#include "gd32h77x_78x.h"

/* EDIM definitions */
#define EDIM_TFMT                           (EDIM_BASE + 0x00000400U)                       /*!< EDIM_TFMT base address */          

/* registers definitions */
#define EDIM_TFMT_DATAID                    REG32(EDIM_TFMT + 0x00000000U)                  /*!< EDIM_TFMT data ID register */
#define EDIM_TFMT_EEPROM                    REG32(EDIM_TFMT + 0x00000004U)                  /*!< EDIM_TFMT romdata register */
#define EDIM_TFMT_CFG                       REG32(EDIM_TFMT + 0x00000008U)                  /*!< EDIM_TFMT configuration register */
#define EDIM_TFMT_SWT                       REG32(EDIM_TFMT + 0x0000000CU)                  /*!< EDIM_TFMT software trigger register */
#define EDIM_TFMT_STAT                      REG32(EDIM_TFMT + 0x00000010U)                  /*!< EDIM_TFMT state register */
#define EDIM_TFMT_INTEN                     REG32(EDIM_TFMT + 0x00000014U)                  /*!< EDIM_TFMT interrupt enable register */
#define EDIM_TFMT_RDATA(x)                  REG32(EDIM_TFMT + 0x00000018U + 0x04U * (x))    /*!< EDIM_TFMT receive data register */
#define EDIM_TFMT_FIFODATA                  REG32(EDIM_TFMT + 0x00000128U)                  /*!< EDIM_TFMT FIFO data register */
#define EDIM_TFMT_STATUPMODE                REG32(EDIM_TFMT + 0x00000200U)                  /*!< EDIM_TFMT status update mode register */

/* bits definitions */
/* EDIM_TFMT_DATAID */
#define EDIM_TFMT_DATAID_CC                 BITS(0, 3)                                      /*!< EDIM_TFMT data ID code */

/* EDIM_TFMT_EEPROM */
#define EDIM_TFMT_EEPROM_EEPROMDATA         BITS(0, 7)                                      /*!< EDIM_TFMT data to be written into EEPROM of encoder */
#define EDIM_TFMT_EEPROM_EEPROMADDR         BITS(8, 14)                                     /*!< EDIM_TFMT EEPROM accessing address of encoder */

/* EDIM_TFMT_CFG */
#define EDIM_TFMT_CFG_TRANSTSEL             BIT(0)                                          /*!< EDIM_TFMT transmission start trigger selection */
#define EDIM_TFMT_CFG_DFEN                  BIT(16)                                         /*!< EDIM_TFMT DMA request and FIFO enable */
#define EDIM_TFMT_CFG_FIFOFH                BIT(17)                                         /*!< EDIM_TFMT FIFO flush */
#define EDIM_TFMT_CFG_DFEN_MASK             BITS(20,23)                                     /*!< EDIM_TFMT DMA enable mask */
#define EDIM_TFMT_CFG_DFEN0                 BIT(20)                                         /*!< EDIM_TFMT DMA request and FIFO enable for EDIM_TFMT_RDATA0 register */
#define EDIM_TFMT_CFG_DFEN1                 BIT(21)                                         /*!< EDIM_TFMT DMA request and FIFO enable for EDIM_TFMT_RDATA1 register */
#define EDIM_TFMT_CFG_DFEN2                 BIT(22)                                         /*!< EDIM_TFMT DMA request and FIFO enable for EDIM_TFMT_RDATA2 register */
#define EDIM_TFMT_CFG_DFEN3                 BIT(23)                                         /*!< EDIM_TFMT DMA request and FIFO enable for EDIM_TFMT_RDATA3 register */

/* EDIM_TFMT_SWT */
#define EDIM_TFMT_SWT_SWTR                  BIT(0)                                          /*!< EDIM_TFMT data transmission software trigger */

/* EDIM_TFMT_STAT */
#define EDIM_TFMT_STAT_EOC                  BIT(0)                                          /*!< EDIM_TFMT end of communication */
#define EDIM_TFMT_STAT_TBUSYF               BIT(1)                                          /*!< EDIM_TFMT transmit busy flag */
#define EDIM_TFMT_STAT_RBUSYF               BIT(2)                                          /*!< EDIM_TFMT receive busy flag */
#define EDIM_TFMT_STAT_TOIF                 BIT(3)                                          /*!< EDIM_TFMT encoder transmission timeout error interrupt flag */
#define EDIM_TFMT_STAT_CRCIF                BIT(4)                                          /*!< EDIM_TFMT CRC error interrupt flag in received frame */
#define EDIM_TFMT_STAT_SDELIF               BIT(5)                                          /*!< EDIM_TFMT Start bit error interrupt flag or delimiter error flag in received frame */
#define EDIM_TFMT_STAT_PCTLIF               BIT(6)                                          /*!< EDIM_TFMT parity error interrupt flag in received control field of frame */
#define EDIM_TFMT_STAT_CCIF                 BIT(7)                                          /*!< EDIM_TFMT data ID code error interrupt flag */
#define EDIM_TFMT_STAT_EEPROMBUSYIF         BIT(8)                                          /*!< EDIM_TFMT EEPROM busy interrupt flag */
#define EDIM_TFMT_STAT_DELIF                BIT(9)                                          /*!< EDIM_TFMT delimiter error interrupt flag in request frame */
#define EDIM_TFMT_STAT_PREQIF               BIT(10)                                         /*!< EDIM_TFMT parity error interrupt flag in request frame */
#define EDIM_TFMT_STAT_ALRMIF               BIT(11)                                         /*!< EDIM_TFMT alarm interrupt flag of encoder */
#define EDIM_TFMT_STAT_CNTIF                BIT(12)                                         /*!< EDIM_TFMT counting error interrupt flag of encoder */
#define EDIM_TFMT_STAT_FIFOOVRIF            BIT(16)                                         /*!< EDIM_TFMT FIFO overrun error interrupt flag */
#define EDIM_TFMT_STAT_FIFOUNRIF            BIT(17)                                         /*!< EDIM_TFMT FIFO underrun error interrupt flag */
#define EDIM_TFMT_STAT_DMATOIF              BIT(18)                                         /*!< EDIM_TFMT DMA request timeout error interrupt flag */

/* EDIM_TFMT_INTEN */
#define EDIM_TFMT_INTEN_EOCIE               BIT(0)                                          /*!< EDIM_TFMT interrupt enable for EOC */
#define EDIM_TFMT_INTEN_TOIE                BIT(3)                                          /*!< EDIM_TFMT interrupt enable for TOIF */
#define EDIM_TFMT_INTEN_CRCIE               BIT(4)                                          /*!< EDIM_TFMT interrupt enable for CRCIF */
#define EDIM_TFMT_INTEN_SDELIE              BIT(5)                                          /*!< EDIM_TFMT interrupt enable for SDELIF */
#define EDIM_TFMT_INTEN_PCTLIE              BIT(6)                                          /*!< EDIM_TFMT interrupt enable for PCTLIF */
#define EDIM_TFMT_INTEN_CCIE                BIT(7)                                          /*!< EDIM_TFMT interrupt enable for CCIF */
#define EDIM_TFMT_INTEN_EEPROMBUSYIE        BIT(8)                                          /*!< EDIM_TFMT interrupt enable for EEPROMBUSYIF */
#define EDIM_TFMT_INTEN_DELIE               BIT(9)                                          /*!< EDIM_TFMT interrupt enable for DELIF */
#define EDIM_TFMT_INTEN_PREQIE              BIT(10)                                         /*!< EDIM_TFMT interrupt enable for PREQIF */
#define EDIM_TFMT_INTEN_ALRMIE              BIT(11)                                         /*!< EDIM_TFMT interrupt enable for ALRMIF */
#define EDIM_TFMT_INTEN_CNTIE               BIT(12)                                         /*!< EDIM_TFMT interrupt enable for CNTIF */
#define EDIM_TFMT_INTEN_FIFOOVRIE           BIT(16)                                         /*!< EDIM_TFMT interrupt enable of FIFOOVRIF */
#define EDIM_TFMT_INTEN_FIFOUNRIE           BIT(17)                                         /*!< EDIM_TFMT interrupt enable of FIFOUNRIF */
#define EDIM_TFMT_INTEN_DMATOIE             BIT(18)                                         /*!< EDIM_TFMT interrupt enable of DMATOIF */

/* constants definitions */
/* EDIM_TFMT_RDATAx */
#define EDIM_TFMT_RDATA_RDATA               BITS(0, 31)                                     /*!< EDIM_TFMT received data from encoder */

/* EDIM_TFMT_FIFODATA */
#define EDIM_TFMT_FIFODATA_FIFODATA         BITS(0, 31)                                     /*!< EDIM_TFMT FIFO data from TFMT_RDATAx registers */

/* EDIM_TFMT_STATUPMODE */
#define EDIM_TFMT_STATUPMODE_STATUPMODE     BIT(0)                                          /*!< EDIM_TFMT status update mode from TFMT_STATUPMODE register */
                                                                                           
/* constants definitions */
/* EDIM_TFMT communication command code */
#define DATAID_CC(regval)                   (BITS(0,3) & (uint32_t)(regval))
#define EDIM_TFMT_DATAID_CC_RDPOS           DATAID_CC(0)                                    /*!< read absolute data in one revolution */
#define EDIM_TFMT_DATAID_CC_RDTURNS         DATAID_CC(1)                                    /*!< read multi-turn data */
#define EDIM_TFMT_DATAID_CC_RDENID          DATAID_CC(2)                                    /*!< read ENID */
#define EDIM_TFMT_DATAID_CC_RDALL           DATAID_CC(3)                                    /*!< read all data */
#define EDIM_TFMT_DATAID_CC_WRROM           DATAID_CC(6)                                    /*!< write EEPROM */
#define EDIM_TFMT_DATAID_CC_RSTERR          DATAID_CC(7)                                    /*!< reset all errors */
#define EDIM_TFMT_DATAID_CC_RSTPOS          DATAID_CC(8)                                    /*!< reset one revolution data */
#define EDIM_TFMT_DATAID_CC_RSTTURNSERR     DATAID_CC(12)                                   /*!< reset multi-turn data and all errors */
#define EDIM_TFMT_DATAID_CC_RDROM           DATAID_CC(13)                                   /*!< read EEPROM */

/* EDIM_TFMT eeprom */
#define EEPROMDATA(regval)                  (BITS(0,7) & (uint32_t)(regval))                /*!< eeprom write data */
#define EEPROMADDR(regval)                  (BITS(8,14) & ((uint32_t)(regval) << 8))        /*!< eeprom write address */

/* EDIM_TFMT interrupt enable or disable */
#define EDIM_TFMT_INTEN_MASK                ((uint32_t)0x00071FF9U)
#define EDIM_TFMT_INT_EOC                   EDIM_TFMT_INTEN_EOCIE                           /*!< end of communication interrupt enable */
#define EDIM_TFMT_INT_TOERR                 EDIM_TFMT_INTEN_TOIE                            /*!< timeout error interrupt enable */
#define EDIM_TFMT_INT_CRC                   EDIM_TFMT_INTEN_CRCIE                           /*!< crc error interrupt enable */
#define EDIM_TFMT_INT_SDEL                  EDIM_TFMT_INTEN_SDELIE                          /*!< frame error in received frame interrupt enable */
#define EDIM_TFMT_INT_PCTL                  EDIM_TFMT_INTEN_PCTLIE                          /*!< parity error in received frame interrupt enable*/
#define EDIM_TFMT_INT_CC                    EDIM_TFMT_INTEN_CCIE                            /*!< data ID error interrupt enable */
#define EDIM_TFMT_INT_EEPROMBUSY            EDIM_TFMT_INTEN_EEPROMBUSYIE                    /*!< eeprom busy interrupt enable */
#define EDIM_TFMT_INT_DEL                   EDIM_TFMT_INTEN_DELIE                           /*!< frame error in request frame interrupt enable */
#define EDIM_TFMT_INT_PREQ                  EDIM_TFMT_INTEN_PREQIE                          /*!< parity error in request frame interrupt enable */
#define EDIM_TFMT_INT_ALRM                  EDIM_TFMT_INTEN_ALRMIE                          /*!< alarm interrupt enable*/
#define EDIM_TFMT_INT_CNT                   EDIM_TFMT_INTEN_CNTIE                           /*!< counting error interrupt enable */
#define EDIM_TFMT_INT_FIFOOVR               EDIM_TFMT_INTEN_FIFOOVRIE                       /*!< FIFO overrun error interrupt enable */
#define EDIM_TFMT_INT_FIFOUNR               EDIM_TFMT_INTEN_FIFOUNRIE                       /*!< FIFO underrun error interrupt enable */
#define EDIM_TFMT_INT_DMATO                 EDIM_TFMT_INTEN_DMATOIE                         /*!< DMA request timeout error interrupt enable */

/* define the EDIM_TFMT  bit position and its register index offset */
#define EDIM_TFMT_REG_VAL(edim_periph, offset)                    (REG32((edim_periph) + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define EDIM_TFMT_BIT_POS(val)                                    ((uint32_t)(val) & 0x0000001FU)
#define EDIM_TFMT_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                                  | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define EDIM_TFMT_REG_VAL2(edim_periph, offset)                   (REG32((edim_periph) + ((uint32_t)(offset) >> 22)))
#define EDIM_TFMT_BIT_POS2(val)                                   (((uint32_t)(val) & 0x001F0000U) >> 16)

/* EDIM_TFMT register offset */
#define EDIM_TFMT_INTEN_REG_OFFSET          ((uint32_t)0x00000014U)                          /*!< INTEN register offset */
#define EDIM_TFMT_STAT_REG_OFFSET           ((uint32_t)0x00000010U)                          /*!< STAT register offset */

/* EDIM_TFMT interrupt flags */
typedef enum {
    EDIM_TFMT_INT_FLAG_EOC = EDIM_TFMT_REGIDX_BIT2(EDIM_TFMT_INTEN_REG_OFFSET, 0U, EDIM_TFMT_STAT_REG_OFFSET, 0U),            /*!< end of communication interrupt flag */
    EDIM_TFMT_INT_FLAG_TOERR =  EDIM_TFMT_REGIDX_BIT2(EDIM_TFMT_INTEN_REG_OFFSET, 3U, EDIM_TFMT_STAT_REG_OFFSET, 3U),         /*!< timeout error interrupt flag */
    EDIM_TFMT_INT_FLAG_CRC = EDIM_TFMT_REGIDX_BIT2(EDIM_TFMT_INTEN_REG_OFFSET, 4U, EDIM_TFMT_STAT_REG_OFFSET, 4U),            /*!< crc error interrupt flag */
    EDIM_TFMT_INT_FLAG_SDEL = EDIM_TFMT_REGIDX_BIT2(EDIM_TFMT_INTEN_REG_OFFSET, 5U, EDIM_TFMT_STAT_REG_OFFSET, 5U),           /*!< frame error in received frame interrupt flag */
    EDIM_TFMT_INT_FLAG_PCTL = EDIM_TFMT_REGIDX_BIT2(EDIM_TFMT_INTEN_REG_OFFSET, 6U, EDIM_TFMT_STAT_REG_OFFSET, 6U),           /*!< parity error in received frame interrupt flag*/
    EDIM_TFMT_INT_FLAG_CC  = EDIM_TFMT_REGIDX_BIT2(EDIM_TFMT_INTEN_REG_OFFSET, 7U, EDIM_TFMT_STAT_REG_OFFSET, 7U),            /*!< data ID error interrupt flag */
    EDIM_TFMT_INT_FLAG_EEPROMBUSY = EDIM_TFMT_REGIDX_BIT2(EDIM_TFMT_INTEN_REG_OFFSET, 8U, EDIM_TFMT_STAT_REG_OFFSET, 8U),     /*!< eeprom busy interrupt flag */
    EDIM_TFMT_INT_FLAG_DEL = EDIM_TFMT_REGIDX_BIT2(EDIM_TFMT_INTEN_REG_OFFSET, 9U, EDIM_TFMT_STAT_REG_OFFSET, 9U),            /*!< frame error in request frame interrupt flag */
    EDIM_TFMT_INT_FLAG_PREQ = EDIM_TFMT_REGIDX_BIT2(EDIM_TFMT_INTEN_REG_OFFSET, 10U, EDIM_TFMT_STAT_REG_OFFSET, 10U),         /*!< parity error in request frame interrupt flag */
    EDIM_TFMT_INT_FLAG_ALRM = EDIM_TFMT_REGIDX_BIT2(EDIM_TFMT_INTEN_REG_OFFSET, 11U, EDIM_TFMT_STAT_REG_OFFSET, 11U),         /*!< alarm interrupt flag*/
    EDIM_TFMT_INT_FLAG_CNT = EDIM_TFMT_REGIDX_BIT2(EDIM_TFMT_INTEN_REG_OFFSET, 12U, EDIM_TFMT_STAT_REG_OFFSET, 12U),          /*!< counting error interrupt flag */
    EDIM_TFMT_INT_FLAG_FIFOOVR = EDIM_TFMT_REGIDX_BIT2(EDIM_TFMT_INTEN_REG_OFFSET, 16U, EDIM_TFMT_STAT_REG_OFFSET, 16U),      /*!< FIFO overrun error interrupt flag */
    EDIM_TFMT_INT_FLAG_FIFOUNR = EDIM_TFMT_REGIDX_BIT2(EDIM_TFMT_INTEN_REG_OFFSET, 17U, EDIM_TFMT_STAT_REG_OFFSET, 17U),      /*!< FIFO underrun error interrupt flag */
    EDIM_TFMT_INT_FLAG_DMATO = EDIM_TFMT_REGIDX_BIT2(EDIM_TFMT_INTEN_REG_OFFSET, 18U, EDIM_TFMT_STAT_REG_OFFSET, 18U),        /*!< DMA request timeout error interrupt flag */
} edim_tfmt_interrupt_flag_enum;

/* EDIM_TFMT flag */
#define EDIM_TFMT_FLAG_MASK                      ((uint32_t)0x00071FFFU)
#define EDIM_TFMT_FLAG_EOC                       EDIM_TFMT_STAT_EOC                                   /*!< end of communication flag */
#define EDIM_TFMT_FLAG_TBUSYF                    EDIM_TFMT_STAT_TBUSYF                                /*!< transmit busy flag */
#define EDIM_TFMT_FLAG_RBUSYF                    EDIM_TFMT_STAT_RBUSYF                                /*!< receive busy flag */
#define EDIM_TFMT_FLAG_TOERR                     EDIM_TFMT_STAT_TOIF                                  /*!< timeout error flag */
#define EDIM_TFMT_FLAG_CRC                       EDIM_TFMT_STAT_CRCIF                                 /*!< crc error flag */
#define EDIM_TFMT_FLAG_SDEL                      EDIM_TFMT_STAT_SDELIF                                /*!< frame error in received frame flag */
#define EDIM_TFMT_FLAG_PCTL                      EDIM_TFMT_STAT_PCTLIF                                /*!< parity error in received frame flag*/
#define EDIM_TFMT_FLAG_CC                        EDIM_TFMT_STAT_CCIF                                  /*!< data ID error flag */
#define EDIM_TFMT_FLAG_EEPROMBUSY                EDIM_TFMT_STAT_EEPROMBUSYIF                          /*!< eeprom busy flag */
#define EDIM_TFMT_FLAG_DEL                       EDIM_TFMT_STAT_DELIF                                 /*!< frame error in request frame flag */
#define EDIM_TFMT_FLAG_PREQ                      EDIM_TFMT_STAT_PREQIF                                /*!< parity error in request frame flag */
#define EDIM_TFMT_FLAG_ALRM                      EDIM_TFMT_STAT_ALRMIF                                /*!< alarm flag*/
#define EDIM_TFMT_FLAG_CNT                       EDIM_TFMT_STAT_CNTIF                                 /*!< counting error flag */
#define EDIM_TFMT_FLAG_FIFOOVR                   EDIM_TFMT_STAT_FIFOOVRIF                             /*!< FIFO overrun error flag */
#define EDIM_TFMT_FLAG_FIFOUNR                   EDIM_TFMT_STAT_FIFOUNRIF                             /*!< FIFO underrun error flag */
#define EDIM_TFMT_FLAG_DMATO                     EDIM_TFMT_STAT_DMATOIF                               /*!< DMA request timeout error flag */

/* EDIM_TFMT status mode */
#define EDIM_TFMT_STAT_DYNAMIC                   (uint32_t)(0x00000000U)                         /*!< EDIM_TFMT status dynamic update mode */
#define EDIM_TFMT_STAT_STATIC                    EDIM_TFMT_STATUPMODE_STATUPMODE                 /*!< EDIM_TFMT status static update mode */

typedef enum {                                                                               
    EDIM_TFMT_TRIGGER_SWT = 0,                                                                   /*!< EDIM_TFMT trigger select SWT */
    EDIM_TFMT_TRIGGER_TRIGSEL = 1,                                                               /*!< EDIM_TFMT trigger select TRIGSEL */
} edim_tfmt_trigger_enum;

typedef enum {
    EDIM_TFMT_RDATA0 = 0,                                                                        /*!< EDIM_TFMT RDATA0 */
    EDIM_TFMT_RDATA1 = 1,                                                                        /*!< EDIM_TFMT RDATA1 */
    EDIM_TFMT_RDATA2 = 2,                                                                        /*!< EDIM_TFMT RDATA2 */
    EDIM_TFMT_RDATA3 = 3,                                                                        /*!< EDIM_TFMT RDATA3 */
} edim_tfmt_rdata_enum;

/* function declarations */
/* initialization functions */
/* reset EDIM_TFMT */
void edim_tfmt_deinit(void);
/* configure EDIM_TFMT trigger mode */
void edim_tfmt_trigger_mode_config(edim_tfmt_trigger_enum mode);
/* configure EDIM_TFMT command to be sent */
void edim_tfmt_command(uint32_t cc);
/* configure EDIM_TFMT command with eeprom write to be sent */
void edim_tfmt_command_with_eeprom_write(uint8_t addr, uint8_t data);
/* configure EDIM_TFMT command with eeprom read to be sent */
void edim_tfmt_command_with_eeprom_read(uint8_t addr);
/* enable EDIM_TFMT software trigger */
void edim_tfmt_software_trigger(void);
/* enable EDIM_TFMT DMA */
void edim_tfmt_dma_enable(void);
/* disable EDIM_TFMT DMA */
void edim_tfmt_dma_disable(void);
/* flush EDIM_TFMT DMA FIFO */
void edim_tfmt_dma_flush(void);
/* select EDIM_TFMT DMA FIFO data source */
void edim_tfmt_dma_select(uint32_t reg_selected);
/* read EDIM_TFMT RDATAx */
uint32_t edim_tfmt_data_read(edim_tfmt_rdata_enum data_n);
/* configure EDIM_TFMT status update mode */
void edim_tfmt_status_update_mode_config(uint32_t mode);
/* enable EDIM_TFMT interrupt */
void edim_tfmt_interrupt_enable(uint32_t interrupt);
/* disable EDIM_TFMT interrupt */
void edim_tfmt_interrupt_disable(uint32_t interrupt);
/* get EDIM_TFMT flag status */
FlagStatus edim_tfmt_flag_get(uint32_t flag);
/* clear EDIM_TFMT flag status */
void edim_tfmt_flag_clear(uint32_t flag);
/* get EDIM_TFMT interrupt flag */
FlagStatus edim_tfmt_interrupt_flag_get(edim_tfmt_interrupt_flag_enum int_flag);
/* clear EDIM_TFMT interrupt flag */
void edim_tfmt_interrupt_flag_clear(edim_tfmt_interrupt_flag_enum int_flag);

#endif /* GD32H77X_78X_EDIM_TFMT_H */