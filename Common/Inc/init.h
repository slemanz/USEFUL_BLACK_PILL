#ifndef INC_INIT_H_
#define INC_INIT_H_

#include "common-defines.h"
#include "stm32f401xx.h"

#define  LED_EXT_PORT       GPIOA
#define  LED_EXT_PIN        GPIO_PIN_NO_5

void init_io(void);


#endif /* INC_INIT_H_ */