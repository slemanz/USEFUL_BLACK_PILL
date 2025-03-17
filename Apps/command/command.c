#include "common-defines.h"
#include "init.h"
#include "ticks.h"

#include <stdio.h>

int main(void)
{
    init_io();
    init_systick();
    init_serial();

    uint64_t start_time = ticks_get();
    uint64_t start_time2 = ticks_get();

    while (1)
    {
        if((ticks_get() - start_time) == 500)
        {
            GPIO_ToggleOutputPin(LED_EXT_PORT, LED_EXT_PIN);
            start_time = ticks_get();
        }

        if((ticks_get() - start_time2) == 2000)
        {
            printf("Testando!\n\r");
            start_time2 = ticks_get();
        }
    }
}