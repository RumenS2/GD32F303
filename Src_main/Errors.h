/*
 * Errors.h
 *
 *  Created on: Dec 3, 2022
 *      Author: ru
 */

#ifndef INC_ERRORS_H_
#define INC_ERRORS_H_


#define iEF_TooBigAngle       0x00000001
#define iEF_AntStillPresent     0x00000002
#define iEF_AntNotFound        0x00000004
#define iEF_AntStillPresent2     0x00000008
#define iEF_WireMainSnzFault     0x00000010
#define iEF_WireRevBurnSnzFault   0x00000020
#define iEF_RevBurningHigh      0x00000040
#define iEF_bEmptyProfile      0x00000080
#define iEF_CALisLost          0x00000100
#define iEF_CFGisLost          0x00000200 //for current profile
#define iEF_LSE_FailedToStart  0x00000400
#define iEF_ADCNotReady        0x00000800
#define iEF_BurnerProfSendErr  0x00001000
#define iEF_BurnerProfGetErr   0x00002000
#define iEF_dEmptyProfile      0x00004000
#define iEF_TouchCALisLost     0x00008000
#define iEF_MemFlashError      0x00010000
#define iEF_NMI_Error          0x00020000
#define iEF_xxx                0x00040000
#define iEF_xxxx               0x00080000
#define iEF_xxxxx              0x00100000
#define iEF_HSE_FailedToStart   0x00200000
#define iEF_IWDG_Reset          0x00400000
#define iEF_RTC_Batery          0x00800000
#define iEF_RTC_PRESC_ERR       0x01000000

#define iWF_HeaterIsON         0x80000000
#define iWF_PON_Reset          0x40000000
#define iWF_PINRST_Reset       0x08000000


extern volatile uint32_t LocErrorFlags;

#endif /* INC_ERRORS_H_ */
