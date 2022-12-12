/**
  ******************************************************************************
  * @file    hw_config.c
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    11-July-2011
  * @brief   This file provides targets hardware configuration.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/

#include "hw_config.h"

#include "gd32f30x.h"
#include "gd32f30x_it.h"  //for SysTickCntr



#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif

void Init(void)
{

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/
  /* MemoryManagement_IRQn interrupt configuration */
  NVIC_SetPriority(MemoryManagement_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  /* BusFault_IRQn interrupt configuration */
  NVIC_SetPriority(BusFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  /* UsageFault_IRQn interrupt configuration */
  NVIC_SetPriority(UsageFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  /* SVCall_IRQn interrupt configuration */
  NVIC_SetPriority(SVCall_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  /* DebugMonitor_IRQn interrupt configuration */
  NVIC_SetPriority(DebugMonitor_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  /* PendSV_IRQn interrupt configuration */
  NVIC_SetPriority(PendSV_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

//  LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
//  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_5)
//  {
//  Error_Handler();
//  }
//  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);


//  LL_RCC_HSE_Enable();
//   /* Wait till HSE is ready */
//  while(LL_RCC_HSE_IsReady() != 1)
//  {
//  }
	//^^^^^^^^^^^ this is done in SystemInit ^^^^^^^^^^^^^^^^^------------------



  rcu_osci_on(RCU_IRC40K);
  /* wait till RCU_IRC40K is ready */
  while(SUCCESS != rcu_osci_stab_wait(RCU_IRC40K)){
  }
//  LL_RCC_LSI_Enable();
   /* Wait till LSI is ready */
//  while(LL_RCC_LSI_IsReady() != 1)
//  {
//  }


//  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLP_DIV_2);

//  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
//  while(LL_RCC_PLL_IsReady() != 1)
//  {
//  }
//  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
//  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
//  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
 // LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
//  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
//  {
//  }
  //^^^^^^^^^^^^^^^^^^^^ this is done in SystemInit ^^^^^^^^^^^^^^^^^^-------------------
  SystemCoreClockUpdate(); //calculate current SystemCoreClock (set to 72MHz in system init)

  SysTick_Config(SystemCoreClock/(10*1000)); // 0.1ms=100us==>> See stm32f4xx_it.c SysTick_Handler!!!!!!!!!!!!!!!!!!!!!!!!!!
  systick_clksource_set(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn,OPPSysTick_IRQn);
}

/* CRC init function */
void MX_CRC_Init(void)
{

  // Peripheral clock enable
  rcu_periph_clock_enable(RCU_CRC);
}

/* IWDG init function */
void MX_IWDG_Init(void)
{

    rcu_osci_on(RCU_IRC40K);

    /* wait till IRC32K is ready */
    while(SUCCESS != rcu_osci_stab_wait(RCU_IRC40K)){
    }
    //clock is 40000 internal rc
    fwdgt_config(3*1000,FWDGT_PSC_DIV32); // 32 ~ 1.2 KHz

    fwdgt_enable();
}

void MX_USART2_Init(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_USART2);

    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, PB10_UART2_TX_Pin);
    gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, PB11_UART2_RX_Pin);

    usart_deinit(USART2);
    usart_word_length_set(USART2,8);
    usart_stop_bit_set(USART2,1);
    usart_parity_config(USART2, USART_PM_NONE);
    usart_baudrate_set(USART2, 115200U);
    usart_receive_config(USART2, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART2, USART_TRANSMIT_ENABLE);
    usart_enable(USART2);

  NVIC_SetPriority(USART2_IRQn, OPPUSART3_IRQn);  //prio from h2_config.h from
  NVIC_EnableIRQ(USART2_IRQn);
//!it is a master usart, send comands to ext board
//  usart_interrupt_enable(USART2, USART_INT_RBNE);
  LoRCV_Enbl_485_2;

}

void MX_SPI1_Init(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_SPI1);

    spi_parameter_struct spi_init_struct;

    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, PB13_SPI1_SCK_Pin | PB15_SPI1_MOSI_Pin);
    gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, PB14_SPI1_MISO_Pin);
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, PB12_SPI1_NSS_Pin); //soft nss

    /* chip select invalid*/
    HiSPI2_NSS;

    /* SPI0 parameter config */
    spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode          = SPI_MASTER;
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE; //SPI_CK_PL_HIGH_PH_1EDGE;
    spi_init_struct.nss                  = SPI_NSS_SOFT;
    spi_init_struct.prescale             = SPI_PSC_4 ; //apb1 here is 36mhz/4=9mhz (max standard speed for spi sck on ili9341 is 10MHz.)
    spi_init_struct.endian               = SPI_ENDIAN_MSB; //msb first
    spi_init(SPI1, &spi_init_struct);

    /* enable SPI0 */
    spi_enable(SPI1);

}



void MX_GPIO_Init(void)
{

    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);

    gpio_pin_remap_config(GPIO_SWJ_DISABLE_REMAP, ENABLE); //Disconnect jtag, from pa13 pa14 pa15 pb3 pb4

    gpio_bit_reset(GPIOA, GPIO_PIN_ALL);
    gpio_bit_reset(GPIOB, GPIO_PIN_ALL);
    gpio_bit_reset(GPIOC, GPIO_PIN_ALL);

//inputs
  /**/
    gpio_init(GPIOA,GPIO_MODE_IPU,GPIO_OSPEED_50MHZ,GPIO_PIN_ALL);
    gpio_init(GPIOB,GPIO_MODE_IPU,GPIO_OSPEED_50MHZ,0x00ff); //pb0-pb7
    gpio_init(GPIOC,GPIO_MODE_IPU,GPIO_OSPEED_50MHZ,PC14_S4_IN_Pin|PC15_S5_IN_Pin);

//ouputs
  /**/
    gpio_init(GPIOA,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,PA12_485_DRV_Pin|PA15_DispRST_Pin);
    gpio_init(GPIOB,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,PB8_DispCS_Pin|PB9_DispRS_Pin|PB12_SPI1_NSS_Pin);
    gpio_init(GPIOC,GPIO_MODE_OUT_PP,GPIO_OSPEED_50MHZ,PC13_LEDDIM_Pin);

}



/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
