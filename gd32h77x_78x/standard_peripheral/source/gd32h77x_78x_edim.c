/*!
    \file    gd32h77x_78x_edim.c
    \brief   EDIM driver

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

#include "gd32h77x_78x_edim.h"
#include "gd32h77x_78x_edim_afmt.h"
#include "gd32h77x_78x_edim_biss.h"
#include "gd32h77x_78x_edim_endat.h"
#include "gd32h77x_78x_edim_tfmt.h"
#include "gd32h77x_78x_edim_hdsl.h"
#include <stddef.h>

typedef struct {
    uint32_t int_enable_bit;     /* interrupt enable bit/mask */
    uint32_t int_flag_bit;       /* interrupt flag bit/mask */
    uint32_t status_flag_bit;    /* raw status flag bit/mask */
} edim_dma_err_map_struct;

/* order: TIMEOUT, OVERRUN, UNDERRUN */
static const edim_dma_err_map_struct edim_dma_err_map_afmt[] = {
    { EDIM_AFMT_INT_DMATO,    EDIM_AFMT_INT_FLAG_DMATO,    EDIM_AFMT_FLAG_DMATO},
    { EDIM_AFMT_INT_FIFOOVR,  EDIM_AFMT_INT_FLAG_FIFOOVR,  EDIM_AFMT_FLAG_FIFOOVR},
    { EDIM_AFMT_INT_FIFOUNR,  EDIM_AFMT_INT_FLAG_FIFOUNR,  EDIM_AFMT_FLAG_FIFOUNR},
};
static const edim_dma_err_map_struct edim_dma_err_map_tfmt[] = {
    { EDIM_TFMT_INT_DMATO,    EDIM_TFMT_INT_FLAG_DMATO,    EDIM_TFMT_FLAG_DMATO},
    { EDIM_TFMT_INT_FIFOOVR,  EDIM_TFMT_INT_FLAG_FIFOOVR,  EDIM_TFMT_FLAG_FIFOOVR},
    { EDIM_TFMT_INT_FIFOUNR,  EDIM_TFMT_INT_FLAG_FIFOUNR,  EDIM_TFMT_FLAG_FIFOUNR},
};
static const edim_dma_err_map_struct edim_dma_err_map_endat[] = {
    { EDIM_ENDAT_INT_DMATO,   EDIM_ENDAT_INT_FLAG_DMATO,   EDIM_ENDAT_FLAG_DMATO},
    { EDIM_ENDAT_INT_FIFOOVR, EDIM_ENDAT_INT_FLAG_FIFOOVR, EDIM_ENDAT_FLAG_FIFOOVR},
    { EDIM_ENDAT_INT_FIFOUNR, EDIM_ENDAT_INT_FLAG_FIFOUNR, EDIM_ENDAT_FLAG_FIFOUNR},
};
static const edim_dma_err_map_struct edim_dma_err_map_biss[] = {
    { EDIM_BISS_INT_DMATOIE,  EDIM_BISS_INT_FLAG_DMATO,    EDIM_BISS_FLAG_DMATO},
    { EDIM_BISS_INT_FIFOOVRIE,EDIM_BISS_INT_FLAG_FIFOOVR,  EDIM_BISS_FLAG_FIFOOVR},
    { EDIM_BISS_INT_FIFOUNRIE,EDIM_BISS_INT_FLAG_FIFOUNR,  EDIM_BISS_FLAG_FIFOUNR},
};

/* poll until the specified register bit(s) become set */
static edim_error_enum edim_wait_flag_set(volatile uint32_t *reg, uint32_t mask, uint32_t timeout_cycles);
/* validate DMA error type index */
static int edim_dma_err_index_valid(edim_dma_error_type_enum t);
/* get DMA error mapping entry pointer */
static const edim_dma_err_map_struct *edim_dma_err_map_get(edim_proto_enum edim_proto, edim_dma_error_type_enum t);

/*!
    \brief      poll until the specified register bit(s) become set
    \param[in]  reg: pointer to the volatile register address
    \param[in]  mask: bit mask of the bit(s) to check (must become set)
    \param[in]  timeout_cycles: maximum polling iterations; pass EDIM_TIMEOUT_INFINITE (timeout_cycles is 0) to wait indefinitely
    \param[out] none
    \retval     EDIM_ERROR_NONE: if successful, 
                EDIM_ERROR_TIMEOUT: if timeout error
 */
static edim_error_enum edim_wait_flag_set(volatile uint32_t *reg, uint32_t mask, uint32_t timeout_cycles)
{
    edim_error_enum ret = EDIM_ERROR_NONE;
    uint32_t t = timeout_cycles;
    if (timeout_cycles == EDIM_TIMEOUT_INFINITE) {
        while(((*reg) & mask) == 0U) {
        }
    } else {
        while(((*reg) & mask) == 0U) {
            if(--t == 0U) {
                break;
            }
        }
        if (t == 0U) {
            ret = EDIM_ERROR_TIMEOUT;
        }
    }
    return ret;
}

/*!
    \brief      deinit all EDIM protocol submodules (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void edim_deinit(void)
{
    edim_hdsl_deinit();
    edim_biss_deinit();
    edim_endat_deinit();
    edim_afmt_deinit();
    edim_tfmt_deinit();
}

/*!
    \brief      enable EDIM DMA for selected protocol (API_ID(0x0002U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: select BISS (supports 16 FIFOs)
      \arg        EDIM_PROTO_ENDAT: select ENDAT (supports 4 FIFOs)
      \arg        EDIM_PROTO_AFMT: select AFMT (supports 3 FIFOs)
      \arg        EDIM_PROTO_TFMT: select TFMT (supports 4 FIFOs)
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: channel 0
    \param[out] none
    \retval     EDIM_ERROR_NONE: if successful
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_dma_enable(edim_proto_enum edim_proto, edim_channel_enum edim_ch)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        switch (edim_proto) {
        case EDIM_PROTO_BISS:
            edim_biss_dma_enable();
            break;
        case EDIM_PROTO_ENDAT:
            edim_endat_dma_enable();
            break;
        case EDIM_PROTO_AFMT:
            edim_afmt_dma_enable();
            break;
        case EDIM_PROTO_TFMT:
            edim_tfmt_dma_enable();
            break;
        default:
            error = EDIM_ERROR_INVAL_PROTO;
            break;
        }
    }
    return error;
}

/*!
    \brief      disable EDIM DMA for selected protocol (API_ID(0x0003U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: select BISS
      \arg        EDIM_PROTO_ENDAT: select ENDAT
      \arg        EDIM_PROTO_AFMT: select AFMT
      \arg        EDIM_PROTO_TFMT: select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: channel 0
    \param[out] none
    \retval     EDIM_ERROR_NONE: if successful
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_dma_disable(edim_proto_enum edim_proto, edim_channel_enum edim_ch)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        switch (edim_proto) {
        case EDIM_PROTO_BISS:
            edim_biss_dma_disable();
            break;
        case EDIM_PROTO_ENDAT:
            edim_endat_dma_disable();
            break;
        case EDIM_PROTO_AFMT:
            edim_afmt_dma_disable();
            break;
        case EDIM_PROTO_TFMT:
            edim_tfmt_dma_disable();
            break;
        default:
            error = EDIM_ERROR_INVAL_PROTO;
            break;
        }
    }
    return error;
}

/*!
    \brief      flush EDIM DMA FIFO (API_ID(0x0004U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: select BISS
      \arg        EDIM_PROTO_ENDAT: select ENDAT
      \arg        EDIM_PROTO_AFMT: select AFMT
      \arg        EDIM_PROTO_TFMT: select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: channel 0
    \param[out] none
    \retval     EDIM_ERROR_NONE: if successful
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_dma_flush(edim_proto_enum edim_proto, edim_channel_enum edim_ch)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        switch (edim_proto) {
        case EDIM_PROTO_BISS:
            edim_biss_dma_flush();
            break;
        case EDIM_PROTO_ENDAT:
            edim_endat_dma_flush();
            break;
        case EDIM_PROTO_AFMT:
            edim_afmt_dma_flush();
            break;
        case EDIM_PROTO_TFMT:
            edim_tfmt_dma_flush();
            break;
        default:
            error = EDIM_ERROR_INVAL_PROTO;
            break;
        }
    }
    return error;
}

/*!
    \brief      select EDIM protocol DMA FIFO data origin (API_ID(0x0005U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: select BISS (supports 16 FIFOs)
      \arg        EDIM_PROTO_ENDAT: select ENDAT (supports 4 FIFOs)
      \arg        EDIM_PROTO_AFMT: select AFMT (supports 3 FIFOs)
      \arg        EDIM_PROTO_TFMT: select TFMT (supports 4 FIFOs)
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: channel 0
    \param[in]  fifo_selected: FIFO enable mask (protocol dependent)
                one or more parameters can be selected which is shown as below:
      \arg        EDIM_FIFOEN0 ... EDIM_FIFOEN15
    \param[out] none
    \retval     EDIM_ERROR_NONE: if successful
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_dma_select(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_fifoen_enum fifo_selected)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        uint32_t reg_select = 0U;
        switch (edim_proto) {
        case EDIM_PROTO_BISS: {
            uint32_t maskLocal = (uint32_t)fifo_selected & 0xFFFFU;
            reg_select = (maskLocal << EDIM_DMA_BISS_DFEN_START_BIT) & EDIM_BISS_DFCTL_DMA_DFEN;
            edim_biss_dma_select(reg_select);
            break;
        }
        case EDIM_PROTO_ENDAT: {
            uint32_t maskLocal = (uint32_t)fifo_selected & 0x0FU;
            reg_select = (maskLocal << EDIM_DMA_ENDAT_DFEN_START_BIT) & EDIM_ENDAT_CFG0_DFEN_MASK;
            edim_endat_dma_select(reg_select);
            break;
        }
        case EDIM_PROTO_AFMT: {
            uint32_t maskLocal = (uint32_t)fifo_selected & 0x07U;
            reg_select = (maskLocal << EDIM_DMA_AFMT_DFEN_START_BIT) & EDIM_AFMT_CFG_DFEN_MASK;
            edim_afmt_dma_select(reg_select);
            break;
        }
        case EDIM_PROTO_TFMT: {
            uint32_t maskLocal = (uint32_t)fifo_selected & 0x0FU;
            reg_select = (maskLocal << EDIM_DMA_TFMT_DFEN_START_BIT) & EDIM_TFMT_CFG_DFEN_MASK;
            edim_tfmt_dma_select(reg_select);
            break;
        }
        default:
            error = EDIM_ERROR_INVAL_PROTO;
            break;
        }
    }
    return error;
}

/*!
    \brief      read EDIM RDATA register (API_ID(0x0006U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_HDSL: EDIM select HDSL
      \arg        EDIM_PROTO_BISS: EDIM select BISS
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0
    \param[out] edim_buf: EDIM buffer structure
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_data_read(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_buf_struct *edim_buf)
{
    edim_error_enum error = EDIM_ERROR_NONE;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(edim_buf)) {
        fw_debug_report_err(EDIM_MODULE_ID, API_ID(0x0006U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if (edim_ch >= EDIM_CHANNEL_MAX) {
            error = EDIM_ERROR_INVAL_CHANNEL;
        } else if ((edim_buf == NULL) || (edim_buf->sl_nums > EDIM_SLAVES_MAX)) {
            error = EDIM_ERROR_INVAL_PARA;
        } else {
            switch (edim_proto) {
            case EDIM_PROTO_HDSL: {
                uint64_t pos = edim_hdsl_position_read();
                edim_buf->rd_words[0] = (uint32_t)(pos & 0xFFFFFFFFULL);
                edim_buf->rd_words[1] = (uint32_t)((pos >> 32) & 0xFFFFFFFFULL);
                break;
            }
            case EDIM_PROTO_BISS:
                for (uint32_t i = 0U; i < edim_buf->sl_nums; i++) {
                    uint64_t data = edim_biss_data_read(i);
                    edim_buf->rd_words[2U * i] = (uint32_t)(data & 0xFFFFFFFFU);
                    edim_buf->rd_words[2U * i + 1U] = (uint32_t)((data >> 32U) & 0xFFFFFFFFU);
                }
                break;
            case EDIM_PROTO_ENDAT:
                edim_buf->rd_words[0] = EDIM_ENDAT_RDATA0;
                edim_buf->rd_words[1] = EDIM_ENDAT_RDATA1;
                edim_buf->rd_words[2] = EDIM_ENDAT_RDATA2;
                edim_buf->rd_words[3] = EDIM_ENDAT_RDATA3;
                break;
            case EDIM_PROTO_AFMT:
                for (uint32_t i = 0U; i < edim_buf->sl_nums; i++) {
                    for (uint32_t j = 0U; j < 3U; j++) {
                        edim_buf->rd_words[3U * i + j] = edim_afmt_data_read((edim_afmt_slave_enum)i, (edim_afmt_rdata_enum)j);
                    }
                }
                break;
            case EDIM_PROTO_TFMT:
                for (uint32_t j = 0U; j < 4U; j++) {
                    edim_buf->rd_words[j] = edim_tfmt_data_read((edim_tfmt_rdata_enum)j);
                }
                break;
            default:
                error = EDIM_ERROR_INVAL_PROTO;
                break;
            }
        }
    }
    return error;
}

/*!
    \brief      set EDIM baud rate (API_ID(0x0007U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: EDIM select BISS
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0
    \param[in]  baud_rate: baud rate to be set
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_baud_set(edim_proto_enum edim_proto, edim_channel_enum edim_ch, uint32_t baud_rate)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    }
    struct baud_item { uint32_t rate; uint32_t regval; };
    const struct baud_item *table = NULL;
    uint32_t table_sz = 0U;
    uint32_t reg_mask = 0U;
    volatile uint32_t *reg_addr = NULL;
    uint32_t add_tmp = 0U;

    if (error == EDIM_ERROR_NONE) {
        if (baud_rate == 0U) {
            error = EDIM_ERROR_INVAL_PARA;
        } else {
            switch (edim_proto) {
            case EDIM_PROTO_AFMT: {
                static const struct baud_item afmt_tbl[] = {
                    { 2500000UL, EDIM_AFMT_BAUD_2_5MBPS },
                    { 4000000UL, EDIM_AFMT_BAUD_4MBPS },
                    { 6667000UL, EDIM_AFMT_BAUD_6_67MBPS },
                    { 8000000UL, EDIM_AFMT_BAUD_8MBPS },
                    {16000000UL, EDIM_AFMT_BAUD_16MBPS },
                };
                table = afmt_tbl;
                table_sz = sizeof(afmt_tbl) / sizeof(afmt_tbl[0]);
                reg_mask = EDIM_AFMT_CFG_BAUD;
                reg_addr = &EDIM_AFMT_CFG;
                break;
            }
            case EDIM_PROTO_ENDAT: {
                static const struct baud_item endat_tbl[] = {
                    {16670000UL, EDIM_ENDAT_TCLK_16_67MHz},
                    { 8330000UL, EDIM_ENDAT_TCLK_8_33MHz },
                    { 4160000UL, EDIM_ENDAT_TCLK_4_16MHz },
                    { 2000000UL, EDIM_ENDAT_TCLK_2MHz    },
                    { 1000000UL, EDIM_ENDAT_TCLK_1MHz    },
                    { 200000UL,  EDIM_ENDAT_TCLK_200KHz  },
                    { 100000UL,  EDIM_ENDAT_TCLK_100KHz  },
                };
                table = endat_tbl;
                table_sz = sizeof(endat_tbl) / sizeof(endat_tbl[0]);
                reg_mask = EDIM_ENDAT_CFG0_TCLK;
                reg_addr = &EDIM_ENDAT_CFG0;
                break;
            }
            case EDIM_PROTO_BISS: {
                uint32_t pclk1 = rcu_clock_freq_get(CK_APB1);
                uint64_t ratio_times2 = ((uint64_t)pclk1 * 2ULL) / (uint64_t)baud_rate;
                uint32_t ratio = (uint32_t)((ratio_times2 + 1ULL) / 2ULL);
                uint32_t prescaler = (ratio > 0U) ? (ratio - 1U) : 0U;
                if (prescaler < 7U) {
                    prescaler = 7U;
                }
                if (prescaler > 32767U) {
                    prescaler = 32767U;
                }
                edim_biss_ma_prescaler_config(prescaler);
                break;
            }
            default:
                error = EDIM_ERROR_INVAL_PROTO;
                break;
            }
        }
    }

    if ((error == EDIM_ERROR_NONE) && (table != NULL)) {
        int matched = 0;
        for (uint32_t i = 0U; i < table_sz; i++) {
            add_tmp = (uint32_t)table + i * 8U;
            if ((*(struct baud_item *)add_tmp).rate == baud_rate) {
                uint32_t regv = *reg_addr;
                regv &= ~reg_mask;
                regv |= (*(struct baud_item *)add_tmp).regval;
                *reg_addr = regv;
                matched = 1;
                break;
            }
        }
        if (!matched) {
            error = EDIM_ERROR_INVAL_BAUD;
        }
    }
    return error;
}

/*!
    \brief      access edim register operation (API_ID(0x0008U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: EDIM select BISS
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0
    \param[in]  config: control configuration structure
    \param[in]  timeout_cycles: control timeout time 
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_reg_access_operation(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_reg_access_config_struct *config, uint32_t timeout_cycles)
{
    edim_error_enum error = EDIM_ERROR_NONE;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(config)) {
        fw_debug_report_err(EDIM_MODULE_ID, API_ID(0x0008U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if (edim_ch >= EDIM_CHANNEL_MAX) {
            error = EDIM_ERROR_INVAL_CHANNEL;
        } else if (config == NULL) {
            error = EDIM_ERROR_INVAL_PARA;
        } else if (config->sl_index >= EDIM_SLAVES_MAX ) {
            error = EDIM_ERROR_INVAL_PARA;
        } else {
            switch (edim_proto) {
            case EDIM_PROTO_BISS: {
                if ((config->size == 0U) || (config->size > 64U)) {
                    error = EDIM_ERROR_INVAL_PARA;
                    break;
                }
                edim_biss_control_comm_struct reg_access_cmd;
                reg_access_cmd.reg_addr   = config->memaddr;
                reg_access_cmd.reg_n_byte = config->size;
                reg_access_cmd.reg_r_w    = config->reg_rw;
                reg_access_cmd.slave_id   = config->sl_index;
                for (uint32_t i = 0U; i < reg_access_cmd.reg_n_byte; i++) {
                    reg_access_cmd.r_w_data[i] = (uint8_t)config->data[i];
                }
                edim_biss_reg_access(&reg_access_cmd);
                edim_biss_send_frame(EDIM_BISS_SEND_AUTO_CTRL_FRAME);
                error = edim_wait_flag_set(&EDIM_BISS_STAT0, EDIM_BISS_STAT0_EOCC, timeout_cycles);
                break;
            }
            case EDIM_PROTO_ENDAT: {
                edim_endat_command(EDIM_ENDAT_MODE_SELECT_MEM_AREA, (uint32_t)config->memaddr, 0U);
                edim_software_trigger(edim_proto, edim_ch);
                error = edim_wait_flag_set(&EDIM_ENDAT_STAT, EDIM_ENDAT_STAT_NEXTRDYF, timeout_cycles);
                if (error != EDIM_ERROR_NONE) {
                    break;
                }
                if (config->reg_rw == EDIM_WRITE) {
                    edim_endat_command(EDIM_ENDAT_MODE_RECEIVE_PARA, (uint32_t)config->data[0U], (uint32_t)config->data[1U]);
                } else {
                    edim_endat_command(EDIM_ENDAT_MODE_SEND_PARA, (uint32_t)config->data[0U], 0U);
                }
                edim_software_trigger(edim_proto, edim_ch);
                error = edim_wait_flag_set(&EDIM_ENDAT_STAT, EDIM_ENDAT_STAT_NEXTRDYF, timeout_cycles);
                break;
            }
            case EDIM_PROTO_AFMT: {
                if (config->reg_rw == EDIM_WRITE) {
                    edim_afmt_command_with_eeprom_write((uint8_t)config->sl_index, (uint8_t)config->memaddr, (uint16_t)config->data[0]);
                } else {
                    edim_afmt_command_with_eeprom_read((uint8_t)config->sl_index, (uint8_t)config->memaddr);
                }
                edim_software_trigger(edim_proto, edim_ch);
                error = edim_wait_flag_set(&EDIM_AFMT_STAT, EDIM_AFMT_FLAG_EOC, timeout_cycles);
                break;
            }
            case EDIM_PROTO_TFMT: {
                if (config->reg_rw == EDIM_WRITE) {
                    edim_tfmt_command_with_eeprom_write((uint8_t)config->memaddr, (uint8_t)config->data[0]);
                } else {
                    edim_tfmt_command_with_eeprom_read((uint8_t)config->memaddr);
                }
                edim_software_trigger(edim_proto, edim_ch);
                error = edim_wait_flag_set(&EDIM_TFMT_STAT, EDIM_TFMT_FLAG_EOC, timeout_cycles);
                break;
            }
            default:
                error = EDIM_ERROR_INVAL_PROTO;
                break;
            }
        }
    }
    return error;
}

/*!
    \brief      edim full position acquisition operation (API_ID(0x0009U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: EDIM select BISS
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0
    \param[in]  config: control configuration structure
    \param[in]  timeout_cycles: control timeout time
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_full_pos_acquisition_operation(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_process_data_config_struct *config, uint32_t timeout_cycles)
{
    edim_error_enum error = EDIM_ERROR_NONE;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(config)) {
        fw_debug_report_err(EDIM_MODULE_ID, API_ID(0x0009U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if (edim_ch >= EDIM_CHANNEL_MAX) {
            error = EDIM_ERROR_INVAL_CHANNEL;
        } else {
            switch (edim_proto) {
            case EDIM_PROTO_BISS:
                edim_biss_send_frame(EDIM_BISS_SEND_SINGLE_DATA_FRAME_WITH_CDM_0);
                error = edim_wait_flag_set(&EDIM_BISS_STAT0, EDIM_BISS_STAT0_EODT, timeout_cycles);
                break;
            case EDIM_PROTO_ENDAT:
                edim_endat_command(EDIM_ENDAT_MODE_GET_POS, 0U, 0U);
                edim_software_trigger(edim_proto, edim_ch);
                error = edim_wait_flag_set(&EDIM_ENDAT_STAT, EDIM_ENDAT_STAT_NEXTRDYF, timeout_cycles);
                break;
            case EDIM_PROTO_AFMT: {
                if ((config == NULL) || (config->sl_index >= EDIM_SLAVES_MAX)) {
                    error = EDIM_ERROR_INVAL_PARA;
                } else {
                    uint32_t cmd = (config->commu_mode == EDIM_COMM_MODE_GLOBAL) ? EDIM_AFMT_CMD_CC_BRDABS40 : EDIM_AFMT_CMD_CC_INDABS40;
                    edim_afmt_command((uint8_t)config->sl_index, (uint8_t)cmd);
                    edim_software_trigger(edim_proto, edim_ch);
                    error = edim_wait_flag_set(&EDIM_AFMT_STAT, EDIM_AFMT_FLAG_EOC, timeout_cycles);
                }
                break;
            }
            case EDIM_PROTO_TFMT:
                edim_tfmt_command(EDIM_TFMT_DATAID_CC_RDALL);
                edim_software_trigger(edim_proto, edim_ch);
                error = edim_wait_flag_set(&EDIM_TFMT_STAT, EDIM_TFMT_FLAG_EOC, timeout_cycles);
                break;
            default:
                error = EDIM_ERROR_INVAL_PROTO;
                break;
            }
        }
    }
    return error;
}

/*!
    \brief      edim control encoder operations (API_ID(0x000AU))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: EDIM select BISS
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0
    \param[in]  config: control configuration structure
    \param[in]  timeout_cycles: control timeout time 
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_control_encoder_operation(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_control_config_struct *config, uint32_t timeout_cycles)
{
    edim_error_enum error = EDIM_ERROR_NONE;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(config)) {
        fw_debug_report_err(EDIM_MODULE_ID, API_ID(0x000AU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if (edim_ch >= EDIM_CHANNEL_MAX) {
            error = EDIM_ERROR_INVAL_CHANNEL;
        } else if (config == NULL) {
            error = EDIM_ERROR_INVAL_PARA;
        } else {
            switch (edim_proto) {
            case EDIM_PROTO_BISS: {
                static const uint32_t biss_cmd_arr[4] = { EDIM_BISS_CMD_CHECKIDA(0), EDIM_BISS_CMD_CHECKIDA(1), EDIM_BISS_CMD_ALWAYSEXE(0), EDIM_BISS_CMD_ALWAYSEXE(1) };
                if ((config->op > EDIM_CONTROL_ALL_SLAVE_COMMUNICATION_CONTROL_ACTIVE) ||
                    (config->op < EDIM_CONTROL_PROCESS_DATA_ACTIVE) ||
                    ((uint32_t)config->sl_index > (uint32_t)EDIM_CONTROL_ALL_SLAVE_COMMUNICATION_CONTROL_ACTIVE)) {
                    error = EDIM_ERROR_INVAL_PARA;
                } else {
                    edim_biss_command((uint32_t)config->sl_index, biss_cmd_arr[((uint32_t)config->op - (uint32_t)EDIM_CONTROL_PROCESS_DATA_ACTIVE)]);
                    edim_biss_send_frame(EDIM_BISS_SEND_AUTO_CTRL_FRAME);
                }
                if (error == EDIM_ERROR_NONE) {
                    error = edim_wait_flag_set(&EDIM_BISS_STAT0, EDIM_BISS_STAT0_EOCC, timeout_cycles);
                }
                break;
            }
            case EDIM_PROTO_ENDAT:
                if (config->op != EDIM_CONTROL_RESET_STATUS) {
                    error = EDIM_ERROR_INVAL_PARA;
                } else {
                    edim_endat_command(EDIM_ENDAT_MODE_RECEIVE_RESET, 0U, 0U);
                    edim_endat_data_transmission_software_trigger();
                    error = edim_wait_flag_set(&EDIM_ENDAT_STAT, EDIM_ENDAT_STAT_NEXTRDYF, timeout_cycles);
                }
                break;
            case EDIM_PROTO_AFMT: {
                static const uint32_t afmt_cmd_arr[3] = {EDIM_AFMT_CMD_CC_INDSTACLR, EDIM_AFMT_CMD_CC_ABSRST, EDIM_AFMT_CMD_CC_MUTCLR};
                if ((config->op > EDIM_CONTROL_SET_SLAVE_ADDRESS) || (config->sl_index >= EDIM_SLAVES_MAX)) {
                    error = EDIM_ERROR_INVAL_PARA;
                    break;
                }
                if (config->op == EDIM_CONTROL_SET_SLAVE_ADDRESS) {
                    edim_afmt_command((uint8_t)config->sl_index, (uint8_t)EDIM_AFMT_CMD_CC_ADDSETII);
                    edim_software_trigger(edim_proto, edim_ch);
                    error = edim_wait_flag_set(&EDIM_AFMT_STAT, EDIM_AFMT_FLAG_EOC, timeout_cycles);
                } else {
                    for (uint32_t j = 0U; j < EDIM_AFMT_RESET_OP_CNT; j++) {
                        edim_afmt_command((uint8_t)config->sl_index, (uint8_t)afmt_cmd_arr[config->op]);
                        edim_software_trigger(edim_proto, edim_ch);
                        error = edim_wait_flag_set(&EDIM_AFMT_STAT, EDIM_AFMT_FLAG_EOC, timeout_cycles);
                        if (error != EDIM_ERROR_NONE) {
                            break;
                        }
                    }
                }
                break;
            }
            case EDIM_PROTO_TFMT: {
                static const uint32_t tfmt_cmd_arr[3] = { EDIM_TFMT_DATAID_CC_RSTERR, EDIM_TFMT_DATAID_CC_RSTPOS, EDIM_TFMT_DATAID_CC_RSTTURNSERR };
                if (config->op > EDIM_CONTROL_RESET_MULTIPLE_POS) {
                    error = EDIM_ERROR_INVAL_PARA;
                    break;
                }
                for (uint32_t j = 0U; j < EDIM_TFMT_RESET_OP_CNT; j++) {
                    edim_tfmt_flag_clear(EDIM_TFMT_FLAG_EOC);
                    edim_tfmt_command(tfmt_cmd_arr[config->op]);
                    edim_software_trigger(edim_proto, edim_ch);
                    error = edim_wait_flag_set(&EDIM_TFMT_STAT, EDIM_TFMT_FLAG_EOC, timeout_cycles);
                    if (error != EDIM_ERROR_NONE) {
                        break;
                    }
                }
                break;
            }
            default:
                error = EDIM_ERROR_INVAL_PROTO;
                break;
            }
        }
    }
    return error;
}

/*!
    \brief      edim software trigger (API_ID(0x000BU))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_software_trigger(edim_proto_enum edim_proto, edim_channel_enum edim_ch)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        switch (edim_proto) {
        case EDIM_PROTO_ENDAT:
            edim_endat_data_transmission_software_trigger();
            break;
        case EDIM_PROTO_AFMT:
            edim_afmt_software_trigger();
            break;
        case EDIM_PROTO_TFMT:
            edim_tfmt_software_trigger();
            break;
        default:
            error = EDIM_ERROR_INVAL_PROTO;
            break;
        }
    }
    return error;
}

/*!
    \brief      edim hardware trigger (API_ID(0x000CU))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: EDIM select BISS
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_select_ext_trigger(edim_proto_enum edim_proto, edim_channel_enum edim_ch)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        switch (edim_proto) {
        case EDIM_PROTO_BISS:
            edim_biss_auto_transmission_config(EDIM_BISS_AUTO_DATA_TRANSMIT_EXT_TRIGGER);
            break;
        case EDIM_PROTO_ENDAT:
            edim_endat_internal_timer_trigger_period_config(EDIM_ENDAT_PERIOD_DISABLE);
            edim_endat_hardware_trigger_config(ENABLE);
            break;
        case EDIM_PROTO_AFMT:
            edim_afmt_trigger_mode_config(EDIM_AFMT_TRIGGER_TRIGSEL);
            break;
        case EDIM_PROTO_TFMT:
            edim_tfmt_trigger_mode_config(EDIM_TFMT_TRIGGER_TRIGSEL);
            break;
        default:
            error = EDIM_ERROR_INVAL_PROTO;
            break;
        }
    }
    return error;
}

/*!
    \brief      enable frame-end interrupt for a protocol (API_ID(0x000DU))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: EDIM select BISS
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0, EDIM channel 0
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
 */
edim_error_enum edim_frame_end_interrupt_enable(edim_proto_enum edim_proto, edim_channel_enum edim_ch)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        switch (edim_proto) {
        case EDIM_PROTO_AFMT:
            edim_afmt_interrupt_enable(EDIM_AFMT_INT_EOC);
            break;
        case EDIM_PROTO_TFMT:
            edim_tfmt_interrupt_enable(EDIM_TFMT_INT_EOC);
            break;
        case EDIM_PROTO_ENDAT:
            edim_endat_interrupt_enable(EDIM_ENDAT_INT_DATACHK);
            break;
        case EDIM_PROTO_BISS:
            edim_biss_interrupt_enable(EDIM_BISS_INT_EODTIE);
            break;
        default:
            error = EDIM_ERROR_INVAL_PROTO;
            break;
        }
    }
    return error;
}

/*!
    \brief      disable frame-end interrupt for a protocol (API_ID(0x000EU))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: EDIM select BISS
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_frame_end_interrupt_disable(edim_proto_enum edim_proto, edim_channel_enum edim_ch)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        switch (edim_proto) {
        case EDIM_PROTO_AFMT:
            edim_afmt_interrupt_disable(EDIM_AFMT_INT_EOC);
            break;
        case EDIM_PROTO_TFMT:
            edim_tfmt_interrupt_disable(EDIM_TFMT_INT_EOC);
            break;
        case EDIM_PROTO_ENDAT:
            edim_endat_interrupt_disable(EDIM_ENDAT_INT_DATACHK);
            break;
        case EDIM_PROTO_BISS:
            edim_biss_interrupt_disable(EDIM_BISS_INT_EODTIE);
            break;
        default:
            error = EDIM_ERROR_INVAL_PROTO;
            break;
        }
    }
    return error;
}

/*!
    \brief      get frame-end interrupt flag state (API_ID(0x000FU))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: EDIM select BISS
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0  
    \param[out]  status output flag status (SET if active)
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
 */
edim_error_enum edim_frame_end_interrupt_flag_get(edim_proto_enum edim_proto, edim_channel_enum edim_ch, FlagStatus *status)
{
    edim_error_enum error = EDIM_ERROR_NONE;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(status)) {
        fw_debug_report_err(EDIM_MODULE_ID, API_ID(0x000FU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if (edim_ch >= EDIM_CHANNEL_MAX) {
            error = EDIM_ERROR_INVAL_CHANNEL;
        } else if (status == NULL) {
            error = EDIM_ERROR_INVAL_PARA;
        } else {
            switch (edim_proto) {
            case EDIM_PROTO_AFMT:
                *status = edim_afmt_interrupt_flag_get(EDIM_AFMT_INT_FLAG_EOC);
                break;
            case EDIM_PROTO_TFMT:
                *status = edim_tfmt_interrupt_flag_get(EDIM_TFMT_INT_FLAG_EOC);
                break;
            case EDIM_PROTO_ENDAT:
                *status = edim_endat_interrupt_flag_get(EDIM_ENDAT_INT_FLAG_DATACHK);
                break;
            case EDIM_PROTO_BISS:
                *status = edim_biss_interrupt_flag_get(EDIM_BISS_INT_FLAG_EODT);
                break;
            default:
                error = EDIM_ERROR_INVAL_PROTO;
                break;
            }
        }
    }
    return error;
}

/*!
    \brief      clear frame-end interrupt flag (API_ID(0x0010U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: EDIM select BISS
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0, EDIM channel 0
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_frame_end_interrupt_flag_clear(edim_proto_enum edim_proto, edim_channel_enum edim_ch)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        switch (edim_proto) {
        case EDIM_PROTO_AFMT:
            break;
        case EDIM_PROTO_TFMT:
            break;
        case EDIM_PROTO_ENDAT:
            edim_endat_interrupt_flag_clear(EDIM_ENDAT_INT_FLAG_DATACHK);
            break;
        case EDIM_PROTO_BISS:
            edim_biss_interrupt_flag_clear(EDIM_BISS_INT_FLAG_EODT);
            break;
        default:
            error = EDIM_ERROR_INVAL_PROTO;
            break;
        }
    }
    return error;
}

/*!
    \brief      get raw frame-end status flag (independent of interrupt enable) (API_ID(0x0011U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: EDIM select BISS
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0, EDIM channel 0  
    \param[out] status output flag status (SET if active)
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
 */
edim_error_enum edim_frame_end_flag_get(edim_proto_enum edim_proto, edim_channel_enum edim_ch, FlagStatus *status)
{
    edim_error_enum error = EDIM_ERROR_NONE;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(status)) {
        fw_debug_report_err(EDIM_MODULE_ID, API_ID(0x0011U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if (edim_ch >= EDIM_CHANNEL_MAX) {
            error = EDIM_ERROR_INVAL_CHANNEL;
        } else if (status == NULL) {
            error = EDIM_ERROR_INVAL_PARA;
        } else {
            switch (edim_proto) {
            case EDIM_PROTO_AFMT:
                *status = edim_afmt_flag_get(EDIM_AFMT_FLAG_EOC);
                break;
            case EDIM_PROTO_TFMT:
                *status = edim_tfmt_flag_get(EDIM_TFMT_FLAG_EOC);
                break;
            case EDIM_PROTO_ENDAT:
                *status = edim_endat_flag_get(EDIM_ENDAT_FLAG_DATACHK);
                break;
            case EDIM_PROTO_BISS:
                *status = edim_biss_flag_get(EDIM_BISS_FLAG_EODT);
                break;
            default:
                error = EDIM_ERROR_INVAL_PROTO;
                break;
            }
        }
    }
    return error;
}

/*!
    \brief      clear raw frame-end status flag (API_ID(0x0012U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_BISS: EDIM select BISS
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_frame_end_flag_clear(edim_proto_enum edim_proto, edim_channel_enum edim_ch)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        switch (edim_proto) {
        case EDIM_PROTO_AFMT:
            break;
        case EDIM_PROTO_TFMT:
            break;
        case EDIM_PROTO_ENDAT:
            edim_endat_flag_clear(EDIM_ENDAT_FLAG_DATACHK);
            break;
        case EDIM_PROTO_BISS:
            edim_biss_flag_clear(EDIM_BISS_FLAG_EODT);
            break;
        default:
            error = EDIM_ERROR_INVAL_PROTO;
            break;
        }
    }
    return error;
}

/*!
    \brief      enable timeout interrupt for a protocol (API_ID(0x0013U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
 */
edim_error_enum edim_timeout_interrupt_enable(edim_proto_enum edim_proto, edim_channel_enum edim_ch)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        switch (edim_proto) {
        case EDIM_PROTO_AFMT:
            edim_afmt_interrupt_enable(EDIM_AFMT_INT_TOERR);
            break;
        case EDIM_PROTO_TFMT:
            edim_tfmt_interrupt_enable(EDIM_TFMT_INT_TOERR);
            break;
        case EDIM_PROTO_ENDAT:
            edim_endat_interrupt_enable(EDIM_ENDAT_INT_TO);
            break;
        default:
            error = EDIM_ERROR_INVAL_PROTO;
            break;
        }
    }
    return error;
}

/*!
    \brief      disable timeout interrupt for a protocol (API_ID(0x0014U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
 */
edim_error_enum edim_timeout_interrupt_disable(edim_proto_enum edim_proto, edim_channel_enum edim_ch)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        switch (edim_proto) {
        case EDIM_PROTO_AFMT:
            edim_afmt_interrupt_disable(EDIM_AFMT_INT_TOERR);
            break;
        case EDIM_PROTO_TFMT:
            edim_tfmt_interrupt_disable(EDIM_TFMT_INT_TOERR);
            break;
        case EDIM_PROTO_ENDAT:
            edim_endat_interrupt_disable(EDIM_ENDAT_INT_TO);
            break;
        default:
            error = EDIM_ERROR_INVAL_PROTO;
            break;
        }
    }
    return error;
}

/*!
    \brief      get timeout interrupt flag state (API_ID(0x0015U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0  
    \param[out] status: output flag status (SET if active)
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
 */
edim_error_enum edim_timeout_interrupt_flag_get(edim_proto_enum edim_proto, edim_channel_enum edim_ch, FlagStatus *status)
{
    edim_error_enum error = EDIM_ERROR_NONE;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(status)) {
        fw_debug_report_err(EDIM_MODULE_ID, API_ID(0x0015U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if (edim_ch >= EDIM_CHANNEL_MAX) {
            error = EDIM_ERROR_INVAL_CHANNEL;
        } else if (status == NULL) {
            error = EDIM_ERROR_INVAL_PARA;
        } else {
            switch (edim_proto) {
            case EDIM_PROTO_AFMT:
                *status = edim_afmt_interrupt_flag_get(EDIM_AFMT_INT_FLAG_TOERR);
                break;
            case EDIM_PROTO_TFMT:
                *status = edim_tfmt_interrupt_flag_get(EDIM_TFMT_INT_FLAG_TOERR);
                break;
            case EDIM_PROTO_ENDAT:
                *status = edim_endat_interrupt_flag_get(EDIM_ENDAT_INT_FLAG_TO);
                break;
            default:
                error = EDIM_ERROR_INVAL_PROTO;
                break;
            }
        }
    }
    return error;
}

/*!
    \brief      clear timeout interrupt flag (API_ID(0x0016U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
 */
edim_error_enum edim_timeout_interrupt_flag_clear(edim_proto_enum edim_proto, edim_channel_enum edim_ch)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        switch (edim_proto) {
        case EDIM_PROTO_AFMT:
            edim_afmt_interrupt_flag_clear(EDIM_AFMT_INT_FLAG_TOERR);
            break;
        case EDIM_PROTO_TFMT:
            edim_tfmt_interrupt_flag_clear(EDIM_TFMT_INT_FLAG_TOERR);
            break;
        case EDIM_PROTO_ENDAT:
            edim_endat_interrupt_flag_clear(EDIM_ENDAT_INT_FLAG_TO);
            break;
        default:
            error = EDIM_ERROR_INVAL_PROTO;
            break;
        }
    }
    return error;
}

/*!
    \brief      get raw timeout status flag (independent of interrupt enable) (API_ID(0x0017U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0  
    \param[out] status output flag status (SET if active)
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
 */
edim_error_enum edim_timeout_flag_get(edim_proto_enum edim_proto, edim_channel_enum edim_ch, FlagStatus *status)
{
    edim_error_enum error = EDIM_ERROR_NONE;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(status)) {
        fw_debug_report_err(EDIM_MODULE_ID, API_ID(0x0017U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if (edim_ch >= EDIM_CHANNEL_MAX) {
            error = EDIM_ERROR_INVAL_CHANNEL;
        } else if (status == NULL) {
            error = EDIM_ERROR_INVAL_PARA;
        } else {
            switch (edim_proto) {
            case EDIM_PROTO_AFMT:
                *status = edim_afmt_flag_get(EDIM_AFMT_FLAG_TOERR);
                break;
            case EDIM_PROTO_TFMT:
                *status = edim_tfmt_flag_get(EDIM_TFMT_FLAG_TOERR);
                break;
            case EDIM_PROTO_ENDAT:
                *status = edim_endat_flag_get(EDIM_ENDAT_FLAG_TO);
                break;
            default:
                error = EDIM_ERROR_INVAL_PROTO;
                break;
            }
        }
    }
    return error;
}

/*!
    \brief      clear raw timeout status flag (API_ID(0x0018U))
    \param[in]  edim_proto: EDIM protocol
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_timeout_flag_clear(edim_proto_enum edim_proto, edim_channel_enum edim_ch)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        switch (edim_proto) {
        case EDIM_PROTO_AFMT:
            edim_afmt_flag_clear(EDIM_AFMT_FLAG_TOERR);
            break;
        case EDIM_PROTO_TFMT:
            edim_tfmt_flag_clear(EDIM_TFMT_FLAG_TOERR);
            break;
        case EDIM_PROTO_ENDAT:
            edim_endat_flag_clear(EDIM_ENDAT_FLAG_TO);
            break;
        default:
            error = EDIM_ERROR_INVAL_PROTO;
            break;
        }
    }
    return error;
}

/*!
    \brief      validate DMA error type index
    \param[in]  t: DMA error type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_DMAERR_TIMEOUT: DMA request timeout error
      \arg        EDIM_DMAERR_OVERRUN: DMA FIFO overrun error
      \arg        EDIM_DMAERR_UNDERRUN: DMA FIFO underrun error
    \param[out] none
    \retval     non-zero if valid, 0 if invalid
*/
static int edim_dma_err_index_valid(edim_dma_error_type_enum t)
{
    return ((t == EDIM_DMAERR_TIMEOUT) || (t == EDIM_DMAERR_OVERRUN) || (t == EDIM_DMAERR_UNDERRUN));
}

/*!
    \brief      get DMA error mapping entry pointer
    \param[in]  edim_proto: EDIM protocol selector
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_BISS: EDIM select BISS
    \param[in]  t: DMA error type (see edim_dma_err_index_valid)
    \param[out] none
    \retval     pointer to mapping entry if valid, NULL if edim_proto or type invalid
*/
static const edim_dma_err_map_struct *edim_dma_err_map_get(edim_proto_enum edim_proto, edim_dma_error_type_enum t)
{
    const edim_dma_err_map_struct *p = NULL;
    if (edim_dma_err_index_valid(t)) {
        switch (edim_proto) {
        case EDIM_PROTO_AFMT:
            p = &edim_dma_err_map_afmt[t];
            break;
        case EDIM_PROTO_TFMT:
            p = &edim_dma_err_map_tfmt[t];
            break;
        case EDIM_PROTO_ENDAT:
            p = &edim_dma_err_map_endat[t];
            break;
        case EDIM_PROTO_BISS:
            p = &edim_dma_err_map_biss[t];
            break;
        default:
            break;
        }
    }
    return p;
}

/*!
    \brief      enable DMA error interrupt (timeout / overrun / underrun) for a protocol (API_ID(0x0019U))
    \param[in]  edim_proto: protocol selector
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_BISS: EDIM select BISS
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0  
    \param[in]  err_type: DMA error type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_DMAERR_TIMEOUT: DMA request timeout error
      \arg        EDIM_DMAERR_OVERRUN: FIFO overrun error
      \arg        EDIM_DMAERR_UNDERRUN: FIFO underrun error
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success 
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_dma_error_interrupt_enable(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_dma_error_type_enum err_type)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        const edim_dma_err_map_struct *m = edim_dma_err_map_get(edim_proto, err_type);
        if (m == NULL) {
            error = (edim_proto >= EDIM_PROTO_MAX) ? EDIM_ERROR_INVAL_PROTO : EDIM_ERROR_INVAL_PARA;
        } else {
            switch (edim_proto) {
            case EDIM_PROTO_AFMT:
                edim_afmt_interrupt_enable(m->int_enable_bit);
                break;
            case EDIM_PROTO_TFMT:
                edim_tfmt_interrupt_enable(m->int_enable_bit);
                break;
            case EDIM_PROTO_ENDAT:
                edim_endat_interrupt_enable(m->int_enable_bit);
                break;
            case EDIM_PROTO_BISS:
                edim_biss_interrupt_enable(m->int_enable_bit);
                break;
            default:
                error = EDIM_ERROR_INVAL_PROTO;
                break;
            }
        }
    }
    return error;
}

/*!
    \brief      disable DMA error interrupt (timeout / overrun / underrun) for a protocol (API_ID(0x001AU))
    \param[in]  edim_proto: protocol selector
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_BISS: EDIM select BISS
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0  
    \param[in]  err_type: DMA error type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_DMAERR_TIMEOUT: DMA request timeout error
      \arg        EDIM_DMAERR_OVERRUN: FIFO overrun error
      \arg        EDIM_DMAERR_UNDERRUN: FIFO underrun error
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_dma_error_interrupt_disable(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_dma_error_type_enum err_type)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        const edim_dma_err_map_struct *m = edim_dma_err_map_get(edim_proto, err_type);
        if (m == NULL) {
            error = (edim_proto >= EDIM_PROTO_MAX) ? EDIM_ERROR_INVAL_PROTO : EDIM_ERROR_INVAL_PARA;
        } else {
            switch (edim_proto) {
            case EDIM_PROTO_AFMT:
                edim_afmt_interrupt_disable(m->int_enable_bit);
                break;
            case EDIM_PROTO_TFMT:
                edim_tfmt_interrupt_disable(m->int_enable_bit);
                break;
            case EDIM_PROTO_ENDAT:
                edim_endat_interrupt_disable(m->int_enable_bit);
                break;
            case EDIM_PROTO_BISS:
                edim_biss_interrupt_disable(m->int_enable_bit);
                break;
            default:
                error = EDIM_ERROR_INVAL_PROTO;
                break;
            }
        }
    }
    return error;
}

/*!
    \brief      get DMA error interrupt flag (timeout / overrun / underrun) for a protocol (API_ID(0x001BU))
    \param[in]  edim_proto: protocol selector
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_BISS: EDIM select BISS
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0  
    \param[in]  err_type: DMA error type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_DMAERR_TIMEOUT: DMA request timeout error
      \arg        EDIM_DMAERR_OVERRUN: FIFO overrun error
      \arg        EDIM_DMAERR_UNDERRUN: FIFO underrun error
    \param[out] status: SET if active, RESET otherwise
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_dma_error_interrupt_flag_get(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_dma_error_type_enum err_type, FlagStatus *status)
{
    edim_error_enum error = EDIM_ERROR_NONE;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(status)) {
        fw_debug_report_err(EDIM_MODULE_ID, API_ID(0x001BU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        const edim_dma_err_map_struct *m = NULL;
        if (edim_ch >= EDIM_CHANNEL_MAX) {
            error = EDIM_ERROR_INVAL_CHANNEL;
        } else if (status == NULL) {
            error = EDIM_ERROR_INVAL_PARA;
        } else {
            m = edim_dma_err_map_get(edim_proto, err_type);
            if (m == NULL) {
                error = (edim_proto >= EDIM_PROTO_MAX) ? EDIM_ERROR_INVAL_PROTO : EDIM_ERROR_INVAL_PARA;
            } else {
                switch (edim_proto) {
                case EDIM_PROTO_AFMT:
                    *status = edim_afmt_interrupt_flag_get((edim_afmt_interrupt_flag_enum)m->int_flag_bit);
                    break;
                case EDIM_PROTO_TFMT:
                    *status = edim_tfmt_interrupt_flag_get((edim_tfmt_interrupt_flag_enum)m->int_flag_bit);
                    break;
                case EDIM_PROTO_ENDAT:
                    *status = edim_endat_interrupt_flag_get((edim_endat_interrupt_flag_enum)m->int_flag_bit);
                    break;
                case EDIM_PROTO_BISS:
                    *status = edim_biss_interrupt_flag_get((edim_biss_interrupt_flag_enum)m->int_flag_bit);
                    break;
                default:
                    error = EDIM_ERROR_INVAL_PROTO;
                    break;
                }
            }
        }
    }
    return error;
}

/*!
    \brief      clear DMA error interrupt flag (timeout / overrun / underrun) for a protocol (API_ID(0x001CU))
    \param[in]  edim_proto: protocol selector
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_BISS: EDIM select BISS
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0  
    \param[in]  err_type: DMA error type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_DMAERR_TIMEOUT: DMA request timeout error
      \arg        EDIM_DMAERR_OVERRUN: FIFO overrun error
      \arg        EDIM_DMAERR_UNDERRUN: FIFO underrun error
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_dma_error_interrupt_flag_clear(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_dma_error_type_enum err_type)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        const edim_dma_err_map_struct *m = edim_dma_err_map_get(edim_proto, err_type);
        if (m == NULL) {
            error = (edim_proto >= EDIM_PROTO_MAX) ? EDIM_ERROR_INVAL_PROTO : EDIM_ERROR_INVAL_PARA;
        } else {
            switch (edim_proto) {
            case EDIM_PROTO_AFMT:
                edim_afmt_interrupt_flag_clear((edim_afmt_interrupt_flag_enum)m->int_flag_bit);
                break;
            case EDIM_PROTO_TFMT:
                edim_tfmt_interrupt_flag_clear((edim_tfmt_interrupt_flag_enum)m->int_flag_bit);
                break;
            case EDIM_PROTO_ENDAT:
                edim_endat_interrupt_flag_clear((edim_endat_interrupt_flag_enum)m->int_flag_bit);
                break;
            case EDIM_PROTO_BISS:
                edim_biss_interrupt_flag_clear((edim_biss_interrupt_flag_enum)m->int_flag_bit);
                break;
            default:
                error = EDIM_ERROR_INVAL_PROTO;
                break;
            }
        }
    }
    return error;
}

/*!
    \brief      get raw DMA error status (timeout / overrun / underrun) independent of interrupt enable (API_ID(0x001DU))
    \param[in]  edim_proto: protocol selector
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_BISS: EDIM select BISS
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0  
    \param[in]  err_type: DMA error type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_DMAERR_TIMEOUT: DMA request timeout error
      \arg        EDIM_DMAERR_OVERRUN: FIFO overrun error
      \arg        EDIM_DMAERR_UNDERRUN: FIFO underrun error
    \param[out] status: SET if active, RESET otherwise
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_dma_error_flag_get(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_dma_error_type_enum err_type, FlagStatus *status)
{
    edim_error_enum error = EDIM_ERROR_NONE;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(status)) {
        fw_debug_report_err(EDIM_MODULE_ID, API_ID(0x001DU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        const edim_dma_err_map_struct *m = NULL;
        if (edim_ch >= EDIM_CHANNEL_MAX) {
            error = EDIM_ERROR_INVAL_CHANNEL;
        } else if (status == NULL) {
            error = EDIM_ERROR_INVAL_PARA;
        } else {
            m = edim_dma_err_map_get(edim_proto, err_type);
            if (m == NULL) {
                error = (edim_proto >= EDIM_PROTO_MAX) ? EDIM_ERROR_INVAL_PROTO : EDIM_ERROR_INVAL_PARA;
            } else {
                switch (edim_proto) {
                case EDIM_PROTO_AFMT:
                    *status = edim_afmt_flag_get(m->status_flag_bit);
                    break;
                case EDIM_PROTO_TFMT:
                    *status = edim_tfmt_flag_get(m->status_flag_bit);
                    break;
                case EDIM_PROTO_ENDAT:
                    *status = edim_endat_flag_get(m->status_flag_bit);
                    break;
                case EDIM_PROTO_BISS:
                    *status = edim_biss_flag_get((edim_biss_flag_enum)m->status_flag_bit);
                    break;
                default:
                    error = EDIM_ERROR_INVAL_PROTO;
                    break;
                }
            }
        }
    }
    return error;
}

/*!
    \brief      clear raw DMA error status flag (timeout / overrun / underrun) for a protocol (API_ID(0x001EU))
    \param[in]  edim_proto: protocol selector
                only one parameter can be selected which is shown as below:
      \arg        EDIM_PROTO_AFMT: EDIM select AFMT
      \arg        EDIM_PROTO_TFMT: EDIM select TFMT
      \arg        EDIM_PROTO_ENDAT: EDIM select ENDAT
      \arg        EDIM_PROTO_BISS: EDIM select BISS
    \param[in]  edim_ch: EDIM channel
                only one parameter can be selected which is shown as below:
      \arg        EDIM_CHANNEL_0: EDIM channel 0 
    \param[in]  err_type: DMA error type
                only one parameter can be selected which is shown as below:
      \arg        EDIM_DMAERR_TIMEOUT: DMA request timeout error
      \arg        EDIM_DMAERR_OVERRUN: FIFO overrun error
      \arg        EDIM_DMAERR_UNDERRUN: FIFO underrun error
    \param[out] none
    \retval     EDIM_ERROR_NONE: on success
                EDIM_ERROR_INVAL_CHANNEL: if edim channel error
                EDIM_ERROR_INVAL_PARA: if err_type unsupported for edim_proto
                EDIM_ERROR_INVAL_PROTO: if edim_proto invalid
*/
edim_error_enum edim_dma_error_flag_clear(edim_proto_enum edim_proto, edim_channel_enum edim_ch, edim_dma_error_type_enum err_type)
{
    edim_error_enum error = EDIM_ERROR_NONE;
    if (edim_ch >= EDIM_CHANNEL_MAX) {
        error = EDIM_ERROR_INVAL_CHANNEL;
    } else {
        const edim_dma_err_map_struct *m = edim_dma_err_map_get(edim_proto, err_type);
        if (m == NULL) {
            error = (edim_proto >= EDIM_PROTO_MAX) ? EDIM_ERROR_INVAL_PROTO : EDIM_ERROR_INVAL_PARA;
        } else {
            switch (edim_proto) {
            case EDIM_PROTO_AFMT:
                edim_afmt_flag_clear(m->status_flag_bit);
                break;
            case EDIM_PROTO_TFMT:
                edim_tfmt_flag_clear(m->status_flag_bit);
                break;
            case EDIM_PROTO_ENDAT:
                edim_endat_flag_clear(m->status_flag_bit);
                break;
            case EDIM_PROTO_BISS:
                edim_biss_flag_clear((edim_biss_flag_enum)m->status_flag_bit);
                break;
            default:
                error = EDIM_ERROR_INVAL_PROTO;
                break;
            }
        }
    }
    return error;
}
