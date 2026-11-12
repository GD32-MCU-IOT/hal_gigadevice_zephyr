/*!
    \file    gd32h77x_78x_edim_hdsl.h
    \brief   definitions for the EDIM HDSL

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

#ifndef GD32H77X_78X_EDIM_HDSL_H
#define GD32H77X_78X_EDIM_HDSL_H

#include "gd32h77x_78x.h"

/* peripheral definitions */
/* peripheral base addresses */
#define EDIM_HDSL                              (EDIM_BASE + 0x00001400U)                               /*!< EDIM_HDSL base address */

/* registers definitions */
/* HDSL drive interface registers */
#define EDIM_HDSL_SYS_CTRL                REG8((EDIM_HDSL) + 0x00000000U)                              /*!< system control register */
#define EDIM_HDSL_SYNC_CTRL               REG8((EDIM_HDSL) + 0x00000001U)                              /*!< synchronization control register */
#define EDIM_HDSL_MASTER_QM               REG8((EDIM_HDSL) + 0x00000003U)                              /*!< quality monitoring register */
#define EDIM_HDSL_EVENT_H                 REG8((EDIM_HDSL) + 0x00000004U)                              /*!< high byte event register */
#define EDIM_HDSL_EVENT_L                 REG8((EDIM_HDSL) + 0x00000005U)                              /*!< low byte event register*/
#define EDIM_HDSL_MASK_H                  REG8((EDIM_HDSL) + 0x00000006U)                              /*!< high byte event mask register */
#define EDIM_HDSL_MASK_L                  REG8((EDIM_HDSL) + 0x00000007U)                              /*!< low byte event mask register */
#define EDIM_HDSL_MASK_SUM                REG8((EDIM_HDSL) + 0x00000008U)                              /*!< summary mask register */
#define EDIM_HDSL_EDGES                   REG8((EDIM_HDSL) + 0x00000009U)                              /*!< edge register */
#define EDIM_HDSL_DELAY                   REG8((EDIM_HDSL) + 0x0000000AU)                              /*!< run time delay register */
#define EDIM_HDSL_VERSION                 REG8((EDIM_HDSL) + 0x0000000BU)                              /*!< version register */
#define EDIM_HDSL_ENC_ID2                 REG8((EDIM_HDSL) + 0x0000000DU)                              /*!< encoder ID 2 register */
#define EDIM_HDSL_ENC_ID1                 REG8((EDIM_HDSL) + 0x0000000EU)                              /*!< encoder ID 1 register */
#define EDIM_HDSL_ENC_ID0                 REG8((EDIM_HDSL) + 0x0000000FU)                              /*!< encoder ID 0 register */
#define EDIM_HDSL_POS4                    REG8((EDIM_HDSL) + 0x00000010U)                              /*!< fast position byte 4 register */
#define EDIM_HDSL_POS3                    REG8((EDIM_HDSL) + 0x00000011U)                              /*!< fast position byte 3 register */
#define EDIM_HDSL_POS2                    REG8((EDIM_HDSL) + 0x00000012U)                              /*!< fast position byte 2 register */
#define EDIM_HDSL_POS1                    REG8((EDIM_HDSL) + 0x00000013U)                              /*!< fast position byte 1 register */
#define EDIM_HDSL_POS0                    REG8((EDIM_HDSL) + 0x00000014U)                              /*!< fast position byte 0 register */
#define EDIM_HDSL_VEL2                    REG8((EDIM_HDSL) + 0x00000015U)                              /*!< speed byte 2 register */
#define EDIM_HDSL_VEL1                    REG8((EDIM_HDSL) + 0x00000016U)                              /*!< speed byte 1 register */
#define EDIM_HDSL_VEL0                    REG8((EDIM_HDSL) + 0x00000017U)                              /*!< speed byte 0 register */
#define EDIM_HDSL_MIR_SUM                 REG8((EDIM_HDSL) + 0x00000018U)                              /*!< mirror status summary register */
#define EDIM_HDSL_PC_BUFFER0              REG8((EDIM_HDSL) + 0x00000020U)                              /*!< parameter channel buffer 0 register */
#define EDIM_HDSL_PC_BUFFER1              REG8((EDIM_HDSL) + 0x00000021U)                              /*!< parameter channel buffer 1 register */
#define EDIM_HDSL_PC_BUFFER2              REG8((EDIM_HDSL) + 0x00000022U)                              /*!< parameter channel buffer 2 register */
#define EDIM_HDSL_PC_BUFFER3              REG8((EDIM_HDSL) + 0x00000023U)                              /*!< parameter channel buffer 3 register */
#define EDIM_HDSL_PC_BUFFER4              REG8((EDIM_HDSL) + 0x00000024U)                              /*!< parameter channel buffer 4 register */
#define EDIM_HDSL_PC_BUFFER5              REG8((EDIM_HDSL) + 0x00000025U)                              /*!< parameter channel buffer 5 register */
#define EDIM_HDSL_PC_BUFFER6              REG8((EDIM_HDSL) + 0x00000026U)                              /*!< parameter channel buffer 6 register */
#define EDIM_HDSL_PC_BUFFER7              REG8((EDIM_HDSL) + 0x00000027U)                              /*!< parameter channel buffer 7 register */
#define EDIM_HDSL_PC_ADD_H                REG8((EDIM_HDSL) + 0x00000028U)                              /*!< high byte long message address register */
#define EDIM_HDSL_PC_ADD_L                REG8((EDIM_HDSL) + 0x00000029U)                              /*!< low byte long message address register */
#define EDIM_HDSL_PC_OFF_H                REG8((EDIM_HDSL) + 0x0000002AU)                              /*!< high byte long message address offset register */
#define EDIM_HDSL_PC_OFF_L                REG8((EDIM_HDSL) + 0x0000002BU)                              /*!< low byte long message address offset register */
#define EDIM_HDSL_PC_CTRL                 REG8((EDIM_HDSL) + 0x0000002CU)                              /*!< parameter channel control register */
#define EDIM_HDSL_PIPE_S                  REG8((EDIM_HDSL) + 0x0000002DU)                              /*!< the sensorhub channel status register */
#define EDIM_HDSL_PIPE_D                  REG8((EDIM_HDSL) + 0x0000002EU)                              /*!< sensorhub FIFO register */
#define EDIM_HDSL_PC_DATA                 REG8((EDIM_HDSL) + 0x0000002FU)                              /*!< parameter channel short message mirror register */
#define EDIM_HDSL_ACC_ERR_CNT             REG8((EDIM_HDSL) + 0x00000038U)                              /*!< fast position error counter register */
#define EDIM_HDSL_MAXACC                  REG8((EDIM_HDSL) + 0x00000039U)                              /*!< fast position acceleration boundary register */
#define EDIM_HDSL_MAXDEV_H                REG8((EDIM_HDSL) + 0x0000003AU)                              /*!< fast position estimator deviation high byte register */
#define EDIM_HDSL_MAXDEV_L                REG8((EDIM_HDSL) + 0x0000003BU)                              /*!< fast position estimator deviation low byte register */
#define EDIM_HDSL_DUMMY                   REG8((EDIM_HDSL) + 0x0000003FU)                              /*!< dummy register */
#define EDIM_HDSL_MIR_ST(n)               REG8((EDIM_HDSL) + 0x00000060U + (0x1U * (n)))               /*!< mirror status n register (n = 0 to 7) */
 
/* HDSL safe channel 1 interface registers */ 
#define EDIM_HDSL_SAFE_EDGES              REG8((EDIM_HDSL) + (0x200U) + 0x00000009U)                    /*!< edge register */
#define EDIM_HDSL_SAFE_DELAY              REG8((EDIM_HDSL) + (0x200U) + 0x0000000AU)                    /*!< run time delay register */
#define EDIM_HDSL_SAFE_VERSION            REG8((EDIM_HDSL) + (0x200U) + 0x0000000BU)                    /*!< version register */
#define EDIM_HDSL_SAFE_ENC_ID2            REG8((EDIM_HDSL) + (0x200U) + 0x0000000DU)                    /*!< encoder ID 2 register */
#define EDIM_HDSL_SAFE_ENC_ID1            REG8((EDIM_HDSL) + (0x200U) + 0x0000000EU)                    /*!< encoder ID 1 register */
#define EDIM_HDSL_SAFE_ENC_ID0            REG8((EDIM_HDSL) + (0x200U) + 0x0000000FU)                    /*!< encoder ID 0 register */
#define EDIM_HDSL_VPOS4                   REG8((EDIM_HDSL) + (0x200U) + 0x00000019U)                    /*!< safe position 4 register */
#define EDIM_HDSL_VPOS3                   REG8((EDIM_HDSL) + (0x200U) + 0x0000001AU)                    /*!< safe position 3 register */
#define EDIM_HDSL_VPOS2                   REG8((EDIM_HDSL) + (0x200U) + 0x0000001BU)                    /*!< safe position 2 register */
#define EDIM_HDSL_VPOS1                   REG8((EDIM_HDSL) + (0x200U) + 0x0000001CU)                    /*!< safe position 1 register */
#define EDIM_HDSL_VPOS0                   REG8((EDIM_HDSL) + (0x200U) + 0x0000001DU)                    /*!< safe position 0 register */
#define EDIM_HDSL_VPOSCRC_H               REG8((EDIM_HDSL) + (0x200U) + 0x0000001EU)                    /*!< safe position CRC high byte register */
#define EDIM_HDSL_VPOSCRC_L               REG8((EDIM_HDSL) + (0x200U) + 0x0000001FU)                    /*!< safe position CRC low byte register */
#define EDIM_HDSL_SAFE_CTRL               REG8((EDIM_HDSL) + (0x200U) + 0x00000035U)                    /*!< safe system control register */
#define EDIM_HDSL_SAFE_SUM                REG8((EDIM_HDSL) + (0x200U) + 0x00000036U)                    /*!< safe status summary register */
#define EDIM_HDSL_S_PC_DATA               REG8((EDIM_HDSL) + (0x200U) + 0x00000037U)                    /*!< parameter channel short message register */
#define EDIM_HDSL_EVENT_S                 REG8((EDIM_HDSL) + (0x200U) + 0x0000003DU)                    /*!< safe event register */
#define EDIM_HDSL_MASK_S                  REG8((EDIM_HDSL) + (0x200U) + 0x0000003EU)                    /*!< safe event mask register */
#define EDIM_HDSL_ENC_ST(n)               REG8((EDIM_HDSL) + (0x200U) + 0x00000040U + (0x1U * (n)))     /*!< encoder status n register (n = 0 to 7) */
#define EDIM_HDSL_SRSSI                   REG8((EDIM_HDSL) + (0x200U) + 0x0000007CU)                    /*!< slave RSSI register */
#define EDIM_HDSL_MAIL                    REG8((EDIM_HDSL) + (0x200U) + 0x0000007EU)                    /*!< slave Mail register */
#define EDIM_HDSL_PING                    REG8((EDIM_HDSL) + (0x200U) + 0x0000007FU)                    /*!< slave Ping register */

/* HDSL safe channel 2 interface registers */
#define EDIM_HDSL_VERSION2                REG8((EDIM_HDSL) + (0x300U) + 0x0000000BU)                   /*!< version in safe channel 2 register */
#define EDIM_HDSL_ENC2_ID                 REG8((EDIM_HDSL) + (0x300U) + 0x0000000FU)                   /*!< encoder ID in safe channel 2 register */
#define EDIM_HDSL_STATUS2                 REG8((EDIM_HDSL) + (0x300U) + 0x00000018U)                   /*!< safe channel 2 status register */
#define EDIM_HDSL_VPOS24                  REG8((EDIM_HDSL) + (0x300U) + 0x00000019U)                   /*!< safe position channel 2 byte 4 register */
#define EDIM_HDSL_VPOS23                  REG8((EDIM_HDSL) + (0x300U) + 0x0000001AU)                   /*!< safe position channel 2 byte 3 register */
#define EDIM_HDSL_VPOS22                  REG8((EDIM_HDSL) + (0x300U) + 0x0000001BU)                   /*!< safe position channel 2 byte 2 register */
#define EDIM_HDSL_VPOS21                  REG8((EDIM_HDSL) + (0x300U) + 0x0000001CU)                   /*!< safe position channel 2 byte 1 register */
#define EDIM_HDSL_VPOS20                  REG8((EDIM_HDSL) + (0x300U) + 0x0000001DU)                   /*!< safe position channel 2 byte 0 register */
#define EDIM_HDSL_VPOSCRC2_H              REG8((EDIM_HDSL) + (0x300U) + 0x0000001EU)                   /*!< high byte position checksum channel 2 register */
#define EDIM_HDSL_VPOSCRC2_L              REG8((EDIM_HDSL) + (0x300U) + 0x0000001FU)                   /*!< low byte position checksum channel 2 register */
#define EDIM_HDSL_DUMMY2                  REG8((EDIM_HDSL) + (0x300U) + 0x0000003FU)                   /*!< dummy in safe channel 2 register */

/* HDSL general registers */
#define EDIM_HDSL_CTL                     REG32((EDIM_HDSL) + (0x380U) + 0x00000000U)                  /*!< hiperface DSL control register0 */
#define EDIM_HDSL_ONLINE_STATUS_D         REG32((EDIM_HDSL) + (0x380U) + 0x00000004U)                  /*!< online status D */
#define EDIM_HDSL_ONLINE_STATUS_1         REG32((EDIM_HDSL) + (0x380U) + 0x00000008U)                  /*!< online status 1 */
#define EDIM_HDSL_ONLINE_STATUS_2         REG32((EDIM_HDSL) + (0x380U) + 0x0000000CU)                  /*!< online status 2 */
#define EDIM_HDSL_SYNLK                   REG32((EDIM_HDSL) + (0x380U) + 0x00000010U)                  /*!< sync lock status */
#define EDIM_HDSL_INTEN                   REG32((EDIM_HDSL) + (0x380U) + 0x00000014U)                  /*!< interrupt configure  */


/* bits definitions */
/* EDIM_HDSL_SYS_CTRL */
#define EDIM_HDSL_SYS_CTRL_OEN            BIT(0)                               /*!< activation of the output */
#define EDIM_HDSL_SYS_CTRL_SPOL           BIT(1)                               /*!< polarity of the synchronization pulse */
#define EDIM_HDSL_SYS_CTRL_LOOP           BIT(4)                               /*!< test drive interface */
#define EDIM_HDSL_SYS_CTRL_FRST           BIT(5)                               /*!< pipeline FIFO, reset */
#define EDIM_HDSL_SYS_CTRL_MRST           BIT(6)                               /*!< messages reset */
#define EDIM_HDSL_SYS_CTRL_PRST           BIT(7)                               /*!< protocol reset */

/* EDIM_HDSL_SYNC_CTRL */
#define EDIM_HDSL_SYNC_CTRL_ES            BITS(0,7)                            /*!< external synchronization */

/* EDIM_HDSL_MASTER_QM */
#define EDIM_HDSL_MASTER_QM_QM            BITS(0,3)                            /*!< quality monitoring bits */
#define EDIM_HDSL_MASTER_QM_LINK          BIT(7)                               /*!< DSL protocol connection status */

/* EDIM_HDSL_EVENT_H */
#define EDIM_HDSL_EVENT_H_PRST            BIT(0)                               /*!< protocol reset warning */
#define EDIM_HDSL_EVENT_H_DTE             BIT(1)                               /*!< estimator deviation threshold error */
#define EDIM_HDSL_EVENT_H_POS             BIT(3)                               /*!< estimator turned on */
#define EDIM_HDSL_EVENT_H_SUM             BIT(6)                               /*!< remote event monitoring */
#define EDIM_HDSL_EVENT_H_INT             BIT(7)                               /*!< interrupt status */

/* EDIM_HDSL_EVENT_L */
#define EDIM_HDSL_EVENT_L_FREL            BIT(1)                               /*!< channel free for "long message" */
#define EDIM_HDSL_EVENT_L_QMLW            BIT(2)                               /*!< quality monitoring low-value warning */
#define EDIM_HDSL_EVENT_L_ANS             BIT(4)                               /*!< erroneous answer to "long message" */
#define EDIM_HDSL_EVENT_L_MIN             BIT(5)                               /*!< message initialization */

/* EDIM_HDSL_MASK_H */
#define EDIM_HDSL_MASK_H_MPRST            BIT(0)                               /*!< mask for protocol reset warning */
#define EDIM_HDSL_MASK_H_MDTE             BIT(1)                               /*!< mask for estimator deviation threshold error warning */
#define EDIM_HDSL_MASK_H_MPOS             BIT(3)                               /*!< mask for fast position error */
#define EDIM_HDSL_MASK_H_MSUM             BIT(6)                               /*!< mask for remote event monitoring */
 
/* EDIM_HDSL_MASK_L */ 
#define EDIM_HDSL_MASK_L_MFREL            BIT(1)                               /*!< mask for "channel free for "long message"" */
#define EDIM_HDSL_MASK_L_MQMLW            BIT(2)                               /*!< mask for low-quality monitoring value warning */
#define EDIM_HDSL_MASK_L_MANS             BIT(4)                               /*!< mask for erroneous answer to "long message" */
#define EDIM_HDSL_MASK_L_MMIN             BIT(5)                               /*!< mask for message initialization confirmation */

/* EDIM_HDSL_MASK_SUM */
#define EDIM_HDSL_MASK_SUM_MSUM           BITS(0,7)                            /*!< mask for status summary bits */
#define EDIM_HDSL_MASK_SUM_0              BIT(0)                               /*!< mask for status summary bit 0 */
#define EDIM_HDSL_MASK_SUM_1              BIT(1)                               /*!< mask for status summary bit 1 */
#define EDIM_HDSL_MASK_SUM_2              BIT(2)                               /*!< mask for status summary bit 2 */
#define EDIM_HDSL_MASK_SUM_3              BIT(3)                               /*!< mask for status summary bit 3 */
#define EDIM_HDSL_MASK_SUM_4              BIT(4)                               /*!< mask for status summary bit 4 */
#define EDIM_HDSL_MASK_SUM_5              BIT(5)                               /*!< mask for status summary bit 5 */
#define EDIM_HDSL_MASK_SUM_6              BIT(6)                               /*!< mask for status summary bit 6 */
#define EDIM_HDSL_MASK_SUM_7              BIT(7)                               /*!< mask for status summary bit 7 */

/* EDIM_HDSL_EDGES */
#define EDIM_HDSL_EDGES_EDGES             BITS(0,7)                            /*!< identification of edges in the cable signal */

/* EDIM_HDSL_DELAY */
#define EDIM_HDSL_DELAY_CBLDLY            BITS(0,3)                            /*!< 4-bit value for cable delay */
#define EDIM_HDSL_DELAY_RSSI              BITS(4,7)                            /*!< indication of the received signal strength */

/* EDIM_HDSL_VERSION */
#define EDIM_HDSL_VERSION_MINOR           BITS(0,3)                            /*!< minor release number */
#define EDIM_HDSL_VERSION_MAJOR           BITS(4,5)                            /*!< major release number */
#define EDIM_HDSL_VERSION_CODE            BITS(6,7)                            /*!< type of module */

/* EDIM_HDSL_ENC_ID2 */
#define EDIM_HDSL_ENC_ID2_ENCID           BITS(0,3)                            /*!< encoder designation code bit 19 to bit 16 */
#define EDIM_HDSL_ENC_ID2_SCI             BITS(4,6)                            /*!< indication of special characters */

/* EDIM_HDSL_ENC_ID0/1 */
#define EDIM_HDSL_ENC_ID01_ENCID          BITS(0,7)                            /*!< encoder designation code, byte n */

/* EDIM_HDSL_POSn */
#define EDIM_HDSL_POS_POS                 BITS(0,7)                            /*!< fast position, byte n */

/* EDIM_HDSL_VELn */ 
#define EDIM_HDSL_VEL_VEL                 BITS(0,7)                            /*!< speed, byte n */

/* EDIM_HDSL_MIR_SUM */
#define EDIM_HDSL_MIR_SUM_SUM             BITS(0,7)                            /*!< status summary bits */

/* EDIM_HDSL_PC_BUFFERn */
#define EDIM_HDSL_PC_BUFFER_PCBUF         BITS(0,7)                            /*!< parameter channel, byte n */

/* EDIM_HDSL_PC_ADD_H */
#define EDIM_HDSL_PC_ADD_H_LADDH          BITS(0,1)                            /*!< long message address, bit 9 to bit 8 */
#define EDIM_HDSL_PC_ADD_H_LLEN           BITS(2,3)                            /*!< data length of the "long message" */
#define EDIM_HDSL_PC_ADD_H_LIND           BIT(4)                               /*!< indirect addressing of long messages */
#define EDIM_HDSL_PC_ADD_H_LOFF           BIT(5)                               /*!< long message addressing mode/long message error */
#define EDIM_HDSL_PC_ADD_H_LRW            BIT(6)                               /*!< long message, read/write mode */

/* EDIM_HDSL_PC_ADD_L */
#define EDIM_HDSL_PC_ADD_L_LADDL          BITS(0,7)                            /*!< long message address, bit 7 to bit 0 */

/* EDIM_HDSL_PC_OFF_H */
#define EDIM_HDSL_PC_OFF_H_LOFFADDH       BITS(0,6)                            /*!< long message offset value, bit 14 to bit 8 */
#define EDIM_HDSL_PC_OFF_H_LID            BIT(7)                               /*!< long message identification */

/* EDIM_HDSL_PC_OFF_L */
#define EDIM_HDSL_PC_OFF_L_LOFFADDL       BITS(0,7)                            /*!< long message offset value, bit 7 to bit 0 */

/* EDIM_HDSL_PC_CTRL */
#define EDIM_HDSL_PC_CTRL_LSTA            BIT(0)                               /*!< control of the long message start */

/* EDIM_HDSL_PIPE_S */
#define EDIM_HDSL_PIPE_S_PSCI             BIT(0)                               /*!< indication for special characters in the SensorHub Channel */
#define EDIM_HDSL_PIPE_S_PERR             BIT(1)                               /*!< coding error of the bits in the SensorHub Channel */
#define EDIM_HDSL_PIPE_S_PEMP             BIT(2)                               /*!< the SensorHub channel buffer is empty */
#define EDIM_HDSL_PIPE_S_POVR             BIT(3)                               /*!< SensorHub Channel overflow */

/* EDIM_HDSL_PIPE_D */
#define EDIM_HDSL_PIPE_D_SCDATA           BITS(0,7)                            /*!< SensorHub Channel data */

/* EDIM_HDSL_PC_DATA */
#define EDIM_HDSL_PC_DATA_PCDATA          BITS(0,7)                            /*!< "short message" Mirror register data */

/* EDIM_HDSL_ACC_ERR_CNT */
#define EDIM_HDSL_ACC_ERR_CNT_CNT         BITS(0,4)                            /*!< position error count/threshold */

/* EDIM_HDSL_MAXACC */
#define EDIM_HDSL_MAXACC_MNT              BITS(0,5)                            /*!< mantissa of fast position acceleration boundary */
#define EDIM_HDSL_MAXACC_RES              BITS(6,7)                            /*!< mantissa of fast position acceleration boundary */

/* EDIM_HDSL_MAXDEV */
#define EDIM_HDSL_MAXDEV_H_DEVH           BITS(0,7)                            /*!< fast position estimator deviation high byte */
#define EDIM_HDSL_MAXDEV_L_DEVL           BITS(0,7)                            /*!< fast position estimator deviation low byte */

/* EDIM_HDSL_DUMMY */
#define EDIM_HDSL_DUMMY_DUMMY             BITS(0,7)                            /*!< DUMMY */

/* EDIM_HDSL_MIR_STn */
#define EDIM_HDSL_MIR_ST_MIRST            BITS(0,7)                            /*!< mirror status, byte n */
#define EDIM_HDSL_MIR_ST_BIT(n)           BIT(n)                               /*!< mirror status, bit n */

/* EDIM_HDSL_VPOSn */
#define EDIM_HDSL_VPOS_VPOS               BITS(0,7)                            /*!< safe position, byte n */

/* EDIM_HDSL_VPOSCRC_H */
#define EDIM_HDSL_VPOSCRC_H_VPOSCRCH      BITS(0,7)                            /*!< CRC of the safe position, bit 15 to bit 8 */

/* EDIM_HDSL_VPOSCRC_L */
#define EDIM_HDSL_VPOSCRC_L_VPOSCRCL      BITS(0,7)                            /*!< CRC of the safe position, bit 7 to bit 0 */

/* EDIM_HDSL_SAFE_CTRL */
#define EDIM_HDSL_SAFE_CTRL_MRST          BIT(6)                               /*!< message reset */
#define EDIM_HDSL_SAFE_CTRL_PRST          BIT(7)                               /*!< protocol reset */

/* EDIM_HDSL_SAFE_SUM */
#define EDIM_HDSL_SAFE_SUM_SSUM           BITS(0,7)                            /*!< status summary bit */

/* EDIM_HDSL_S_PC_DATA */
#define EDIM_HDSL_S_PC_DATA_SPCDATA       BITS(0,7)                            /*!< "short message" parameter channel data */

/* EDIM_HDSL_EVENT_S */
#define EDIM_HDSL_EVENT_S_FRES            BIT(0)                               /*!< channel free for "short message" */
#define EDIM_HDSL_EVENT_S_MIN             BIT(1)                               /*!< message init */
#define EDIM_HDSL_EVENT_S_PRST            BIT(2)                               /*!< protocol reset warning */
#define EDIM_HDSL_EVENT_S_QMLW            BIT(3)                               /*!< quality monitoring low-value warning */
#define EDIM_HDSL_EVENT_S_VPOS            BIT(4)                               /*!< safe position error */
#define EDIM_HDSL_EVENT_S_SCE             BIT(5)                               /*!< error on the safe channel */
#define EDIM_HDSL_EVENT_S_SSUM            BIT(6)                               /*!< remote event monitoring */
#define EDIM_HDSL_EVENT_S_SINT            BIT(7)                               /*!< safe interrupt status */

/* EDIM_HDSL_MASK_S */
#define EDIM_HDSL_MASK_S_MFRES            BIT(0)                               /*!< mask for channel free for "short message" */
#define EDIM_HDSL_MASK_S_MMIN             BIT(1)                               /*!< mask for message init */
#define EDIM_HDSL_MASK_S_MPRST            BIT(2)                               /*!< mask for protocol reset warning */
#define EDIM_HDSL_MASK_S_MQMLW            BIT(3)                               /*!< mask for quality monitoring low-value warning */
#define EDIM_HDSL_MASK_S_MVPOS            BIT(4)                               /*!< mask for safe position error */
#define EDIM_HDSL_MASK_S_MSCE             BIT(5)                               /*!< mask for error on the safe channel */
#define EDIM_HDSL_MASK_S_MSSUM            BIT(6)                               /*!< mask for remote event monitoring */

/* EDIM_HDSL_ENC_STn */
#define EDIM_HDSL_ENC_ST_ENCST            BITS(0,7)                            /*!< encoder status, byte n */
#define EDIM_HDSL_ENC_ST_BIT(n)           BIT(n)                               /*!< encoder status, bit n */

/* EDIM_HDSL_SRSSI */
#define EDIM_HDSL_SRSSI_SRSSI             BITS(0,2)                            /*!< value of the slave RSSI */

/* EDIM_HDSL_MAIL */
#define EDIM_HDSL_MAIL_MAIL               BITS(0,7)                            /*!< slave-Mail */

/* EDIM_HDSL_PING */
#define EDIM_HDSL_PING_PING               BITS(0,7)                            /*!< slave-Ping */

/* EDIM_HDSL_VERSION2 */
#define EDIM_HDSL_VERSION2_MINOR          BITS(0,3)                            /*!< minor release number */
#define EDIM_HDSL_VERSION2_MAJOR          BITS(4,5)                            /*!< major release number */
#define EDIM_HDSL_VERSION2_CODE           BITS(6,7)                            /*!< type of module */

/* EDIM_HDSL_ENC2_ID */
#define EDIM_HDSL_ENC2_ID_ENC2ID          BITS(0,7)                            /*!< designation of the safe channel 2 channel */

/* EDIM_HDSL_STATUS2 */
#define EDIM_HDSL_STATUS2_FIX2            BITS(0,4)                            /*!< safe channel 2 fixed bit pattern */
#define EDIM_HDSL_STATUS2_ERR2            BIT(5)                               /*!< safe channel 2 position error */
#define EDIM_HDSL_STATUS2_TEST2           BIT(6)                               /*!< safe channel 2 test */
#define EDIM_HDSL_STATUS2_TOG2            BIT(7)                               /*!< safe channel 2 toggle */

/* EDIM_HDSL_VPOS2n */
#define EDIM_HDSL_VPOS2_VPOS2            BITS(0,7)                            /*!< safe position, Channel 2, byte n */

/* EDIM_HDSL_VPOSCRC2_H */
#define EDIM_HDSL_VPOSCRC2_H_VPOSCRC2H    BITS(0,7)                            /*!< CRC of the safe position 2, bit 15 to bit 8 */

/* EDIM_HDSL_VPOSCRC2_L */
#define EDIM_HDSL_VPOSCRC2_L_VPOSCRC2L    BITS(0,7)                            /*!< CRC of the safe position 2, bit 7 to bit 0 */

/* EDIM_HDSL_DUMMY2 */
#define EDIM_HDSL_DUMMY2_DUMMY            BITS(0,7)                            /*!< DUMMY */

/* EDIM_HDSL_CTL */
#define EDIM_HDSL_CTL_ENDIAN              BIT(0)                               /*!< HIPERFACE DSL unit 0 endian Mode */
#define EDIM_HDSL_CTL_SSEL1               BIT(1)                               /*!< HIPERFACE DSL unit 0 safe channel 1 interface select */ 
#define EDIM_HDSL_CTL_DSEL                BIT(2)                               /*!< HIPERFACE DSL unit 0 driver interface select */
#define EDIM_HDSL_CTL_SSEL2               BIT(3)                               /*!< HIPERFACE DSL unit 0 safe channel 2 interface select */ 

/* EDIM_HDSL_ONLINE_STATUS_D */
#define EDIM_HDSL_ONLINE_STATUS_D_FREL         BIT(1)                               /*!< channel status for long message */
#define EDIM_HDSL_ONLINE_STATUS_D_QMLW         BIT(2)                               /*!< quality monitoring at low level */
#define EDIM_HDSL_ONLINE_STATUS_D_ANS          BIT(4)                               /*!< incorrect answer detected */
#define EDIM_HDSL_ONLINE_STATUS_D_MIN          BIT(5)                               /*!< acknowledgment of message Initialization */
#define EDIM_HDSL_ONLINE_STATUS_D_POSTX        BITS(6,7)                            /*!< position transmission status */
#define EDIM_HDSL_ONLINE_STATUS_D_PRST         BIT(8)                               /*!< protocol reset */
#define EDIM_HDSL_ONLINE_STATUS_D_DTE          BIT(9)                               /*!< deviation threshold error */
#define EDIM_HDSL_ONLINE_STATUS_D_POS          BIT(11)                              /*!< estimator turned on */
#define EDIM_HDSL_ONLINE_STATUS_D_SUM          BIT(14)                              /*!< summary byte */
#define EDIM_HDSL_ONLINE_STATUS_D_INT          BIT(15)                              /*!< status of the interrupt signal */

/* EDIM_HDSL_ONLINE_STATUS_1 */
#define EDIM_HDSL_ONLINE_STATUS_1_FRES         BIT(0)                               /*!< channel Status for the short message */
#define EDIM_HDSL_ONLINE_STATUS_1_QMLW         BIT(2)                               /*!< quality monitoring at low level */
#define EDIM_HDSL_ONLINE_STATUS_1_MIN          BIT(5)                               /*!< acknowledgment of message Initialization */
#define EDIM_HDSL_ONLINE_STATUS_1_POSTX        BITS(6,7)                            /*!< position transmission status */
#define EDIM_HDSL_ONLINE_STATUS_1_PRST         BIT(8)                               /*!< protocol reset */
#define EDIM_HDSL_ONLINE_STATUS_1_VPOS         BIT(10)                              /*!< safe Position Invalid */
#define EDIM_HDSL_ONLINE_STATUS_1_SCE          BIT(13)                              /*!< CRC Error on the Safe Channel */
#define EDIM_HDSL_ONLINE_STATUS_1_SSUM         BIT(14)                              /*!< Safe summary bit */
#define EDIM_HDSL_ONLINE_STATUS_1_SINT         BIT(15)                              /*!< status of the interrupt signal */

/* EDIM_HDSL_ONLINE_STATUS_2 */
#define EDIM_HDSL_ONLINE_STATUS_2_QMLW         BIT(2)                               /*!< quality monitoring at low level */
#define EDIM_HDSL_ONLINE_STATUS_2_POSTX        BITS(6,7)                            /*!< position transmission status */
#define EDIM_HDSL_ONLINE_STATUS_2_PRST         BIT(8)                               /*!< protocol reset */
#define EDIM_HDSL_ONLINE_STATUS_2_VPOS2        BIT(10)                              /*!< safe Position 2 Invalid */
#define EDIM_HDSL_ONLINE_STATUS_2_SCE2         BIT(13)                              /*!< transmission Error Channel 2 */
#define EDIM_HDSL_ONLINE_STATUS_2_SSUM2        BIT(14)                              /*!< summary byte Channel 2 */

/* EDIM_HDSL_SYNLK */
#define EDIM_HDSL_SYNLK_SYNLK                  BIT(0)                               /*!< position sampling resolution locked */

/* EDIM_HDSL_INTEN */
#define EDIM_HDSL_INTEN_INTSRC                 BITS(0,3)                            /*!< POSTX interrupt source */
#define EDIM_HDSL_INTEN_POSTXIE                BIT(8)                               /*!< POSTX interrupt enable */
#define EDIM_HDSL_INTEN_INTSIE                 BIT(9)                               /*!< Interrupt_s enable */

/* constants definitions */
/* Polarity of the synchronization pulse */
#define EDIM_HDSL_SYNC_TRAILING                ((uint8_t)0x00U)                     /*!< the SYNC trailing edge is used */
#define EDIM_HDSL_SYNC_LEADING                 EDIM_HDSL_SYS_CTRL_SPOL              /*!< the SYNC leading edge is used */
                                                                                    
/* EDIM_HDSL flag definitions */ 
#define EDIM_HDSL_FLAG_MASK                    ((uint32_t)0x00004B36U)
#define EDIM_HDSL_FLAG_PRST                    (EDIM_HDSL_EVENT_H_PRST << 8)        /*!< protocol reset warning */
#define EDIM_HDSL_FLAG_DTE                     (EDIM_HDSL_EVENT_H_DTE << 8)         /*!< estimator deviation threshold error */
#define EDIM_HDSL_FLAG_POS                     (EDIM_HDSL_EVENT_H_POS << 8)         /*!< estimator turned on */
#define EDIM_HDSL_FLAG_SUM                     (EDIM_HDSL_EVENT_H_SUM << 8)         /*!< remote event monitoring */
#define EDIM_HDSL_FLAG_INT                     (EDIM_HDSL_EVENT_H_INT << 8)         /*!< interrupt status */
#define EDIM_HDSL_FLAG_FREL                    EDIM_HDSL_EVENT_L_FREL               /*!< channel free for "long message" */
#define EDIM_HDSL_FLAG_QMLW                    EDIM_HDSL_EVENT_L_QMLW               /*!< quality monitoring low-value warning */
#define EDIM_HDSL_FLAG_ANS                     EDIM_HDSL_EVENT_L_ANS                /*!< erroneous answer to "long message" */
#define EDIM_HDSL_FLAG_MIN                     EDIM_HDSL_EVENT_L_MIN                /*!< message initialization */
                                                                                    
/* EDIM_HDSL interrupt enable definitions */
#define EDIM_HDSL_INTEN_MASK                   ((uint32_t)0x00004B36U)
#define EDIM_HDSL_INT_PRST                     (EDIM_HDSL_MASK_H_MPRST << 8)        /*!< Protocol reset warning */
#define EDIM_HDSL_INT_DTE                      (EDIM_HDSL_MASK_H_MDTE << 8)         /*!< Estimator deviation threshold error */
#define EDIM_HDSL_INT_POS                      (EDIM_HDSL_MASK_H_MPOS << 8)         /*!< Estimator turned on */
#define EDIM_HDSL_INT_SUM                      (EDIM_HDSL_MASK_H_MSUM << 8)         /*!< Remote event monitoring */
#define EDIM_HDSL_INT_FREL                     EDIM_HDSL_MASK_L_MFREL               /*!< Channel free for "long message" */
#define EDIM_HDSL_INT_QMLW                     EDIM_HDSL_MASK_L_MQMLW               /*!< Quality monitoring low-value warning */
#define EDIM_HDSL_INT_ANS                      EDIM_HDSL_MASK_L_MANS                /*!< Erroneous answer to "long message" */
#define EDIM_HDSL_INT_MIN                      EDIM_HDSL_MASK_L_MMIN                /*!< Message initialization */

/* EDIM_HDSL interrupt flag definitions */ 
#define EDIM_HDSL_INT_FLAG_MASK                ((uint32_t)0x00004B36U)
#define EDIM_HDSL_INT_FLAG_PRST                (EDIM_HDSL_EVENT_H_PRST << 8)        /*!< Protocol reset warning */
#define EDIM_HDSL_INT_FLAG_DTE                 (EDIM_HDSL_EVENT_H_DTE << 8)         /*!< Estimator deviation threshold error */
#define EDIM_HDSL_INT_FLAG_POS                 (EDIM_HDSL_EVENT_H_POS << 8)         /*!< Estimator turned on */
#define EDIM_HDSL_INT_FLAG_SUM                 (EDIM_HDSL_EVENT_H_SUM << 8)         /*!< Remote event monitoring */
#define EDIM_HDSL_INT_FLAG_FREL                EDIM_HDSL_EVENT_L_FREL               /*!< Channel free for "long message" */
#define EDIM_HDSL_INT_FLAG_QMLW                EDIM_HDSL_EVENT_L_QMLW               /*!< Quality monitoring low-value warning */
#define EDIM_HDSL_INT_FLAG_ANS                 EDIM_HDSL_EVENT_L_ANS                /*!< Erroneous answer to "long message" */
#define EDIM_HDSL_INT_FLAG_MIN                 EDIM_HDSL_EVENT_L_MIN                /*!< Message initialization */
                                                      
/* PC_ADD_H register bit define */
/* EDIM_HDSL data length of the "long message" */
#define ADD_H_LLEN(regval)                    (BITS(2,3) & ((uint32_t)(regval) << 2U))
#define EDIM_HDSL_LONG_MSG_LEN_0              ADD_H_LLEN(0)                         /*!< No data bytes */
#define EDIM_HDSL_LONG_MSG_LEN_2              ADD_H_LLEN(1)                         /*!< 2 data bytes */
#define EDIM_HDSL_LONG_MSG_LEN_4              ADD_H_LLEN(2)                         /*!< 4 data bytes */
#define EDIM_HDSL_LONG_MSG_LEN_8              ADD_H_LLEN(3)                         /*!< 8 data bytes */

/* EDIM_HDSL indirect addressing of long messages */
#define EDIM_HDSL_LONG_MSG_DIRECT             ((uint8_t)0x00U)                      /*!< direct addressing of "long messages" */
#define EDIM_HDSL_LONG_MSG_INDIRECT           EDIM_HDSL_PC_ADD_H_LIND               /*!< indirect addressing of "long messages" */
                                                                                    
/* EDIM_HDSL Long message addressing mode/long message error */                  
#define EDIM_HDSL_LONG_MSG_WITHOUT_OFFSET     ((uint8_t)0x00U)                      /*!< addressing of "long message" without offset */
#define EDIM_HDSL_LONG_MSG_OFFSET             EDIM_HDSL_PC_ADD_H_LOFF               /*!< offset addressing of "long message" */
                                                                                    
/* EDIM_HDSL Long message addressing mode/long message error */                  
#define EDIM_HDSL_LONG_MSG_WRITE              ((uint8_t)0x00U)                      /*!< "long message" write operation */
#define EDIM_HDSL_LONG_MSG_READ               EDIM_HDSL_PC_ADD_H_LRW                /*!< "long message" read operation */

/* EDIM_HDSL sensorhub flag */ 
#define EDIM_HDSL_SENSORHUB_FLAG_PSCI         EDIM_HDSL_PIPE_S_PSCI                 /*!< Indication for special characters in the SensorHub Channel */
#define EDIM_HDSL_SENSORHUB_FLAG_PERR         EDIM_HDSL_PIPE_S_PERR                 /*!< Coding error of the bits in the SensorHub Channel */
#define EDIM_HDSL_SENSORHUB_FLAG_PEMP         EDIM_HDSL_PIPE_S_PEMP                 /*!< The SensorHub channel buffer is empty */
#define EDIM_HDSL_SENSORHUB_FLAG_POVR         EDIM_HDSL_PIPE_S_POVR                 /*!< SensorHub Channel overflow */

/* EDIM_HDSL max acceleration resolution */ 
#define EDIM_HDSL_MAXACC_RES_256              ((uint8_t)0x00U)                      /*!< acceleration boundary resolution is 256 */
#define EDIM_HDSL_MAXACC_RES_64               ((uint8_t)0x01U)                      /*!< acceleration boundary resolution is 64 */
#define EDIM_HDSL_MAXACC_RES_16               ((uint8_t)0x02U)                      /*!< acceleration boundary resolution is 16 */
#define EDIM_HDSL_MAXACC_RES_4                ((uint8_t)0x03U)                      /*!< acceleration boundary resolution is 4 */

/* EDIM_HDSL safe channel 1 event flag definitions */                                                         
#define EDIM_HDSL_SAFE_FLAG_FRES               EDIM_HDSL_EVENT_S_FRES               /*!< Channel free for "short message" */
#define EDIM_HDSL_SAFE_FLAG_MIN                EDIM_HDSL_EVENT_S_MIN                /*!< Message init */
#define EDIM_HDSL_SAFE_FLAG_PRST               EDIM_HDSL_EVENT_S_PRST               /*!< Protocol reset warning */
#define EDIM_HDSL_SAFE_FLAG_QMLW               EDIM_HDSL_EVENT_S_QMLW               /*!< Quality monitoring low-value warning */
#define EDIM_HDSL_SAFE_FLAG_VPOS               EDIM_HDSL_EVENT_S_VPOS               /*!< Safe position error */
#define EDIM_HDSL_SAFE_FLAG_SCE                EDIM_HDSL_EVENT_S_SCE                /*!< Error on the Safe Channel */
#define EDIM_HDSL_SAFE_FLAG_SSUM               EDIM_HDSL_EVENT_S_SSUM               /*!< Remote event monitoring */
#define EDIM_HDSL_SAFE_FLAG_SINT               EDIM_HDSL_EVENT_S_SINT               /*!< Safe interrupt status */
                                                                                    
/* EDIM_HDSL safe channel 1 event interrupt definitions */                                                    
#define EDIM_HDSL_SAFE_INT_FLAG_FRES           EDIM_HDSL_EVENT_S_FRES               /*!< Channel free for "short message" */
#define EDIM_HDSL_SAFE_INT_FLAG_MIN            EDIM_HDSL_EVENT_S_MIN                /*!< Message init */
#define EDIM_HDSL_SAFE_INT_FLAG_PRST           EDIM_HDSL_EVENT_S_PRST               /*!< Protocol reset warning */
#define EDIM_HDSL_SAFE_INT_FLAG_QMLW           EDIM_HDSL_EVENT_S_QMLW               /*!< Quality monitoring low-value warning */
#define EDIM_HDSL_SAFE_INT_FLAG_VPOS           EDIM_HDSL_EVENT_S_VPOS               /*!< Safe position error */
#define EDIM_HDSL_SAFE_INT_FLAG_SCE            EDIM_HDSL_EVENT_S_SCE                /*!< Error on the Safe Channel */
#define EDIM_HDSL_SAFE_INT_FLAG_SSUM           EDIM_HDSL_EVENT_S_SSUM               /*!< Remote event monitoring */

/* EDIM_HDSL safe channel 1 event interrupt enable definitions */
#define EDIM_HDSL_SAFE_INT_FRES                EDIM_HDSL_MASK_S_MFRES               /*!< Interrupt enable for channel free for "short message" */
#define EDIM_HDSL_SAFE_INT_MIN                 EDIM_HDSL_MASK_S_MMIN                /*!< Interrupt enable for message init */
#define EDIM_HDSL_SAFE_INT_PRST                EDIM_HDSL_MASK_S_MPRST               /*!< Interrupt enable for protocol reset warning */
#define EDIM_HDSL_SAFE_INT_QMLW                EDIM_HDSL_MASK_S_MQMLW               /*!< Interrupt enable for quality monitoring low-value warning */
#define EDIM_HDSL_SAFE_INT_VPOS                EDIM_HDSL_MASK_S_MVPOS               /*!< Interrupt enable for safe position error */
#define EDIM_HDSL_SAFE_INT_SCE                 EDIM_HDSL_MASK_S_MSCE                /*!< Interrupt enable for error on the Safe Channel */
#define EDIM_HDSL_SAFE_INT_SSUM                EDIM_HDSL_MASK_S_MSSUM               /*!< Interrupt enable for remote event monitoring */

/* EDIM_HDSL safe channel 2 flag definitions */                                                         
#define EDIM_HDSL_SAFE2_FLAG_ERR               EDIM_HDSL_STATUS2_ERR2               /*!< Safe Channel 2 Position Error */
#define EDIM_HDSL_SAFE2_FLAG_TEST              EDIM_HDSL_STATUS2_TEST2              /*!< Safe Channel 2 Test */
#define EDIM_HDSL_SAFE2_FLAG_TOG               EDIM_HDSL_STATUS2_TOG2               /*!< Safe Channel 2 Toggle */

/* EDIM_HDSL endian mode */
#define EDIM_HDSL_ENDIAN_MODE_BIG              ((uint8_t)0x00U)                     /*!< Big endian mode */
#define EDIM_HDSL_ENDIAN_MODE_LITTLE           ((uint8_t)0x01U)                     /*!< Little endian mode */

/* EDIM_HDSL channel selection */
#define EDIM_HDSL_DRIVE                        ((uint8_t)0x00U)                     /*!< HDSL unit0 drive*/
#define EDIM_HDSL_SAFE_CHANNEL1                ((uint8_t)0x01U)                     /*!< HDSL unit0 safe channel 1 */
#define EDIM_HDSL_SAFE_CHANNEL2                ((uint8_t)0x02U)                     /*!< HDSL unit0 safe channel 2 */

/* EDIM_HDSL interface */
#define EDIM_HDSL_BUS_INTERFACE                ((uint8_t)0x00U)                     /*!< Internal bus interface */
#define EDIM_HDSL_SPI_INTERFACE                ((uint8_t)0x01U)                     /*!< SPI interface */

/* EDIM_HDSL online drive flag */
#define EDIM_HDSL_ONLINE_D_FLAG_FREL           EDIM_HDSL_ONLINE_STATUS_D_FREL       /*!< channel status for long message */
#define EDIM_HDSL_ONLINE_D_FLAG_QMLW           EDIM_HDSL_ONLINE_STATUS_D_QMLW       /*!< quality monitoring at low level */
#define EDIM_HDSL_ONLINE_D_FLAG_ANS            EDIM_HDSL_ONLINE_STATUS_D_ANS        /*!< incorrect answer detected */
#define EDIM_HDSL_ONLINE_D_FLAG_MIN            EDIM_HDSL_ONLINE_STATUS_D_MIN        /*!< acknowledgment of message initialization */
#define EDIM_HDSL_ONLINE_D_FLAG_PRST           EDIM_HDSL_ONLINE_STATUS_D_PRST       /*!< protocol reset */
#define EDIM_HDSL_ONLINE_D_FLAG_DTE            EDIM_HDSL_ONLINE_STATUS_D_DTE        /*!< deviation threshold error */
#define EDIM_HDSL_ONLINE_D_FLAG_POS            EDIM_HDSL_ONLINE_STATUS_D_POS        /*!< estimator turned on */
#define EDIM_HDSL_ONLINE_D_FLAG_SUM            EDIM_HDSL_ONLINE_STATUS_D_SUM        /*!< summary byte */
#define EDIM_HDSL_ONLINE_D_FLAG_INT            EDIM_HDSL_ONLINE_STATUS_D_INT        /*!< status of the interrupt signal */

/* EDIM_HDSL online safe channel 1 flag */
#define EDIM_HDSL_ONLINE_1_FLAG_FRES           EDIM_HDSL_ONLINE_STATUS_1_FRES       /*!< channel status for the short message */
#define EDIM_HDSL_ONLINE_1_FLAG_QMLW           EDIM_HDSL_ONLINE_STATUS_1_QMLW       /*!< quality monitoring at low level */
#define EDIM_HDSL_ONLINE_1_FLAG_MIN            EDIM_HDSL_ONLINE_STATUS_1_MIN        /*!< acknowledgment of message Initialization */
#define EDIM_HDSL_ONLINE_1_FLAG_PRST           EDIM_HDSL_ONLINE_STATUS_1_PRST       /*!< protocol reset */
#define EDIM_HDSL_ONLINE_1_FLAG_VPOS           EDIM_HDSL_ONLINE_STATUS_1_VPOS       /*!< safe position invalid */
#define EDIM_HDSL_ONLINE_1_FLAG_SCE            EDIM_HDSL_ONLINE_STATUS_1_SCE        /*!< CRC Error on the Safe Channel */
#define EDIM_HDSL_ONLINE_1_FLAG_SSUM           EDIM_HDSL_ONLINE_STATUS_1_SSUM       /*!< Safe summary bit */
#define EDIM_HDSL_ONLINE_1_FLAG_SINT           EDIM_HDSL_ONLINE_STATUS_1_SINT       /*!< Status of the interrupt signal */

/* EDIM_HDSL online safe channel 2 flag */
#define EDIM_HDSL_ONLINE_2_FLAG_QMLW           EDIM_HDSL_ONLINE_STATUS_2_QMLW       /*!< quality monitoring at low level */
#define EDIM_HDSL_ONLINE_2_FLAG_PRST           EDIM_HDSL_ONLINE_STATUS_2_PRST       /*!< protocol reset */
#define EDIM_HDSL_ONLINE_2_FLAG_VPOS2          EDIM_HDSL_ONLINE_STATUS_2_VPOS2      /*!< safe position 2 invalid */
#define EDIM_HDSL_ONLINE_2_FLAG_SCE2           EDIM_HDSL_ONLINE_STATUS_2_SCE2       /*!< transmission error channel 2 */
#define EDIM_HDSL_ONLINE_2_FLAG_SSUM2          EDIM_HDSL_ONLINE_STATUS_2_SSUM2      /*!< summary byte channel 2 */

/* EDIM_HDSL POSTX interrupt source */
#define EDIM_HDSL_POSTX_SRC_01                 ((uint32_t)0x00000000U)              /*!< when POSTX=2'b01 */
#define EDIM_HDSL_POSTX_SRC_10                 ((uint32_t)0x00000001U)              /*!< when POSTX=2'b10 */
#define EDIM_HDSL_POSTX_SRC_11                 ((uint32_t)0x00000002U)              /*!< when POSTX=2'b11 */
#define EDIM_HDSL_POSTX_SRC_01_10_11           ((uint32_t)0x00000003U)              /*!< when POSTX = 2'b01, 2'b10, 2'b11 */
#define EDIM_HDSL_POSTX_SRC_00_TO_01           ((uint32_t)0x00000004U)              /*!< when POSTX transfer from 2'b00 to 2'b01 */
#define EDIM_HDSL_POSTX_SRC_00_TO_10           ((uint32_t)0x00000005U)              /*!< when POSTX transfer from 2'b00 to 2'b10 */
#define EDIM_HDSL_POSTX_SRC_00_TO_01_10        ((uint32_t)0x00000007U)              /*!< when POSTX transfer from 2'b00 to 2'b01 or 2'b10 */
#define EDIM_HDSL_POSTX_SRC_01_TO_10           ((uint32_t)0x00000008U)              /*!< when POSTX transfer from 2'b01 to 2'b10 */
#define EDIM_HDSL_POSTX_SRC_10_TO_11           ((uint32_t)0x00000009U)              /*!< when POSTX transfer from 2'b10 to 2'b11 */
#define EDIM_HDSL_POSTX_SRC_CHANGES            ((uint32_t)0x0000000AU)              /*!< when POSTX changes */


/* edim_hdsl sent long message parameter struct definitions */
typedef struct
{
    uint8_t direction;                                                              /*!< long message, read/write mode */
    uint8_t offset;                                                                 /*!< with offset/withoutoffset */
    uint8_t d_i_mode;                                                               /*!< direct/indirect addressing */
    uint8_t len;                                                                    /*!< long message length */
    uint8_t laddh;                                                                  /*!< long message address, bit 9 to bit 8 (database entry with 10-bit address for a "long message" operation)*/
    uint8_t laddl;                                                                  /*!< long message address, bit 7 to bit 0(database entry with 10-bit address for a "long message" operation) */
    uint8_t ladd_off_l;                                                             /*!< long message address offset, byte 0 */
    uint8_t ladd_off_h;                                                             /*!< long message address offset, byte 1 */
} edim_hdsl_long_msg_addr_struct;

/* function declarations */
/* initialization functions */
/* reset EDIM_HDSL */
void edim_hdsl_deinit(void);
/* initialize edim_hdsl */
void edim_hdsl_init(uint8_t es, uint8_t sync_polarity, uint8_t acc_err_cnt);
/* activation of the output */
void edim_hdsl_output_enable(void);
/* unactivation of the output */
void edim_hdsl_output_disable(void);
/* test drive interface */
void edim_hdsl_test_drive_interface(ControlStatus newvalue);
/* reset pipeline fifo */
void edim_hdsl_pipeline_fifo_reset(ControlStatus newvalue);
/* reset message */
void edim_hdsl_message_reset(ControlStatus newvalue);
/* reset protocol status */
void edim_hdsl_protocol_reset(ControlStatus newvalue);

/* quality monitoring functions */
/* get quality monitoring bits */
uint8_t edim_hdsl_quality_monitoring_get(void);
/* get DSL protocol connection status */
FlagStatus edim_hdsl_protocol_connection_status_get(void);

/* cable and signal functions */
/* get edges in cable signal */
uint8_t edim_hdsl_cable_signal_edge_get(void);
/* get cable delay */
uint8_t edim_hdsl_cable_delay_get(void);
/* get received signal strength */
uint8_t edim_hdsl_received_signal_strength_get(void);

/* version and ID functions */
/* get current version */
uint8_t edim_hdsl_version_get(void);
/* get encoder id information */
uint32_t edim_hdsl_encoder_id_get(void);

/* position and speed functions */
/* get fast position */
uint64_t edim_hdsl_position_read(void);
/* get safe position */
uint64_t edim_hdsl_vposition_read(void);
/* get safe position value from safe channel 2 */
uint64_t edim_hdsl_vposition2_read(void);
/* get speed */
uint32_t edim_hdsl_speed_read(void);

/* status functions */
/* get mirror status summary flag */
uint8_t edim_hdsl_mirror_status_sum_flag_get(void);

/* parameter channel functions */
/* write parameter channel buffer */
void edim_hdsl_long_message_write(uint64_t data);
/* read the answer to a long message in parameter channel buffer */
uint64_t edim_hdsl_long_message_read(void);
/* read errors in encoder resources arising from the previous "long message" operation */
uint16_t edim_hdsl_long_message_error_read(void);
/* initialize EDIM_HDSL long message address struct with a default value */
void edim_hdsl_long_message_addr_init_struct_para_init(edim_hdsl_long_msg_addr_struct *initpara);
/* long message send address initialization */
void edim_hdsl_long_message_addr_init(edim_hdsl_long_msg_addr_struct* msg_addr_struct);
/* long message error flag get */
FlagStatus edim_hdsl_long_message_error_flag_get(void);
/* configure long message addressing offset mode */
void edim_hdsl_long_message_addr_offset_mode_config(uint8_t mode);
/* configure long message read / write mode */
void edim_hdsl_long_message_read_write_mode_config(uint8_t mode);
/* configure long message addressing direction mode */
void edim_hdsl_long_message_addr_direction_config(uint8_t mode);
/* configure long message data length */
void edim_hdsl_long_message_data_length_config(uint8_t length);
/* configure long message address */
void edim_hdsl_long_message_addr_config(uint8_t laddh, uint8_t laddl);
/* configure long message address offset */
void edim_hdsl_long_message_addr_offset_config(uint8_t ladd_off_h, uint8_t ladd_off_l);
/* start "long message" transaction */
void edim_hdsl_long_message_transaction_start(void);

/* sensorhub channel functions */
/* get sensorhub channel flag */
FlagStatus edim_hdsl_sensorhub_channel_flag_get(uint32_t flag);
/* read sensorhub channel data */
uint8_t edim_hdsl_sensorhub_channel_data_read(void);
/* read short message mirror data */
uint8_t edim_hdsl_short_message_mirror_data_read(void);

/* position error and acceleration functions */
/* read position error count */
uint8_t edim_hdsl_position_error_count_read(void);
/* configure fast position acceleration boundary */
void edim_hdsl_fast_position_acc_boundary_config(uint8_t mantissa, uint8_t resolution);
/* configure fast position estimator deviation threshold */
void edim_hdsl_fast_position_estimator_deviation_threshold_config(uint16_t threshold);
/* read fast position estimator deviation */
uint16_t edim_hdsl_fast_position_estimator_deviation_read(void);

/* dummy functions */
/* read dummy */
uint8_t edim_hdsl_dummy_read(void);

/* mirror status functions */
/* access slave mirror system errors, events, and warnings from the DSL encoder */
uint8_t edim_hdsl_mirror_status_flag_access(uint8_t reg_idx);
/* clear slave mirror system errors, events, and warnings from the DSL encoder */
void edim_hdsl_mirror_status_flag_clear(uint8_t reg_idx);

/* safe channel 1 functions */
/* get edges in safe channel 1 cable signal */
uint8_t edim_hdsl_safe_channel1_cable_signal_edge_get(void);
/* get safe channel 1 cable delay */
uint8_t edim_hdsl_safe_channel1_cable_delay_get(void);
/* get received safe channel 1 signal strength */
uint8_t edim_hdsl_received_safe_channel1_signal_strength_get(void);
/* safe channel 1 version information */
uint8_t edim_hdsl_safe_channel1_version_get(void);
/* get safe channel 1 encoder id information */
uint32_t edim_hdsl_safe_channel1_encoder_id_get(void);
/* read safe channel 1 position crc */
uint16_t edim_hdsl_safe_channel1_position_crc_read(void);
/* reset message for the safety-related application */
void edim_hdsl_safe_message_reset(ControlStatus newvalue);
/* reset protocol status for the safety-related application */
void edim_hdsl_safe_protocol_reset(ControlStatus newvalue);
/* get safe status summary flag */
uint8_t edim_hdsl_safe_status_sum_flag_get(void);
/* read parameter channel short message */
uint8_t edim_hdsl_short_message_read(void);

/* encoder status functions */
/* access slave system errors, events, and warnings from the DSL encoder */
uint8_t edim_hdsl_encoder_status_flag_access(uint8_t reg_idx);
/* clear slave system errors, events, and warnings from the DSL encoder */
void edim_hdsl_encoder_status_flag_clear(uint8_t reg_idx);

/* slave RSSI and communication functions */
/* read slave RSSI */
uint8_t edim_hdsl_slave_rssi_read(void);
/* configure slave mail */
void edim_hdsl_slave_mail_config(uint8_t mail);
/* configure slave ping */
void edim_hdsl_slave_ping_write(uint8_t ping);
/* read slave ping */
uint8_t edim_hdsl_slave_ping_read(void);

/* safe channel 2 functions */
/* get safe channel 2 version information */
uint8_t edim_hdsl_safe_channel2_version_get(void);
/* safe channel 2 encoder ID information */
uint8_t edim_hdsl_safe_channel2_encoder_id_get(void);
/* read EDIM_HDSL safe channel 2 fixed bit pattern */
uint8_t edim_hdsl_safe_channel2_fix_bit_read(void);
/* read safe channel 2 position crc */
uint16_t edim_hdsl_safe_channel2_position_crc_read(void);
/* read dummy2 */
uint8_t edim_hdsl_dummy2_read(void);

/* configuration functions */
/* configure hdsl unit0 endian mode */
void edim_hdsl_endian_mode_config(uint8_t mode);
/* select hdsl unit0 interface */
void edim_hdsl_interface_select(uint8_t channel, uint8_t mode);

/* synchronization functions */
/* get hdsl position sampling resolution lock */
FlagStatus edim_hdsl_position_sampling_resolution_lock_get(void);
/* configure hdsl POSTX interrupt source */
void edim_hdsl_postx_interrupt_source_select(uint32_t source);
/* enable POSTX interrupt */
void edim_hdsl_postx_interrupt_enable(void);
/* disable POSTX interrupt */
void edim_hdsl_postx_interrupt_disable(void);
/* enable safe channel 1 global interrupt */
void edim_hdsl_safe_channel1_global_interrupt_enable(void);
/* disable safe channel 1 global interrupt */
void edim_hdsl_safe_channel1_global_interrupt_disable(void);

/* status functions */
/* get EDIM_HDSL online d flag */
FlagStatus edim_hdsl_online_d_flag_get(uint32_t flag);
/* get online d position transmission status */
uint8_t edim_hdsl_online_d_position_transmission_status_get(void);
/* get EDIM_HDSL online 1 flag */
FlagStatus edim_hdsl_online_1_flag_get(uint32_t flag);
/* get online 1 position transmission status */
uint8_t edim_hdsl_online_1_position_transmission_status_get(void);
/* get EDIM_HDSL online 2 flag */
FlagStatus edim_hdsl_online_2_flag_get(uint32_t flag);
/* get online 2 position transmission status */
uint8_t edim_hdsl_online_2_position_transmission_status_get(void);

/* flag and interrupt functions */
/* get EDIM_HDSL flag status */
FlagStatus edim_hdsl_flag_get(uint32_t flag);
/* clear EDIM_HDSL flag status */
void edim_hdsl_flag_clear(uint32_t flag);
/* enable EDIM_HDSL interrupt */
void edim_hdsl_interrupt_enable(uint32_t interrupt);
/* disable EDIM_HDSL interrupt */
void edim_hdsl_interrupt_disable(uint32_t interrupt);
/* enable mirror sum bit set the sum event monitoring in the EVENT_H register and the interrupt signal */
void edim_hdsl_mir_sum_event_enable(uint32_t flag);
/* disable mirror sum bit set the sum event monitoring in the EVENT_H register and the interrupt signal */
void edim_hdsl_mir_sum_event_disable(uint32_t flag);
/* get EDIM_HDSL interrupt event flag */
FlagStatus edim_hdsl_interrupt_flag_get(uint32_t flag);
/* clear EDIM_HDSL interrupt event flag */
void edim_hdsl_interrupt_flag_clear(uint32_t flag);
/* get EDIM_HDSL safe channel 1 event flag */
FlagStatus edim_hdsl_safe_channel1_flag_get(uint8_t flag);
/* clear EDIM_HDSL safe channel 1 event flag */
void edim_hdsl_safe_channel1_flag_clear(uint8_t flag);
/* enable EDIM_HDSL safe channel 1 interrupt */
void edim_hdsl_safe_channel1_interrupt_enable(uint8_t interrupt);
/* disable EDIM_HDSL safe channel 1 interrupt */
void edim_hdsl_safe_channel1_interrupt_disable(uint8_t interrupt);
/* get EDIM_HDSL safe channel 1 interrupt event flag */
FlagStatus edim_hdsl_safe_channel1_interrupt_flag_get(uint8_t flag);
/* clear EDIM_HDSL safe channel 1 event flag */
void edim_hdsl_safe_channel1_interrupt_flag_clear(uint8_t flag);
/* get EDIM_HDSL safe channel 2 flag */
FlagStatus edim_hdsl_safe_channel2_flag_get(uint8_t flag);

#endif /* GD32H77X_78X_EDIM_HDSL_H */