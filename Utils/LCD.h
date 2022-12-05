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

void LCD_SetPoint(uint16_t x,uint16_t y, uint16_t pcolor);//»­µã
void FillBox(int16_t startx,int16_t starty,int16_t endx,int16_t endy,uint16_t rC);


#endif /* INC_LCD_H_ */
