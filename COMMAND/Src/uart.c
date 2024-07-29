#include "stm32f401.h"

void uart2_init(void)
{
	 // Configure UART2
	 UART2->BRR = (UART2_BRR_VALUE << 4); // Set baud rate
	 UART2->CR1 |= USART_CR1_TE; // Enable TX
	 UART2->CR1 |= USART_CR1_RE; // Enable RX
	 UART2->CR1 |= USART_CR1_UE; // Enable USART

	 // Enable RXNE interrupt (optional, if you handle interrupts)
	 //UART2_CR1 |= (1 << 5); // RXNE interrupt enable
}

void uart2_send_char(int c)
{
    while (!(UART2->SR & USART_SR_TXE)); // Wait until TXE (Transmit Data Register Empty)
    UART2->DR = (c & 0xFF); // Transmit character
}

char uart2_receive_char(void)
{
    while (!(UART2->SR & USART_SR_RXNE)); // Wait until RXNE (Receive Data Register Not Empty)
    return (char)(UART2->DR & 0xFF); // Read received character
}

void uart2_send_string(const char *str)
{
    while (*str)
    {
        uart2_send_char((int)*str++);
    }
}

int __io_putchar(int ch)
{
	uart2_send_char(ch);
	return ch;
}
