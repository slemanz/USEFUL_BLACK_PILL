#include "common-defines.h"
#include "init.h"
#include "ticks.h"

int main(void)
{
    init_io();
    init_systick();

    uint64_t start_time = ticks_get();

    while (1)
    {
        if((ticks_get() - start_time) == 500)
        {
            GPIO_ToggleOutputPin(LED_EXT_PORT, LED_EXT_PIN);
            start_time = ticks_get();
        }
    }
}