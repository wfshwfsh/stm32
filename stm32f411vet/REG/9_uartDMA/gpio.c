#include "stm32f4xx.h"

void gpio_config(void)
{
	RCC->AHB1ENR |= (1<<0);
	
	GPIOA->MODER |= (1<<10);
	
	GPIOA->OTYPER = 0;
	GPIOA->OSPEEDR = 0;
}

