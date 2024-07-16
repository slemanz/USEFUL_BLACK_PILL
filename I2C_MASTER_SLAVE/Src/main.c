#include "stm32f401.h"


#define SLAVE_ADDR 0x68

char name_msg[32] = "Welcome Man\n";
uint8_t active_command = 0xff;

void Clock_Config(void);
void GPIO_Config(void);
void I2C_Config(void);
void NVIC_EnableIRQ(uint8_t IRQNumber);
void NVIC_Config(void);

uint8_t get_len_of_data(void) {
    return (uint8_t)strlen(name_msg);
}

void delay(void)
{
	for(uint32_t i = 0; i < 1000000; i++);
}


int main(void) {
    Clock_Config();
    GPIO_Config();
    I2C_Config();
    NVIC_Config();

    // blink led to say that config is OKAY
    LED = 1;
	delay();
	LED = 0;
	delay();
	 LED = 1;



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
    // Configure PB6 and PB7 as alternate function I2C1
    GPIOB->MODER &= ~(0xF << (6 * 2)); // Clear mode for PB6 and PB7
    GPIOB->MODER |= (0xA << (6 * 2));  // Set PB6 and PB7 to alternate function

    GPIOB->OTYPER |= (0x3 << 6);       // Set output type to open-drain for PB6 and PB7
    GPIOB->OSPEEDR |= (0xF << (6 * 2));// Set speed to very high for PB6 and PB7
    GPIOB->PUPDR &= ~(0xF << (6 * 2)); // No pull-up/pull-down for PB6 and PB7

    GPIOB->AFR[0] |= (0x44 << (6 * 4)); // Set alternate function to I2C1 for PB6 and PB7

    // Confifure PA6 as led output
    GPIOA->MODER &= ~(1 << 16);
    GPIOA->MODER |=  (1 << 16);
}


void I2C_Config(void) {
    I2C1->CR1 &= ~I2C_CR1_PE; // Disable I2C1
    I2C1->CR2 = 16;           // APB1 clock frequency in MHz (set to 16 MHz)
    I2C1->OAR1 = I2C_OAR1_OA1EN | (SLAVE_ADDR << 1); // Set slave address and enable it
    //I2C1->OAR1 = (SLAVE_ADDR << 1); // Set slave address
    I2C1->CCR = 80;           // Configure clock control (standard mode, 100 kHz), consindering 16MHz system clock
    I2C1->TRISE = 17;         // Configure maximum rise time

    // Enable ACK, I2C peripheral, and interrupts
    I2C1->CR1 |= I2C_CR1_ACK | I2C_CR1_PE;
    I2C1->CR2 |= I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN | I2C_CR2_ITERREN;
}

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
}


void I2C1_EV_IRQHandler(void) {
    if ((I2C1->SR1 & I2C_SR1_ADDR) == I2C_SR1_ADDR) {
        uint32_t temp = I2C1->SR1;
        temp = I2C1->SR2; // Clear ADDR flag
        (void)temp;      // Prevent unused variable warning
    }

    if ((I2C1->SR1 & I2C_SR1_RXNE) == I2C_SR1_RXNE) {
        active_command = I2C1->DR;
    }

    if ((I2C1->SR1 & I2C_SR1_TXE) == I2C_SR1_TXE) {
        if (active_command == 0x51)
        {
            uint8_t len = get_len_of_data();
            I2C1->DR = len;
            active_command = 0xff;
        } else if (active_command == 0x52)
        {
            static uint8_t index = 0;
            I2C1->DR = name_msg[index++];
            if (index >= strlen(name_msg))
            {
                index = 0;
                active_command = 0xff;
            }
        }
    }
}


void I2C1_ER_IRQHandler(void) {

    if ((I2C1->SR1 & I2C_SR1_AF) == I2C_SR1_AF) {
        I2C1->SR1 &= ~I2C_SR1_AF; // Clear acknowledge failure flag
    }


    if ((I2C1->SR1 & I2C_SR1_OVR) == I2C_SR1_OVR) {
        I2C1->SR1 &= ~I2C_SR1_OVR; // Clear overrun/underrun flag
    }

    if ((I2C1->SR1 & I2C_SR1_BERR) == I2C_SR1_BERR) {
        I2C1->SR1 &= ~I2C_SR1_BERR; // Clear bus error flag
    }
}

