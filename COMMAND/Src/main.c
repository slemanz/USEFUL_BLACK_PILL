#include "stm32f401.h"


#define SLAVE_ADDR 0x68
uint8_t active_command = 0xff;

void Clock_Config(void);
void GPIO_Config(void);

void delay(void)
{
	for(uint32_t i = 0; i < 1000000; i++);
}


int main(void) {
    Clock_Config();
    GPIO_Config();




    while (1)
    {
        // Main loop does nothing as we rely on interrupts

    }
}



/*
 * FUNCTIONS
 */



void Clock_Config(void) {
    // Enable HSI (internal high speed clock)
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY)); // Wait for HSI to be ready

    // Select HSI as system clock source
    RCC->CFGR &= ~RCC_CFGR_SW; // clear
    RCC->CFGR |= RCC_CFGR_SW_HSI; // set
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); // Wait till HSI is used as system clock source

    // Enable clocks for GPIOB and I2C1
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
}


void GPIO_Config(void) {
	// Enable GPIOA clock (where UART2 is located)
	RCC_AHB1ENR |= (1 << 0); // Enable GPIOA clock

	 // Configure PA2 as Alternate Function mode for UART2 TX
	// Configure PA3 as Alternate Function mode for UART2 RX
	GPIOA_MODER &= ~(0xF << 4); // Clear mode for PA2 and PA3
	GPIOA_MODER |= (0xA << 4);  // Set PA2 and PA3 to Alternate function mode

	// Set Alternate Function 7 (USART2) for PA2 and PA3
	GPIOA_AFRL &= ~(0xFF << 8); // Clear alternate function for PA2 and PA3
	GPIOA_AFRL |= (0x77 << 8);  // Set PA2 and PA3 to AF7 (USART2)


}


/*
void NVIC_EnableIRQ(uint8_t IRQNumber)
{
	if(IRQNumber <= 31)
	{
		// program ISER0 register
		*NVIC_ISER0 |= (1 << IRQNumber);

	}else if(IRQNumber > 31 && IRQNumber < 64) // 32 to 63
	{
		// program ISER1 register
		*NVIC_ISER1 |= (1 << (IRQNumber % 32));

	}else if(IRQNumber >= 64 && IRQNumber < 96) // 64 to 95
	{
		// program ISER2 register
		*NVIC_ISER2 |= (1 << (IRQNumber % 64));

	}
}

void NVIC_Config(void) {
	// priority will be default
    NVIC_EnableIRQ(IRQ_NO_I2C1_EV); // Enable I2C1 event interrupt
    NVIC_EnableIRQ(IRQ_NO_I2C1_ER); // Enable I2C1 error interrupt
}*/


