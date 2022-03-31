#include "stm32f4xx.h"
#include "gpio.h"

void gpio_config(void)
{
	RCC->AHB1ENR |= (1<<0);
	
	GPIOA->MODER |= (1<<10);
	
	GPIOA->OTYPER = 0;
	GPIOA->OSPEEDR = 0;
	
	
	//adding PA1 for exti source
	GPIOA->MODER &= ~(3<<2);  // Bits (3:2) = 0:0  --> PA1 in Input Mode
	GPIOA->PUPDR |=  (2<<2);  // Bits (3:2) = 1:0  --> PA1 is in Pull Down mode
	
	//adding PA7 for exti source
	//GPIOA->MODER &= ~(3<<14);  // Bits (3:2) = 0:0  --> PA7 in Input Mode
	//GPIOA->PUPDR |=  (2<<14);  // Bits (3:2) = 1:0  --> PA7 is in Pull Down mode
	
	
}

