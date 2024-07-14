#ifndef STM32F401_H_
#define STM32F401_H_

// This header defines all useful things to code be able to work
#include <stdint.h>
#include <string.h>
#include <stddef.h>

#define __vo volatile
#define __weak __attribute__((weak))

// MEMORY ADDRESSES

#define RCC_BASE_ADDR 	(0x40023800)



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

#define RCC 	((RCC_RegDef_t*)RCC_BASE_ADDR)



// MACROS

#define RCC_CR_HSION 	(1 << 0)
#define RCC_CR_HSIRDY	(1 << 1)

#define RCC_CFGR_SW		(0x3)










#endif /* STM32F401_H_ */
