/*!
    \file    gd32h77x_78x_edim.h
    \brief   definitions for the EDIM

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

#ifndef GD32H77X_78X_EDIM_H
#define GD32H77X_78X_EDIM_H

#include "gd32h77x_78x.h"

/* timeouts */
#define EDIM_TIMEOUT_INFINITE              0U                                     /*!< infinite wait sentinel for polling APIs */

/* unified DMA DFEN starting bit offsets per protocol */
#define EDIM_DMA_BISS_DFEN_START_BIT       16U                                    /*!< BISS DFEN0 bit position */
#define EDIM_DMA_ENDAT_DFEN_START_BIT      25U                                    /*!< ENDAT DFEN0 bit position */
#define EDIM_DMA_AFMT_DFEN_START_BIT       20U                                    /*!< AFMT DFEN0 bit position */
#define EDIM_DMA_TFMT_DFEN_START_BIT       20U                                    /*!< TFMT DFEN0 bit position */

/* reset operation iteration counts (protocol specific) */
#define EDIM_AFMT_RESET_OP_CNT             8U                                     /*!< AFMT reset sequence operations */
#define EDIM_TFMT_RESET_OP_CNT             10U                                    /*!< TFMT reset sequence operations */


/* EDIM register access direction */
typedef enum {EDIM_READ = 0,  EDIM_WRITE = !EDIM_READ} edim_reg_access_enum;

/* EDIM communication mode (broadcast / unicast) */
typedef enum {EDIM_COMM_MODE_UNICAST = 0, EDIM_COMM_MODE_GLOBAL = !EDIM_COMM_MODE_UNICAST} edim_comm_mode_enum;

/* EDIM slave index enumeration */
typedef enum {
    EDIM_SLAVE0 = 0,                                                             /*!< slave index 0 */
    EDIM_SLAVE1,                                                                 /*!< slave index 1 */
    EDIM_SLAVE2,                                                                 /*!< slave index 2 */
    EDIM_SLAVE3,                                                                 /*!< slave index 3 */
    EDIM_SLAVE4,                                                                 /*!< slave index 4 */
    EDIM_SLAVE5,                                                                 /*!< slave index 5 */
    EDIM_SLAVE6,                                                                 /*!< slave index 6 */
    EDIM_SLAVE7,                                                                 /*!< slave index 7 */
    EDIM_SLAVES_MAX                                                              /*!< number of slaves */
} edim_slave_number_enum;

/* EDIM protocol selector */
typedef enum {
    EDIM_PROTO_HDSL = 0,                                                         /*!< HDSL protocol */
    EDIM_PROTO_BISS,                                                             /*!< BISS protocol */
    EDIM_PROTO_ENDAT,                                                            /*!< ENDAT protocol */
    EDIM_PROTO_AFMT,                                                             /*!< AFMT protocol */
    EDIM_PROTO_TFMT,                                                             /*!< TFMT protocol */
    EDIM_PROTO_MAX                                                               /*!< number of supported protocols */
} edim_proto_enum;

/* EDIM channel selector */
typedef enum {
    EDIM_CHANNEL_0 = 0,                                                          /*!< channel 0 only supported */
    EDIM_CHANNEL_MAX                                                             /*!< number of channels */
} edim_channel_enum;

/* EDIM error codes */
typedef enum {
    EDIM_ERROR_NONE          = 0,                                                 /*!< no error */
    EDIM_ERROR_INVAL_PROTO   = -1,                                                /*!< invalid protocol */
    EDIM_ERROR_INVAL_CHANNEL = -2,                                                /*!< invalid channel index */
    EDIM_ERROR_INVAL_PARA    = -3,                                                /*!< invalid parameter */
    EDIM_ERROR_INVAL_BAUD    = -4,                                                /*!< invalid baud rate */
    EDIM_ERROR_TIMEOUT       = -5,                                                /*!< operation timeout */
} edim_error_enum;

/* EDIM control operation selector */
typedef enum {
    EDIM_CONTROL_RESET_STATUS = 0,                                               /*!< reset status/error flags */
    EDIM_CONTROL_RESET_SINGLE_POS,                                               /*!< reset single-turn position */
    EDIM_CONTROL_RESET_MULTIPLE_POS,                                             /*!< reset multi-turn position */
    EDIM_CONTROL_SET_SLAVE_ADDRESS,                                              /*!< assign (set) slave address */
    EDIM_CONTROL_PROCESS_DATA_ACTIVE,                                            /*!< enable process data */
    EDIM_CONTROL_COMMUNICATION_CONTROL_STOP,                                     /*!< stop communication control frame */
    EDIM_CONTROL_ALL_SLAVE_PROCESS_DATA_STOP,                                    /*!< stop process data for all slaves */
    EDIM_CONTROL_ALL_SLAVE_COMMUNICATION_CONTROL_ACTIVE,                         /*!< activate communication control for all slaves */
    EDIM_CONTROL_OP_MAX                                                          /*!< number of control ops */
} edim_control_op_enum;

/* EDIM DMA error types */
typedef enum {
    EDIM_DMAERR_TIMEOUT  = 0,                                                    /*!< DMA request timeout error */
    EDIM_DMAERR_OVERRUN  = 1,                                                    /*!< FIFO overrun error */
    EDIM_DMAERR_UNDERRUN = 2,                                                    /*!< FIFO underrun error */
} edim_dma_error_type_enum;

/* EDIM FIFO enable mask bits (protocol dependent width usage) */
typedef enum {
    EDIM_FIFOEN0  = 0x00000001U,                                                /*!< FIFO enable bit 0 */
    EDIM_FIFOEN1  = 0x00000002U,                                                /*!< FIFO enable bit 1 */
    EDIM_FIFOEN2  = 0x00000004U,                                                /*!< FIFO enable bit 2 */
    EDIM_FIFOEN3  = 0x00000008U,                                                /*!< FIFO enable bit 3 */
    EDIM_FIFOEN4  = 0x00000010U,                                                /*!< FIFO enable bit 4 */
    EDIM_FIFOEN5  = 0x00000020U,                                                /*!< FIFO enable bit 5 */
    EDIM_FIFOEN6  = 0x00000040U,                                                /*!< FIFO enable bit 6 */
    EDIM_FIFOEN7  = 0x00000080U,                                                /*!< FIFO enable bit 7 */
    EDIM_FIFOEN8  = 0x00000100U,                                                /*!< FIFO enable bit 8 */
    EDIM_FIFOEN9  = 0x00000200U,                                                /*!< FIFO enable bit 9 */
    EDIM_FIFOEN10 = 0x00000400U,                                                /*!< FIFO enable bit 10 */
    EDIM_FIFOEN11 = 0x00000800U,                                                /*!< FIFO enable bit 11 */
    EDIM_FIFOEN12 = 0x00001000U,                                                /*!< FIFO enable bit 12 */
    EDIM_FIFOEN13 = 0x00002000U,                                                /*!< FIFO enable bit 13 */
    EDIM_FIFOEN14 = 0x00004000U,                                                /*!< FIFO enable bit 14 */
    EDIM_FIFOEN15 = 0x00008000U,                                                /*!< FIFO enable bit 15 */
} edim_fifoen_enum;

/* EDIM data buffer structure */
typedef struct {
    uint32_t sl_nums;                                                            /*!< number of slaves for read */
    uint32_t rd_words[24];                                                       /*!< protocol data words (capacity 24) */
} edim_buf_struct;

/* EDIM process data configuration */
typedef struct {
    edim_comm_mode_enum commu_mode;                                              /*!< communication mode */
    edim_slave_number_enum sl_index;                                             /*!< slave index */
} edim_process_data_config_struct;

/* EDIM register/EEPROM access configuration */
typedef struct {
    edim_reg_access_enum reg_rw;                                                 /*!< access direction */
    edim_slave_number_enum sl_index;                                             /*!< slave index */
    uint32_t memaddr;                                                            /*!< target memory address */
    uint32_t size;                                                               /*!< byte count */
    uint32_t data[64];                                                           /*!< data buffer (LSB significant per byte) */
} edim_reg_access_config_struct;

/* EDIM encoder control configuration */
typedef struct {
    edim_control_op_enum op;                                                      /*!< control operation code */
    edim_slave_number_enum sl_index;                                              /*!< slave index */
} edim_control_config_struct;

/* function declarations */
/* reset all EDIM protocol blocks */
void edim_deinit(void);
/* enable EDIM protocol DMA */
edim_error_enum edim_dma_enable(edim_proto_enum edim_proto, edim_channel_enum edim_ch);
/* disable EDIM protocol DMA */
edim_error_enum edim_dma_disable(edim_proto_enum edim_proto, edim_channel_enum edim_ch);
/* flush EDIM protocol DMA FIFO */
edim_error_enum edim_dma_flush(edim_proto_enum edim_proto, edim_channel_enum edim_ch);
/* select EDIM protocol DMA FIFO source */
edim_error_enum edim_dma_select(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_fifoen_enum fifo_selected);
/* read EDIM protocol data words */
edim_error_enum edim_data_read(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_buf_struct *edim_buf);
/* protocol register/EEPROM access */
edim_error_enum edim_reg_access_operation(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_reg_access_config_struct *config, uint32_t timeout_cycles);
/* protocol full position read */
edim_error_enum edim_full_pos_acquisition_operation(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_process_data_config_struct *config, uint32_t timeout_cycles);
/* protocol encoder control operations */
edim_error_enum edim_control_encoder_operation(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_control_config_struct *config, uint32_t timeout_cycles);
/* EDIM software trigger */
edim_error_enum edim_software_trigger(edim_proto_enum edim_proto, edim_channel_enum edim_ch);
/* select external trigger mode */
edim_error_enum edim_select_ext_trigger(edim_proto_enum edim_proto, edim_channel_enum edim_ch);
/* set protocol baud rate */
edim_error_enum edim_baud_set(edim_proto_enum edim_proto, edim_channel_enum edim_ch, uint32_t baud_rate);

/* frame-end interrupt enable */
edim_error_enum edim_frame_end_interrupt_enable(edim_proto_enum edim_proto, edim_channel_enum edim_ch);
/* frame-end interrupt disable */
edim_error_enum edim_frame_end_interrupt_disable(edim_proto_enum edim_proto, edim_channel_enum edim_ch);
/* get frame-end interrupt flag (requires enable) */
edim_error_enum edim_frame_end_interrupt_flag_get(edim_proto_enum edim_proto, edim_channel_enum edim_ch, FlagStatus *status);
/* clear frame-end interrupt flag */
edim_error_enum edim_frame_end_interrupt_flag_clear(edim_proto_enum edim_proto, edim_channel_enum edim_ch);
/* get raw frame-end status flag */
edim_error_enum edim_frame_end_flag_get(edim_proto_enum edim_proto, edim_channel_enum edim_ch, FlagStatus *status);
/* clear raw frame-end status flag */
edim_error_enum edim_frame_end_flag_clear(edim_proto_enum edim_proto, edim_channel_enum edim_ch);

/* timeout interrupt enable */
edim_error_enum edim_timeout_interrupt_enable(edim_proto_enum edim_proto, edim_channel_enum edim_ch);
/* timeout interrupt disable */
edim_error_enum edim_timeout_interrupt_disable(edim_proto_enum edim_proto, edim_channel_enum edim_ch);
/* get timeout interrupt flag */
edim_error_enum edim_timeout_interrupt_flag_get(edim_proto_enum edim_proto, edim_channel_enum edim_ch, FlagStatus *status);
/* clear timeout interrupt flag */
edim_error_enum edim_timeout_interrupt_flag_clear(edim_proto_enum edim_proto, edim_channel_enum edim_ch);
/* get raw timeout status flag */
edim_error_enum edim_timeout_flag_get(edim_proto_enum edim_proto, edim_channel_enum edim_ch, FlagStatus *status);
/* clear raw timeout status flag */
edim_error_enum edim_timeout_flag_clear(edim_proto_enum edim_proto, edim_channel_enum edim_ch);

/* DMA error interrupt enable (timeout/overrun/underrun) */
edim_error_enum edim_dma_error_interrupt_enable(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_dma_error_type_enum err_type);
/* DMA error interrupt disable */
edim_error_enum edim_dma_error_interrupt_disable(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_dma_error_type_enum err_type);
/* get DMA error interrupt flag */
edim_error_enum edim_dma_error_interrupt_flag_get(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_dma_error_type_enum err_type, FlagStatus *status);
/* clear DMA error interrupt flag */
edim_error_enum edim_dma_error_interrupt_flag_clear(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_dma_error_type_enum err_type);
/* get raw DMA error status flag */
edim_error_enum edim_dma_error_flag_get(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_dma_error_type_enum err_type, FlagStatus *status);
/* clear raw DMA error status flag */
edim_error_enum edim_dma_error_flag_clear(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_dma_error_type_enum err_type);

#endif /* GD32H77X_78X_EDIM_H */