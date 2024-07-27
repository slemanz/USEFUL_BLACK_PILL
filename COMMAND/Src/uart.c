#include "stm32f401.h"

void uart2_init(void)
{
	 RCC_APB1ENR |= (1 << 17); // Enable UART2 clock

	 // Configure UART2
	     UART2_BRR = UART2_BRR_VALUE; // Set baud rate
	     UART2_CR1 |= (1 << 2); // Enable TX
	     UART2_CR1 |= (1 << 3); // Enable RX
	     UART2_CR1 |= (1 << 0); // Enable USART

	     // Enable RXNE interrupt (optional, if you handle interrupts)
	     //UART2_CR1 |= (1 << 5); // RXNE interrupt enable
}

void uart2_send_char(char c)
{
    while (!(UART2_ISR & (1 << 7))); // Wait until TXE (Transmit Data Register Empty)
    UART2_TDR = c; // Transmit character
}

char uart2_receive_char(void)
{
    while (!(UART2_ISR & (1 << 5))); // Wait until RXNE (Receive Data Register Not Empty)
    return (char)(UART2_RDR & 0xFF); // Read received character
}

void uart2_send_string(const char *str)
{
    while (*str)
    {
        uart2_send_char(*str++);
    }
}
