/*!
    \file    gd32h77x_78x_gpsi.h
    \brief   definitions for the GPSI

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

#ifndef GD32H77X_78X_GPSI_H
#define GD32H77X_78X_GPSI_H

#include "gd32h77x_78x.h"

/* GPSI definitions */
#define GPSI                       GPSI_BASE

/* registers definitions */
#define GPSI_CTL                   REG32(GPSI + 0x00000000U)            /*!< Control register */
#define GPSI_STAT                  REG32(GPSI + 0x00000004U)            /*!< Status register 0 */
#define GPSI_INTF                  REG32(GPSI + 0x00000008U)            /*!< Status register 1 */
#define GPSI_INTEN                 REG32(GPSI + 0x0000000CU)            /*!< Interrupt enable register */
#define GPSI_MINTF                 REG32(GPSI + 0x00000010U)            /*!< Masked interrupt status register */
#define GPSI_INTC                  REG32(GPSI + 0x00000014U)            /*!< Interrupt flag register */
#define GPSI_DATA                  REG32(GPSI + 0x00000028U)            /*!< Data register */

/* bits definitions */                               
/* GPSI_CTL */                     
#define GPSI_CTL_DIRSEL            BIT(31)                              /*!< Data direction */
#define GPSI_CTL_DMAEN             BIT(30)                              /*!< GPSI DMA transfers are enabled  */
#define GPSI_CTL_SIGCFG            BITS(18,20)                          /*!< Data enable and ready setting bits */
#define GPSI_CTL_GPSIEN            BIT(14)                              /*!< GPSI enable */
#define GPSI_CTL_GPSIF             BITS(10,11)                          /*!< Captured data width select */
#define GPSI_CTL_RPL               BIT(8)                               /*!< Ready (GPSI_RDY) polarity */
#define GPSI_CTL_DPL               BIT(6)                               /*!< Data enable (GPSI_DE) polarity */
#define GPSI_CTL_CKPL              BIT(5)                               /*!< Parallel data clock polarity */
                                                      
/* GPSI_STAT */                                       
#define GPSI_STAT_4BRF             BIT(2)                               /*!< FIFO is ready to transfer four bytes */
#define GPSI_STAT_1BRF             BIT(3)                               /*!< FIFO is ready to transfer one byte */
#define GPSI_STAT_2BRF             BIT(4)                               /*!< FIFO is ready to transfer one byte */
                                                      
/* GPSI_INTF */                                       
#define GPSI_INTF_OUIF             BIT(1)                               /*!< Data buffer overrun/underrun raw interrupt status */
                                                      
/* GPSI_INTEN */                                      
#define GPSI_INTEN_OUIE            BIT(1)                               /*!< Data buffer overrun/underrun interrupt enable */
                                                      
/* GPSI_MINTF */                                      
#define GPSI_MINTF_OUMIF           BIT(1)                               /*!< Data buffer overrun/underrun masked interrupt status */
                                                      
/* GPSI_INTC */                                       
#define GPSI_INTC_OUFC             BIT(1)                               /*!< Data buffer overrun/underrun interrupt status clear */
                                                      
/* GPSI_DATA */                                       
#define GPSI_DATA_DT0              BITS(0,7)                            /*!< GPSI data 0 */
#define GPSI_DATA_DT1              BITS(8,15)                           /*!< GPSI data 1 */
#define GPSI_DATA_DT2              BITS(16,23)                          /*!< GPSI data 2 */
#define GPSI_DATA_DT3              BITS(24,31)                          /*!< GPSI data 3 */

/* constants definitions */
#define GPSI_RECEIVE_MODE          0x00000000U                          /*!< Receive mode */
#define GPSI_TRANSMIT_MODE         GPSI_CTL_DIRSEL                      /*!< Transmit mode */

#define GPSI_DE_RDY_CFG(regval)    (BITS(18,20) & ((uint32_t)(regval) << 18U))
#define GPSI_DE_RDY_DISABLE        GPSI_DE_RDY_CFG(0)                   /*!< GPSI_DE and GPSI_RDY both disabled */
#define GPSI_RDY_ENABLE            GPSI_DE_RDY_CFG(1)                   /*!< Only GPSI_RDY enabled */
#define GPSI_DE_ENABLE             GPSI_DE_RDY_CFG(2)                   /*!< Only GPSI_DE enabled */
#define GPSI_DE_RDY_ALT_ENABLE     GPSI_DE_RDY_CFG(3)                   /*!< Both GPSI_RDY and GPSI_DE alternate functions enabled*/
#define GPSI_MAP_RDY_BIDIR_ENABLE  GPSI_DE_RDY_CFG(4)                   /*!< Both GPSI_RDY and GPSI_DE features enabled - bidirectional on GPSI_RDY pin  */
#define GPSI_RDY_MAP_ENABLE        GPSI_DE_RDY_CFG(5)                   /*!< Only GPSI_RDY function enabled, but mapped to GPSI_DE pin */
#define GPSI_DE_MAP_ENABLE         GPSI_DE_RDY_CFG(6)                   /*!< Only GPSI_DE function enabled, but mapped to GPSI_RDY pin */
#define GPSI_MAP_DE_BIDIR_ENABLE   GPSI_DE_RDY_CFG(7)                   /*!< Both GPSI_RDY and GPSI_DE features enabled - bidirectional on GPSI_DE pin */

#define GPSI_8LINES                0x00000000U                          /*!< 8 data lines  */
#define GPSI_16LINES               GPSI_CTL_GPSIF                       /*!< 16 data lines */
                    
/* GPSI_Data_Enable_Polarity Data Enable Polarity */                  
#define GPSI_DEPOL_ACTIVE_LOW      0x00000000U                          /*!< Active Low */
#define GPSI_DEPOL_ACTIVE_HIGH     GPSI_CTL_DPL                         /*!< Active High */
                    
/* GPSI_Ready_Polarity Ready Polarity */                  
#define GPSI_RDYPOL_ACTIVE_LOW     0x00000000U                          /*!< Active Low */
#define GPSI_RDYPOL_ACTIVE_HIGH    GPSI_CTL_RPL                         /*!< Active High */
                    
/* GPSI_Clock_Polarity Clock Polarity */                  
#define GPSI_FALLING_EDGE          0x00000000U                          /*!< Falling Edge */
#define GPSI_RISING_EDGE           GPSI_CTL_CKPL                        /*!< Rising Edge */

/* GPSI parameter structure definitions */
typedef struct {
    uint32_t data_direction;                           /*!< Data direction */
    uint32_t data_en_ready_config;                     /*!< GPSI capture mode: continuous or snapshot */
    uint32_t clock_polarity;                           /*!< Clock polarity selection */
    uint32_t de_polarity;                              /*!< Data enable polarity selection */
    uint32_t rdy_polarity;                             /*!< Ready polarity selection */
    uint32_t data_width;                               /*!< Captured data width select */
} gpsi_parameter_struct;

/* function declarations */
/* initialization functions */
/* gpsi deinit */
void gpsi_deinit(void);
/* initialize the GPSI parameter structure with default values */
void gpsi_struct_para_init(gpsi_parameter_struct *gpsi_struct);
/* initialize gpsi registers */
void gpsi_init(gpsi_parameter_struct *gpsi_struct);
/* select captured data width */
void gpsi_buswidth_config(uint32_t buswidth);
/* enable gpsi function */
void gpsi_enable(void);
/* disable gpsi function */
void gpsi_disable(void);
/* read gpsi data register */
uint32_t gpsi_data_read(void);
/* gpsi dma transfers enable*/
void gpsi_dma_enable(void);
/* gpsi dma transfers disable */
void gpsi_dma_disable(void);

/* interrupt & flag functions */
/* get specified flag */
FlagStatus gpsi_flag_get(uint32_t flag);
/* enable specified gpsi interrupt */
void gpsi_interrupt_enable(uint32_t interrupt);
/* disable specified gpsi interrupt */
void gpsi_interrupt_disable(uint32_t interrupt);
/* get specified interrupt flag */
FlagStatus gpsi_interrupt_flag_get(uint32_t int_flag);
/* clear specified interrupt flag */
void gpsi_interrupt_flag_clear(uint32_t int_flag);

#endif /* GD32H77X_78X_GPSI_H */
