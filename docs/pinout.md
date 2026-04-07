# Pinout - NUCLEO-G474RE (v0.1)

## LPUART1 - ST-Link VCP (default)

Per ST **UM2505** §6.6.5, VCP uses **LPUART1** unless solder bridges move it to **USART1**.

| Function | MCU pin (typical Cube mapping) |
|----------|--------------------------------|
| LPUART1_TX | PA2 |
| LPUART1_RX | PA3 |

Confirm in generated **`main.h`** / **`.ioc`**.

## I2C1 - sensor bus

| Function | MCU pin |
|----------|---------|
| I2C1_SCL | PB8 |
| I2C1_SDA | PB9 |

Use **100 kHz** initially. Add **4.7 kΩ** pull-ups to **3.3 V** if a breakout lacks them.

## LD2

The checked-in `.ioc` config uses **PA5** as **GPIO_Output** with the label **LD2**. `Core/Inc/main.h` maps this through `APP_LED_GPIO_Port` / `APP_LED_Pin` for the application layer.

## NVIC

Document final UART vs I2C IRQ priorities in a comment once drivers use interrupts; v0.1 may run UART RX via polling in **`cli_task`**.
