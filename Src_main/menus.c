
void MenuSetingsTC(uint16_t act);
void MenuMainTC(uint16_t act);
void Print3VrsMN(EVCFG* p, int16_t amn, uint16_t maxvars);
void VisPvSp(uint16_t act);
//-------------------------------------------------------------------
/* Touch only
int16_t CheckTag(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1)
{
int16_t n;
n=0;
        if ((mTSc.state==TSSTAT_PRESSED)||(mTSc.state==TSSTAT_TOUCH))
        {
          if ( (mTSc.X>x0)&&(mTSc.X<x1)&&(mTSc.Y>y0)&&(mTSc.Y<y1) )
          {
               n=mTSc.state;mTSc.state=TSSTAT_NOTHING;
          }
        }
return (n);
}
*/
//----------------------4 squares-------------------
#define TagULsq_X0 0
#define TagULsq_Y0 0
#define TagULsq_X1 49
#define TagULsq_Y1 49
#define PlaseULsq(a,b) FillBox(TagULsq_X0,TagULsq_Y0,TagULsq_X1,TagULsq_Y1,a);SetLineMy(TagULsq_X0,TagULsq_Y0,TagULsq_X1,TagULsq_Y1,b)

#define TagURsq_X0 (LCD_TPIXL_X-1-49)
#define TagURsq_Y0 0
#define TagURsq_X1 (LCD_TPIXL_X-1)
#define TagURsq_Y1 49
#define PlaseURsq(a,b) FillBox(TagURsq_X0,TagURsq_Y0,TagURsq_X1,TagURsq_Y1,a);SetLineMy(TagURsq_X1,TagURsq_Y0,TagURsq_X0,TagURsq_Y1,b)

#define TagDLsq_X0 0
#define TagDLsq_Y0 (LCD_TPIXL_Y-1-49)
#define TagDLsq_X1 49
#define TagDLsq_Y1 (LCD_TPIXL_Y-1)
#define PlaseDLsq(a,b) FillBox(TagDLsq_X0,TagDLsq_Y0,TagDLsq_X1,TagDLsq_Y1,a);SetLineMy(TagDLsq_X1,TagDLsq_Y0,TagDLsq_X0,TagDLsq_Y1,b)

#define TagDRsq_X0 (LCD_TPIXL_X-1-49)
#define TagDRsq_Y0 (LCD_TPIXL_Y-1-49)
#define TagDRsq_X1 (LCD_TPIXL_X-1)
#define TagDRsq_Y1 (LCD_TPIXL_Y-1)
#define PlaseDRsq(a,b) FillBox(TagDRsq_X0,TagDRsq_Y0,TagDRsq_X1,TagDRsq_Y1,a);SetLineMy(TagDRsq_X0,TagDRsq_Y0,TagDRsq_X1,TagDRsq_Y1,b)

//-------------------NASTROIKI---------------------
#define TagNastroiki_X0 50
#define TagNastroiki_Y0 (LCD_TPIXL_Y-1-50)
#define TagNastroiki_X1 (LCD_TPIXL_X-1-50)
#define TagNastroiki_Y1 (LCD_TPIXL_Y-1)
//void PlaseTagNastroiki(void)
//{
//  FillBox(TagNastroiki_X0,TagNastroiki_Y0,TagNastroiki_X1,TagNastroiki_Y1,CR_yellow_FFFF00);
//  DM_SetFontN(AnonymosProFont15x28);DM_gotoxy(100,LCD_TPIXL_Y-50+10);DM_meth=1;rTextColor=CR_blue_0000FF;
//  DM_printf(&MessSettings[iR2_CFG.CurrentLanguage][0]);
//}

//---------------------INFO---------------------------
#define TagInfo_X0 0
#define TagInfo_Y0 50
#define TagInfo_X1 50
#define TagInfo_Y1 (LCD_TPIXL_Y-1-50)
void PlaseTagInfo(uint16_t colrbk,uint16_t colrfrg)
{
  FillBox(TagInfo_X0,TagInfo_Y0,TagInfo_X1,TagInfo_Y1,colrbk);
  DM_SetFontN(AnonymosProFont15x28);DM_gotoxy(10,LCD_TPIXL_Y-50-25);DM_meth=1;rTextColor=colrfrg;
  DM_printfV((const char*)&MessInfo[1][0]);
}
//-----------------------ErrLog---------------------------------------
#define TagErrLog_X0 (LCD_TPIXL_X-1-50)
#define TagErrLog_Y0 50
#define TagErrLog_X1 (LCD_TPIXL_X-1)
#define TagErrLog_Y1 (LCD_TPIXL_Y-1-50)
void PlaseTagSetings(uint16_t colrbk,uint16_t colrfrg)
{
  FillBox(TagErrLog_X0,TagErrLog_Y0,TagErrLog_X1,TagErrLog_Y1,colrbk);
  DM_SetFontN(AnonymosProFont15x28);DM_gotoxy(LCD_TPIXL_X-50+10,LCD_TPIXL_Y-50-25);DM_meth=1;rTextColor=colrfrg;
  DM_printfV((const char*)&MessSettings[1][0]);

}
//-----------------------ErrLog---------------------------------------
//#define TagSleep_X0 (50)
//#define TagSleep_Y0 0
//#define TagSleep_X1 (LCD_TPIXL_X-1-50)
//#define TagSleep_Y1 (50)
//const uint8_t MessSleep[10]={" ÍÀÑÒÐ  "};
//void PlaseTagSleep(void)
//{
//  FillBox(TagSleep_X0,TagSleep_Y0,TagSleep_X1,TagSleep_Y1,CR_yellow_FFFF00);
//  DM_SetFontN(AnonymosProFont15x28);DM_gotoxy(100,10);DM_meth=1;rTextColor=CR_blue_0000FF;
//  DM_printf(&MessSleep[0]);
//}

//====================================================================================
//====================================================================================
void Print3VrsMN(EVCFG* p, int16_t amn, uint16_t maxvars)
{

  FillBox(0,0,LCD_TPIXL_X-1,5,MAIN2_BCKG_COLOR);
  FillBox(0,LCD_TPIXL_Y-1-5,LCD_TPIXL_X-1,LCD_TPIXL_Y-1,MAIN2_BCKG_COLOR);


    if (amn>0)
    {
      amn--;
      PrintVariable((EVCFG*)&p[amn], 0, CR_dark_green_006400, CR_white_FFFFFF);amn++;
    }
    else //==0
    {
      FillBox(0,FIRSV_YPOS+(AnonymosProFont15x28YDim+10)*2*(0),16*LHLEN,FIRSV_YPOS+(AnonymosProFont15x28YDim+10)*2*(1),MAIN2_BCKG_COLOR);
    }

    PrintVariable((EVCFG*)&p[amn], 1, CR_yellow_FFFF00, CR_blue_0000FF);amn++;

    if (amn==maxvars)
    {
      FillBox(0,FIRSV_YPOS+(AnonymosProFont15x28YDim+10)*2*(2),16*LHLEN,FIRSV_YPOS+(AnonymosProFont15x28YDim+10)*2*(3),MAIN2_BCKG_COLOR);
    }
    else
    {
      PrintVariable((EVCFG*)&p[amn], 2, CR_dark_green_006400, CR_white_FFFFFF);amn++;
    }
}


//------------------------------------------------------------------------------------
//======================================-MAIN-========================================
//------------------------------------------------------------------------------------
void CreateMainMenu()
{
//        Lcd_Init(); //!!!!!!!!!!!!!!
  LCD_Clear(MAIN2_BCKG_COLOR);

rBackgroundColor=CR_yellow_FFFF00;rTextColor=CR_blue_0000FF;
ActMenuSelector=MENU_MAIN;
if (SendCurrentProfilToDrvBrd()!=0){  fwdgt_counter_reload();LCD_Clear(CR_red_FF0000);} //send cfg to baseboard
                     else{  fwdgt_counter_reload();LCD_Clear(MAIN2_BCKG_COLOR);}

PlaseTagInfo(CR_yellow_FFFF00,CR_blue_0000FF);
PlaseTagSetings(CR_yellow_FFFF00,CR_blue_0000FF);
fwdgt_counter_reload();ActSubMenuIsSelected=0;SubSubMenuIsSelected=0;
VisPvSp(1);    MenuMainTC(1);
}

void CreateAndVisInfoMenu(int16_t act)
{
static int16_t locit, lociv, locrefv;
static int16_t locfl, locma, locpump;
static uint32_t LocErrCopy,lSfv;

  if (act==1)
  {
   locit=0x5aa5, lociv=0x5aa5, locrefv=0x5aa5;
   locfl=0x5aa5, locma=0x5aa5, locpump=0x5aa5;
   LocErrCopy=0xffffffff;lSfv=0xffffffff;
   fwdgt_counter_reload();LCD_Clear(MAIN2_BCKG_COLOR);
  }

 ActMenuSelector=MENU_INFO;
 ActSubMenuIsSelected=0;
    if (S5Cntr>1500)
        {ActSubMenuIsSelected=1;S5Cntr=-10000;
        CreateMainMenu();
        goto exii;}

 DM_SetFontN(AnonymosProFont15x28);DM_meth=0;
 if (iMState.IntTemperature==locit) goto nonewit;
 locit=iMState.IntTemperature;
 DM_x=6;DM_y=0;
 rTextColor=CR_white_FFFFFF;rBackgroundColor=CR_green_008000;
 if (locit>8000) rBackgroundColor=CR_red_FF0000;
 DM_printf("t uC =%6.2f C",(float)((float)locit/100.0));
nonewit:;

 if (iMState.IntVoltage==lociv) goto nonewiv;
 lociv=iMState.IntVoltage;
 DM_x=6;DM_y=1*CurrentFontYDim;
 rTextColor=CR_white_FFFFFF;rBackgroundColor=CR_green_008000;
 if ((lociv>350)||(lociv<300)) rBackgroundColor=CR_red_FF0000;
 DM_printf("U uC =%6.2f V",(float)((float)lociv/100.0));
nonewiv:;

 if (iMState.RefVoltage==locrefv) goto nonewref;
 locrefv=iMState.RefVoltage;
 DM_x=6;DM_y=2*CurrentFontYDim;
 rTextColor=CR_white_FFFFFF;rBackgroundColor=CR_green_008000;
 if ((locrefv>540)||(locrefv<450)) rBackgroundColor=CR_red_FF0000;
 DM_printf("Uref =%6.2f V",(float)((float)locrefv/100.0));
nonewref:;

 if (iMState.Ant==locfl) goto nonefl;
 locfl=iMState.Ant;
 DM_x=6;DM_y=3*CurrentFontYDim;
 rTextColor=CR_white_FFFFFF;rBackgroundColor=CR_blue_0000FF;
 DM_printf("AntSn=%6.2f  ",(float)((float)locfl));
nonefl:;

 if (iMState.Pedal==locma) goto nonema;
 locma=iMState.Pedal;
 DM_x=6;DM_y=4*CurrentFontYDim;
 rTextColor=CR_white_FFFFFF;rBackgroundColor=CR_green_008000;
 if (iMState.ErrorFlags&iEF_WireMainSnzFault) rBackgroundColor=CR_red_FF0000;
 DM_printf("Pedal=%6.2f  ",(float)((float)locma));
nonema:;

 if (iMState.PotValue==locpump) goto nonepump;
 locpump=iMState.PotValue;
 DM_x=6;DM_y=5*CurrentFontYDim;
 rTextColor=CR_white_FFFFFF;rBackgroundColor=CR_green_008000;
 if (iMState.ErrorFlags&iEF_WireRevBurnSnzFault) rBackgroundColor=CR_red_FF0000;
 DM_printf("ExtPot=%6.2f ",(float)((float)locpump));
nonepump:;

 if (iMState.ErrorFlags==LocErrCopy) goto nonelocerr;
 LocErrCopy=iMState.ErrorFlags;
 DM_x=6;DM_y=6*CurrentFontYDim;
 rTextColor=CR_white_FFFFFF;rBackgroundColor=CR_green_008000;
 if (LocErrCopy&(0x0fffffff)) rBackgroundColor=CR_red_FF0000;
 DM_printf("StauC=%08X",LocErrCopy);
nonelocerr:;

 if (SoftVersion==lSfv) goto nonesfv;
 lSfv=SoftVersion;
 DM_x=6;DM_y=7*CurrentFontYDim;
 rTextColor=CR_black_000000;rBackgroundColor=CR_golden_rod_DAA520;
 DM_printf("SofVr=%08X",lSfv);
nonesfv:;




exii:;
}

void CreateSetingsMenu()
{
	fwdgt_counter_reload();LCD_Clear(MAIN2_BCKG_COLOR);
   ActMenuSelector=MENU_SETINGS;
   ActSubMenuIsSelected=0;
   MenuSetingsTC(1);
}

void MenuSetingsTC(uint16_t act)
{
static int16_t mCurrentPos=0,locPos=0,lpold=0;
  if (act){mCurrentPos=0;locPos=0;CurrentPosition=0;locCurrentPosition=0;Print3VrsMN((EVCFG*)&SLPrs,0,SLEEPMAXVARS);}
  if (ActSubMenuIsSelected==0) {lpold=locPos;locPos+=CurrentPosition-mCurrentPos;mCurrentPos=CurrentPosition; }else goto toedit;
  if (locPos>(SLEEPMAXVARS-1)) locPos=0;
  if (locPos<0) locPos=SLEEPMAXVARS-1;

  if (locPos==0)
  {
//    ActSubMenuSelector=SUBMENU_MANGLE;
    if ((lpold!=locPos)&&(ActSubMenuIsSelected==0))
    {
      Print3VrsMN((EVCFG*)&SLPrs,0,SLEEPMAXVARS);goto exii;
    }
    if ((S5Cntr>1500)&&(ActSubMenuIsSelected==0)){S5Cntr=-5000;ActSubMenuIsSelected=1;EVAVvState=0;EVAVvp32=234345356;goto toedit;}
  }
  if (locPos==1)
  {
//    ActSubMenuSelector=SUBMENU_MINFO;
    if ((lpold!=locPos)&&(ActSubMenuIsSelected==0))
    {
      Print3VrsMN((EVCFG*)&SLPrs,1,SLEEPMAXVARS);goto exii;
    }
    if ((S5Cntr>1500)&&(ActSubMenuIsSelected==0)){S5Cntr=-5000;ActSubMenuIsSelected=1;EVAVvState=0;EVAVvp32=234345356;goto toedit;}
  }
  if (locPos==2)
  {
    if ((lpold!=locPos)&&(ActSubMenuIsSelected==0))
    {
      Print3VrsMN((EVCFG*)&SLPrs,2,SLEEPMAXVARS);goto exii;
    }
    if ((S5Cntr>1500)&&(ActSubMenuIsSelected==0)){S5Cntr=-5000;ActSubMenuIsSelected=1;EVAVvState=0;EVAVvp32=234345356;goto toedit;}
  }
  if (locPos==3)
  {
    if ((lpold!=locPos)&&(ActSubMenuIsSelected==0))
    {
      Print3VrsMN((EVCFG*)&SLPrs,3,SLEEPMAXVARS);goto exii;
    }
    if ((S5Cntr>1500)&&(ActSubMenuIsSelected==0)){S5Cntr=-5000;ActSubMenuIsSelected=1;EVAVvState=0;EVAVvp32=234345356;goto toedit;}
  }
  if (locPos==4)
  {
    if ((lpold!=locPos)&&(ActSubMenuIsSelected==0))
    {
      Print3VrsMN((EVCFG*)&SLPrs,4,SLEEPMAXVARS);goto exii;
    }
    if ((S5Cntr>1500)&&(ActSubMenuIsSelected==0)){S5Cntr=-5000;ActSubMenuIsSelected=1;EVAVvState=0;EVAVvp32=234345356;goto toedit;}
  }
toedit:
    if (ActSubMenuIsSelected)
    {
      if (SLPrs[locPos].pVr)
      {
        rBackgroundColor=CR_yellow_FFFF00;
        DM_gotoxy(0,FIRSV_YPOS+(AnonymosProFont15x28YDim+10)*(1*2));
        if (EditViewActiveVar((EVCFG*)&SLPrs[locPos], CR_blue_0000FF, 0x8000|AnonymosProFont15x28)==0x200)
        {
             ActSubMenuIsSelected=0;
            if (locPos==3)
            {
            	ActSubMenuIsSelected=0;EVAVvState=0;EVAVvp32=234345356;S5Cntr=-5000;rTextColor=CR_dark_green_006400;
            	if (WriteCFGtoFlash(iR2_CFG.res4))
            	{LCD_Clear(CR_hot_pink_FF69B4);DM_x=0;DM_y=0;DM_printf("PROBLEM!!!");{uint32_t del=SysTickCntr+20000;while(del>SysTickCntr) fwdgt_counter_reload();}}
            	iOlCo.AngleToMake=iR2_CFG.Angles[TabIndex];
            	CreateMainMenu();
            	goto exii;
            }
            if (locPos==4)
            {
            	ActSubMenuIsSelected=0;EVAVvState=0;EVAVvp32=234345356;S5Cntr=-5000;rTextColor=CR_dark_green_006400;
            	if (ReadCFGfromFlash(iR2_CFG.res5))
            	{LCD_Clear(CR_hot_pink_FF69B4);DM_x=0;DM_y=0;DM_printf("PROBLEM!!!");{uint32_t del=SysTickCntr+20000;while(del>SysTickCntr) fwdgt_counter_reload();}}
            	iOlCo.AngleToMake=iR2_CFG.Angles[TabIndex];
            	CreateMainMenu();
            	goto exii;
            }
        }
      }
    }

//  mCurrentPos=CurrentPosition;
exii:;
}

void PrntAngles(int16_t idx)
{
       DM_SetFontN(AnonymosProFont15x28);
       DM_gotoxy(90,120-28 -30 -30);if (idx>=2) {DM_printf("St%02u=%04d",(int)idx-2,(int)iR2_CFG.Angles[idx-2]);}else{DM_printf("         ");}
       DM_gotoxy(90,120-28 -30    );if (idx>=1) {DM_printf("St%02u=%04d",(int)idx-1,(int)iR2_CFG.Angles[idx-1]);}else{DM_printf("         ");}
       DM_gotoxy(90,120-28        );DM_printf2x2("%04d",iOlCo.AngleToMake); //DM_printf("St%02u ",(int)iR2_CFG.Angles[idx]);
       DM_gotoxy(90,120+30 +30 -30);if (idx<=38) {DM_printf("St%02u=%04d",(int)idx+1,(int)iR2_CFG.Angles[idx+1]);}else{DM_printf("         ");}
       DM_gotoxy(90,120+30 +30    );if (idx<=37) {DM_printf("St%02u=%04d",(int)idx+2,(int)iR2_CFG.Angles[idx+2]);}else{DM_printf("         ");}
}
void VisPvSp(uint16_t act)
{
static int16_t mAngleToMake;
static uint16_t mRunFlag,museri,rsecode;
static int16_t mTabIndex,mAnt,mPedal;
//static uint32_t loctim;
 if (act) {mAngleToMake=-1;mAnt=5555;mPedal=4564;mRunFlag=0x1234;mTabIndex=-1;museri=0xffff;rsecode=0;} //loctim=SysTickCntr;}
 DM_meth=0;
 if ((iOlCo.AngleToMake!=mAngleToMake)||(mTabIndex!=TabIndex))
 {
    DM_SetFontN(AnonymosProFont15x28);DM_gotoxy(120,120-28);
    if (ActSubMenuSelector==SUBMENU_MANGLE)
    {
      if (ActSubMenuIsSelected) {rTextColor=CR_rosy_brown_BC8F8F;rBackgroundColor=CR_cyan_00FFFF;}else{rTextColor=CR_yellow_FFFF00;rBackgroundColor=CR_blue_0000FF;}
      if (SubSubMenuIsSelected){rTextColor=CR_blue_0000FF;rBackgroundColor=MAIN_BCKG_COLOR;}
    }
    else
    {
      rTextColor=CR_blue_0000FF;rBackgroundColor=CR_yellow_FFFF00;
    }

    PrntAngles(TabIndex);  //DM_printf2x2("%03u",iOlCo.AngleToMake);
    mAngleToMake=iOlCo.AngleToMake;mTabIndex=TabIndex;
 }

 if (iMState.Ant!=mAnt)
 {
     mAnt=iMState.Ant; DM_SetFontN(AnonymosProFont15x28);DM_gotoxy(60,0);DM_meth=0;
     rTextColor=CR_red_FF0000;rBackgroundColor=MAIN_BCKG_COLOR;if (mAnt>150) DM_printf("Z"); else DM_printf(" ");
 }

 if (iMState.Pedal!=mPedal)
 {
     mPedal=iMState.Pedal; DM_SetFontN(AnonymosProFont15x28);DM_gotoxy(75,0);DM_meth=0;
     rTextColor=CR_red_FF0000;rBackgroundColor=MAIN_BCKG_COLOR;if (mPedal<150) DM_printf("P"); else DM_printf(" ");
 }

 if (iMState.RunFlag!=mRunFlag)
 {
     mRunFlag=iMState.RunFlag; DM_SetFontN(AnonymosProFont15x28);DM_gotoxy(90,0);DM_meth=0;
     rTextColor=CR_lime_00FF00;rBackgroundColor=MAIN_BCKG_COLOR;DM_printf("Ðåæèì %04X",mRunFlag);
//     rTextColor=CR_blue_0000FF;DM_SetFontN(1);DM_gotoxy(240,12);DM_meth=0;DM_printf("t=%05d  ",SysTickCntr-loctim);
//     loctim=SysTickCntr;
 }

 if (iMState.USERI!=museri)
 {
     museri=iMState.USERI; DM_SetFontN(1);DM_gotoxy(240,0);DM_meth=0;
     rTextColor=CR_black_000000;rBackgroundColor=MAIN_BCKG_COLOR;DM_printf("U%05d",museri);
 }

if (RSS2.ErrCod)
{
     rsecode=(RS2Buffer[RsPosCMD]<<8)|RS2Buffer[RsPosSubCMD];
     DM_SetFontN(1);DM_gotoxy(240,12);DM_meth=0;
     rTextColor=CR_red_FF0000;rBackgroundColor=MAIN_BCKG_COLOR;DM_printf("e=%04X",RSS2.ErrCod);
}
else
{
    if (rsecode){rsecode=0;
    DM_SetFontN(1);DM_gotoxy(240,12);DM_meth=0;
     rTextColor=CR_red_FF0000;rBackgroundColor=MAIN_BCKG_COLOR;DM_printf("       ",rsecode);
    }
}
}
//---------------------
void MenuMainTC(uint16_t act)
{
static int16_t mCurrentPos=-32767,locPos=0;
  if (act){mCurrentPos=0x4000;locPos=0;CurrentPosition=0;locCurrentPosition=0;goto frun;}

  if (ActSubMenuIsSelected==0) locPos+=CurrentPosition-mCurrentPos;
  if (locPos>2) locPos=0;
  if (locPos<0) locPos=2;
frun:
  if (locPos==0)
  {
    ActSubMenuSelector=SUBMENU_MANGLE;
    if ((mCurrentPos!=CurrentPosition)&&(ActSubMenuIsSelected==0))
    {
      PlaseTagInfo(CR_yellow_FFFF00,CR_blue_0000FF);
      PlaseTagSetings(CR_yellow_FFFF00,CR_blue_0000FF);
      VisPvSp(1);
    }
    if (ActSubMenuIsSelected==0) {if (S5Cntr>1500){ActSubMenuIsSelected=1;S5Cntr=-5000;VisPvSp(1);goto exii;}}
    if (ActSubMenuIsSelected)
    {
      if (S5Cntr>1500)
          {
            S5Cntr=-5000;
            if (SubSubMenuIsSelected) {ActSubMenuIsSelected=0;SubSubMenuIsSelected=0;VisPvSp(1);goto exii;}
            SubSubMenuIsSelected=1;iR2_CFG.Angles[TabIndex]=iOlCo.AngleToMake;VisPvSp(1);
          }
      if (mCurrentPos!=CurrentPosition)
      {
       if (SubSubMenuIsSelected)
       {
         iOlCo.AngleToMake+=CurrentPosition-mCurrentPos;mCurrentPos=CurrentPosition;
         if (iOlCo.AngleToMake<-220) iOlCo.AngleToMake=-220;
         if (iOlCo.AngleToMake>220) iOlCo.AngleToMake=220;
         iR2_CFG.Angles[TabIndex]=iOlCo.AngleToMake;VisPvSp(0);goto exii;
       }
       else
       {
         TabIndex+=CurrentPosition-mCurrentPos;mCurrentPos=CurrentPosition;
         if (TabIndex>39) TabIndex=39; //0;
         if (TabIndex<0)  TabIndex=0; //39;
         iOlCo.AngleToMake=iR2_CFG.Angles[TabIndex];VisPvSp(0);goto exii;
       }
      }
    }
  }
  if (locPos==1)
  {
    ActSubMenuSelector=SUBMENU_MINFO;
    if (mCurrentPos!=CurrentPosition)
    {
      PlaseTagInfo(CR_blue_0000FF,CR_yellow_FFFF00);
      PlaseTagSetings(CR_yellow_FFFF00,CR_blue_0000FF);
      VisPvSp(1);
    }
    if (S5Cntr>1500)
        {ActSubMenuIsSelected=1;S5Cntr=-5000;
        CreateAndVisInfoMenu(1);
        goto exii;}
  }
  if (locPos==2)
  {
    ActSubMenuSelector=SUBMENU_MSETINGS;
    if (mCurrentPos!=CurrentPosition)
    {
      PlaseTagSetings(CR_blue_0000FF,CR_yellow_FFFF00);
      PlaseTagInfo(CR_yellow_FFFF00,CR_blue_0000FF);
      VisPvSp(1);
    }
    if (S5Cntr>1500)
        {ActSubMenuIsSelected=1;S5Cntr=-10000;
        CreateSetingsMenu();
        mCurrentPos=0x4000;locPos=0;CurrentPosition=0;locCurrentPosition=0;
        goto exii;}
  }

  mCurrentPos=CurrentPosition;
exii:;
}
//------------------------------------------------------------------------------------
//===========================-NASTROIKI-==============================================
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//===========================---SLEEP---==============================================
//------------------------------------------------------------------------------------



