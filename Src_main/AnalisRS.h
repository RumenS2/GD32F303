#ifndef __ANALISRS_H
#define __ANALISRS_H

#include "gd32f30x.h"

#define RSBUFLEN 2048 //space for E_ERR[MAXERRORS][2] //220*8

#define RsSlaveDeviceN 0

#define RsPosDN 0
#define RsPosCMD 1
#define RsPosSubCMD 2

#define RsRetrCMD 3

#define COMM_GET 0x22
#define COMM_SET 0x66

#define SubCmd_OIST  0x01   //ALL4x16bit A,B,C,D
#define SubCmd_OldComands 0x11
#define SubCmd_OutsA32   0x31
#define SubCmd_PWM1   0x51
#define SubCmd_PWM2   0x61
#define SubCmd_AINvolt 0x57   //ALL7
#define SubCmd_AINspc 0x77   //ALL7
#define SubCmd_StructSTATUS 0x03 //len StructSTATUS
#define SubCmd_Config       0x04 //len config
#define SubCmd_TIME       0x05
#define SubCmd_USERI      0x06
#define SubCmd_Calib      0x07
#define SubCmd_SVpBV      0x08
#define SubCmd_Errors     0x09

#define COMM_STOP_ALL 0xf2
#define SLAVE_ANS_ACK  0xfc  //==confirmation==ACK after set comands

#define RSstIdle 0x00
#define RSstWait1Rcv 0x03
#define RSstTrn  0x10
//#define RSstWaitTC 0x11
#define RSstWaitTC_data 0x11
#define RSstWaitTC_break 0x12
#define RSstRcv  0x20
#define RSstAck  0x30
#define RSstNoAns 0x40
#define RSstNoValidAns 0x50

struct RS_State{
uint8_t  State; //00=idle_rcv_enabled,10=trn,20=rcv,30=ack,40=noans
uint8_t  RetrCnt;
uint8_t  ErrCod;
uint8_t  TraceCod;
uint16_t  wCRC;
uint16_t  CommCntr;
volatile uint8_t  *BegPnt;
volatile uint8_t  *EndPnt;
uint32_t CntAnalisRS;
uint32_t CntTimeout;
uint32_t LastAnsTimeStamp;
uint32_t ExtraCntTimeout;
};

//extern uint8_t RSBuffer[RSBUFLEN];
extern uint8_t RS2Buffer[RSBUFLEN];
//extern volatile struct RS_State RSS;
extern volatile struct RS_State RSS2;
extern volatile uint8_t CommandToIOM;
extern volatile uint8_t ConfigNowReceived;
extern volatile uint32_t SoftVersion;


void Calc_CS_WithCopy(uint8_t* BegSourceAddr,uint8_t* BegDestAddr, uint16_t Len);
void AddCRC(volatile uint16_t *pbCRC,volatile uint8_t *pbBuffer);
void Crc16ModbusFast(volatile uint16_t* lCrc, volatile uint8_t* lData); // sourcer32@gmail.com
uint16_t Calc_CS(uint8_t* BegAd, uint16_t Len);
void AnalisRS(void);
void mainSSC_iOlCo(void);
void SGET_iSVpBV(void);
void SGET_Config(void);
void SGET_Errors(void);
void SSC_iR2_CFG(void);

#endif

