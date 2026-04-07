# Architecture - v0.1

## Layout

The firmware tree is split between generated platform code and authored application code. The checked-in `firmware/` directory already contains the Cube-style project files, the linker script, and a Makefile.

```text
firmware/
├── Makefile
├── sensor-hub.ioc
├── STM32G474RETX_FLASH.ld
├── Core/          generated startup, init, IRQ, syscalls
├── Drivers/       STM32 HAL + CMSIS
├── Middlewares/   FreeRTOS + CMSIS-RTOS2
├── App/           application state, boot, task creation
├── Services/      cli, telemetry, fault_mgr
├── modules/       sensor_hub stub and future device glue
└── Common/        logging and shared status types
```

## Layering

| Layer | Path | Rules |
|-------|------|-------|
| Generated platform | `Core/`, `Drivers/`, `Middlewares/` | Regenerate from `.ioc` when needed; keep edits inside `USER CODE` blocks |
| Modules | `modules/` | Sensor-facing helpers return `status_t`; no RTOS queue or delay policy inside low-level chip access |
| Services | `Services/` | Own CLI parsing, telemetry queueing/formatting, and fault bookkeeping |
| App | `App/` | Own system mode, cadence, boot reporting, and task orchestration |

Retries, fault policy, and mode decisions belong in the service/app layers rather than in reusable device access helpers.

## Major units

| Unit | Responsibility |
|------|----------------|
| `Core/Src/main.c` | HAL init, GPIO/UART/I2C bring-up, call `app_init_early()`, start FreeRTOS |
| `Core/Src/freertos.c` | Create Cube default task, then call `app_rtos_create_tasks()` |
| `App/app.c` | Boot banner, `RUN` / `IDLE` state, LED heartbeat, sample cadence |
| `Services/telemetry.c` | Queue owner and `TLM` line formatting |
| `Services/cli.c` | Blocking UART receive loop and command dispatch |
| `Services/fault_mgr.c` | In-RAM fault ring buffer |
| `modules/sensor_hub.c` | Build one `sample_frame_t` from stub sensor values |
| `Core/Src/syscalls.c` | Route `printf` to `hlpuart1` |

## Data flow

```text
UART RX -> cli_task -> app_set_mode / app_get_status

app_task -> sensor_hub_read_all -> telemetry_publish -> queue -> telemetry_task -> LOG_LINE / printf -> LPUART1
```

## Runtime notes

- `app_init_early()` prints `BOOT` using `RCC->CSR`, then clears reset flags.
- The heartbeat LED uses `APP_LED_GPIO_Port` / `APP_LED_Pin`, which map to LD2 on PA5 in the checked-in Cube config.
- `sensor_hub` is still a stub: I2C1 is initialized, but real device transactions are not implemented yet.
- UART DMA, watchdog service policy, and sensor-specific fault handling remain future work.

## Build paths

The current repo supports either STM32CubeIDE via `sensor-hub.ioc` or the checked-in `firmware/Makefile`. This polish pass did not rebuild the target.
