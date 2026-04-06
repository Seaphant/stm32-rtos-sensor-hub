/**
  ******************************************************************************
  * @file    FreeRTOSConfig.h
  * @brief   FreeRTOS configuration — matches sensor-hub.ioc settings.
  ******************************************************************************
  */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
  #define configPRIO_BITS __NVIC_PRIO_BITS
#else
  #define configPRIO_BITS 4
#endif

#define configENABLE_FPU                         1
#define configENABLE_MPU                         0

#define configUSE_PREEMPTION                     1
#define configSUPPORT_STATIC_ALLOCATION          1
#define configSUPPORT_DYNAMIC_ALLOCATION         1
#define configUSE_IDLE_HOOK                      0
#define configUSE_TICK_HOOK                      0
#define configCPU_CLOCK_HZ                       (170000000UL)
#define configTICK_RATE_HZ                       ((TickType_t)1000)
#define configMAX_PRIORITIES                     (56)
#define configMINIMAL_STACK_SIZE                 ((uint16_t)128)
#define configTOTAL_HEAP_SIZE                    ((size_t)15360)
#define configMAX_TASK_NAME_LEN                  (16)
#define configUSE_TRACE_FACILITY                 1
#define configUSE_16_BIT_TICKS                   0
#define configUSE_MUTEXES                        1
#define configQUEUE_REGISTRY_SIZE                8
#define configUSE_RECURSIVE_MUTEXES              1
#define configUSE_COUNTING_SEMAPHORES            1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION   0
#define configRECORD_STACK_HIGH_ADDRESS           1

#define configUSE_MALLOC_FAILED_HOOK             1
#define configCHECK_FOR_STACK_OVERFLOW           2

/* Timer / daemon task. */
#define configUSE_TIMERS                         1
#define configTIMER_TASK_PRIORITY                 (2)
#define configTIMER_QUEUE_LENGTH                  10
#define configTIMER_TASK_STACK_DEPTH              (configMINIMAL_STACK_SIZE * 2)

#define configIDLE_SHOULD_YIELD                  1
#define configUSE_TASK_NOTIFICATIONS             1
#define configUSE_APPLICATION_TASK_TAG            0
#define configUSE_NEWLIB_REENTRANT               0
#define configENABLE_BACKWARD_COMPATIBILITY      1
#define configUSE_CO_ROUTINES                    0
#define configMAX_CO_ROUTINE_PRIORITIES          (2)
#define configGENERATE_RUN_TIME_STATS            0
#define configUSE_STATS_FORMATTING_FUNCTIONS     0
#define configUSE_TICKLESS_IDLE                  0
#define configUSE_DAEMON_TASK_STARTUP_HOOK       0

/* INCLUDE_ knobs required by the application code. */
#define INCLUDE_vTaskPrioritySet                 1
#define INCLUDE_uxTaskPriorityGet                1
#define INCLUDE_vTaskDelete                      1
#define INCLUDE_vTaskCleanUpResources            0
#define INCLUDE_vTaskSuspend                     1
#define INCLUDE_vTaskDelayUntil                  1
#define INCLUDE_vTaskDelay                       1
#define INCLUDE_xTaskGetSchedulerState           1
#define INCLUDE_eTaskGetState                    1
#define INCLUDE_xTaskGetCurrentTaskHandle        1
#define INCLUDE_xQueueGetMutexHolder             1
#define INCLUDE_xSemaphoreGetMutexHolder         1
#define INCLUDE_pcTaskGetTaskName                1
#define INCLUDE_uxTaskGetStackHighWaterMark       1
#define INCLUDE_xTaskGetHandle                   1
#define INCLUDE_xTaskAbortDelay                  1
#define INCLUDE_xTaskResumeFromISR               1
#define INCLUDE_xTimerPendFunctionCall            1

/*
 * Interrupt nesting — must match NVIC priority grouping (PRIORITYGROUP_4).
 * configLIBRARY_* are raw 4-bit priority values;
 * configKERNEL_INTERRUPT_PRIORITY and configMAX_SYSCALL_INTERRUPT_PRIORITY
 * are the shifted values that the CPU actually sees.
 */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY          15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY     5
#define configKERNEL_INTERRUPT_PRIORITY        (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))
#define configMAX_SYSCALL_INTERRUPT_PRIORITY   (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

/* FreeRTOS handlers are defined in the CMSIS-RTOS2 port or stm32g4xx_it.c. */
#define vPortSVCHandler    SVC_Handler
#define xPortPendSVHandler PendSV_Handler

/* The SysTick handler is called from the FreeRTOS port. */

/* Hook for assertion failures. */
#define configASSERT(x) if ((x) == 0) { taskDISABLE_INTERRUPTS(); for (;;); }

#endif /* FREERTOS_CONFIG_H */
