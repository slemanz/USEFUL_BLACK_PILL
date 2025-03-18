#include "serial.h"
#include "ring-buffer.h"
#include "stm32f401xx.h"

static ring_buffer_t rb = {0U};
static uint8_t data_buffer[SERIAL_BUFFER_SIZE] = {0U};

void USART2_IRQHandler(void)
{
	const bool overrun_occurred = UART_GetFlagStatus(UART2, UART_FLAG_ORE);
	const bool received_data = UART_GetFlagStatus(UART2, UART_FLAG_RXNE);

	if(received_data || overrun_occurred)
	{
		if(ring_buffer_write(&rb, (uint8_t)uart_read_byte(UART2)))
		{
			// handle some error/failure
		}
	}
}

void serial_setup(void)
{
    ring_buffer_setup(&rb, data_buffer, SERIAL_BUFFER_SIZE);
}

bool serial_data_available(void)
{
    return !ring_buffer_empty(&rb);
}

uint32_t serial_read(uint8_t *data, const uint32_t Len)
{
    if(Len == 0)
	{
		return 0;
	}
	
	for(uint32_t bytes_read = 0; bytes_read < Len; bytes_read++)
	{
		if(!ring_buffer_read(&rb, &data[bytes_read]))
		{
			return bytes_read;
		}
	}

	return Len;
}

uint8_t serial_read_byte(void)
{
    uint8_t byte;
	
	(void)serial_read(&byte, 1);

	return byte;
}

void serial_send(uint8_t *data, const uint32_t Len)
{
    uart_write(UART2, data, Len);
}

