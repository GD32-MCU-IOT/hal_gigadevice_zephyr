;/*!
;    \file    startup_gd32h77x_78x.s
;    \brief   start up file
;
;    \version 2026-11-09, V1.0.0, firmware for GD32H77x_78x
;*/

;/*
; * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
; * Copyright (c) 2026, GigaDevice Semiconductor Inc.
; *
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

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00001000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000800

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


;               /* reset Vector Mapped to at Address 0 */
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                                 ; Top of Stack
                DCD     Reset_Handler                                ; Reset Handler
                DCD     NMI_Handler                                  ; NMI Handler
                DCD     HardFault_Handler                            ; Hard Fault Handler
                DCD     MemManage_Handler                            ; MPU Fault Handler
                DCD     BusFault_Handler                             ; Bus Fault Handler
                DCD     UsageFault_Handler                           ; Usage Fault Handler
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     SVC_Handler                                  ; SVCall Handler
                DCD     DebugMon_Handler                             ; Debug Monitor Handler
                DCD     0                                            ; Reserved
                DCD     PendSV_Handler                               ; PendSV Handler
                DCD     SysTick_Handler                              ; SysTick Handler

                ; External Interrupts
                DCD     WWDGT_IRQHandler                             ; 16:WWDGT interrupt
                DCD     VAVD_LVD_VOVD_VUVD_IRQHandler                ; 17:VAVD / LVD / VOVD / VUVD through exti line detection interrupt
                DCD     TAMPER_STAMP_LXTAL_IRQHandler                ; 18:RTC tamper and timestamp from EXTI interrupt, LXTAL clock stuck interrupt
                DCD     RTC_WKUP_IRQHandler                          ; 19:RTC wakeup from EXTI interrupt
                DCD     NVMC_IRQHandler                              ; 20:NVMC global interrupt
                DCD     RCU_IRQHandler                               ; 21:RCU global interrupt
                DCD     EXTI0_IRQHandler                             ; 22:EXTI line0 interrupt
                DCD     EXTI1_IRQHandler                             ; 23:EXTI line1 interrupt
                DCD     EXTI2_IRQHandler                             ; 24:EXTI line2 interrupt
                DCD     EXTI3_IRQHandler                             ; 25:EXTI line3 interrupt
                DCD     EXTI4_IRQHandler                             ; 26:EXTI line4 interrupt
                DCD     DMA0_Channel0_IRQHandler                     ; 27:DMA0 channel0 global interrupt
                DCD     DMA0_Channel1_IRQHandler                     ; 28:DMA0 channel1 global interrupt
                DCD     DMA0_Channel2_IRQHandler                     ; 29:DMA0 channel2 global interrupt
                DCD     DMA0_Channel3_IRQHandler                     ; 30:DMA0 channel3 global interrupt
                DCD     DMA0_Channel4_IRQHandler                     ; 31:DMA0 channel4 global interrupt
                DCD     DMA0_Channel5_IRQHandler                     ; 32:DMA0 channel5 global interrupt
                DCD     DMA0_Channel6_IRQHandler                     ; 33:DMA0 channel6 global interrupt
                DCD     ADC0_1_RDCM_IRQHandler                       ; 34:ADC0 and ADC1 global interrupt, RDCM global interrupt
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     EXTI5_9_IRQHandler                           ; 39:EXTI line5-9 interrupt
                DCD     TIMER0_BRK_IRQHandler                        ; 40:TIMER0 break interrupt
                DCD     TIMER0_UP_IRQHandler                         ; 41:TIMER0 update interrupt
                DCD     TIMER0_TRG_CMT_IRQHandler                    ; 42:TIMER0 trigger and commutation interrupt
                DCD     TIMER0_Channel_IRQHandler                    ; 43:TIMER0 capture compare interrupt
                DCD     TIMER1_IRQHandler                            ; 44:TIMER1 global interrupt
                DCD     TIMER2_IRQHandler                            ; 45:TIMER2 global interrupt
                DCD     TIMER3_IRQHandler                            ; 46:TIMER3 global interrupt
                DCD     I2C0_EV_IRQHandler                           ; 47:I2C0 event interrupt
                DCD     I2C0_ER_IRQHandler                           ; 48:I2C0 error interrupt
                DCD     I2C1_EV_IRQHandler                           ; 49:I2C1 event interrupt
                DCD     I2C1_ER_IRQHandler                           ; 50:I2C1 error interrupt
                DCD     SPI0_IRQHandler                              ; 51:SPI0 global interrupt
                DCD     SPI1_IRQHandler                              ; 52:SPI1 global interrupt
                DCD     USART0_IRQHandler                            ; 53:USART0 global and wakeup interrupt
                DCD     USART1_IRQHandler                            ; 54:USART1 global and wakeup interrupt
                DCD     USART2_IRQHandler                            ; 55:USART2 global and wakeup interrupt
                DCD     EXTI10_15_IRQHandler                         ; 56:EXTI line10-15 interrupt
                DCD     RTC_Alarm_IRQHandler                         ; 57:RTC alarm from EXTI interrupt
                DCD     0                                            ; Reserved
                DCD     TIMER7_BRK_IRQHandler                        ; 59:TIMER7 break interrupt
                DCD     TIMER7_UP_IRQHandler                         ; 60:TIMER7 update interrupt
                DCD     TIMER7_TRG_CMT_IRQHandler                    ; 61:TIMER7 trigger and commutation interrupt
                DCD     TIMER7_Channel_IRQHandler                    ; 62:TIMER7 capture compare interrupt
                DCD     DMA0_Channel7_IRQHandler                     ; 63:DMA0 channel7 global interrupt
                DCD     EXMC_IRQHandler                              ; 64:EXMC global interrupt
                DCD     SDIO0_IRQHandler                             ; 65:SDIO0 global interrupt
                DCD     TIMER4_IRQHandler                            ; 66:TIMER4 global interrupt
                DCD     SPI2_IRQHandler                              ; 67:SPI2 global interrupt
                DCD     UART3_IRQHandler                             ; 68:UART3 global interrupt
                DCD     UART4_IRQHandler                             ; 69:UART4 global interrupt
                DCD     TIMER5_DAC_UDR_IRQHandler                    ; 70:TIMER5 global interrupt and DAC underrun error interrupt
                DCD     TIMER6_IRQHandler                            ; 71:TIMER6 global interrupt
                DCD     DMA1_Channel0_IRQHandler                     ; 72:DMA1 channel0 global interrupt
                DCD     DMA1_Channel1_IRQHandler                     ; 73:DMA1 channel1 global interrupt
                DCD     DMA1_Channel2_IRQHandler                     ; 74:DMA1 channel2 global interrupt
                DCD     DMA1_Channel3_IRQHandler                     ; 75:DMA1 channel3 global interrupt
                DCD     DMA1_Channel4_IRQHandler                     ; 76:DMA1 channel4 global interrupt
                DCD     ENET0_IRQHandler                             ; 77:ENET0 global interrupt
                DCD     ENET0_WKUP_IRQHandler                        ; 78:ENET0 wakeup from EXTI interrupt
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     DMA1_Channel5_IRQHandler                     ; 84:DMA1 channel5 global interrupt
                DCD     DMA1_Channel6_IRQHandler                     ; 85:DMA1 channel6 global interrupt
                DCD     DMA1_Channel7_IRQHandler                     ; 86:DMA1 channel7 global interrupt
                DCD     USART5_IRQHandler                            ; 87:USART5 global and wakeup interrupt
                DCD     I2C2_EV_IRQHandler                           ; 88:I2C2 event interrupt
                DCD     I2C2_ER_IRQHandler                           ; 89:I2C2 error interrupt
                DCD     USBHS0_EP1_OUT_IRQHandler                    ; 90:USBHS0 endpoint 1 out interrupt
                DCD     USBHS0_EP1_IN_IRQHandler                     ; 91:USBHS0 endpoint 1 in interrupt
                DCD     USBHS0_WKUP_IRQHandler                       ; 92:USBHS0 wakeup from EXTI interrupt
                DCD     USBHS0_IRQHandler                            ; 93:USBHS0 global interrupt
                DCD     DCI_IRQHandler                               ; 94:DCI global interrupt
                DCD     CAU_IRQHandler                               ; 95:CAU global interrupt
                DCD     HAU_TRNG_IRQHandler                          ; 96:HAU and TRNG global interrupt
                DCD     FPU_IRQHandler                               ; 97:FPU global interrupt
                DCD     UART6_IRQHandler                             ; 98:UART6 global interrupt
                DCD     UART7_IRQHandler                             ; 99:UART7 global interrupt
                DCD     SPI3_IRQHandler                              ; 100:SPI3 global interrupt
                DCD     SPI4_IRQHandler                              ; 101:SPI4 global interrupt
                DCD     SPI5_IRQHandler                              ; 102:SPI5 global interrupt
                DCD     SAI0_IRQHandler                              ; 103:SAI0 global interrupt
                DCD     TLI_IRQHandler                               ; 104:TLI global interrupt
                DCD     TLI_ER_IRQHandler                            ; 105:TLI error interrupt
                DCD     IPA_IRQHandler                               ; 106:IPA global interrupt
                DCD     SAI1_IRQHandler                              ; 107:SAI1 global interrupt
                DCD     OSPI0_IRQHandler                             ; 108:OSPI0 global interrupt
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     I2C3_EV_IRQHandler                           ; 111:I2C3 event interrupt
                DCD     I2C3_ER_IRQHandler                           ; 112:I2C3 error interrupt
                DCD     RSPDIF_IRQHandler                            ; 113:RSPDIF global interrupt
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     DMAMUX_OVR_IRQHandler                        ; 118:DMAMUX overrun interrupt
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     HPDF_INT4_IRQHandler                         ; 125:HPDF global interrupt 4
                DCD     HPDF_INT0_IRQHandler                         ; 126:HPDF global interrupt 0
                DCD     HPDF_INT1_IRQHandler                         ; 127:HPDF global interrupt 1
                DCD     HPDF_INT2_IRQHandler                         ; 128:HPDF global interrupt 2
                DCD     HPDF_INT3_IRQHandler                         ; 129:HPDF global interrupt 3
                DCD     SAI2_IRQHandler                              ; 130:SAI2 global interrupt
                DCD     0                                            ; Reserved
                DCD     TIMER14_IRQHandler                           ; 132:TIMER14 global interrupt
                DCD     TIMER15_IRQHandler                           ; 133:TIMER15 global interrupt
                DCD     TIMER16_IRQHandler                           ; 134:TIMER16 global interrupt
                DCD     0                                            ; Reserved
                DCD     MDIO_IRQHandler                              ; 136:MDIO global interrupt
                DCD     0                                            ; Reserved
                DCD     MDMA_IRQHandler                              ; 138:MDMA global interrupt
                DCD     0                                            ; Reserved
                DCD     SDIO1_IRQHandler                             ; 140:SDIO1 global interrupt
                DCD     HWSEM_IRQHandler                             ; 141:HWSEM global interrupt
                DCD     0                                            ; Reserved
                DCD     ADC2_IRQHandler                              ; 143:ADC2 global interrupt
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     CMP0_1_IRQHandler                            ; 153:CMP0 and CMP1 global interrupt, CMP0 and CMP1 through EXTI line detection interrupt
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     CTC_IRQHandler                               ; 160:CTC interrupt
                DCD     RAMECCMU_IRQHandler                          ; 161:RAMECCMU global interrupt
                DCD     SAI3_IRQHandler                              ; 162:SAI3 global interrupt
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     OSPI1_IRQHandler                             ; 166:OSPI1 global interrupt
                DCD     RTDEC0_IRQHandler                            ; 167:RTDEC0 global interrupt
                DCD     RTDEC1_IRQHandler                            ; 168:RTDEC1 global interrupt
                DCD     FAC_IRQHandler                               ; 169:FAC global interrupt
                DCD     TMU_IRQHandler                               ; 170:TMU global interrupt
                DCD     FFT_IRQHandler                               ; 171:FFT global interrupt
                DCD     ESC_SYNC0_IRQHandler                         ; 172:ESC SYNC0 interrupt
                DCD     ESC_SYNC1_IRQHandler                         ; 173:ESC SYNC1 interrupt
                DCD     ESC_IRQHandler                               ; 174:ESC IRQ interrupt
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     TIMER22_IRQHandler                           ; 177:TIMER22 global interrupt
                DCD     TIMER23_IRQHandler                           ; 178:TIMER23 global interrupt
                DCD     TIMER30_IRQHandler                           ; 179:TIMER30 global interrupt
                DCD     TIMER31_IRQHandler                           ; 180:TIMER31 global interrupt
                DCD     TIMER40_IRQHandler                           ; 181:TIMER40 global interrupt
                DCD     TIMER41_IRQHandler                           ; 182:TIMER41 global interrupt
                DCD     TIMER42_IRQHandler                           ; 183:TIMER42 global interrupt
                DCD     TIMER43_IRQHandler                           ; 184:TIMER43 global interrupt
                DCD     TIMER44_IRQHandler                           ; 185:TIMER44 global interrupt
                DCD     TIMER50_IRQHandler                           ; 186:TIMER50 global interrupt
                DCD     TIMER51_IRQHandler                           ; 187:TIMER51 global interrupt
                DCD     USBHS1_EP1_OUT_IRQHandler                    ; 188:USBHS1 endpoint 1 out interrupt
                DCD     USBHS1_EP1_IN_IRQHandler                     ; 189:USBHS1 endpoint 1 in interrupt
                DCD     USBHS1_WKUP_IRQHandler                       ; 190:USBHS1 wakeup from EXTI interrupt
                DCD     USBHS1_IRQHandler                            ; 191:USBHS1 global interrupt
                DCD     ENET1_IRQHandler                             ; 192:ENET1 global interrupt
                DCD     ENET1_WKUP_IRQHandler                        ; 193:ENET1 wakeup from EXTI interrupt
                DCD     0                                            ; Reserved
                DCD     CAN0_WKUP_IRQHandler                         ; 195:CAN0 wakeup through EXTI line detection interrupt
                DCD     CAN0_Message_IRQHandler                      ; 196:CAN0 interrupt for message buffer
                DCD     CAN0_Busoff_IRQHandler                       ; 197:CAN0 interrupt for bus off / bus off done
                DCD     CAN0_Error_IRQHandler                        ; 198:CAN0 interrupt for error
                DCD     CAN0_FastError_IRQHandler                    ; 199:CAN0 interrupt for error in fast transmission
                DCD     CAN0_TEC_IRQHandler                          ; 200:CAN0 interrupt for transmit warning
                DCD     CAN0_REC_IRQHandler                          ; 201:CAN0 interrupt for receive warning
                DCD     CAN1_WKUP_IRQHandler                         ; 202:CAN1 wakeup through EXTI line detection interrupt
                DCD     CAN1_Message_IRQHandler                      ; 203:CAN1 interrupt for message buffer
                DCD     CAN1_Busoff_IRQHandler                       ; 204:CAN1 interrupt for bus off / bus off done
                DCD     CAN1_Error_IRQHandler                        ; 205:CAN1 interrupt for error
                DCD     CAN1_FastError_IRQHandler                    ; 206:CAN1 interrupt for error in fast transmission
                DCD     CAN1_TEC_IRQHandler                          ; 207:CAN1 interrupt for transmit warning
                DCD     CAN1_REC_IRQHandler                          ; 208:CAN1 interrupt for receive warning
                DCD     CAN2_WKUP_IRQHandler                         ; 209:CAN2 wakeup through EXTI line detection interrupt
                DCD     CAN2_Message_IRQHandler                      ; 210:CAN2 interrupt for message buffer
                DCD     CAN2_Busoff_IRQHandler                       ; 211:CAN2 interrupt for bus off / bus off done
                DCD     CAN2_Error_IRQHandler                        ; 212:CAN2 interrupt for error
                DCD     CAN2_FastError_IRQHandler                    ; 213:CAN2 interrupt for error in fast transmission
                DCD     CAN2_TEC_IRQHandler                          ; 214:CAN2 interrupt for transmit warning
                DCD     CAN2_REC_IRQHandler                          ; 215:CAN2 interrupt for receive warning
                DCD     OTP_IRQHandler                               ; 216:OTP global interrupt
                DCD     I2C0_WKUP_IRQHandler                         ; 217:I2C0 wakeup through EXTI line detection interrupt
                DCD     I2C1_WKUP_IRQHandler                         ; 218:I2C1 wakeup through EXTI line detection interrupt
                DCD     I2C2_WKUP_IRQHandler                         ; 219:I2C2 wakeup through EXTI line detection interrupt
                DCD     I2C3_WKUP_IRQHandler                         ; 220:I2C3 wakeup through EXTI line detection interrupt
                DCD     LPDTS_IRQHandler                             ; 221:LPDTS interrupt
                DCD     LPDTS_WKUP_IRQHandler                        ; 222:LPDTS wakeup through EXTI line detection interrupt
                DCD     TIMER0_DEC_IRQHandler                        ; 223:TIMER0 DEC interrupt
                DCD     TIMER7_DEC_IRQHandler                        ; 224:TIMER7 DEC interrupt
                DCD     TIMER1_DEC_IRQHandler                        ; 225:TIMER1 DEC interrupt
                DCD     TIMER2_DEC_IRQHandler                        ; 226:TIMER2 DEC interrupt
                DCD     TIMER3_DEC_IRQHandler                        ; 227:TIMER3 DEC interrupt
                DCD     TIMER4_DEC_IRQHandler                        ; 228:TIMER4 DEC interrupt
                DCD     TIMER22_DEC_IRQHandler                       ; 229:TIMER22 DEC interrupt
                DCD     TIMER23_DEC_IRQHandler                       ; 230:TIMER23 DEC interrupt
                DCD     TIMER30_DEC_IRQHandler                       ; 231:TIMER30 DEC interrupt
                DCD     TIMER31_DEC_IRQHandler                       ; 232:TIMER31 DEC interrupt
                DCD     CPU_DCACHE_ERR_IRQHandler                    ; 233:CPU D-Cache error detection interrupt
                DCD     CPU_ICACHE_ERR_IRQHandler                    ; 234:CPU I-Cache error detection interrupt
                DCD     VOVD_VUVD_FILTER_IRQHandler                  ; 235:VOVD / VUVD interrupt after digital filtering
                DCD     0                                            ; 236:Reserved
                DCD     TIMER0_Channel_BRK_IRQHandler                ; 237:TIMER0 channel break interrupt
                DCD     TIMER7_Channel_BRK_IRQHandler                ; 238:TIMER7 channel break interrupt
                DCD     DSI_IRQHandler                               ; 239:DSI global interrupt
                DCD     PKCAU_IRQHandler                             ; 240:PKCAU global interrupt
                DCD     ESC_BRIDGE_IRQHandler                        ; 241:ESC internal interrupt
                DCD     EDIM_IRQHandler                              ; 242:EDIM global interrupt

__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

;/* reset Handler */
Reset_Handler    PROC
                 EXPORT  Reset_Handler                    [WEAK]
                 IMPORT  SystemInit
                 IMPORT  __main
                 IMPORT |Image$$RW_IRAM1$$RW$$Base|

                 LDR     R0, =|Image$$RW_IRAM1$$RW$$Base|
                 ADD     R1, R0, #0x8000
                 LDR     R2, =0x0
MEM_INIT         STRD    R2, R2, [ R0 ] , #8
                 CMP     R0, R1
                 BNE     MEM_INIT

                 LDR     R0, =SystemInit
                 BLX     R0
                 LDR     R0, =__main
                 BX      R0
                 ENDP

;/* dummy Exception Handlers */
NMI_Handler\
                PROC
                EXPORT  NMI_Handler                       [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler                 [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler                 [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler                  [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler                [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                       [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler                  [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                    [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                   [WEAK]
                B       .
                ENDP                                     
                                                          
Default_Handler PROC                                      
;               /* external interrupts handler */
                EXPORT  WWDGT_IRQHandler                  [WEAK]
                EXPORT  VAVD_LVD_VOVD_VUVD_IRQHandler     [WEAK]
                EXPORT  TAMPER_STAMP_LXTAL_IRQHandler     [WEAK]
                EXPORT  RTC_WKUP_IRQHandler               [WEAK]
                EXPORT  NVMC_IRQHandler                   [WEAK]
                EXPORT  RCU_IRQHandler                    [WEAK]
                EXPORT  EXTI0_IRQHandler                  [WEAK]
                EXPORT  EXTI1_IRQHandler                  [WEAK]
                EXPORT  EXTI2_IRQHandler                  [WEAK]
                EXPORT  EXTI3_IRQHandler                  [WEAK]
                EXPORT  EXTI4_IRQHandler                  [WEAK]
                EXPORT  DMA0_Channel0_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel1_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel2_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel3_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel4_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel5_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel6_IRQHandler          [WEAK]
                EXPORT  ADC0_1_RDCM_IRQHandler            [WEAK]
                EXPORT  EXTI5_9_IRQHandler                [WEAK]
                EXPORT  TIMER0_BRK_IRQHandler             [WEAK]
                EXPORT  TIMER0_UP_IRQHandler              [WEAK]
                EXPORT  TIMER0_TRG_CMT_IRQHandler         [WEAK]
                EXPORT  TIMER0_Channel_IRQHandler         [WEAK]
                EXPORT  TIMER1_IRQHandler                 [WEAK]
                EXPORT  TIMER2_IRQHandler                 [WEAK]
                EXPORT  TIMER3_IRQHandler                 [WEAK]
                EXPORT  I2C0_EV_IRQHandler                [WEAK]
                EXPORT  I2C0_ER_IRQHandler                [WEAK]
                EXPORT  I2C1_EV_IRQHandler                [WEAK]
                EXPORT  I2C1_ER_IRQHandler                [WEAK]
                EXPORT  SPI0_IRQHandler                   [WEAK]
                EXPORT  SPI1_IRQHandler                   [WEAK]
                EXPORT  USART0_IRQHandler                 [WEAK]
                EXPORT  USART1_IRQHandler                 [WEAK]
                EXPORT  USART2_IRQHandler                 [WEAK]
                EXPORT  EXTI10_15_IRQHandler              [WEAK]
                EXPORT  RTC_Alarm_IRQHandler              [WEAK]
                EXPORT  TIMER7_BRK_IRQHandler             [WEAK]
                EXPORT  TIMER7_UP_IRQHandler              [WEAK]
                EXPORT  TIMER7_TRG_CMT_IRQHandler         [WEAK]
                EXPORT  TIMER7_Channel_IRQHandler         [WEAK]
                EXPORT  DMA0_Channel7_IRQHandler          [WEAK]
                EXPORT  EXMC_IRQHandler                   [WEAK]
                EXPORT  SDIO0_IRQHandler                  [WEAK]
                EXPORT  TIMER4_IRQHandler                 [WEAK]
                EXPORT  SPI2_IRQHandler                   [WEAK]
                EXPORT  UART3_IRQHandler                  [WEAK]
                EXPORT  UART4_IRQHandler                  [WEAK]
                EXPORT  TIMER5_DAC_UDR_IRQHandler         [WEAK]
                EXPORT  TIMER6_IRQHandler                 [WEAK]
                EXPORT  DMA1_Channel0_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler          [WEAK]
                EXPORT  ENET0_IRQHandler                  [WEAK]
                EXPORT  ENET0_WKUP_IRQHandler             [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler          [WEAK]
                EXPORT  USART5_IRQHandler                 [WEAK]
                EXPORT  I2C2_EV_IRQHandler                [WEAK]
                EXPORT  I2C2_ER_IRQHandler                [WEAK]
                EXPORT  USBHS0_EP1_OUT_IRQHandler         [WEAK]
                EXPORT  USBHS0_EP1_IN_IRQHandler          [WEAK]
                EXPORT  USBHS0_WKUP_IRQHandler            [WEAK]
                EXPORT  USBHS0_IRQHandler                 [WEAK]
                EXPORT  DCI_IRQHandler                    [WEAK]
                EXPORT  CAU_IRQHandler                    [WEAK]
                EXPORT  HAU_TRNG_IRQHandler               [WEAK]
                EXPORT  FPU_IRQHandler                    [WEAK]
                EXPORT  UART6_IRQHandler                  [WEAK]
                EXPORT  UART7_IRQHandler                  [WEAK]
                EXPORT  SPI3_IRQHandler                   [WEAK]
                EXPORT  SPI4_IRQHandler                   [WEAK]
                EXPORT  SPI5_IRQHandler                   [WEAK]
                EXPORT  SAI0_IRQHandler                   [WEAK]
                EXPORT  TLI_IRQHandler                    [WEAK]
                EXPORT  TLI_ER_IRQHandler                 [WEAK]
                EXPORT  IPA_IRQHandler                    [WEAK]
                EXPORT  SAI1_IRQHandler                   [WEAK]
                EXPORT  OSPI0_IRQHandler                  [WEAK]
                EXPORT  I2C3_EV_IRQHandler                [WEAK]
                EXPORT  I2C3_ER_IRQHandler                [WEAK]
                EXPORT  RSPDIF_IRQHandler                 [WEAK]
                EXPORT  DMAMUX_OVR_IRQHandler             [WEAK]
                EXPORT  HPDF_INT4_IRQHandler              [WEAK]
                EXPORT  HPDF_INT0_IRQHandler              [WEAK]
                EXPORT  HPDF_INT1_IRQHandler              [WEAK]
                EXPORT  HPDF_INT2_IRQHandler              [WEAK]
                EXPORT  HPDF_INT3_IRQHandler              [WEAK]
                EXPORT  SAI2_IRQHandler                   [WEAK]
                EXPORT  TIMER14_IRQHandler                [WEAK]
                EXPORT  TIMER15_IRQHandler                [WEAK]
                EXPORT  TIMER16_IRQHandler                [WEAK]
                EXPORT  MDIO_IRQHandler                   [WEAK]
                EXPORT  MDMA_IRQHandler                   [WEAK]
                EXPORT  SDIO1_IRQHandler                  [WEAK]
                EXPORT  HWSEM_IRQHandler                  [WEAK]
                EXPORT  ADC2_IRQHandler                   [WEAK]
                EXPORT  CMP0_1_IRQHandler                 [WEAK]
                EXPORT  CTC_IRQHandler                    [WEAK]
                EXPORT  RAMECCMU_IRQHandler               [WEAK]
                EXPORT  SAI3_IRQHandler                   [WEAK]
                EXPORT  OSPI1_IRQHandler                  [WEAK]
                EXPORT  RTDEC0_IRQHandler                 [WEAK]
                EXPORT  RTDEC1_IRQHandler                 [WEAK]
                EXPORT  FAC_IRQHandler                    [WEAK]
                EXPORT  TMU_IRQHandler                    [WEAK]
                EXPORT  FFT_IRQHandler                    [WEAK]
                EXPORT  ESC_SYNC0_IRQHandler              [WEAK]
                EXPORT  ESC_SYNC1_IRQHandler              [WEAK]
                EXPORT  ESC_IRQHandler                    [WEAK]
                EXPORT  TIMER22_IRQHandler                [WEAK]
                EXPORT  TIMER23_IRQHandler                [WEAK]
                EXPORT  TIMER30_IRQHandler                [WEAK]
                EXPORT  TIMER31_IRQHandler                [WEAK]
                EXPORT  TIMER40_IRQHandler                [WEAK]
                EXPORT  TIMER41_IRQHandler                [WEAK]
                EXPORT  TIMER42_IRQHandler                [WEAK]
                EXPORT  TIMER43_IRQHandler                [WEAK]
                EXPORT  TIMER44_IRQHandler                [WEAK]
                EXPORT  TIMER50_IRQHandler                [WEAK]
                EXPORT  TIMER51_IRQHandler                [WEAK]
                EXPORT  USBHS1_EP1_OUT_IRQHandler         [WEAK]
                EXPORT  USBHS1_EP1_IN_IRQHandler          [WEAK]
                EXPORT  USBHS1_WKUP_IRQHandler            [WEAK]
                EXPORT  USBHS1_IRQHandler                 [WEAK]
                EXPORT  ENET1_IRQHandler                  [WEAK]
                EXPORT  ENET1_WKUP_IRQHandler             [WEAK]
                EXPORT  CAN0_WKUP_IRQHandler              [WEAK]
                EXPORT  CAN0_Message_IRQHandler           [WEAK]
                EXPORT  CAN0_Busoff_IRQHandler            [WEAK]
                EXPORT  CAN0_Error_IRQHandler             [WEAK]
                EXPORT  CAN0_FastError_IRQHandler         [WEAK]
                EXPORT  CAN0_TEC_IRQHandler               [WEAK]
                EXPORT  CAN0_REC_IRQHandler               [WEAK]
                EXPORT  CAN1_WKUP_IRQHandler              [WEAK]
                EXPORT  CAN1_Message_IRQHandler           [WEAK]
                EXPORT  CAN1_Busoff_IRQHandler            [WEAK]
                EXPORT  CAN1_Error_IRQHandler             [WEAK]
                EXPORT  CAN1_FastError_IRQHandler         [WEAK]
                EXPORT  CAN1_TEC_IRQHandler               [WEAK]
                EXPORT  CAN1_REC_IRQHandler               [WEAK]
                EXPORT  CAN2_WKUP_IRQHandler              [WEAK]
                EXPORT  CAN2_Message_IRQHandler           [WEAK]
                EXPORT  CAN2_Busoff_IRQHandler            [WEAK]
                EXPORT  CAN2_Error_IRQHandler             [WEAK]
                EXPORT  CAN2_FastError_IRQHandler         [WEAK]
                EXPORT  CAN2_TEC_IRQHandler               [WEAK]
                EXPORT  CAN2_REC_IRQHandler               [WEAK]
                EXPORT  OTP_IRQHandler                    [WEAK]
                EXPORT  I2C0_WKUP_IRQHandler              [WEAK]
                EXPORT  I2C1_WKUP_IRQHandler              [WEAK]
                EXPORT  I2C2_WKUP_IRQHandler              [WEAK]
                EXPORT  I2C3_WKUP_IRQHandler              [WEAK]
                EXPORT  LPDTS_IRQHandler                  [WEAK]
                EXPORT  LPDTS_WKUP_IRQHandler             [WEAK]
                EXPORT  TIMER0_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER7_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER1_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER2_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER3_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER4_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER22_DEC_IRQHandler            [WEAK]
                EXPORT  TIMER23_DEC_IRQHandler            [WEAK]
                EXPORT  TIMER30_DEC_IRQHandler            [WEAK]
                EXPORT  TIMER31_DEC_IRQHandler            [WEAK]
                EXPORT  CPU_DCACHE_ERR_IRQHandler         [WEAK]
                EXPORT  CPU_ICACHE_ERR_IRQHandler         [WEAK]
                EXPORT  VOVD_VUVD_FILTER_IRQHandler       [WEAK]
                EXPORT  TIMER0_Channel_BRK_IRQHandler     [WEAK]
                EXPORT  TIMER7_Channel_BRK_IRQHandler     [WEAK]
                EXPORT  DSI_IRQHandler                    [WEAK]
                EXPORT  PKCAU_IRQHandler                  [WEAK]
                EXPORT  ESC_BRIDGE_IRQHandler             [WEAK]
                EXPORT  EDIM_IRQHandler                   [WEAK]

;/* external interrupts handler */
WWDGT_IRQHandler                  
VAVD_LVD_VOVD_VUVD_IRQHandler     
TAMPER_STAMP_LXTAL_IRQHandler     
RTC_WKUP_IRQHandler               
NVMC_IRQHandler                   
RCU_IRQHandler                    
EXTI0_IRQHandler                  
EXTI1_IRQHandler                  
EXTI2_IRQHandler                  
EXTI3_IRQHandler                  
EXTI4_IRQHandler                  
DMA0_Channel0_IRQHandler          
DMA0_Channel1_IRQHandler          
DMA0_Channel2_IRQHandler          
DMA0_Channel3_IRQHandler          
DMA0_Channel4_IRQHandler          
DMA0_Channel5_IRQHandler          
DMA0_Channel6_IRQHandler          
ADC0_1_RDCM_IRQHandler            
EXTI5_9_IRQHandler                
TIMER0_BRK_IRQHandler             
TIMER0_UP_IRQHandler              
TIMER0_TRG_CMT_IRQHandler         
TIMER0_Channel_IRQHandler         
TIMER1_IRQHandler                 
TIMER2_IRQHandler                 
TIMER3_IRQHandler                 
I2C0_EV_IRQHandler                
I2C0_ER_IRQHandler                
I2C1_EV_IRQHandler                
I2C1_ER_IRQHandler                
SPI0_IRQHandler                   
SPI1_IRQHandler                   
USART0_IRQHandler                 
USART1_IRQHandler                 
USART2_IRQHandler                 
EXTI10_15_IRQHandler              
RTC_Alarm_IRQHandler              
TIMER7_BRK_IRQHandler             
TIMER7_UP_IRQHandler              
TIMER7_TRG_CMT_IRQHandler         
TIMER7_Channel_IRQHandler         
DMA0_Channel7_IRQHandler          
EXMC_IRQHandler                   
SDIO0_IRQHandler                  
TIMER4_IRQHandler                 
SPI2_IRQHandler                   
UART3_IRQHandler                  
UART4_IRQHandler                  
TIMER5_DAC_UDR_IRQHandler         
TIMER6_IRQHandler                 
DMA1_Channel0_IRQHandler          
DMA1_Channel1_IRQHandler          
DMA1_Channel2_IRQHandler          
DMA1_Channel3_IRQHandler          
DMA1_Channel4_IRQHandler          
ENET0_IRQHandler                  
ENET0_WKUP_IRQHandler             
DMA1_Channel5_IRQHandler          
DMA1_Channel6_IRQHandler          
DMA1_Channel7_IRQHandler          
USART5_IRQHandler                 
I2C2_EV_IRQHandler                
I2C2_ER_IRQHandler                
USBHS0_EP1_OUT_IRQHandler         
USBHS0_EP1_IN_IRQHandler          
USBHS0_WKUP_IRQHandler            
USBHS0_IRQHandler                 
DCI_IRQHandler                    
CAU_IRQHandler                    
HAU_TRNG_IRQHandler               
FPU_IRQHandler                    
UART6_IRQHandler                  
UART7_IRQHandler                  
SPI3_IRQHandler                   
SPI4_IRQHandler                   
SPI5_IRQHandler                   
SAI0_IRQHandler                   
TLI_IRQHandler                    
TLI_ER_IRQHandler                 
IPA_IRQHandler                    
SAI1_IRQHandler                   
OSPI0_IRQHandler                  
I2C3_EV_IRQHandler                
I2C3_ER_IRQHandler                
RSPDIF_IRQHandler                 
DMAMUX_OVR_IRQHandler             
HPDF_INT4_IRQHandler              
HPDF_INT0_IRQHandler              
HPDF_INT1_IRQHandler              
HPDF_INT2_IRQHandler              
HPDF_INT3_IRQHandler              
SAI2_IRQHandler                   
TIMER14_IRQHandler                
TIMER15_IRQHandler                
TIMER16_IRQHandler                
MDIO_IRQHandler                   
MDMA_IRQHandler                   
SDIO1_IRQHandler                  
HWSEM_IRQHandler                  
ADC2_IRQHandler                   
CMP0_1_IRQHandler                 
CTC_IRQHandler                    
RAMECCMU_IRQHandler               
SAI3_IRQHandler                   
OSPI1_IRQHandler                  
RTDEC0_IRQHandler                 
RTDEC1_IRQHandler                 
FAC_IRQHandler                    
TMU_IRQHandler                    
FFT_IRQHandler                    
ESC_SYNC0_IRQHandler              
ESC_SYNC1_IRQHandler              
ESC_IRQHandler                    
TIMER22_IRQHandler                
TIMER23_IRQHandler                
TIMER30_IRQHandler                
TIMER31_IRQHandler                
TIMER40_IRQHandler                
TIMER41_IRQHandler                
TIMER42_IRQHandler                
TIMER43_IRQHandler                
TIMER44_IRQHandler                
TIMER50_IRQHandler                
TIMER51_IRQHandler                
USBHS1_EP1_OUT_IRQHandler         
USBHS1_EP1_IN_IRQHandler          
USBHS1_WKUP_IRQHandler            
USBHS1_IRQHandler                 
ENET1_IRQHandler                  
ENET1_WKUP_IRQHandler             
CAN0_WKUP_IRQHandler              
CAN0_Message_IRQHandler           
CAN0_Busoff_IRQHandler            
CAN0_Error_IRQHandler             
CAN0_FastError_IRQHandler         
CAN0_TEC_IRQHandler               
CAN0_REC_IRQHandler               
CAN1_WKUP_IRQHandler              
CAN1_Message_IRQHandler           
CAN1_Busoff_IRQHandler            
CAN1_Error_IRQHandler             
CAN1_FastError_IRQHandler         
CAN1_TEC_IRQHandler               
CAN1_REC_IRQHandler               
CAN2_WKUP_IRQHandler              
CAN2_Message_IRQHandler           
CAN2_Busoff_IRQHandler            
CAN2_Error_IRQHandler             
CAN2_FastError_IRQHandler         
CAN2_TEC_IRQHandler               
CAN2_REC_IRQHandler               
OTP_IRQHandler                    
I2C0_WKUP_IRQHandler              
I2C1_WKUP_IRQHandler              
I2C2_WKUP_IRQHandler              
I2C3_WKUP_IRQHandler              
LPDTS_IRQHandler                  
LPDTS_WKUP_IRQHandler             
TIMER0_DEC_IRQHandler             
TIMER7_DEC_IRQHandler             
TIMER1_DEC_IRQHandler             
TIMER2_DEC_IRQHandler             
TIMER3_DEC_IRQHandler             
TIMER4_DEC_IRQHandler             
TIMER22_DEC_IRQHandler            
TIMER23_DEC_IRQHandler            
TIMER30_DEC_IRQHandler            
TIMER31_DEC_IRQHandler            
CPU_DCACHE_ERR_IRQHandler         
CPU_ICACHE_ERR_IRQHandler         
VOVD_VUVD_FILTER_IRQHandler       
TIMER0_Channel_BRK_IRQHandler     
TIMER7_Channel_BRK_IRQHandler     
DSI_IRQHandler                    
PKCAU_IRQHandler                  
ESC_BRIDGE_IRQHandler             
EDIM_IRQHandler                   


                B       .

                ENDP

                ALIGN

; user Initial Stack & Heap

                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

