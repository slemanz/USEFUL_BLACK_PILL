#include "init.h"

void init_io(void)
{
    GPIO_Handle_t led;
    led.pGPIOx = LED_EXT_PORT;
    led.GPIO_PinConfig.GPIO_PinNumber = LED_EXT_PIN;
    led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
    GPIO_Init(&led);
}
