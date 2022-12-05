#include "variables.h"
#include "gfunct.h"


volatile struct iOldComands iOlCo;

struct iMain_State iMState;
uint16_t BoardVersion;

struct iACFG iRtmp_CFG,iR2_CFG;

///*Variables placed in DataFlash */
struct iACFG E_CFG[MaxCFGProfiles] __attribute__ ((section ("SCFG")));   // __attribute__ ((section ("__SCFG"))); //__attribute__((at(0x08080000)));
struct iACFG R_CFG[MaxCFGProfiles];
//uint32_t  EEtest __attribute__ ((section ("__SCAL")));
//!!!!!!!!! sections must be defined in linker stm32l152rb.ld

//const struct iACFG C_CFG[MaxCFGProfiles]=
//{
const struct iACFG C_CFG=
{
  0x55aacc33, //uint32_t    wID_ConfigValid;

  97,5000,0,0,0,
  {
    0,0,0,0,0, 0,0,0,0,0,
        0,0,0,0,0, 0,0,0,0,0,
            0,0,0,0,0, 0,0,0,0,0,
                0,0,0,0,0, 0,0,0,0,0
  },
//float clrzerotest;
  0x00, //uint32_t    CS32;
  0xa559c3b7 // uint32_t     ct0xa559c3b7;  //ct used for UNzeroing CS !!!
};

//};
//===========================================================================================//


//==========================================================================================
//==========================================================================================

int16_t ActMenuIsSelected=0,ActSubMenuIsSelected=0,ActMenuSelector=0,ActSubMenuSelector=0,SubSubMenuIsSelected=0,TabIndex=0;

uint16_t LStatesIdx=0,EErrIdx=0,LState=0;
uint32_t E_ERR[MAXERRORS][2];
uint32_t LSTATES[MAXLSTATES][2];


const uint8_t MessCal[32]={"���������� �������� �� 4 �����"};
const uint8_t MessPressCircleCenter[24]={"<<<������� �������� "};
const uint8_t MessPressCircleCenter2[24]={"������� ��������>>>"};
const uint8_t MessTestCursor[24]={"������������� ������"};


const float cprofmax=MaxCFGProfiles-1;
const float cplus2=2.0;
const float cplus1=1.0;
const float cplus100=100.0;
const float cplus300=300.0;
const float cplus40=40.0;
const float cplus255=255.0;
const float cplus31=31.0;
const float cplus59=59.0;
const float cplus12=12.0;
const float cplus2000=2000.0;
const float cplus1500=1500.0;
const float cplus2037=2037.0;
const float cplus23=23.0;
const float cplus10=10.0;
const float cminus511=-511.0;
const float cplus511=511.0;
const float cplus3600=3600.0;
const float cplus65000=65000.0;
const float czero=0.0;

const float cmaxcfg=MaxCFGProfiles-1;

const uint8_t MessSettings[3][10]={{"��������"},{"��������"},{"SETTINGS"}};
const uint8_t MessInfo[3][10]={{" ������ "},{" ������ "},{"  INFO  "}};


const uint8_t HelpOneDegCt[LHLEN]=  {"���� ������ Ct  \x00"};
const uint8_t HelpReversTimeOfDelay[LHLEN]=  {"�������� ������ \x00"};
const uint8_t HelpMode[LHLEN]=  {"����� ���/����� \x00"};
const uint8_t Helpres4[LHLEN]=  {"����� � �����   \x00"};
const uint8_t Helpres5[LHLEN]=  {"������ � �����  \x00"};

const EVCFG SLPrs[SLEEPMAXVARS]=
{
{&iR2_CFG.OneDegCt,0x02,&HelpOneDegCt[0],(void*)&czero,(void*)&cplus65000,LHLEN,"%5d"},
{&iR2_CFG.ReversTimeOfDelay,0x02,&HelpReversTimeOfDelay[0],(void*)&cplus1500,(void*)&cplus65000,LHLEN,"%5d"},
{&iR2_CFG.Mode,0x02,&HelpMode[0],(void*)&czero,(void*)&cplus65000,LHLEN,"%5d"},
{&iR2_CFG.res4,0x02,&Helpres4[0],(void*)&czero,(void*)&cmaxcfg,LHLEN,"%5d"},
{&iR2_CFG.res5,0x02,&Helpres5[0],(void*)&czero,(void*)&cmaxcfg,LHLEN,"%5d"}
};
//-----------------errors--------------------------------------
const uint32_t HelpErrorFlagsColor[32][2] = {
 {CR_red_FF0000,CR_white_FFFFFF}, //0
 {CR_red_FF0000,CR_white_FFFFFF}, //1
 {CR_red_FF0000,CR_white_FFFFFF}, //2
 {CR_red_FF0000,CR_white_FFFFFF}, //3
 {CR_red_FF0000,CR_white_FFFFFF}, //4
 {CR_red_FF0000,CR_white_FFFFFF}, //5
 {CR_red_FF0000,CR_white_FFFFFF}, //6
 {CR_red_FF0000,CR_white_FFFFFF}, //7
 {CR_red_FF0000,CR_white_FFFFFF}, //8
 {CR_red_FF0000,CR_white_FFFFFF}, //9
 {CR_red_FF0000,CR_white_FFFFFF}, //10
 {CR_red_FF0000,CR_white_FFFFFF}, //11
 {CR_red_FF0000,CR_white_FFFFFF}, //12
 {CR_red_FF0000,CR_white_FFFFFF}, //13
 {CR_gold_FFD700,CR_black_000000}, //14
 {CR_red_FF0000,CR_white_FFFFFF}, //15
 {CR_red_FF0000,CR_white_FFFFFF}, //16
 {CR_red_FF0000,CR_white_FFFFFF}, //17
 {CR_red_FF0000,CR_white_FFFFFF}, //18
 {CR_red_FF0000,CR_white_FFFFFF}, //19
 {CR_red_FF0000,CR_white_FFFFFF}, //20
 {CR_red_FF0000,CR_white_FFFFFF}, //21
 {CR_red_FF0000,CR_white_FFFFFF}, //22
 {CR_red_FF0000,CR_white_FFFFFF}, //23
 {CR_red_FF0000,CR_white_FFFFFF}, //24
 {CR_red_FF0000,CR_white_FFFFFF}, //25
 {CR_red_FF0000,CR_white_FFFFFF}, //26
 {CR_red_FF0000,CR_white_FFFFFF}, //27
 {CR_red_FF0000,CR_white_FFFFFF}, //28
 {CR_red_FF0000,CR_white_FFFFFF}, //29
 {CR_green_008000,CR_white_FFFFFF}, //30
 {CR_gold_FFD700,CR_black_000000} //31
};
const uint8_t HelpRuErrorFlags[32][LHLEN+2]= {        //! �
"0 ���������� ������  \x00",
"1 ���������� ������  \x00",
"2 ��� ����� t ������ \x00",
"3 ����� ���� ���.����\x00",
"4 ������ t Pv �������\x00",
"5 ������ t RB �������\x00",
"6 �������� ���� >>t  \x00",
"7 �������0 �� ������ \x00",
"8 �������� ����������\x00",
"9 �������� ����������\x00",
"10 ���� ��� ���������\x00",
"11 ��� ��� ��������� \x00",
"12 �������ProfSendErr\x00",
"13 ������� ProfGetErr\x00",
"14 ����������� ������\x00",
"15 ������� ����������\x00",
"16 Memory Flash Error\x00",
"17 NMI ������        \x00",
"18 ����������� ������\x00",
"19 ����������� ������\x00",
"20 ����������� ������\x00",
"21 HSE �� ���������� \x00",
"22 ����� �� IWDG     \x00",
"23 ���� ���������??? \x00",
"24 ���� PRS ���������\x00",
"25 ����������� ������\x00",
"26 ����������� ������\x00",
"27 PinRST ������     \x00",
"28 ����������� ������\x00",
"29 ����������� ������\x00",
"30 ��������� ������  \x00",
"31 ��������� ��������\x00"
};

const uint8_t HelpBgErrorFlags[32][LHLEN+2] = {        //! �
"0 ��������� ������   \x00",
"1 ��������� ������   \x00",
"2 ���� ����� t ������\x00",
"3 ������ ��� ���.����\x00",
"4 ������ t Pv �������\x00",
"5 ������ t RB �������\x00",
"6 ������� ���� >>t   \x00",
"7 ������ 0 �� �������\x00",
"8 �������� ����������\x00",
"9 �������� ����������\x00",
"11 ��� �� ������??   \x00",
"10 �������� �� �����?\x00",
"12 �������ProfSendErr\x00",
"13 ������� ProfGetErr\x00",
"14 ����������� ������\x00",
"15 ������� ����������\x00",
"16 Memory Flash Error\x00",
"17 NMI ������        \x00",
"18 ���������� ������ \x00",
"19 ���������� ������ \x00",
"20 ���������� ������ \x00",
"21 HSE �� �� ������� \x00", //0x0020 0000
"22 ����� �� IWDG     \x00", //0x0040 0000
"23 �������� �������??\x00", //0x0080 0000
"24 �����PRS �������??\x00", //0x0100 0000
"25 ���������� ������ \x00", //0x0200 0000
"26 ���������� ������ \x00", //0x0400 0000
"27 PinRST ������     \x00", //0x0800 0000
"28 ���������� ������ \x00", //0x1000 0000
"29 ���������� ������ \x00", //0x2000 0000
"30 �������� ����     \x00", //0x4000 0000
"31 ��������� � ���!  \x00"  //0x8000 0000
};

const uint8_t HelpEnErrorFlags[32][LHLEN+2] = {        //! �
"0 Program error      \x00",
"1 Program error      \x00",
"2 No Change t sensor \x00",
"3 FlameBellowMinLevel\x00",
"4 Sensor t Pv problem\x00",
"5 Sensor t RB problem\x00",
"6 Revers Burning Hi t\x00",
"7 Profil 0 not found \x00",
"8 Calib is LOST      \x00",
"9 Config is LOST     \x00",
"10 Clock not ready???\x00",
"11 ADC not ready???? \x00",
"12 Commun.ProfSendErr\x00",
"13 Commun. ProfGetErr\x00",
"14 DispProfile empty \x00",
"15 DispTouch Calib???\x00",
"16 Memory Flash Error\x00",
"17 NMI error         \x00",
"18 Unknown error     \x00",
"19 Unknown error     \x00",
"20 Unknown error     \x00",
"21 HSE not working   \x00",
"22 Reset from IWDG   \x00",
"23 Clock battery ????\x00",
"24 ClockPRS battery??\x00",
"25 Unknown error     \x00",
"26 Unknown error     \x00",
"27 PinRST error      \x00",
"28 Unknown error     \x00",
"29 Unknown error     \x00",
"30 Normal start      \x00",
"31 Heater is ON!     \x00"
};

