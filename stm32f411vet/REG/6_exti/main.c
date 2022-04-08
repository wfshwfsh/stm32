#include <stdio.h>
#include "stm32f4xx.h"
#include "main.h"

uint8_t count = 0;
int flag = 0;



//setting EXTI handler
// * check EXTI source
// * clear interrupt
void EXTI1_IRQHandler(void)
{
	/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
	
	1. Check the Pin, which trgerred the Interrupt
	2. Clear the Interrupt Pending Bit
	
	********************************************************/
	if (EXTI->PR & (1<<1))    // If the PA1 triggered the interrupt
	{
		flag = 1;
		EXTI->PR |= (1<<1);  // Clear the interrupt flag by writing a 7 
	}
}

void EXTI9_5_IRQHandler(void)
{
	/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
	
	1. Check the Pin, which trgerred the Interrupt
	2. Clear the Interrupt Pending Bit
	
	********************************************************/
	if (EXTI->PR & (1<<7))    // If the PA7 triggered the interrupt
	{
		flag = 1;
		EXTI->PR |= (1<<7);  // Clear the interrupt flag by writing a 7 
	}
}


int main(void)
{
	SysClockConfig();
	gpio_config();
	//uart2_config();
	tim2_config();
	exti_config();
	
	//GPIOA->BSRR |= (1<<5);
	while(1)
	{
		//uint32_t val = GPIOA->IDR;
		//if((val & (1<<7))){
		//	GPIOA->BSRR |= (1<<5);
		//}else{
		//	GPIOA->BSRR |= ((1<<5) <<16);
		//}
		
		//delay_us(5000);
		//GPIOA->BSRR |= (1<<5);
		//delay_ms(3000);
		//
		//GPIOA->BSRR |= ((1<<5) <<16);
		//delay_ms(3000);
		
		//UART2_SendString("Hello World\n");
		//delay(1000);
		
		if (flag)
		{
			GPIOA->BSRR |= (1<<5);
			delay_ms (1000);
			count++;
			flag = 0;
		}else{
			GPIOA->BSRR |= ((1<<5) <<16);
		}
	}
}


