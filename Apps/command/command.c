#include "common-defines.h"
#include "init.h"

// Function prototype
void delay(volatile uint32_t count);

int main(void)
{
    init_io();

    while (1)
    {
        GPIO_ToggleOutputPin(LED_EXT_PORT, LED_EXT_PIN);
        delay(3000000);
    }
}

void delay(volatile uint32_t count) {
    while (count-- > 0) {
        __asm("NOP"); // No operation for delay
    }
}


