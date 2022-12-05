/*!
    \file    fmc_operation.c
    \brief   flash program, erase
    
    \version 2016-08-15, V1.0.0, firmware for GD32F4xx
    \version 2018-12-12, V2.0.0, firmware for GD32F4xx
    \version 2020-09-30, V2.1.0, firmware for GD32F4xx
    \version 2022-03-09, V3.0.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

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

#include <EE_EMUL.h>
#include "gd32f30x.h"

//! device with memory <=512kb have only bank0 with 2kb pages
//! device with memory >512kb have additional bank1 with 4kb pages for addresses >512kb

#define FMC_PAGE_SIZE           ((uint16_t)0x800U)


void fmc_erase_pages(uint32_t StartAddr,uint32_t EndAddr)
{
	uint32_t	PageNum = (EndAddr - StartAddr) / FMC_PAGE_SIZE;
//	uint32_t	WordNum = ((EndAddr - StartAddr) >> 2);
    uint32_t 	EraseCounter=0;

    /* unlock the flash program/erase controller */
    fmc_unlock();

    /* clear all pending flags */
    fmc_flag_clear(FMC_FLAG_BANK0_END);
    fmc_flag_clear(FMC_FLAG_BANK0_WPERR);
    fmc_flag_clear(FMC_FLAG_BANK0_PGERR);

pak:;
        fmc_page_erase(StartAddr + (FMC_PAGE_SIZE * EraseCounter));
        fmc_flag_clear(FMC_FLAG_BANK0_END);
        fmc_flag_clear(FMC_FLAG_BANK0_WPERR);
        fmc_flag_clear(FMC_FLAG_BANK0_PGERR);
    if (EraseCounter < PageNum) {EraseCounter++;goto pak;}

    /* lock the main FMC after the erase operation */
    fmc_lock();
}

/*!
    \brief      program fmc word by word from FMC_WRITE_START_ADDR to FMC_WRITE_END_ADDR
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_program(uint32_t StartAddr,uint32_t EndAddr, uint32_t* srcaddr)
{
	uint32_t wdata;
    /* unlock the flash program/erase controller */
    fmc_unlock();

    uint32_t address = StartAddr;

    /* program flash */
    while(address < EndAddr){
    	wdata=*srcaddr;
        fmc_word_program(address, wdata);
        address += 4;srcaddr++;
        fmc_flag_clear(FMC_FLAG_BANK0_END);
        fmc_flag_clear(FMC_FLAG_BANK0_WPERR);
        fmc_flag_clear(FMC_FLAG_BANK0_PGERR);
    }

    /* lock the main FMC after the program operation */
    fmc_lock();
}


int32_t WriteEEprom32a32(uint32_t* pdst,uint32_t* psrc, uint32_t Len32words)
{
  uint32_t idx=0;
  int32_t status=0;
  idx=(uint32_t)pdst;
  fmc_erase_pages(idx,idx+(Len32words*4));
  fmc_program(idx,idx+(Len32words*4), psrc);
  for (idx=0;idx<Len32words;idx++)
  {
	  if (*pdst!=*psrc) status++;
	  pdst++;psrc++;
  }
  return status;
}


uint32_t CalcCRC32a32(uint32_t *pBegin, uint32_t *pEnd)
{
 uint32_t dum;
    /* Reset CRC generator */
    CRC_CTL |= (uint32_t)CRC_CTL_RST; //CRC->CR = CRC_CR_RESET;
    dum=CRC_DATA;dum=CRC_DATA;dum=CRC_DATA; //CRC->DR;
pak:;
	CRC_DATA = *pBegin; //CRC->DR;
    dum=CRC_DATA;//CRC->DR;
    if (pBegin!=pEnd) {pBegin++;goto pak;}
  dum=CRC_DATA; //CRC->DR;
 return (dum);
}

