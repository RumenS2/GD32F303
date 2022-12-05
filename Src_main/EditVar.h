#ifndef __EDITVAR_H
#define __EDITVAR_H

#include "variables.h"

#define MAXDISPPOS 3
#define FIRSV_YPOS 5
extern int32_t EVAVvp32;
extern uint16_t EVAVvState;
void PrintVariable(EVCFG* p, uint16_t DispPosNumber, uint16_t BColor, uint16_t TColor);
int16_t EditViewActiveVar(EVCFG* p, uint16_t Vcolor, uint16_t VFont);

#endif
