/**
  ******************************************************************************
  * @file    hw_config.h
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    11-July-2011
  * @brief   Target config file module.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HARDWARE_CONFIG_H
#define __HARDWARE_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "gd32f30x.h"

//#include "variables.h"
//#include "AnalisRS.h"

#define OPPSysTick_IRQn             0x01
#define xOPPRTC_IRQn                 0x0c  //not exist here
#define OPPOTG_FS_IRQn               0x07
#define OPPOTG_HS_IRQn               0x08
#define OPPUSART2_IRQn             0x04
#define OPPUSART1_IRQn             0x03
#define OPPUSART3_IRQn               0x02
#define OPPTIM7_IRQn               0x0a
#define OPPEXTI9_5_IRQn           0x0c

#define EiN()  __set_PRIMASK(0);
#define DiN()  __set_PRIMASK(1);


#define PA0_XP_IN_Pin GPIO_PIN_0

#define PA1_YP_IN_Pin GPIO_PIN_1

#define PA2_XM_IN_Pin GPIO_PIN_2

#define PA3_YM_IN_Pin GPIO_PIN_3

#define PA4_SPI0NSS_Pin GPIO_PIN_4 //spi1 stm32 used for touch reading

#define PA5_SPI0SCK_Pin GPIO_PIN_5 //spi1 stm32

#define PA6_SPI0MISO_Pin GPIO_PIN_6 //spi1 stm32

#define PA7_SPI0MOSI_Pin GPIO_PIN_7 //spi1 stm32

#define PA8_xxx_INT_Pin GPIO_PIN_8
#define PA8_xxx_INT_EXTI_IRQn EXTI4_15_IRQn

#define PA9_S1_IN_Pin GPIO_PIN_9

#define PA10_ChA_IN_Pin GPIO_PIN_10

#define PA11_ChB_IN_Pin GPIO_PIN_11

#define PA12_485_DRV_Pin GPIO_PIN_12

#define PA13_S2_IN_Pin GPIO_PIN_13

#define PA14_S3_IN_Pin GPIO_PIN_14

#define PA15_DispRST_Pin GPIO_PIN_15

#define PB0_xxx_INT_Pin GPIO_PIN_0
#define PB1_xxx_IN_Pin GPIO_PIN_1
#define PB2_xxx_IN_Pin GPIO_PIN_2
#define PB3_xxx_IN_Pin GPIO_PIN_3
#define PB4_xxx_IN_Pin GPIO_PIN_4
#define PB5_xxx_IN_Pin GPIO_PIN_5
#define PB6_xxx_CTS_Pin GPIO_PIN_6
#define PB7_xxx_IN_Pin GPIO_PIN_7
#define PB8_DispCS_Pin GPIO_PIN_8
#define PB9_DispRS_Pin GPIO_PIN_9
#define PB10_UART2_TX_Pin GPIO_PIN_10  //U1 in STM32
#define PB11_UART2_RX_Pin GPIO_PIN_11  //U1 in stm32
#define PB12_SPI1_NSS_Pin GPIO_PIN_12 //S2 in stm32 used for LCD
#define PB13_SPI1_SCK_Pin GPIO_PIN_13
#define PB14_SPI1_MISO_Pin GPIO_PIN_14
#define PB15_SPI1_MOSI_Pin GPIO_PIN_15

#define PC13_LEDDIM_Pin GPIO_PIN_13

#define PC14_S4_IN_Pin GPIO_PIN_14

#define PC15_S5_IN_Pin GPIO_PIN_15


#define Get_RIGHT   (GPIO_ISTAT(GPIOC)&PC14_S4_IN_Pin)
#define Get_UP      (GPIO_ISTAT(GPIOC)&PC15_S5_IN_Pin)
#define Get_LEFT    (GPIO_ISTAT(GPIOA)&PA13_S2_IN_Pin)
#define Get_DOWN    (GPIO_ISTAT(GPIOA)&PA14_S3_IN_Pin)
#define Get_CENTER  (GPIO_ISTAT(GPIOA)&PA9_S1_IN_Pin)
#define Get_ChB 	(GPIO_ISTAT(GPIOA)&PA10_ChA_IN_Pin)
#define Get_ChA 	(GPIO_ISTAT(GPIOA)&PA11_ChB_IN_Pin)


#define LoRCV_Enbl_485_2 GPIO_BC(GPIOA)=(uint32_t)GPIO_PIN_12      //000000
#define HiTRN_Enbl_485_2 GPIO_BOP(GPIOA)=(uint32_t)GPIO_PIN_12     //111111

#define HiSPI2_NSS GPIO_BOP(GPIOB)=(uint32_t)PB12_SPI1_NSS_Pin
#define LoSPI2_NSS GPIO_BC(GPIOB)=(uint32_t)PB12_SPI1_NSS_Pin

#define HiDRS GPIO_BOP(GPIOB)=(uint32_t)PB9_DispRS_Pin
#define LoDRS GPIO_BC(GPIOB)=(uint32_t)PB9_DispRS_Pin

#define HiILIRST GPIO_BOP(GPIOA)=(uint32_t)PA15_DispRST_Pin
#define LoILIRST GPIO_BC(GPIOA)=(uint32_t)PA15_DispRST_Pin


/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
 void Init(void);
 void SystemClock_Config(void);
 void MX_GPIO_Init(void);
 void MX_IWDG_Init(void);
 void MX_USART2_Init(void);
  void MX_CRC_Init(void);
  void MX_SPI1_Init(void);


#ifdef __cplusplus
}
#endif

#endif /* __HARDWARE_CONFIG_H */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
