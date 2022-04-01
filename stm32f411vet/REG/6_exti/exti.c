#include "stm32f4xx.h"
#include "main.h"
#include "exti.h"


void exti_config(void)
{
	//1. Enable SYSCNFG/AFIO in APB2ENR (systeme configuration controller clock)
	RCC->APB2ENR |= (1<<14);
	
	//11111111 USE_EXTI_PA1 11111111111111111
	//2. Config EXTI source
	SYSCFG->EXTICR[0] &= ~(0xf<<4);//PA1
		
	//3. Disable EXTI Mask
	EXTI->IMR |= (1<<1);
		
	//4. Setting EXTI Trigger type
	EXTI->RTSR &= ~(1<<1);
	EXTI->FTSR |= (1<<1);
	
	//5. setting EXTI priority and enable EXTI
	NVIC_SetPriority(EXTI1_IRQn, 1);
	NVIC_EnableIRQ(EXTI1_IRQn);

	
	//77777777 USE_EXTI_PA1 77777777777777777
	//2. Config EXTI source
	SYSCFG->EXTICR[1] &= ~(0xf<<12);//PA7
	
	//3. Disable EXTI Mask
	EXTI->IMR |= (1<<7);
	
	//4. Setting EXTI Trigger type
	EXTI->RTSR &= ~(1<<7);
	EXTI->FTSR |= (1<<7);
	
	//5. setting EXTI priority and enable EXTI
	NVIC_SetPriority(EXTI9_5_IRQn, 1);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	
}

