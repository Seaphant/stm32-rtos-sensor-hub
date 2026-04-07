# Test plan - v0.1

## Intent

Verify flash, **UART**, **FreeRTOS** tasks, and protocol strings on **NUCLEO-G474RE** (**STM32G474RET6**) before I2C sensor driver work.

## Environment

- USB to ST-Link; serial terminal **115200 8N1**, local echo off
- Firmware built either from the checked-in **`firmware/Makefile`** or from **STM32CubeIDE** using **`firmware/sensor-hub.ioc`**

## Manual checks

| ID | Step | Pass criterion |
|----|------|----------------|
| T1 | Flash **Debug** build | No hard fault; **LD2** toggles |
| T2 | Reset; watch UART | Exactly one **`BOOT`** line with a valid reset reason |
| T3 | Send `help` | `OK commands: help \| status \| start \| stop` |
| T4 | Send `status` | Line starts with `OK`; `mode=IDLE` |
| T5 | Send `start` | `OK mode=RUN`; ~10 **`TLM`** lines per second |
| T6 | Send `stop` | `OK mode=IDLE`; **`TLM`** stops |
| T7 | Send unknown command | `ERR unknown_cmd` |
| T8 | Send line longer than CLI buffer | Line discarded safely; no lock-up |

## Preconditions

- Generated project provides **`UART_HandleTypeDef hlpuart1`** and **`I2C_HandleTypeDef hi2c1`**
- **`app_init_early()`** and **`app_rtos_create_tasks()`** remain wired per [cube-integration.md](cube-integration.md)

## Post–v0.1

WHO_AM_I per sensor, I2C fault injection, IWDG reset reason, soak logs.

## Records

Keep UART captures under **`logs/`** (gitignored). Record the observed boot reason, CLI transcript, and `TLM` sample rate when you run the board smoke test.
