/*!
    \file    gd32h77x_78x_esc.c
    \brief   ESC driver

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

#include "gd32h77x_78x_esc.h"
#include <string.h>

#define ESC_ADDR_MASK           (uint16_t)0x0FFFU
#define ESC_TIMEOUT_CNT_MASK    (uint32_t)0x000001FFU
/* rc_w1 flag bits of ESC_CTL, must be written as 0 in read-modify-write to avoid clearing them */
#define ESC_CTL_FLAG_MASK       (ESC_CTL_EERF | ESC_CTL_WDLF | ESC_CTL_TOF | ESC_CTL_WEF | ESC_CTL_IVF | ESC_CTL_I2CF)

#define ESC_DELAY               ((uint32_t)0x01FFFFFFU)     /* Timeout for ESC operations */

/*!
    \brief      pdi direct access read esc register (API_ID(0x0001U))
    \param[in]  readbuffer: data read buffer
    \param[in]  addr: esc register address offset
    \param[in]  count: the number to read from esc register
    \param[out] none
    \retval     none
*/
void pdi_direct_read_reg(uint8_t readbuffer[], uint16_t addr, uint16_t count)
{
    uint16_t address = (addr & ESC_ADDR_MASK);
    uint16_t i;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(readbuffer)) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0001U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(count) {
        case 0x1U:
            *(uint8_t *)readbuffer = REG8(ESC_BASE + address);
            break;
        case 0x2U:
            *(uint16_t *)readbuffer = REG16(ESC_BASE + address);
            break;
        case 0x4U:
            *(uint32_t *)readbuffer = REG32(ESC_BASE + address);
            break;
        default:
            for(i = 0U; i < count; i++) {
                readbuffer[i] = REG8(ESC_BASE + address + i);
            }
            break;
        }
    }
}

/*!
    \brief      pdi direct access write esc register (API_ID(0x0002U))
    \param[in]  writebuffer: data write buffer
    \param[in]  addr: esc register address offset
    \param[in]  count: the number to write to esc register
    \param[out] none
    \retval     none
*/
void pdi_direct_write_reg(uint8_t writebuffer[], uint16_t addr, uint16_t count)
{
    uint16_t address = (addr & ESC_ADDR_MASK);
    uint16_t i;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(writebuffer)) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(count) {
        case 0x0001U:
            REG8(ESC_BASE + address) = *(uint8_t *)writebuffer;
            break;
        case 0x0002U:
            REG16(ESC_BASE + address) = *(uint16_t *)writebuffer;
            break;
        case 0x0004U:
            REG32(ESC_BASE + address) = *(uint32_t *)writebuffer;
            break;
        default:
            for(i = 0U; i < count; i++) {
                REG8(ESC_BASE + address + i) = writebuffer[i];
            }
            break;
        }
    }
}

/*!
    \brief      pdi direct access read esc pdram (API_ID(0x0003U))
    \param[in]  readbuffer: data read buffer
    \param[in]  addr: esc pdram address offset
    \param[in]  count: the number to read from esc pdram
    \param[out] none
    \retval     none
*/
void pdi_direct_read_pdram(uint8_t readbuffer[], uint16_t addr, uint16_t count)
{
    uint32_t address = (uint32_t)addr;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(readbuffer)) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint16_t i = 0U;

        while(i < count) {
            /* check if current address is 4-byte aligned and we have at least 4 bytes left */
            if(((address + i) % 4U == 0U) && ((count - i) >= 4U)) {
                /* use 32-bit access with proper type casting */
                *(uint32_t *)(&readbuffer[i]) = REG32(ESC_BASE + address + i);
                i += 4U;
            } else {
                /* use 8-bit access for unaligned or remaining bytes */
                readbuffer[i] = REG8(ESC_BASE + address + i);
                i++;
            }
        }
    }
}

/*!
    \brief      pdi direct access write esc pdram (API_ID(0x0004U))
    \param[in]  writebuffer: data write buffer
    \param[in]  addr: esc pdram address offset
    \param[in]  count: the number to write to esc pdram
    \param[out] none
    \retval     none
*/
void pdi_direct_write_pdram(uint8_t writebuffer[], uint16_t addr, uint16_t count)
{
    uint32_t address = (uint32_t)addr;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(writebuffer)) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0004U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint16_t i = 0U;

        while(i < count) {
            /* check if current address is 4-byte aligned and we have at least 4 bytes left */
            if(((address + i) % 4U == 0U) && ((count - i) >= 4U)) {
                /* use 32-bit access with proper type casting */
                REG32(ESC_BASE + address + i) = *(uint32_t *)(&writebuffer[i]);
                i += 4U;
            } else {
                /* use 8-bit access for unaligned or remaining bytes */
                REG8(ESC_BASE + address + i) = writebuffer[i];
                i++;
            }
        }
    }
}

/*!
    \brief      esc pdi reset (API_ID(0x0005U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pdi_reset(void)
{
    uint8_t wbuffer[1] = {0U};
    wbuffer[0] = PDI_RESET_R; /* R */
    pdi_direct_write_reg(wbuffer, ESC_RST_PDI_OFFSET, 0x0001U);
    wbuffer[0] = PDI_RESET_E; /* E */
    pdi_direct_write_reg(wbuffer, ESC_RST_PDI_OFFSET, 0x0001U);
    wbuffer[0] = PDI_RESET_S; /* S */
    pdi_direct_write_reg(wbuffer, ESC_RST_PDI_OFFSET, 0x0001U);
}

/*!
    \brief      PDI read phy (API_ID(0x0006U))
    \param[in]  phy_addr: phy address, 0~31
    \param[in]  phy_reg_addr: phy register address
    \param[out] none
    \retval     res: 16-bit PHY register data read from the specified address
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
uint16_t pdi_phy_read(uint8_t phy_addr, uint8_t phy_reg_addr)
{
    uint8_t temp        = 0U;
    uint8_t value       = 0U;
    uint8_t readbuf[2]  = {0U};
    uint16_t res        = 0U;
    uint32_t timeout;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(phy_addr > 31U) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0006U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* PDI access MDIO allowed */
        temp = PDI_ACCESS_MII_MANAGEMENT_ENABLE;
        pdi_direct_write_reg(&temp, MIIM_PDI_ACC_STAT_OFFSET, 0x0001U);

        /*1. check mdio idle state */
        timeout = ESC_DELAY;
        do {
            pdi_direct_read_reg(&temp, ESC_MII_MNG_STAT_OFFSET, 0x0001U);
            timeout--;
        } while((0U != timeout) && (temp & 0x80U));

        /*2. write PHY address and PHY register */
        value = phy_addr;
        pdi_direct_write_reg(&value, ESC_PHY_ADDR_OFFSET, 0x0001U);
        value = phy_reg_addr;
        pdi_direct_write_reg(&value, ESC_PHY_REG_ADDR_OFFSET, 0x0001U);

        /* 3. write PHY command */
        value = READ_PHY_CMD;
        pdi_direct_write_reg(&value, ESC_MII_MNG_STAT_OFFSET, 0x0001U);

        /* 4. wait for mdio idle and get data */
        timeout = ESC_DELAY;
        do {
            pdi_direct_read_reg(&temp, ESC_MII_MNG_STAT_OFFSET, 0x0001U);
            timeout--;
        } while((0U != timeout) && (temp & 0x80U));

        /* 5. check mdio idle state */
        pdi_direct_read_reg(readbuf, ESC_PHY_DATA_OFFSET, 0x0002U);

        res = (uint16_t)((((uint32_t)readbuf[1]) << 8U) | (readbuf[0]));
    }
    return res;
}

/*!
    \brief      PDI write phy (API_ID(0x0007U))
    \param[in]  phy_addr: phy address, 0~31
    \param[in]  phy_reg_addr: phy register address
    \param[in]  phy_data: phy data
    \param[out] none
    \retval     none
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
void pdi_phy_write(uint8_t phy_addr, uint8_t phy_reg_addr, uint16_t phy_data)
{
    uint8_t temp         = 0U;
    uint8_t value        = 0U;
    uint8_t writebuf[2]  = {0U};
    uint32_t timeout;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(phy_addr > 31U) {
        fw_debug_report_err(ESC_MODULE_ID, API_ID(0x0007U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        writebuf[0] = (uint8_t)phy_data;
        writebuf[1] = (uint8_t)(phy_data >> 8U);

        /* PDI access MDIO allowed */
        temp = PDI_ACCESS_MII_MANAGEMENT_ENABLE;
        pdi_direct_write_reg(&temp, MIIM_PDI_ACC_STAT_OFFSET, 0x0001U);

        /* 1. check mdio idle state */
        timeout = ESC_DELAY;
        do {
            pdi_direct_read_reg(&temp, ESC_MII_MNG_STAT_OFFSET, 0x0001U);
            timeout--;
        } while((0U != timeout) && (temp & 0x80U));

        /* 2. write PHY address and PHY register */
        value = phy_addr;
        pdi_direct_write_reg(&value, ESC_PHY_ADDR_OFFSET, 0x0001U);
        value = phy_reg_addr;
        pdi_direct_write_reg(&value, ESC_PHY_REG_ADDR_OFFSET, 0x0001U);

        /* 3. write PHY data */
        pdi_direct_write_reg(writebuf, ESC_PHY_DATA_OFFSET, 0x0002U);

        /* 4. write PHY command and enable */
        value = WRITE_PHY_ENABLE;
        pdi_direct_write_reg(&value, ESC_MII_MNG_CTL_OFFSET, 0x0001U);
        value = WRITE_PHY_CMD;
        pdi_direct_write_reg(&value, ESC_MII_MNG_STAT_OFFSET, 0x0001U);

        /* 5. wait for mdio idle */
        timeout = ESC_DELAY;
        do {
            pdi_direct_read_reg(&temp, ESC_MII_MNG_STAT_OFFSET, 0x0001U);
            timeout--;
        } while((0U != timeout) && (temp & 0x80U));
    }
}

/*!
    \brief      ESC brp enable (API_ID(0x0008U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void esc_brp_enable(void)
{
    ESC_CTL = (ESC_CTL & ~ESC_CTL_FLAG_MASK) | ESC_CTL_BRP;
}

/*!
    \brief      ESC brp disable (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void esc_brp_disable(void)
{
    ESC_CTL &= ~(ESC_CTL_FLAG_MASK | ESC_CTL_BRP);
}

/*!
    \brief      ESC timeout enable (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void esc_timeout_enable(void)
{
    ESC_CTL = (ESC_CTL & ~ESC_CTL_FLAG_MASK) | ESC_CTL_TOEN;
}

/*!
    \brief      ESC timeout disable (API_ID(0x000BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void esc_timeout_disable(void)
{
    ESC_CTL &= ~(ESC_CTL_FLAG_MASK | ESC_CTL_TOEN);
}

/*!
    \brief      ESC timeout counter (API_ID(0x000CU))
    \param[in]  cnt:0-511
    \param[out] none
    \retval     none
*/
void esc_timeout_cnt(uint32_t cnt)
{
    uint32_t reg;

    reg = ESC_CTL & ~(ESC_CTL_FLAG_MASK | ESC_CTL_TO_CNT);
    reg |= ESC_TO_CNT(cnt & ESC_TIMEOUT_CNT_MASK);
    ESC_CTL = reg;
}

/*!
    \brief      enable the on_chip_bus interrupt (API_ID(0x000DU))
    \param[in]  interrupt: refer to esc_on_chip_bus_interrupt_enum
                  only one parameter can be selected which is shown as below:
      \arg        ESC_I2CIE: Internal I2C overrun interrupt enable
      \arg        ESC_IVIE: CCTL size & addr illegal value interrupt enable
      \arg        ESC_WEIE: write error interrupt enable
      \arg        ESC_TOIE: time out interrupt enable
      \arg        ESC_WDLIE: write data lost interrupt enable
      \arg        ESC_EERIE: EEPROM reload complete interrupt enable
    \param[out] none
    \retval     none
*/
void esc_interrupt_enable(esc_on_chip_bus_interrupt_enum interrupt)
{
    ESC_REG_VAL(interrupt) = (ESC_REG_VAL(interrupt) & ~ESC_CTL_FLAG_MASK) | BIT(ESC_BIT_POS(interrupt));
}

/*!
    \brief      disable the on_chip_bus interrupt (API_ID(0x000EU))
    \param[in]  interrupt: refer to esc_on_chip_bus_interrupt_enum
                  only one parameter can be selected which is shown as below:
      \arg        ESC_I2CIE: Internal I2C overrun interrupt enable
      \arg        ESC_IVIE: CCTL size & addr illegal value interrupt enable
      \arg        ESC_WEIE: write error interrupt enable
      \arg        ESC_TOIE: time out interrupt enable
      \arg        ESC_WDLIE: write data lost interrupt enable
      \arg        ESC_EERIE: EEPROM reload complete interrupt enable
    \param[out] none
    \retval     none
*/
void esc_interrupt_disable(esc_on_chip_bus_interrupt_enum interrupt)
{
    ESC_REG_VAL(interrupt) &= ~(ESC_CTL_FLAG_MASK | BIT(ESC_BIT_POS(interrupt)));
}

/*!
    \brief      get esc on_chip_bus interrupt flag (API_ID(0x000FU))
    \param[in]  int_flag: refer to esc_on_chip_bus_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        ESC_FLAG_I2CF: Internal I2C communication error flag
      \arg        ESC_FLAG_IVF: CCTL size & addr illegal value flag
      \arg        ESC_FLAG_WEF: write error flag
      \arg        ESC_FLAG_TOF: time out flag
      \arg        ESC_FLAG_WDLF: write data lost flag
      \arg        ESC_FLAG_EERF: EEPROM reload complete flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
    \note       SET is returned only when both the flag and its interrupt enable bit are set.
                After the interrupt enable bit is cleared, if the hardware flag remains set, this API will still return RESET.
                Therefore, in an ISR or during the interrupt-disable flow, this API alone must not be relied upon to determine whether the flag should be cleared.
                The corresponding flag must be cleared according to the module-specific rules, and the NVIC-pending bit should also be cleared when necessary.
*/
FlagStatus esc_interrupt_flag_get(esc_on_chip_bus_flag_enum int_flag)
{
    FlagStatus reval = RESET;
    uint32_t reg = ESC_REG_VAL(int_flag);
    uint32_t pos = ESC_BIT_POS(int_flag);

    /* each interrupt enable bit is located one bit below its flag bit */
    if((RESET != (reg & BIT(pos))) && (RESET != (reg & BIT(pos - 1U)))) {
        reval = SET;
    }
    return reval;
}

/*!
    \brief      clear esc on_chip_bus interrupt flag (API_ID(0x0010U))
    \param[in]  int_flag: refer to esc_on_chip_bus_flag_enum
                  only one parameter can be selected which is shown as below:
      \arg        ESC_FLAG_I2CF: Internal I2C communication error flag
      \arg        ESC_FLAG_IVF: CCTL size & addr illegal value flag
      \arg        ESC_FLAG_WEF: write error flag
      \arg        ESC_FLAG_TOF: time out flag
      \arg        ESC_FLAG_WDLF: write data lost flag
      \arg        ESC_FLAG_EERF: EEPROM reload complete flag
    \param[out] none
    \retval     none
*/
void esc_interrupt_flag_clear(esc_on_chip_bus_flag_enum int_flag)
{
    ESC_REG_VAL(int_flag) = (ESC_REG_VAL(int_flag) & ~ESC_CTL_FLAG_MASK) | BIT(ESC_BIT_POS(int_flag));
}

/*!
    \brief      clear SYNC0 interrupt (API_ID(0x0011U))
    \param[in]  none
    \param[out] none
    \retval     none
    \note       SYNC0_INT bit is not readable, writing any value clears it to zero.
*/
void esc_sync0_interrupt_clear(void)
{
    ESC_SYNC0 = ESC_SYNC0_SYNC0INT;
}

/*!
    \brief      clear SYNC1 interrupt (API_ID(0x0012U))
    \param[in]  none
    \param[out] none
    \retval     none
    \note       SYNC1_INT bit is not readable, writing any value clears it to zero.
*/
void esc_sync1_interrupt_clear(void)
{
    ESC_SYNC1 = ESC_SYNC1_SYNC1INT;
}
