######################################################################
# Makefile for sensor-hub — STM32G474RETx + FreeRTOS
######################################################################

TARGET = sensor-hub

# Build output directory
BUILD_DIR = build

# Toolchain — use the ARM GCC bundled with STM32CubeIDE
CUBEIDE_PLUGINS = /Applications/STM32CubeIDE.app/Contents/Eclipse/plugins
GCC_DIR = $(wildcard $(CUBEIDE_PLUGINS)/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.*/tools)
PREFIX = $(GCC_DIR)/bin/arm-none-eabi-
ifdef GCC_ARM_NONE_EABI_PATH
  PREFIX = $(GCC_ARM_NONE_EABI_PATH)/bin/arm-none-eabi-
endif

CC  = $(PREFIX)gcc
AS  = $(PREFIX)gcc -x assembler-with-cpp
CP  = $(PREFIX)objcopy
SZ  = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

# MCU flags
CPU   = -mcpu=cortex-m4
FPU   = -mfpu=fpv4-sp-d16
FLOAT = -mfloat-abi=hard
MCU   = $(CPU) -mthumb $(FPU) $(FLOAT)

# C defines
C_DEFS = \
-DUSE_HAL_DRIVER \
-DSTM32G474xx \
-DCMSIS_device_header=\"stm32g4xx.h\"

# Include paths
C_INCLUDES = \
-ICore/Inc \
-IDrivers/STM32G4xx_HAL_Driver/Inc \
-IDrivers/STM32G4xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32G4xx/Include \
-IDrivers/CMSIS/Include \
-IMiddlewares/Third_Party/FreeRTOS/Source/include \
-IMiddlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 \
-IMiddlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F \
-IApp \
-ICommon \
-IServices \
-Imodules

######################################################################
# Source files
######################################################################

# Core sources
C_SOURCES = \
Core/Src/main.c \
Core/Src/freertos.c \
Core/Src/stm32g4xx_it.c \
Core/Src/stm32g4xx_hal_msp.c \
Core/Src/stm32g4xx_hal_timebase_tim.c \
Core/Src/system_stm32g4xx.c \
Core/Src/syscalls.c \
Core/Src/sysmem.c

# HAL driver sources (only modules we actually use)
C_SOURCES += \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cortex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_exti.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ramfunc.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_gpio.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_i2c.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_i2c_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim_ex.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart.c \
Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart_ex.c

# FreeRTOS sources
C_SOURCES += \
Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
Middlewares/Third_Party/FreeRTOS/Source/list.c \
Middlewares/Third_Party/FreeRTOS/Source/queue.c \
Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
Middlewares/Third_Party/FreeRTOS/Source/timers.c \
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c

# Application sources (handwritten)
C_SOURCES += \
App/app.c \
Common/log.c \
Services/cli.c \
Services/fault_mgr.c \
Services/telemetry.c \
modules/sensor_hub.c

# ASM sources
ASM_SOURCES = Core/Startup/startup_stm32g474retx.s

######################################################################
# CFLAGS / LDFLAGS
######################################################################

OPT = -Og

CFLAGS  = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT)
CFLAGS += -Wall -fdata-sections -ffunction-sections -fstack-usage
CFLAGS += -g -gdwarf-2
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
CFLAGS += --specs=nano.specs

ASFLAGS = $(MCU) -g -gdwarf-2

LDSCRIPT = STM32G474RETX_FLASH.ld

LIBS = -lc -lm -lnosys
LDFLAGS  = $(MCU) --specs=nano.specs -T$(LDSCRIPT) $(LIBS)
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref
LDFLAGS += -Wl,--gc-sections -Wl,--no-warn-rwx-segments
LDFLAGS += -u _printf_float

######################################################################
# Build rules
######################################################################

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

OBJECTS  = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

flash: $(BUILD_DIR)/$(TARGET).bin
	st-flash write $< 0x08000000

.PHONY: all clean flash

-include $(wildcard $(BUILD_DIR)/*.d)
