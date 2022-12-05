/*
 * gfunct.h
 *
 *  Created on: 11.02.2021 ã.
 *      Author: ru
 */

#ifndef INC_GFUNCT_H_
#define INC_GFUNCT_H_

#include "gd32f30x.h"

#define myabs(a)   ((a) < 0 ? ((a) * -1) : (a))
//================================================================================
typedef struct{
                uint8_t r,g,b;
              }rRGB;


#define RGB888565(r,g,b)        (uint16_t)( ( ((uint16_t)r>>3) <<11) | (((uint16_t)g>>2)<<5) | (uint16_t)(b>>3) )
//#define RGB888565(r,g,b) ((uint16_t)( (((uint16_t)r&0xf8)<<8) | (((uint16_t)g&0xFC)<<3) | ((uint16_t)b>>3) ))

//#define RGB888565(r,g,b) ((((r>>3)<<11) | ((g>>2)<<5) | (b>>3)))

#define CR_maroon_800000 RGB888565(128,0,0)
#define CR_dark_red_8B0000 RGB888565(139,0,0)
#define CR_brown_A52A2A RGB888565(165,42,42)
#define CR_firebrick_B22222 RGB888565(178,34,34)
#define CR_crimson_DC143C RGB888565(220,20,60)
#define CR_red_FF0000 RGB888565(255,0,0)
#define CR_tomato_FF6347 RGB888565(255,99,71)
#define CR_coral_FF7F50 RGB888565(255,127,80)
#define CR_indian_red_CD5C5C RGB888565(205,92,92)
#define CR_light_coral_F08080 RGB888565(240,128,128)
#define CR_dark_salmon_E9967A RGB888565(233,150,122)
#define CR_salmon_FA8072 RGB888565(250,128,114)
#define CR_light_salmon_FFA07A RGB888565(255,160,122)
#define CR_orange_red_FF4500 RGB888565(255,69,0)
#define CR_dark_orange_FF8C00 RGB888565(255,140,0)
#define CR_orange_FFA500 RGB888565(255,165,0)
#define CR_gold_FFD700 RGB888565(255,215,0)
#define CR_dark_golden_rod_B8860B RGB888565(184,134,11)
#define CR_golden_rod_DAA520 RGB888565(218,165,32)
#define CR_pale_golden_rod_EEE8AA RGB888565(238,232,170)
#define CR_dark_khaki_BDB76B RGB888565(189,183,107)
#define CR_khaki_F0E68C RGB888565(240,230,140)
#define CR_olive_808000 RGB888565(128,128,0)
#define CR_yellow_FFFF00 RGB888565(255,255,0)
#define CR_yellow_green_9ACD32 RGB888565(154,205,50)
#define CR_dark_olive_green_556B2F RGB888565(85,107,47)
#define CR_olive_drab_6B8E23 RGB888565(107,142,35)
#define CR_lawn_green_7CFC00 RGB888565(124,252,0)
#define CR_chart_reuse_7FFF00 RGB888565(127,255,0)
#define CR_green_yellow_ADFF2F RGB888565(173,255,47)
#define CR_dark_green_006400 RGB888565(0,100,0)
#define CR_green_008000 RGB888565(0,128,0)
#define CR_forest_green_228B22 RGB888565(34,139,34)
#define CR_lime_00FF00 RGB888565(0,255,0)
#define CR_lime_green_32CD32 RGB888565(50,205,50)
#define CR_light_green_90EE90 RGB888565(144,238,144)
#define CR_pale_green_98FB98 RGB888565(152,251,152)
#define CR_dark_sea_green_8FBC8F RGB888565(143,188,143)
#define CR_medium_spring_green_00FA9A RGB888565(0,250,154)
#define CR_spring_green_00FF7F RGB888565(0,255,127)
#define CR_sea_green_2E8B57 RGB888565(46,139,87)
#define CR_medium_aqua_marine_66CDAA RGB888565(102,205,170)
#define CR_medium_sea_green_3CB371 RGB888565(60,179,113)
#define CR_light_sea_green_20B2AA RGB888565(32,178,170)
#define CR_dark_slate_gray_2F4F4F RGB888565(47,79,79)
#define CR_teal_008080 RGB888565(0,128,128)
#define CR_dark_cyan_008B8B RGB888565(0,139,139)
#define CR_aqua_00FFFF RGB888565(0,255,255)
#define CR_cyan_00FFFF RGB888565(0,255,255)
#define CR_light_cyan_E0FFFF RGB888565(224,255,255)
#define CR_dark_turquoise_00CED1 RGB888565(0,206,209)
#define CR_turquoise_40E0D0 RGB888565(64,224,208)
#define CR_medium_turquoise_48D1CC RGB888565(72,209,204)
#define CR_pale_turquoise_AFEEEE RGB888565(175,238,238)
#define CR_aqua_marine_7FFFD4 RGB888565(127,255,212)
#define CR_powder_blue_B0E0E6 RGB888565(176,224,230)
#define CR_cadet_blue_5F9EA0 RGB888565(95,158,160)
#define CR_steel_blue_4682B4 RGB888565(70,130,180)
#define CR_corn_flower_blue_6495ED RGB888565(100,149,237)
#define CR_deep_sky_blue_00BFFF RGB888565(0,191,255)
#define CR_dodger_blue_1E90FF RGB888565(30,144,255)
#define CR_light_blue_ADD8E6 RGB888565(173,216,230)
#define CR_sky_blue_87CEEB RGB888565(135,206,235)
#define CR_light_sky_blue_87CEFA RGB888565(135,206,250)
#define CR_midnight_blue_191970 RGB888565(25,25,112)
#define CR_navy_000080 RGB888565(0,0,128)
#define CR_dark_blue_00008B RGB888565(0,0,139)
#define CR_medium_blue_0000CD RGB888565(0,0,205)
#define CR_blue_0000FF RGB888565(0,0,255)
#define CR_royal_blue_4169E1 RGB888565(65,105,225)
#define CR_blue_violet_8A2BE2 RGB888565(138,43,226)
#define CR_indigo_4B0082 RGB888565(75,0,130)
#define CR_dark_slate_blue_483D8B RGB888565(72,61,139)
#define CR_slate_blue_6A5ACD RGB888565(106,90,205)
#define CR_medium_slate_blue_7B68EE RGB888565(123,104,238)
#define CR_medium_purple_9370DB RGB888565(147,112,219)
#define CR_dark_magenta_8B008B RGB888565(139,0,139)
#define CR_dark_violet_9400D3 RGB888565(148,0,211)
#define CR_dark_orchid_9932CC RGB888565(153,50,204)
#define CR_medium_orchid_BA55D3 RGB888565(186,85,211)
#define CR_purple_800080 RGB888565(128,0,128)
#define CR_thistle_D8BFD8 RGB888565(216,191,216)
#define CR_plum_DDA0DD RGB888565(221,160,221)
#define CR_violet_EE82EE RGB888565(238,130,238)
#define CR_magenta_FF00FF RGB888565(255,0,255)
#define CR_orchid_DA70D6 RGB888565(218,112,214)
#define CR_medium_violet_red_C71585 RGB888565(199,21,133)
#define CR_pale_violet_red_DB7093 RGB888565(219,112,147)
#define CR_deep_pink_FF1493 RGB888565(255,20,147)
#define CR_hot_pink_FF69B4 RGB888565(255,105,180)
#define CR_light_pink_FFB6C1 RGB888565(255,182,193)
#define CR_pink_FFC0CB RGB888565(255,192,203)
#define CR_antique_white_FAEBD7 RGB888565(250,235,215)
#define CR_beige_F5F5DC RGB888565(245,245,220)
#define CR_bisque_FFE4C4 RGB888565(255,228,196)
#define CR_blanched_almond_FFEBCD RGB888565(255,235,205)
#define CR_wheat_F5DEB3 RGB888565(245,222,179)
#define CR_corn_silk_FFF8DC RGB888565(255,248,220)
#define CR_lemon_chiffon_FFFACD RGB888565(255,250,205)
#define CR_light_golden_rod_yellow_FAFAD2 RGB888565(250,250,210)
#define CR_light_yellow_FFFFE0 RGB888565(255,255,224)
#define CR_saddle_brown_8B4513 RGB888565(139,69,19)
#define CR_sienna_A0522D RGB888565(160,82,45)
#define CR_chocolate_D2691E RGB888565(210,105,30)
#define CR_peru_CD853F RGB888565(205,133,63)
#define CR_sandy_brown_F4A460 RGB888565(244,164,96)
#define CR_burly_wood_DEB887 RGB888565(222,184,135)
#define CR_tan_D2B48C RGB888565(210,180,140)
#define CR_rosy_brown_BC8F8F RGB888565(188,143,143)
#define CR_moccasin_FFE4B5 RGB888565(255,228,181)
#define CR_navajo_white_FFDEAD RGB888565(255,222,173)
#define CR_peach_puff_FFDAB9 RGB888565(255,218,185)
#define CR_misty_rose_FFE4E1 RGB888565(255,228,225)
#define CR_lavender_blush_FFF0F5 RGB888565(255,240,245)
#define CR_linen_FAF0E6 RGB888565(250,240,230)
#define CR_old_lace_FDF5E6 RGB888565(253,245,230)
#define CR_papaya_whip_FFEFD5 RGB888565(255,239,213)
#define CR_sea_shell_FFF5EE RGB888565(255,245,238)
#define CR_mint_cream_F5FFFA RGB888565(245,255,250)
#define CR_slate_gray_708090 RGB888565(112,128,144)
#define CR_light_slate_gray_778899 RGB888565(119,136,153)
#define CR_light_steel_blue_B0C4DE RGB888565(176,196,222)
#define CR_lavender_E6E6FA RGB888565(230,230,250)
#define CR_floral_white_FFFAF0 RGB888565(255,250,240)
#define CR_alice_blue_F0F8FF RGB888565(240,248,255)
#define CR_ghost_white_F8F8FF RGB888565(248,248,255)
#define CR_honeydew_F0FFF0 RGB888565(240,255,240)
#define CR_ivory_FFFFF0 RGB888565(255,255,240)
#define CR_azure_F0FFFF RGB888565(240,255,255)
#define CR_snow_FFFAFA RGB888565(255,250,250)
#define CR_black_000000 RGB888565(0,0,0)
#define CR_dim_gray_696969 RGB888565(105,105,105)
#define CR_gray_808080 RGB888565(128,128,128)
#define CR_dark_gray_A9A9A9 RGB888565(169,169,169)
#define CR_silver_C0C0C0 RGB888565(192,192,192)
#define CR_light_gray_D3D3D3 RGB888565(211,211,211)
#define CR_gainsboro_DCDCDC RGB888565(220,220,220)
#define CR_white_smoke_F5F5F5 RGB888565(245,245,245)
#define CR_white_FFFFFF RGB888565(255,255,255)
#define CR_fyellow_FFFF66 RGB888565(255,255,0x66)

#define MAIN_BCKG_COLOR CR_white_smoke_F5F5F5
#define MAIN2_BCKG_COLOR CR_white_FFFFFF

extern uint32_t rTextColor,rBackgroundColor;

//===============================================================================
typedef struct{
                int32_t XSize;
                int32_t YSize;
                rRGB  *pPallete; //will be array:rRGB Pallete[max256] 2or16or256
                uint8_t *pPicData; //will be array:uint8_t
                int32_t PicDataSize;
                uint8_t PicDataType; //0:1-2color(2bit) 2:15-16color(4bit) 16:255-256color(8bit) 256:3-24bitcolor(24bit type rRGB)
              }rPictInf;
//================================================================================
//void LCD_SetPoint(int x, int y, uint32_t rColor); //only this function is hardware dependent
//extern HDC hdc; //used only from SetPoint (i.e. WINDOWS)

void DrawRect(int x,int y,int W,int H,uint32_t rC);
//void SSD1963_FastFillBox(int32_t startx,int32_t starty,int32_t endx,int32_t endy,uint32_t rC);
void FillCircle(int32_t x,int32_t y,int32_t r,uint32_t rC);
void SetCircle(int32_t x_center,int32_t y_center,int32_t radius,uint32_t rC);

void SetBox(int32_t startx,int32_t starty,int32_t endx,int32_t endy,uint32_t rC);
void SetLine(int32_t startx,int32_t starty,int32_t endx,int32_t endy,uint32_t rC);
//void SetLine(int32 startx,int32 starty,int32 endx,int32 endy,uint32_t rC);
void SetLineMy(int16_t startx,int16_t starty,int16_t endx,int16_t endy,uint16_t cc);
void SetPicture(int32_t x, int32_t y, rPictInf *pI); //x,y=upper left corner

void DM_printfV (const char *s, ... );
void DM_putcharV(unsigned char c);
void DM_printf (const char *s, ... );
void DM_putchar(unsigned char c);
void DM_printf2x2 (const char *s, ... );
void DM_putchar2x2(unsigned char c);
//void DM_gotoxy(unsigned short x,unsigned short y);
#define DM_gotoxy(a,b) DM_x=a;DM_y=b
void DM_SetFontN(int FontN);


//void RestoreLast8x8x16printf(void);
//void DM_putchar_only8x8x16WithSave(unsigned char c);
//void DM_printf_only8x8x16WithSave(const char *s, ... );

extern unsigned short CurrentFontXDim,CurrentFontYDim,CurrentFont;
extern unsigned short DM_x,DM_y,DM_meth,DM_MaxPrintfChars;


#endif /* INC_GFUNCT_H_ */
