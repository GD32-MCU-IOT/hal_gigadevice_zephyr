/*!
    \file    gd32h77x_78x_edim_afmt.h
    \brief   definitions for the EDIM_AFMT

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

#ifndef GD32H77X_78X_EDIM_AFMT_H
#define GD32H77X_78X_EDIM_AFMT_H

#include "gd32h77x_78x.h"

#define EDIM_AFMT                                (EDIM_BASE + 0x00000000U)                        /*!< EDIM_AFMT base address */

#define EDIM_AFMT_CMD                            REG32(EDIM_AFMT + 0x00000080U)                   /*!< EDIM_AFMT command register */
#define EDIM_AFMT_EEPROM                         REG32(EDIM_AFMT + 0x00000084U)                   /*!< EDIM_AFMT romdata register */
#define EDIM_AFMT_IDCODE                         REG32(EDIM_AFMT + 0x00000088U)                   /*!< EDIM_AFMT id register */
#define EDIM_AFMT_TRGM                           REG32(EDIM_AFMT + 0x0000008CU)                   /*!< EDIM_AFMT trigger mode select */
#define EDIM_AFMT_SWT                            REG32(EDIM_AFMT + 0x00000090U)                   /*!< EDIM_AFMT software trigger register */
#define EDIM_AFMT_CFG                            REG32(EDIM_AFMT + 0x00000094U)                   /*!< EDIM_AFMT configuration register*/
#define EDIM_AFMT_STAT                           REG32(EDIM_AFMT + 0x00000098U)                   /*!< EDIM_AFMT state register */
#define EDIM_AFMT_INTEN                          REG32(EDIM_AFMT + 0x0000009CU)                   /*!< EDIM_AFMT interrupt enable register */
#define EDIM_AFMT_ENCRDATA(m, n)                 REG32(EDIM_AFMT + 0x04U * (m) + 0x10U * (n))         /*!< EDIM_AFMT receive data register */
#define EDIM_AFMT_FIFODATA                       REG32(EDIM_AFMT + 0x00000140U)                   /*!< EDIM_AFMT FIFO data register */

/* bits definitions */
/* EDIM_AFMT_CMD */
#define EDIM_AFMT_CMD_MEA                        BITS(0, 2)                                       /*!< EDIM_AFMT encoder receive communication command code */
#define EDIM_AFMT_CMD_CC                         BITS(3, 7)                                       /*!< EDIM_AFMT matching address of encoder */

/* EDIM_AFMT_EEPROM */
#define EDIM_AFMT_EEPROM_EEPROMDATA              BITS(0, 15)                                      /*!< EDIM_AFMT data to be written into EEPROM of encoder */
#define EDIM_AFMT_EEPROM_EEPROMADDR              BITS(16, 23)                                     /*!< EDIM_AFMT EEPROM accessing address of encoder */

/* EDIM_AFMT_ID */
#define EDIM_AFMT_IDCODE_IDCODE                  BITS(0, 23)                                      /*!< EDIM_AFMT ID code for communication */

/* EDIM_AFMT_TRGM */
#define EDIM_AFMT_TRGM_TRANSTSEL                 BIT(0)                                           /*!< EDIM_AFMT transmission start trigger selection */

/* EDIM_AFMT_SWT */
#define EDIM_AFMT_SWT_SWTR                       BIT(0)                                           /*!< EDIM_AFMT data transmission software trigger */

/* EDIM_AFMT_CFG */
#define EDIM_AFMT_CFG_BAUD                       BITS(0, 2)                                       /*!< EDIM_AFMT communication baud rate configuration */
#define EDIM_AFMT_CFG_T2FAC                      BITS(4, 11)                                      /*!< EDIM_AFMT time step factor of t2 */
#define EDIM_AFMT_CFG_DFEN                       BIT(16)                                          /*!< EDIM_AFMT DMA request and FIFO enable */
#define EDIM_AFMT_CFG_FIFOFH                     BIT(17)                                          /*!< EDIM_AFMT FIFO flush */
#define EDIM_AFMT_CFG_DFEN_MASK                  BITS(20,22)                                      /*!< EDIM_AFMT DMA enable mask */
#define EDIM_AFMT_CFG_DFEN0                      BIT(20)                                          /*!< EDIM_AFMT DMA request and FIFO enable for EDIM_AFMT_ENCnRDATA0 register */
#define EDIM_AFMT_CFG_DFEN1                      BIT(21)                                          /*!< EDIM_AFMT DMA request and FIFO enable for EDIM_AFMT_ENCnRDATA1 register */
#define EDIM_AFMT_CFG_DFEN2                      BIT(22)                                          /*!< EDIM_AFMT DMA request and FIFO enable for EDIM_AFMT_ENCnRDATA2 register */

/* EDIM_AFMT_STAT */
#define EDIM_AFMT_STAT_CBUSYF                    BIT(0)                                           /*!< EDIM_AFMT communication busy flag */
#define EDIM_AFMT_STAT_EOC                       BIT(1)                                           /*!< EDIM_AFMT end of communication */
#define EDIM_AFMT_STAT_TOIF                      BIT(2)                                           /*!< EDIM_AFMT timeout error interrupt flag */
#define EDIM_AFMT_STAT_FIFOOVRIF                 BIT(16)                                          /*!< EDIM_AFMT FIFO overrun error interrupt flag */
#define EDIM_AFMT_STAT_FIFOUNRIF                 BIT(17)                                          /*!< EDIM_AFMT FIFO underrun error interrupt flag */
#define EDIM_AFMT_STAT_DMATOIF                   BIT(18)                                          /*!< EDIM_AFMT DMA request timeout error interrupt flag */

/* EDIM_AFMT_INTEN */
#define EDIM_AFMT_INTEN_EOCIE                    BIT(1)                                           /*!< EDIM_AFMT interrupt enable for EOC */
#define EDIM_AFMT_INTEN_TOIE                     BIT(2)                                           /*!< EDIM_AFMT interrupt enable for TOIF */
#define EDIM_AFMT_INTEN_FIFOOVRIE                BIT(16)                                          /*!< EDIM_AFMT interrupt enable of FIFOOVRIF */
#define EDIM_AFMT_INTEN_FIFOUNRIE                BIT(17)                                          /*!< EDIM_AFMT interrupt enable of FIFOUNRIF */
#define EDIM_AFMT_INTEN_DMATOIE                  BIT(18)                                          /*!< EDIM_AFMT interrupt enable of DMATOIF */

/* EDIM_AFMT_FIFODATA */
#define EDIM_AFMT_FIFODATA_FIFODATA              BITS(0, 31)                                      /*!< EDIM_AFMT FIFO data from TFMT_RDATAx registers */

/* EDIM_AFMT_ENCRXDATA */
#define EDIM_AFMT_ENCRDATA_RDATA                 BITS(0, 31)                                      /*!< EDIM_AFMT received data from encoder */

/* constants definitions */
/* EDIM AFMT parameter struct definitions */
typedef struct {
    uint32_t baud_rate;                                                                           /*!< communication baud rate */
    uint32_t t2;                                                                                  /*!< t2 time */
} edim_afmt_parameter_struct;

/* EDIM_AFMT match address of communication */
#define CMD_MEA(regval)                          (BITS(0,2) & ((uint32_t)(regval) << 0U))
#define EDIM_AFMT_ADDR(n)                        CMD_MEA(n)                                        /*!< EDIM_AFMT slave address */

/* EDIM_AFMT communication command code */
#define CMD_CC(regval)                           (BITS(3,7) & ((uint32_t)(regval) << 3U))          /*!< EDIM_AFMT command id */
#define EDIM_AFMT_CMD_CC_INDABS40                CMD_CC(0)                                         /*!< Individual ABS full 40-bit data request */
#define EDIM_AFMT_CMD_CC_INDABSL24               CMD_CC(1)                                         /*!< Individual ABS lower 24-bit data request */
#define EDIM_AFMT_CMD_CC_INDABSU24               CMD_CC(2)                                         /*!< Individual ABS upper 24-bit data request */
#define EDIM_AFMT_CMD_CC_INDSTA                  CMD_CC(3)                                         /*!< Individual Encoder status request */
#define EDIM_AFMT_CMD_CC_BRDABS40                CMD_CC(4)                                         /*!< Broadcast ABS full 40-bit data request */
#define EDIM_AFMT_CMD_CC_BRDABSL24               CMD_CC(5)                                         /*!< Broadcast ABS lower 24-bit data request */
#define EDIM_AFMT_CMD_CC_BRDABSU24               CMD_CC(6)                                         /*!< Broadcast ABS upper 24-bit data request */
#define EDIM_AFMT_CMD_CC_BRDSTA                  CMD_CC(7)                                         /*!< Broadcast Encoder status request */
#define EDIM_AFMT_CMD_CC_INDSTACLR               CMD_CC(8)                                         /*!< Status flag clear request */
#define EDIM_AFMT_CMD_CC_MUTCLR                  CMD_CC(9)                                         /*!< Multi-rotation data clear request */
#define EDIM_AFMT_CMD_CC_STAMUTCLR               CMD_CC(10)                                        /*!< Status and multi-rotation data clear requests */
#define EDIM_AFMT_CMD_CC_ADDSETI                 CMD_CC(11)                                        /*!< Encoder address setting I */
#define EDIM_AFMT_CMD_CC_ABSRST                  CMD_CC(12)                                        /*!< One-rotation data zero preset */
#define EDIM_AFMT_CMD_CC_MEMRD                   CMD_CC(13)                                        /*!< Memory read request */
#define EDIM_AFMT_CMD_CC_MEMWR                   CMD_CC(14)                                        /*!< Memory write request */
#define EDIM_AFMT_CMD_CC_TEMREQ                  CMD_CC(15)                                        /*!< 10-bit temperature data request */
#define EDIM_AFMT_CMD_CC_IDRDI                   CMD_CC(16)                                        /*!< ID code read I */
#define EDIM_AFMT_CMD_CC_IDRDII                  CMD_CC(17)                                        /*!< ID code read II */
#define EDIM_AFMT_CMD_CC_IDWRI                   CMD_CC(18)                                        /*!< ID code write I */
#define EDIM_AFMT_CMD_CC_IDWRII                  CMD_CC(19)                                        /*!< ID code write II */
#define EDIM_AFMT_CMD_CC_ADDSETII                CMD_CC(20)                                        /*!< Encoder address setting II */
#define EDIM_AFMT_CMD_CC_INDABSL17               CMD_CC(21)                                        /*!< Individual ABS lower 17-bit data request */
#define EDIM_AFMT_CMD_CC_BRDABSL17               CMD_CC(22)                                        /*!< Broadcast ABS lower 17-bit data request */
#define EDIM_AFMT_CMD_CC_INDABSL24STA            CMD_CC(27)                                        /*!< Individual ABS lower 24-bit data and status requests */
#define EDIM_AFMT_CMD_CC_BRDABSL24STA            CMD_CC(28)                                        /*!< Broadcast ABS lower 24-bit data and status requests */
#define EDIM_AFMT_CMD_CC_INDABSL24TEM            CMD_CC(29)                                        /*!< Individual ABS lower 24-bit data and temperature requests */
#define EDIM_AFMT_CMD_CC_BRDABSL24TEM            CMD_CC(30)                                        /*!< Broadcast ABS lower 24-bit data and temperature requests */


/* EDIM_AFMT communication baud rate */
#define CFG_BAUD(regval)                         (BITS(0,2) & ((uint32_t)(regval) << 0U))
#define EDIM_AFMT_BAUD_2_5MBPS                   CFG_BAUD(0)                                       /*!< communication baud rate 2.5Mbps */
#define EDIM_AFMT_BAUD_4MBPS                     CFG_BAUD(1)                                       /*!< communication baud rate 4Mbps */
#define EDIM_AFMT_BAUD_6_67MBPS                  CFG_BAUD(2)                                       /*!< communication baud rate 6.67Mbps */
#define EDIM_AFMT_BAUD_8MBPS                     CFG_BAUD(3)                                       /*!< communication baud rate 8Mbps */
#define EDIM_AFMT_BAUD_16MBPS                    CFG_BAUD(4)                                       /*!< communication baud rate 16Mbps */

/* EDIM_AFMT time step factor of T2 */
#define CFG_T2FAC(regval)                        (BITS(4,11) & ((uint32_t)(regval) << 4U))
#define EDIM_AFMT_T2_FACTOR(n)                   CFG_T2FAC(n)                                      /*!< t2 time factor */

/* EDIM_AFMT eeprom */
#define EEPROM_EEPROMDATA(regval)                (BITS(0,15) & (uint32_t)(regval))                 /*!< eeprom write data */
#define EEPROM_EEPROMADDR(regval)                (BITS(16,23) & ((uint32_t)(regval) << 16))        /*!< eeprom write address */

/* EDIM_AFMT interrupt enable or disable */
#define EDIM_AFMT_INTEN_MASK                     ((uint32_t)0x00070006U)
#define EDIM_AFMT_INT_EOC                        EDIM_AFMT_INTEN_EOCIE                             /*!< EDIM_AFMT interrupt enable for EOC */
#define EDIM_AFMT_INT_TOERR                      EDIM_AFMT_INTEN_TOIE                              /*!< EDIM_AFMT interrupt enable for TOIF */
#define EDIM_AFMT_INT_FIFOOVR                    EDIM_AFMT_INTEN_FIFOOVRIE                         /*!< EDIM_AFMT interrupt enable of FIFOOVRIF */
#define EDIM_AFMT_INT_FIFOUNR                    EDIM_AFMT_INTEN_FIFOUNRIE                         /*!< EDIM_AFMT interrupt enable of FIFOUNRIF */
#define EDIM_AFMT_INT_DMATO                      EDIM_AFMT_INTEN_DMATOIE                           /*!< EDIM_AFMT interrupt enable of DMATOIF */

/* define the EDIM_AFMT bit position and its register index offset */
#define EDIM_AFMT_REG_VAL(edim_periph, offset)                (REG32((edim_periph) + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define EDIM_AFMT_BIT_POS(val)                   ((uint32_t)(val) & 0x0000001FU)
#define EDIM_AFMT_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                                   | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define EDIM_AFMT_REG_VAL2(edim_periph, offset)               (REG32((edim_periph) + ((uint32_t)(offset) >> 22)))
#define EDIM_AFMT_BIT_POS2(val)                  (((uint32_t)(val) & 0x001F0000U) >> 16)

/* register offset */
#define EDIM_AFMT_INTEN_REG_OFFSET               ((uint32_t)0x0000009CU)                         /*!< INTEN register offset */
#define EDIM_AFMT_STAT_REG_OFFSET                ((uint32_t)0x00000098U)                         /*!< STAT register offset */

/* EDIM_AFMT interrupt flags */
typedef enum {
    EDIM_AFMT_INT_FLAG_EOC = EDIM_AFMT_REGIDX_BIT2(EDIM_AFMT_INTEN_REG_OFFSET, 1U, EDIM_AFMT_STAT_REG_OFFSET, 1U),            /*!< end of communication interrupt flag */
    EDIM_AFMT_INT_FLAG_TOERR =  EDIM_AFMT_REGIDX_BIT2(EDIM_AFMT_INTEN_REG_OFFSET, 2U, EDIM_AFMT_STAT_REG_OFFSET, 2U),         /*!< timeout error interrupt flag */
    EDIM_AFMT_INT_FLAG_FIFOOVR = EDIM_AFMT_REGIDX_BIT2(EDIM_AFMT_INTEN_REG_OFFSET, 16U, EDIM_AFMT_STAT_REG_OFFSET, 16U),      /*!< FIFO overrun error interrupt flag */
    EDIM_AFMT_INT_FLAG_FIFOUNR = EDIM_AFMT_REGIDX_BIT2(EDIM_AFMT_INTEN_REG_OFFSET, 17U, EDIM_AFMT_STAT_REG_OFFSET, 17U),      /*!< FIFO underrun error interrupt flag */
    EDIM_AFMT_INT_FLAG_DMATO = EDIM_AFMT_REGIDX_BIT2(EDIM_AFMT_INTEN_REG_OFFSET, 18U, EDIM_AFMT_STAT_REG_OFFSET, 18U),        /*!< DMA request timeout error interrupt flag */
} edim_afmt_interrupt_flag_enum;

/* EDIM_AFMT flag */
#define EDIM_AFMT_FLAG_MASK                      ((uint32_t)0x00070007U)
#define EDIM_AFMT_FLAG_CBUSY                     EDIM_AFMT_STAT_CBUSYF                            /*!< communication busy flag */
#define EDIM_AFMT_FLAG_EOC                       EDIM_AFMT_STAT_EOC                               /*!< end of communication flag */
#define EDIM_AFMT_FLAG_TOERR                     EDIM_AFMT_STAT_TOIF                              /*!< timeout error flag */
#define EDIM_AFMT_FLAG_FIFOOVR                   EDIM_AFMT_STAT_FIFOOVRIF                         /*!< FIFO overrun error flag */
#define EDIM_AFMT_FLAG_FIFOUNR                   EDIM_AFMT_STAT_FIFOUNRIF                         /*!< FIFO underrun error flag */
#define EDIM_AFMT_FLAG_DMATO                     EDIM_AFMT_STAT_DMATOIF                           /*!< DMA request timeout error flag */

typedef enum {
    EDIM_AFMT_SLAVE0   = 0x00,                                                                    /*!< EDIM_AFMT slave address 0 */
    EDIM_AFMT_SLAVE1   = 0x01,                                                                    /*!< EDIM_AFMT slave address 1 */
    EDIM_AFMT_SLAVE2   = 0x02,                                                                    /*!< EDIM_AFMT slave address 2 */
    EDIM_AFMT_SLAVE3   = 0x03,                                                                    /*!< EDIM_AFMT slave address 3 */
    EDIM_AFMT_SLAVE4   = 0x04,                                                                    /*!< EDIM_AFMT slave address 4 */
    EDIM_AFMT_SLAVE5   = 0x05,                                                                    /*!< EDIM_AFMT slave address 5 */
    EDIM_AFMT_SLAVE6   = 0x06,                                                                    /*!< EDIM_AFMT slave address 6 */
    EDIM_AFMT_SLAVE7   = 0x07,                                                                    /*!< EDIM_AFMT slave address 7 */
} edim_afmt_slave_enum;

typedef enum {
    EDIM_AFMT_RDATA0 = 0x00,                                                                      /*!< EDIM_AFMT RDATA0 */
    EDIM_AFMT_RDATA1 = 0x01,                                                                      /*!< EDIM_AFMT RDATA1 */
    EDIM_AFMT_RDATA2 = 0x02,                                                                      /*!< EDIM_AFMT RDATA2 */
} edim_afmt_rdata_enum;

typedef enum {
    EDIM_AFMT_TRIGGER_SWT = 0,                                                                    /*!< EDIM_AFMT trigger select SWT */
    EDIM_AFMT_TRIGGER_TRIGSEL = 1,                                                                /*!< EDIM_AFMT trigger select TRIGSEL */
} edim_afmt_trigger_enum;

/* function declarations */
/* initialization functions */
/* reset EDIM_AFMT */
void edim_afmt_deinit(void);
/* initialize EDIM_AFMT init parameter struct with a default value */
void edim_afmt_struct_para_init(edim_afmt_parameter_struct *initpara);
/* initialize EDIM_AFMT configuration */
void edim_afmt_init(edim_afmt_parameter_struct *init_struct);
/* set EDIM_AFMT t2 time */
void edim_afmt_t2_config(uint32_t t2_fac);
/* configure EDIM_AFMT trigger mode */
void edim_afmt_trigger_mode_config(edim_afmt_trigger_enum mode);
/* configure EDIM_AFMT command */
void edim_afmt_command(uint8_t mea, uint8_t cc);
/* configure EDIM_AFMT command with eeprom write */
void edim_afmt_command_with_eeprom_write(uint8_t mea, uint8_t addr, uint16_t data);
/* configure EDIM_AFMT command with eeprom read */
void edim_afmt_command_with_eeprom_read(uint8_t mea, uint8_t addr);
/* configure EDIM_AFMT command with ID code */
void edim_afmt_command_with_id_write(uint8_t mea, uint8_t cc, uint32_t id);
/* enable EDIM_AFMT software trigger */
void edim_afmt_software_trigger(void);

/* enable EDIM_AFMT DMA */
void edim_afmt_dma_enable(void);
/* disable EDIM_AFMT DMA */
void edim_afmt_dma_disable(void);
/* flush EDIM_AFMT DMA FIFO */
void edim_afmt_dma_flush(void);
/* select EDIM_AFMT DMA FIFO data origin */
void edim_afmt_dma_select(uint32_t reg_selected);

/* read EDIM_AFMT RDATAx */
uint32_t edim_afmt_data_read(edim_afmt_slave_enum slv_n, edim_afmt_rdata_enum data_n);

/* enable EDIM_AFMT interrupt */
void edim_afmt_interrupt_enable(uint32_t interrupt);
/* disable EDIM_AFMT interrupt */
void edim_afmt_interrupt_disable(uint32_t interrupt);
/* get EDIM_AFMT flag status */
FlagStatus edim_afmt_flag_get(uint32_t flag);
/* clear EDIM_AFMT flag status */
void edim_afmt_flag_clear(uint32_t flag);
/* get EDIM_AFMT interrupt flag status */
FlagStatus edim_afmt_interrupt_flag_get(edim_afmt_interrupt_flag_enum int_flag);
/* clear EDIM_AFMT interrupt flag status */
void edim_afmt_interrupt_flag_clear(edim_afmt_interrupt_flag_enum int_flag);

#endif /* GD32H77X_78X_EDIM_AFMT_H */