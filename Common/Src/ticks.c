#include "ticks.h"

static uint64_t ticks = 0;

uint64_t ticks_get(void)
{
    return ticks;
}

void SysTick_Handler(void)
{
    ticks++;
}
