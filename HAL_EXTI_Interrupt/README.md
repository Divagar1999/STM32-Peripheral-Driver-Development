# STM32 Interrupt-Driven Button-Controlled LED

## 📌 Overview

This project demonstrates how to control an LED using an external interrupt (EXTI) on the STM32N657X0-Q microcontroller.

The LED turns **ON when the user button is pressed** and turns **OFF when the button is released**. Instead of continuously polling the button state in the main loop, the microcontroller detects button state transitions through GPIO interrupts.

The project uses STM32 HAL APIs and introduces fundamental embedded systems concepts such as GPIO configuration, interrupt handling, rising-edge and falling-edge detection, and active-low LED control.

## 🎯 Objectives

- Configure a GPIO pin as an input with a pull-down resistor.
- Configure an external interrupt (EXTI) for button state changes.
- Detect rising and falling edges of the button signal.
- Control an active-low LED using STM32 HAL GPIO functions.
- Understand interrupt-driven programming versus polling.

## 🛠️ Hardware Requirements

- STM32 NUCLEO-N657X0-Q development board
- On-board user button
- On-board user LED
- USB cable for programming and debugging
- STM32CubeIDE

## ⚙️ Working Principle

The user button is configured as a GPIO input with a pull-down resistor.

| Button state | GPIO input | Interrupt edge | LED state |
|---|---|---|---|
| Released | LOW | Falling edge | OFF |
| Pressed | HIGH | Rising edge | ON |

The LED is active-low, meaning the LED turns ON when its GPIO output is LOW and OFF when its GPIO output is HIGH.

### Interrupt sequence

1. When the button is pressed, the input changes from LOW to HIGH.
2. A rising-edge EXTI interrupt is generated.
3. The interrupt callback drives the LED output LOW, turning it ON.
4. When the button is released, the input changes from HIGH to LOW.
5. A falling-edge EXTI interrupt is generated.
6. The interrupt callback drives the LED output HIGH, turning it OFF.

## 💻 Implementation

The following callbacks illustrate the core logic, assuming the STM32 HAL version supports separate rising-edge and falling-edge callbacks.

```c
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == User_Button_Pin)
    {
        // Button pressed: turn active-low LED ON
        HAL_GPIO_WritePin(Blue_LED_GPIO_Port,
                          Blue_LED_Pin,
                          GPIO_PIN_RESET);
    }
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == User_Button_Pin)
    {
        // Button released: turn active-low LED OFF
        HAL_GPIO_WritePin(Blue_LED_GPIO_Port,
                          Blue_LED_Pin,
                          GPIO_PIN_SET);
    }
}
```

**Note:** Configure the button EXTI for both rising and falling edges. Callback names depend on the STM32 HAL version; verify that your HAL actually invokes these functions. Some HAL versions use `HAL_GPIO_EXTI_Callback()` instead.

## 🔍 Key Concepts Learned

- **GPIO input and output configuration:** Setting up pins for button detection and LED control.
- **External interrupts (EXTI):** Responding to hardware events without continuously polling the input.
- **Rising-edge detection:** Detecting the transition from LOW to HIGH when the button is pressed.
- **Falling-edge detection:** Detecting the transition from HIGH to LOW when the button is released.
- **Active-low logic:** Understanding why writing `GPIO_PIN_RESET` turns the LED ON.
- **Interrupt callback functions:** Executing application logic in response to GPIO events.

## 🧪 Expected Result

- Press and hold the user button → LED remains ON.
- Release the user button → LED turns OFF.
- The main application does not need to continuously poll the button state.

Mechanical button bounce can generate additional transitions. For a simple press-and-hold demonstration, this may not be significant, but more robust applications may require debouncing.

## 🚀 Possible Improvements

- Add software debouncing for the user button.
- Implement button-controlled LED toggling.
- Use a timer to measure button press duration.
- Add low-power operation while waiting for button interrupts.
- Compare interrupt-driven input handling with polling.

## 📚 Tools and Technologies

- Microcontroller: STM32N657X0-Q
- Development board: STM32 NUCLEO-N657X0-Q
- Language: Embedded C
- Framework: STM32 HAL
- IDE: STM32CubeIDE
- Peripheral: GPIO / EXTI

## 👨‍💻 Author

Developed as a hands-on project to learn STM32 GPIO programming and interrupt-driven embedded software development.
