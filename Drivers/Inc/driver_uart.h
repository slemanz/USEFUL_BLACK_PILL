#ifndef INC_DRIVER_UART_H_
#define INC_DRIVER_UART_H_

#include "stm32f401xx.h"

/*
 * Configuration structure for USARTx peripheral
 */

typedef struct
{
	uint8_t USART_Mode;
	uint32_t USART_Baud;
}UART_Config_t;

/*
 * Handle structure for USARTx peripheral
 */

typedef struct{
	UART_RegDef_t *pUSARTx;
	UART_Config_t USART_Config;
}UART_Handle_t;

/*
 *@USART_Mode
 *Possible options for USART_Mode
 */
#define USART_MODE_ONLY_TX		0
#define USART_MODE_ONLY_RX		1
#define USART_MODE_TXRX			2


/*
 *@USART_Baud
 *Possible options for USART_Baud
 */
#define USART_STD_BAUD_1200			1200
#define USART_STD_BAUD_2400			2400
#define USART_STD_BAUD_9600			9600
#define USART_STD_BAUD_19200		19200
#define USART_STD_BAUD_38400		38400
#define USART_STD_BAUD_57600		57600
#define USART_STD_BAUD_115200		115200

/*
 * USART DEFINITIONS
 */


#define USART_CR1_TE			(3)
#define USART_CR1_RE			(2)
#define USART_CR1_UE			(13)

#define USART_SR_TXE            (7)
#define USART_SR_RXNE           (5)

/*
 * USART flags
 */

#define USART_FLAG_TXE 			( 1 << USART_SR_TXE)
#define USART_FLAG_RXNE 		( 1 << USART_SR_RXNE)
#define USART_FLAG_TC 			( 1 << USART_SR_TC)


/********************************************************************************************
 * 								APIs supported by this driver
 * 					for more information check the function definitions
 ********************************************************************************************/

/*
 * Peripheral Clock setup
 */
void UART_PeriClockControl(UART_RegDef_t *pUARTx, uint8_t EnorDi);


/*
 * Init and De-init
 */
void UART_Init(UART_Handle_t *pUARTHandle);
void UART_DeInit(UART_RegDef_t *pUARTx);


/*
 * Data Send and Receive
 */
void UART_SendData(UART_Handle_t *pUARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void UART_ReceiveData(UART_Handle_t *pUARTHandle, uint8_t *pRxBuffer, uint32_t Len);

/*
 * Interrupt Configuration
 */

void UART_InterruptConfig(uint8_t interrupt, uint8_t EnorDi);


/*
 * Other Peripheral Control APIs
 */
void UART_PeripheralControl(UART_RegDef_t *pUARTx, uint8_t EnorDi);
uint8_t UART_GetFlagStatus(UART_RegDef_t *pUARTx , uint8_t FlagName);
void UART_ClearFlag(UART_RegDef_t *pUARTx, uint16_t StatusFlagName);
void UART_SetBaudRate(UART_RegDef_t *pUARTx, uint32_t BaudRate);

#endif /* INC_DRIVER_UART_H_ */