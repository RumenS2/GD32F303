/*
 * mix.c
 *
 *  Created on: Dec 4, 2022
 *      Author: ru
 */
#include "variables.h"
#include "EE_EMUL.h"
#include "AnalisRS.h"
#include "Errors.h"
#include "mix.h"

int16_t GetCurrentProfilFromDrvBrd(void)
{
int16_t errcod;
     SGET_Config();if (RSS2.ErrCod) {LocErrorFlags|=iEF_BurnerProfGetErr;errcod=-2; goto exii;}
     LocErrorFlags&=~iEF_BurnerProfGetErr;
     errcod=0;
exii:
return (errcod);
}

//#define MAX(a, b) (((a) > (b)) ? (a) : (b))
int16_t SendCurrentProfilToDrvBrd(void)
{
int16_t errcod;
 errcod=0;
   iRtmp_CFG=iR2_CFG;
   SSC_iR2_CFG();
   errcod=RSS2.ErrCod;
   if (errcod){iR2_CFG=iRtmp_CFG;LocErrorFlags|=iEF_BurnerProfSendErr; goto exii;}
   LocErrorFlags&=~iEF_BurnerProfSendErr;
exii:;
return (errcod);
}

int16_t ReadCFGfromFlash(uint16_t pn)
{
int16_t errcod;
 if (pn>=MaxCFGProfiles) pn=MaxCFGProfiles-1;

 for (uint16_t i=0;i<MAXANGLES;i++) iR2_CFG.Angles[i]=E_CFG[pn].Angles[i];
   LocErrorFlags&=~iEF_dEmptyProfile;
   errcod=0;
return (errcod);
}

int16_t WriteCFGtoFlash(uint16_t pn)
{
int16_t errcod;
 errcod=0;
 if (pn>=MaxCFGProfiles) pn=MaxCFGProfiles-1;
 iR2_CFG.CS32=CalcCRC32a32((uint32_t*)&iR2_CFG.wID_ConfigValid,((uint32_t*)&iR2_CFG.CS32)-1);
 for (int i=0;i<MaxCFGProfiles;i++) R_CFG[i]=E_CFG[i];
 R_CFG[pn]=iR2_CFG;
 //we write all 10 copies, because E_CFG are stored in flash, and mass erased before write
 if (WriteEEprom32a32((uint32_t*)E_CFG,(uint32_t*)R_CFG,sizeof(R_CFG)>>2)) LocErrorFlags|=iEF_MemFlashError; else LocErrorFlags&=~iEF_MemFlashError;
return (errcod);
}

