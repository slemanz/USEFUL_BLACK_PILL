#include "driver_uart.h"

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

void UART_PeriClockControl(UART_RegDef_t *pUARTx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pUARTx == UART2) UART2_PCLK_EN();

        return;
    }

    if(pUARTx == UART2) UART2_PCLK_DI();
}

void UART_PeripheralControl(UART_RegDef_t *pUARTx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pUARTx->CR1 |= UART_CR1_UE_MASK;
        return;
    }
    pUARTx->CR1 &= ~UART_CR1_UE_MASK;
}

void UART_Init(UART_Handle_t *pUARTHandle)
{
    UART_PeriClockControl(pUARTHandle->pUSARTx, ENABLE);

    uint32_t temp = 0;
    if(pUARTHandle->USART_Config.UART_Mode == UART_MODE_ONLY_TX)
    {
        temp = (UART_CR1_TE_MASK);
    }else if(pUARTHandle->USART_Config.UART_Mode == UART_MODE_ONLY_RX)
    {
        temp = (UART_CR1_RE_MASK);
    }else if(pUARTHandle->USART_Config.UART_Mode == UART_MODE_TXRX)
    {
        temp = (UART_CR1_TE_MASK) | (UART_CR1_RE_MASK);
    }
    pUARTHandle->pUSARTx->CR1 = temp; 
    pUARTHandle->pUSARTx->BRR = compute_uart_div(16000000, pUARTHandle->USART_Config.UART_Baud); // baurate

    UART_PeripheralControl(pUARTHandle->pUSARTx, ENABLE);
}

uint8_t UART_GetFlagStatus(UART_RegDef_t *pUARTx, uint8_t FlagName)
{
    if(pUARTx->SR & FlagName)
    {
    	return FLAG_SET;
    }
    return FLAG_RESET;
}

void uart_write_byte(UART_RegDef_t *pUARTx, uint8_t data)
{
    pUARTx->DR = data;
}

uint8_t uart_read_byte(UART_RegDef_t *pUARTx)
{
    return (uint8_t)(pUARTx->DR);
}

void uart_write(UART_RegDef_t *pUARTx, uint8_t* pTxBuffer, const uint32_t Len)
{
    for(uint32_t i = 0; i < Len; i++)
	{
        while(!UART_GetFlagStatus(pUARTx, UART_FLAG_TXE))
        {
            __asm("NOP");
        }
		uart_write_byte(pUARTx, pTxBuffer[i]);
	}
}

void UART_InterruptConfig(UART_RegDef_t *pUARTx, uint32_t interrupt, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pUARTx->CR1 |= (interrupt);
        return;
    }
    pUARTx->CR1 &= ~(interrupt);
}