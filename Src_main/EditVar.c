#include "EditVar.h"
#include "variables.h"
#include "fonts.h"
#include "gfunct.h"
//#include "touch.h"
#include "LCD.h"
#include "gd32f30x_it.h"

int32_t EVAVvp32=234345356;
uint16_t EVAVvState=0;
void PrintEVAV(EVCFG *p, uint16_t VFont)
{
float fvp;
int32_t li32;
          if (p->tVr==CASE84CODE)
          {
            fvp=(float)EVAVvp32;fvp=fvp/10.0;
            if (VFont&0x8000){DM_printf2x2((const char*)p->FormStr,fvp);}else{DM_printf((const char*)p->FormStr,fvp);} //tttttttt
            goto exii;
          }
         if (p->tVr==CASE88CODE)
          {
            fvp=(float)EVAVvp32; //fvp=fvp/10.0;
            if (VFont&0x8000){DM_printf2x2((const char*)p->FormStr,fvp);}else{DM_printf((const char*)p->FormStr,fvp);} //tttttttt
            goto exii;
          }
         if (p->tVr&CASE40CODE)
         {
           li32=EVAVvp32;
           if (li32<(*(float*)p->pLoVr)) {li32=*(float*)p->pHiVr;} //p->pLoVr;} //ttttt
           if (li32>(*(float*)p->pHiVr)) {li32=*(float*)p->pLoVr;} //p->pHiVr;} //ttttt
 //          if (p->tVr==(CASE40CODE+1)) {DM_printf2x2(&HelpSleepModeCASE41[(uint16_t)iR2_CFG.CurrentLanguage][li32][0]);}
           goto exii;
         }

         if (VFont&0x8000){DM_printf2x2((const char*)p->FormStr,(int)EVAVvp32);}else{DM_printf((const char*)p->FormStr,(int)EVAVvp32);} //tttttttt
exii:;
}
int16_t EditViewActiveVar(EVCFG* p, uint16_t Vcolor, uint16_t VFont)
{
static uint16_t DM_methCopy, DM_CfCopy, ColorCopy;
uint16_t retval;
static uint32_t loctim=0;

     DM_CfCopy=CurrentFont;
     if (EVAVvState==0)
     {
       if (EVAVvp32!=*(int16_t*)p->pVr)        //tttttttt
       {
          DM_SetFontN(VFont&0x7fff);ColorCopy=Vcolor; rTextColor=ColorCopy;
          EVAVvp32=*(int16_t*)p->pVr;//tttttttt
          DM_methCopy=DM_meth; DM_CfCopy=CurrentFont;
          PrintEVAV(p,VFont);
       }
       if (S5Cntr>500){S5Cntr=-10000; EVAVvState=1;loctim=0;locCurrentPosition=EVAVvp32*4;} //ttttttttttttt
       goto exii;
     }
//EVAVvState==1
     //DM_x=DM_xCopy;DM_y=DM_yCopy;
     DM_SetFontN(VFont&0x7fff);
     if (loctim<SysTickCntr)
     {
       loctim=SysTickCntr+3300; ColorCopy^=0xa55a; rTextColor=ColorCopy;
       PrintEVAV(p,VFont);
       goto exii;
     }
     if (EVAVvp32!=(CurrentPosition)) //!in Anstat CurrentPosition=locCurrentPosition/4
     {
       PrintEVAV(p,VFont);
     }
     EVAVvp32=(CurrentPosition);     //!in Anstat CurrentPosition=locCurrentPosition/4

     if (EVAVvp32<(*(float*)p->pLoVr)) {EVAVvp32=*(float*)p->pLoVr;locCurrentPosition=EVAVvp32*4;} //lo //ttttt
     if (EVAVvp32>(*(float*)p->pHiVr)) {EVAVvp32=*(float*)p->pHiVr;locCurrentPosition=EVAVvp32*4;} //hi //ttttt
     if (S5Cntr>500){S5Cntr=-10000;loctim=0; retval=0x200; EVAVvState=0;*(uint16_t*)p->pVr=EVAVvp32;EVAVvp32^=0xcac955ac; goto exii2;} //ttttt
exii:;
     retval=EVAVvState;
exii2:;
     DM_meth=DM_methCopy;DM_SetFontN(DM_CfCopy);
  return(retval);
}


void PrintVariable(EVCFG* p, uint16_t DispPosNumber, uint16_t BColor, uint16_t TColor)
{
float fvp;
uint16_t dmc,cDM_x,cDM_y,cfc;
  cDM_x=DM_x;cDM_y=DM_y;cfc=CurrentFont;dmc=DM_meth;DM_meth=1;

  DM_SetFontN(AnonymosProFont15x28); rBackgroundColor=BColor;rTextColor=TColor;
  FillBox(0,FIRSV_YPOS+(CurrentFontYDim+10)*2*(DispPosNumber),16*LHLEN,FIRSV_YPOS+(CurrentFontYDim+10)*2*(DispPosNumber+1),BColor);

  DM_gotoxy(0,FIRSV_YPOS+(CurrentFontYDim+10)*(DispPosNumber*2));
  if (p->pVr)
  {
    if (p->tVr==CASE84CODE)
    {
      fvp=(float)(*(uint16_t*)p->pVr);fvp=fvp/10.0;
      DM_printf2x2((const char*)p->FormStr,fvp);
      goto prnted;
    }
    if (p->tVr==CASE88CODE)
    {
      fvp=(float)(*(int16_t*)p->pVr); //fvp=fvp/10.0;
      DM_printf2x2((const char*)p->FormStr,fvp);
      goto prnted;
    }
    if (p->tVr&CASE40CODE)
    {
//      if (p->tVr==(CASE40CODE+1)) {DM_printf2x2(&HelpSleepModeCASE41[0][(*(uint16_t*)p->pVr)][0]);}
      goto prnted;
    }

    DM_printf2x2("%d",*(uint16_t*)p->pVr); //ttttttt
    goto prnted;
//    EditViewActiveVar(p, CR_blue_0000FF, 0x8000|AnonymosProFont15x28);
  }
  else
  {
    DM_printf2x2((const char*)((uint32_t)p->hVr));
    goto exii;
  }
prnted:;
  DM_x=0;DM_y+=(CurrentFontYDim)*2;DM_SetFontN(ToshibaFont);
  DM_printf2x2((const char*)((uint32_t)p->hVr));
exii:;
fwdgt_counter_reload();

DM_x=cDM_x;DM_y=cDM_y;CurrentFont=cfc;DM_SetFontN(cfc);DM_meth=dmc;
}








