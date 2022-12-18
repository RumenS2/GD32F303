/*!
    \file  gd32f30x_it.c
    \brief interrupt service routines

    \version 2021-03-23, V2.0.0, demo for GD32F30x
*/

/*
    Copyright (c) 2021, GigaDevice Semiconductor Inc.

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

#include "gd32f30x_it.h"
#include "hw_config.h"
#include "Errors.h"
#include "variables.h"

volatile uint16_t EnableTasking=0;
volatile uint32_t SysTickCntr=0;
volatile uint32_t LocErrorFlags;

/*!
    \brief      this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
	LocErrorFlags|=iEF_NMI_Error;
}

/*!
    \brief      this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    while (1){
    }
}

/*!
    \brief      this function handles MemManage exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MemManage_Handler(void)
{
    /* if Memory Manage exception occurs, go to infinite loop */
    while (1){
    }
}

/*!
    \brief      this function handles BusFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void BusFault_Handler(void)
{
    /* if Bus Fault exception occurs, go to infinite loop */
    while (1){
    }
}

/*!
    \brief      this function handles UsageFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UsageFault_Handler(void)
{
    /* if Usage Fault exception occurs, go to infinite loop */
    while (1){
    }
}

/*!
    \brief      this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void)
{
}

/*!
    \brief      this function handles DebugMon exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void DebugMon_Handler(void)
{
}

/*!
    \brief      this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PendSV_Handler(void)
{
}

/*!
    \brief      this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/

uint32_t LastKeyPressedCnt;
volatile uint32_t SACntrLo,SBCntrLo,SACntrHi,SBCntrHi;
volatile int32_t UPCntr,DNCntr,LFCntr,RGCntr,S5Cntr,CurrentPosition,DirectionSignIs;
volatile uint32_t BeepCounter;
volatile int32_t locCurrentPosition=0;


void SysTick_Handler(void)
{
	  /* USER CODE BEGIN SysTick_IRQn 0 */
		SysTickCntr++; //SysTick is incremented every 100us

		  static uint8_t NewEnC=0,OldEnC=0;

		  LastKeyPressedCnt++;
		  if (LastKeyPressedCnt>(1<<22))
		  {
		    LastKeyPressedCnt--; //prevent overflow after 1-2 days
		  }
		  if (iMState.RunFlag<0x80) goto no_in_manual;
		  //==========NEW===========================
		  if (Get_LEFT==0) {LFCntr++;LastKeyPressedCnt=0;} else LFCntr>>=1;
		  if (Get_DOWN==0)  {DNCntr++;LastKeyPressedCnt=0;} else DNCntr>>=1;
		  if (Get_RIGHT==0) {RGCntr++;LastKeyPressedCnt=0;} else RGCntr>>=1;
		  if (Get_UP==0) {UPCntr++;LastKeyPressedCnt=0;} else UPCntr>>=1;
		  //==========================================


		  if (Get_CENTER==0) {S5Cntr++;LastKeyPressedCnt=0;} else S5Cntr>>=1;
		  if (Get_ChA==0) {SACntrLo++;SACntrHi>>=1;} else {SACntrHi++;SACntrLo>>=1;}
		  if (Get_ChB==0) {SBCntrLo++;SBCntrHi>>=1;} else {SBCntrHi++;SBCntrLo>>=1;}


		     if (SACntrHi==10) {NewEnC|=0x01;}
		     if (SACntrLo==10) {NewEnC&=~0x01;}
		     if (SBCntrHi==10) {NewEnC|=0x02;}
		     if (SBCntrLo==10) {NewEnC&=~0x02;}
		  //not needed, CurrentPosition is restored with big delay   if (EncFirstRun<10) {OldEnC=NewEnC;EncFirstRun++;}
		     if (NewEnC==OldEnC) {goto NoEncChg;}
		     LastKeyPressedCnt=0;
		     if ((NewEnC>>1)^(OldEnC&0x01))  //NewEnc.bit1 XOR OldEnc.bit0
		     {locCurrentPosition++;DirectionSignIs=1;}  //DirectionSignIs is +1 or -1
		     else
		     {locCurrentPosition--;DirectionSignIs=-1;} //DirectionSignIs is +1 or -1
		     OldEnC=NewEnC;
		  NoEncChg:;
		   CurrentPosition=locCurrentPosition>>2;

		no_in_manual:;

		  /* USER CODE BEGIN SysTick_IRQn 1 */

		if (BeepCounter) BeepCounter--;
		if (EnableTasking!=0x10) goto exii;
		extern void AnalisRS(void);
		AnalisRS();

	 /* USER CODE END SysTick_IRQn 1 */
	exii:;

}
