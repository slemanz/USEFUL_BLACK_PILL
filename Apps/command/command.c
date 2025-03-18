#include "common-defines.h"
#include "init.h"
#include "ticks.h"

uint8_t ch = 0;

void USART2_IRQHandler (void)
{
    const bool overrun_occurred = UART_GetFlagStatus(UART2, UART_FLAG_ORE);
	const bool received_data = UART_GetFlagStatus(UART2, UART_FLAG_RXNE);

	if(received_data || overrun_occurred)
	{
        ch = UART2->DR;
	}
}

int main(void)
{
    init_io();
    init_systick();
    init_serial();

    uint64_t start_time = ticks_get();

    while (1)
    {
        if((ticks_get() - start_time) == 500)
        {
            GPIO_ToggleOutputPin(LED_EXT_PORT, LED_EXT_PIN);
            start_time = ticks_get();
        }

		if(ch != 0)
		{
            uart_write(UART2, &ch, 1);
            ch = 0;
		}
    }
}