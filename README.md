# STM32-Learning
This repository documents my journey learning STM32 bare-metal programming 
(no HAL library) alongside Linux fundamentals. Each project is built from 
scratch using direct register manipulation, based on the STM32F446 
Reference Manual (RM0390).

**Hardware:** NUCLEO-F446RE

## 01_LED_Blink
Basic GPIO output - blinking the onboard LED (PA5).

**Concepts covered:**
- Memory-mapped registers and peripheral base addresses
- GPIO clock enable (RCC)
- GPIO mode configuration (MODER)
- Bitwise register manipulation

## 02_UART_Hello
Sending text from the STM32 to a PC terminal over UART.

**Concepts covered:**
- USART2 peripheral configuration
- Alternate function pin mapping (AF7)
- Baud rate calculation
- Status register polling
- C pointers and string handling

## 03_I2C_OLED
*Work in progress*

## Tools
- STM32CubeIDE
- STM32F446 Reference Manual (RM0390)
- Termite (serial terminal)
