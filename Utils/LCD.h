/*
 * LCD.h
 *
 *  Created on: 11.02.2021 ã.
 *      Author: ru
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

 #include <stdint.h>

#define LCD_TPIXL_X 320
#define LCD_TPIXL_Y 240

extern  uint16_t BACK_COLOR;   //±³¾°É«£¬»­±ÊÉ«

void Lcd_Init(void);
void LCD_Clear(uint16_t Color);

void LCD_SetPoint(uint32_t x,uint32_t y, uint16_t pcolor);//»­µã
void FillBox(int32_t startx,int32_t starty,int32_t endx,int32_t endy,uint16_t rC);


#endif /* INC_LCD_H_ */
