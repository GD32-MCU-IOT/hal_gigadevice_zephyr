/*!
    \file    gd32h77x_78x_err_report.h
    \brief   Reporting Error driver

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

#ifndef ERR_REPORT_H
#define ERR_REPORT_H

#include <stdint.h>

/* define the size of the error report buffer */
#define ERR_REPORT_BUFFER_SIZE          2U

/* define the unique identifier of peripherals */
#define ADC_MODULE_ID                                     ((uint8_t)0x01U)               /*!< ADC module ID */
#define CAU_MODULE_ID                                     ((uint8_t)0x02U)               /*!< CAU module ID */
#define CAN_MODULE_ID                                     ((uint8_t)0x03U)               /*!< CAN module ID */
#define CMP_MODULE_ID                                     ((uint8_t)0x04U)               /*!< CMP module ID */
#define CPDM_MODULE_ID                                    ((uint8_t)0x05U)               /*!< CPDM module ID */
#define CRC_MODULE_ID                                     ((uint8_t)0x06U)               /*!< CRC module ID */
#define CTC_MODULE_ID                                     ((uint8_t)0x07U)               /*!< CTC module ID */
#define DAC_MODULE_ID                                     ((uint8_t)0x08U)               /*!< DAC module ID */
#define DBG_MODULE_ID                                     ((uint8_t)0x09U)               /*!< DBG module ID */
#define DCI_MODULE_ID                                     ((uint8_t)0x0AU)               /*!< DCI module ID */
#define DMA_MODULE_ID                                     ((uint8_t)0x0BU)               /*!< DMA module ID */
#define DSI_MODULE_ID                                     ((uint8_t)0x0CU)               /*!< DSI module ID */
#define EDIM_AFMT_MODULE_ID                               ((uint8_t)0x0DU)               /*!< EDIM AFMT module ID */
#define EDIM_BISS_MODULE_ID                               ((uint8_t)0x0EU)               /*!< EDIM BISS module ID */
#define EDIM_ENDAT_MODULE_ID                              ((uint8_t)0x0FU)               /*!< EDIM ENDAT module ID */
#define EDIM_HDSL_MODULE_ID                               ((uint8_t)0x10U)               /*!< EDIM HSDL module ID */
#define EDIM_MODULE_ID                                    ((uint8_t)0x11U)               /*!< EDIM module ID */
#define EDOUT_MODULE_ID                                   ((uint8_t)0x12U)               /*!< EDOUT module ID */
#define ENET_MODULE_ID                                    ((uint8_t)0x13U)               /*!< ENET module ID */
#define ESC_MODULE_ID                                     ((uint8_t)0x14U)               /*!< ESC module ID */
#define EXMC_MODULE_ID                                    ((uint8_t)0x15U)               /*!< EXMC module ID */
#define EXTI_MODULE_ID                                    ((uint8_t)0x16U)               /*!< EXTI module ID */
#define FAC_MODULE_ID                                     ((uint8_t)0x17U)               /*!< FAC module ID */
#define FFT_MODULE_ID                                     ((uint8_t)0x18U)               /*!< FFT module ID */
#define FWDGT_MODULE_ID                                   ((uint8_t)0x19U)               /*!< FWDGT module ID */
#define GPIO_MODULE_ID                                    ((uint8_t)0x1AU)               /*!< GPIO module ID */
#define GPSI_MODULE_ID                                    ((uint8_t)0x1BU)               /*!< GPSI module ID */
#define HAU_MODULE_ID                                     ((uint8_t)0x1CU)               /*!< HAU module ID */
#define HPDF_MODULE_ID                                    ((uint8_t)0x1DU)               /*!< HPDF module ID */
#define HWSEM_MODULE_ID                                   ((uint8_t)0x1EU)               /*!< HWSEM module ID */
#define I2C_MODULE_ID                                     ((uint8_t)0x1FU)               /*!< I2C module ID */
#define IPA_MODULE_ID                                     ((uint8_t)0x20U)               /*!< IPA module ID */
#define LPDTS_MODULE_ID                                   ((uint8_t)0x21U)               /*!< LPDTS module ID */
#define MDIO_MODULE_ID                                    ((uint8_t)0x22U)               /*!< MDIO module ID */
#define MDMA_MODULE_ID                                    ((uint8_t)0x23U)               /*!< MDMA module ID */
#define MISC_MODULE_ID                                    ((uint8_t)0x24U)               /*!< MISC module ID */
#define NVMC_MODULE_ID                                    ((uint8_t)0x25U)               /*!< NVMC module ID */
#define OSPI_MODULE_ID                                    ((uint8_t)0x26U)               /*!< OSPI module ID */
#define OSPIM_MODULE_ID                                   ((uint8_t)0x27U)               /*!< OSPIM module ID */
#define PKCAU_MODULE_ID                                   ((uint8_t)0x28U)               /*!< PKCAU module ID */
#define PMU_MODULE_ID                                     ((uint8_t)0x29U)               /*!< PMU module ID */
#define RAMECCMU_MODULE_ID                                ((uint8_t)0x2AU)               /*!< RAMECCMU module ID */
#define RCU_MODULE_ID                                     ((uint8_t)0x2BU)               /*!< RCU module ID */
#define RDCM_MODULE_ID                                    ((uint8_t)0x2CU)               /*!< RDCM module ID */
#define RSPDIF_MODULE_ID                                  ((uint8_t)0x2DU)               /*!< RSPDIF module ID */
#define RTC_MODULE_ID                                     ((uint8_t)0x2EU)               /*!< RTC module ID */
#define RTDEC_MODULE_ID                                   ((uint8_t)0x2FU)               /*!< RTDEC module ID */
#define SAI_MODULE_ID                                     ((uint8_t)0x30U)               /*!< SAI module ID */
#define SDIO_MODULE_ID                                    ((uint8_t)0x31U)               /*!< SDIO module ID */
#define SPI_MODULE_ID                                     ((uint8_t)0x32U)               /*!< SPI module ID */
#define SYSCFG_MODULE_ID                                  ((uint8_t)0x33U)               /*!< SYSCFG module ID */
#define TIMER_MODULE_ID                                   ((uint8_t)0x34U)               /*!< TIMER module ID */
#define TLI_MODULE_ID                                     ((uint8_t)0x35U)               /*!< TLI module ID */
#define TMU_MODULE_ID                                     ((uint8_t)0x36U)               /*!< TMU module ID */
#define TRIGSEL_MODULE_ID                                 ((uint8_t)0x37U)               /*!< TRIGSEL module ID */
#define TRNG_MODULE_ID                                    ((uint8_t)0x38U)               /*!< TRNG module ID */
#define USART_MODULE_ID                                   ((uint8_t)0x39U)               /*!< USART module ID */
#define USBHS_MODULE_ID                                   ((uint8_t)0x3AU)               /*!< USBHS module ID */
#define VREF_MODULE_ID                                    ((uint8_t)0x3BU)               /*!< VREF module ID */
#define WWDGT_MODULE_ID                                   ((uint8_t)0x3CU)               /*!< WWDGT module ID */

/* define the unique identifier of error type */
#define ERR_PERIPH                                        ((uint8_t)0x01U)               /*!< peripheral error */
#define ERR_PARAM_POINTER                                 ((uint8_t)0x02U)               /*!< invalid pointer */
#define ERR_PARAM_OUT_OF_RANGE                            ((uint8_t)0x03U)               /*!< out of range */
#define ERR_PARAM_INVALID                                 ((uint8_t)0x04U)               /*!< invalid parameter */

/* define the unique identifier of API */
#define API_ID(x)                                         ((uint16_t)(x))                /*!< API ID */

/* definitions for parameter checking */
#define NOT_VALID_POINTER(x)                              ((void *) 0 == (x))            /*!< check the invalid pointer */

/* defining the structure to store the parameters of report error function */
typedef struct {
    /* module ID where the error occurred */
    uint16_t moduleid;
    /* API ID associated with the error */
    uint16_t apiid;
    /* error ID indicating the specific error type */
    uint8_t errid;
} err_report_struct;

/* declare external arrays and variables for error reporting */
extern err_report_struct err_report_buffer[ERR_REPORT_BUFFER_SIZE];
/* index to track the next available position in the error report buffer */
extern uint8_t err_report_buff_index;

/* reporting errors in debug mode */
void fw_debug_report_err(uint16_t moduleid, uint16_t apiid, uint8_t errid);

#endif /* ERR_REPORT_H */
