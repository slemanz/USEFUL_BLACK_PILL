#include "init.h"

void init_io(void)
{
    GPIO_Handle_t led;
    led.pGPIOx = LED_EXT_PORT;
    led.GPIO_PinConfig.GPIO_PinNumber = LED_EXT_PIN;
    led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
    GPIO_Init(&led);
}

void init_systick(void)
{
    systick_set_frequency(SYSTICK_FREQ, CPU_FREQ);
    systick_counter_enable();
    systick_interrupt_enable();
}

void init_serial(void)
{
    GPIO_Handle_t UartPin;
    UartPin.pGPIOx = UART_PORT;
    UartPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    UartPin.GPIO_PinConfig.GPIO_PinNumber = UART_TX_PIN;
    UartPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    UartPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    UartPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    UartPin.GPIO_PinConfig.GPIO_PinAltFunMode = PA2_ALTFN_UART2_TX;
    GPIO_Init(&UartPin);

    UartPin.GPIO_PinConfig.GPIO_PinNumber = UART_RX_PIN;
    UartPin.GPIO_PinConfig.GPIO_PinAltFunMode = PA3_ALTFN_UART2_RX;
    GPIO_Init(&UartPin);

    UART_Handle_t UartHandle;
    UartHandle.pUSARTx = UART2;
    UartHandle.USART_Config.UART_Baud = UART_STD_BAUD_115200;
    UartHandle.USART_Config.UART_Mode = UART_MODE_TXRX;
    UART_Init(&UartHandle);
}

// printf retarget
extern int __io_putchar(int ch)
{
    uart_write(UART2, (uint8_t*)&ch, 1);
    return ch;
}