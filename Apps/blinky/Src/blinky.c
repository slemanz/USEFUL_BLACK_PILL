#include <stdint.h>

// Base address definitions
#define RCC_BASE                        (0x40023800UL)
#define GPIOA_BASE                      (0x40020000UL)

// RCC registers
#define RCC_AHB1ENR                     (*(volatile uint32_t *)(RCC_BASE + 0x30))

// GPIOA registers
#define GPIOA_MODER                     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR                       (*(volatile uint32_t *)(GPIOA_BASE + 0x14))

// Bit definitions
#define RCC_AHB1ENR_GPIOAEN             (1U << 0)
#define PIN_NUMBER                      (5)

// Function prototype
void delay(volatile uint32_t count);

int main(void) {
    // Enable GPIOA clock
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Set GPIOA pin 8 as output
    GPIOA_MODER &= ~(3U << (PIN_NUMBER*2)); 
    GPIOA_MODER |= (1U << (PIN_NUMBER*2)); 


    while (1)
    {
        // Toggle GPIOA5
        GPIOA_ODR ^= (1 << PIN_NUMBER);
        delay(1000000);
    }
}

void delay(volatile uint32_t count) {
    while (count-- > 0) {
        __asm("NOP"); // No operation for delay
    }
}

