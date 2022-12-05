/*!
    \file  main.c
    \brief systick LED demo
    
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

#include "gd32f30x.h"
#include "gd32f30x_it.h"
#include "hw_config.h"
#include "AnalisRS.h"
#include "LCD.h"
#include "gfunct.h"
#include "fonts.h"
#include "rtot.h"
#include "variables.h"
#include "EditVar.h"
#include "mix.h"

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
uint32_t CntPrnt;
uint16_t OldRunFlag;
void CreateMainMenu(void);
void VisPvSp(uint16_t act);
void MenuMainTC(uint16_t act);
void CreateAndVisInfoMenu(int16_t act);
void MenuSetingsTC(uint16_t act);
void PlaseTagInfo(uint16_t colrbk,uint16_t colrfrg);
void PlaseTagSetings(uint16_t colrbk,uint16_t colrfrg);

int main(void)
{
	  Init();

	  SystemClock_Config();

	  MX_GPIO_Init();
	  MX_SPI1_Init();
	  MX_USART2_Init();RSS2.State=RSstIdle;
	  MX_CRC_Init();

	  EnableTasking=0x10;

	  Lcd_Init();

	  LCD_Clear(CR_yellow_green_9ACD32);LCD_Clear(CR_yellow_green_9ACD32);
	  LCD_Clear(CR_hot_pink_FF69B4);LCD_Clear(CR_hot_pink_FF69B4);
	  LCD_Clear(CR_sienna_A0522D);LCD_Clear(CR_sienna_A0522D);
	  LCD_Clear(CR_light_yellow_FFFFE0);LCD_Clear(CR_light_yellow_FFFFE0);

	  rTextColor=CR_blue_0000FF;rBackgroundColor=MAIN_BCKG_COLOR;
	  DM_SetFontN(AnonymosProFont9x17);

	  DM_x=0;DM_y=0; //DM_printf("tmp=%d %d",RSS2.CntTimeout,RSS2.CntAnalisRS);
	  DM_printf("GetVersion..");SGET_iSVpBV();
	  if (RSS2.ErrCod) {rTextColor=CR_red_FF0000;DM_printf("PROBLEM\n");}else{DM_printf("%08X\n",SoftVersion);}
	  rTextColor=CR_blue_0000FF;
	  DM_x=0;DM_y=20;
	  DM_printf("GetConfig..");
	  if (GetCurrentProfilFromDrvBrd()!=0)
	  {
	    rTextColor=CR_red_FF0000;DM_printf("PROBLEM\n");
	  }
	  else
	  {
	    DM_printf("OK\n");
	  }

	  DM_x=0;DM_y=40;DM_printf("CPU clock %d",SystemCoreClock);
	  {uint32_t del=SysTickCntr+20000;while(del>SysTickCntr);}

	    iOlCo.AngleToMake=iR2_CFG.Angles[TabIndex];CreateMainMenu();OldRunFlag=iMState.RunFlag;

	  MX_IWDG_Init(); //and run it
pak:;
		fwdgt_counter_reload();
/*
		if (CntPrnt<=SysTickCntr)
		{
			  DM_x=0;DM_y=100;DM_printf("Test %X",SysTickCntr);
static float fvol=700.0f,fv2;
			  CntPrnt=SysTickCntr+5000; //0.5s
			  fv2=rtot(fvol);
			  DM_x=0;DM_y=160;DM_printf("v=%f temp=%f",fvol,fv2);
			  fvol+=100.01f; if (fvol>20000.0f) fvol=700.0f;
		}
*/

	    if (ActMenuSelector==MENU_MAIN)
	    {
	        VisPvSp(0);
	        MenuMainTC(0);
	    }
	    if (ActMenuSelector==MENU_INFO)
	    {
	            CreateAndVisInfoMenu(0);
	    }
	    if (ActMenuSelector==MENU_SETINGS)
	    {
	       MenuSetingsTC(0);
	    }



	if ((iMState.RunFlag==0)&&((OldRunFlag==6)||(OldRunFlag==4)))
	{
	   TabIndex++;if (TabIndex>39) TabIndex=0;
	   if (iR2_CFG.Angles[TabIndex]==0) TabIndex=0; //end of program, go in begin
	   iOlCo.AngleToMake=iR2_CFG.Angles[TabIndex];
	   OldRunFlag=iMState.RunFlag;
	}
	if (iMState.Pedal<100) //!pedal is pressed
	{
	   if (iR2_CFG.Angles[TabIndex]==0) TabIndex=0; //end of program, go in begin
	   iOlCo.AngleToMake=iR2_CFG.Angles[TabIndex];
	}
	if ((iMState.RunFlag==0x80)&&(OldRunFlag<0x80))
	{
	//    CreateMainMenu();
	        Lcd_Init(); //!!!!!!!!!!!!!!
	rBackgroundColor=CR_yellow_FFFF00;rTextColor=CR_blue_0000FF;
	  LCD_Clear(MAIN2_BCKG_COLOR);
	ActMenuSelector=MENU_MAIN;
	PlaseTagInfo(CR_yellow_FFFF00,CR_blue_0000FF);
	PlaseTagSetings(CR_yellow_FFFF00,CR_blue_0000FF);
	fwdgt_counter_reload();ActSubMenuIsSelected=0;SubSubMenuIsSelected=0;
	VisPvSp(1);    MenuMainTC(1);
	}
	OldRunFlag=iMState.RunFlag;






goto pak;
}

#include "menus.c"


