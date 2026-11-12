/*!
    \file    gd32h77x_78x_hwsem.c
    \brief   HWSEM driver

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

#include "gd32h77x_78x_hwsem.h"

#define HWSEM_SEM_MASK         ((uint32_t)0x0000001FU)    /* bit mask of HWSEM semaphore index */

/*!
    \brief      try to lock the specific semaphore by writing process ID (API_ID(0x0001U))
    \param[in]  semaphore: semaphore index
                only one parameter can be selected which is shown as below:
      \arg        0 - 0x1F
    \param[in]  process: the process to lock the semaphore
                only one parameter can be selected which is shown as below:
      \arg        0 - 0xFF
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hwsem_lock_set(uint32_t semaphore, uint32_t process)
{
    ErrStatus ret = ERROR;

    semaphore = semaphore & HWSEM_SEM_MASK;
    process = process & HWSEM_CTL_PID;
    /* try to lock the semaphore */
    HWSEM_CTL(semaphore) = HWSEM_LOCK | CTL_MID(HWSEM_CPU_MASTER_ID) | process;

    /* read the control register to confirm the semaphore is locked by target process or not */
    if((HWSEM_LOCK | CTL_MID(HWSEM_CPU_MASTER_ID) | process) == HWSEM_CTL(semaphore)) {
        ret = SUCCESS;
    } else {
        /* do nothing */
    }

    return ret;
}

/*!
    \brief      try to release the lock of the semaphore by writing process ID (API_ID(0x0002U))
    \param[in]  semaphore: semaphore index
                only one parameter can be selected which is shown as below:
      \arg        0 - 0x1F
    \param[in]  process: the process to unlock the semaphore
                only one parameter can be selected which is shown as below:
      \arg        0 - 0xFF
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hwsem_lock_release(uint32_t semaphore, uint32_t process)
{
    ErrStatus ret = ERROR;

    semaphore = semaphore & HWSEM_SEM_MASK;
    process = process & HWSEM_CTL_PID;
    HWSEM_CTL(semaphore) = CTL_MID(HWSEM_CPU_MASTER_ID) | process;

    /* read the control register to confirm the LK bit is cleared */
    if(0U == (HWSEM_CTL(semaphore) & HWSEM_LOCK)) {
        ret = SUCCESS;
    } else {
        /* do nothing */
    }

    return ret;
}

/*!
    \brief      try to lock the semaphore by reading (API_ID(0x0003U))
    \param[in]  semaphore: semaphore index
                only one parameter can be selected which is shown as below:
      \arg        0 - 0x1F
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hwsem_lock_by_reading(uint32_t semaphore)
{
    ErrStatus ret = ERROR;

    semaphore = semaphore & HWSEM_SEM_MASK;
    if((HWSEM_LOCK | CTL_MID(HWSEM_CPU_MASTER_ID)) == HWSEM_RLK(semaphore)) {
        ret = SUCCESS;
    } else {
        /* do nothing */
    }

    return ret;
}

/*!
    \brief      unlock all semaphores of the master ID (API_ID(0x0004U))
    \param[in]  key: key value
                only one parameter can be selected which is shown as below:
      \arg        0 - 0xFFFF
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hwsem_unlock_all(uint32_t key)
{
    ErrStatus ret = ERROR;
    HWSEM_UNLK = UNLK_KEY(key) | (UNLK_MID(HWSEM_CPU_MASTER_ID) & HWSEM_UNLK_MID);

    if(key == GET_KEY_KEY(HWSEM_KEY)) {
        ret = SUCCESS;
    } else {
        /* do nothing */
    }
    return ret;
}

/*!
    \brief      get process ID of the specific semaphore (API_ID(0x0005U))
    \param[in]  semaphore: semaphore index
                only one parameter can be selected which is shown as below:
      \arg        0 - 0x1F
    \param[out] none
    \retval     uint32_t: process ID of semaphore
*/
uint32_t hwsem_process_id_get(uint32_t semaphore)
{
    return (HWSEM_CTL(semaphore & HWSEM_SEM_MASK) & HWSEM_CTL_PID);
}

/*!
    \brief      get master ID of the specific semaphore (API_ID(0x0006U))
    \param[in]  semaphore: semaphore index
                only one parameter can be selected which is shown as below:
      \arg        0 - 0x1F
    \param[out] none
    \retval     uint32_t: master ID of semaphore
*/
uint32_t hwsem_master_id_get(uint32_t semaphore)
{
    return (GET_CTL_MID(HWSEM_CTL(semaphore & HWSEM_SEM_MASK)));
}

/*!
    \brief      get the lock status of the semaphore (API_ID(0x0007U))
    \param[in]  semaphore: semaphore index
                only one parameter can be selected which is shown as below:
      \arg        0 - 0x1F
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hwsem_lock_status_get(uint32_t semaphore)
{
    FlagStatus ret = RESET;

    if(0U != (HWSEM_CTL(semaphore & HWSEM_SEM_MASK) & HWSEM_LOCK)) {
        ret = SET;
    } else {
        /* do nothing */
    }

    return ret;
}

/*!
    \brief      set the key (API_ID(0x0008U))
    \param[in]  key: key value
                only one parameter can be selected which is shown as below:
      \arg        0 - 0xFFFF
    \param[out] none
    \retval     none
*/
void hwsem_key_set(uint32_t key)
{
    HWSEM_KEY = KEY_KEY(key);
}

/*!
    \brief      get the key (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     uint32_t: key to unlock all semaphores
*/
uint32_t hwsem_key_get(void)
{
    return (GET_KEY_KEY(HWSEM_KEY));
}

/*!
    \brief      get the HWSEM flag status (API_ID(0x000AU))
    \param[in]  semaphore: semaphore index
                only one parameter can be selected which is shown as below:
      \arg        0 - 0x1F
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hwsem_flag_get(uint32_t semaphore)
{
    FlagStatus ret = RESET;

    semaphore = semaphore & HWSEM_SEM_MASK;
    if(0U != ((HWSEM_STAT >> semaphore) & 0x1U)) {
        ret = SET;
    } else {
        /* do nothing */
    }

    return ret;
}

/*!
    \brief      clear HWSEM flag status (API_ID(0x000BU))
    \param[in]  semaphore: semaphore index
                only one parameter can be selected which is shown as below:
      \arg        0 - 0x1F
    \param[out] none
    \retval     none
*/
void hwsem_flag_clear(uint32_t semaphore)
{
    HWSEM_INTC = ((uint32_t)1U << (semaphore & HWSEM_SEM_MASK));
}

/*!
    \brief      get HWSEM interrupt flag status (API_ID(0x000CU))
    \param[in]  semaphore: semaphore index
                only one parameter can be selected which is shown as below:
      \arg        0 - 0x1F
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hwsem_interrupt_flag_get(uint32_t semaphore)
{
    FlagStatus ret = RESET;

    semaphore = semaphore & HWSEM_SEM_MASK;
    if(0U != ((HWSEM_INTF >> semaphore) & 0x1U)) {
        ret = SET;
    } else {
        /* do nothing */
    }

    return ret;
}

/*!
    \brief      clear HWSEM interrupt flag (API_ID(0x000DU))
    \param[in]  semaphore: semaphore index
                only one parameter can be selected which is shown as below:
      \arg        0 - 0x1F
    \param[out] none
    \retval     none
*/
void hwsem_interrupt_flag_clear(uint32_t semaphore)
{
    HWSEM_INTC = ((uint32_t)1U << (semaphore & HWSEM_SEM_MASK));
}

/*!
    \brief      enable HWSEM interrupt (API_ID(0x000EU))
    \param[in]  semaphore: semaphore index
                only one parameter can be selected which is shown as below:
      \arg        0 - 0x1F
    \param[out] none
    \retval     none
*/
void hwsem_interrupt_enable(uint32_t semaphore)
{
    HWSEM_INTEN |= ((uint32_t)1U << (semaphore & HWSEM_SEM_MASK));
}

/*!
    \brief      disable HWSEM interrupt (API_ID(0x000FU))
    \param[in]  semaphore: semaphore index
                only one parameter can be selected which is shown as below:
      \arg        0 - 0x1F
    \param[out] none
    \retval     none
*/
void hwsem_interrupt_disable(uint32_t semaphore)
{
    HWSEM_INTEN &= (uint32_t)(~((uint32_t)1U << (semaphore & HWSEM_SEM_MASK)));
}
