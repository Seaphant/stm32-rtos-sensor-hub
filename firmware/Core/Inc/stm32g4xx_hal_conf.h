/**
  ******************************************************************************
  * @file    stm32g4xx_hal_conf.h
  * @brief   HAL configuration file for STM32G4xx.
  ******************************************************************************
  */

#ifndef STM32G4xx_HAL_CONF_H
#define STM32G4xx_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#define HAL_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_EXTI_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_I2C_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_TIM_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED

#if !defined(HSE_VALUE)
  #define HSE_VALUE    24000000UL
#endif

#if !defined(HSE_STARTUP_TIMEOUT)
  #define HSE_STARTUP_TIMEOUT    100UL
#endif

#if !defined(HSI_VALUE)
  #define HSI_VALUE    16000000UL
#endif

#if !defined(HSI48_VALUE)
  #define HSI48_VALUE    48000000UL
#endif

#if !defined(LSI_VALUE)
  #define LSI_VALUE    32000UL
#endif

#if !defined(LSE_VALUE)
  #define LSE_VALUE    32768UL
#endif

#if !defined(LSE_STARTUP_TIMEOUT)
  #define LSE_STARTUP_TIMEOUT    5000UL
#endif

#if !defined(EXTERNAL_CLOCK_VALUE)
  #define EXTERNAL_CLOCK_VALUE    12288000UL
#endif

#define VDD_VALUE                    3300UL
#define TICK_INT_PRIORITY            15UL
#define USE_RTOS                     0UL
#define PREFETCH_ENABLE              0UL
#define INSTRUCTION_CACHE_ENABLE     1UL
#define DATA_CACHE_ENABLE            1UL

#define USE_HAL_I2C_REGISTER_CALLBACKS    0U
#define USE_HAL_TIM_REGISTER_CALLBACKS    0U
#define USE_HAL_UART_REGISTER_CALLBACKS   0U

#define USE_SPI_CRC                  0U

#ifdef HAL_RCC_MODULE_ENABLED
  #include "stm32g4xx_hal_rcc.h"
  #include "stm32g4xx_hal_rcc_ex.h"
#endif

#ifdef HAL_GPIO_MODULE_ENABLED
  #include "stm32g4xx_hal_gpio.h"
  #include "stm32g4xx_hal_gpio_ex.h"
#endif

#ifdef HAL_DMA_MODULE_ENABLED
  #include "stm32g4xx_hal_dma.h"
  #include "stm32g4xx_hal_dma_ex.h"
#endif

#ifdef HAL_CORTEX_MODULE_ENABLED
  #include "stm32g4xx_hal_cortex.h"
#endif

#ifdef HAL_EXTI_MODULE_ENABLED
  #include "stm32g4xx_hal_exti.h"
#endif

#ifdef HAL_FLASH_MODULE_ENABLED
  #include "stm32g4xx_hal_flash.h"
  #include "stm32g4xx_hal_flash_ex.h"
  #include "stm32g4xx_hal_flash_ramfunc.h"
#endif

#ifdef HAL_I2C_MODULE_ENABLED
  #include "stm32g4xx_hal_i2c.h"
  #include "stm32g4xx_hal_i2c_ex.h"
#endif

#ifdef HAL_PWR_MODULE_ENABLED
  #include "stm32g4xx_hal_pwr.h"
  #include "stm32g4xx_hal_pwr_ex.h"
#endif

#ifdef HAL_TIM_MODULE_ENABLED
  #include "stm32g4xx_hal_tim.h"
  #include "stm32g4xx_hal_tim_ex.h"
#endif

#ifdef HAL_UART_MODULE_ENABLED
  #include "stm32g4xx_hal_uart.h"
  #include "stm32g4xx_hal_uart_ex.h"
#endif

#ifdef HAL_PCD_MODULE_ENABLED
  #include "stm32g4xx_hal_pcd.h"
  #include "stm32g4xx_hal_pcd_ex.h"
#endif

#define assert_param(expr) ((void)0U)

#ifdef __cplusplus
}
#endif

#endif /* STM32G4xx_HAL_CONF_H */
