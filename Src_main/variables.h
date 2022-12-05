/*
 * variables.h
 *
 *  Created on: 22.02.2021 ã.
 *      Author: ru
 */

#ifndef INC_VARIABLES_H_
#define INC_VARIABLES_H_

#include "gd32f30x.h" //types
#include "Errors.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

struct iOldComands{
uint16_t ButtonsState;   //set from touch display board
int16_t AngleToMake;      //set from touch display board
int16_t vReserv2;      //set from touch display board
uint16_t vReserv;
};
extern volatile struct iOldComands iOlCo;
#define iModeManualSig   (iOlCo.ButtonsState&0x0001)
#define iModeManBit      0x0001
#define iModeAutoBit     0x0004
#define iModeAutoSig     (iOlCo.ButtonsState&0x0004)
#define iModeTestSig     (iOlCo.ButtonsState&0x1000)

#define iKeyIntScrewSig          (iOlCo.ButtonsState&0x0010)
#define iKeyPumpSig         (iOlCo.ButtonsState&0x0020)
#define iKeyHetingSig       (iOlCo.ButtonsState&0x0040)
#define iKeySetTimeSig      (iOlCo.ButtonsState&0x0080)
#define iKeyTestMode        (iOlCo.ButtonsState&0x1000)

#define iSetModeManualSig      (iOlCo.ButtonsState|=0x0001)
#define iSetModeAutoSig        (iOlCo.ButtonsState|=0x0004)
#define iSetKeyIntScrewSig          (iOlCo.ButtonsState|=0x0010)
#define iSetKeyPumpSig         (iOlCo.ButtonsState|=0x0020)
#define iSetKeyHeatingSig      (iOlCo.ButtonsState|=0x0040)
#define iSetKeySetTimeSig      (iOlCo.ButtonsState|=0x0080)
#define iSetTestMode           (iOlCo.ButtonsState|=0x1000)

#define iClrModeManualSig   (iOlCo.ButtonsState&=~0x0001)
#define iClrModeAutoSig     (iOlCo.ButtonsState&=~0x0004)
#define iClrKeyIntScrewSig       (iOlCo.ButtonsState&=~0x0010)
#define iClrKeyPumpSig      (iOlCo.ButtonsState&=~0x0020)
#define iClrKeyHeatingSig   (iOlCo.ButtonsState&=~0x0040)
#define iClrKeySetTimeSig   (iOlCo.ButtonsState&=~0x0080)
#define iClrTestMode        (iOlCo.ButtonsState&=~0x1000)

#define iMenuMain 0x00                     // 0
#define iMenuEncTest      (0x25+0x03)             // 4
#define iMenuTestIOs (355)             //0x55

//extern uint16_t EEOutsSTOPState[4];


struct iMain_State{
 uint16_t  USERI;
 uint32_t  ErrorFlags;
 int16_t   IntVoltage,IntTemperature,RefVoltage,Ant,Pedal,PotValue;
 uint16_t  RunFlag;
};


extern struct iMain_State iMState;
extern uint16_t BoardVersion;

typedef struct {
void* pVr;
uint8_t tVr;     //0-16U/1-16S/2-32U/3-32S/4-float/5-8U/6-8S/7-32hex //0x52 date timer //0x55 -spec week day bit field
const uint8_t* hVr;
void* pLoVr;
void* pHiVr;
uint8_t SizSTR;  //|0x80->AnonymosProFont9x17
uint8_t FormStr[8];
} EVCFG;

#define MaxCFGProfiles 10         //!!!!!!!! Max

#define MAXANGLES 40
//extern const EVCFG EVrs[TOTCFVARS];

struct iACFG {
  uint32_t    wID_ConfigValid;

  uint32_t OneDegCt,ReversTimeOfDelay,Mode,res4,res5;
  int16_t  Angles[MAXANGLES];
//float clrzerotest;
  uint32_t    CS32;
  uint32_t     ct0xa559c3b7;  //ct used for UNzeroing CS !!!
          };


extern struct iACFG iRtmp_CFG,iR2_CFG;
//===========================================================================================//
//===========================================================================================//

extern const struct iACFG C_CFG;
extern struct iACFG E_CFG[MaxCFGProfiles];
extern struct iACFG R_CFG[MaxCFGProfiles];
//extern uint32_t  EEtest;


//==========================================================================================//
#define MAXERRORS 21
#define MAXLSTATES 101
extern uint16_t LStatesIdx,EErrIdx,LState;
extern uint32_t E_ERR[MAXERRORS][2];
extern uint32_t LSTATES[MAXLSTATES][2];

//==========================================================================================
#define MENU_MAIN 0
#define MENU_INFO 1
#define MENU_SETINGS 2

#define SUBMENU_MANGLE 0
#define SUBMENU_MINFO 1
#define SUBMENU_MSETINGS 2

#define SUBMENU_SONEDEG 0
#define SUBMENU_SREVDELAY 1
#define SUBMENU_SAUTOMAN 2
#define SUBMENU_SRESV4 3

#define SLEEPMAXVARS 5 //6

#define LHLEN 20
#define TMLEN 10


extern const EVCFG SLPrs[SLEEPMAXVARS];
//==========================================================================================//

extern int16_t ActMenuIsSelected,ActSubMenuIsSelected,ActMenuSelector,ActSubMenuSelector,SubSubMenuIsSelected,TabIndex;

#define CASE84CODE 0x84  //uint x10
#define CASE88CODE 0x88  //int x10
#define CASE40CODE 0x40
#define CASE40LHLEN 6

extern const uint8_t MessCal[32];
extern const uint8_t MessPressCircleCenter[24];
extern const uint8_t MessPressCircleCenter2[24];
extern const uint8_t MessTestCursor[24];

extern const uint8_t MessSettings[3][10];
extern const uint8_t MessInfo[3][10];
extern const uint8_t MessErrLog[3][10];


extern const uint8_t MessCMode[3][10];
extern const uint8_t MessExtCont[3][10];
extern const uint8_t MessExtTerm[3][10];
extern const uint8_t SMessCMode[3][2];
extern const uint8_t SMessExtCont[3][2];
extern const uint8_t SMessExtTerm[3][2];

extern const uint32_t HelpErrorFlagsColor[32][2];
extern const uint8_t HelpRuErrorFlags[32][LHLEN+2];
extern const uint8_t HelpBgErrorFlags[32][LHLEN+2];
extern const uint8_t HelpEnErrorFlags[32][LHLEN+2];

#endif /* INC_VARIABLES_H_ */
