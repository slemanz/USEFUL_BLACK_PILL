#include "common-defines.h"
#include "init.h"
#include "ticks.h"
#include "serial.h"


int main(void)
{
    init_io();
    init_systick();
    init_serial();
    
    serial_setup();

    uint64_t start_time = ticks_get();
    uint8_t ch = 0;

    while (1)
    {
        if((ticks_get() - start_time) == 500)
        {
            GPIO_ToggleOutputPin(LED_EXT_PORT, LED_EXT_PIN);
            start_time = ticks_get();
        }

		if(serial_data_available())
		{
            ch = serial_read_byte();
            serial_send(&ch, 1);
		}
    }
}