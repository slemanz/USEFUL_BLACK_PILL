#ifndef INC_DRIVER_UART_H_
#define INC_DRIVER_UART_H_

#include "stm32f401xx.h"

/*
 * Configuration structure for USARTx peripheral
 */

typedef struct
{
	uint8_t UART_Mode;
	uint32_t UART_Baud;
}UART_Config_t;

/*
 * Handle structure for USARTx peripheral
 */

typedef struct{
	UART_RegDef_t *pUSARTx;
	UART_Config_t USART_Config;
}UART_Handle_t;

/*
 *@UART_Mode
 *Possible options for USART_Mode
 */
#define UART_MODE_ONLY_TX		0
#define UART_MODE_ONLY_RX		1
#define UART_MODE_TXRX			2


/*
 *@UART_Baud
 *Possible options for USART_Baud
 */
#define UART_STD_BAUD_1200              1200
#define UART_STD_BAUD_2400              2400
#define UART_STD_BAUD_9600              9600
#define UART_STD_BAUD_19200             19200
#define UART_STD_BAUD_38400             38400
#define UART_STD_BAUD_57600             57600
#define UART_STD_BAUD_115200            115200

/*
 * UART DEFINITIONS
 */


#define UART_CR1_SBK                    (0)
#define UART_CR1_RWU                    (1)
#define UART_CR1_RE                     (2)
#define UART_CR1_TE                     (3)
#define UART_CR1_IDLEIE                 (4)
#define UART_CR1_RXNEIE                 (5)
#define UART_CR1_TCIE                   (6)
#define UART_CR1_TXEIE                  (7)
#define UART_CR1_PEIE                   (8)
#define UART_CR1_PS                     (9)
#define UART_CR1_PCE                    (10)
#define UART_CR1_WAKE                   (11)
#define UART_CR1_M                      (12)
#define UART_CR1_UE                     (13)
#define UART_CR1_OVER8                  (15)

#define UART_SR_ORE                     (3)
#define UART_SR_RXNE                    (5)
#define UART_SR_TC                      (6)
#define UART_SR_TXE                     (7)
#define UART_SR_CTS                     (9)

/*
 * UART MASK
 */

#define UART_CR1_TE_MASK                (1 << UART_CR1_TE)
#define UART_CR1_RE_MASK                (1 << UART_CR1_RE)
#define UART_CR1_UE_MASK                (1 << UART_CR1_UE)

#define UART_SR_CTS_MASK                (1 << UART_SR_CTS)
#define UART_SR_TXE_MASK                (1 << UART_SR_TXE)
#define UART_SR_TC_MASK                 (1 << UART_SR_TC)
#define UART_SR_RXNE_MASK               (1 << UART_SR_RXNE)
#define UART_SR_ORE_MASK                (1 << UART_SR_ORE)

/*
 * UART flags
 */

#define UART_FLAG_CTS	                (UART_SR_CTS_MASK)
#define UART_FLAG_TXE                   (UART_SR_TXE_MASK)
#define UART_FLAG_TC                 	(UART_SR_TC_MASK)
#define UART_FLAG_RXNE                  (UART_SR_RXNE_MASK)
#define UART_FLAG_ORE                 	(UART_SR_ORE_MASK)

/*
 * UART Interrupts
 */

#define UART_INTERRUPT_RXNE         (1 << UART_CR1_RXNEIE)

/*
 * UART IRQ numbers
 */

#define IRQ_NO_UART1                37
#define IRQ_NO_UART2                38
#define IRQ_NO_UART6                71


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
 * Data write and Read
 */
void uart_write_byte(UART_RegDef_t *pUARTx, uint8_t data);
uint8_t uart_read_byte(UART_RegDef_t *pUARTx);

 void uart_write(UART_RegDef_t *pUARTx, uint8_t* pTxBuffer, const uint32_t Len);
 void uart_read(UART_RegDef_t *pUARTx, uint8_t* pRxBuffer, const uint32_t Len);

/*
 * Interrupt Configuration
 */

void UART_InterruptConfig(UART_RegDef_t *pUARTx, uint32_t interrupt, uint8_t EnorDi);


/*
 * Other Peripheral Control APIs
 */
void UART_PeripheralControl(UART_RegDef_t *pUARTx, uint8_t EnorDi);
uint8_t UART_GetFlagStatus(UART_RegDef_t *pUARTx , uint8_t FlagName);
void UART_ClearFlag(UART_RegDef_t *pUARTx, uint16_t StatusFlagName);
void UART_SetBaudRate(UART_RegDef_t *pUARTx, uint32_t BaudRate);

#endif /* INC_DRIVER_UART_H_ */