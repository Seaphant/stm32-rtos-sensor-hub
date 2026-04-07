# Firmware

## Current layout

This directory already contains the checked-in STM32 project plus the handwritten application layers:

```text
firmware/
├── Makefile
├── sensor-hub.ioc
├── STM32G474RETX_FLASH.ld
├── Core/
├── Drivers/
├── Middlewares/
├── App/
├── Services/
├── modules/
└── Common/
```

## Hand-written sources

Maintain product code under:

- **`App/`** — application and RTOS task creation
- **`Services/`** — **CLI**, **telemetry**, **fault_mgr**
- **`modules/`** — **`sensor_hub`** and future chip-level glue (**not** Cube HAL)
- **`Common/`** — **shared types**, **`log.h`**, **`log.c`** (mutex + `log_line`)

**Recommendation:** Keep Cube’s HAL/CMSIS exclusively in the generated **`Drivers/`** folder. Put **`sensor_hub`** and future chip glue in **`modules/`** so the name **`Drivers/`** always means STM32 vendor code only.

## Include paths (STM32CubeIDE)

**Project → Properties → C/C++ Build → MCU GCC Compiler → Include paths** — add (adjust to your project root):

- `${ProjDirPath}/App`
- `${ProjDirPath}/Services`
- `${ProjDirPath}/modules`
- `${ProjDirPath}/Common`

## Integration hooks

See [docs/cube-integration.md](../docs/cube-integration.md) for **`main.c`**, **`freertos.c`**, and safe regeneration.

## Supported workflows

- **STM32CubeIDE**: import or reopen `sensor-hub.ioc`
- **Command line**: run `make all` or `make flash` from this directory

## Handles

Authored code expects:

- **`UART_HandleTypeDef hlpuart1`**
- **`I2C_HandleTypeDef hi2c1`**

If your `.ioc` renames handles, update the matching **`extern`** declarations in authored sources.

## printf

`Core/Src/syscalls.c` already retargets **`_write`** to **LPUART1** so **`LOG_LINE`** / **`printf`** reach the ST-Link VCP. Details: [docs/cube-integration.md](../docs/cube-integration.md).
