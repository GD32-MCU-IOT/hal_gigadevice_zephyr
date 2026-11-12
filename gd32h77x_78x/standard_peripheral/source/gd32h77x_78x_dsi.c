/*!
    \file    gd32h77x_78x_dsi.c
    \brief   DSI driver

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

#include "gd32h77x_78x_dsi.h"
#include <stdlib.h>

/*!
    \brief      deinitialize DSI registers (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dsi_deinit(void)
{
    rcu_periph_reset_enable(RCU_DSIRST);
    rcu_periph_reset_disable(RCU_DSIRST);
}

/*!
    \brief      initialize the DSI_Init structure with the default values (API_ID(0x0002U))
    \param[in]  none
    \param[out] dsi_init_struct: DSI Init parameter struct
    \retval     none
*/
void dsi_init_struct_para_init(dsi_init_parameter_struct *dsi_init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check for null pointer */
    if(NULL == dsi_init_struct) {
        fw_debug_report_err(DSI_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the struct parameters with default values */
        dsi_init_struct->lane_count = DSI_DATA_LANE_ONE;
        dsi_init_struct->mode_type = DSI_VIDEO_MODE;
        dsi_init_struct->video_mode_format = DSI_VIDEO_MODE_FORMAT_NONE;
        dsi_init_struct->color_format = DSI_VIDEO_MODE_FMT_RGB888;
        dsi_init_struct->data_width = DSI_CMD_MODE_DTW_8BIT;
        dsi_init_struct->cmd_size = 0U;
        dsi_init_struct->virtual_channel = DSI_VIRTUAL_CHANNEL_0;
        dsi_init_struct->polarity = DSI_VSYNC_POLARITY;
    }
}

/*!
    \brief      initialize the DSI host according to the specified parameters in the dsi_init_struct (API_ID(0x0003U))
    \param[in]  dsi_init_struct: DSI Init parameter struct
                  lane_count: number of active data lanes, possible values are:
                    DSI_DATA_LANE_ONE: one data lane
                    DSI_DATA_LANE_TWO: two data lanes
                  mode_type: video mode or command mode, possible values are:
                    DSI_VIDEO_MODE: video mode
                    DSI_COMMAND_MODE: command mode
                  video_mode_format: video mode format for video mode, possible values are:
                    DSI_VIDEO_MODE_FORMAT_NONE: none video mode format
                    DSI_NON_BURST_MODE_SYNC_PULSE: non burst mode with sync pulse
                    DSI_NON_BURST_MODE_SYNC_EVENTS: non burst mode with sync events
                    DSI_BURST_MODE: burst mode
                  color_format: color format for video mode, possible values are:
                    DSI_VIDEO_MODE_FMT_RGB565: RGB565 or 16-bit format
                    DSI_VIDEO_MODE_FMT_RGB666: RGB666 or 18-bit format
                    DSI_VIDEO_MODE_FMT_RGB666LP: RGB666 loosely packed format
                    DSI_VIDEO_MODE_FMT_RGB888: RGB888 or 24-bit format
                  data_width: data width for command mode
                    DSI_CMD_MODE_DTW_8BIT: 8-bit data width
                    DSI_CMD_MODE_DTW_16BIT: 16-bit data width
                    DSI_CMD_MODE_DTW_24BIT: 24-bit data width
                  cmd_size: DSI command size (used only in command mode)
                  virtual_channel: virtual channel ID, possible values are:
                    DSI_VIRTUAL_CHANNEL_0: virtual channel 0
                    DSI_VIRTUAL_CHANNEL_1: virtual channel 1
                    DSI_VIRTUAL_CHANNEL_2: virtual channel 2
                    DSI_VIRTUAL_CHANNEL_3: virtual channel 3
                  polarity: polarity configuration, possible values are:
                    DSI_VSYNC_POLARITY: vsync
                    DSI_HSYNC_POLARITY: hsync
                    DSI_SHUTDOWN_POLARITY: shutdown
                    DSI_COLOR_MODE_POLARITY: color mode
    \param[out] none
    \retval     none
*/
void dsi_init(dsi_init_parameter_struct *dsi_init_struct)
{
    uint32_t reg_val;

#ifdef FW_DEBUG_ERR_REPORT
    /* check for null pointer */
    if(NULL == dsi_init_struct) {
        fw_debug_report_err(DSI_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure FUNCPRG register: set data lanes, virtual channel and color format based on mode type */
        reg_val = DSI_FUNCPRG;
        reg_val &= ~(DSI_FUNCPRG_DTLANE_PRG | DSI_FUNCPRG_VCHNUMCM | DSI_FUNCPRG_SFMTVM | DSI_FUNCPRG_SDTWCM);
        reg_val |= dsi_init_struct->lane_count;

        if(DSI_COMMAND_MODE == dsi_init_struct->mode_type) {
            /* For command mode:
               - clear VCHNUMCM and set virtual channel in VCHNUMCM
               - clear SFMTVM (set to 0 for command mode)
               - set supported data width in command mode */
            reg_val |= (((dsi_init_struct->virtual_channel & 0x3U) << 5) | dsi_init_struct->data_width); /* VCHNUMCM is at bits 5-6 */
            /* clear video mode format */
            DSI_VMFMT &= ~DSI_VMFMT_VMFMT;
        } else {
            /* For video mode:
               - clear VCHNUMVM and set virtual channel in VCHNUMVM
               - clear SFMTVM and set color format in SFMTVM */
            reg_val |= ((dsi_init_struct->virtual_channel & 0x3U) << 3 | dsi_init_struct->color_format);
            /* set video mode format */
            DSI_VMFMT = dsi_init_struct->video_mode_format;
        }

        DSI_FUNCPRG = reg_val;

        /* set polarity configuration */
        reg_val = DSI_PLCTL;
        reg_val &= ~DSI_PLCTL_PL;
        reg_val |= dsi_init_struct->polarity;
        DSI_PLCTL = reg_val;

        /* set command size */
        if(DSI_COMMAND_MODE == dsi_init_struct->mode_type) {
            DSI_DCSWC = dsi_init_struct->cmd_size;
        }
    }
}

/*!
    \brief      set the DSI host device ready state (API_ID(0x0004U))
    \param[in]  ready_state
                only one parameter can be selected which is shown as below:
      \arg        DSI_DEVICE_NOT_READY: not ready
      \arg        DSI_DEVICE_READY: ready
    \param[out] none
    \retval     none
*/
void dsi_device_ready_set(uint32_t ready_state)
{
    uint32_t reg_val;

    reg_val = DSI_DEVRDY;
    reg_val &= ~DSI_DEVRDY_DEVRDY;
    reg_val |= ready_state & DSI_DEVRDY_DEVRDY;
    DSI_DEVRDY = reg_val;
}

/*!
    \brief      set the ULPS state (API_ID(0x0005U))
    \param[in]  ulps_mode
                only one parameter can be selected which is shown as below:
      \arg        DSI_ULPS_NORMAL_OPERATION: normal operation
      \arg        DSI_ULPS_EXIT_MODE: ultra low power EXIT mode
      \arg        DSI_ULPS_POWER_SAVING_MODE: ultra low power [POWER SAVING] mode
    \param[out] none
    \retval     none
*/
void dsi_ulps_mode_set(uint32_t ulps_mode)
{
    uint32_t reg_val;

    reg_val = DSI_DEVRDY;
    reg_val &= ~DSI_DEVRDY_ULPS_STATE;
    reg_val |= ulps_mode & DSI_DEVRDY_ULPS_STATE;
    DSI_DEVRDY = reg_val;
}

/*!
    \brief      control display bus possession, (API_ID(0x0006U))
    \param[in]  bus_pos
                only one parameter can be selected which is shown as below:
      \arg        DSI_BUS_POSSESSION_STOP: stop the display bus possession of the DSI receive
      \arg        DSI_BUS_POSSESSION_RECEIVE: inform that DSI receiver has to be given bus possession for receiving the tearing effect trigger message
    \param[out] none
    \retval     none
*/
void dsi_display_bus_possession_set(uint32_t bus_pos)
{
    uint32_t reg_val;

    reg_val = DSI_DEVRDY;
    reg_val &= ~DSI_DEVRDY_BUS_POSS;
    reg_val |= bus_pos & DSI_DEVRDY_BUS_POSS;
    DSI_DEVRDY = reg_val;
}

/*!
    \brief      configure the DSI low power byte clock (API_ID(0x0007U))
    \param[in]  byte_clk: LP clock equivalence in terms of byte clock (0-65535)
    \param[out] none
    \retval     none
*/
void dsi_lp_byte_clk_config(uint16_t byte_clk)
{
    DSI_LPBCLKCFG = (uint32_t)(byte_clk & DSI_LPBCLKCFG_LPBYTECLK);
}

/*!
    \brief      initialize DSI horizontal and vertical count structure with the default values (API_ID(0x0008U))
    \param[in]  none
    \param[out] hv_count: DSI horizontal and vertical count struct
    \retval     none
*/
void dsi_hv_count_struct_para_init(dsi_hv_count_struct *hv_count)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check for null pointer */
    if(NULL == hv_count) {
        fw_debug_report_err(DSI_MODULE_ID, API_ID(0x0008U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the horizontal and vertical count parameters with default values */
        hv_count->hsa_count = 0U;
        hv_count->hbp_count = 0U;
        hv_count->hfp_count = 0U;
        hv_count->hac_count = 0U;
        hv_count->vsa_count = 0U;
        hv_count->vbp_count = 0U;
        hv_count->vfp_count = 0U;
    }
}

/*!
    \brief      configure the DSI for video mode with complete timing parameters (API_ID(0x0009U))
    \param[in]  hv_count: DSI horizontal and vertical count struct
                  hsa_count: horizontal sync active count
                  hbp_count: horizontal back porch count
                  hfp_count: horizontal front porch count
                  hac_count: horizontal active count
                  vsa_count: vertical sync active count
                  vbp_count: vertical back porch count
                  vfp_count: vertical front porch count
    \param[out] none
    \retval     none
*/
void dsi_hv_count_config(dsi_hv_count_struct *hv_count)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check for null pointer */
    if(NULL == hv_count) {
        fw_debug_report_err(DSI_MODULE_ID, API_ID(0x0009U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure horizontal timing parameters */
        DSI_HSACFG = (uint32_t)(hv_count->hsa_count & DSI_HSACFG_HSACNT);
        DSI_HBPCFG = (uint32_t)(hv_count->hbp_count & DSI_HBPCFG_HBPCNT);
        DSI_HFPCFG = (uint32_t)(hv_count->hfp_count & DSI_HFPCFG_HFPCNT);
        DSI_HACFG = (uint32_t)(hv_count->hac_count & DSI_HACFG_HACNT);

        /* configure vertical timing parameters */
        DSI_VSACFG = (uint32_t)(hv_count->vsa_count & DSI_VSACFG_VSACNT);
        DSI_VBPCFG = (uint32_t)(hv_count->vbp_count & DSI_VBPCFG_VBPCNT);
        DSI_VFPCFG = (uint32_t)(hv_count->vfp_count & DSI_VFPCFG_VFPCNT);
    }
}

/*!
    \brief      configure horizontal sync active count (API_ID(0x000AU))
    \param[in]  count: horizontal sync active count value
    \param[out] none
    \retval     none
*/
void dsi_horizontal_sync_active_count_set(uint16_t count)
{
    DSI_HSACFG = (uint32_t)(count & DSI_HSACFG_HSACNT);
}

/*!
    \brief      configure horizontal back porch count (API_ID(0x000BU))
    \param[in]  count: horizontal back porch count value
    \param[out] none
    \retval     none
*/
void dsi_horizontal_back_porch_count_set(uint16_t count)
{
    DSI_HBPCFG = (uint32_t)(count & DSI_HBPCFG_HBPCNT);
}

/*!
    \brief      configure horizontal front porch count (API_ID(0x000CU))
    \param[in]  count: horizontal front porch count value
    \param[out] none
    \retval     none
*/
void dsi_horizontal_front_porch_count_set(uint16_t count)
{
    DSI_HFPCFG = (uint32_t)(count & DSI_HFPCFG_HFPCNT);
}

/*!
    \brief      configure horizontal active area count (API_ID(0x000DU))
    \param[in]  count: horizontal active area count value (time for active horizontal address)
    \param[out] none
    \retval     none
*/
void dsi_horizontal_active_count_set(uint16_t count)
{
    DSI_HACFG = (uint32_t)(count & DSI_HACFG_HACNT);
}

/*!
    \brief      configure vertical sync active count (API_ID(0x000EU))
    \param[in]  count: vertical sync active count value
    \param[out] none
    \retval     none
*/
void dsi_vertical_sync_active_count_set(uint16_t count)
{
    DSI_VSACFG = (uint32_t)(count & DSI_VSACFG_VSACNT);
}

/*!
    \brief      configure vertical back porch count (API_ID(0x000FU))
    \param[in]  count: vertical back porch count value
    \param[out] none
    \retval     none
*/
void dsi_vertical_back_porch_count_set(uint16_t count)
{
    DSI_VBPCFG = (uint32_t)(count & DSI_VBPCFG_VBPCNT);
}

/*!
    \brief      configure vertical front porch count (API_ID(0x0010U))
    \param[in]  count: vertical front porch count value
    \param[out] none
    \retval     none
*/
void dsi_vertical_front_porch_count_set(uint16_t count)
{
    DSI_VFPCFG = (uint32_t)(count & DSI_VFPCFG_VFPCNT);
}

/*!
    \brief      enable DSI command is packetized for the DPI's virtual channel (API_ID(0x0011U))
    \param[in]  cmd: DSI command to be enabled
                only one parameter can be selected which is shown as below:
      \arg        DSI_CMD_SHUT_DOWN: DPI shutdown (0x01) command
      \arg        DSI_CMD_TURN_ON: DPI turn on (0x02) command
      \arg        DSI_CMD_COLOR_MODE_ON: color mode on (0x04) command
      \arg        DSI_CMD_COLOR_MODE_OFF: color mode off (0x08) command
    \param[out] none
    \retval     none
*/
void dsi_cmd_pkt_dpi_vchannel_enable(dsi_command_enum cmd)
{
    /* set the appropriate bit for the specified command */
    DSI_DPICTL |= (uint32_t)cmd;
}

/*!
    \brief      disable DSI command is packetized for the DPI's virtual channel (API_ID(0x0012U))
    \param[in]  cmd: DSI command to be disabled
                only one parameter can be selected which is shown as below:
      \arg        DSI_CMD_SHUT_DOWN: DPI shutdown (0x01) command
      \arg        DSI_CMD_TURN_ON: DPI turn on (0x02) command
      \arg        DSI_CMD_COLOR_MODE_ON: color mode on (0x04) command
      \arg        DSI_CMD_COLOR_MODE_OFF: color mode off (0x08) command
    \param[out] none
    \retval     none
*/
void dsi_cmd_pkt_dpi_vchannel_disable(dsi_command_enum cmd)
{
    /* clear the appropriate bit for the specified command */
    DSI_DPICTL &= ~((uint32_t)cmd);
}

/*!
    \brief      set DPI resolution (API_ID(0x0013U))
    \param[in]  hor_resolution: DPI resolution value (horizontal pixels)
    \param[in]  ver_resolution: DPI resolution value (vertical pixels)
    \param[out] none
    \retval     none
*/
void dsi_dpi_resolution_set(uint16_t hor_resolution, uint16_t ver_resolution)
{
    DSI_DPIRES = (uint32_t)((uint32_t)ver_resolution << 16) | (uint32_t)hor_resolution;
}

/*!
    \brief      initialize DSI timing parameters structure with default values (API_ID(0x0014U))
    \param[in]  none
    \param[out] timing_struct: DSI timing parameters struct
    \retval     none
*/
void dsi_timing_struct_para_init(dsi_timing_parameter_struct *timing_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check for null pointer */
    if(NULL == timing_struct) {
        fw_debug_report_err(DSI_MODULE_ID, API_ID(0x0014U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the timing parameters with default values */
        timing_struct->hs_to_count = 0U;
        timing_struct->lp_rx_to_count = 0U;
        timing_struct->ta_to_count = 0U;
        timing_struct->dphy_pll_count = 0U;
        timing_struct->device_reset_timer = 0U;
        timing_struct->lp_bcm_count = 0U;
        timing_struct->hs_switch_count = 0U;
        timing_struct->clk_hs_lp_switch_count = 0U;
        timing_struct->clk_lp_hs_switch_count = 0U;
        timing_struct->init_count = 0U;
    }
}

/*!
    \brief      configure all timing parameters (API_ID(0x0015U))
    \param[in]  timing_struct: DSI timing parameters struct
                  hs_to_count: high-speed transmission timeout counter
                  lp_rx_to_count: low-power reception timeout counter
                  ta_to_count: turn-around timeout counter
                  dphy_pll_count: PLL counter
                  device_reset_timer: device reset timer value
                  lp_bcm_count: low-power byte clock mode counter
                  hs_switch_count: HS to LP and LP to HS switch count
                  clk_hs_lp_switch_count: clock lane HS to LP switch count
                  clk_lp_hs_switch_count: clock lane LP to HS switch count
                  init_count: DPHY initialization counter
    \param[out] none
    \retval     none
*/
void dsi_timing_config(dsi_timing_parameter_struct *timing_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check for null pointer */
    if(NULL == timing_struct) {
        fw_debug_report_err(DSI_MODULE_ID, API_ID(0x0015U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure high-speed transmission timeout */
        DSI_HSTXTO = (uint32_t)(timing_struct->hs_to_count & DSI_HSTXTO_HSTXTOCNT);

        /* configure low-power reception timeout */
        DSI_LPRXTO = (uint32_t)(timing_struct->lp_rx_to_count & DSI_LPRXTO_LPRXTOCNT);

        /* configure turn-around timeout */
        DSI_TATO = (uint32_t)(timing_struct->ta_to_count & DSI_TATO_TATO);

        /* configure device reset timer */
        DSI_DEVRSTTM = (uint32_t)(timing_struct->device_reset_timer & DSI_DEVRSTTM_DEVRTSTTM);

        /* configure PLL counter */
        DSI_DPHY_PLLLK = (uint32_t)(timing_struct->dphy_pll_count & DSI_DPHY_PLLLK_PLLCNTVAL);

        /* configure data lane high-low switch count */
        DSI_DLCFG = (uint32_t)(timing_struct->hs_switch_count & DSI_DLCFG_DLCFG);

        /* configure clock lane high-low switch count */
        DSI_CKLSWCFG = ((uint32_t)((uint32_t)timing_struct->clk_lp_hs_switch_count << 16U) & DSI_CKLSWCFG_LPHSSW) |
                       ((uint32_t)timing_struct->clk_hs_lp_switch_count & DSI_CKLSWCFG_HSLPSW);

        /* configure low-power byte clock */
        DSI_LPBCLKCFG = (uint32_t)(timing_struct->lp_bcm_count & DSI_LPBCLKCFG_LPBYTECLK);

        /* configure DPHY initialization count */
        DSI_INITCFG = (uint32_t)(timing_struct->init_count & DSI_INITCFG_INITCNT);
    }
}

/*!
    \brief      configure high speed transmission timeout counter (API_ID(0x0016U))
    \param[in]  timeout: high-speed transmission timeout counter value
    \param[out] none
    \retval     none
*/
void dsi_hs_tx_timeout_set(uint32_t timeout)
{
    DSI_HSTXTO = timeout & DSI_HSTXTO_HSTXTOCNT;
}

/*!
    \brief      configure low power reception timeout counter (API_ID(0x0017U))
    \param[in]  timeout: low-power reception timeout counter value
    \param[out] none
    \retval     none
*/
void dsi_lp_rx_timeout_set(uint32_t timeout)
{
    DSI_LPRXTO = timeout & DSI_LPRXTO_LPRXTOCNT;
}

/*!
    \brief      configure turn-around timeout (API_ID(0x0018U))
    \param[in]  timeout: turn-around timeout counter value
    \param[out] none
    \retval     none
*/
void dsi_turnaround_timeout_set(uint8_t timeout)
{
    DSI_TATO = (uint32_t)(timeout & DSI_TATO_TATO);
}

/*!
    \brief      configure device reset timer (API_ID(0x0019U))
    \param[in]  timer: device reset timer value
    \param[out] none
    \retval     none
*/
void dsi_device_reset_timer_set(uint16_t timer)
{
    DSI_DEVRSTTM = (uint32_t)(timer & DSI_DEVRSTTM_DEVRTSTTM);
}

/*!
    \brief      configure DSI initialization counter (API_ID(0x001AU))
    \param[in]  counter: initialization counter value in terms of low power clock
    \param[out] none
    \retval     none
*/
void dsi_init_counter_set(uint16_t counter)
{
    DSI_INITCFG = (uint32_t)(counter & DSI_INITCFG_INITCNT);
}

/*!
    \brief      set the number of data lanes (API_ID(0x001BU))
    \param[in]  number: number of data lanes
                only one parameter can be selected which is shown as below:
      \arg        DSI_DATA_LANE_ONE: one data lane
      \arg        DSI_DATA_LANE_TWO: two data lanes
    \param[out] none
    \retval     none
*/
void dsi_data_lanes_number_set(uint32_t number)
{
    uint32_t reg_val;

    /* configure the number of data lanes */
    reg_val = DSI_FUNCPRG;
    reg_val &= ~DSI_FUNCPRG_DTLANE_PRG;
    reg_val |= number & DSI_FUNCPRG_DTLANE_PRG;
    DSI_FUNCPRG = reg_val;
}

/*!
    \brief      set virtual channel for video mode (API_ID(0x001CU))
    \param[in]  virtual_channel: virtual channel ID
                only one parameter can be selected which is shown as below:
      \arg        DSI_VIRTUAL_CHANNEL_0: virtual channel 0
      \arg        DSI_VIRTUAL_CHANNEL_1: virtual channel 1
      \arg        DSI_VIRTUAL_CHANNEL_2: virtual channel 2
      \arg        DSI_VIRTUAL_CHANNEL_3: virtual channel 3
    \param[out] none
    \retval     none
*/
void dsi_video_mode_virtual_channel_set(uint32_t virtual_channel)
{
    uint32_t reg_val;

    /* set the virtual channel for video mode */
    reg_val = DSI_FUNCPRG;
    reg_val &= ~DSI_FUNCPRG_VCHNUMVM;
    reg_val |= (uint32_t)(virtual_channel << 3) & DSI_FUNCPRG_VCHNUMVM;
    DSI_FUNCPRG = reg_val;
}

/*!
    \brief      set the video mode format (API_ID(0x001DU))
    \param[in]  video_mode: video mode format
                only one parameter can be selected which is shown as below:
      \arg        DSI_VIDEO_MODE_FORMAT_NONE: none video mode format
      \arg        DSI_NON_BURST_MODE_SYNC_PULSE: non burst mode with sync pulse
      \arg        DSI_NON_BURST_MODE_SYNC_EVENTS: non burst mode with sync events
      \arg        DSI_BURST_MODE: burst mode
    \param[out] none
    \retval     none
*/
void dsi_video_mode_format_set(uint8_t video_mode)
{
    DSI_VMFMT &= ~DSI_VMFMT_VMFMT;
    DSI_VMFMT |= video_mode & DSI_VMFMT_VMFMT;
}

/*!
    \brief      set the virtual channel for command mode (API_ID(0x001EU))
    \param[in]  virtual_channel: virtual channel ID
                only one parameter can be selected which is shown as below:
      \arg        DSI_VIRTUAL_CHANNEL_0: virtual channel 0
      \arg        DSI_VIRTUAL_CHANNEL_1: virtual channel 1
      \arg        DSI_VIRTUAL_CHANNEL_2: virtual channel 2
      \arg        DSI_VIRTUAL_CHANNEL_3: virtual channel 3
    \param[out] none
    \retval     none
*/
void dsi_command_mode_virtual_channel_set(uint32_t virtual_channel)
{
    uint32_t reg_val;

    /* set the virtual channel for command mode */
    reg_val = DSI_FUNCPRG;
    reg_val &= ~DSI_FUNCPRG_VCHNUMCM;
    reg_val |= (uint32_t)(virtual_channel << 5) & DSI_FUNCPRG_VCHNUMCM;
    DSI_FUNCPRG = reg_val;
}

/*!
    \brief      set color format for video mode (API_ID(0x001FU))
    \param[in]  color_format: color format
                only one parameter can be selected which is shown as below:
       \arg       DSI_VIDEO_MODE_DISABLE: Video mode is not supported
       \arg       DSI_VIDEO_MODE_FMT_RGB565: RGB565 or 16-bit format
       \arg       DSI_VIDEO_MODE_FMT_RGB666: RGB666 or 18-bit format
       \arg       DSI_VIDEO_MODE_FMT_RGB666LP: RGB666 loosely packed format
       \arg       DSI_VIDEO_MODE_FMT_RGB888: RGB888 or 24-bit format
    \param[out] none
    \retval     none
*/
void dsi_video_mode_color_format_set(uint32_t color_format)
{
    uint32_t reg_val;

    /* set the color format for video mode */
    reg_val = DSI_FUNCPRG;
    reg_val &= ~DSI_FUNCPRG_SFMTVM;
    reg_val |= color_format & DSI_FUNCPRG_SFMTVM;
    DSI_FUNCPRG = reg_val;
}

/*!
    \brief      set data width for command mode (API_ID(0x0020U))
    \param[in]  data_width: data width
                only one parameter can be selected which is shown as below:
       \arg       DSI_CMD_MODE_DTW_8BIT: 8-bit data width
       \arg       DSI_CMD_MODE_DTW_16BIT: 16-bit data width
       \arg       DSI_CMD_MODE_DTW_24BIT: 24-bit data width
    \param[out] none
    \retval     none
*/
void dsi_command_mode_data_width_set(uint32_t data_width)
{
    uint32_t reg_val;

    /* set the data width for command mode */
    reg_val = DSI_FUNCPRG;
    reg_val &= ~DSI_FUNCPRG_SDTWCM;
    reg_val |= data_width & DSI_FUNCPRG_SDTWCM;
    DSI_FUNCPRG = reg_val;
}

/*!
    \brief      configure maximum return packet size and data transfer type (API_ID(0x0021U))
    \param[in]  hplp: data transfer type
                only one parameter can be selected which is shown as below:
       \arg       DSI_TRANSFER_HS: high-speed transfer
       \arg       DSI_TRANSFER_LP: low-power transfer
    \param[in]  size: maximum return packet size in bytes
    \param[out] none
    \retval     none
*/
void dsi_max_return_packet_config(uint16_t hplp, uint16_t size)
{
    DSI_MAXRPKTCTL = (uint32_t)(size & DSI_MAXRPKTCTL_MAXRPKTSZ) | (hplp & DSI_MAXRPKTCTL_HS_LP);
}

/*!
    \brief      set DSI polarity (API_ID(0x004FU))
    \param[in]  polarity: DSI polarity configuration
                only one parameter can be selected which is shown as below:
       \arg       DSI_VSYNC_POLARITY: vsync
       \arg       DSI_HSYNC_POLARITY: hsync
       \arg       DSI_SHUTDOWN_POLARITY: shutdown
       \arg       DSI_COLOR_MODE_POLARITY: color mode
    \param[out] none
    \retval     none
*/
void dsi_polarity_set(uint32_t polarity)
{
    DSI_PLCTL &= ~DSI_PLCTL_PL;
    DSI_PLCTL |= polarity & DSI_PLCTL_PL;
}

/*!
    \brief      swap DSI polarity to active high (API_ID(0x0022U))
    \param[in]  polarity: polarity to swap
                one or more parameters can be selected which are shown as below:
       \arg       DSI_VSYNC_POLARITY_SWAP: vsync polarity swap
       \arg       DSI_HSYNC_POLARITY_SWAP: hsync polarity swap
       \arg       DSI_SHUTDOWN_POLARITY_SWAP: shutdown polarity swap
       \arg       DSI_COLORMODE_POLARITY_SWAP: color mode polarity swap
    \param[out] none
    \retval     none
*/
void dsi_polarity_swap_high(uint32_t polarity)
{
    DSI_PLSWAP |= polarity;
}

/*!
    \brief      swap DSI polarity to active low (API_ID(0x0023U))
    \param[in]  polarity: polarity to swap
                one or more parameters can be selected which are shown as below:
       \arg       DSI_VSYNC_POLARITY_SWAP: vsync polarity swap
       \arg       DSI_HSYNC_POLARITY_SWAP: hsync polarity swap
       \arg       DSI_SHUTDOWN_POLARITY_SWAP: shutdown polarity swap
       \arg       DSI_COLORMODE_POLARITY_SWAP: color mode polarity swap
    \param[out] none
    \retval     none
*/
void dsi_polarity_swap_low(uint32_t polarity)
{
    DSI_PLSWAP &= (uint32_t)~polarity;
}

/*!
    \brief      enable EOT packet transmission (API_ID(0x0024U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dsi_eot_transmission_enable(void)
{
    uint32_t reg_val;

    reg_val = DSI_CKEOTCTL;
    reg_val &= ~DSI_CKEOTCTL_EOTDIS;
    DSI_CKEOTCTL = reg_val;
}

/*!
    \brief      disable EOT packet transmission (API_ID(0x0025U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dsi_eot_transmission_disable(void)
{
    uint32_t reg_val;

    reg_val = DSI_CKEOTCTL;
    reg_val |= DSI_CKEOTCTL_EOTDIS;
    DSI_CKEOTCTL = reg_val;
}

/*!
    \brief      enable clock stopping feature (API_ID(0x0026U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dsi_clock_stopping_enable(void)
{
    uint32_t reg_val;

    reg_val = DSI_CKEOTCTL;
    reg_val |= DSI_CKEOTCTL_CKSTOP;
    DSI_CKEOTCTL = reg_val;
}

/*!
    \brief      disable clock stopping feature (API_ID(0x0027U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dsi_clock_stopping_disable(void)
{
    uint32_t reg_val;

    reg_val = DSI_CKEOTCTL;
    reg_val &= ~DSI_CKEOTCTL_CKSTOP;
    DSI_CKEOTCTL = reg_val;
}

/*!
    \brief      enable video BTA (API_ID(0x0028U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dsi_video_bta_enable(void)
{
    uint32_t reg_val;

    reg_val = DSI_CKEOTCTL;
    reg_val &= ~DSI_CKEOTCTL_VBTADIS;
    DSI_CKEOTCTL = reg_val;
}

/*!
    \brief      disable video BTA (API_ID(0x0029U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dsi_video_bta_disable(void)
{
    uint32_t reg_val;

    reg_val = DSI_CKEOTCTL;
    reg_val |= DSI_CKEOTCTL_VBTADIS;
    DSI_CKEOTCTL = reg_val;
}

/*!
    \brief      configure HS to LP switching counter for clock lane (API_ID(0x002AU))
    \param[in]  count: HS to LP switching count value
    \param[out] none
    \retval     none
*/
void dsi_clk_hs_to_lp_switch_count_set(uint16_t count)
{
    uint32_t reg_val;

    reg_val = DSI_CKLSWCFG;
    reg_val &= ~DSI_CKLSWCFG_HSLPSW;
    reg_val |= (uint32_t)count & DSI_CKLSWCFG_HSLPSW;
    DSI_CKLSWCFG = reg_val;
}

/*!
    \brief      configure LP to HS switching counter for clock lane (API_ID(0x002BU))
    \param[in]  count: LP to HS switching count value
    \param[out] none
    \retval     none
*/
void dsi_clk_lp_to_hs_switch_count_set(uint16_t count)
{
    uint32_t reg_val;

    reg_val = DSI_CKLSWCFG;
    reg_val &= ~DSI_CKLSWCFG_LPHSSW;
    reg_val |= ((uint32_t)count << 16U) & DSI_CKLSWCFG_LPHSSW;
    DSI_CKLSWCFG = reg_val;
}

/*!
    \brief      configure data lane switching counter (API_ID(0x002CU))
    \param[in]  count: data lane switching count value
    \param[out] none
    \retval     none
*/
void dsi_data_lane_switch_count_set(uint16_t count)
{
    DSI_DLCFG = (uint32_t)(count & DSI_DLCFG_DLCFG);
}

/*!
    \brief      initialize DSI DPHY parameter structure with default values (API_ID(0x002DU))
    \param[in]  none
    \param[out] dphy_struct: DSI DPHY parameter struct
    \retval     none
*/
void dsi_dphy_struct_para_init(dsi_dphy_parameter_struct *dphy_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check for null pointer */
    if(NULL == dphy_struct) {
        fw_debug_report_err(DSI_MODULE_ID, API_ID(0x002DU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the DPHY parameters with default values */
        dphy_struct->hs_prepare = 0U;
        dphy_struct->hs_zero = 0U;
        dphy_struct->hs_trail = 0U;
        dphy_struct->hs_exit = 0U;
        dphy_struct->clk_prepare = 0U;
        dphy_struct->clk_zero = 0U;
        dphy_struct->clk_trail = 0U;
        dphy_struct->clk_exit = 0U;
    }
}

/*!
    \brief      configure the DPHY parameters (API_ID(0x002EU))
    \param[in]  dphy_struct: DSI DPHY parameter struct
                  hs_prepare: HS preparation time
                  hs_zero: HS zero time
                  hs_trail: HS trail time
                  hs_exit: HS exit time
                  clk_prepare: CLK preparation time
                  clk_zero: CLK zero time
                  clk_trail: CLK trail time
                  clk_exit: CLK exit time
    \param[out] none
    \retval     none
*/
void dsi_dphy_config(dsi_dphy_parameter_struct *dphy_struct)
{
    uint32_t reg_val_pcfg = 0U;
    uint32_t reg_val_cltmpcfg = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check for null pointer */
    if(NULL == dphy_struct) {
        fw_debug_report_err(DSI_MODULE_ID, API_ID(0x002EU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure DPHY parameters */
        reg_val_pcfg = ((uint32_t)dphy_struct->hs_prepare) |
                       ((uint32_t)dphy_struct->hs_zero << 8U) |
                       ((uint32_t)dphy_struct->hs_trail << 16U) |
                       ((uint32_t)dphy_struct->hs_exit << 24U);

        reg_val_cltmpcfg = ((uint32_t)dphy_struct->clk_prepare) |
                           ((uint32_t)dphy_struct->clk_zero << 8U) |
                           ((uint32_t)dphy_struct->clk_trail << 16U) |
                           ((uint32_t)dphy_struct->clk_exit << 24U);

        DSI_DPHY_PCFG = reg_val_pcfg;
        DSI_DPHY_CLTMPCFG = reg_val_cltmpcfg;
    }
}

/*!
    \brief      configure the PLL counter value (API_ID(0x002FU))
    \param[in]  counter_value: PLL counter value in terms of low power clock (0-65535)
    \param[out] none
    \retval     none
*/
void dsi_dphy_pll_counter_set(uint16_t counter_value)
{
    DSI_DPHY_PLLLK = (uint32_t)(counter_value & DSI_DPHY_PLLLK_PLLCNTVAL);
}

/*!
    \brief      set HS preparation time (API_ID(0x0030U))
    \param[in]  hs_prepare: HS preparation time
    \param[out] none
    \retval     none
*/
void dsi_dphy_hs_prepare_time_set(uint8_t hs_prepare)
{
    uint32_t reg_val;

    reg_val = DSI_DPHY_PCFG;
    reg_val &= ~DSI_DPHY_PCFG_HS_PREP;
    reg_val |= (uint32_t)hs_prepare & DSI_DPHY_PCFG_HS_PREP;
    DSI_DPHY_PCFG = reg_val;
}

/*!
    \brief      set HS zero time (API_ID(0x0031U))
    \param[in]  hs_zero: HS zero time
    \param[out] none
    \retval     none
*/
void dsi_dphy_hs_zero_time_set(uint8_t hs_zero)
{
    uint32_t reg_val;

    reg_val = DSI_DPHY_PCFG;
    reg_val &= ~DSI_DPHY_PCFG_HS_ZERO;
    reg_val |= ((uint32_t)hs_zero << 8U) & DSI_DPHY_PCFG_HS_ZERO;
    DSI_DPHY_PCFG = reg_val;
}

/*!
    \brief      set HS trail time (API_ID(0x0032U))
    \param[in]  hs_trail: HS trail time
    \param[out] none
    \retval     none
*/
void dsi_dphy_hs_trail_time_set(uint8_t hs_trail)
{
    uint32_t reg_val;

    reg_val = DSI_DPHY_PCFG;
    reg_val &= ~DSI_DPHY_PCFG_HS_TRAIL;
    reg_val |= ((uint32_t)hs_trail << 16) & DSI_DPHY_PCFG_HS_TRAIL;
    DSI_DPHY_PCFG = reg_val;
}

/*!
    \brief      set HS exit time (API_ID(0x0033U))
    \param[in]  hs_exit: HS exit time
    \param[out] none
    \retval     none
*/
void dsi_dphy_hs_exit_time_set(uint8_t hs_exit)
{
    uint32_t reg_val;

    reg_val = DSI_DPHY_PCFG;
    reg_val &= ~DSI_DPHY_PCFG_HS_EXIT;
    reg_val |= ((uint32_t)hs_exit << 24U) & DSI_DPHY_PCFG_HS_EXIT;
    DSI_DPHY_PCFG = reg_val;
}

/*!
    \brief      set clock preparation time (API_ID(0x0034U))
    \param[in]  clk_prepare: CLK preparation time
    \param[out] none
    \retval     none
*/
void dsi_dphy_clk_prepare_time_set(uint8_t clk_prepare)
{
    uint32_t reg_val;

    reg_val = DSI_DPHY_CLTMPCFG;
    reg_val &= ~DSI_DPHY_CLTMPCFG_CLK_PREP;
    reg_val |= (uint32_t)clk_prepare & DSI_DPHY_CLTMPCFG_CLK_PREP;
    DSI_DPHY_CLTMPCFG = reg_val;
}

/*!
    \brief      set clock zero time (API_ID(0x0035U))
    \param[in]  clk_zero: CLK zero time
    \param[out] none
    \retval     none
*/
void dsi_dphy_clk_zero_time_set(uint8_t clk_zero)
{
    uint32_t reg_val;

    reg_val = DSI_DPHY_CLTMPCFG;
    reg_val &= ~DSI_DPHY_CLTMPCFG_CLK_ZERO;
    reg_val |= ((uint32_t)clk_zero << 8U) & DSI_DPHY_CLTMPCFG_CLK_ZERO;
    DSI_DPHY_CLTMPCFG = reg_val;
}

/*!
    \brief      set clock trail time (API_ID(0x0036U))
    \param[in]  clk_trail: CLK trail time
    \param[out] none
    \retval     none
*/
void dsi_dphy_clk_trail_time_set(uint8_t clk_trail)
{
    uint32_t reg_val;

    reg_val = DSI_DPHY_CLTMPCFG;
    reg_val &= ~DSI_DPHY_CLTMPCFG_CLK_TRAIL;
    reg_val |= ((uint32_t)clk_trail << 16U) & DSI_DPHY_CLTMPCFG_CLK_TRAIL;
    DSI_DPHY_CLTMPCFG = reg_val;
}

/*!
    \brief      set clock exit time (API_ID(0x0037U))
    \param[in]  clk_exit: CLK exit time
    \param[out] none
    \retval     none
*/
void dsi_dphy_clk_exit_time_set(uint8_t clk_exit)
{
    uint32_t reg_val;

    reg_val = DSI_DPHY_CLTMPCFG;
    reg_val &= ~DSI_DPHY_CLTMPCFG_CLK_EXIT;
    reg_val |= ((uint32_t)clk_exit << 24U) & DSI_DPHY_CLTMPCFG_CLK_EXIT;
    DSI_DPHY_CLTMPCFG = reg_val;
}

/*!
    \brief      enable control reset to the digital front end (API_ID(0x0038U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dsi_dphy_dfe_reset_enable(void)
{
    DSI_DPHY_RSTENDFE = DSI_DPHY_RSTENDFE_RSTENDFE;
}

/*!
    \brief      disable control reset to the digital front end (API_ID(0x0039U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dsi_dphy_dfe_reset_disable(void)
{
    DSI_DPHY_RSTENDFE = 0U;
}

/*!
    \brief      configure DPHY trim settings (API_ID(0x003AU))
    \param[in]  trim0: trim control 0 value
    \param[in]  trim1: trim control 1 value
    \param[in]  trim2: trim control 2 value
    \param[out] none
    \retval     none
*/
void dsi_dphy_trim_config(uint32_t trim0, uint32_t trim1, uint32_t trim2)
{
    DSI_DPHY_TRIMCTL0 = trim0;
    DSI_DPHY_TRIMCTL1 = trim1;
    DSI_DPHY_TRIMCTL2 = trim2;
}

/*!
    \brief      set specific DPHY trim control 0 parameter (API_ID(0x003BU))
    \param[in]  value: value to set for the trim parameter
    \param[out] none
    \retval     none
*/
void dsi_dphy_trim_control0_set(uint32_t value)
{
    DSI_DPHY_TRIMCTL0 = value;
}

/*!
    \brief      set specific DPHY trim control 1 parameter (API_ID(0x003CU))
    \param[in]  value: value to set for the trim parameter
    \param[out] none
    \retval     none
*/
void dsi_dphy_trim_control1_set(uint32_t value)
{
    DSI_DPHY_TRIMCTL1 = value;
}

/*!
    \brief      set specific DPHY trim control 2 parameter (API_ID(0x003DU))
    \param[in]  value: value to set for the trim parameter
    \param[out] none
    \retval     none
*/
void dsi_dphy_trim_control2_set(uint32_t value)
{
    DSI_DPHY_TRIMCTL2 = value;
}

/*!
    \brief      enable/disable deskew calibration (API_ID(0x003EU))
    \param[in]  state: deskew calibration state
                only one parameter can be selected which is shown as below:
      \arg        DSI_DESKEW_DISABLE: disable deskew calibration
      \arg        DSI_INIT_DESKEW_ENABLE: enable init deskew calibration
      \arg        DSI_PERIODIC_DESKEW_ENABLE: enable periodic deskew calibration
    \param[out] none
    \retval     none
*/
void dsi_deskew_calibration_config(uint32_t state)
{
    uint32_t reg_val;

    reg_val = DSI_DSKCTL;
    reg_val &= ~DSI_DSKCTL_DSKCALIB;
    reg_val |= state & DSI_DSKCTL_DSKCALIB;
    DSI_DSKCTL = reg_val;
}

/*!
    \brief      set deskew duration (API_ID(0x003FU))
    \param[in]  duration: deskew duration value
    \param[out] none
    \retval     none
*/
void dsi_deskew_duration_set(uint16_t duration)
{
    uint32_t reg_val;

    reg_val = DSI_DSKCTL;
    reg_val &= ~DSI_DSKCTL_DSKDUR;
    reg_val |= ((uint32_t)duration << 2U) & DSI_DSKCTL_DSKDUR;
    DSI_DSKCTL = reg_val;
}

/*!
    \brief      set deskew periodic timer (API_ID(0x0040U))
    \param[in]  period: periodic deskew timer value
    \param[out] none
    \retval     none
*/
void dsi_deskew_timer_set(uint16_t period)
{
    DSI_DSKTM = (uint32_t)(period & DSI_DSKTM_DSKTM);
}

/*!
    \brief      get deskew calibration in progress status (API_ID(0x0041U))
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dsi_deskew_in_progress_status_get(void)
{
    return (DSI_DSKSTAT & DSI_DSKSTAT_DSKIP) ? SET : RESET;
}

/*!
    \brief      enable error auto recovery options (API_ID(0x0042U))
    \param[in]  recovery_options
                one or more parameters can be selected which are shown as below:
      \arg        DSI_ERR_AUTO_REC_ECC_MUL: ECC multiple error recovery
      \arg        DSI_ERR_AUTO_REC_INVLD_DT: invalid data error recovery
      \arg        DSI_ERR_AUTO_REC_HI_CONT: high contention error recovery
      \arg        DSI_ERR_AUTO_REC_LO_CONT: low contention error recovery
      \arg        DSI_ERR_AUTO_REC_HS_RX_TO: HS RX timeout error recovery
      \arg        DSI_ERR_AUTO_REC_LP_RX_TO: LP RX timeout error recovery
    \param[out] none
    \retval     none
*/
void dsi_error_auto_recovery_enable(uint32_t recovery_options)
{
    DSI_EARCTL |= recovery_options;
}

/*!
    \brief      disable error auto recovery options (API_ID(0x0043U))
    \param[in]  recovery_options
                one or more parameters can be selected which are shown as below:
      \arg        DSI_ERR_AUTO_REC_ECC_MUL: ECC multiple error recovery
      \arg        DSI_ERR_AUTO_REC_INVLD_DT: invalid data error recovery
      \arg        DSI_ERR_AUTO_REC_HI_CONT: high contention error recovery
      \arg        DSI_ERR_AUTO_REC_LO_CONT: low contention error recovery
      \arg        DSI_ERR_AUTO_REC_HS_RX_TO: HS RX timeout error recovery
      \arg        DSI_ERR_AUTO_REC_LP_RX_TO: LP RX timeout error recovery
    \param[out] none
    \retval     none
*/
void dsi_error_auto_recovery_disable(uint32_t recovery_options)
{
    DSI_EARCTL &= (uint32_t)~recovery_options;
}

/*!
    \brief      get difference in one line time between DPI and DSI (API_ID(0x0044U))
    \param[in]  none
    \param[out] none
    \retval     difference value in one line time
*/
uint16_t dsi_dpi_difference_get(void)
{
    return (uint16_t)((DSI_MIPIDIRDPISTAT & DSI_MIPIDIRDPISTAT_DPI_DIFF) >> 16);
}

/*!
    \brief      get DPI line time is greater or DSI line time is greater (API_ID(0x0045U))
    \param[in]  none
    \param[out] none
    \retval     line time status
*/
uint32_t dsi_dpi_line_time_status_get(void)
{
    return (uint32_t)((DSI_MIPIDIRDPISTAT & DSI_MIPIDIRDPISTAT_DPI_HI) >> 15);
}

/*!
    \brief      get MIPI BUS direction (API_ID(0x0046U))
    \param[in]  none
    \param[out] none
    \retval     MIPI bus direction
*/
uint32_t dsi_mipi_bus_direction_get(void)
{
    return (DSI_MIPIDIRDPISTAT & DSI_MIPIDIRDPISTAT_MIPI_DIR);
}

/*!
    \brief      set DDR frequency mode (API_ID(0x0047U))
    \param[in]  freq_mode: DDR frequency mode
                only one parameter can be selected which is shown as below:
      \arg        DDR_FREQ_LT_200MHZ: DDR freq < 200MHz
      \arg        DDR_FREQ_GT_EQ_200MHZ: DDR freq >= 200MHz
    \param[out] none
    \retval     none
*/
void dsi_ddr_freq_mode_set(uint32_t freq_mode)
{
    DSI_FMCTL = freq_mode;
}

/*!
    \brief      set TX data width (API_ID(0x0048U))
    \param[in]  width: TX data width value (0-255)
    \param[out] none
    \retval     none
*/
void dsi_tx_data_width_set(uint8_t width)
{
    DSI_TXDTWCFG = (uint32_t)width & DSI_TXDTWCFG_TXDTWIDTH;
}

/*!
    \brief      set LP control parameters (API_ID(0x0049U))
    \param[in]  data_type: data type (0-63)
    \param[in]  virtual_channel: virtual channel (0-3)
    \param[in]  word_count: word count
    \param[out] none
    \retval     none
*/
void dsi_lp_control_set(uint8_t data_type, uint8_t virtual_channel, uint32_t word_count)
{
    uint32_t reg_val = 0U;

    reg_val = ((uint32_t)data_type & 0x3FU) |
              (((uint32_t)virtual_channel & 0x3U) << 6U) |
              (((uint32_t)word_count & 0xFFFFU) << 8U);

    DSI_LPCTL = reg_val;
}

/*!
    \brief      set HS control parameters (API_ID(0x004AU))
    \param[in]  data_type: data type (0-63)
    \param[in]  virtual_channel: virtual channel
      \arg        DSI_VIRTUAL_CHANNEL_0
      \arg        DSI_VIRTUAL_CHANNEL_1
      \arg        DSI_VIRTUAL_CHANNEL_2
      \arg        DSI_VIRTUAL_CHANNEL_3
    \param[in]  word_count: word count
    \param[out] none
    \retval     none
*/
void dsi_hs_control_set(uint8_t data_type, uint8_t virtual_channel, uint32_t word_count)
{
    uint32_t reg_val = 0U;

    reg_val = ((uint32_t)data_type & 0x3FU) |
              (((uint32_t)virtual_channel & 0x3U) << 6U) |
              (((uint32_t)word_count & 0xFFFFU) << 8U);

    DSI_HSCTL = reg_val;
}

/*!
    \brief      write data to LP data register (API_ID(0x004BU))
    \param[in]  data: data used for Generic/DCS data transfers in low power mode
    \param[out] none
    \retval     none
*/
void dsi_lp_data_write(uint32_t data)
{
    DSI_LPDATA = data & DSI_LPDATA_LPDATA;
}

/*!
    \brief      read data to LP data register (API_ID(0x0071U))
    \param[in]  none
    \param[out] none
    \retval     data used for Generic/DCS data transfers in low power mode
*/
uint32_t dsi_lp_data_read(void)
{
    return DSI_LPDATA;
}

/*!
    \brief      write data to HS data register (API_ID(0x004CU))
    \param[in]  data: data used for Generic/DCS data transfers in high-speed mode
    \param[out] none
    \retval     none
*/
void dsi_hs_data_write(uint32_t data)
{
    DSI_HSDATA = data & DSI_HSDATA_HSDATA;
}

/*!
    \brief      write data to HS data register (API_ID(0x0072U))
    \param[in]  none
    \param[out] none
    \retval     data used for Generic/DCS data transfers in high-speed mode
*/
uint32_t dsi_hs_data_read(void)
{
    return DSI_HSDATA;
}

/*!
    \brief      set DCS word count (API_ID(0x004DU))
    \param[in]  count: DCS word count value
    \param[out] none
    \retval     none
*/
void dsi_dcs_word_count_set(uint16_t count)
{
    DSI_DCSWC = (uint32_t)(count & DSI_DCSWC_DCSWC);
}

/*!
    \brief      select high-speed or low-power mode for the next transmission packet (API_ID(0x004EU))
    \param[in]  mode: transmission mode
                only one parameter can be selected which is shown as below:
      \arg        DSI_TRANSFER_HS: high-speed transfer
      \arg        DSI_TRANSFER_LP: low-power transfer
    \param[out] none
    \retval     none
*/
void dsi_transfer_mode_set(uint32_t mode)
{
    uint32_t reg_val;

    reg_val = DSI_MAXRPKTCTL;
    reg_val &= ~DSI_MAXRPKTCTL_HS_LP;
    reg_val |= mode & DSI_MAXRPKTCTL_HS_LP;
    DSI_MAXRPKTCTL = reg_val;
}

/*!
    \brief      set TE polarity (API_ID(0x0051U))
    \param[in]  polarity: TE pin polarity,
                only one parameter can be selected which is shown as below:
      \arg        DSI_TE_POL_RISING_EDGE: TE pin polarity is rising edge
      \arg        DSI_TE_POL_FALLING_EDGE: TE pin polarity is falling edge
    \param[out] none
    \retval     none
*/
void dsi_wrapper_te_polarity_set(uint32_t polarity)
{
    uint32_t reg_val;

    reg_val = DSI_WCTL;
    reg_val &= ~DSI_WCTL_TEPOL;
    reg_val |= polarity & DSI_WCTL_TEPOL;
    DSI_WCTL = reg_val;
}

/*!
    \brief      enable or disable TLI DMA mode (API_ID(0x0052U))
    \param[in]  tli_dma: TLI DMA mode configuration
                only one parameter can be selected which is shown as below:
      \arg        DSI_TLI_DMA_MODE_DISABLE: DMA mode disable, DMA used by TLI
      \arg        DSI_TLI_DMA_MODE_ENABLE: DMA mode enable, DMA used by DSI
    \param[out] none
    \retval     none
*/
void dsi_wrapper_tli_dma_mode_config(uint32_t tli_dma)
{
    uint32_t reg_val;

    reg_val = DSI_WCTL;
    reg_val &= ~DSI_WCTL_TLIDMA;
    reg_val |= tli_dma & DSI_WCTL_TLIDMA;
    DSI_WCTL = reg_val;
}

/*!
    \brief      set TE source (API_ID(0x0053U))
    \param[in]  source: TE source configuration
                only one parameter can be selected which is shown as below:
      \arg        DSI_TE_EXTERNAL_PIN: external TE source
      \arg        DSI_TE_DSI_LINK: DSI packet TE source
    \param[out] none
    \retval     none
*/
void dsi_wrapper_te_source_set(uint32_t source)
{
    uint32_t reg_val;

    reg_val = DSI_WCTL;
    reg_val &= ~DSI_WCTL_TESRC;
    reg_val |= source & DSI_WCTL_TESRC;
    DSI_WCTL = reg_val;
}

/*!
    \brief      enable or disable automatic refresh mode (API_ID(0x0054U))
    \param[in]  auto_ref_mod: automatic refresh mode configuration
                only one parameter can be selected which is shown as below:
      \arg        DSI_AUTO_REFRESH_MODE_DISABLE: Automatic refresh mode disable
      \arg        DSI_AUTO_REFRESH_MODE_ENABLE: Automatic refresh mode enable
    \param[out] none
    \retval     none
*/
void dsi_wrapper_auto_refresh_mode_config(uint32_t auto_ref_mod)
{
    uint32_t reg_val;

    reg_val = DSI_WCTL;
    reg_val &= ~DSI_WCTL_ARM;
    reg_val |= auto_ref_mod & DSI_WCTL_ARM;
    DSI_WCTL = reg_val;
}

/*!
    \brief      refresh command FIFO buffer (API_ID(0x0055U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dsi_wrapper_cmd_fifo_buffer_refresh(void)
{
    DSI_WCTL |= DSI_WCTL_RBUF;
}

/*!
    \brief      enable or disable hardware auto refresh cmd buffer (API_ID(0x0056U))
    \param[in]  auto_ref_buf: hardware auto refresh buffer configuration
                only one parameter can be selected which is shown as below:
      \arg        DSI_AUTO_REFRESH_BUF_DISABLE: No auto-refresh of cmd FIFO
      \arg        DSI_AUTO_REFRESH_BUF_ENABLE: Auto-refresh cmd FIFO
    \param[out] none
    \retval     none
*/
void dsi_wrapper_auto_refresh_buffer_config(uint32_t auto_ref_buf)
{
    uint32_t reg_val;

    reg_val = DSI_WCTL;
    reg_val &= ~DSI_WCTL_ARBUF;
    reg_val |= auto_ref_buf & DSI_WCTL_ARBUF;
    DSI_WCTL = reg_val;
}

/*!
    \brief      set RGB data format (API_ID(0x0057U))
    \param[in]  format: RGB format configuration
                only one parameter can be selected which is shown as below:
      \arg        DSI_TLI_DATA_FORMAT_RGB565: RGB565 format
      \arg        DSI_TLI_DATA_RGB888: RGB888 format
      \arg        DSI_TLI_DATA_RGB888_TO_RGB666: RGB888 to RGB666 format
      \arg        DSI_TLI_DATA_RGB565_TO_RGB666: RGB565 to RGB666 format
    \param[out] none
    \retval     none
*/
void dsi_wrapper_rgb_format_set(uint32_t format)
{
    DSI_WRGBDF &= ~DSI_WRGBDF_TLI_DF;
    DSI_WRGBDF |= format & DSI_WRGBDF_TLI_DF;
}

/*!
    \brief      select HS command mode data source (API_ID(0x0058U))
    \param[in]  source: HS command mode data source
                only one parameter can be selected which is shown as below:
      \arg        DSI_HS_DATASRC_HSDATA: From DSI_HSDATA(0x104)
      \arg        DSI_HS_DATASRC_TLI_DMA: From TLI DMA
    \param[out] none
    \retval     none
*/
void dsi_wrapper_hs_cmd_data_source_set(uint32_t source)
{
    uint32_t reg_val;

    reg_val = DSI_WCMDDS;
    reg_val &= ~DSI_WCMDDS_HSCMDDS;
    reg_val |= source & DSI_WCMDDS_HSCMDDS;
    DSI_WCMDDS = reg_val;
}

/*!
    \brief      select LP command mode data source (API_ID(0x0059U))
    \param[in]  source: LP command mode data source
                only one parameter can be selected which is shown as below:
      \arg        DSI_LP_DATASRC_LPDATA: From DSI_LPDATA(0xFC)
      \arg        DSI_LP_DATASRC_TLI_DMA: From TLI DMA
    \param[out] none
    \retval     none
*/
void dsi_wrapper_lp_cmd_data_source_set(uint32_t source)
{
    uint32_t reg_val;

    reg_val = DSI_WCMDDS;
    reg_val &= ~DSI_WCMDDS_LPCMDDS;
    reg_val |= source & DSI_WCMDDS_LPCMDDS;
    DSI_WCMDDS = reg_val;
}

/*!

    \brief      select the DMA request source for command mode data (API_ID(0x005AU))
    \param[in]  source: DMA request source
                only one parameter can be selected which is shown as below:
      \arg        DSI_DMA_REQ_SRC_HSDTFIFOHE: DMA request source select HSDTFIFOHE
      \arg        DSI_DMA_REQ_SRC_HSDTFIFOE: DMA request source select HSDTFIFOE
      \arg        DSI_DMA_REQ_SRC_HSDTFIFOF_INV: DMA request source select ~HSDTFIFOF
      \arg        DSI_DMA_REQ_SRC_LPDTFIFOHE: DMA request source select LPDTFIFOHE
      \arg        DSI_DMA_REQ_SRC_LPDTFIFOE: DMA request source select LPDTFIFOE
      \arg        DSI_DMA_REQ_SRC_LPDTFIFOF_INV: DMA request source select ~LPDTFIFOF
    \param[out] none
    \retval     none
*/
void dsi_dma_request_source_select(uint32_t source)
{
    DSI_WDMARCTL &= ~DSI_WDMARCTL_DMASRC;
    DSI_WDMARCTL |= source & DSI_WDMARCTL_DMASRC;
}

/*!
    \brief      initialize DSI WMS structure with default values (API_ID(0x005BU))
    \param[in]  none
    \param[out] wms_struct: DSI WMS parameter struct
    \retval     none
*/
void dsi_wms_struct_para_init(dsi_wms_parameter_struct *wms_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check for null pointer */
    if(NULL == wms_struct) {
        fw_debug_report_err(DSI_MODULE_ID, API_ID(0x005BU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* initialize the WMS parameters with default values */
        wms_struct->wms_mode = DSI_WMS_MODE_HS;
        wms_struct->first_packet_header = 0U;
        wms_struct->second_packet_header = 0U;
        wms_struct->dcs_command = 0U;
        wms_struct->packet_length = 0U;
        wms_struct->total_length = 0U;
    }
}

/*!
    \brief      configure the DSI wrapper WMS parameters (API_ID(0x005CU))
    \param[in]  wms_struct: DSI WMS parameter struct
                  wms_mode: WMS mode, DSI_WMS_MODE_HS, DSI_WMS_MODE_LP
                  first_packet_header: first split packet head
                  second_packet_header: secondary split packet head
                  dcs_command: long packet DCS command
                  packet_length: packet length in words
                  total_length: total number of words to be transferred
    \param[out] none
    \retval     none
*/
void dsi_wms_config(dsi_wms_parameter_struct *wms_struct)
{
    uint32_t reg_val;

#ifdef FW_DEBUG_ERR_REPORT
    /* check for null pointer */
    if(NULL == wms_struct) {
        fw_debug_report_err(DSI_MODULE_ID, API_ID(0x005CU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* Configure WMS control register */
        reg_val = DSI_WWMS_WCTL;
        reg_val &= ~DSI_WWMS_WCTL_WMS_MODE;
        reg_val |= wms_struct->wms_mode & DSI_WWMS_WCTL_WMS_MODE;
        DSI_WWMS_WCTL = reg_val;

        /* Configure WMS header */
        DSI_WWMS_HEAD = ((uint32_t)wms_struct->first_packet_header) |
                        ((uint32_t)wms_struct->second_packet_header << 8U) |
                        ((uint32_t)wms_struct->dcs_command << 16U);

        /* Configure WMS size */
        DSI_WWMS_SIZE = ((uint32_t)wms_struct->packet_length & 0xFFU) |
                        ((uint32_t)wms_struct->total_length << 8U);
    }
}

/*!
    \brief      enable WMS function (API_ID(0x005DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dsi_wrapper_wms_enable(void)
{
    DSI_WWMS_WCTL |= DSI_WWMS_WCTL_WMS_EN;
}


/*!
    \brief      set WMS mode (API_ID(0x005FU))
    \param[in]  mode: WMS mode configuration
                only one parameter can be selected which is shown as below:
      \arg        DSI_WMS_MODE_HS: WMS HS mode
      \arg        DSI_WMS_MODE_LP: WMS LP mode
    \param[out] none
    \retval     none
*/
void dsi_wrapper_wms_mode_set(uint32_t mode)
{
    uint32_t reg_val;

    reg_val = DSI_WWMS_WCTL;
    reg_val &= ~DSI_WWMS_WCTL_WMS_MODE;
    reg_val |= mode & DSI_WWMS_WCTL_WMS_MODE;
    DSI_WWMS_WCTL = reg_val;
}

/*!
    \brief      check if WMS end flag is set (API_ID(0x0060U))
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dsi_wrapper_wms_end_flag_get(void)
{
    return (DSI_WWMS_WCTL & DSI_WWMS_WCTL_WMS_END) ? SET : RESET;
}

/*!
    \brief      mask or unmask the WMS end interrupt (API_ID(0x0061U))
    \param[in]  state: mask state, RESET or SET
    \param[out] none
    \retval     none
*/
void dsi_wrapper_wms_end_interrupt_mask(FlagStatus state)
{
    if(state == SET) {
        /* Mask the WMS end interrupt */
        DSI_WWMS_INTMSK |= DSI_WWMS_INTMSK_WMS_ENDMSK;
    } else {
        /* Unmask the WMS end interrupt */
        DSI_WWMS_INTMSK &= ~DSI_WWMS_INTMSK_WMS_ENDMSK;
    }
}

/*!
    \brief      set WMS header messages (API_ID(0x0062U))
    \param[in]  first_header: first split packet head message
    \param[in]  second_header: secondary split packet head message
    \param[in]  dcs_cmd: long packet DCS command
    \param[out] none
    \retval     none
*/
void dsi_wrapper_wms_header_set(uint8_t first_header, uint8_t second_header, uint8_t dcs_cmd)
{
    DSI_WWMS_HEAD = ((uint32_t)first_header) |
                    ((uint32_t)second_header << 8U) |
                    ((uint32_t)dcs_cmd << 16U);
}

/*!
    \brief      set WMS packet length and total length (API_ID(0x0063U))
    \param[in]  packet_length: packet length in words
    \param[in]  total_length: total number of words to be transferred
    \param[out] none
    \retval     none
*/
void dsi_wrapper_wms_size_set(uint8_t packet_length, uint32_t total_length)
{
    DSI_WWMS_SIZE = ((uint32_t)packet_length & 0xFFU) |
                    ((uint32_t)total_length << 8U);
}

/*!
    \brief      get WMS packet number (API_ID(0x0064U))
    \param[in]  none
    \param[out] none
    \retval     uint16_t: current number of packets transferred
*/
uint16_t dsi_wrapper_wms_packet_number_get(void)
{
    return (uint16_t)(DSI_WWMS_STAT0 & DSI_WWMS_STAT0_PKT_NUM);
}

/*!
    \brief      get WMS sum count (API_ID(0x0065U))
    \param[in]  none
    \param[out] none
    \retval     uint32_t: current count of transferred words
*/
uint32_t dsi_wrapper_wms_sum_count_get(void)
{
    return (DSI_WWMS_STAT1 & DSI_WWMS_STAT1_SUM_CNT);
}

/*!
    \brief      check the status of specific FIFO (API_ID(0x0066U))
    \param[in]  fifo_stat: FIFO status to check
                one or more parameters can be selected which are shown as below:
      \arg        DSI_DATA_FIFO_STAT_HS_FULL: HS Generic/DCS data FIFO full
      \arg        DSI_DATA_FIFO_STAT_HS_HALF_EMPTY: HS Generic/DCS data FIFO half empty
      \arg        DSI_DATA_FIFO_STAT_HS_EMPTY: HS Generic/DCS data FIFO empty
      \arg        DSI_DATA_FIFO_STAT_LP_FULL: LP Generic/DCS data FIFO full
      \arg        DSI_DATA_FIFO_STAT_LP_HALF_EMPTY: LP Generic/DCS data FIFO half empty
      \arg        DSI_DATA_FIFO_STAT_LP_EMPTY: LP Generic/DCS data FIFO empty
      \arg        DSI_CTRL_FIFO_STAT_HS_FULL: HS Generic/DCS control FIFO full
      \arg        DSI_CTRL_FIFO_STAT_HS_HALF_EMPTY: HS Generic/DCS control FIFO half empty
      \arg        DSI_CTRL_FIFO_STAT_HS_EMPTY: HS Generic/DCS control FIFO empty
      \arg        DSI_CTRL_FIFO_STAT_LP_FULL: LP Generic/DCS control FIFO full
      \arg        DSI_CTRL_FIFO_STAT_LP_HALF_EMPTY: LP Generic/DCS control FIFO half empty
      \arg        DSI_CTRL_FIFO_STAT_LP_EMPTY: LP Generic/DCS control FIFO empty
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dsi_fifo_status_get(uint32_t fifo_stat)
{
    return (DSI_FIFOSTAT & fifo_stat) ? SET : RESET;
}

/*!
    \brief      get DSI specific flag status (API_ID(0x0067U))
    \param[in]  flag: flag to check, possible values from dsi_flag_enum:
       \arg       DSI_FLAG_RXSOTE: Rx Sot Error flag
       \arg       DSI_FLAG_RXSOTSYNCE: Rx Sot Sync Error flag
       \arg       DSI_FLAG_RXEOTSYNCE: Rx Eot sync Error flag
       \arg       DSI_FLAG_RXESCMEE: Rx Escape Mode Entry Error flag
       \arg       DSI_FLAG_RXLPTXSYNCE: Rx LP tx sync error flag
       \arg       DSI_FLAG_RXPTOE: Rx Peripheral timeout Error flag
       \arg       DSI_FLAG_RXFCTLE: RxFalse Control Error flag
       \arg       DSI_FLAG_RXECCSE: Rx ECC single bit error flag
       \arg       DSI_FLAG_RXECCME: Rx ECC multibit error flag
       \arg       DSI_FLAG_RXCHKE: Rx checksum error flag
       \arg       DSI_FLAG_RXDSIDTNR: Rx DSI data type not recognized flag
       \arg       DSI_FLAG_RXDSIVCIDINV: Rx DSI virtual channel ID invalid flag
       \arg       DSI_FLAG_TXFCTLE: Tx False Control Error flag
       \arg       DSI_FLAG_TXECCSE: Tx ECC single bit error flag
       \arg       DSI_FLAG_TXECCME: Tx ECC multibit error flag
       \arg       DSI_FLAG_TXCHKE: Tx checksum(CRC) error flag
       \arg       DSI_FLAG_TXDSIDTNR: Tx DSI data type not recognized flag
       \arg       DSI_FLAG_TXDSIVCIDINV: Tx DSI virtual channel ID invalid flag
       \arg       DSI_FLAG_HCONT: high contention flag
       \arg       DSI_FLAG_LCONT: low contention flag
       \arg       DSI_FLAG_FIFOE: FIFO empty flag
       \arg       DSI_FLAG_HSTXTO: HS Tx timeout flag
       \arg       DSI_FLAG_LPRXTO: LP Rx timeout flag
       \arg       DSI_FLAG_TAACKTO: turn around ack timeout flag
       \arg       DSI_FLAG_ACKNE: ACK with No error flag
       \arg       DSI_FLAG_RXINVTXCE: Rx Invalid transmission count error flag
       \arg       DSI_FLAG_RXDSIPV: Rx DSI protocol violation flag
       \arg       DSI_FLAG_SPKTCMDS: special packet command sent flag
       \arg       DSI_FLAG_INIT_DONE: DSI initialization is done flag
       \arg       DSI_FLAG_RXCONTDET: Rx Contention Detected flag
       \arg       DSI_FLAG_DPILTO: dpi line timeout flag
       \arg       DSI_FLAG_DPIPE: dpi program error flag
       \arg       DSI_FLAG_HSDTFIFOF: HS Generic/DCS data FIFO full flag
       \arg       DSI_FLAG_LPDTFIFOF: LP Generic/DCS data FIFO full flag
       \arg       DSI_FLAG_HSCTLFIFOF: HS Generic/DCS control FIFO full flag
       \arg       DSI_FLAG_LPCTLFIFOF: LP Generic/DCS control FIFO full flag
       \arg       DSI_FLAG_RDDTA: LP Generic/DCS read data available flag
       \arg       DSI_FLAG_TETG: tearing effect(TE) trigger message received flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dsi_flag_get(dsi_flag_enum flag)
{
    FlagStatus retval = RESET;
    /* check if the flag is set */
    if(DSI_REG_VAL(DSI, flag) & BIT(DSI_BIT_POS(flag))) {
        retval = SET;
    } else {
        /* do nothing */
    }
    return retval;
}

/*!
    \brief      enable DSI specific interrupt (API_ID(0x0068U))
    \param[in]  interrupt: interrupt to enable
                only one parameter can be selected which is shown as below:
       \arg       DSI_INT_RXSOTE: Rx Sot Error interrupt
       \arg       DSI_INT_RXSOTSYNCE: Rx Sot Sync Error interrupt
       \arg       DSI_INT_RXEOTSYNCE: Rx Eot sync Error interrupt
       \arg       DSI_INT_RXESCMEE: Rx Escape Mode Entry Error interrupt
       \arg       DSI_INT_RXLPTXSYNCE: Rx LP tx sync error interrupt
       \arg       DSI_INT_RXPTOE: Rx Peripheral timeout Error interrupt
       \arg       DSI_INT_RXFCTLE: RxFalse Control Error interrupt
       \arg       DSI_INT_RXECCSE: Rx ECC single bit error interrupt
       \arg       DSI_INT_RXECCME: Rx ECC multibit error interrupt
       \arg       DSI_INT_RXCHKE: Rx checksum error interrupt
       \arg       DSI_INT_RXDSIDTNR: Rx DSI data type not recognized interrupt
       \arg       DSI_INT_RXDSIVCIDINV: Rx DSI virtual channel ID invalid interrupt
       \arg       DSI_INT_TXFCTLE: Tx False Control Error interrupt
       \arg       DSI_INT_TXECCSE: Tx ECC single bit error interrupt
       \arg       DSI_INT_TXECCME: Tx ECC multibit error interrupt
       \arg       DSI_INT_TXCHKE: Tx checksum(CRC) error interrupt
       \arg       DSI_INT_TXDSIDTNR: Tx DSI data type not recognized interrupt
       \arg       DSI_INT_TXDSIVCIDINV: Tx DSI virtual channel ID invalid interrupt
       \arg       DSI_INT_HCONT: high contention interrupt
       \arg       DSI_INT_LCONT: low contention interrupt
       \arg       DSI_INT_FIFOE: FIFO empty interrupt
       \arg       DSI_INT_HSTXTO: HS Tx timeout interrupt
       \arg       DSI_INT_LPRXTO: LP Rx timeout interrupt
       \arg       DSI_INT_TAACKTO: turn around ack timeout interrupt
       \arg       DSI_INT_ACKNE: ACK with No error interrupt
       \arg       DSI_INT_RXINVTXCE: Rx Invalid transmission count error interrupt
       \arg       DSI_INT_RXDSIPV: Rx DSI protocol violation interrupt
       \arg       DSI_INT_SPKTCMDS: special packet command sent interrupt
       \arg       DSI_INT_INIT_DONE: DSI initialization is done interrupt
       \arg       DSI_INT_RXCONTDET: Rx Contention Detected interrupt
       \arg       DSI_INT_DPILTO: DPI line timeout interrupt
       \arg       DSI_INT_DPIPE: DPI program error interrupt
       \arg       DSI_INT_HSDTFIFOF: HS Generic/DCS data FIFO full interrupt
       \arg       DSI_INT_LPDTFIFOF: LP Generic/DCS data FIFO full interrupt
       \arg       DSI_INT_LPCTLFIFOF: LP Generic/DCS control FIFO full interrupt
       \arg       DSI_INT_HSCTLFIFOF: HS Generic/DCS control FIFO full interrupt
       \arg       DSI_INT_RDDTA: LP Generic/DCS read data available interrupt
       \arg       DSI_INT_TETG: tearing effect(TE) trigger message received interrupt
     \param[out] none
     \retval     none
*/
void dsi_interrupt_enable(dsi_int_enum interrupt)
{
    DSI_REG_VAL(DSI, interrupt) |= BIT(DSI_BIT_POS(interrupt));
}

/*!
    \brief      disable DSI specific interrupt (API_ID(0x0069U))
    \param[in]  interrupt: interrupt to disable
                only one parameter can be selected which is shown as below:
       \arg       DSI_INT_RXSOTE: Rx Sot Error interrupt
       \arg       DSI_INT_RXSOTSYNCE: Rx Sot Sync Error interrupt
       \arg       DSI_INT_RXEOTSYNCE: Rx Eot sync Error interrupt
       \arg       DSI_INT_RXESCMEE: Rx Escape Mode Entry Error interrupt
       \arg       DSI_INT_RXLPTXSYNCE: Rx LP tx sync error interrupt
       \arg       DSI_INT_RXPTOE: Rx Peripheral timeout Error interrupt
       \arg       DSI_INT_RXFCTLE: RxFalse Control Error interrupt
       \arg       DSI_INT_RXECCSE: Rx ECC single bit error interrupt
       \arg       DSI_INT_RXECCME: Rx ECC multibit error interrupt
       \arg       DSI_INT_RXCHKE: Rx checksum error interrupt
       \arg       DSI_INT_RXDSIDTNR: Rx DSI data type not recognized interrupt
       \arg       DSI_INT_RXDSIVCIDINV: Rx DSI virtual channel ID invalid interrupt
       \arg       DSI_INT_TXFCTLE: Tx False Control Error interrupt
       \arg       DSI_INT_TXECCSE: Tx ECC single bit error interrupt
       \arg       DSI_INT_TXECCME: Tx ECC multibit error interrupt
       \arg       DSI_INT_TXCHKE: Tx checksum(CRC) error interrupt
       \arg       DSI_INT_TXDSIDTNR: Tx DSI data type not recognized interrupt
       \arg       DSI_INT_TXDSIVCIDINV: Tx DSI virtual channel ID invalid interrupt
       \arg       DSI_INT_HCONT: high contention interrupt
       \arg       DSI_INT_LCONT: low contention interrupt
       \arg       DSI_INT_FIFOE: FIFO empty interrupt
       \arg       DSI_INT_HSTXTO: HS Tx timeout interrupt
       \arg       DSI_INT_LPRXTO: LP Rx timeout interrupt
       \arg       DSI_INT_TAACKTO: turn around ack timeout interrup
       \arg       DSI_INT_ACKNE: ACK with No error interrupt
       \arg       DSI_INT_RXINVTXCE: Rx Invalid transmission count error interrupt
       \arg       DSI_INT_RXDSIPV: Rx DSI protocol violation interrupt
       \arg       DSI_INT_SPKTCMDS: special packet command sent interrupt
       \arg       DSI_INT_INIT_DONE: DSI initialization is done interrupt
       \arg       DSI_INT_RXCONTDET: Rx Contention Detected interrupt
       \arg       DSI_INT_DPILTO: DPI line timeout interrupt
       \arg       DSI_INT_DPIPE: DPI program error interrupt
       \arg       DSI_INT_HSDTFIFOF: HS Generic/DCS data FIFO full interrupt
       \arg       DSI_INT_LPDTFIFOF: LP Generic/DCS data FIFO full interrupt
       \arg       DSI_INT_LPCTLFIFOF: LP Generic/DCS control FIFO full interrupt
       \arg       DSI_INT_HSCTLFIFOF: HS Generic/DCS control FIFO full interrupt
       \arg       DSI_INT_RDDTA: LP Generic/DCS read data available interrupt
       \arg       DSI_INT_TETG: tearing effect(TE) trigger message received interrupt
    \param[out] none
    \retval     none
*/
void dsi_interrupt_disable(dsi_int_enum interrupt)
{
    DSI_REG_VAL(DSI, interrupt) &= ~BIT(DSI_BIT_POS(interrupt));
}

/*!
    \brief      get DSI specific interrupt flag status (API_ID(0x006AU))
    \param[in]  int_flag: interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        DSI_INT_FLAG_RXSOTE: Rx Sot Error interrupt flag
      \arg        DSI_INT_FLAG_RXSOTSYNCE: Rx Sot Sync Error interrupt flag
      \arg        DSI_INT_FLAG_RXEOTSYNCE: Rx Eot sync Error interrupt flag
      \arg        DSI_INT_FLAG_RXESCMEE: Rx Escape Mode Entry Error interrupt flag
      \arg        DSI_INT_FLAG_RXLPTXSYNCE: Rx LP tx sync error interrupt flag
      \arg        DSI_INT_FLAG_RXPTOE: Rx Peripheral timeout Error interrupt flag
      \arg        DSI_INT_FLAG_RXFCTLE: RxFalse Control Error interrupt flag
      \arg        DSI_INT_FLAG_RXECCSE: Rx ECC single bit error interrupt flag
      \arg        DSI_INT_FLAG_RXECCME: Rx ECC multibit error interrupt flag
      \arg        DSI_INT_FLAG_RXCHKE: Rx checksum error interrupt flag
      \arg        DSI_INT_FLAG_RXDSIDTNR: Rx DSI data type not recognized interrupt flag
      \arg        DSI_INT_FLAG_RXDSIVCIDINV: Rx DSI virtual channel ID invalid interrupt flag
      \arg        DSI_INT_FLAG_TXFCTLE: Tx False Control Error interrupt flag
      \arg        DSI_INT_FLAG_TXECCSE: Tx ECC single bit error interrupt flag
      \arg        DSI_INT_FLAG_TXECCME: Tx ECC multibit error interrupt flag
      \arg        DSI_INT_FLAG_TXCHKE: Tx checksum(CRC) error interrupt flag
      \arg        DSI_INT_FLAG_TXDSIDTNR: Tx DSI data type not recognized interrupt flag
      \arg        DSI_INT_FLAG_TXDSIVCIDINV: Tx DSI virtual channel ID invalid interrupt flag
      \arg        DSI_INT_FLAG_HCONT: high contention interrupt flag
      \arg        DSI_INT_FLAG_LCONT: low contention interrupt flag
      \arg        DSI_INT_FLAG_FIFOE: FIFO empty interrupt flag
      \arg        DSI_INT_FLAG_HSTXTO: HS Tx timeout interrupt flag
      \arg        DSI_INT_FLAG_LPRXTO: LP Rx timeout interrupt flag
      \arg        DSI_INT_FLAG_TAACKTO: turn around ack timeout interrupt flag
      \arg        DSI_INT_FLAG_ACKNE: ACK with No error interrupt flag
      \arg        DSI_INT_FLAG_RXINVTXCE: Rx Invalid transmission count error interrupt flag
      \arg        DSI_INT_FLAG_RXDSIPV: Rx DSI protocol violation interrupt flag
      \arg        DSI_INT_FLAG_SPKTCMDS: special packet command sent interrupt flag
      \arg        DSI_INT_FLAG_INIT_DONE: DSI initialization is done interrupt flag
      \arg        DSI_INT_FLAG_RXCONTDET: Rx Contention Detected interrupt flag
      \arg        DSI_INT_FLAG_DPILTO: DPI line timeout interrupt flag
      \arg        DSI_INT_FLAG_DPIPE: DPI program error interrupt flag
      \arg        DSI_INT_FLAG_HSDTFIFOF: HS Generic/DCS data FIFO full flag
      \arg        DSI_INT_FLAG_LPDTFIFOF: LP Generic/DCS data FIFO full flag
      \arg        DSI_INT_FLAG_HSCTLFIFOF: HS Generic/DCS control FIFO full flag
      \arg        DSI_INT_FLAG_LPCTLFIFOF: LP Generic/DCS control FIFO full flag
      \arg        DSI_INT_FLAG_RDDTA: LP Generic/DCS read data available flag
      \arg        DSI_INT_FLAG_TETG: tearing effect(TE) trigger message received flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
    \Note       After the interrupt enable bit is cleared, if the hardware flag remains set, this API will still return RESET.
                Therefore, in an ISR or during the interrupt-disable flow, this API alone must not be relied upon to determine whether the flag should be cleared.
                The corresponding flag must be cleared according to the module-specific rules, and the NVIC-pending bit should also be cleared when necessary.
*/
FlagStatus dsi_interrupt_flag_get(dsi_int_flag_enum int_flag)
{
    uint32_t interrupt_enable = 0U;
    uint32_t interrupt_flag = 0U;
    FlagStatus retval = RESET;

    /* check interrupt flag */
    interrupt_flag = DSI_REG_VAL(DSI, int_flag) & BIT(DSI_BIT_POS(int_flag));

    /* check interrupt enable */
    if((uint32_t)(int_flag) >> 22 != 0U) {
        interrupt_enable = DSI_REG_VAL2(DSI, int_flag) & BIT(DSI_BIT_POS2(int_flag));
    } else {
        interrupt_enable = 0x01U;
    }

    /* check if the flag is set and enabled */
    if(interrupt_flag && interrupt_enable) {
        retval = SET;
    } else {
        /* do nothing */
    }
    return retval;
}

/*!
    \brief      clear DSI specific interrupt flag (API_ID(0x006BU))
    \param[in]  int_flag: interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        DSI_INT_FLAG_RXSOTE: Rx Sot Error interrupt flag
      \arg        DSI_INT_FLAG_RXSOTSYNCE: Rx Sot Sync Error interrupt flag
      \arg        DSI_INT_FLAG_RXEOTSYNCE: Rx Eot sync Error interrupt flag
      \arg        DSI_INT_FLAG_RXESCMEE: Rx Escape Mode Entry Error interrupt flag
      \arg        DSI_INT_FLAG_RXLPTXSYNCE: Rx LP tx sync error interrupt flag
      \arg        DSI_INT_FLAG_RXPTOE: Rx Peripheral timeout Error interrupt flag
      \arg        DSI_INT_FLAG_RXFCTLE: RxFalse Control Error interrupt flag
      \arg        DSI_INT_FLAG_RXECCSE: Rx ECC single bit error interrupt flag
      \arg        DSI_INT_FLAG_RXECCME: Rx ECC multibit error interrupt flag
      \arg        DSI_INT_FLAG_RXCHKE: Rx checksum error interrupt flag
      \arg        DSI_INT_FLAG_RXDSIDTNR: Rx DSI data type not recognized interrupt flag
      \arg        DSI_INT_FLAG_RXDSIVCIDINV: Rx DSI virtual channel ID invalid interrupt flag
      \arg        DSI_INT_FLAG_TXFCTLE: Tx False Control Error interrupt flag
      \arg        DSI_INT_FLAG_TXECCSE: Tx ECC single bit error interrupt flag
      \arg        DSI_INT_FLAG_TXECCME: Tx ECC multibit error interrupt flag
      \arg        DSI_INT_FLAG_TXCHKE: Tx checksum(CRC) error interrupt flag
      \arg        DSI_INT_FLAG_TXDSIDTNR: Tx DSI data type not recognized interrupt flag
      \arg        DSI_INT_FLAG_TXDSIVCIDINV: Tx DSI virtual channel ID invalid interrupt flag
      \arg        DSI_INT_FLAG_HCONT: high contention interrupt flag
      \arg        DSI_INT_FLAG_LCONT: low contention interrupt flag
      \arg        DSI_INT_FLAG_FIFOE: FIFO empty interrupt flag
      \arg        DSI_INT_FLAG_HSTXTO: HS Tx timeout interrupt flag
      \arg        DSI_INT_FLAG_LPRXTO: LP Rx timeout interrupt flag
      \arg        DSI_INT_FLAG_TAACKTO: turn around ack timeout interrupt flag
      \arg        DSI_INT_FLAG_ACKNE: ACK with No error interrupt flag
      \arg        DSI_INT_FLAG_RXINVTXCE: Rx Invalid transmission count error interrupt flag
      \arg        DSI_INT_FLAG_RXDSIPV: Rx DSI protocol violation interrupt flag
      \arg        DSI_INT_FLAG_SPKTCMDS: special packet command sent interrupt flag
      \arg        DSI_INT_FLAG_INIT_DONE: DSI initialization is done interrupt flag
      \arg        DSI_INT_FLAG_RXCONTDET: Rx Contention Detected interrupt flag
      \arg        DSI_INT_FLAG_DPILTO: DPI line timeout interrupt flag
      \arg        DSI_INT_FLAG_DPIPE: DPI program error interrupt flag
      \arg        DSI_INT_FLAG_HSDTFIFOF: HS Generic/DCS data FIFO full flag
      \arg        DSI_INT_FLAG_LPDTFIFOF: LP Generic/DCS data FIFO full flag
      \arg        DSI_INT_FLAG_HSCTLFIFOF: HS Generic/DCS control FIFO full flag
      \arg        DSI_INT_FLAG_LPCTLFIFOF: LP Generic/DCS control FIFO full flag
      \arg        DSI_INT_FLAG_RDDTA: LP Generic/DCS read data available flag
      \arg        DSI_INT_FLAG_TETG: tearing effect(TE) trigger message received flag
    \param[out] none
    \retval     none
*/
void dsi_interrupt_flag_clear(dsi_int_flag_enum int_flag)
{
    DSI_REG_VAL(DSI, int_flag) |= BIT(DSI_BIT_POS(int_flag));
}

/*!
    \brief      get DSI wrapper specific flag status (API_ID(0x006CU))
    \param[in]  flag: flag to check
                only one parameter can be selected which is shown as below:
      \arg        DSI_FLAG_TE: tearing effect flag
      \arg        DSI_FLAG_PLL_LOCK: PLL lock flag
      \arg        DSI_FLAG_PLL_UNLOCK: PLL unlock flag
      \arg        DSI_FLAG_PLL_LOCK_STAT: PLL lock status
      \arg        DSI_FLAG_WMS_END: write memory split packet end flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dsi_wrapper_flag_get(dsi_wrapper_flag_enum flag)
{
    FlagStatus retval = RESET;
    /* check if the flag is set */
    if(DSI_REG_VAL(DSI, flag) & BIT(DSI_BIT_POS(flag))) {
        retval = SET;
    } else {
        /* do nothing */
    }
    return retval;
}

/*!
    \brief      enable DSI wrapper specific interrupt (API_ID(0x006DU))
    \param[in]  interrupt: interrupt to enable
                only one parameter can be selected which is shown as below:
       \arg       DSI_INT_TE: tearing effect interrupt
       \arg       DSI_INT_PLL_LOCK: PLL lock interrupt
       \arg       DSI_INT_PLL_UNLOCK: PLL unlock interrupt
       \arg       DSI_INT_WMS_END_MSK: write memory split packet WMS_END flag interrupt signal mask
    \param[out] none
    \retval     none
*/
void dsi_wrapper_interrupt_enable(dsi_wrapper_int_enum interrupt)
{
    DSI_REG_VAL(DSI, interrupt) |= BIT(DSI_BIT_POS(interrupt));
}

/*!
    \brief      disable DSI wrapper specific interrupt (API_ID(0x006EU))
    \param[in]  interrupt: interrupt to disable
                only one parameter can be selected which is shown as below:
       \arg       DSI_INT_TE: tearing effect interrupt
       \arg       DSI_INT_PLL_LOCK: PLL lock interrupt
       \arg       DSI_INT_PLL_UNLOCK: PLL unlock interrupt
       \arg       DSI_INT_WMS_END_MSK: write memory split packet WMS_END flag interrupt signal mask
    \param[out] none
    \retval     none
*/
void dsi_wrapper_interrupt_disable(dsi_wrapper_int_enum interrupt)
{
    DSI_REG_VAL(DSI, interrupt) &= ~BIT(DSI_BIT_POS(interrupt));
}

/*!
    \brief      get DSI wrapper specific interrupt flag status (API_ID(0x006FU))
    \param[in]  int_flag: interrupt flag to check
                only one parameter can be selected which is shown as below:
       \arg       DSI_INT_FLAG_TE: tearing effect flag
       \arg       DSI_INT_FLAG_PLL_LOCK: PLL lock flag
       \arg       DSI_INT_FLAG_PLL_UNLOCK: PLL unlock flag
       \arg       DSI_INT_FLAG_PLL_LOCK_STAT: PLL lock status
       \arg       DSI_INT_FLAG_WMS_END: write memory split packet end flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dsi_wrapper_interrupt_flag_get(dsi_wrapper_int_flag_enum int_flag)
{
    FlagStatus retval = RESET;
    /* check if the flag is set */
    if(DSI_REG_VAL(DSI, int_flag) & BIT(DSI_BIT_POS(int_flag))) {
        retval = SET;
    } else {
        /* do nothing */
    }
    return retval;
}

/*!
    \brief      clear DSI wrapper specific interrupt flag (API_ID(0x0070U))
    \param[in]  int_flag: interrupt flag to clear
                only one parameter can be selected which is shown as below:
       \arg       DSI_INT_FLAG_TE_CLR: tearing effect flag clear
       \arg       DSI_INT_FLAG_PLL_LOCK_CLR: PLL lock flag clear
       \arg       DSI_INT_FLAG_PLL_UNLOCK_CLR: PLL unlock flag clear
       \arg       DSI_INT_FLAG_WMS_END_CLR: write memory split packet end flag
    \param[out] none
    \retval     none
*/
void dsi_wrapper_interrupt_flag_clear(dsi_wrapper_int_flag_clr_enum int_flag)
{
    DSI_REG_VAL(DSI, int_flag) |= BIT(DSI_BIT_POS(int_flag));
}
