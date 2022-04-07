#include "stm32f4xx.h"

void SysClockConfig (void)
{
	//1. enable HSE, and wait for Ready
	RCC->CR |= (1<<16);
	while( !(RCC->CR & (1<<17)) );
	
	//2. set power enable clock and voltage regulator
	RCC->APB1ENR |= 1<<28;
	RCC->CR |= 3<<14;
	
	//3. config Flash Pretech, Latency, ... settings
	FLASH->ACR = (1<<8) | (1<<9) | (1<<10) | (5<<0);
	
	//4. config Prescalers HCLK, PCLK1, PCLK2
	//AHB PR
	RCC->CFGR &= ~(1<<4);
	
	//APB1 PR
	RCC->CFGR |= (4<<10);
	
	//APB2 PR
	RCC->CFGR &= ~(1<<13);
	
	//5. config main PLL
	#define PLL_M 4
	#define PLL_N 72
	#define PLL_P 0
	//bit 22: clock source 1-HSE, 0-HSI
	RCC->PLLCFGR = (1<<22) | (PLL_P<<16) | (PLL_N<<6) | (PLL_M<<0);
	
	//6. enable the PLL and wait for ready
	RCC->CR |= (1<<24);
	while( !(RCC->CR & (1<<25)) );
	
	//7. Select the clock source and wait for it to be set
	RCC->CFGR |= (2<<0);
	while( !(RCC->CFGR & (2<<2)) );
	
}
