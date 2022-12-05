#include "AnalisRS.h"
#include "variables.h"
#include "hw_config.h"
#include "gd32f30x_it.h"
#include <string.h>

void GetSomething(uint8_t GetSubCmdCode);
void Set_iOlCo(void);


//uint8_t RS2Buffer[RSBUFLEN];
uint8_t RS2Buffer[RSBUFLEN];
uint32_t globalrserrcnt=0;
//volatile struct RS_State RSS;
volatile struct RS_State RSS2;
volatile uint8_t CommandToIOM=0;
volatile uint8_t ConfigNowReceived=0;
volatile uint8_t AnalisRSIsBusy=0;   //!=0 if AnalisRS are executed
uint32_t UsartInUse=USART2;
volatile uint32_t SoftVersion=0x22120000;

__STATIC_INLINE void USART2_RX_START(void)
{
	LoRCV_Enbl_485_2;
	USART_REG_VAL(USART2, USART_INT_RBNE) |= BIT(USART_BIT_POS(USART_INT_RBNE));
	USART_CTL0(USART2)|=USART_CTL0_REN;
}
__STATIC_INLINE void USARTinUSE_TX_START(uint32_t USARTx)
{
    if (USARTx==USART2)
    {
    	HiTRN_Enbl_485_2;
    	RSS2.CntTimeout=SysTickCntr+10; //1ms
    	RSS2.State=RSstTrn;
    }
	USART_CTL0(USARTx)|=USART_CTL0_TEN;
	USART_REG_VAL(USARTx, USART_INT_TBE) |= BIT(USART_BIT_POS(USART_INT_TBE));
}
//__STATIC_INLINE void USARTinUSE_RX_START(uint32_t USARTx)
//{
//	if (USARTx==USART2) LoRCV_Enbl_485_2;
//	USART_REG_VAL(USARTx, USART_INT_RBNE) |= BIT(USART_BIT_POS(USART_INT_RBNE));
//	USART_CTL0(USARTx)|=USART_CTL0_REN;
//}
__STATIC_INLINE void USARTinUSE_RX_DISABLE(uint32_t USARTx)
{
	USART_CTL0(USARTx)&=~USART_CTL0_REN;
	USART_REG_VAL(USARTx, USART_INT_RBNE) &= ~BIT(USART_BIT_POS(USART_INT_RBNE));
	USART_REG_VAL(USARTx, USART_INT_IDLE) &= ~BIT(USART_BIT_POS(USART_INT_IDLE));
}

void AnalisMRS3(void);

__STATIC_INLINE int SetSemB(volatile uint8_t* addr,uint8_t val)
{
	uint8_t t8;
	pak:;
	  t8=__LDREXB(addr);
	  if (t8) {__CLREX();goto isbusy;} //is already set (not free)
	  if (__STREXB(val,addr)) goto pak;
	  t8=0; //ok
isbusy:;
	  return t8;
}
//!==========================================================================================================
void AnalisRS(void)
{
	AnalisMRS3();
}

void AnalisMRS3(void) //Master mode
{
uint16_t ti16;
uint32_t ti32;
//------------------------------------------------
	if (SetSemB(&AnalisRSIsBusy, 1)) goto rsisbusy;

//------------------------------------------------
  if (RSS2.State==RSstIdle)
  {
	if (RSS2.CntAnalisRS<SysTickCntr)
    {
      RSS2.CntAnalisRS=SysTickCntr+537; //53.7ms
      RSS2.RetrCnt=0;
      RSS2.CommCntr++; if (RSS2.CommCntr>6) RSS2.CommCntr=1;
      if (RSS2.CommCntr==1) GetSomething(SubCmd_StructSTATUS);
      if (RSS2.CommCntr==2) Set_iOlCo();
      if (RSS2.CommCntr==3) GetSomething(SubCmd_StructSTATUS);
      if (RSS2.CommCntr==4) Set_iOlCo();
      if (RSS2.CommCntr==5) GetSomething(SubCmd_StructSTATUS);
      if (RSS2.CommCntr==6) Set_iOlCo();
      USARTinUSE_TX_START(UsartInUse); //because TX was enabled, IDLE frame will be sent
    }
    goto exit_ok;
  }
//IF No idle state, only timeout is criteria for end of Trn/Rcv sequence
  if (RSS2.CntTimeout>SysTickCntr) goto exit_ok;

  USARTinUSE_RX_DISABLE(UsartInUse);
  if (RSS2.State==RSstWait1Rcv){RSS2.ErrCod=5;RSS2.RetrCnt++;RSS2.State=RSstIdle;goto exi_err;}
  if (RSS2.wCRC!=0)
  {
    if (RSS2.BegPnt==&RS2Buffer[0]) {RSS2.ErrCod=2;}else{RSS2.ErrCod=3;}
    RSS2.RetrCnt++;RSS2.State=RSstIdle;goto exi_err;
  }
  if (RS2Buffer[RsPosDN]!=RsSlaveDeviceN) { RSS2.RetrCnt++;RSS2.ErrCod=1;RSS2.State=RSstIdle; goto exi_err;}
  if (RS2Buffer[RsPosCMD]==COMM_GET) //check slave answer on COMM_GET
  {
    if (RS2Buffer[RsPosSubCMD]==SubCmd_StructSTATUS)
    {
      RSS2.LastAnsTimeStamp=SysTickCntr;
      RSS2.RetrCnt=0;RSS2.ErrCod=0;
      memcpy((void*)&iMState,(const void*)&RS2Buffer[RsPosSubCMD+1],sizeof(iMState));
      RSS2.State=RSstIdle;goto exit_ok;
    }
    if (RS2Buffer[RsPosSubCMD]==SubCmd_Config)
    {
      RSS2.RetrCnt=0;RSS2.ErrCod=0;
      memcpy((void*)&iR2_CFG,(const void*)&RS2Buffer[RsPosSubCMD+1],sizeof(iR2_CFG));
      RSS2.State=RSstIdle;goto exit_ok;
    }
    if (RS2Buffer[RsPosSubCMD]==SubCmd_Errors)
    {
      RSS2.RetrCnt=0;RSS2.ErrCod=0;
      memcpy((void*)&E_ERR,(const void*)&RS2Buffer[RsPosSubCMD+1],sizeof(E_ERR));
      RSS2.State=RSstIdle;goto exit_ok;
    }
    if (RS2Buffer[RsPosSubCMD]==SubCmd_SVpBV)
    {
      RSS2.RetrCnt=0;RSS2.ErrCod=0;
      memcpy((void*)&ti16,(const void*)&RS2Buffer[RsPosSubCMD+1],sizeof(ti16));
      ti32=ti16;SoftVersion|=ti32;
      RSS2.State=RSstIdle;goto exit_ok;
    }
    RSS2.ErrCod=11;
  }
  if (RS2Buffer[RsPosCMD]==COMM_SET) //check slave answer on COMM_SET
  {   //no another checks?
    if (RS2Buffer[RsPosSubCMD]==SubCmd_Config) { RSS2.RetrCnt=0;RSS2.ErrCod=0;RSS2.State=RSstIdle;goto exit_ok;}
    if (RS2Buffer[RsPosSubCMD]==SubCmd_OldComands){ RSS2.RetrCnt=0;RSS2.ErrCod=0;RSS2.State=RSstIdle;goto exit_ok;}
    RSS2.ErrCod=12;
  }
  RSS2.RetrCnt++;RSS2.ErrCod|=0x20;RSS2.State=RSstIdle; RSS2.CntAnalisRS=SysTickCntr+100;//start new question!!!
exi_err:;
globalrserrcnt+=RSS2.RetrCnt;
exit_ok:;
  AnalisRSIsBusy=0;
rsisbusy:;
}
//!==========================================================================================================
//........................................................................................
void USART2_IRQHandler (void) //MASTER VERSION
{
unsigned int IIR;
  IIR = USART_STAT0(USART2);

   if ((RSS2.State==RSstWait1Rcv))
	   if (IIR&USART_STAT0_RBNE)
		   {
			   RSS2.BegPnt=&RS2Buffer[0];RSS2.wCRC=0xffff;
			   RSS2.CntTimeout=SysTickCntr+3; //~3chars
			   *RSS2.BegPnt=(uint8_t)USART_DATA(USART2);Crc16ModbusFast(&RSS2.wCRC,RSS2.BegPnt);
			   RSS2.BegPnt++;
			   USART_REG_VAL(USART2, USART_INT_IDLE) |= BIT(USART_BIT_POS(USART_INT_IDLE)); //IDLE may be used as END if line have 2x680ohm!!
			   RSS2.State=RSstRcv;
//already cleared with reading form SR and DR if (IIR&(USART_SR_FE|USART_SR_IDLE|USART_SR_LBD)){USART1->SR=(USART_SR_FE|USART_SR_IDLE|USART_SR_LBD);}
			   goto exii;
		   }
	if ((RSS2.State==RSstTrn)) //&&(IIR&USART_STAT0_TBE))
	{
		RSS2.CntTimeout=SysTickCntr+3; //~3 chars
		if (RSS2.BegPnt==RSS2.EndPnt)
		{
			USART_REG_VAL(USART2, USART_INT_TBE) &= ~BIT(USART_BIT_POS(USART_INT_TBE));
			USART_DATA(USART2)=*RSS2.BegPnt;*RSS2.BegPnt=0xcc; //sc_add_30-09-2015
			USART_REG_VAL(USART2, USART_INT_TC) |= BIT(USART_BIT_POS(USART_INT_TC));
	        RSS2.State=RSstWaitTC_data;
			goto exii;
		}
		USART_DATA(USART2)=*RSS2.BegPnt;*RSS2.BegPnt=0xcc; //sc_add_30-09-2015
		RSS2.BegPnt++;RSS2.TraceCod++;
		goto exii;
	}
	if ((RSS2.State==RSstWaitTC_data)) //&&(IIR&USART_STAT0_TC)) //!!!!THIS IS A MASTER CASE!!!!!!!!!
	{ //  V--------MASTER go in Receiv, wait answer
		USART_REG_VAL(USART2, USART_INT_TC) &= ~BIT(USART_BIT_POS(USART_INT_TC));
		USART_CTL0(USART2)&=~USART_CTL0_TEN;
		//LL_USART_DisableIT_TC(USART1);LL_USART_DisableDirectionTx(USART1);
        RSS2.State=RSstWait1Rcv;
        USART2_RX_START();
	     RSS2.CntTimeout=SysTickCntr+100+100+RSS2.ExtraCntTimeout; //10+10ms bonus time to slave begin answer
		goto exii;
	}
	if (RSS2.State==RSstRcv)
	{
		if (IIR&(USART_STAT0_FERR|USART_STAT0_IDLEF)) // |USART_STAT0_LBDF))
		{
//already cleared with reading form SR and DR USART1->SR=(USART_SR_FE|USART_SR_IDLE|USART_SR_LBD);
			if (RSS2.wCRC==0){USARTinUSE_RX_DISABLE(USART2);RSS2.CntTimeout=SysTickCntr;goto exii;}
		}
		*RSS2.BegPnt=(uint8_t)USART_DATA(USART2);
		Crc16ModbusFast(&RSS2.wCRC,RSS2.BegPnt);RSS2.CntTimeout=SysTickCntr+3; //~3chars

		RSS2.BegPnt++;if (RSS2.BegPnt>=&RS2Buffer[RSBUFLEN-1]){RSS2.BegPnt--;USARTinUSE_RX_DISABLE(USART2);RSS2.CntTimeout=SysTickCntr;} //no waiting
		goto exii;
	}
	RSS2.ErrCod=(uint8_t)USART_DATA(USART2);
	RSS2.ErrCod=128; //unknown state, TX&RX must be disabled, go in idle
	USARTinUSE_RX_DISABLE(USART2);
	USART_REG_VAL(USART2, USART_INT_TBE) &= ~BIT(USART_BIT_POS(USART_INT_TBE));
	USART_REG_VAL(USART2, USART_INT_TC) &= ~BIT(USART_BIT_POS(USART_INT_TC));
	USART_CTL0(USART2)&=~USART_CTL0_TEN;
//	LL_USART_DisableIT_TXE(USART1);LL_USART_DisableIT_TC(USART1);LL_USART_DisableDirectionTx(USART1);
	RSS2.State=RSstIdle; //MASTER version
exii:;
}

//........................................................................................
//........................................................................................
//........................................................................................
//........................................................................................
//.............................................................................................
void GetSomething(uint8_t GetSubCmdCode)
{
                        RS2Buffer[RsPosDN]=RsSlaveDeviceN;RS2Buffer[RsPosCMD]=COMM_GET;RS2Buffer[RsPosSubCMD]=GetSubCmdCode;
                        RSS2.BegPnt=&RS2Buffer[0];RSS2.EndPnt=&RS2Buffer[RsPosSubCMD+2];
                        Calc_CS_WithCopy((uint8_t*)&RS2Buffer[0],(uint8_t*)&RS2Buffer[0],RsPosSubCMD+1);
                        RSS2.TraceCod=0;
}
//.............................................................................................
void Set_iOlCo(void)
{
  RS2Buffer[RsPosDN]=RsSlaveDeviceN;RS2Buffer[RsPosCMD]=COMM_SET;RS2Buffer[RsPosSubCMD]=SubCmd_OldComands;
  memcpy((void*)&RS2Buffer[RsPosSubCMD+1],(const void*)&iOlCo,sizeof(iOlCo));
         RSS2.BegPnt=&RS2Buffer[0];RSS2.EndPnt=&RS2Buffer[RsPosSubCMD+sizeof(iOlCo)+2];
  Calc_CS_WithCopy((uint8_t*)&RS2Buffer[0],(uint8_t*)&RS2Buffer[0],RsPosSubCMD+1+sizeof(iOlCo));
  RSS2.TraceCod=0;//NOT ZEROED IN CICLYC CHECK RSS2.ErrCod=0;
}
//.............................................................................................
//.............................................................................................
//.............................................................................................
void mainSSC_iOlCo(void)
{
	uint16_t lect=0;
  pak:
  	while (RSS2.State!=RSstIdle){;} //now {AnalisRS();} is irq called
  	if (SetSemB(&AnalisRSIsBusy, 64)) goto pak;
    RSS2.CntAnalisRS=SysTickCntr+137; //13.7ms
    RSS2.RetrCnt=0;
    RS2Buffer[RsPosDN]=RsSlaveDeviceN;RS2Buffer[RsPosCMD]=COMM_SET;RS2Buffer[RsPosSubCMD]=SubCmd_OldComands;
    memcpy((void*)&RS2Buffer[RsPosSubCMD+1],(const void*)&iOlCo,sizeof(iOlCo));
  	 RSS2.BegPnt=&RS2Buffer[0];RSS2.EndPnt=&RS2Buffer[RsPosSubCMD+sizeof(iOlCo)+2];
    Calc_CS_WithCopy((uint8_t*)&RS2Buffer[0],(uint8_t*)&RS2Buffer[0],RsPosSubCMD+1+sizeof(iOlCo));
    RSS2.TraceCod=0;RSS2.ErrCod=0;
    USARTinUSE_TX_START(UsartInUse);;
    AnalisRSIsBusy=0; while (RSS2.State!=RSstIdle){;}
  if (RSS2.ErrCod) {BeepCounter=10000;if (lect<5) goto pak;}else  BeepCounter=1;
}

//........................................................................................
//........................................................................................
void SGET_iSVpBV(void)
{
  uint16_t lect=0;
  pak:
  	 while (RSS2.State!=RSstIdle){;} //now {AnalisRS();} is irq called
  	 if (SetSemB(&AnalisRSIsBusy, 64)) goto pak;
    lect++;
    RSS2.CntAnalisRS=SysTickCntr+237; //23.7ms
    RSS2.RetrCnt=0;RSS2.ErrCod=0;
    GetSomething(SubCmd_SVpBV); //<<<<<<<<<<<<<<<<<
    USARTinUSE_TX_START(UsartInUse);
    AnalisRSIsBusy=0; while (RSS2.State!=RSstIdle){;}
    if (RSS2.ErrCod) {BeepCounter=10000;if (lect<5) goto pak;}else  BeepCounter=1;
}
//........................................................................................
void SGET_Config(void)
{
	  uint16_t lect=0;
	  pak:
	  	 while (RSS2.State!=RSstIdle){;} //now {AnalisRS();} is irq called
	  	 if (SetSemB(&AnalisRSIsBusy, 64)) goto pak;
	    lect++;
	    RSS2.CntAnalisRS=SysTickCntr+237; //23.7ms
  RSS2.ExtraCntTimeout=100;
  RSS2.RetrCnt=0;RSS2.ErrCod=0;
  GetSomething(SubCmd_Config);
  USARTinUSE_TX_START(UsartInUse);
  AnalisRSIsBusy=0; while (RSS2.State!=RSstIdle){;}
  if (RSS2.ErrCod) {BeepCounter=10000;if (lect<5) goto pak;}else  BeepCounter=1;
RSS2.ExtraCntTimeout=0;
}
//........................................................................................
void SGET_Errors(void)
{
	  uint16_t lect=0;
	  pak:
	  	 while (RSS2.State!=RSstIdle){;} //now {AnalisRS();} is irq called
	  	 if (SetSemB(&AnalisRSIsBusy, 64)) goto pak;
	    lect++;
	    RSS2.CntAnalisRS=SysTickCntr+237; //23.7ms
  RSS2.ExtraCntTimeout=100;
  RSS2.RetrCnt=0;RSS2.ErrCod=0;
  GetSomething(SubCmd_Errors);
  USARTinUSE_TX_START(UsartInUse);
  AnalisRSIsBusy=0; while (RSS2.State!=RSstIdle){;}
  if (RSS2.ErrCod) {BeepCounter=10000;if (lect<5) goto pak;}else  BeepCounter=1;
RSS2.ExtraCntTimeout=0;
}
//........................................................................................
//.............................................................................................
void SSC_iR2_CFG(void)
{
	  uint16_t lect=0;
	  pak:
	  	 while (RSS2.State!=RSstIdle){;} //now {AnalisRS();} is irq called
	  	 if (SetSemB(&AnalisRSIsBusy, 64)) goto pak;
	    lect++;
	    RSS2.CntAnalisRS=SysTickCntr+337; //33.7ms
	  RSS2.ExtraCntTimeout=100;
	  RSS2.RetrCnt=0;RSS2.ErrCod=0;
  RS2Buffer[RsPosDN]=RsSlaveDeviceN;RS2Buffer[RsPosCMD]=COMM_SET;RS2Buffer[RsPosSubCMD]=SubCmd_Config;
  memcpy((void*)&RS2Buffer[RsPosSubCMD+1],(const void*)&iR2_CFG,sizeof(iR2_CFG));
         RSS2.BegPnt=&RS2Buffer[0];RSS2.EndPnt=&RS2Buffer[RsPosSubCMD+sizeof(iR2_CFG)+2];
  Calc_CS_WithCopy((uint8_t*)&RS2Buffer[0],(uint8_t*)&RS2Buffer[0],RsPosSubCMD+1+sizeof(iR2_CFG));
  RSS2.TraceCod=0;RSS2.ErrCod=0;
  USARTinUSE_TX_START(UsartInUse);
  AnalisRSIsBusy=0; while (RSS2.State!=RSstIdle){;}
  if (RSS2.ErrCod) {BeepCounter=10000;if (lect<5) goto pak;}else  BeepCounter=1;
RSS2.ExtraCntTimeout=0;

//??wait for result?? while (RSS2.State!=RSstIdle) {AnalisRS();}
}
//.............................................................................................
//===========================================================================================//
void AddCRC(volatile uint16_t *pbCRC,volatile uint8_t *pbBuffer)
{
uint16_t wBit,wTmp;
  wBit=(uint16_t)*pbBuffer;
 *pbCRC^=wBit;
  wBit=8;
  do    {
          wTmp=*pbCRC&0x1;
          *pbCRC=*pbCRC>>1;
          if ( wTmp!=0 ) *pbCRC^=0xa001;
          wBit--;
        } while (wBit>0);
}

void Crc16ModbusFast(volatile uint16_t* lCrc, volatile uint8_t* lData) // sourcer32@gmail.com
{
    static const uint16_t CrcTable[16] = { // Nibble lookup for 0xA001 polynomial
        0x0000,0xCC01,0xD801,0x1400,0xF001,0x3C00,0x2800,0xE401,
        0xA001,0x6C00,0x7800,0xB401,0x5000,0x9C01,0x8801,0x4400 };
    uint16_t Crc;
    uint8_t Data;
    Crc=*lCrc; Data=*lData;
    Crc = Crc ^ Data;

    // Process 8-bits, 4 at a time, or 2 rounds

    Crc = (Crc >> 4) ^ CrcTable[Crc & 0xF];
    Crc = (Crc >> 4) ^ CrcTable[Crc & 0xF];

    *lCrc=Crc;
}

//===========================================================================================//
uint16_t Calc_CS(uint8_t* BegAd, uint16_t Len)
{
  uint16_t  wCRC=0xffff;
  for (;Len !=0 ; Len-- )
    {
     Crc16ModbusFast(&wCRC,BegAd);BegAd++;
    }// end for
   return wCRC;
}
//============================================================================================//
void Calc_CS_WithCopy(uint8_t* BegSourceAddr,uint8_t* BegDestAddr, uint16_t Len)
{
  uint16_t  wCRC=0xffff;
  for (;Len !=0 ; Len-- )
  {
    Crc16ModbusFast(&wCRC,BegSourceAddr);
	*BegDestAddr=*BegSourceAddr;
	BegSourceAddr++;BegDestAddr++;
   }// end for

  *BegDestAddr=(uint8_t)wCRC;
  BegDestAddr++;
  *BegDestAddr=(uint8_t)(wCRC>>8);
}
//==============================================================================================//
