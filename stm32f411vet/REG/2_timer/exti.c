#include "stm32f4xx.h"
#include "exti.h"


void exti_config(void)
{
	//1. Enable SYSCNFG/AFIO in APB2ENR (systeme configuration controller clock)
	RCC->APB2ENR |= (1<<14);
	
	//2. Config EXTI source
	//SYSCFG->EXTICR[1] &= ~(0xf<<12);//PA7
	SYSCFG->EXTICR[0] &= ~(0xf<<4);//PA1
	
	//3. Disable EXTI Mask
	//EXTI->IMR |= (1<<7);
	EXTI->IMR |= (1<<1);
	
	//4. Setting EXTI Trigger type
	EXTI->RTSR &= ~(1<<1);
	EXTI->FTSR |= (1<<1);
	
	//5. setting EXTI priority and enable EXTI
	NVIC_SetPriority(EXTI1_IRQn, 1);
	NVIC_EnableIRQ(EXTI1_IRQn);
}

