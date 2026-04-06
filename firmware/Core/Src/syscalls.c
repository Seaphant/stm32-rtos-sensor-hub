/**
  ******************************************************************************
  * @file    syscalls.c
  * @brief   Newlib syscall stubs — routes printf/vprintf to LPUART1.
  ******************************************************************************
  */

#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <unistd.h>

#include "stm32g4xx_hal.h"

extern UART_HandleTypeDef hlpuart1;

int __io_putchar(int ch)
{
  uint8_t c = (uint8_t)ch;
  HAL_UART_Transmit(&hlpuart1, &c, 1, HAL_MAX_DELAY);
  return ch;
}

int __io_getchar(void)
{
  uint8_t c = 0;
  HAL_UART_Receive(&hlpuart1, &c, 1, HAL_MAX_DELAY);
  return (int)c;
}

int _write(int file, char *ptr, int len)
{
  (void)file;
  HAL_UART_Transmit(&hlpuart1, (uint8_t *)ptr, (uint16_t)len, HAL_MAX_DELAY);
  return len;
}

int _read(int file, char *ptr, int len)
{
  (void)file;
  (void)ptr;
  (void)len;
  return -1;
}

int _close(int file)   { (void)file; return -1; }
int _isatty(int file)  { (void)file; return 1; }
int _lseek(int file, int ptr, int dir) { (void)file; (void)ptr; (void)dir; return 0; }
int _fstat(int file, struct stat *st) { (void)file; st->st_mode = S_IFCHR; return 0; }

int _getpid(void)      { return 1; }
int _kill(int pid, int sig) { (void)pid; (void)sig; errno = EINVAL; return -1; }

void _exit(int status)
{
  (void)status;
  while (1) {}
}
