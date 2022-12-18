/*
 * LCD.c
 *
 *  Created on: 11.02.2021 ã.
 *      Author: ru
 */

#include "LCD.h"
#include "gd32f30x_it.h"
#include "hw_config.h"

uint16_t BACK_COLOR, POINT_COLOR;

//void Address_set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void LCD_WR_DATA8(uint8_t da);
void LCD_WR_REG(uint8_t da);

void delayms(uint32_t dd)
{
dd=SysTickCntr+dd*10;
pak:
  if (dd>SysTickCntr) goto pak;
}

void LCD_Writ_Bus(register uint8_t da)
{

//  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
LoSPI2_NSS;
	SPI_DATA(SPI1) = (uint32_t)da;
	while (spi_i2s_flag_get(SPI1, SPI_FLAG_RBNE) == RESET){;} //valid in full duplex mode only!!!!
	da=(uint8_t)SPI_DATA(SPI1);
HiSPI2_NSS;
/*
    if (da&0x80) {LoSPI2_SCK;HiSPI2_MOSI;}else{LoSPI2_SCK;LoSPI2_MOSI;}
    HiSPI2_SCK;`
    if (da&0x40) {LoSPI2_SCK;HiSPI2_MOSI;}else{LoSPI2_SCK;LoSPI2_MOSI;}
    HiSPI2_SCK;
    if (da&0x20) {LoSPI2_SCK;HiSPI2_MOSI;}else{LoSPI2_SCK;LoSPI2_MOSI;}
    HiSPI2_SCK;
    if (da&0x10) {LoSPI2_SCK;HiSPI2_MOSI;}else{LoSPI2_SCK;LoSPI2_MOSI;}
    HiSPI2_SCK;
    if (da&0x08) {LoSPI2_SCK;HiSPI2_MOSI;}else{LoSPI2_SCK;LoSPI2_MOSI;}
    HiSPI2_SCK;
    if (da&0x04) {LoSPI2_SCK;HiSPI2_MOSI;}else{LoSPI2_SCK;LoSPI2_MOSI;}
    HiSPI2_SCK;
    if (da&0x02) {LoSPI2_SCK;HiSPI2_MOSI;}else{LoSPI2_SCK;LoSPI2_MOSI;}
    HiSPI2_SCK;
    if (da&0x01) {LoSPI2_SCK;HiSPI2_MOSI;}else{LoSPI2_SCK;LoSPI2_MOSI;}
    HiSPI2_SCK;
*/
}

uint32_t oldx=0;
uint32_t oldy=0;

void LCD_WR_DATA8(uint8_t da) //·¢ËÍÊý¾Ý-8Î»²ÎÊý
{
    HiDRS;
        LCD_Writ_Bus(da);
}

void LCD_WR_REG(uint8_t da)
{
    LoDRS;
        LCD_Writ_Bus(da);
}
 void LCD_WR_REG_DATA(uint16_t reg,uint16_t da)
{
    LCD_WR_REG(reg);

    	HiDRS;
        LCD_Writ_Bus(da>>8);
        LCD_Writ_Bus(da);
}

void Address_set(int16_t x1,int16_t y1,int16_t x2,int16_t y2)
{
   LCD_WR_REG(0x2a);
   LCD_WR_DATA8(x1>>8);
   LCD_WR_DATA8(x1);
   LCD_WR_DATA8(x2>>8);
   LCD_WR_DATA8(x2);

   LCD_WR_REG(0x2b);
   LCD_WR_DATA8(y1>>8);
   LCD_WR_DATA8(y1);
   LCD_WR_DATA8(y2>>8);
   LCD_WR_DATA8(y2);

   LCD_WR_REG(0x2C);

        oldx=0x80000;
        oldy=0x80000;

}

void Lcd_Init(void)
{

        HiSPI2_NSS; //==HiDCS;
        LoILIRST;
        delayms(20);
        HiILIRST;
        delayms(20);
        LoSPI2_NSS; //== LoDCS;
        delayms(2);
        oldx=0x80000;
        oldy=0x80000;

        LCD_WR_REG(0xCB);
    LCD_WR_DATA8(0x39);
    LCD_WR_DATA8(0x2C);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x34);
    LCD_WR_DATA8(0x02);

    LCD_WR_REG(0xCF);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0XC1);
    LCD_WR_DATA8(0X30);

        LCD_WR_REG(0xE8);
    LCD_WR_DATA8(0x85);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x78);

        LCD_WR_REG(0xEA);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x00);

        LCD_WR_REG(0xED);
    LCD_WR_DATA8(0x64);
    LCD_WR_DATA8(0x03);
    LCD_WR_DATA8(0X12);
    LCD_WR_DATA8(0X81);

    LCD_WR_REG(0xF7);
    LCD_WR_DATA8(0x20);

    LCD_WR_REG(0xC0);    //Power control
    LCD_WR_DATA8(0x23);   //VRH[5:0]

    LCD_WR_REG(0xC1);    //Power control
    LCD_WR_DATA8(0x10);   //SAP[2:0];BT[3:0]

    LCD_WR_REG(0xC5);    //VCM control
    LCD_WR_DATA8(0x3e); //¶Ô±È¶Èµ÷½Ú
    LCD_WR_DATA8(0x28);

    LCD_WR_REG(0xC7);    //VCM control2
    LCD_WR_DATA8(0x86);  //--

    LCD_WR_REG(0x36);    // Memory Access Control
    LCD_WR_DATA8(0x28); //         //48 68ÊúÆÁ//28 E8 ºáÆÁ

    LCD_WR_REG(0x3A);
    LCD_WR_DATA8(0x55);

    LCD_WR_REG(0xB1);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x18);

    LCD_WR_REG(0xB6);    // Display Function Control
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x82);
    LCD_WR_DATA8(0x27);

        LCD_WR_REG(0xF2);    // 3Gamma Function Disable
    LCD_WR_DATA8(0x00);

        LCD_WR_REG(0x26);    //Gamma curve selected
    LCD_WR_DATA8(0x01);

        LCD_WR_REG(0xE0);    //Set Gamma
    LCD_WR_DATA8(0x0F);
    LCD_WR_DATA8(0x31);
    LCD_WR_DATA8(0x2B);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x0E);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x4E);
    LCD_WR_DATA8(0xF1);
    LCD_WR_DATA8(0x37);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x10);
    LCD_WR_DATA8(0x03);
    LCD_WR_DATA8(0x0E);
    LCD_WR_DATA8(0x09);
    LCD_WR_DATA8(0x00);

    LCD_WR_REG(0XE1);    //Set Gamma
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x0E);
    LCD_WR_DATA8(0x14);
    LCD_WR_DATA8(0x03);
    LCD_WR_DATA8(0x11);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x31);
    LCD_WR_DATA8(0xC1);
    LCD_WR_DATA8(0x48);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x0F);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x31);
    LCD_WR_DATA8(0x36);
    LCD_WR_DATA8(0x0F);

        LCD_WR_REG(0x2A);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0xEF);

    LCD_WR_REG(0x2B);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x01);
    LCD_WR_DATA8(0x3F);
    LCD_WR_REG(0x11);    //Exit Sleep
    delayms(120);

     LCD_WR_REG(0x29);    //Display on
     LCD_WR_REG(0x2c);
}
//ÇåÆÁº¯Êý
//Color:ÒªÇåÆÁµÄÌî³äÉ«

        // Çàêðàøèâàíèå ïðÿìîóãîëüíèêà â çàäàííûé öâåò
void FillBox(int32_t startx,int32_t starty,int32_t endx,int32_t endy,uint16_t rC)
{
        uint8_t VH,VL;
    int32_t begX,endX;
    uint32_t i,imax;
    VH=rC>>8;VL=rC;
           begX=startx<endx ? startx:endx;
           endX=startx>endx ? startx:endx;
           imax=((endx-begX+1)*(endy-starty+1));
           Address_set(begX,starty,endX,endy);
           for (i=0;i<=imax;++i)
           {
            LCD_WR_DATA8(VH);
            LCD_WR_DATA8(VL);
           }
}

void LCD_Clear(uint16_t Color)
{
	FillBox(0,0,LCD_TPIXL_X-1,LCD_TPIXL_Y-1,Color);
}

void LCD_SetPoint(uint32_t x,uint32_t y, uint16_t pcolor)
{
uint32_t fl=0;
    if (x!=oldx)
    {
       if (x==(oldx+1)) {goto noset_X_addr_is_autoInc;}
       fl=1;
       LCD_WR_REG(0x2a);
       LCD_WR_DATA8(x>>8);
       LCD_WR_DATA8(x);
       if (oldx==0x80000)
       {
         LCD_WR_DATA8(320>>8);
         LCD_WR_DATA8(320&0xff);
       }
    }
noset_X_addr_is_autoInc:
    if (y!=oldy)
    {
     fl=1;
     LCD_WR_REG(0x2b);
     LCD_WR_DATA8(y>>8);
     LCD_WR_DATA8(y);
     if (oldy==0x80000)
     {
       LCD_WR_DATA8(240>>8);
       LCD_WR_DATA8(240&0xff);
     }
    }

    if (fl) LCD_WR_REG(0x2C); //set Xcntr and Ycntr to new(last set) 2Ah 2Bh values
    HiDRS;
    oldx=x;oldy=y;
    LCD_Writ_Bus(pcolor>>8);
    LCD_Writ_Bus(pcolor);
}
