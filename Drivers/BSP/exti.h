#ifndef __EXTI_H_
#define __EXTI_H_

#include "stm32f1xx.h"
#include "stdint.h"

#define TRUE 1
#define FALSE 0

void exti_init(void);
void exti_PA4_init(void);

void exti_PB4_init(void);
uint8_t ia_flag_get(void);
void ia_flag_set(uint8_t value);
#endif
