/**
  ******************************************************************************
  * @file    sysmem.c
  * @brief   System Memory calls — _sbrk implementation for newlib heap.
  ******************************************************************************
  */

#include <errno.h>
#include <stdint.h>

extern uint8_t _end;      /* defined by the linker */
extern uint8_t _estack;
extern uint32_t _Min_Stack_Size;

void *_sbrk(ptrdiff_t incr)
{
  static uint8_t *__sbrk_heap_end = NULL;
  uint8_t *prev_heap_end;

  if (__sbrk_heap_end == NULL)
  {
    __sbrk_heap_end = &_end;
  }

  prev_heap_end = __sbrk_heap_end;

  if ((uint8_t *)(__sbrk_heap_end + incr) > (uint8_t *)(&_estack - (uint32_t)(uintptr_t)&_Min_Stack_Size))
  {
    errno = ENOMEM;
    return (void *)-1;
  }

  __sbrk_heap_end += incr;
  return (void *)prev_heap_end;
}
