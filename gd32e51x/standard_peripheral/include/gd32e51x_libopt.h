/*!
    \file    gd32e51x_libopt.h
    \brief   library optional for gd32e51x

    \version 2025-01-26, V1.0.0, firmware for GD32E51x
*/

/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.

    SPDX-License-Identifier: Apache-2.0
*/

#ifndef GD32E51X_LIBOPT_H
#define GD32E51X_LIBOPT_H

#include "gd32e51x_adc.h"
#include "gd32e51x_bkp.h"
#include "gd32e51x_can.h"
#include "gd32e51x_cmp.h"
#include "gd32e51x_crc.h"
#include "gd32e51x_ctc.h"
#include "gd32e51x_dac.h"
#include "gd32e51x_dbg.h"
#include "gd32e51x_dma.h"
#include "gd32e51x_exmc.h"
#include "gd32e51x_exti.h"
#include "gd32e51x_fmc.h"
#include "gd32e51x_fwdgt.h"
#include "gd32e51x_gpio.h"
#include "gd32e51x_shrtimer.h"
#include "gd32e51x_i2c.h"
#include "gd32e51x_misc.h"
#include "gd32e51x_pmu.h"
#include "gd32e51x_rcu.h"
#include "gd32e51x_rtc.h"
#include "gd32e51x_spi.h"
#include "gd32e51x_sqpi.h"
#include "gd32e51x_timer.h"
#include "gd32e51x_usart.h"
#include "gd32e51x_wwdgt.h"

#if defined (GD32E51X_CL)
#include "gd32e51x_enet.h"
#include "gd32e51x_tmu.h"
#else
#include "gd32e51x_sdio.h"
#endif /* GD32E51X_CL */

#endif /* GD32E51X_LIBOPT_H */
