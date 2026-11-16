# STM32 GPIO Interrupt-Based Button-Controlled LED

## 📌 Project Overview

This project demonstrates how to configure and handle **external interrupts (EXTI) using direct register-level programming** on the STM32 Nucleo-N657X0-Q development board.

A user button connected to **PC13 (GPIO Port C, Pin 13)** is configured to generate an interrupt on both rising and falling edges. The interrupt handler detects the button state transition and controls the onboard LED connected to **PG8 (GPIO Port G, Pin 8)**.

When the button is pressed, the LED turns ON. When the button is released, the LED turns OFF. The application uses hardware interrupts instead of continuously polling the button state in the main loop.

## 🎯 Project Objectives

- Configure GPIO pins using direct register access.
- Enable peripheral clocks through the RCC registers.
- Configure PC13 as an input with an internal pull-down resistor.
- Configure PG8 as a push-pull output.
- Configure EXTI to detect both rising and falling edges.
- Enable and configure interrupt priority through the NVIC.
- Handle interrupt events using the `EXTI13_IRQHandler()` function.
- Control the LED using the GPIO bit set/reset register (BSRR).

## ⚙️ Hardware and Software Requirements

- **Development Board:** STM32 Nucleo-N657X0-Q
- **Microcontroller:** STM32N657 series
- **Programming Language:** Embedded C
- **IDE:** STM32CubeIDE
- **Configuration Approach:** Direct register-level programming
- **Peripheral Modules:** GPIO, RCC, EXTI, NVIC

## 🔄 Working Principle

1. The application initializes the HAL and configures the GPIO and EXTI peripherals.
2. PC13 is configured as an input with a pull-down resistor.
3. PG8 is configured as an output, and the LED is initialized to the OFF state.
4. EXTI line 13 is mapped to Port C and configured for rising and falling edges.
5. The NVIC enables the EXTI13 interrupt.
6. When the button is pressed, a rising-edge interrupt occurs and the LED turns ON.
7. When the button is released, a falling-edge interrupt occurs and the LED turns OFF.
8. The main loop remains available for other application tasks because button detection is interrupt-driven.

## 🧠 Key Concepts Learned

- GPIO register configuration using `MODER` and `PUPDR`
- RCC peripheral clock enable using `AHB4ENR`
- EXTI configuration using `EXTICR`, `IMR1`, `RTSR1` and `FTSR1`
- NVIC interrupt enable and priority configuration
- Interrupt pending flag handling using `RPR1` and `FPR1`
- GPIO output control using `BSRR`
- Rising-edge and falling-edge interrupt handling
- Difference between polling and interrupt-based input handling

## 📂 Code Highlights

| Register / Function | Purpose |
|---|---|
| `RCC->AHB4ENR` | Enables GPIO peripheral clocks |
| `GPIOC->MODER` | Configures PC13 as an input |
| `GPIOC->PUPDR` | Enables the pull-down resistor |
| `GPIOG->MODER` | Configures PG8 as an output |
| `EXTI->EXTICR[3]` | Maps EXTI line 13 to Port C |
| `EXTI->RTSR1` | Enables rising-edge detection |
| `EXTI->FTSR1` | Enables falling-edge detection |
| `EXTI13_IRQHandler()` | Handles button interrupts |
| `GPIOG->BSRR` | Sets or resets the LED output |

## ✅ Expected Output

- **Button released:** LED OFF
- **Button pressed:** LED ON
- **Button released after pressing:** LED OFF

The LED responds to button state transitions through interrupt handling without requiring continuous button polling.

## 🚀 Future Improvements

- Implement software debouncing for the mechanical button.
- Add interrupt-driven button-controlled LED toggling.
- Explore interrupt priority and interrupt latency.
- Integrate the interrupt-driven input with an RTOS task.
- Compare direct register programming with STM32 HAL-based implementation.

## 📚 Conclusion

This project provides practical experience with low-level STM32 peripheral programming and interrupt handling. It builds a foundation for understanding GPIO configuration, interrupt-driven firmware, NVIC operation, and efficient event handling in embedded systems.
