/*!
    \file    gd32h77x_78x_syscfg.c
    \brief   SYSCFG driver

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

#include "gd32h77x_78x_syscfg.h"

#define SYSCFG_FMP_MASK                         0x000000FFU
#define SYSCFG_ANALOG_SWITCH_MASK               0x0F000000U
#define SYSCFG_LOCKUP_MASK                      0x0000F8C4U
#define SYSCFG_LINKACT_POLSEL_MASK              0x00000380U
#define SYSCFG_NLINK_POLSEL_MASK                0x00070000U
#define SYSCFG_PHY_OFFSET_MASK                  0x0000001FU
#define SYSCFG_MOS_COMPENSATION_MASK            0x0000000FU
#define SYSCFG_BUSTO_MASK                       0x0001FFFFU

/*!
    \brief      reset the SYSCFG registers (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_deinit(void)
{
    rcu_periph_reset_enable(RCU_SYSCFGRST);
    rcu_periph_reset_disable(RCU_SYSCFGRST);
}

/*!
    \brief      enable I2Cx(x=0,1,2,3) fast mode plus or I2C fast mode plus PBx(x=6,7,8,9) (API_ID(0x0002U))
    \param[in]  i2c_fmp
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_I2C0_FMP: I2C0 fast mode plus
      \arg        SYSCFG_I2C1_FMP: I2C1 fast mode plus
      \arg        SYSCFG_I2C2_FMP: I2C2 fast mode plus
      \arg        SYSCFG_I2C3_FMP: I2C3 fast mode plus
      \arg        SYSCFG_I2C_FMP_PB6: I2C fast mode plus on PB6 pin
      \arg        SYSCFG_I2C_FMP_PB7: I2C fast mode plus on PB7 pin
      \arg        SYSCFG_I2C_FMP_PB8: I2C fast mode plus on PB8 pin
      \arg        SYSCFG_I2C_FMP_PB9: I2C fast mode plus on PB9 pin
    \param[out] none
    \retval     none
*/
void syscfg_i2c_fast_mode_plus_enable(uint32_t i2c_fmp)
{
    SYSCFG_PMCFG0 |= i2c_fmp & SYSCFG_FMP_MASK;
}

/*!
    \brief      disable I2Cx(x=0,1,2,3) fast mode plus or I2C fast mode plus PBx(x=6,7,8,9) (API_ID(0x0003U))
    \param[in]  i2c_fmp
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_I2C0_FMP: I2C0 fast mode plus
      \arg        SYSCFG_I2C1_FMP: I2C1 fast mode plus
      \arg        SYSCFG_I2C2_FMP: I2C2 fast mode plus
      \arg        SYSCFG_I2C3_FMP: I2C3 fast mode plus
      \arg        SYSCFG_I2C_FMP_PB6: I2C fast mode plus on PB6 pin
      \arg        SYSCFG_I2C_FMP_PB7: I2C fast mode plus on PB7 pin
      \arg        SYSCFG_I2C_FMP_PB8: I2C fast mode plus on PB8 pin
      \arg        SYSCFG_I2C_FMP_PB9: I2C fast mode plus on PB9 pin
    \param[out] none
    \retval     none
*/
void syscfg_i2c_fast_mode_plus_disable(uint32_t i2c_fmp)
{
    SYSCFG_PMCFG0 &= (uint32_t)(~(i2c_fmp & SYSCFG_FMP_MASK));
}

/*!
    \brief      open analog switch (Pxy and Pxy_C are separated pads) (API_ID(0x0004U))
    \param[in]  gpio_answ: GPIO analog switch
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_PA0_ANALOG_SWITCH: PA0 analog switch
      \arg        SYSCFG_PA1_ANALOG_SWITCH: PA1 analog switch
      \arg        SYSCFG_PC2_ANALOG_SWITCH: PC2 analog switch
      \arg        SYSCFG_PC3_ANALOG_SWITCH: PC3 analog switch
    \param[out] none
    \retval     none
*/
void syscfg_analog_switch_enable(uint32_t gpio_answ)
{
    SYSCFG_PMCFG0 |= gpio_answ & SYSCFG_ANALOG_SWITCH_MASK;
}

/*!
    \brief      close analog switch (Pxy and Pxy_C are connected through the analog switch) (API_ID(0x0005U))
    \param[in]  gpio_answ: GPIO analog switch
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_PA0_ANALOG_SWITCH: PA0 analog switch
      \arg        SYSCFG_PA1_ANALOG_SWITCH: PA1 analog switch
      \arg        SYSCFG_PC2_ANALOG_SWITCH: PC2 analog switch
      \arg        SYSCFG_PC3_ANALOG_SWITCH: PC3 analog switch
    \param[out] none
    \retval     none
*/
void syscfg_analog_switch_disable(uint32_t gpio_answ)
{
    SYSCFG_PMCFG0 &= (uint32_t)(~(gpio_answ & SYSCFG_ANALOG_SWITCH_MASK));
}

/*!
    \brief      configure the PHY interface for the ethernet MAC (API_ID(0x0006U))
    \param[in]  ethernet: ENETx(x=0,1)
    \param[in]  phy_interface: specifies the media interface mode
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_ENET_PHY_MII: MII mode is selected
      \arg        SYSCFG_ENET_PHY_RMII: RMII mode is selected
    \param[out] none
    \retval     none
*/
void syscfg_enet_phy_interface_config(uint32_t ethernet, uint32_t phy_interface)
{
    uint32_t reg;
    /* read the value of SYSCFG_PMCFG0 register */
    reg = SYSCFG_PMCFG0;
    /* configure the ENET media interface */
    if(ENET0 == ethernet) {
        reg &= ~SYSCFG_PMCFG0_ENET0_PHY_SEL;
        reg |= ENET0_MEDIA_INTERFACE(phy_interface);
    } else {
        reg &= ~SYSCFG_PMCFG0_ENET1_PHY_SEL;
        reg |= ENET1_MEDIA_INTERFACE(phy_interface);
    }
    SYSCFG_PMCFG0 = reg;
}

/*!
    \brief      configure the GPIO pin as EXTI Line (API_ID(0x0007U))
    \param[in]  exti_port: specify the GPIO port used in EXTI
                only one parameter can be selected which is shown as below:
      \arg        EXTI_SOURCE_GPIOx(x = A,B,C,D,E,F,G,H,J,K): EXTI GPIO port
    \param[in]  exti_pin: specify the EXTI line
                only one parameter can be selected which is shown as below:
      \arg        EXTI_SOURCE_PINx(GPIOA x = 0..15,GPIOB x = 0..15,GPIOC x = 0..15,GPIOD x = 0..15,GPIOE x = 0..15,
                  GPIOF x = 0..15,GPIOG x = 0..15,GPIOH x = 0..15,GPIOI x = 0..15,GPIOJ x = 8,9,10,11, GPIOK x = 0,1,2,4,5,6): EXTI GPIO pin
    \param[out] none
    \retval     none
*/
void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin)
{
    uint32_t clear_exti_mask = ~((uint32_t)EXTI_SS_MASK << (EXTI_SS_MSTEP(exti_pin)));
    uint32_t config_exti_mask = ((uint32_t)exti_port) << (EXTI_SS_MSTEP(exti_pin));

    switch(exti_pin / EXTI_SS_JSTEP) {
    case EXTISS0:
        /* clear EXTI source line(0..3) */
        SYSCFG_EXTISS0 &= clear_exti_mask;
        /* configure EXTI source line(0..3) */
        SYSCFG_EXTISS0 |= config_exti_mask;
        break;
    case EXTISS1:
        /* clear EXTI source line(4..7) */
        SYSCFG_EXTISS1 &= clear_exti_mask;
        /* configure EXTI source line(4..7) */
        SYSCFG_EXTISS1 |= config_exti_mask;
        break;
    case EXTISS2:
        /* clear EXTI source line(8..11) */
        SYSCFG_EXTISS2 &= clear_exti_mask;
        /* configure EXTI source line(8..11) */
        SYSCFG_EXTISS2 |= config_exti_mask;
        break;
    case EXTISS3:
        /* clear EXTI source line(12..15) */
        SYSCFG_EXTISS3 &= clear_exti_mask;
        /* configure EXTI source line(12..15) */
        SYSCFG_EXTISS3 |= config_exti_mask;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable module lockup function (function can be disabled by system reset) (API_ID(0x0008U))
    \param[in]  lockup:
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_LVD_LOCKUP: LVD signal
      \arg        SYSCFG_CPU_LOCKUP: CPU lockup signal
      \arg        SYSCFG_BKPRAM_LOCKUP: Region 2 backup SRAM ECC double error signal
      \arg        SYSCFG_SRAM1_LOCKUP: Region 1 SRAM1 ECC double error signal
      \arg        SYSCFG_SRAM0_LOCKUP: Region 1 SRAM0 ECC double error signal
      \arg        SYSCFG_DTCM_LOCKUP: Region 0 DTCM ECC double error signal
      \arg        SYSCFG_ITCM_LOCKUP: Region 0 ITCM-RAM ECC double error signal
      \arg        SYSCFG_AXIRAM_LOCKUP: Region 0 AXI-SRAM ECC double error signal
    \param[out] none
    \retval     none
*/
void syscfg_lockup_enable(uint32_t lockup)
{
    SYSCFG_LKCTL |= lockup & SYSCFG_LOCKUP_MASK;
}

/*!
    \brief      select timer channel input source (API_ID(0x0009U))
    \param[in]  timer_input: Timer channel input select, refer to timer_channel_input_enum
      \arg        TIMER7_CI0_INPUT_TIMER7_CH0: select TIMER7 CH0 as TIMER7 CI0
      \arg        TIMER7_CI0_INPUT_CMP1_OUT: select CMP1 output as TIMER7 CI0
      \arg        TIMER0_CI0_INPUT_TIMER0_CH0: select TIMER0 CH0 as TIMER0 CI0
      \arg        TIMER0_CI0_INPUT_CMP0_OUT: select CMP0 output as TIMER0 CI0
      \arg        TIMER2_CI0_INPUT_TIMER2_CH0: select TIMER2 CH0 as TIMER2 CI0
      \arg        TIMER2_CI0_INPUT_CMP0_OUT: select CMP0 as TIMER2 CI0
      \arg        TIMER2_CI0_INPUT_CMP1_OUT: select CMP1 as TIMER2 CI0
      \arg        TIMER2_CI0_INPUT_CMP0_OR_CMP1_OUT: select CMP0 or CMP1 as TIMER2 CI0
      \arg        TIMER1_CI3_INPUT_TIMER1_CH3: select TIMER1 CH3 as TIMER1 CI3
      \arg        TIMER1_CI3_INPUT_CMP0_OUT: select CMP0 output as TIMER1 CI3
      \arg        TIMER1_CI3_INPUT_CMP1_OUT: select CMP1 output as TIMER1 CI3
      \arg        TIMER1_CI3_INPUT_CMP0_OR_CMP1_OUT: select CMP0 or CMP1 output as TIMER1 CI3
      \arg        TIMER22_CI3_INPUT_TIMER22_CH3: select TIMER22 CH3 as TIMER22 CI3
      \arg        TIMER22_CI3_INPUT_CMP0_OUT: select CMP0 output as TIMER22 CI3
      \arg        TIMER22_CI3_INPUT_CMP1_OUT: select CMP1 output as TIMER22 CI3
      \arg        TIMER22_CI3_INPUT_CMP0_OR_CMP1_OUT: select CMP0 or CMP1 output as TIMER22 CI3
      \arg        TIMER31_CI0_INPUT_TIMER31_CH0: select TIMER31 CH0 as TIMER31 CI0
      \arg        TIMER31_CI0_INPUT_CMP0_OUT: select CMP0 output as TIMER31 CI0
      \arg        TIMER31_CI0_INPUT_CMP1_OUT: select CMP1 output as TIMER31 CI0
      \arg        TIMER31_CI0_INPUT_CMP0_OR_CMP1_OUT: select CMP0 or CMP1 output as TIMER31 CI0
      \arg        TIMER30_CI0_INPUT_TIMER30_CH0: select TIMER30 CH0 as TIMER30 CI0
      \arg        TIMER30_CI0_INPUT_CMP0_OUT: select CMP0 output as TIMER30 CI0
      \arg        TIMER30_CI0_INPUT_CMP1_OUT: select CMP1 output as TIMER30 CI0
      \arg        TIMER30_CI0_INPUT_CMP0_OR_CMP1_OUT  : select CMP0 or CMP1 output as TIMER30 CI0
      \arg        TIMER14_CI0_INPUT_TIMER14_CH0: select TIMER14 CH0 as TIMER14 CI0
      \arg        TIMER14_CI0_INPUT_TIMER1_CH0: select TIMER1 CH0 as TIMER14 CI0
      \arg        TIMER14_CI0_INPUT_TIMER2_CH0: select TIMER2 CH0 as TIMER14 CI0
      \arg        TIMER14_CI0_INPUT_TIMER3_CH0: select TIMER3 CH0 as TIMER14 CI0
      \arg        TIMER14_CI0_INPUT_LXTAL: select LXTAL as TIMER14 CI0
      \arg        TIMER14_CI0_INPUT_LPIRC4M: select LPIRC4M as TIMER14 CI0
      \arg        TIMER14_CI0_INPUT_CKOUT1: select CKOUT1 as TIMER14 CI0
      \arg        TIMER14_CI1_INPUT_TIMER14_CH1: select TIMER14 CH1 as TIMER14 CI1
      \arg        TIMER14_CI1_INPUT_TIMER1_CH1: select TIMER1 CH1 as TIMER14 CI1
      \arg        TIMER14_CI1_INPUT_TIMER2_CH1: select TIMER2 CH1 as TIMER14 CI1
      \arg        TIMER14_CI1_INPUT_TIMER3_CH1: select TIMER3 CH1 as TIMER14 CI1
      \arg        TIMER40_CI0_INPUT_TIMER40_CH0: select TIMER40 CH0 as TIMER40 CI0
      \arg        TIMER40_CI0_INPUT_TIMER2_CH0: select TIMER2 CH0 as TIMER40 CI0
      \arg        TIMER40_CI0_INPUT_TIMER3_CH0: select TIMER3 CH0 as TIMER40 CI0
      \arg        TIMER40_CI0_INPUT_TIMER4_CH0: select TIMER4 CH0 as TIMER40 CI0
      \arg        TIMER40_CI0_INPUT_LXTAL: select LXTAL as TIMER40 CI0
      \arg        TIMER40_CI0_INPUT_LPIRC4M: select LPIRC4M as TIMER40 CI0
      \arg        TIMER40_CI0_INPUT_CKOUT1: select CKOUT1 as TIMER40 CI0
      \arg        TIMER40_CI1_INPUT_TIMER40_CH1: select TIMER40 CH1 as TIMER40 CI1
      \arg        TIMER40_CI1_INPUT_TIMER2_CH1: select TIMER2 CH1 as TIMER40 CI1
      \arg        TIMER40_CI1_INPUT_TIMER3_CH1: select TIMER3 CH1 as TIMER40 CI1
      \arg        TIMER40_CI1_INPUT_TIMER4_CH1: select TIMER4 CH1 as TIMER40 CI1
      \arg        TIMER41_CI0_INPUT_TIMER41_CH0: select TIMER41 CH0 as TIMER41 CI0
      \arg        TIMER41_CI0_INPUT_TIMER3_CH0: select TIMER3 CH0 as TIMER41 CI0
      \arg        TIMER41_CI0_INPUT_TIMER4_CH0: select TIMER4 CH0 as TIMER41 CI0
      \arg        TIMER41_CI0_INPUT_TIMER22_CH0: select TIMER22 CH0 as TIMER41 CI0
      \arg        TIMER41_CI0_INPUT_LXTAL: select LXTAL as TIMER41 CI0
      \arg        TIMER41_CI0_INPUT_LPIRC4M: select LPIRC4M as TIMER41 CI0
      \arg        TIMER41_CI0_INPUT_CKOUT1: select CKOUT1 as TIMER41 CI0
      \arg        TIMER41_CI1_INPUT_TIMER41_CH1: select TIMER41 CH1 as TIMER41 CI1
      \arg        TIMER41_CI1_INPUT_TIMER3_CH1: select TIMER3 CH1 as TIMER41 CI1
      \arg        TIMER41_CI1_INPUT_TIMER4_CH1: select TIMER4 CH1 as TIMER41 CI1
      \arg        TIMER41_CI1_INPUT_TIMER22_CH1: select TIMER22 CH1 as TIMER41 CI1
      \arg        TIMER42_CI0_INPUT_TIMER42_CH0: select TIMER42 CH0 as TIMER42 CI0
      \arg        TIMER42_CI0_INPUT_TIMER4_CH0: select TIMER4 CH0 as TIMER42 CI0
      \arg        TIMER42_CI0_INPUT_TIMER22_CH0: select TIMER22 CH0 as TIMER42 CI0
      \arg        TIMER42_CI0_INPUT_TIMER23_CH0: select TIMER23 CH0 as TIMER42 CI0
      \arg        TIMER42_CI0_INPUT_LXTAL: select LXTAL as TIMER42 CI0
      \arg        TIMER42_CI0_INPUT_LPIRC4M: select LPIRC4M as TIMER42 CI0
      \arg        TIMER42_CI0_INPUT_CKOUT1: select CKOUT1 as TIMER42 CI0
      \arg        TIMER42_CI1_INPUT_TIMER42_CH1: select TIMER42 CH1 as TIMER42 CI1
      \arg        TIMER42_CI1_INPUT_TIMER4_CH1 : select TIMER4 CH1 as TIMER42 CI1
      \arg        TIMER42_CI1_INPUT_TIMER22_CH1: select TIMER22 CH1 as TIMER42 CI1
      \arg        TIMER42_CI1_INPUT_TIMER23_CH1: select TIMER23 CH1 as TIMER42 CI1
      \arg        TIMER15_CI0_INPUT_TIMER15_CH0: select TIMER15 CH0 as TIMER15 CI0
      \arg        TIMER15_CI0_INPUT_IRC32K: select IRC32K as TIMER15 CI0
      \arg        TIMER15_CI0_INPUT_LXTAL: select LXTAL as TIMER15 CI0
      \arg        TIMER15_CI0_INPUT_WKUP_IT: select WKUP IT as TIMER15 CI0
      \arg        TIMER16_CI0_INPUT_TIMER16_CH0: select TIMER16 CH0 as TIMER16 CI0
      \arg        TIMER16_CI0_INPUT_RSPDIF: select RSPDIF FS as TIMER16 CI0
      \arg        TIMER16_CI0_INPUT_HXTAL_RTCDIV: select HXTAL/RTCDIV 1M as TIMER16 CI0
      \arg        TIMER16_CI0_INPUT_CKOUT0: select CKOUT0 as TIMER16 CI0
      \arg        TIMER43_CI0_INPUT_TIMER43_CH0: select TIMER43 CH0 as TIMER43 CI0
      \arg        TIMER43_CI0_INPUT_TIMER22_CH0: select TIMER22 CH0 as TIMER43 CI0
      \arg        TIMER43_CI0_INPUT_TIMER23_CH0: select TIMER23 CH0 as TIMER43 CI0
      \arg        TIMER43_CI0_INPUT_TIMER30_CH0: select TIMER30 CH0 as TIMER43 CI0
      \arg        TIMER43_CI0_INPUT_LXTAL: select LXTAL as TIMER43 CI0
      \arg        TIMER43_CI0_INPUT_LPIRC4M: select LPIRC4M as TIMER43 CI0
      \arg        TIMER43_CI0_INPUT_CKOUT1: select CKOUT1 as TIMER43 CI0
      \arg        TIMER43_CI1_INPUT_TIMER43_CH1: select TIMER43 CH1 as TIMER43 CI1
      \arg        TIMER43_CI1_INPUT_TIMER22_CH1: select TIMER22 CH1 as TIMER43 CI1
      \arg        TIMER43_CI1_INPUT_TIMER23_CH1: select TIMER23 CH1 as TIMER43 CI1
      \arg        TIMER43_CI1_INPUT_TIMER30_CH1: select TIMER30 CH1 as TIMER43 CI1
      \arg        TIMER44_CI0_INPUT_TIMER44_CH0: select TIMER44 CH0 as TIMER44 CI0
      \arg        TIMER44_CI0_INPUT_TIMER23_CH0: select TIMER23 CH0 as TIMER44 CI0
      \arg        TIMER44_CI0_INPUT_TIMER30_CH0: select TIMER30 CH0 as TIMER44 CI0
      \arg        TIMER44_CI0_INPUT_TIMER31_CH0: select TIMER31 CH0 as TIMER44 CI0
      \arg        TIMER44_CI0_INPUT_LXTAL: select LXTAL as TIMER44 CI0
      \arg        TIMER44_CI0_INPUT_LPIRC4M: select LPIRC4M as TIMER44 CI0
      \arg        TIMER44_CI0_INPUT_CKOUT1: select CKOUT1 as TIMER44 CI0
      \arg        TIMER44_CI1_INPUT_TIMER44_CH1: select TIMER44 CH1 as TIMER44 CI1
      \arg        TIMER44_CI1_INPUT_TIMER23_CH1: select TIMER23 CH1 as TIMER44 CI1
      \arg        TIMER44_CI1_INPUT_TIMER30_CH1: select TIMER30 CH1 as TIMER44 CI1
      \arg        TIMER44_CI1_INPUT_TIMER31_CH1: select TIMER31 CH1 as TIMER44 CI1
    \param[out] none
    \retval     none
*/
void syscfg_timer_input_source_select(timer_channel_input_enum timer_input)
{
    uint32_t clear_timer_mask = ~((uint32_t)TIMER_IS_MASK << (TIMER_BIT_POS(timer_input)));
    uint32_t config_timer_mask = (TIMER_SEL_VAL(timer_input) << TIMER_BIT_POS(timer_input));

    switch(TIMER_REG_INDEX(timer_input)) {
    case TIMERCISEL0:
        /* clear Timer channel input select */
        SYSCFG_TIMERCISEL0 &= clear_timer_mask;
        /* config Timer channel input */
        SYSCFG_TIMERCISEL0 |= config_timer_mask;
        break;
    case TIMERCISEL1:
        /* clear Timer channel input select */
        SYSCFG_TIMERCISEL1 &= clear_timer_mask;
        /* config Timer channel input */
        SYSCFG_TIMERCISEL1 |= config_timer_mask;
        break;
    case TIMERCISEL3:
        /* clear Timer channel input select */
        SYSCFG_TIMERCISEL3 &= clear_timer_mask;
        /* config Timer channel input */
        SYSCFG_TIMERCISEL3 |= config_timer_mask;
        break;
    case TIMERCISEL4:
        /* clear Timer channel input select */
        SYSCFG_TIMERCISEL4 &= clear_timer_mask;
        /* config Timer channel input */
        SYSCFG_TIMERCISEL4 |= config_timer_mask;
        break;
    case TIMERCISEL5:
        /* clear Timer channel input select */
        SYSCFG_TIMERCISEL5 &= clear_timer_mask;
        /* config Timer channel input */
        SYSCFG_TIMERCISEL5 |= config_timer_mask;
        break;
    case TIMERCISEL6:
        /* clear Timer channel input select */
        SYSCFG_TIMERCISEL6 &= clear_timer_mask;
        /* config Timer channel input */
        SYSCFG_TIMERCISEL6 |= config_timer_mask;
        break;
    default:
        break;
    }
}

/*!
    \brief      select coder IO (API_ID(0x000AU))
    \param[in]  io_group: coder gpio group
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_CODER_GROUP0: coder IO group 0
      \arg        SYSCFG_CODER_GROUP1: coder IO group 1
    \param[in]  coder_io: coder gpio mode
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_CODER_IO_AFMT: connect to AFMT IO
      \arg        SYSCFG_CODER_IO_TFMT: connect to TFMT IO
      \arg        SYSCFG_CODER_IO_ENDAT: connect to Endat IO
      \arg        SYSCFG_CODER_IO_BISS_C: connect to BISS-C IO
      \arg        SYSCFG_CODER_IO_HDSL: connect to HDSL IO
      \arg        SYSCFG_CODER_IO_NOT_CONNECTED: not connected
    \param[out] none
    \retval     none
*/
void syscfg_coder_io_select(uint32_t io_group, uint32_t coder_io)
{
    if(SYSCFG_CODER_GROUP0 == io_group) {
        SYSCFG_PMCFG0 &= ~SYSCFG_PMCFG0_IO_SEL_G0;
        SYSCFG_PMCFG0 |= (uint32_t)(coder_io << io_group);
    } else {
        SYSCFG_PMCFG1 &= ~SYSCFG_PMCFG1_IO_SEL_G1;
        SYSCFG_PMCFG1 |= (uint32_t)(coder_io << io_group);
    }
}

/*!
    \brief      enable VOS configurability (API_ID(0x0029U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_vos_config_enable(void)
{
    SYSCFG_PMCFG1 |= SYSCFG_PMCFG1_VOSCFGEN;
}

/*!
    \brief      disable VOS configurability (API_ID(0x002AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_vos_config_disable(void)
{
    SYSCFG_PMCFG1 &= ~SYSCFG_PMCFG1_VOSCFGEN;
}

/*!
    \brief      enable standby flag output from PC13 (API_ID(0x0027U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_standby_flag_output_enable(void)
{
    SYSCFG_PMCFG1 |= SYSCFG_PMCFG1_STBOEN;
}

/*!
    \brief      disable standby flag output from PC13 (API_ID(0x0028U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_standby_flag_output_disable(void)
{
    SYSCFG_PMCFG1 &= ~SYSCFG_PMCFG1_STBOEN;
}

/*!
    \brief      enable CK_EXMC clock (API_ID(0x002BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_ck_exmc_enable(void)
{
    SYSCFG_PMCFG1 &= ~SYSCFG_PMCFG1_CK_EXMC_DIS;
}

/*!
    \brief      disable CK_EXMC clock (API_ID(0x002CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_ck_exmc_disable(void)
{
    SYSCFG_PMCFG1 |= SYSCFG_PMCFG1_CK_EXMC_DIS;
}

/*!
    \brief      configure bus timeout (API_ID(0x000BU))
    \param[in]  periph
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_BUSTO_SDIO0BUS: SDIO0 BUS Timeout
      \arg        SYSCFG_BUSTO_CPUBUS: CPU BUS timeout
      \arg        SYSCFG_BUSTO_TLIBUS: TLI BUS timeout
      \arg        SYSCFG_BUSTO_MDMABUS: MDMA BUS timeout
      \arg        SYSCFG_BUSTO_IPABUS: IPA BUS timeout
      \arg        SYSCFG_BUSTO_CPUAHBPBUS: CPU AHBP BUS timeout
      \arg        SYSCFG_BUSTO_DMA0MEMBUS: DMA0 mem BUS timeout
      \arg        SYSCFG_BUSTO_DMA0PERIPHBUS: DMA0 per BUS timeout
      \arg        SYSCFG_BUSTO_DMA1MEMBUS: DMA1 mem BUS timeout
      \arg        SYSCFG_BUSTO_DMA1PERIPHBUS: DMA1 per BUS timeout
      \arg        SYSCFG_BUSTO_ENET0BUS: ENET0 BUS timeout
      \arg        SYSCFG_BUSTO_ENET1BUS: ENET1 BUS timeout
      \arg        SYSCFG_BUSTO_SDIO1BUS: SDIO1 BUS timeout
      \arg        SYSCFG_BUSTO_USBHS0BUS: USBHS0 BUS timeout
      \arg        SYSCFG_BUSTO_USBHS1BUS: USBHS1 BUS timeout
      \arg        SYSCFG_BUSTO_FFTBUS: FFT BUS timeout
      \arg        SYSCFG_BUSTO_ESCBUS: ETHERCAT BUS timeout
    \param[in]  enable: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void syscfg_bus_timeout_config(uint32_t periph, ControlStatus enable)
{
    if(ENABLE == enable) {
        SYSCFG_BUSTO |= periph & SYSCFG_BUSTO_MASK;
    } else {
        SYSCFG_BUSTO &= (uint32_t)(~(periph & SYSCFG_BUSTO_MASK));
    }
}

/*!
    \brief      set Ethercat internal EEPROM address (API_ID(0x000CU))
    \param[in]  size
                only one parameter can be selected which is shown as below:
      \arg        ESC_INTERNAL_EEPROM_SIZE1: Select internal EEPROM size is 1k~15k bit
      \arg        ESC_INTERNAL_EEPROM_SIZE2: Select internal EEPROM size is 16k~4M bit
    \param[in]  address: SRAM or Non-volatile memory address
    \param[out] none
    \retval     none
*/
void syscfg_esc_internal_eeprom_set(uint32_t size, uint32_t address)
{
    SYSCFG_ESCCFG0 &= ~(SYSCFG_ESCCFG0_ESC_EEPROM | SYSCFG_ESCCFG0_EEPROMSZ);
    SYSCFG_ESCCFG0 |= SYSCFG_ESCCFG0_ESC_EEPROM | (size & SYSCFG_ESCCFG0_EEPROMSZ);

    SYSCFG_ESCCFG1 &= ~SYSCFG_ESCCFG1_ESC_SRAM;
    SYSCFG_ESCCFG1 |= address;
}

/*!
    \brief      select Ethercat external EEPROM (API_ID(0x000DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_esc_external_eeprom_sel(void)
{
    SYSCFG_ESCCFG0 &= ~SYSCFG_ESCCFG0_ESC_EEPROM;
}

/*!
    \brief      enable Ethercat mii txshift pin strap (API_ID(0x000EU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_esc_mii_txshift_pin_enable(void)
{
    SYSCFG_ESCCFG0 &= ~(SYSCFG_ESCCFG0_SHIFTSTEN);
    SYSCFG_ESCCFG0 |= SYSCFG_ESCCFG0_SHIFTSTEN;
}

/*!
    \brief      disable Ethercat mii txshift pin strap (API_ID(0x000FU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_esc_mii_txshift_pin_disable(void)
{
    SYSCFG_ESCCFG0 &= ~(SYSCFG_ESCCFG0_SHIFTSTEN);
}

/*!
    \brief      set Ethercat rmii0 mode tx_shift and rmii_shift (API_ID(0x0010U))
    \param[in]  txshift0
                only one parameter can be selected which is shown as below:
      \arg        ESC_RMII0_TXSHIFT0_0NS: rmii0 txshift value is 0ns
      \arg        ESC_RMII0_TXSHIFT0_10NS: rmii0 txshift value is 10ns
      \arg        ESC_RMII0_TXSHIFT0_20NS: rmii0 txshift value is 20ns
      \arg        ESC_RMII0_TXSHIFT0_30NS: rmii0 txshift value is 30ns
    \param[in]  rmii0_shift0
                only one parameter can be selected which is shown as below:
      \arg        ESC_RMII0_SHIFT0_0: rmii0 phase compensation value is 0ns
      \arg        ESC_RMII0_SHIFT0_1: rmii0 phase compensation value is 2.5ns
      \arg        ESC_RMII0_SHIFT0_2: rmii0 phase compensation value is 5ns
      \arg        ESC_RMII0_SHIFT0_3: rmii0 phase compensation value is 7.5ns
      \arg        ESC_RMII0_SHIFT0_4: rmii0 phase compensation value is 10ns
      \arg        ESC_RMII0_SHIFT0_5: rmii0 phase compensation value is 12.5ns
      \arg        ESC_RMII0_SHIFT0_6: rmii0 phase compensation value is 15ns
      \arg        ESC_RMII0_SHIFT0_7: rmii0 phase compensation value is 17.5ns
    \param[out] none
    \retval     none
*/
void syscfg_esc_rmii0_mode_shift_set(uint32_t txshift0, uint32_t rmii0_shift0)
{
    SYSCFG_ESCCFG0 &= ~(SYSCFG_ESCCFG0_RMIITX_S0_VAL | SYSCFG_ESCCFG0_RMII_S0);
    SYSCFG_ESCCFG0 |= (txshift0 & SYSCFG_ESCCFG0_RMIITX_S0_VAL) | (rmii0_shift0 & SYSCFG_ESCCFG0_RMII_S0);
}

/*!
    \brief      set Ethercat rmii1 mode tx_shift and rmii_shift (API_ID(0x0011U))
    \param[in]  txshift1
                only one parameter can be selected which is shown as below:
      \arg        ESC_RMII1_TXSHIFT1_0NS: rmii1 txshift value is 0ns
      \arg        ESC_RMII1_TXSHIFT1_10NS: rmii1 txshift value is 10ns
      \arg        ESC_RMII1_TXSHIFT1_20NS: rmii1 txshift value is 20ns
      \arg        ESC_RMII1_TXSHIFT1_30NS: rmii1 txshift value is 30ns
    \param[in]  rmii1_shift1
                only one parameter can be selected which is shown as below:
      \arg        ESC_RMII1_SHIFT1_0: rmii1 phase compensation value is 0ns
      \arg        ESC_RMII1_SHIFT1_1: rmii1 phase compensation value is 2.5ns
      \arg        ESC_RMII1_SHIFT1_2: rmii1 phase compensation value is 5ns
      \arg        ESC_RMII1_SHIFT1_3: rmii1 phase compensation value is 7.5ns
      \arg        ESC_RMII1_SHIFT1_4: rmii1 phase compensation value is 10ns
      \arg        ESC_RMII1_SHIFT1_5: rmii1 phase compensation value is 12.5ns
      \arg        ESC_RMII1_SHIFT1_6: rmii1 phase compensation value is 15ns
      \arg        ESC_RMII1_SHIFT1_7: rmii1 phase compensation value is 17.5ns
    \param[out] none
    \retval     none
*/
void syscfg_esc_rmii1_mode_shift_set(uint32_t txshift1, uint32_t rmii1_shift1)
{
    SYSCFG_ESCCFG0 &= ~(SYSCFG_ESCCFG0_RMIITX_S1_VAL | SYSCFG_ESCCFG0_RMII_S1);
    SYSCFG_ESCCFG0 |= (txshift1 & SYSCFG_ESCCFG0_RMIITX_S1_VAL) | (rmii1_shift1 & SYSCFG_ESCCFG0_RMII_S1);
}

/*!
    \brief      select Ethercat linkactled output polarity (API_ID(0x0012U))
    \param[in]  linkactled0
                only one parameter can be selected which is shown as below:
      \arg        ESC_LINKACTLED0_POL_LOW: EtherCat linkactled0 output 0
      \arg        ESC_LINKACTLED0_POL_HIGH: EtherCat linkactled0 output 1
    \param[in]  linkactled1
                only one parameter can be selected which is shown as below:
      \arg        ESC_LINKACTLED1_POL_LOW: EtherCat linkactled1 output 0
      \arg        ESC_LINKACTLED1_POL_HIGH: EtherCat linkactled1 output 1
    \param[in]  linkactled2
                only one parameter can be selected which is shown as below:
      \arg        ESC_LINKACTLED2_POL_LOW: EtherCat linkactled2 output 0
      \arg        ESC_LINKACTLED2_POL_HIGH: EtherCat linkactled2 output 1
    \param[out] none
    \retval     none
*/
void syscfg_esc_linkactled_pol_sel(uint32_t linkactled0, uint32_t linkactled1, uint32_t linkactled2)
{
    SYSCFG_ESCCFG0 &= ~(SYSCFG_ESCCFG0_LINKACTLED0_POLSEL | SYSCFG_ESCCFG0_LINKACTLED1_POLSEL | SYSCFG_ESCCFG0_LINKACTLED2_POLSEL);
    SYSCFG_ESCCFG0 |= (linkactled0 | linkactled1 | linkactled2) & SYSCFG_LINKACT_POLSEL_MASK;
}

/*!
    \brief      select Ethercat lederr output polarity (API_ID(0x0013U))
    \param[in]  lederr
                only one parameter can be selected which is shown as below:
      \arg        ESC_LEDERR_POL_LOW: EtherCat lederr output 0
      \arg        ESC_LEDERR_POL_HIGH: EtherCat lederr output 1
    \param[out] none
    \retval     none
*/
void syscfg_esc_lederr_pol_sel(uint32_t lederr)
{
    SYSCFG_ESCCFG0 &= ~(SYSCFG_ESCCFG0_LEDERR_POLSEL);
    SYSCFG_ESCCFG0 |= lederr & SYSCFG_ESCCFG0_LEDERR_POLSEL;
}

/*!
    \brief      select Ethercat ledrun output polarity (API_ID(0x0014U))
    \param[in]  ledrun
                only one parameter can be selected which is shown as below:
      \arg        ESC_LEDRUN_POL_LOW: EtherCat ledrun output 0
      \arg        ESC_LEDRUN_POL_HIGH: EtherCat ledrun output 1
    \param[out] none
    \retval     none
*/
void syscfg_esc_ledrun_pol_sel(uint32_t ledrun)
{
    SYSCFG_ESCCFG0 &= ~(SYSCFG_ESCCFG0_LEDRUN_POLSEL);
    SYSCFG_ESCCFG0 |= ledrun & SYSCFG_ESCCFG0_LEDRUN_POLSEL;
}

/*!
    \brief      set Ethercat reset_out output polarity and count of clock cycles (API_ID(0x0015U))
    \param[in]  rstout_pol
                only one parameter can be selected which is shown as below:
      \arg        ESC_RSTOUT_POL_HIGH: EtherCat reset_out output 1
      \arg        ESC_RSTOUT_POL_LOW: EtherCat reset_out output 0
    \param[in]  rstout_cnt: 0~0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void syscfg_esc_resetout_set(uint32_t rstout_pol, uint32_t rstout_cnt)
{
    SYSCFG_ESCCFG0 &= ~(SYSCFG_ESCCFG0_RSTOUT_POLSEL);
    SYSCFG_ESCCFG0 |= rstout_pol & SYSCFG_ESCCFG0_RSTOUT_POLSEL;

    SYSCFG_ESCCFG2 = rstout_cnt;
}

/*!
    \brief      select Ethercat linkactled output polarity (API_ID(0x0016U))
    \param[in]  link0
                only one parameter can be selected which is shown as below:
      \arg        ESC_LINK0_POL_HIGH: EtherCat LINK0 output 1
      \arg        ESC_LINK0_POL_LOW: EtherCat LINK0 output 0
    \param[in]  link1
                only one parameter can be selected which is shown as below:
      \arg        ESC_LINK1_POL_HIGH: EtherCat LINK1 output 1
      \arg        ESC_LINK1_POL_LOW: EtherCat LINK1 output 0
    \param[in]  link2
                only one parameter can be selected which is shown as below:
      \arg        ESC_LINK2_POL_HIGH: EtherCat LINK2 output 1
      \arg        ESC_LINK2_POL_LOW: EtherCat LINK2 output 0
    \param[out] none
    \retval     none
*/
void syscfg_esc_link_pol_sel(uint32_t link0, uint32_t link1, uint32_t link2)
{
    SYSCFG_ESCCFG0 &= ~(SYSCFG_ESCCFG0_NLINK0_POLSEL | SYSCFG_ESCCFG0_NLINK1_POLSEL | SYSCFG_ESCCFG0_NLINK2_POLSEL);
    SYSCFG_ESCCFG0 |= (link0 | link1 | link2) & SYSCFG_NLINK_POLSEL_MASK;
}

/*!
    \brief      select Ethercat mii or rmii (API_ID(0x0017U))
    \param[in]  mii_rmii_sel
                only one parameter can be selected which is shown as below:
      \arg        ESC_MII: ESC MII
      \arg        ESC_RMII: ESC RMII
    \param[out] none
    \retval     none
*/
void syscfg_esc_mii_rmii_sel(uint32_t mii_rmii_sel)
{
    SYSCFG_ESCCFG0 &= ~(SYSCFG_ESCCFG0_RMIIEN);
    SYSCFG_ESCCFG0 |= mii_rmii_sel & SYSCFG_ESCCFG0_RMIIEN;
}

/*!
    \brief      configure Ethercat SMPS_DRIVE's drive capability (API_ID(0x0018U))
    \param[in]  drive_cap: drive capability
                only one parameter can be selected which is shown as below:
      \arg        ESC_SMPS_DRIVE_CAP_NORMAL: Drive capability is normal
      \arg        ESC_SMPS_DRIVE_CAP_REDUCED: Drive capability is reduced
    \param[out] none
    \retval     none
*/
void syscfg_esc_smps_drive_config(uint32_t drive_cap)
{
    SYSCFG_ESCCFG0 &= ~(SYSCFG_ESCCFG0_SMPS_DRIVE);
    SYSCFG_ESCCFG0 |= drive_cap & SYSCFG_ESCCFG0_SMPS_DRIVE;
}

/*!
    \brief      set Ethercat port0 phy address offset (API_ID(0x0019U))
    \param[in]  phyadd_offset_sel
                only one parameter can be selected which is shown as below:
      \arg        ESC_PHY_ADDRESS_OFFSET_0: port0 phy address offset is 0
      \arg        ESC_PHY_ADDRESS_OFFSET_16: port0 phy address offset is 16
    \param[in]  offset_value: 0~31
    \param[out] none
    \retval     none
*/
void syscfg_esc_phyaddress_offset_set(uint32_t phyadd_offset_sel, uint32_t offset_value)
{
    SYSCFG_ESCCFG0 &= ~(SYSCFG_ESCCFG0_PHY_OFFSETSEL | SYSCFG_ESCCFG0_PHY_OFFSET);
    SYSCFG_ESCCFG0 |= (phyadd_offset_sel & SYSCFG_ESCCFG0_PHY_OFFSETSEL) | PHY_ADDRESS_OFFSET(offset_value & SYSCFG_PHY_OFFSET_MASK);
}

/*!
    \brief    configure the I/O compensation cell (API_ID(0x001AU))
    \param[in]  syscfg_cps: specifies the I/O compensation cell mode
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_IO_COMPENSATION_ENABLE: I/O compensation cell is enabled
      \arg        SYSCFG_IO_COMPENSATION_DISABLE: I/O compensation cell is disabled
    \param[out] none
    \retval     none
*/
void syscfg_io_compensation_config(uint32_t syscfg_cps)
{
    uint32_t reg;

    reg = SYSCFG_CPSCTL;
    /* reset the SYSCFG_CPSCTL_CPS_EN bit and set according to syscfg_compensation */
    reg &= ~SYSCFG_CPSCTL_CPS_EN;
    SYSCFG_CPSCTL = (reg | (syscfg_cps & SYSCFG_CPSCTL_CPS_EN));
}

/*!
    \brief      get bus timeout flag status (API_ID(0x001BU))
    \param[in]  flag: Bus Timeout flags
                only one parameter can be selected which is shown as below:
      \arg        SYSCFG_BUSTOSTAT_SDIO0BUSTOF: SDIO0 BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_CPUBUSTOF: CPU BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_TLIBUSTOF: TLI BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_MDMABUSTOF: MDMA BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_IPABUSTOF: IPA BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_CPUAHBPBUSTOF: CPU AHBP BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_DMA0MEMBUSTOF: DMA0 mem BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_DMA0PERIPHBUSTOF: DMA0 per BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_DMA1MEMBUSTOF: DMA1 mem BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_DMA1PERIPHBUSTOF: DMA1 per BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_ENET0BUSTOF: ENET0 BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_ENET1BUSTOF: ENET1 BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_SDIO1BUSTOF: SDIO1 BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_USBHS0BUSTOF: USBHS0 BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_USBHS1BUSTOF: USBHS1 BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_FFTBUSTOF: FFT BUS Timeout flag
      \arg        SYSCFG_BUSTOSTAT_ESCBUSTOF: ETHERCAT BUS Timeout flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_bus_timeout_flag_get(uint32_t flag)
{
    FlagStatus retval = RESET;
    if(RESET != (SYSCFG_BUSTOSTAT & flag)) {
        retval = SET;
    } else {
        /* do nothing */
    }
    return retval;
}

/*!
    \brief      enable I/O speed optimization, high-speed at low-voltage (API_ID(0x001CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_io_low_voltage_speed_optimization_enable(void)
{
    SYSCFG_CPSCTL |= SYSCFG_CPSCTL_IOSPDOP;
}

/*!
    \brief      disable I/O speed optimization, high-speed at low-voltage (API_ID(0x001DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_io_low_voltage_speed_optimization_disable(void)
{
    SYSCFG_CPSCTL &= ~SYSCFG_CPSCTL_IOSPDOP;
}

/*!
    \brief      set P/N MOS compensation value (API_ID(0x001EU))
    \param[in]  mos
                only one parameter can be selected which is shown as below:
      \arg        NMOS_COMPENSATION: NMOS
      \arg        PMOS_COMPENSATION: PMOS
    \param[in]  code: P/N MOS compensation value
    \param[out] none
    \retval     none
*/
void syscfg_pnmos_compensation_code_set(uint32_t mos, uint32_t code)
{
    uint32_t value;
    value = SYSCFG_CPSCCCFG;
    if(NMOS_COMPENSATION == mos) {
        /* configure NMOS compensation */
        value &= ~SYSCFG_CPSCCCFG_NCPSCC;
        value |= (code & SYSCFG_MOS_COMPENSATION_MASK);
    } else {
        /* configure PMOS compensation */
        value &= ~SYSCFG_CPSCCCFG_PCPSCC;
        value |= ((code & SYSCFG_MOS_COMPENSATION_MASK) << 4U);
    }
    SYSCFG_CPSCCCFG = value;
}

/*!
    \brief      set secure SRAM size (API_ID(0x001FU))
    \param[in]  size: SRAM size
                only one parameter can be selected which is shown as below:
      \arg        SECURE_SRAM_SIZE_0KB: secure SRAM size is 0KB
      \arg        SECURE_SRAM_SIZE_32KB: secure SRAM size is 32KB
      \arg        SECURE_SRAM_SIZE_64KB: secure SRAM size is 64KB
      \arg        SECURE_SRAM_SIZE_128KB: secure SRAM size is 128KB
    \param[out] none
    \retval     none
*/
void syscfg_secure_sram_size_set(uint32_t size)
{
    SYSCFG_SRAMCFG0 &= (uint32_t)(~SYSCFG_SRAMCFG0_SECURE_SRAM_SIZE);
    SYSCFG_SRAMCFG0 |= size & SYSCFG_SRAMCFG0_SECURE_SRAM_SIZE;
}

/*!
    \brief      get secure SRAM size (API_ID(0x0020U))
    \param[in]  none
    \param[out] none
    \retval     SRAM size
      \arg        SECURE_SRAM_SIZE_0KB: secure SRAM size is 0KB
      \arg        SECURE_SRAM_SIZE_32KB: secure SRAM size is 32KB
      \arg        SECURE_SRAM_SIZE_64KB: secure SRAM size is 64KB
      \arg        SECURE_SRAM_SIZE_128KB: secure SRAM size is 128KB
*/
uint32_t syscfg_secure_sram_size_get(void)
{
    return (SYSCFG_SRAMCFG0 & SYSCFG_SRAMCFG0_SECURE_SRAM_SIZE);
}

/*!
    \brief      get BOOT mode (API_ID(0x0021U))
    \param[in]  none
    \param[out] none
    \retval     boot mode
      \arg        BOOT_SRAM: BOOT from SRAM (ITCM/DTCM/RAM shared/AXI SRAM)
      \arg        BOOT_SECURITY: BOOT from Security
      \arg        BOOT_SYSTEM: BOOT_SYS (BootLoader)
      \arg        BOOT_USER: BOOT_USER (NVMC / OSPI0/1)
*/
uint32_t syscfg_bootmode_get(void)
{
    return ((SYSCFG_USERCFG & SYSCFG_USERCFG_BOOT_MODE) >> 4U);
}

/*!
    \brief      enable SYSCFG interrupt (API_ID(0x0022U))
    \param[in]  interrupt
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_INT_INEXACT: inexact interrupt
      \arg        SYSCFG_INT_INPUT_ABNORMAL: input abnormal interrupt
      \arg        SYSCFG_INT_OVERFLOW: overflow interrupt
      \arg        SYSCFG_INT_UNDERFLOW: underflow interrupt
      \arg        SYSCFG_INT_DIV0: divide-by-zero interrupt
      \arg        SYSCFG_INT_INVALID_OPERATION: invalid operation interrupt
      \arg        SYSCFG_INT_CPU_DCDET: CPU DCACHE error bank information interrupt
      \arg        SYSCFG_INT_CPU_ICDET: CPU ICACHE error detection information interrupt
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_enable(uint32_t interrupt)
{
    SYSCFG_CFPUINTEN |= interrupt;
}

/*!
    \brief      disable SYSCFG interrupt (API_ID(0x0023U))
    \param[in]  interrupt
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_INT_INEXACT: inexact interrupt
      \arg        SYSCFG_INT_INPUT_ABNORMAL: input abnormal interrupt
      \arg        SYSCFG_INT_OVERFLOW: overflow interrupt
      \arg        SYSCFG_INT_UNDERFLOW: underflow interrupt
      \arg        SYSCFG_INT_DIV0: divide-by-zero interrupt
      \arg        SYSCFG_INT_INVALID_OPERATION: invalid operation interrupt
      \arg        SYSCFG_INT_CPU_DCDET: CPU DCACHE error bank information interrupt
      \arg        SYSCFG_INT_CPU_ICDET: CPU ICACHE error detection information interrupt
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_disable(uint32_t interrupt)
{
    SYSCFG_CFPUINTEN &= (uint32_t)(~interrupt);
}

/*!
    \brief      get compensation cell flags (API_ID(0x0024U))
    \param[in]  cps_flag: compensation flag
      \arg        SYSCFG_FLAG_IO_LOW_VOLTAGE: I/O in low voltage state flag, product supply voltage is working below 2.5V
      \arg        SYSCFG_FLAG_COMPENSATION_READY: I/O compensation cell ready flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_compensation_flag_get(uint32_t cps_flag)
{
    FlagStatus retval = RESET;
    if(SYSCFG_CPSCTL & cps_flag) {
        retval = SET;
    } else {
        /* do nothing */
    }
    return retval;
}

/*!
    \brief      get the ICACHE or DCACHE detection and error information (API_ID(0x0025U))
    \param[in]  cache:
                only one parameter can be selected which is shown as below:
      \arg        ICACHE_STATUS: select ICACHE
      \arg        DCACHE_STATUS: select DCACHE
    \param[in]  status:
                only one parameter can be selected which is shown as below:
      \arg        CPU_CACHE_ERROR_DETECTION: select detection information
      \arg        CPU_CACHE_ERROR_BANK: select error information
    \param[out] none
    \retval     value
*/
uint32_t syscfg_cpu_cache_status_get(uint32_t cache, uint32_t status)
{
    uint32_t value = 0U;
    switch(cache) {
    /* get ICACHE information */
    case ICACHE_STATUS:
        if(CPU_CACHE_ERROR_DETECTION == status) {
            /* return detection information */
            value = (uint32_t)((SYSCFG_CPUICAC & SYSCFG_CPUICAC_CPU_ICDET) >> 28U);
        } else {
            /* return error bank information */
            value = (uint32_t)((SYSCFG_CPUICAC & SYSCFG_CPUICAC_CPU_ICERR) >> 6U);
        }
        break;
    /* get DCACHE information */
    case DCACHE_STATUS:
        if(CPU_CACHE_ERROR_DETECTION == status) {
            /* return detection information */
            value = (uint32_t)((SYSCFG_CPUDCAC & SYSCFG_CPUDCAC_CPU_DCDET) >> 28U);
        } else {
            /* return error bank information */
            value = (uint32_t)((SYSCFG_CPUDCAC & SYSCFG_CPUDCAC_CPU_DCERR) >> 6U);
        }
        break;
    default:
        break;
    }
    return value;
}

/*!
    \brief      get brownout reset threshold level (API_ID(0x0026U))
    \param[in]  none
    \param[out] none
    \retval     BOR level
      \arg        BOR_OFF: no BOR function
      \arg        BOR_THRESHOLD_VAL1: BOR threshold value 1
      \arg        BOR_THRESHOLD_VAL2: BOR threshold value 2
      \arg        BOR_THRESHOLD_VAL3: BOR threshold value 3
*/
uint32_t syscfg_brownout_reset_threshold_level_get(void)
{
    return (SYSCFG_USERCFG & SYSCFG_USERCFG_BOR_TH);
}
