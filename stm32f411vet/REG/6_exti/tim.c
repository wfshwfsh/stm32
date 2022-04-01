#include "stm32f4xx.h"
#include "tim.h"


void tim2_config(void)
{
	// 1. enable timer2 from APB1
	RCC->APB1ENR |= (1<<0);
	
	// 2. set PSC, ARR register
	//Note: The Timer2 under "APB1 timer clock" freq is 72MHz (not 36 MHz)
	TIM2->PSC = 72-1;//7200-1;
	TIM2->ARR = 0xffff-1;
	
	// 3. enable clock timer and wait ready
	TIM2->CR1 |= (1<<0);
	while(!(TIM2->SR & (1<<0)));
}

void delay_us(int us)
{
	//clear counter
	TIM2->CNT = 0;
	
	while(TIM2->CNT < us);
}


void delay_ms(int ms)
{
	for(uint16_t i=0;i<ms;i++)
	{
		delay_us(1000);
	}
}