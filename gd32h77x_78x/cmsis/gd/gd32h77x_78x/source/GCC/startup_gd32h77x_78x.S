;/*!
;    \file    startup_gd32h77x_78x.S
;    \brief   start up file
;
;    \version 2026-11-09, V1.0.0, firmware for GD32H77x_78x
;*/
;
;/*
; * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
; * Copyright (c) 2026, GigaDevice Semiconductor Inc.
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; */
;/* This file refers the CMSIS standard, some adjustments are made according to GigaDevice chips */

  .syntax unified
  .cpu cortex-m7
  .fpu softvfp
  .thumb

.global  Default_Handler

/* necessary symbols defined in linker script to initialize data */
.word  _sidata
.word  _sdata
.word  _edata
.word  _sbss
.word  _ebss

  .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function

/* reset Handler */
Reset_Handler:
  LDR     r1, =0x24000000
  LDR     r2, =0x8000  /* can be modify by actual memory allocation*/
  MOV     r0, #0x00
SRAM_INIT:
  STM     r1!, {r0}
  SUBS    r2, r2, #4
  CMP     r2, #0x00
  BNE     SRAM_INIT

Init:
  movs r1, #0
  b DataInit

CopyData:
  ldr r3, =_sidata
  ldr r3, [r3, r1]
  str r3, [r0, r1]
  adds r1, r1, #4

DataInit:
  ldr r0, =_sdata
  ldr r3, =_edata
  adds r2, r0, r1
  cmp r2, r3
  bcc CopyData
  ldr r2, =_sbss
  b Zerobss

FillZerobss:
  movs r3, #0
  str r3, [r2], #4

Zerobss:
  ldr r3, = _ebss
  cmp r2, r3
  bcc FillZerobss

/* Call SystemInit function */
  bl  SystemInit
/* Call static constructors */
  bl __libc_init_array
/*Call the main function */
  bl main
  bx lr

.size Reset_Handler, .-Reset_Handler

  .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler

  .section  .vectors,"a",%progbits
  .global __gVectors
__gVectors:
                    .word _sp                                     /* Top of Stack */
                    .word Reset_Handler                           /* Reset Handler */
                    .word NMI_Handler                             /* NMI Handler */
                    .word HardFault_Handler                       /* Hard Fault Handler */
                    .word MemManage_Handler                       /* MPU Fault Handler */
                    .word BusFault_Handler                        /* Bus Fault Handler */
                    .word UsageFault_Handler                      /* Usage Fault Handler */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word SVC_Handler                             /* SVCall Handler */
                    .word DebugMon_Handler                        /* Debug Monitor Handler */
                    .word 0                                       /* Reserved */
                    .word PendSV_Handler                          /* PendSV Handler */
                    .word SysTick_Handler                         /* SysTick Handler */

                    /* External interrupts handler */
                    .word WWDGT_IRQHandler                        /* Vector Number 16,WWDGT interrupt */
                    .word VAVD_LVD_VOVD_VUVD_IRQHandler           /* Vector Number 17,VAVD / LVD / VOVD / VUVD through exti line detection interrupt */
                    .word TAMPER_STAMP_LXTAL_IRQHandler           /* Vector Number 18,RTC tamper and timestamp from EXTI interrupt, LXTAL clock stuck interrupt */
                    .word RTC_WKUP_IRQHandler                     /* Vector Number 19,RTC wakeup from EXTI interrupt */
                    .word NVMC_IRQHandler                         /* Vector Number 20,NVMC global interrupt */
                    .word RCU_IRQHandler                          /* Vector Number 21,RCU global interrupt */
                    .word EXTI0_IRQHandler                        /* Vector Number 22,EXTI line0 interrupt */
                    .word EXTI1_IRQHandler                        /* Vector Number 23,EXTI line1 interrupt */
                    .word EXTI2_IRQHandler                        /* Vector Number 24,EXTI line2 interrupt */
                    .word EXTI3_IRQHandler                        /* Vector Number 25,EXTI line3 interrupt */
                    .word EXTI4_IRQHandler                        /* Vector Number 26,EXTI line4 interrupt */
                    .word DMA0_Channel0_IRQHandler                /* Vector Number 27,DMA0 channel0 global interrupt */
                    .word DMA0_Channel1_IRQHandler                /* Vector Number 28,DMA0 channel1 global interrupt */
                    .word DMA0_Channel2_IRQHandler                /* Vector Number 29,DMA0 channel2 global interrupt */
                    .word DMA0_Channel3_IRQHandler                /* Vector Number 30,DMA0 channel3 global interrupt */
                    .word DMA0_Channel4_IRQHandler                /* Vector Number 31,DMA0 channel4 global interrupt */
                    .word DMA0_Channel5_IRQHandler                /* Vector Number 32,DMA0 channel5 global interrupt */
                    .word DMA0_Channel6_IRQHandler                /* Vector Number 33,DMA0 channel6 global interrupt */
                    .word ADC0_1_RDCM_IRQHandler                  /* Vector Number 34,ADC0 and ADC1 global interrupt, RDCM global interrupt */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word EXTI5_9_IRQHandler                      /* Vector Number 39,EXTI line5-9 interrupt */
                    .word TIMER0_BRK_IRQHandler                   /* Vector Number 40,TIMER0 break interrupt */
                    .word TIMER0_UP_IRQHandler                    /* Vector Number 41,TIMER0 update interrupt */
                    .word TIMER0_TRG_CMT_IRQHandler               /* Vector Number 42,TIMER0 trigger and commutation interrupt */
                    .word TIMER0_Channel_IRQHandler               /* Vector Number 43,TIMER0 capture compare interrupt */
                    .word TIMER1_IRQHandler                       /* Vector Number 44,TIMER1 global interrupt */
                    .word TIMER2_IRQHandler                       /* Vector Number 45,TIMER2 global interrupt */
                    .word TIMER3_IRQHandler                       /* Vector Number 46,TIMER3 global interrupt */
                    .word I2C0_EV_IRQHandler                      /* Vector Number 47,I2C0 event interrupt */
                    .word I2C0_ER_IRQHandler                      /* Vector Number 48,I2C0 error interrupt */
                    .word I2C1_EV_IRQHandler                      /* Vector Number 49,I2C1 event interrupt */
                    .word I2C1_ER_IRQHandler                      /* Vector Number 50,I2C1 error interrupt */
                    .word SPI0_IRQHandler                         /* Vector Number 51,SPI0 global interrupt */
                    .word SPI1_IRQHandler                         /* Vector Number 52,SPI1 global interrupt */
                    .word USART0_IRQHandler                       /* Vector Number 53,USART0 global and wakeup interrupt */
                    .word USART1_IRQHandler                       /* Vector Number 54,USART1 global and wakeup interrupt */
                    .word USART2_IRQHandler                       /* Vector Number 55,USART2 global and wakeup interrupt */
                    .word EXTI10_15_IRQHandler                    /* Vector Number 56,EXTI line10-15 interrupt */
                    .word RTC_Alarm_IRQHandler                    /* Vector Number 57,RTC alarm from EXTI interrupt */
                    .word 0                                       /* Reserved */
                    .word TIMER7_BRK_IRQHandler                   /* Vector Number 59,TIMER7 break interrupt */
                    .word TIMER7_UP_IRQHandler                    /* Vector Number 60,TIMER7 update interrupt */
                    .word TIMER7_TRG_CMT_IRQHandler               /* Vector Number 61,TIMER7 trigger and commutation interrupt */
                    .word TIMER7_Channel_IRQHandler               /* Vector Number 62,TIMER7 capture compare interrupt */
                    .word DMA0_Channel7_IRQHandler                /* Vector Number 63,DMA0 channel7 global interrupt */
                    .word EXMC_IRQHandler                         /* Vector Number 64,EXMC global interrupt */
                    .word SDIO0_IRQHandler                        /* Vector Number 65,SDIO0 global interrupt */
                    .word TIMER4_IRQHandler                       /* Vector Number 66,TIMER4 global interrupt */
                    .word SPI2_IRQHandler                         /* Vector Number 67,SPI2 global interrupt */
                    .word UART3_IRQHandler                        /* Vector Number 68,UART3 global interrupt */
                    .word UART4_IRQHandler                        /* Vector Number 69,UART4 global interrupt */
                    .word TIMER5_DAC_UDR_IRQHandler               /* Vector Number 70,TIMER5 global interrupt and DAC underrun error interrupt */
                    .word TIMER6_IRQHandler                       /* Vector Number 71,TIMER6 global interrupt */
                    .word DMA1_Channel0_IRQHandler                /* Vector Number 72,DMA1 channel0 global interrupt */
                    .word DMA1_Channel1_IRQHandler                /* Vector Number 73,DMA1 channel1 global interrupt */
                    .word DMA1_Channel2_IRQHandler                /* Vector Number 74,DMA1 channel2 global interrupt */
                    .word DMA1_Channel3_IRQHandler                /* Vector Number 75,DMA1 channel3 global interrupt */
                    .word DMA1_Channel4_IRQHandler                /* Vector Number 76,DMA1 channel4 global interrupt */
                    .word ENET0_IRQHandler                        /* Vector Number 77,ENET0 global interrupt */
                    .word ENET0_WKUP_IRQHandler                   /* Vector Number 78,ENET0 wakeup from EXTI interrupt */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word DMA1_Channel5_IRQHandler                /* Vector Number 84,DMA1 channel5 global interrupt */
                    .word DMA1_Channel6_IRQHandler                /* Vector Number 85,DMA1 channel6 global interrupt */
                    .word DMA1_Channel7_IRQHandler                /* Vector Number 86,DMA1 channel7 global interrupt */
                    .word USART5_IRQHandler                       /* Vector Number 87,USART5 global and wakeup interrupt */
                    .word I2C2_EV_IRQHandler                      /* Vector Number 88,I2C2 event interrupt */
                    .word I2C2_ER_IRQHandler                      /* Vector Number 89,I2C2 error interrupt */
                    .word USBHS0_EP1_OUT_IRQHandler               /* Vector Number 90,USBHS0 endpoint 1 out interrupt */
                    .word USBHS0_EP1_IN_IRQHandler                /* Vector Number 91,USBHS0 endpoint 1 in interrupt */
                    .word USBHS0_WKUP_IRQHandler                  /* Vector Number 92,USBHS0 wakeup from EXTI interrupt */
                    .word USBHS0_IRQHandler                       /* Vector Number 93,USBHS0 global interrupt */
                    .word DCI_IRQHandler                          /* Vector Number 94,DCI global interrupt */
                    .word CAU_IRQHandler                          /* Vector Number 95,CAU global interrupt */
                    .word HAU_TRNG_IRQHandler                     /* Vector Number 96,HAU and TRNG global interrupt */
                    .word FPU_IRQHandler                          /* Vector Number 97,FPU global interrupt */
                    .word UART6_IRQHandler                        /* Vector Number 98,UART6 global interrupt */
                    .word UART7_IRQHandler                        /* Vector Number 99,UART7 global interrupt */
                    .word SPI3_IRQHandler                         /* Vector Number 100,SPI3 global interrupt */
                    .word SPI4_IRQHandler                         /* Vector Number 101,SPI4 global interrupt */
                    .word SPI5_IRQHandler                         /* Vector Number 102,SPI5 global interrupt */
                    .word SAI0_IRQHandler                         /* Vector Number 103,SAI0 global interrupt */
                    .word TLI_IRQHandler                          /* Vector Number 104,TLI global interrupt */
                    .word TLI_ER_IRQHandler                       /* Vector Number 105,TLI error interrupt */
                    .word IPA_IRQHandler                          /* Vector Number 106,IPA global interrupt */
                    .word SAI1_IRQHandler                         /* Vector Number 107,SAI1 global interrupt */
                    .word OSPI0_IRQHandler                        /* Vector Number 108,OSPI0 global interrupt */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word I2C3_EV_IRQHandler                      /* Vector Number 111,I2C3 event interrupt */
                    .word I2C3_ER_IRQHandler                      /* Vector Number 112,I2C3 error interrupt */
                    .word RSPDIF_IRQHandler                       /* Vector Number 113,RSPDIF global interrupt */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word DMAMUX_OVR_IRQHandler                   /* Vector Number 118,DMAMUX overrun interrupt */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word HPDF_INT4_IRQHandler                    /* Vector Number 125,HPDF global interrupt 4 */
                    .word HPDF_INT0_IRQHandler                    /* Vector Number 126,HPDF global interrupt 0 */
                    .word HPDF_INT1_IRQHandler                    /* Vector Number 127,HPDF global interrupt 1 */
                    .word HPDF_INT2_IRQHandler                    /* Vector Number 128,HPDF global interrupt 2 */
                    .word HPDF_INT3_IRQHandler                    /* Vector Number 129,HPDF global interrupt 3 */
                    .word SAI2_IRQHandler                         /* Vector Number 130,SAI2 global interrupt */
                    .word 0                                       /* Reserved */
                    .word TIMER14_IRQHandler                      /* Vector Number 132,TIMER14 global interrupt */
                    .word TIMER15_IRQHandler                      /* Vector Number 133,TIMER15 global interrupt */
                    .word TIMER16_IRQHandler                      /* Vector Number 134,TIMER16 global interrupt */
                    .word 0                                       /* Reserved */
                    .word MDIO_IRQHandler                         /* Vector Number 136,MDIO global interrupt */
                    .word 0                                       /* Reserved */
                    .word MDMA_IRQHandler                         /* Vector Number 138,MDMA global interrupt */
                    .word 0                                       /* Reserved */
                    .word SDIO1_IRQHandler                        /* Vector Number 140,SDIO1 global interrupt */
                    .word HWSEM_IRQHandler                        /* Vector Number 141,HWSEM global interrupt */
                    .word 0                                       /* Reserved */
                    .word ADC2_IRQHandler                         /* Vector Number 143,ADC2 global interrupt */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word CMP0_1_IRQHandler                       /* Vector Number 153,CMP0 and CMP1 global interrupt, CMP0 and CMP1 through EXTI line detection interrupt */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word CTC_IRQHandler                          /* Vector Number 160,CTC interrupt */
                    .word RAMECCMU_IRQHandler                     /* Vector Number 161,RAMECCMU global interrupt */
                    .word SAI3_IRQHandler                         /* Vector Number 162,SAI3 global interrupt */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word OSPI1_IRQHandler                        /* Vector Number 166,OSPI1 global interrupt */
                    .word RTDEC0_IRQHandler                       /* Vector Number 167,RTDEC0 global interrupt */
                    .word RTDEC1_IRQHandler                       /* Vector Number 168,RTDEC1 global interrupt */
                    .word FAC_IRQHandler                          /* Vector Number 169,FAC global interrupt */
                    .word TMU_IRQHandler                          /* Vector Number 170,TMU global interrupt */
                    .word FFT_IRQHandler                          /* Vector Number 171,FFT global interrupt */
                    .word ESC_SYNC0_IRQHandler                    /* Vector Number 172,ESC SYNC0 interrupt */
                    .word ESC_SYNC1_IRQHandler                    /* Vector Number 173,ESC SYNC1 interrupt */
                    .word ESC_IRQHandler                          /* Vector Number 174,ESC IRQ interrupt */
                    .word 0                                       /* Reserved */
                    .word 0                                       /* Reserved */
                    .word TIMER22_IRQHandler                      /* Vector Number 177,TIMER22 global interrupt */
                    .word TIMER23_IRQHandler                      /* Vector Number 178,TIMER23 global interrupt */
                    .word TIMER30_IRQHandler                      /* Vector Number 179,TIMER30 global interrupt */
                    .word TIMER31_IRQHandler                      /* Vector Number 180,TIMER31 global interrupt */
                    .word TIMER40_IRQHandler                      /* Vector Number 181,TIMER40 global interrupt */
                    .word TIMER41_IRQHandler                      /* Vector Number 182,TIMER41 global interrupt */
                    .word TIMER42_IRQHandler                      /* Vector Number 183,TIMER42 global interrupt */
                    .word TIMER43_IRQHandler                      /* Vector Number 184,TIMER43 global interrupt */
                    .word TIMER44_IRQHandler                      /* Vector Number 185,TIMER44 global interrupt */
                    .word TIMER50_IRQHandler                      /* Vector Number 186,TIMER50 global interrupt */
                    .word TIMER51_IRQHandler                      /* Vector Number 187,TIMER51 global interrupt */
                    .word USBHS1_EP1_OUT_IRQHandler               /* Vector Number 188,USBHS1 endpoint 1 out interrupt */
                    .word USBHS1_EP1_IN_IRQHandler                /* Vector Number 189,USBHS1 endpoint 1 in interrupt */
                    .word USBHS1_WKUP_IRQHandler                  /* Vector Number 190,USBHS1 wakeup from EXTI interrupt */
                    .word USBHS1_IRQHandler                       /* Vector Number 191,USBHS1 global interrupt */
                    .word ENET1_IRQHandler                        /* Vector Number 192,ENET1 global interrupt */
                    .word ENET1_WKUP_IRQHandler                   /* Vector Number 193,ENET1 wakeup from EXTI interrupt */
                    .word 0                                       /* Reserved */
                    .word CAN0_WKUP_IRQHandler                    /* Vector Number 195,CAN0 wakeup through EXTI line detection interrupt */
                    .word CAN0_Message_IRQHandler                 /* Vector Number 196,CAN0 interrupt for message buffer */
                    .word CAN0_Busoff_IRQHandler                  /* Vector Number 197,CAN0 interrupt for bus off / bus off done */
                    .word CAN0_Error_IRQHandler                   /* Vector Number 198,CAN0 interrupt for error */
                    .word CAN0_FastError_IRQHandler               /* Vector Number 199,CAN0 interrupt for error in fast transmission */
                    .word CAN0_TEC_IRQHandler                     /* Vector Number 200,CAN0 interrupt for transmit warning */
                    .word CAN0_REC_IRQHandler                     /* Vector Number 201,CAN0 interrupt for receive warning */
                    .word CAN1_WKUP_IRQHandler                    /* Vector Number 202,CAN1 wakeup through EXTI line detection interrupt */
                    .word CAN1_Message_IRQHandler                 /* Vector Number 203,CAN1 interrupt for message buffer */
                    .word CAN1_Busoff_IRQHandler                  /* Vector Number 204,CAN1 interrupt for bus off / bus off done */
                    .word CAN1_Error_IRQHandler                   /* Vector Number 205,CAN1 interrupt for error */
                    .word CAN1_FastError_IRQHandler               /* Vector Number 206,CAN1 interrupt for error in fast transmission */
                    .word CAN1_TEC_IRQHandler                     /* Vector Number 207,CAN1 interrupt for transmit warning */
                    .word CAN1_REC_IRQHandler                     /* Vector Number 208,CAN1 interrupt for receive warning */
                    .word CAN2_WKUP_IRQHandler                    /* Vector Number 209,CAN2 wakeup through EXTI line detection interrupt */
                    .word CAN2_Message_IRQHandler                 /* Vector Number 210,CAN2 interrupt for message buffer */
                    .word CAN2_Busoff_IRQHandler                  /* Vector Number 211,CAN2 interrupt for bus off / bus off done */
                    .word CAN2_Error_IRQHandler                   /* Vector Number 212,CAN2 interrupt for error */
                    .word CAN2_FastError_IRQHandler               /* Vector Number 213,CAN2 interrupt for error in fast transmission */
                    .word CAN2_TEC_IRQHandler                     /* Vector Number 214,CAN2 interrupt for transmit warning */
                    .word CAN2_REC_IRQHandler                     /* Vector Number 215,CAN2 interrupt for receive warning */
                    .word OTP_IRQHandler                          /* Vector Number 216,OTP global interrupt */
                    .word I2C0_WKUP_IRQHandler                    /* Vector Number 217,I2C0 wakeup through EXTI line detection interrupt */
                    .word I2C1_WKUP_IRQHandler                    /* Vector Number 218,I2C1 wakeup through EXTI line detection interrupt */
                    .word I2C2_WKUP_IRQHandler                    /* Vector Number 219,I2C2 wakeup through EXTI line detection interrupt */
                    .word I2C3_WKUP_IRQHandler                    /* Vector Number 220,I2C3 wakeup through EXTI line detection interrupt */
                    .word LPDTS_IRQHandler                        /* Vector Number 221,LPDTS interrupt */
                    .word LPDTS_WKUP_IRQHandler                   /* Vector Number 222,LPDTS wakeup through EXTI line detection interrupt */
                    .word TIMER0_DEC_IRQHandler                   /* Vector Number 223,TIMER0 DEC interrupt */
                    .word TIMER7_DEC_IRQHandler                   /* Vector Number 224,TIMER7 DEC interrupt */
                    .word TIMER1_DEC_IRQHandler                   /* Vector Number 225,TIMER1 DEC interrupt */
                    .word TIMER2_DEC_IRQHandler                   /* Vector Number 226,TIMER2 DEC interrupt */
                    .word TIMER3_DEC_IRQHandler                   /* Vector Number 227,TIMER3 DEC interrupt */
                    .word TIMER4_DEC_IRQHandler                   /* Vector Number 228,TIMER4 DEC interrupt */
                    .word TIMER22_DEC_IRQHandler                  /* Vector Number 229,TIMER22 DEC interrupt */
                    .word TIMER23_DEC_IRQHandler                  /* Vector Number 230,TIMER23 DEC interrupt */
                    .word TIMER30_DEC_IRQHandler                  /* Vector Number 231,TIMER30 DEC interrupt */
                    .word TIMER31_DEC_IRQHandler                  /* Vector Number 232,TIMER31 DEC interrupt */
                    .word CPU_DCACHE_ERR_IRQHandler               /* Vector Number 233,CPU D-Cache error detection interrupt */
                    .word CPU_ICACHE_ERR_IRQHandler               /* Vector Number 234,CPU I-Cache error detection interrupt */
                    .word VOVD_VUVD_FILTER_IRQHandler             /* Vector Number 235,VOVD / VUVD interrupt after digital filtering */
                    .word 0                                       /* Vector Number 236,Reserved */
                    .word TIMER0_Channel_BRK_IRQHandler           /* Vector Number 237,TIMER0 channel break interrupt */
                    .word TIMER7_Channel_BRK_IRQHandler           /* Vector Number 238,TIMER7 channel break interrupt */
                    .word DSI_IRQHandler                          /* Vector Number 239,DSI global interrupt */
                    .word PKCAU_IRQHandler                        /* Vector Number 240,PKCAU global interrupt */
                    .word ESC_BRIDGE_IRQHandler                   /* Vector Number 241,ESC internal interrupt */
                    .word EDIM_IRQHandler                         /* Vector Number 242,EDIM global interrupt */

  .size   __gVectors, . - __gVectors

  .weak NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak MemManage_Handler
  .thumb_set MemManage_Handler,Default_Handler

  .weak BusFault_Handler
  .thumb_set BusFault_Handler,Default_Handler

  .weak UsageFault_Handler
  .thumb_set UsageFault_Handler,Default_Handler

  .weak SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak DebugMon_Handler
  .thumb_set DebugMon_Handler,Default_Handler

  .weak PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak WWDGT_IRQHandler
  .thumb_set WWDGT_IRQHandler,Default_Handler

  .weak VAVD_LVD_VOVD_VUVD_IRQHandler
  .thumb_set VAVD_LVD_VOVD_VUVD_IRQHandler,Default_Handler

  .weak TAMPER_STAMP_LXTAL_IRQHandler
  .thumb_set TAMPER_STAMP_LXTAL_IRQHandler,Default_Handler

  .weak RTC_WKUP_IRQHandler
  .thumb_set RTC_WKUP_IRQHandler,Default_Handler

  .weak NVMC_IRQHandler
  .thumb_set NVMC_IRQHandler,Default_Handler

  .weak RCU_IRQHandler
  .thumb_set RCU_IRQHandler,Default_Handler

  .weak EXTI0_IRQHandler
  .thumb_set EXTI0_IRQHandler,Default_Handler

  .weak EXTI1_IRQHandler
  .thumb_set EXTI1_IRQHandler,Default_Handler

  .weak EXTI2_IRQHandler
  .thumb_set EXTI2_IRQHandler,Default_Handler

  .weak EXTI3_IRQHandler
  .thumb_set EXTI3_IRQHandler,Default_Handler

  .weak EXTI4_IRQHandler
  .thumb_set EXTI4_IRQHandler,Default_Handler

  .weak DMA0_Channel0_IRQHandler
  .thumb_set DMA0_Channel0_IRQHandler,Default_Handler

  .weak DMA0_Channel1_IRQHandler
  .thumb_set DMA0_Channel1_IRQHandler,Default_Handler

  .weak DMA0_Channel2_IRQHandler
  .thumb_set DMA0_Channel2_IRQHandler,Default_Handler

  .weak DMA0_Channel3_IRQHandler
  .thumb_set DMA0_Channel3_IRQHandler,Default_Handler

  .weak DMA0_Channel4_IRQHandler
  .thumb_set DMA0_Channel4_IRQHandler,Default_Handler

  .weak DMA0_Channel5_IRQHandler
  .thumb_set DMA0_Channel5_IRQHandler,Default_Handler

  .weak DMA0_Channel6_IRQHandler
  .thumb_set DMA0_Channel6_IRQHandler,Default_Handler

  .weak ADC0_1_RDCM_IRQHandler
  .thumb_set ADC0_1_RDCM_IRQHandler,Default_Handler

  .weak EXTI5_9_IRQHandler
  .thumb_set EXTI5_9_IRQHandler,Default_Handler

  .weak TIMER0_BRK_IRQHandler
  .thumb_set TIMER0_BRK_IRQHandler,Default_Handler

  .weak TIMER0_UP_IRQHandler
  .thumb_set TIMER0_UP_IRQHandler,Default_Handler

  .weak TIMER0_TRG_CMT_IRQHandler
  .thumb_set TIMER0_TRG_CMT_IRQHandler,Default_Handler

  .weak TIMER0_Channel_IRQHandler
  .thumb_set TIMER0_Channel_IRQHandler,Default_Handler

  .weak TIMER1_IRQHandler
  .thumb_set TIMER1_IRQHandler,Default_Handler

  .weak TIMER2_IRQHandler
  .thumb_set TIMER2_IRQHandler,Default_Handler

  .weak TIMER3_IRQHandler
  .thumb_set TIMER3_IRQHandler,Default_Handler

  .weak I2C0_EV_IRQHandler
  .thumb_set I2C0_EV_IRQHandler,Default_Handler

  .weak I2C0_ER_IRQHandler
  .thumb_set I2C0_ER_IRQHandler,Default_Handler

  .weak I2C1_EV_IRQHandler
  .thumb_set I2C1_EV_IRQHandler,Default_Handler

  .weak I2C1_ER_IRQHandler
  .thumb_set I2C1_ER_IRQHandler,Default_Handler

  .weak SPI0_IRQHandler
  .thumb_set SPI0_IRQHandler,Default_Handler

  .weak SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler

  .weak USART0_IRQHandler
  .thumb_set USART0_IRQHandler,Default_Handler

  .weak USART1_IRQHandler
  .thumb_set USART1_IRQHandler,Default_Handler

  .weak USART2_IRQHandler
  .thumb_set USART2_IRQHandler,Default_Handler

  .weak EXTI10_15_IRQHandler
  .thumb_set EXTI10_15_IRQHandler,Default_Handler

  .weak RTC_Alarm_IRQHandler
  .thumb_set RTC_Alarm_IRQHandler,Default_Handler

  .weak TIMER7_BRK_IRQHandler
  .thumb_set TIMER7_BRK_IRQHandler,Default_Handler

  .weak TIMER7_UP_IRQHandler
  .thumb_set TIMER7_UP_IRQHandler,Default_Handler

  .weak TIMER7_TRG_CMT_IRQHandler
  .thumb_set TIMER7_TRG_CMT_IRQHandler,Default_Handler

  .weak TIMER7_Channel_IRQHandler
  .thumb_set TIMER7_Channel_IRQHandler,Default_Handler

  .weak DMA0_Channel7_IRQHandler
  .thumb_set DMA0_Channel7_IRQHandler,Default_Handler

  .weak EXMC_IRQHandler
  .thumb_set EXMC_IRQHandler,Default_Handler

  .weak SDIO0_IRQHandler
  .thumb_set SDIO0_IRQHandler,Default_Handler

  .weak TIMER4_IRQHandler
  .thumb_set TIMER4_IRQHandler,Default_Handler

  .weak SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler,Default_Handler

  .weak UART3_IRQHandler
  .thumb_set UART3_IRQHandler,Default_Handler

  .weak UART4_IRQHandler
  .thumb_set UART4_IRQHandler,Default_Handler

  .weak TIMER5_DAC_UDR_IRQHandler
  .thumb_set TIMER5_DAC_UDR_IRQHandler,Default_Handler

  .weak TIMER6_IRQHandler
  .thumb_set TIMER6_IRQHandler,Default_Handler

  .weak DMA1_Channel0_IRQHandler
  .thumb_set DMA1_Channel0_IRQHandler,Default_Handler

  .weak DMA1_Channel1_IRQHandler
  .thumb_set DMA1_Channel1_IRQHandler,Default_Handler

  .weak DMA1_Channel2_IRQHandler
  .thumb_set DMA1_Channel2_IRQHandler,Default_Handler

  .weak DMA1_Channel3_IRQHandler
  .thumb_set DMA1_Channel3_IRQHandler,Default_Handler

  .weak DMA1_Channel4_IRQHandler
  .thumb_set DMA1_Channel4_IRQHandler,Default_Handler

  .weak ENET0_IRQHandler
  .thumb_set ENET0_IRQHandler,Default_Handler

  .weak ENET0_WKUP_IRQHandler
  .thumb_set ENET0_WKUP_IRQHandler,Default_Handler

  .weak DMA1_Channel5_IRQHandler
  .thumb_set DMA1_Channel5_IRQHandler,Default_Handler

  .weak DMA1_Channel6_IRQHandler
  .thumb_set DMA1_Channel6_IRQHandler,Default_Handler

  .weak DMA1_Channel7_IRQHandler
  .thumb_set DMA1_Channel7_IRQHandler,Default_Handler

  .weak USART5_IRQHandler
  .thumb_set USART5_IRQHandler,Default_Handler

  .weak I2C2_EV_IRQHandler
  .thumb_set I2C2_EV_IRQHandler,Default_Handler

  .weak I2C2_ER_IRQHandler
  .thumb_set I2C2_ER_IRQHandler,Default_Handler

  .weak USBHS0_EP1_OUT_IRQHandler
  .thumb_set USBHS0_EP1_OUT_IRQHandler,Default_Handler

  .weak USBHS0_EP1_IN_IRQHandler
  .thumb_set USBHS0_EP1_IN_IRQHandler,Default_Handler

  .weak USBHS0_WKUP_IRQHandler
  .thumb_set USBHS0_WKUP_IRQHandler,Default_Handler

  .weak USBHS0_IRQHandler
  .thumb_set USBHS0_IRQHandler,Default_Handler

  .weak DCI_IRQHandler
  .thumb_set DCI_IRQHandler,Default_Handler

  .weak CAU_IRQHandler
  .thumb_set CAU_IRQHandler,Default_Handler

  .weak HAU_TRNG_IRQHandler
  .thumb_set HAU_TRNG_IRQHandler,Default_Handler

  .weak FPU_IRQHandler
  .thumb_set FPU_IRQHandler,Default_Handler

  .weak UART6_IRQHandler
  .thumb_set UART6_IRQHandler,Default_Handler

  .weak UART7_IRQHandler
  .thumb_set UART7_IRQHandler,Default_Handler

  .weak SPI3_IRQHandler
  .thumb_set SPI3_IRQHandler,Default_Handler

  .weak SPI4_IRQHandler
  .thumb_set SPI4_IRQHandler,Default_Handler

  .weak SPI5_IRQHandler
  .thumb_set SPI5_IRQHandler,Default_Handler

  .weak SAI0_IRQHandler
  .thumb_set SAI0_IRQHandler,Default_Handler

  .weak TLI_IRQHandler
  .thumb_set TLI_IRQHandler,Default_Handler

  .weak TLI_ER_IRQHandler
  .thumb_set TLI_ER_IRQHandler,Default_Handler

  .weak IPA_IRQHandler
  .thumb_set IPA_IRQHandler,Default_Handler

  .weak SAI1_IRQHandler
  .thumb_set SAI1_IRQHandler,Default_Handler

  .weak OSPI0_IRQHandler
  .thumb_set OSPI0_IRQHandler,Default_Handler

  .weak I2C3_EV_IRQHandler
  .thumb_set I2C3_EV_IRQHandler,Default_Handler

  .weak I2C3_ER_IRQHandler
  .thumb_set I2C3_ER_IRQHandler,Default_Handler

  .weak RSPDIF_IRQHandler
  .thumb_set RSPDIF_IRQHandler,Default_Handler

  .weak DMAMUX_OVR_IRQHandler
  .thumb_set DMAMUX_OVR_IRQHandler,Default_Handler

  .weak HPDF_INT4_IRQHandler
  .thumb_set HPDF_INT4_IRQHandler,Default_Handler

  .weak HPDF_INT0_IRQHandler
  .thumb_set HPDF_INT0_IRQHandler,Default_Handler

  .weak HPDF_INT1_IRQHandler
  .thumb_set HPDF_INT1_IRQHandler,Default_Handler

  .weak HPDF_INT2_IRQHandler
  .thumb_set HPDF_INT2_IRQHandler,Default_Handler

  .weak HPDF_INT3_IRQHandler
  .thumb_set HPDF_INT3_IRQHandler,Default_Handler

  .weak SAI2_IRQHandler
  .thumb_set SAI2_IRQHandler,Default_Handler

  .weak TIMER14_IRQHandler
  .thumb_set TIMER14_IRQHandler,Default_Handler

  .weak TIMER15_IRQHandler
  .thumb_set TIMER15_IRQHandler,Default_Handler

  .weak TIMER16_IRQHandler
  .thumb_set TIMER16_IRQHandler,Default_Handler

  .weak MDIO_IRQHandler
  .thumb_set MDIO_IRQHandler,Default_Handler

  .weak MDMA_IRQHandler
  .thumb_set MDMA_IRQHandler,Default_Handler

  .weak SDIO1_IRQHandler
  .thumb_set SDIO1_IRQHandler,Default_Handler

  .weak HWSEM_IRQHandler
  .thumb_set HWSEM_IRQHandler,Default_Handler

  .weak ADC2_IRQHandler
  .thumb_set ADC2_IRQHandler,Default_Handler

  .weak CMP0_1_IRQHandler
  .thumb_set CMP0_1_IRQHandler,Default_Handler

  .weak CTC_IRQHandler
  .thumb_set CTC_IRQHandler,Default_Handler

  .weak RAMECCMU_IRQHandler
  .thumb_set RAMECCMU_IRQHandler,Default_Handler

  .weak SAI3_IRQHandler
  .thumb_set SAI3_IRQHandler,Default_Handler

  .weak OSPI1_IRQHandler
  .thumb_set OSPI1_IRQHandler,Default_Handler

  .weak RTDEC0_IRQHandler
  .thumb_set RTDEC0_IRQHandler,Default_Handler

  .weak RTDEC1_IRQHandler
  .thumb_set RTDEC1_IRQHandler,Default_Handler

  .weak FAC_IRQHandler
  .thumb_set FAC_IRQHandler,Default_Handler

  .weak TMU_IRQHandler
  .thumb_set TMU_IRQHandler,Default_Handler

  .weak FFT_IRQHandler
  .thumb_set FFT_IRQHandler,Default_Handler

  .weak ESC_SYNC0_IRQHandler
  .thumb_set ESC_SYNC0_IRQHandler,Default_Handler

  .weak ESC_SYNC1_IRQHandler
  .thumb_set ESC_SYNC1_IRQHandler,Default_Handler

  .weak ESC_IRQHandler
  .thumb_set ESC_IRQHandler,Default_Handler

  .weak TIMER22_IRQHandler
  .thumb_set TIMER22_IRQHandler,Default_Handler

  .weak TIMER23_IRQHandler
  .thumb_set TIMER23_IRQHandler,Default_Handler

  .weak TIMER30_IRQHandler
  .thumb_set TIMER30_IRQHandler,Default_Handler

  .weak TIMER31_IRQHandler
  .thumb_set TIMER31_IRQHandler,Default_Handler

  .weak TIMER40_IRQHandler
  .thumb_set TIMER40_IRQHandler,Default_Handler

  .weak TIMER41_IRQHandler
  .thumb_set TIMER41_IRQHandler,Default_Handler

  .weak TIMER42_IRQHandler
  .thumb_set TIMER42_IRQHandler,Default_Handler

  .weak TIMER43_IRQHandler
  .thumb_set TIMER43_IRQHandler,Default_Handler

  .weak TIMER44_IRQHandler
  .thumb_set TIMER44_IRQHandler,Default_Handler

  .weak TIMER50_IRQHandler
  .thumb_set TIMER50_IRQHandler,Default_Handler

  .weak TIMER51_IRQHandler
  .thumb_set TIMER51_IRQHandler,Default_Handler

  .weak USBHS1_EP1_OUT_IRQHandler
  .thumb_set USBHS1_EP1_OUT_IRQHandler,Default_Handler

  .weak USBHS1_EP1_IN_IRQHandler
  .thumb_set USBHS1_EP1_IN_IRQHandler,Default_Handler

  .weak USBHS1_WKUP_IRQHandler
  .thumb_set USBHS1_WKUP_IRQHandler,Default_Handler

  .weak USBHS1_IRQHandler
  .thumb_set USBHS1_IRQHandler,Default_Handler

  .weak ENET1_IRQHandler
  .thumb_set ENET1_IRQHandler,Default_Handler

  .weak ENET1_WKUP_IRQHandler
  .thumb_set ENET1_WKUP_IRQHandler,Default_Handler

  .weak CAN0_WKUP_IRQHandler
  .thumb_set CAN0_WKUP_IRQHandler,Default_Handler

  .weak CAN0_Message_IRQHandler
  .thumb_set CAN0_Message_IRQHandler,Default_Handler

  .weak CAN0_Busoff_IRQHandler
  .thumb_set CAN0_Busoff_IRQHandler,Default_Handler

  .weak CAN0_Error_IRQHandler
  .thumb_set CAN0_Error_IRQHandler,Default_Handler

  .weak CAN0_FastError_IRQHandler
  .thumb_set CAN0_FastError_IRQHandler,Default_Handler

  .weak CAN0_TEC_IRQHandler
  .thumb_set CAN0_TEC_IRQHandler,Default_Handler

  .weak CAN0_REC_IRQHandler
  .thumb_set CAN0_REC_IRQHandler,Default_Handler

  .weak CAN1_WKUP_IRQHandler
  .thumb_set CAN1_WKUP_IRQHandler,Default_Handler

  .weak CAN1_Message_IRQHandler
  .thumb_set CAN1_Message_IRQHandler,Default_Handler

  .weak CAN1_Busoff_IRQHandler
  .thumb_set CAN1_Busoff_IRQHandler,Default_Handler

  .weak CAN1_Error_IRQHandler
  .thumb_set CAN1_Error_IRQHandler,Default_Handler

  .weak CAN1_FastError_IRQHandler
  .thumb_set CAN1_FastError_IRQHandler,Default_Handler

  .weak CAN1_TEC_IRQHandler
  .thumb_set CAN1_TEC_IRQHandler,Default_Handler

  .weak CAN1_REC_IRQHandler
  .thumb_set CAN1_REC_IRQHandler,Default_Handler

  .weak CAN2_WKUP_IRQHandler
  .thumb_set CAN2_WKUP_IRQHandler,Default_Handler

  .weak CAN2_Message_IRQHandler
  .thumb_set CAN2_Message_IRQHandler,Default_Handler

  .weak CAN2_Busoff_IRQHandler
  .thumb_set CAN2_Busoff_IRQHandler,Default_Handler

  .weak CAN2_Error_IRQHandler
  .thumb_set CAN2_Error_IRQHandler,Default_Handler

  .weak CAN2_FastError_IRQHandler
  .thumb_set CAN2_FastError_IRQHandler,Default_Handler

  .weak CAN2_TEC_IRQHandler
  .thumb_set CAN2_TEC_IRQHandler,Default_Handler

  .weak CAN2_REC_IRQHandler
  .thumb_set CAN2_REC_IRQHandler,Default_Handler

  .weak OTP_IRQHandler
  .thumb_set OTP_IRQHandler,Default_Handler

  .weak I2C0_WKUP_IRQHandler
  .thumb_set I2C0_WKUP_IRQHandler,Default_Handler

  .weak I2C1_WKUP_IRQHandler
  .thumb_set I2C1_WKUP_IRQHandler,Default_Handler

  .weak I2C2_WKUP_IRQHandler
  .thumb_set I2C2_WKUP_IRQHandler,Default_Handler

  .weak I2C3_WKUP_IRQHandler
  .thumb_set I2C3_WKUP_IRQHandler,Default_Handler

  .weak LPDTS_IRQHandler
  .thumb_set LPDTS_IRQHandler,Default_Handler

  .weak LPDTS_WKUP_IRQHandler
  .thumb_set LPDTS_WKUP_IRQHandler,Default_Handler

  .weak TIMER0_DEC_IRQHandler
  .thumb_set TIMER0_DEC_IRQHandler,Default_Handler

  .weak TIMER7_DEC_IRQHandler
  .thumb_set TIMER7_DEC_IRQHandler,Default_Handler

  .weak TIMER1_DEC_IRQHandler
  .thumb_set TIMER1_DEC_IRQHandler,Default_Handler

  .weak TIMER2_DEC_IRQHandler
  .thumb_set TIMER2_DEC_IRQHandler,Default_Handler

  .weak TIMER3_DEC_IRQHandler
  .thumb_set TIMER3_DEC_IRQHandler,Default_Handler

  .weak TIMER4_DEC_IRQHandler
  .thumb_set TIMER4_DEC_IRQHandler,Default_Handler

  .weak TIMER22_DEC_IRQHandler
  .thumb_set TIMER22_DEC_IRQHandler,Default_Handler

  .weak TIMER23_DEC_IRQHandler
  .thumb_set TIMER23_DEC_IRQHandler,Default_Handler

  .weak TIMER30_DEC_IRQHandler
  .thumb_set TIMER30_DEC_IRQHandler,Default_Handler

  .weak TIMER31_DEC_IRQHandler
  .thumb_set TIMER31_DEC_IRQHandler,Default_Handler

  .weak CPU_DCACHE_ERR_IRQHandler
  .thumb_set CPU_DCACHE_ERR_IRQHandler,Default_Handler

  .weak CPU_ICACHE_ERR_IRQHandler
  .thumb_set CPU_ICACHE_ERR_IRQHandler,Default_Handler

  .weak VOVD_VUVD_FILTER_IRQHandler
  .thumb_set VOVD_VUVD_FILTER_IRQHandler,Default_Handler

  .weak TIMER0_Channel_BRK_IRQHandler
  .thumb_set TIMER0_Channel_BRK_IRQHandler,Default_Handler

  .weak TIMER7_Channel_BRK_IRQHandler
  .thumb_set TIMER7_Channel_BRK_IRQHandler,Default_Handler

  .weak DSI_IRQHandler
  .thumb_set DSI_IRQHandler,Default_Handler

  .weak PKCAU_IRQHandler
  .thumb_set PKCAU_IRQHandler,Default_Handler

  .weak ESC_BRIDGE_IRQHandler
  .thumb_set ESC_BRIDGE_IRQHandler,Default_Handler

  .weak EDIM_IRQHandler
  .thumb_set EDIM_IRQHandler,Default_Handler
