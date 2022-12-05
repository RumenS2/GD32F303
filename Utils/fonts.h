/*
 * fonts.h
 *
 *  Created on: 11.02.2021 ã.
 *      Author: ru
 */

#ifndef INC_FONTS_H_
#define INC_FONTS_H_

 #include <stdint.h>
// Toshiba CG ROM type 0101
#define ToshibaFont 1
#define ToshibaFontXDim 8
#define ToshibaFontYDim 8
extern const unsigned char fontje[224][8];

#define AnonymosProFont9x17 11
#define AnonymosProFont9x17XDim 9
#define AnonymosProFont9x17YDim 17
extern const uint16_t Fontap9x17[256][17];

#define AnonymosProFont15x28 12
#define AnonymosProFont15x28XDim 15
#define AnonymosProFont15x28YDim 28
extern const uint16_t Fontap15x28[256][28];


#endif /* INC_FONTS_H_ */
