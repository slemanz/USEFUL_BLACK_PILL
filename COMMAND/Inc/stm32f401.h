#ifndef STM32F401_H_
#define STM32F401_H_

// This header defines all useful things to code be able to work
#include <stdint.h>
#include <string.h>
#include <stddef.h>

#define __vo volatile
#define __weak __attribute__((weak))

// MEMORY ADDRESSES

#define RCC_BASE          0x40023800

#define USART2_BASE       0x40004400
#define GPIOA_BASE        0x40020000


// RCC Register offsets
#define RCC_APB1ENR      (*(volatile uint32_t *)(RCC_BASE + 0x40))
#define RCC_AHB1ENR      (*(volatile uint32_t *)(RCC_BASE + 0x30))

// GPIOA Register offsets
#define GPIOA_MODER      (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRL       (*(volatile uint32_t *)(GPIOA_BASE + 0x20))

#define GPIOA_BASE_ADDR 	(0x40020000)
#define GPIOB_BASE_ADDR 	(0x40020400)

#define I2C1_BASE_ADDR		(0x40005400)



// MEMORY STRUCTS

typedef struct
{
	__vo uint32_t CR; 			// 0x00
	__vo uint32_t PLLCFGR;		// 0x04
	__vo uint32_t CFGR;			//0x08
	__vo uint32_t CIR;			// 0x0C
	__vo uint32_t AHB1RSTR;		// 0x10
	__vo uint32_t AHB2RSTR;		// 0x14
	__vo uint32_t reserved[2];
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t reserved1[2];
	__vo uint32_t AHB1ENR;		//
	__vo uint32_t AHB2ENR;
	__vo uint32_t reserved2[2];
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t reserved3[2];
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t reserved4[2];
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	__vo uint32_t reserved5[2];
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	__vo uint32_t reserved6[2];
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
	__vo uint32_t DCKCFGR;
}RCC_RegDef_t;

#define RCC 	((RCC_RegDef_t*)RCC_BASE)




typedef struct
{
	__vo uint32_t MODER; /* configure the mode of pin 			address offset: 0x00 */
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
}GPIO_RegDef_t;

#define GPIOA 	((GPIO_RegDef_t*)GPIOA_BASE_ADDR)
#define GPIOB 	((GPIO_RegDef_t*)GPIOB_BASE_ADDR)



typedef struct
{
	__vo uint32_t SR; /* configure the mode of pin 			address offset: 0x00 */
	__vo uint32_t DR;
	__vo uint32_t BRR;
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t CR3;
	__vo uint32_t GTPR;
}USART_RegDef_t;


#define UART2 	((USART_RegDef_t*)USART2_BASE)


// MACROS

#define RCC_CR_HSION 		(1 << 0)
#define RCC_CR_HSIRDY		(1 << 1)

#define RCC_CFGR_SW			(0x3)
#define RCC_CFGR_SW_HSI		(0x0)
#define RCC_CFGR_SWS		(0x3 << 2)
#define RCC_CFGR_SWS_HSI	(0x0)

#define RCC_AHB1ENR_GPIOAEN 	(1 << 0)
#define RCC_AHB1ENR_GPIOBEN 	(1 << 1)
#define RCC_APB1ENR_I2C1EN 		(1 << 21)
#define RCC_APB1ENR_USART2EN 	(1 << 17)

/*
 * USART DEFINITIONS
 */


#define USART_CR1_TE			(1 << 3)
#define USART_CR1_RE			(1 << 2)
#define USART_CR1_UE			(1 << 13)

#define USART_SR_TXE			(1 << 7)
#define USART_SR_RXNE			(1 << 5)





#define NVIC_ISER0 						((__vo uint32_t*)0xE000E100UL)
#define NVIC_ISER1 						((__vo uint32_t*)0xE000E104UL)
#define NVIC_ISER2 						((__vo uint32_t*)0xE000E108UL)
#define NVIC_ISER3 						((__vo uint32_t*)0xE000E10CUL)

#define IRQ_NO_I2C1_EV		31
#define IRQ_NO_I2C1_ER 		32



// PIN ABSTRACTION

typedef struct{
	__vo uint32_t pin0  		: 1;
	__vo uint32_t pin1  		: 1;
	__vo uint32_t pin2  		: 1;
	__vo uint32_t pin3  		: 1;
	__vo uint32_t pin4  		: 1;
	__vo uint32_t pin5  		: 1;
	__vo uint32_t pin6  		: 1;
	__vo uint32_t pin7  		: 1;
	__vo uint32_t pin8  		: 1;
	__vo uint32_t pin9 	 		: 1;
	__vo uint32_t pin10  		: 1;
	__vo uint32_t pin11  		: 1;
	__vo uint32_t pin12  		: 1;
	__vo uint32_t pin13  		: 1;
	__vo uint32_t pin14  		: 1;
	__vo uint32_t pin15  		: 1;
	__vo uint32_t reserved  	: 16;
}PORTx_pin_t;

#define PORTA_OUT ((PORTx_pin_t*)&GPIOA->ODR)
#define LED (PORTA_OUT->pin8)



/*
 *  INCLUDES
 */

#include "uart.h"
#include "command.h"


#endif /* STM32F401_H_ */
