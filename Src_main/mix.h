/*
 * mix.h
 *
 *  Created on: Dec 4, 2022
 *      Author: ru
 */

#ifndef MIX_H_
#define MIX_H_

int16_t GetCurrentProfilFromDrvBrd(void);
int16_t SendCurrentProfilToDrvBrd(void);
int16_t ReadCFGfromFlash(uint16_t pn);
int16_t WriteCFGtoFlash(uint16_t pn);
#endif /* MIX_H_ */
