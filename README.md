# stm32-rtos-sensor-hub

Embedded C firmware for the **NUCLEO-G474RE** (**STM32G474RET6**) using **FreeRTOS**, **LPUART1** text I/O, and **I2C1** sensor-bus bring-up toward **LSM6DSO**, **TMP117**, and **INA219**. The repo includes both the authored application layers and the checked-in Cube-style project files under `firmware/`.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

## Project summary

This is a small embedded systems portfolio project focused on the part of firmware work that matters early on: MCU bring-up, task partitioning, UART observability, RTOS integration, and a clean boundary between generated HAL code and handwritten product code.

## Implemented now

- Checked-in STM32 project tree under `firmware/`, including `Core/`, `Drivers/`, `Middlewares/`, `STM32G474RETX_FLASH.ld`, `sensor-hub.ioc`, and [`firmware/Makefile`](firmware/Makefile)
- Handwritten application layers under `firmware/{App,Services,modules,Common}`
- `app_init_early()` wired into `main.c` after GPIO/UART/I2C init and before the scheduler
- `app_rtos_create_tasks()` wired into `MX_FREERTOS_Init()` to create the `app`, `tlm`, and `cli` tasks
- `printf` / `LOG_LINE` retargeted to **LPUART1** over the ST-Link virtual COM port
- `sensor_hub` stub path that publishes deterministic sample data while real device drivers are still pending
- RAM-backed fault log for queue drops and CLI line overflow
- After regenerating the Cube project, use [`firmware/PASTE_AFTER_CUBE_GENERATION.txt`](firmware/PASTE_AFTER_CUBE_GENERATION.txt) for the exact `USER CODE` snippets and linker paths

## Hardware platform

| Item | Details |
|------|---------|
| Board | ST **NUCLEO-G474RE** |
| MCU | **STM32G474RET6** |
| UART | **LPUART1** on ST-Link VCP, **115200 8N1** |
| I2C | **I2C1** on **PB8/PB9** |
| LED | **LD2** on **PA5** in the checked-in Cube config |
| Planned sensors | **LSM6DSO**, **TMP117**, **INA219** |

Supporting notes: [hardware/BOM.md](hardware/BOM.md), [hardware/wiring.md](hardware/wiring.md), [docs/pinout.md](docs/pinout.md)

## Architecture

- **App**: mode control, heartbeat timing, task creation, boot banner, sampling cadence
- **Services**: CLI, telemetry queue/formatting, fault logging
- **modules**: sensor aggregation entry point (`sensor_hub`) for future device-driver work
- **Common**: shared status and logging utilities

Details: [docs/architecture.md](docs/architecture.md) and [diagrams/architecture.txt](diagrams/architecture.txt)

## Runtime behavior

On reset, the firmware initializes GPIO, LPUART1, and I2C1, prints a single `BOOT` line, and starts FreeRTOS. The LED heartbeat toggles every 500 ms. The system starts in `IDLE`; `start` switches to `RUN` and emits stub `TLM` lines at roughly 10 Hz, while `stop` returns to `IDLE`.

Example boot line:

```text
BOOT mcu=STM32G474 t_ms=0 reason=BOR fw=0.1.0 cal=0
```

Example CLI session:

```text
help
OK commands: help | status | start | stop
start
OK mode=RUN
```

Example telemetry line:

```text
TLM seq=0 t_ms=120 imu_ax_mg=0 imu_ay_mg=0 imu_az_mg=1000 gx_mdps=0 gy_mdps=0 gz_mdps=0 tmp_c=23.681 vbus_mv=3300 i_ma=0
```

## Current status

- Current baseline: committed Cube/HAL/FreeRTOS project plus working application/task wiring
- Validation evidence in the repo: source layout, `.ioc`, linker script, Makefile, UART protocol docs, and a manual smoke-test plan
- Still pending: real LSM6DSO / TMP117 / INA219 drivers, WHO_AM_I checks, fault-on-wire reporting, watchdog policy, and calibration persistence

## Build / flash

This polish pass did **not** rebuild or reflash the project. The checked-in repo supports both of these workflows:

1. Import [`firmware/sensor-hub.ioc`](firmware/sensor-hub.ioc) into **STM32CubeIDE** and build there.
2. Or build from the command line:

```text
cd firmware
make all
make flash
```

`make flash` expects `st-flash` to be installed and a board connected. Serial monitoring uses the ST-Link VCP at **115200 8N1**.

## Why this project matters

For embedded roles, this repo shows board-focused firmware work rather than app-layer glue: clock and peripheral setup, RTOS task orchestration, HAL integration, serial debugging, memory-conscious C code, and an incremental path from bring-up to real sensor drivers.

## Docs index

| File | Purpose |
|------|---------|
| [docs/technical-spec.md](docs/technical-spec.md) | Technical scope and current baseline |
| [docs/architecture.md](docs/architecture.md) | Layering and data flow |
| [docs/protocol.md](docs/protocol.md) | `BOOT`, `TLM`, and CLI format |
| [docs/cube-integration.md](docs/cube-integration.md) | Regeneration and safe edit guidance |
| [docs/test-plan.md](docs/test-plan.md) | Manual target-side smoke checks |
| [docs/pinout.md](docs/pinout.md) | Pin assignments from the checked-in `.ioc` |
| [docs/roadmap.md](docs/roadmap.md) | Follow-on milestones |

## License

MIT - see [LICENSE](LICENSE).
