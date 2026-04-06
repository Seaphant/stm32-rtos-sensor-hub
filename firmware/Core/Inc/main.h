/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g4xx_hal.h"

/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* USER CODE END EFP */

/* USER CODE BEGIN Private defines */
#define APP_LED_GPIO_Port LD2_GPIO_Port
#define APP_LED_Pin       LD2_Pin
/* USER CODE END Private defines */

#define LD2_Pin        GPIO_PIN_5
#define LD2_GPIO_Port  GPIOA

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
