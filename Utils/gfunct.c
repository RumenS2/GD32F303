/*
 * gfunct.c
 *
 *  Created on: 11.02.2021 г.
 *      Author: ru
 */


#include "LCD.h"
#include <stdio.h> //for DM_printf
#include <stdarg.h> //for DM_printf

#include "gfunct.h"
#include "fonts.h"

uint32_t rTextColor= RGB888565(0x7f,0x7f,0x7f);
uint32_t rBackgroundColor=RGB888565(0,0,0);

/*
void SSD1963_FastFillBox(int32_t startx,int32_t starty,int32_t endx,int32_t endy,uint32_t rC)
{
   int32_t i,begin,end;
   uint16_t tc,bc;
   if (startx==endx){SetLine(startx,starty,endx,endy,rC);goto exii;}
   if (starty==endy){SetLine(startx,starty,endx,endy,rC);goto exii;}

#if (ROTDISPLAY==180)
int16_t startx16,starty16,endx16,endy16;
startx16=(int16_t)startx;starty16=(int16_t)starty;endx16=(int16_t)endx;endy16=(int16_t)endy;
RotXYs(&startx16,&starty16);RotXYs(&endx16,&endy16);
startx=startx16;starty=starty16;endx=endx16;endy=endy16;
#endif
   if (startx>endx) {i=startx;startx=endx;endx=i;}
      if (starty>endy) {i=starty;starty=endy;endy=i;}
    LCD_GetColors(&tc,&bc);tc=(uint16_t)rC;LCD_SetColors(tc,bc);
    LCD_DrawFullRect((uint16_t) startx, (uint16_t)starty, (uint16_t)(endx-startx), (uint16_t)(endy-starty));
exii:;
}
*/
//inline void LCD_SetPoint(int x, int y, uint32_t rC)  //!!!!!!!!!!!!! this function is hardware dependent
//{
//    Display_PutPixel((uint16_t)(LCD_TPIXL_X-1-x),(uint16_t)(LCD_TPIXL_Y-1-y), (uint16_t)rC->r); //only for s1d13506!!!!
// if ((x>=0)&&(x<(LCD_TPIXL_X))) x=(LCD_TPIXL_X-1)-x;
// if ((y>=0)&&(y<(LCD_TPIXL_Y))) y=(LCD_TPIXL_Y-1)-y;

//    LCD_DrawPoint((uint16_t)x,(uint16_t)y, (uint16_t) rC);
//}



void ScrollDM_y(int y) //!!!!!!!!!!!!! this function is hardware dependent
{
  if (y<0)
  {
    //up&left scroll
    y=0-y;
/*
    for(int z=(bytesPerRow*y);z<9600;z++) //!!!!!!!!!!!!! hardware dependent
    {
      DM[(bytesPerRow*y)-z]=DM[z]; //!!!!!!!!!!!!! hardware dependent
      if (z>(9600-(bytesPerRow*y))) DM[z]=0; //!!!!!!!!!!!!! hardware dependent
    }
*/
  }
  else
  {
    //down&right scroll
  }
}
void ScrollDM_x(int x) //!!!!!!!!!!!!! this function is hardware dependent
{
  if (x<0)
  {
    //up&left scroll
    x=0-x;
/*
    for(int z=(bytesPerRow*y);z<9600;z++) //!!!!!!!!!!!!! hardware dependent
    {
      DM[(bytesPerRow*y)-z]=DM[z]; //!!!!!!!!!!!!! hardware dependent
      if (z>(9600-(bytesPerRow*y))) DM[z]=0; //!!!!!!!!!!!!! hardware dependent
    }
*/
  }
  else
  {
    //down&right scroll
  }
}
void SetLine(int32_t startx,int32_t starty,int32_t endx,int32_t endy,uint32_t rC)
{
         register int32_t t,distance;
         int32_t xerr=0,yerr=0,delta_x,delta_y;
         int32_t incx,incy;

       // вычисление расстояния в обоих направлениях
         delta_x=endx-startx;
         delta_y=endy-starty;

       // определение направления шага,
        //  шаг вычисляется либо по вертикальной, либо горизонтальной
        //  линии
          if (delta_x>0) incx=1;
          else  if (delta_x==0) incx=0;
          else  incx= -1;
          if (delta_y>0) incy=1;
          else  if (delta_y==0) incy=0;
          else  incy= -1;

        // определение какое расстояние больше
          delta_x=myabs(delta_x);
          delta_y=myabs(delta_y);
          if (delta_x>delta_y) distance=delta_x;
          else distance=delta_y;

        // вычерчивание линии
          for (t=0; t<=distance+1; t++)
          {
             //SetPoint(startx,starty,rC);
             LCD_SetPoint((uint16_t)startx,(uint16_t)starty,(uint16_t) rC);
             xerr+=delta_x;
             yerr+=delta_y;
             if (xerr>distance) {
                xerr-=distance;
                startx+=incx;
             }
             if (yerr>distance) {
                yerr-=distance;
                starty+=incy;
             }
          }
}

void SetLineMy(int16_t startx,int16_t starty,int16_t endx,int16_t endy,uint16_t rC)
{
         register int16_t t,distance;
         int16_t xerr=0,yerr=0,delta_x,delta_y;
         int16_t incx,incy;

       // вычисление расстояния в обоих направлениях
         delta_x=endx-startx;
         delta_y=endy-starty;

       // определение направления шага,
        //  шаг вычисляется либо по вертикальной, либо горизонтальной
        //  линии
          if (delta_x>0) incx=1;
          else  if (delta_x==0) incx=0;
          else  incx= -1;
          if (delta_y>0) incy=1;
          else  if (delta_y==0) incy=0;
          else  incy= -1;

        // определение какое расстояние больше
          delta_x=myabs(delta_x);
          delta_y=myabs(delta_y);
          if (delta_x>delta_y) distance=delta_x;
          else distance=delta_y;

        // вычерчивание линии
          for (t=0; t<=distance+1; t++)
          {
//             Display_PutPixel(startx,starty,  rC);// SetPointgg(startx,starty,rC);
             LCD_SetPoint((uint16_t)startx,(uint16_t)starty,(uint16_t) rC);
             xerr+=delta_x;
             yerr+=delta_y;
             if (xerr>distance) {
                xerr-=distance;
                startx+=incx;
             }
             if (yerr>distance) {
                yerr-=distance;
                starty+=incy;
             }
          }
}


void SetBox(int32_t startx,int32_t starty,int32_t endx,int32_t endy,uint32_t rC)
{
  SetLine(startx,starty,endx,starty,rC);// --
  SetLine(endx,starty,endx,endy,rC); //
  SetLine(startx,starty,startx,endy,rC);
  SetLine(startx,endy,endx,endy,rC);

}


#define asp_ratio 1.0;
         /* Функция печатает точки, определяющие окружность */
void plot_circle(int32_t x,int32_t y,int32_t x_center,int32_t y_center,uint32_t rC)
{
              int32_t startx,starty,endx,endy,x1,y1;
              starty=y*asp_ratio;
              endy=(y+1)*asp_ratio;
              startx=x*asp_ratio;
              endx=(x+1)*asp_ratio;

              for (x1=startx;x1<endx;++x1) {
                 LCD_SetPoint(x1+x_center,y+y_center,rC);
                 LCD_SetPoint(x1+x_center,y_center-y,rC);
                 LCD_SetPoint(x_center-x1,y+y_center,rC);
                 LCD_SetPoint(x_center-x1,y_center-y,rC);
              }

              for (y1=starty;y1<endy;++y1) {
                 LCD_SetPoint(y1+x_center,x+y_center,rC);
                 LCD_SetPoint(y1+x_center,y_center-x,rC);
                 LCD_SetPoint(x_center-y1,x+y_center,rC);
                 LCD_SetPoint(x_center-y1,y_center-x,rC);
              }
}

        /* Вычерчивание окружности с использованием алгоритма
           Брезенхама */
void SetCircle(int32_t x_center,int32_t y_center,int32_t radius,uint32_t rC)
{
            int32_t x,y,delta;
             y=radius;
             delta=3-2*radius;
             for (x=0;x<y; ) {
                 plot_circle(x,y,x_center,y_center,rC);
                 if (delta<0)
                    delta+=4*x+6;
                 else {
                    delta+=4*(x-y)+10;
                    y--;
                 }
                 x++;
              }
              x=y;
              if (y) plot_circle(x,y,x_center,y_center,rC);
           }

          /* Закрашивание окружности путем повторного вызова
            circle() с уменьшением радиуса */

void FillCircle(int32_t x,int32_t y,int32_t r,uint32_t rC)
{
               while (r) {
                  SetCircle(x,y,r,rC);
                  r--;
               }
}

void SetPicture(int32_t x, int32_t y, rPictInf *pI) //x,y=upper left corner
{
uint8_t *pIndex;
uint8_t PData;
int32_t ColCounter=0;
rRGB rC={0,0,0};
uint16_t y1,x1,F;

    pIndex=pI->pPicData;ColCounter=(uint32_t)pI->PicDataType;

    for(y1=0;y1<pI->YSize;y1++)
    {
      for(x1=0;x1<pI->XSize;x1++)
      {
        if (ColCounter>=256)
        {
          rC.r=*pIndex;pIndex++;rC.g=*pIndex;pIndex++;rC.b=*pIndex;pIndex++;
 //         SetPoint(x+x1, y+y1,&rC);
          LCD_SetPoint((uint16_t)(x+x1),(uint16_t)(y+y1),RGB888565(rC.r,rC.g,rC.b));
        }

        if ((ColCounter>=16)&&(ColCounter<=255))
        {
          PData=*pIndex;
//          SetPoint(x+x1, y+y1,&pI->pPallete[PData]);
 //SetPointgg(x+x1, y+y1, PData+192); // &pI->pPallete[PData]);
          rC=(pI->pPallete[PData]);
          LCD_SetPoint((uint16_t)(x+x1),(uint16_t)(y+y1),RGB888565(rC.r,rC.g,rC.b));

          pIndex++;
        }

        if ((ColCounter>=2)&&(ColCounter<=15))
        {
            PData=*pIndex;PData&=0x0f;
//            SetPoint(x+x1, y+y1,&pI->pPallete[PData]);
          rC=(pI->pPallete[PData]);
          LCD_SetPoint((uint16_t)(x+x1),(uint16_t)(y+y1),RGB888565(rC.r,rC.g,rC.b));
            PData=*pIndex;PData=(PData>>4);PData&=0x0f;
            x1++;
 //           SetPoint(x+x1, y+y1,&pI->pPallete[PData]);
          rC=(pI->pPallete[PData]);
          LCD_SetPoint((uint16_t)(x+x1),(uint16_t)(y+y1),RGB888565(rC.r,rC.g,rC.b));
           pIndex++;
        }

        if ((ColCounter>=0)&&(ColCounter<=1))
        {
           PData=*pIndex;
           for(F=0;F<8;F++)
           {
             PData=*pIndex;PData=(PData>>F);PData&=0x01;
          rC=(pI->pPallete[PData]);
          LCD_SetPoint((uint16_t)(x+x1),(uint16_t)(y+y1),RGB888565(rC.r,rC.g,rC.b));
             x1++;
           }
           x1--;
           pIndex++;
        }
      }
    }
}
//-------------------------------------------------------------------------------------------------
unsigned short DM_x,DM_y,DM_meth=0,DM_MaxPrintfChars=0;
unsigned short CurrentFontXDim,CurrentFontYDim;
unsigned short CurrentFont;

//void DM_gotoxy(unsigned short x,unsigned short y)
//{
//  DM_x=x;DM_y=y;
//}
//-------------------------------------------------------------------------------------------------
void DM_SetFontN(int FontN)
{
          CurrentFont=FontN;
  switch (FontN)
  {
    case ToshibaFont:
          CurrentFontXDim=ToshibaFontXDim;
          CurrentFontYDim=ToshibaFontYDim;
          break;
    case  AnonymosProFont9x17:
          CurrentFontXDim=AnonymosProFont9x17XDim;
          CurrentFontYDim=AnonymosProFont9x17YDim;
          break;
    case  AnonymosProFont15x28:
          CurrentFontXDim=AnonymosProFont15x28XDim;
          CurrentFontYDim=AnonymosProFont15x28YDim;
          break;
    default:
          CurrentFontXDim=ToshibaFontXDim; //default font
          CurrentFontYDim=ToshibaFontYDim; //default font
          CurrentFont=ToshibaFont;
          break;
   }
;
}
//-------------------------------------------------------------------------------------------------
char pbuf[0x140];
void DM_printf (const char *s, ... )
{
    unsigned short DM_xcopy;
    unsigned int cnt,rc,gc;
//    char pbuf[0x140];
    va_list arg;
    va_start (arg, s);
    gc=vsprintf (pbuf, s, arg);
    va_end (arg);
    DM_xcopy=DM_x;
    cnt=0;
    rc=pbuf[cnt];
    if ((rc==0x0)||(rc==0x0a)) goto exii;
    do
    {
      if (DM_x>((LCD_TPIXL_X-1)-CurrentFontXDim))
      {
        DM_x=0; //DM_x=DM_xcopy;
        DM_y+=CurrentFontYDim;
        if (DM_y>(LCD_TPIXL_Y-1)){DM_y-=CurrentFontYDim;ScrollDM_y(-CurrentFontYDim);}
      }
      DM_putchar((unsigned char)rc);
      cnt++;
      rc=pbuf[cnt];if (DM_MaxPrintfChars!=0) {if (DM_MaxPrintfChars<=cnt) goto exii;}
    }while ((rc!=0)&&(cnt<=gc)&&(rc!=0x0a));
exii:;
    if (rc==0x0a) { DM_y+=(CurrentFontYDim+2); DM_x=DM_xcopy;}
}
//-------------------------------------------------------------------------------------------------
void DM_putchar(unsigned char c) //max font DimX is 32
{
unsigned short int x,y;
unsigned int FontX=0;
  for(y=0;y<CurrentFontYDim;y++)
  {
    switch (CurrentFont)
    {
    case ToshibaFont:
          FontX=(unsigned int)fontje[c-0x20][y];
          break;
    case AnonymosProFont9x17:
          FontX=(unsigned int)Fontap9x17[c][y];
          break;
    case AnonymosProFont15x28:
          FontX=(unsigned int)Fontap15x28[c][y];
          break;
   }

    DM_x+=CurrentFontXDim;
    for (x=0;x<CurrentFontXDim;x++)
    {
      DM_x--;
      if (DM_meth==0) {if ((FontX&0x00000001)!=0) LCD_SetPoint(DM_x,DM_y,rTextColor); else LCD_SetPoint(DM_x,DM_y,rBackgroundColor);}
      if (DM_meth==1) {if ((FontX&0x00000001)!=0) LCD_SetPoint(DM_x,DM_y,rTextColor); }
      if (DM_meth==2) {if ((FontX&0x00000001)==0) LCD_SetPoint(DM_x,DM_y,rBackgroundColor);}
      FontX=FontX>>1;
    }
    DM_y++;
    if (DM_y>(LCD_TPIXL_Y-1)){DM_y-=CurrentFontYDim;ScrollDM_y(-CurrentFontYDim);}
  }
  DM_y-=CurrentFontYDim;
  DM_x+=CurrentFontXDim;
}
//-------------------------------------------------------------------------------------------------
void DM_printfV (const char *s, ... )
{
    unsigned short DM_ycopy;
    unsigned int cnt,rc,gc;
//    char pbuf[0x140];
    va_list arg;
    va_start (arg, s);
    gc=vsprintf (pbuf, s, arg);
    va_end (arg);
    DM_ycopy=DM_y;
    cnt=0;
    rc=pbuf[cnt];
    if ((rc==0x0)||(rc==0x0a)) goto exii;
    do
    {
      if (DM_y>((LCD_TPIXL_Y-1)-CurrentFontXDim))
      {
        DM_y=0; //DM_x=DM_xcopy;
        DM_x+=CurrentFontYDim;
        if (DM_x>(LCD_TPIXL_X-1)){DM_x-=CurrentFontYDim;ScrollDM_x(-CurrentFontYDim);}
      }
      DM_putcharV((unsigned char)rc);
      cnt++;if (DM_MaxPrintfChars!=0) {if (DM_MaxPrintfChars<=cnt) goto exii;}
      rc=pbuf[cnt];
    }while ((rc!=0)&&(cnt<=gc)&&(rc!=0x0a));
exii:;
    if (rc==0x0a) { DM_x+=(CurrentFontYDim+2); DM_y=DM_ycopy;}
}
//-------------------------------------------------------------------------------------------------
void DM_putcharV(unsigned char c) //max font DimX is 32
{
unsigned short int x,y;
unsigned int FontX;
  for(y=0;y<CurrentFontYDim;y++)
  {
    switch (CurrentFont)
    {
    case ToshibaFont:
          FontX=(unsigned int)fontje[c-0x20][y];
          break;
    case AnonymosProFont9x17:
          FontX=(unsigned int)Fontap9x17[c][y];
          break;
    case AnonymosProFont15x28:
          FontX=(unsigned int)Fontap15x28[c][y];
          break;
    default:
          FontX=(unsigned int)fontje[c-0x20][y];
          break;
   }

    //DM_y+=CurrentFontXDim;
    for (x=0;x<CurrentFontXDim;x++)
    {
      if (DM_meth==0) {if ((FontX&0x00000001)!=0) LCD_SetPoint(DM_x,DM_y,rTextColor); else LCD_SetPoint(DM_x,DM_y,rBackgroundColor);}
      if (DM_meth==1) {if ((FontX&0x00000001)!=0) LCD_SetPoint(DM_x,DM_y,rTextColor); }
      if (DM_meth==2) {if ((FontX&0x00000001)==0) LCD_SetPoint(DM_x,DM_y,rBackgroundColor);}
      FontX=FontX>>1;
      DM_y++;
    }
    DM_x++;DM_y-=CurrentFontXDim;
    if (DM_x>(LCD_TPIXL_X-1)){DM_x-=CurrentFontYDim;ScrollDM_x(-CurrentFontYDim);}
  }
  DM_x-=CurrentFontYDim;
  DM_y-=CurrentFontXDim;
}



//-------------------------------------------------------------------------------------------------
void DM_printf2x2 (const char *s, ... )
{
    unsigned short DM_xcopy;
    unsigned int cnt,rc,gc;
//    char pbuf[0x140];
    va_list arg;
    va_start (arg, s);
    gc=vsprintf (pbuf, s, arg);
    va_end (arg);
    DM_xcopy=DM_x;
    cnt=0;
    rc=pbuf[cnt];
    if ((rc==0x0)||(rc==0x0a)) goto exii;
    do
    {
      if (DM_x>((LCD_TPIXL_X-1)-CurrentFontXDim*2))
      {
        DM_x=DM_xcopy;
        DM_y+=CurrentFontYDim*2;
        if (DM_y>(LCD_TPIXL_Y-1)){DM_y-=CurrentFontYDim*2;ScrollDM_y(-CurrentFontYDim*2);}
      }
      DM_putchar2x2((unsigned char)rc);
      cnt++;if (DM_MaxPrintfChars!=0) {if (DM_MaxPrintfChars<=cnt) goto exii;}
      rc=pbuf[cnt];
    }while ((rc!=0)&&(cnt<=gc)&&(rc!=0x0a));
exii:;
    if (rc==0x0a) { DM_y+=(CurrentFontYDim*2+2); DM_x=DM_xcopy;}
}
//-------------------------------------------------------------------------------------------------
void DM_putchar2x2(unsigned char c)
{
unsigned short int x,y;
unsigned int FontX;
  if (DM_meth==0) FillBox(DM_x,DM_y,DM_x+CurrentFontXDim*2,DM_y+CurrentFontYDim*2,rBackgroundColor);
  for(y=0;y<CurrentFontYDim;y++)
  {
    switch (CurrentFont)
    {
    case ToshibaFont:
          FontX=(unsigned int)fontje[c-0x20][y];
          break;
    case AnonymosProFont9x17:
          FontX=(unsigned int)Fontap9x17[c][y];
          break;
    case AnonymosProFont15x28:
          FontX=(unsigned int)Fontap15x28[c][y];
          break;
    default:
          FontX=(unsigned int)fontje[c-0x20][y];
          break;
   }
    DM_x+=CurrentFontXDim*2;
    for (x=0;x<CurrentFontXDim;x++)
    {
      DM_x--;DM_x--;
      if ((FontX&0x00000001)!=0)
      {
        if (DM_meth!=2)
        {
          LCD_SetPoint(DM_x,DM_y,rTextColor);
          LCD_SetPoint(DM_x+1,DM_y,rTextColor);
          LCD_SetPoint(DM_x,DM_y+1,rTextColor);
          LCD_SetPoint(DM_x+1,DM_y+1,rTextColor);
//            SSD1963_FastFillBox(DM_x,DM_y,DM_x+1,DM_y+1,rTextColor); //4 points box
        }
      }
      else
      {
        if (DM_meth==2) //dm meth==0 with SSD1963_FastFillBox
        {
          LCD_SetPoint(DM_x,DM_y,rBackgroundColor);
          LCD_SetPoint(DM_x+1,DM_y,rBackgroundColor);
          LCD_SetPoint(DM_x,DM_y+1,rBackgroundColor);
          LCD_SetPoint(DM_x+1,DM_y+1,rBackgroundColor);
//            SSD1963_FastFillBox(DM_x,DM_y,DM_x+1,DM_y+1,rBackgroundColor); //4 points box
        }
      }
      FontX=FontX>>1;
    }
    DM_y++;DM_y++;
    if (DM_y>(LCD_TPIXL_Y-1)){DM_y-=CurrentFontYDim*2;ScrollDM_y(-CurrentFontYDim*2);}
  }
  DM_y-=CurrentFontYDim*2;
  DM_x+=CurrentFontXDim*2;
}

void DrawRect(int x,int y,int W,int H,uint32_t rC)
{
        SetLine(x,y,x+W,y,rC);
                SetLine(x,y+H,x+W,y+H,rC);
                SetLine(x,y,x,y+H,rC);
                SetLine(x+W,y,x+W,y+H,rC);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/*
uint8_t ArrOldPixels[8*8*16];
uint16_t OldArrIdx=0,OldX,OldY,CurrentArrIdx;
void DM_printf_only8x8x16WithSave(const const char *s, ... )
{
    unsigned short DM_xcopy;
    unsigned int cnt,rc,gc;
//    char pbuf[0x140];
    va_list arg;
    va_start (arg, s);
    gc=vsprintf (pbuf, s, arg);
    va_end (arg);
    DM_xcopy=DM_x;
    CurrentArrIdx=0;
    if (OldArrIdx==0) OldX=DM_x;OldY=DM_y;
    cnt=0;
    rc=pbuf[cnt];
    if ((rc==0x0)||(rc==0x0a)) goto exii;
    do
    {
      if (DM_x>((LCD_TPIXL_X-1)-CurrentFontXDim))
      {
        DM_x=0; //DM_x=DM_xcopy;
        DM_y+=8;
        if (DM_y>(LCD_TPIXL_Y-1)){DM_y-=CurrentFontYDim;ScrollDM_y(-CurrentFontYDim);}
      }
      DM_putchar_only8x8x16WithSave((unsigned char)rc);
      cnt++;
      rc=pbuf[cnt];
    }while ((rc!=0)&&(cnt<=gc)&&(rc!=0x0a));
exii:;
    if (rc==0x0a) { DM_y+=(CurrentFontYDim+2); DM_x=DM_xcopy;}
}
//-------------------------------------------------------------------------------------------------

void DM_putchar_only8x8x16WithSave(unsigned char c)
{
unsigned short int x,y;
unsigned int FontX;
  for(y=0;y<8;y++)
  {
    FontX=(unsigned int)fontje[c-0x20][y];
    DM_x+=8;
    for (x=0;x<8;x++)
    {
      if (CurrentArrIdx>=OldArrIdx)
      {
       ArrOldPixels[OldArrIdx]=Display_GetPixel(DM_x,DM_y);if (OldArrIdx<(8*8*16)) OldArrIdx++;
      }
      CurrentArrIdx++;
      if ((FontX&0x00000001)!=0) SetPoint(DM_x,DM_y,&rTextColor); else SetPoint(DM_x,DM_y,&rBackgroundColor);
//      if ((FontX&0x00000001)!=0) SED133x_SetPixel(DM_x,DM_y,1); else SED133x_SetPixel(DM_x,DM_y,0);
      FontX=FontX>>1;
      DM_x--;
    }
    DM_y++;
    if (DM_y>(LCD_TPIXL_Y-1)){DM_y-=CurrentFontYDim;ScrollDM_y(-CurrentFontYDim);}
  }
  DM_y-=CurrentFontYDim;
  DM_x+=CurrentFontXDim;
}

//==================================================
void RestoreLast8x8x16printf(void)
{
uint16_t U0,Ux,Uy;
if (OldArrIdx==0) goto exii;
Ux=8;Uy=0;
for (U0=0;U0<OldArrIdx;U0++)
{
  Display_PutPixel(OldX+Ux,OldY+Uy,ArrOldPixels[U0]);
  Ux--;
  if (Ux==0)
  {
    Ux=8;Uy++;
    if (Uy==8) {Uy=0;OldX+=8;}
  }
}
OldArrIdx=0;
exii:;
}
*/
//-------------------------------------------------------------------------------------------------
