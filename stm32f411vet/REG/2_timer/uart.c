#include "stm32f4xx.h"
void uart2_config(void);
void UART2_SendChar (uint8_t c);
void UART2_SendString (char *string);
uint8_t UART2_GetChar (void);

void uart2_config(void)
{
	RCC->APB1ENR |= (1<<17);  // Enable UART2 CLOCK
	RCC->AHB1ENR |= (1<<0); // Enable GPIOA CLOCK
	
	//set gpio to alternate function
	GPIOA->MODER |= (2<<4) |(2<<6);
	
	GPIOA->OSPEEDR |= (3<<4) | (3<<6);  
	
	//set gpio PA2 PA3 to uart2
	GPIOA->AFR[0] |= (7<<8);
	GPIOA->AFR[0] |= (7<<12);
	
	//clear
	USART2->CR1 = 0x00;
	
	USART2->CR1 |= (1<<13);
	
	USART2->CR1 &= ~(1<<12);  // M =0; 8 bit word length
	
	USART2->BRR = (9<<0) | (19<<4);
	
	USART2->CR1 |= (1<<2);
	USART2->CR1 |= (1<<3);
}


void UART2_SendChar (uint8_t c)
{
		/*********** STEPS FOLLOWED *************
	
	1. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
		 for each data to be transmitted in case of single buffer.
	2. After writing the last data into the USART_DR register, wait until TC=1. This indicates
		 that the transmission of the last frame is complete. This is required for instance when
		 the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.
	
	****************************************/
	
	USART2->DR = c; // load the data into DR register
	while (!(USART2->SR & (1<<6)));  // Wait for TC to SET.. This indicates that the data has been transmitted
}
	
void UART2_SendString (char *string)
{
	while (*string) UART2_SendChar (*string++);
}

uint8_t UART2_GetChar (void)
{
			/*********** STEPS FOLLOWED *************
	
	1. Wait for the RXNE bit to set. It indicates that the data has been received and can be read.
	2. Read the data from USART_DR  Register. This also clears the RXNE bit
	
	****************************************/

	uint8_t temp;
	
	while (!(USART2->SR & (1<<5)));  // wait for RXNE bit to set
	temp = USART2->DR;  // Read the data. This clears the RXNE also
	return temp;
}
	