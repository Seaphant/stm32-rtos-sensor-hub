/**
  ******************************************************************************
  * @file    stm32g4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  */

#include "main.h"
#include "stm32g4xx_it.h"

extern TIM_HandleTypeDef htim6;

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/

void NMI_Handler(void)
{
  while (1) {}
}

void HardFault_Handler(void)
{
  while (1) {}
}

void MemManage_Handler(void)
{
  while (1) {}
}

void BusFault_Handler(void)
{
  while (1) {}
}

void UsageFault_Handler(void)
{
  while (1) {}
}

void DebugMon_Handler(void)
{
}

/******************************************************************************/
/* STM32G4xx Peripheral Interrupt Handlers                                    */
/******************************************************************************/

/**
  * @brief TIM6 global interrupt, DAC1 and DAC3 channel underrun error interrupt.
  *        Used as HAL timebase (SysTick is reserved for FreeRTOS).
  */
void TIM6_DAC_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim6);
}
