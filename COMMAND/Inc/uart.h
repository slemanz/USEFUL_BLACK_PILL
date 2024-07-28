#ifndef UART_H_
#define UART_H_

#include "stm32f401.h"

// Define UART2 Configuration Parameters
#define UART2_BAUDRATE   9600
#define SYS_CLOCK        16000000 // Assuming system clock is 16 MHz
#define UART2_BRR_VALUE  (SYS_CLOCK / (16 * UART2_BAUDRATE))

void uart2_init(void);
void uart2_send_char(char c);
char uart2_receive_char(void);
void uart2_send_string(const char *str);


#endif /* UART_H_ */
