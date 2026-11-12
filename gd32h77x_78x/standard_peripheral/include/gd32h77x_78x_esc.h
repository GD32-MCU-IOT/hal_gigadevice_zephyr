/*!
    \file    gd32h77x_78x_esc.h
    \brief   definitions for the ESC

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


#ifndef GD32H77X_78X_ESC_H
#define GD32H77X_78X_ESC_H

#include "gd32h77x_78x.h"

#define ESC                                    ESC_BASE

/* ESC core control registers definitions */
#define ESC_CCTL_DATA                     REG32((ESC) + 0x00003300U)                 /*!< ESC CCTL data register */
#define ESC_CCTL_CMD                      REG32((ESC) + 0x00003304U)                 /*!< ESC CCTL command register */
#define ESC_PRAM_FIFO_DR                  REG32((ESC) + 0x00003310U)                 /*!< ESC process ram read data fifo register */
#define ESC_PRAM_ALR                      REG32((ESC) + 0x00003314U)                 /*!< ESC process ram read address length register */
#define ESC_PRAM_CR                       REG32((ESC) + 0x00003318U)                 /*!< ESC process ram read command register */
#define ESC_PRAM_FIFO_DW                  REG32((ESC) + 0x00003320U)                 /*!< ESC process ram write data fifo register */
#define ESC_PRAM_ALW                      REG32((ESC) + 0x00003324U)                 /*!< ESC process ram write address and length register */
#define ESC_PRAM_CW                       REG32((ESC) + 0x00003328U)                 /*!< ESC process ram write command register */
#define ESC_CTL                           REG32((ESC) + 0x00003330U)                 /*!< ESC control register */
#define ESC_SYNC0                         REG32((ESC) + 0x00003334U)                 /*!< ESC sync0 register */
#define ESC_SYNC1                         REG32((ESC) + 0x00003338U)                 /*!< ESC sync1 register */

/* ESC core registers definitions */
#define ESC_TYPE                          REG32((ESC) + 0x00000000U)                 /*!< Type of EtherCAT controller register */
#define ESC_REVISION                      REG32((ESC) + 0x00000001U)                 /*!< Revision of EtherCAT controller register */
#define ESC_BUILD                         REG32((ESC) + 0x00000002U)                 /*!< Build of EtherCAT controller register */
#define ESC_FMMUS                         REG32((ESC) + 0x00000004U)                 /*!< ESC FMMU numbers supported register */
#define ESC_SYNCMS                        REG32((ESC) + 0x00000005U)                 /*!< ESC SyncManagers numbers supported register */
#define ESC_RAMSIZE                       REG32((ESC) + 0x00000006U)                 /*!< ESC RAM Size register */
#define ESC_PORT_DESC                     REG32((ESC) + 0x00000007U)                 /*!< ESC Port Descriptor register */
#define ESC_FEATURE                       REG32((ESC) + 0x00000008U)                 /*!< ESC Feature supported register */
#define ESC_STATION_ADDR                  REG32((ESC) + 0x00000010U)                 /*!< ESC Configured Station Address register */
#define ESC_STATION_ALS                   REG32((ESC) + 0x00000012U)                 /*!< ESC Configured Station Alias register */
#define ESC_REG_WEN                       REG32((ESC) + 0x00000020U)                 /*!< ESC Register Write Enable */
#define ESC_REG_WP                        REG32((ESC) + 0x00000021U)                 /*!< ESC Register Write Protection */
#define ESC_WEN                           REG32((ESC) + 0x00000030U)                 /*!< ESC Write Enable register */
#define ESC_WP                            REG32((ESC) + 0x00000031U)                 /*!< ESC Write Protection register */
#define ESC_RST_ECAT                      REG32((ESC) + 0x00000040U)                 /*!< ESC Reset ECAT register */
#define ESC_RST_PDI                       REG32((ESC) + 0x00000041U)                 /*!< ESC Reset PDI register */
#define ESC_DL_CTL                        REG32((ESC) + 0x00000100U)                 /*!< ESC DL Control register */
#define ESC_PHYSICAL_RW_OFFSET            REG32((ESC) + 0x00000108U)                 /*!< ESC Physical Read/Write Offset register */
#define ESC_DL_STAT                       REG32((ESC) + 0x00000110U)                 /*!< ESC DL Status register */
#define ESC_AL_CTL                        REG32((ESC) + 0x00000120U)                 /*!< ESC AL Control register */
#define ESC_AL_STAT                       REG32((ESC) + 0x00000130U)                 /*!< ESC AL Status register */
#define ESC_AL_STAT_CODE                  REG32((ESC) + 0x00000134U)                 /*!< ESC AL Status Code register */
#define ESC_RUN_LED_OVRD                  REG32((ESC) + 0x00000138U)                 /*!< ESC RUN LED Override register */
#define ESC_ERR_LED_OVRD                  REG32((ESC) + 0x00000139U)                 /*!< ESC ERR LED Override register */
#define ESC_PDI_CTL                       REG32((ESC) + 0x00000140U)                 /*!< ESC PDI Control register */
#define ESC_CFG                           REG32((ESC) + 0x00000141U)                 /*!< ESC Configuration register */
#define ESC_PDI_INFO                      REG32((ESC) + 0x0000014EU)                 /*!< ESC PDI Information register */
#define ESC_PDI_CFG                       REG32((ESC) + 0x00000150U)                 /*!< ESC PDI Configuration register */
#define ESC_SL_CFG                        REG32((ESC) + 0x00000151U)                 /*!< ESC PDI Sync/Latch[1:0] Configuration register */
#define ESC_PDI_EXT_CFG                   REG32((ESC) + 0x00000152U)                 /*!< ESC PDI Extended Configuration register */
#define ESC_EVT_MSK                       REG32((ESC) + 0x00000200U)                 /*!< ESC Event Mask register */
#define ESC_PDI_AL_EVT                    REG32((ESC) + 0x00000204U)                 /*!< ESC PDI AL Event Mask register */
#define ESC_EVT_REQ                       REG32((ESC) + 0x00000210U)                 /*!< ESC PDI AL Event Request register */
#define ESC_AL_EVT_REQ                    REG32((ESC) + 0x00000220U)                 /*!< ESC AL Event Request register */
#define RX_PORTX_ERR(x)                   REG32((ESC) + 0x00000300U + 2U * (x))      /*!< RX Error PORT X register, x = 0...3 */
#define FWD_RX_PORTX_ERR(x)               REG32((ESC) + 0x00000308U + (x))           /*!< Forwarded RX Error PORT X register, x = 0...3 */
#define ESC_PU_ERR                        REG32((ESC) + 0x0000030CU)                 /*!< ESC Processing Unit Error register */
#define ESC_PDI_ERR                       REG32((ESC) + 0x0000030DU)                 /*!< ESC PDI Error Counter register */
#define ESC_PORTX_LOST_LINK(x)            REG32((ESC) + 0x00000310U + (x))           /*!< ESC PORT X Lost Link register, x = 0...3 */
#define ESC_WDG_DIV                       REG32((ESC) + 0x00000400U)                 /*!< ESC Watchdog Divider register */
#define ESC_WDG_TIME_PDI                  REG32((ESC) + 0x00000410U)                 /*!< ESC Watchdog Time PDI register */
#define ESC_WDG_TIME_PDATA                REG32((ESC) + 0x00000420U)                 /*!< ESC Watchdog Time Process Data register */
#define ESC_WDG_STAT_PDATA                REG32((ESC) + 0x00000440U)                 /*!< ESC Watchdog Status Process Data register */
#define ESC_WDG_CNT_PDATA                 REG32((ESC) + 0x00000442U)                 /*!< ESC Watchdog Counter Process Data register */
#define ESC_WDG_CNT_PDI                   REG32((ESC) + 0x00000443U)                 /*!< ESC Watchdog Counter PDI register */
#define ESC_EEPROM_CFG                    REG32((ESC) + 0x00000500U)                 /*!< ESC EEPROM Configuration register */
#define ESC_EEPROM_PDI_ACC                REG32((ESC) + 0x00000501U)                 /*!< ESC EEPROM PDI Access register */
#define ESC_EEPROM_CS                     REG32((ESC) + 0x00000502U)                 /*!< ESC EEPROM Control / Status register */
#define ESC_EEPROM_ADDR                   REG32((ESC) + 0x00000504U)                 /*!< ESC EEPROM Address register */
#define ESC_EEPROM_DATA                   REG32((ESC) + 0x00000508U)                 /*!< ESC EEPROM Data register */
#define ESC_MII_MNG_CTL                   REG32((ESC) + 0x00000510U)                 /*!< ESC MII Management Control register */
#define ESC_MII_MNG_STAT                  REG32((ESC) + 0x00000511U)                 /*!< ESC MII Management Status register */
#define ESC_PHY_ADDR                      REG32((ESC) + 0x00000512U)                 /*!< ESC PHY Address register */
#define ESC_PHY_REG_ADDR                  REG32((ESC) + 0x00000513U)                 /*!< ESC PHY Register Address register */
#define ESC_PHY_DATA                      REG32((ESC) + 0x00000514U)                 /*!< ESC PHY Data register */
#define MIIM_ECAT_ACC_STAT                REG32((ESC) + 0x00000516U)                 /*!< MII Management ECAT Access State register */
#define MIIM_PDI_ACC_STAT                 REG32((ESC) + 0x00000517U)                 /*!< MII Management PDI Access State register */
#define PHY_PORT_STAT(x)                  REG32((ESC) + 0x00000518U + (x))           /*!< PHY Port register, x = 0...3 */
#define FMMU_LOGIC_ADDR(x)                REG32((ESC) + 0x00000600U + 0x10U * (x))   /*!< Logical Start Address FMMU x register, x = 0...7 */
#define FMMU_LENGTH(x)                    REG32((ESC) + 0x00000604U + 0x10U * (x))   /*!< FMMU x Length register, x = 0...7 */
#define FMMU_STRA_BIT(x)                  REG32((ESC) + 0x00000606U + 0x10U * (x))   /*!< FMMU x Start Address Bit register, x = 0...7 */
#define FMMU_STOP_BIT(x)                  REG32((ESC) + 0x00000607U + 0x10U * (x))   /*!< FMMU x Logical Stop Bit register, x = 0...7 */
#define FMMU_ADDR(x)                      REG32((ESC) + 0x00000608U + 0x10U * (x))   /*!< FMMU x Physical Start Address register, x = 0...7 */
#define FMMU_PSBIT(x)                     REG32((ESC) + 0x0000060AU + 0x10U * (x))   /*!< FMMU x Physical Start Bit register, x = 0...7 */
#define FMMU_TYPE(x)                      REG32((ESC) + 0x0000060BU + 0x10U * (x))   /*!< FMMU x Type register, x = 0...7 */
#define FMMU_ACTIVE(x)                    REG32((ESC) + 0x0000060CU + 0x10U * (x))   /*!< FMMU x Activate register, x = 0...7 */
#define SM_START_ADDR(x)                  REG32((ESC) + 0x00000800U + 0x10U * (x))   /*!< SM x Physical Start Address register, x = 0...7 */
#define SM_LENGTH(x)                      REG32((ESC) + 0x00000802U + 0x10U * (x))   /*!< SM x Length register, x = 0...7 */
#define SM_CTL(x)                         REG32((ESC) + 0x00000804U + 0x10U * (x))   /*!< SM x Control register, x = 0...7 */
#define SM_STAT(x)                        REG32((ESC) + 0x00000805U + 0x10U * (x))   /*!< SM x Status register, x = 0...7 */
#define SM_ACTIVE(x)                      REG32((ESC) + 0x00000806U + 0x10U * (x))   /*!< SM x Activate register, x = 0...7 */
#define SM_PDI_CTL(x)                     REG32((ESC) + 0x00000807U + 0x10U * (x))   /*!< SM x PDI Control register, x = 0...7 */
#define ESC_RCV_TIMEP0                    REG32((ESC) + 0x00000900U)                 /*!< ESC Receive Time port0 register */
#define ESC_RCV_TIMEP1                    REG32((ESC) + 0x00000904U)                 /*!< ESC Receive Time port1 register */
#define ESC_RCV_TIMEP2                    REG32((ESC) + 0x00000908U)                 /*!< ESC Receive Time port2 register */
#define ESC_SYS_TIME                      REG32((ESC) + 0x00000910U)                 /*!< ESC System Time register */
#define ESC_RCVT_ECAT_PU                  REG32((ESC) + 0x00000918U)                 /*!< ESC Receive Time ECAT Processing Unit register */
#define ESC_SYS_TIME_OFFSET               REG32((ESC) + 0x00000920U)                 /*!< ESC System Time Offset register */
#define ESC_SYS_TIME_DELAY                REG32((ESC) + 0x00000928U)                 /*!< ESC System Time Delay register */
#define ESC_SYS_TIME_DIFF                 REG32((ESC) + 0x0000092CU)                 /*!< ESC System Time Difference register */
#define ESC_SPD_CNT_START                 REG32((ESC) + 0x00000930U)                 /*!< ESC Speed Counter Start register */
#define ESC_SPD_CNT_DIFF                  REG32((ESC) + 0x00000932U)                 /*!< ESC Speed Counter Diff register */
#define ESC_SYS_TIME_DIFF_FD              REG32((ESC) + 0x00000934U)                 /*!< ESC System Time Difference Filter Depth register */
#define ESC_SPD_CNT_FD                    REG32((ESC) + 0x00000935U)                 /*!< ESC Speed Counter Filter Depth register */
#define ESC_CYC_UNIT_CTL                  REG32((ESC) + 0x00000980U)                 /*!< ESC Cyclic Unit Control register */
#define ESC_REG_ACT                       REG32((ESC) + 0x00000981U)                 /*!< ESC Register Activation register */
#define ESC_PULSE_LEN                     REG32((ESC) + 0x00000982U)                 /*!< ESC Pulse Length of SyncSignals register */
#define ESC_ACT_STAT                      REG32((ESC) + 0x00000984U)                 /*!< ESC Activation Status register */
#define ESC_SYNC0_STAT                    REG32((ESC) + 0x0000098EU)                 /*!< ESC SYNC0 Status register */
#define ESC_SYNC1_STAT                    REG32((ESC) + 0x0000098FU)                 /*!< ESC SYNC1 Status register */
#define ESC_START_TIME_CO                 REG32((ESC) + 0x00000990U)                 /*!< ESC Start Time Cyclic Operation register */
#define ESC_NXT_SYNC1_PULSE               REG32((ESC) + 0x00000998U)                 /*!< ESC Next SYNC1 Pulse register */
#define ESC_SYNC0_CYC_TIME                REG32((ESC) + 0x000009A0U)                 /*!< ESC SYNC0 Cycle Time register */
#define ESC_SYNC1_CYC_TIME                REG32((ESC) + 0x000009A4U)                 /*!< ESC SYNC1 Cycle Time register */
#define ESC_LATCH0_CTL                    REG32((ESC) + 0x000009A8U)                 /*!< ESC Latch0 Control register */
#define ESC_LATCH1_CTL                    REG32((ESC) + 0x000009A9U)                 /*!< ESC Latch1 Control register */
#define ESC_LATCH0_STAT                   REG32((ESC) + 0x000009AEU)                 /*!< ESC Latch0 Status register */
#define ESC_LATCH1_STAT                   REG32((ESC) + 0x000009AFU)                 /*!< ESC Latch1 Status register */
#define ESC_LATCH0_TIME_PE                REG32((ESC) + 0x000009B0U)                 /*!< ESC Latch0 Time Positive Edge register */
#define ESC_LATCH0_TIME_NE                REG32((ESC) + 0x000009B8U)                 /*!< ESC Latch0 Time Negative Edge register */
#define ESC_LATCH1_TIME_PE                REG32((ESC) + 0x000009C0U)                 /*!< ESC Latch1 Time Positive Edge register */
#define ESC_LATCH1_TIME_NE                REG32((ESC) + 0x000009C8U)                 /*!< ESC Latch1 Time Negative Edge register */
#define ESC_BUF_CET                       REG32((ESC) + 0x000009F0U)                 /*!< ESC Buffer Change Event Time register */
#define ESC_PDI_BUF_SET                   REG32((ESC) + 0x000009F8U)                 /*!< ESC PDI Buffer Start Event Time register */
#define ESC_PDI_BUF_CET                   REG32((ESC) + 0x000009FCU)                 /*!< ESC PDI Buffer Change Event Time register */
#define ESC_PRODUCT_ID                    REG32((ESC) + 0x00000E00U)                 /*!< ESC Product ID register */
#define ESC_VENDOR_ID                     REG32((ESC) + 0x00000E08U)                 /*!< ESC Vendor ID register */
#define ESC_DIG_DATA                      REG32((ESC) + 0x00000F00U)                 /*!< ESC Digital I/O Output Data register */
#define ESC_GP_OUTPUT                     REG32((ESC) + 0x00000F10U)                 /*!< ESC General Purpose Outputs register */
#define ESC_GP_INPUT                      REG32((ESC) + 0x00000F18U)                 /*!< ESC General Purpose Inputs register */
#define ESC_USER_RAM                      REG32((ESC) + 0x00000F80U)                 /*!< ESC User Ram Byte 0 register */
#define ESC_PDRAM                         REG32((ESC) + 0x00001000U)                 /*!< ESC Process Data Ram register */

/* ESC_CTL */
#define ESC_CTL_EERF                      BIT(31)                                    /*!< EEPROM reload complete flag */
#define ESC_CTL_EERIE                     BIT(30)                                    /*!< EEPROM reload complete interrupt enable */
#define ESC_CTL_WDLF                      BIT(29)                                    /*!< Write data lost flag */
#define ESC_CTL_WDLIE                     BIT(28)                                    /*!< Write data lost interrupt enable */
#define ESC_CTL_TOF                       BIT(27)                                    /*!< Time out flag */
#define ESC_CTL_TOIE                      BIT(26)                                    /*!< Time out interrupt enable */
#define ESC_CTL_WEF                       BIT(25)                                    /*!< Write error flag */
#define ESC_CTL_WEIE                      BIT(24)                                    /*!< Write error interrupt enable */
#define ESC_CTL_IVF                       BIT(23)                                    /*!< CCTL_SIZE & CCTL_ADDR illegal value flag */
#define ESC_CTL_IVIE                      BIT(22)                                    /*!< CCTL_SIZE & CCTL_ADDR illegal value interrupt enable */
#define ESC_CTL_I2CF                      BIT(21)                                    /*!< Internal I2C communication error flag */
#define ESC_CTL_I2CIE                     BIT(20)                                    /*!< Internal I2C overrun interrupt enable */
#define ESC_CTL_BRP                       BIT(10)                                    /*!< When busy bit is high, prevent register change */
#define ESC_CTL_TO_CNT                    BITS(1,9)                                  /*!< Timeout counter */
#define ESC_CTL_TOEN                      BIT(0)                                     /*!< Timeout enable */

#define ESC_CTL_REG_OFFSET                0x3330U                                    /*!< CTL register offset */

/* ESC_SYNC0 */
#define ESC_SYNC0_SYNC0INT                BIT(0)                                     /*!< SYNC0 interrupt signal, write to clear */

#define ESC_SYNC0_REG_OFFSET              0x3334U                                    /*!< SYNC0 register offset */

/* ESC_SYNC1 */
#define ESC_SYNC1_SYNC1INT                BIT(0)                                     /*!< SYNC1 interrupt signal, write to clear */

#define ESC_SYNC1_REG_OFFSET              0x3338U                                    /*!< SYNC1 register offset */

/* Timeout counter */
#define ESC_TO_CNT(regval)                (BITS(1,9) & (((uint32_t)(regval)) << 1U))   /*!< Timeout counter */

/* Define the ESC on chip bus bit position and its register index offset */
#define ESC_REGIDX_BIT(regidx, bitpos)    (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos))
#define ESC_REG_VAL(periph)               (REG32(ESC + ((uint32_t)(periph) >> 6U)))
#define ESC_BIT_POS(val)                  ((uint32_t)(val) & 0x1FU)


#define ESC_MII_MNG_CTL_OFFSET             0x0510U                                  /*!< ESC MII Management Control register offset */
#define ESC_MII_MNG_STAT_OFFSET            0x0511U                                  /*!< ESC MII Management Status register offset */
#define ESC_PHY_ADDR_OFFSET                0x0512U                                  /*!< ESC PHY Address register offset */
#define ESC_PHY_REG_ADDR_OFFSET            0x0513U                                  /*!< ESC PHY Register Address register offset */
#define ESC_PHY_DATA_OFFSET                0x0514U                                  /*!< ESC PHY Data register offset */
#define MIIM_PDI_ACC_STAT_OFFSET           0x0517U                                  /*!< MII Management PDI Access State register offset */
#define READ_PHY_CMD                       0x1U                                     /*!< read phy command */
#define WRITE_PHY_CMD                      0x2U                                     /*!< write phy command */
#define WRITE_PHY_ENABLE                   0x1U                                     /*!< write phy enable */

#define PDI_ACCESS_MII_MANAGEMENT_ENABLE   0x1U                                     /*!< PDI has access to MII management */

/* Register address offsets for PDI access */
#define ESC_RST_PDI_OFFSET                 0x0041U                                  /*!< ESC Reset PDI register offset */
#define PDI_RESET_R                        0x52U                                    /*!< reset command R */
#define PDI_RESET_E                        0x45U                                    /*!< reset command E */
#define PDI_RESET_S                        0x53U                                    /*!< reset command S */

/* ESC on chip bus interrupt enable or disable*/
typedef enum {
    ESC_I2CIE             = ESC_REGIDX_BIT(ESC_CTL_REG_OFFSET, 20U),                /*!< Internal I2C overrun interrupt */
    ESC_IVIE              = ESC_REGIDX_BIT(ESC_CTL_REG_OFFSET, 22U),                /*!< CCTL size & addr illegal value interrupt */
    ESC_WEIE              = ESC_REGIDX_BIT(ESC_CTL_REG_OFFSET, 24U),                /*!< write error interrupt */
    ESC_TOIE              = ESC_REGIDX_BIT(ESC_CTL_REG_OFFSET, 26U),                /*!< time out interrupt */
    ESC_WDLIE             = ESC_REGIDX_BIT(ESC_CTL_REG_OFFSET, 28U),                /*!< write data lost interrupt */
    ESC_EERIE             = ESC_REGIDX_BIT(ESC_CTL_REG_OFFSET, 30U),                /*!< EEPROM reload complete interrupt */
} esc_on_chip_bus_interrupt_enum;

/* ESC on chip bus flags */
typedef enum {
    ESC_FLAG_I2CF          = ESC_REGIDX_BIT(ESC_CTL_REG_OFFSET, 21U),                /*!< Internal I2C communication error flag */
    ESC_FLAG_IVF           = ESC_REGIDX_BIT(ESC_CTL_REG_OFFSET, 23U),                /*!< CCTL size & addr illegal value flag */
    ESC_FLAG_WEF           = ESC_REGIDX_BIT(ESC_CTL_REG_OFFSET, 25U),                /*!< write error flag */
    ESC_FLAG_TOF           = ESC_REGIDX_BIT(ESC_CTL_REG_OFFSET, 27U),                /*!< time out flag */
    ESC_FLAG_WDLF          = ESC_REGIDX_BIT(ESC_CTL_REG_OFFSET, 29U),                /*!< write data lost flag */
    ESC_FLAG_EERF          = ESC_REGIDX_BIT(ESC_CTL_REG_OFFSET, 31U),                /*!< EEPROM reload complete flag */
} esc_on_chip_bus_flag_enum;

/* esc pdi direct read esc core register */
void pdi_direct_read_reg(uint8_t readbuffer[], uint16_t addr, uint16_t count);
/* esc pdi direct write esc core register */
void pdi_direct_write_reg(uint8_t writebuffer[], uint16_t addr, uint16_t count);
/* esc pdi direct read esc pdram */
void pdi_direct_read_pdram(uint8_t readbuffer[], uint16_t addr, uint16_t count);
/* esc pdi direct write esc pdram */
void pdi_direct_write_pdram(uint8_t writebuffer[], uint16_t addr, uint16_t count);
/* esc pdi reset */
void pdi_reset(void);
/* esc pdi read phy register */
uint16_t pdi_phy_read(uint8_t phy_addr, uint8_t phy_reg_addr);
/* esc pdi write phy register */
void pdi_phy_write(uint8_t phy_addr, uint8_t phy_reg_addr, uint16_t phy_data);
/* esc brp enable */
void esc_brp_enable(void);
/* esc brp disable */
void esc_brp_disable(void);
/* esc time out enable */
void esc_timeout_enable(void);
/* esc time out disable */
void esc_timeout_disable(void);
/* esc time out counter */
void esc_timeout_cnt(uint32_t cnt);
/* esc enable the on_chip_bus interrupt */
void esc_interrupt_enable(esc_on_chip_bus_interrupt_enum interrupt);
/* esc disable the on_chip_bus interrupt */
void esc_interrupt_disable(esc_on_chip_bus_interrupt_enum interrupt);
/* esc get esc on_chip_bus interrupt flags */
FlagStatus esc_interrupt_flag_get(esc_on_chip_bus_flag_enum int_flag);
/* esc clear esc on_chip_bus interrupt flags */
void esc_interrupt_flag_clear(esc_on_chip_bus_flag_enum int_flag);
/* esc clear sync0 interrupt */
void esc_sync0_interrupt_clear(void);
/* esc clear sync1 interrupt */
void esc_sync1_interrupt_clear(void);

#endif /* GD32H77X_78X_ESC_H */
