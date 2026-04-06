/**
  ******************************************************************************
  * @file    stm32g4xx_hal_timebase_tim.c
  * @brief   HAL time base based on TIM6.
  *          SysTick is reserved for FreeRTOS; TIM6 drives HAL_GetTick().
  ******************************************************************************
  */

#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_tim.h"

TIM_HandleTypeDef htim6;

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  RCC_ClkInitTypeDef clkconfig;
  uint32_t uwTimclock;
  uint32_t uwPrescalerValue;
  uint32_t pFLatency;
  HAL_StatusTypeDef status;

  __HAL_RCC_TIM6_CLK_ENABLE();

  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);

  /* TIM6 is on APB1; if APB1 prescaler != 1, timer clock = 2x APB1 */
  uwTimclock = HAL_RCC_GetPCLK1Freq();
  if (clkconfig.APB1CLKDivider != RCC_HCLK_DIV1)
  {
    uwTimclock *= 2U;
  }

  uwPrescalerValue = (uint32_t)((uwTimclock / 1000000U) - 1U);

  htim6.Instance = TIM6;
  htim6.Init.Period = (1000000U / 1000U) - 1U;   /* 1 ms */
  htim6.Init.Prescaler = uwPrescalerValue;
  htim6.Init.ClockDivision = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  status = HAL_TIM_Base_Init(&htim6);
  if (status == HAL_OK)
  {
    status = HAL_TIM_Base_Start_IT(&htim6);
    if (status == HAL_OK)
    {
      HAL_NVIC_SetPriority(TIM6_DAC_IRQn, TickPriority, 0U);
      uwTickPrio = TickPriority;
      HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
    }
  }

  return status;
}

void HAL_SuspendTick(void)
{
  __HAL_TIM_DISABLE_IT(&htim6, TIM_IT_UPDATE);
}

void HAL_ResumeTick(void)
{
  __HAL_TIM_ENABLE_IT(&htim6, TIM_IT_UPDATE);
}
