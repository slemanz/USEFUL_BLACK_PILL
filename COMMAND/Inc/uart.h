#ifndef UART_H_
#define UART_H_

#include "stm32f401.h"

// UART2 Register offsets
#define UART2_CR1        (*(volatile uint32_t *)(UART2_BASE + 0x00))
#define UART2_CR2        (*(volatile uint32_t *)(UART2_BASE + 0x04))
#define UART2_CR3        (*(volatile uint32_t *)(UART2_BASE + 0x08))
#define UART2_BRR        (*(volatile uint32_t *)(UART2_BASE + 0x0C))
#define UART2_ISR        (*(volatile uint32_t *)(UART2_BASE + 0x1C))
#define UART2_RDR        (*(volatile uint32_t *)(UART2_BASE + 0x24))
#define UART2_TDR        (*(volatile uint32_t *)(UART2_BASE + 0x28))

// Define UART2 Configuration Parameters
#define UART2_BAUDRATE   9600
#define SYS_CLOCK        16000000 // Assuming system clock is 16 MHz
#define UART2_BRR_VALUE  (SYS_CLOCK / (16 * UART2_BAUDRATE))

void uart2_init(void);
void uart2_send_char(char c);
char uart2_receive_char(void);
void uart2_send_string(const char *str);


#endif /* UART_H_ */
