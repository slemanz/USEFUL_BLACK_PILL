#include "stm32f401xx.h"

// Function prototype
void delay(volatile uint32_t count);

int main(void) {
    // Config PA8
    GPIO_Handle_t led;
    led.pGPIOx = GPIOA;
    led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
    led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
    GPIO_Init(&led);
    

    while (1)
    {
        GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_8);
        delay(3000000);
    }
}

void delay(volatile uint32_t count) {
    while (count-- > 0) {
        __asm("NOP"); // No operation for delay
    }
}


