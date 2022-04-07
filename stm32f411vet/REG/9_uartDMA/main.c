#include <string.h>
#include <stdio.h>
#include "stm32f4xx.h"

FILE __stdout;

int fputc(int ch, FILE *f){
	UART2_SendString((uint8_t *)&ch);
  return ch;
}

int ferror(FILE *f){
  /* Your implementation of ferror(). */
  return 0;
}



void delay(int time)
{
	int j;
	for(j = 0; j < time*4000; j++)
	{}  /* excute NOP for 1ms */

}

#define RXSIZE 20
uint8_t RxBuf[20];
uint8_t MainBuf [50];

uint8_t indx = 0;
uint8_t enter_isr = 0;

void DMA1_Stream5_IRQHandler (void)
{
	enter_isr++;
	
	//printf("HISR 0X%0x \n", DMA1->HISR);
	
	if ((DMA1->HISR)&(1<<10))  // If the Half Transfer Complete Interrupt is set
	{
		memcpy (&MainBuf[indx], &RxBuf[0], RXSIZE/2);
		DMA1->HIFCR |= (1<<10);
		indx = indx+(RXSIZE/2);
		if (indx>49) indx=0;
	}
	
	if ((DMA1->HISR)&(1<<11))  // If the Transfer Complete Interrupt is set
	{
		memcpy (&MainBuf[indx], &RxBuf[RXSIZE/2], RXSIZE/2);
		DMA1->HIFCR |= (1<<11);
		indx = indx+(RXSIZE/2);
		if (indx>49) indx=0;
	}
	
}



void DMA_Init (void)
{
	
	// 1. Enable DMA1 Clock
	RCC->AHB1ENR |= 1<<21;
	
	// 2. Enable DMA Interrupts
	DMA1_Stream5->CR |= (1<<4)|(1<<3)|(1<<2);  // TCIE, HTIE, TEIE Enabled
	
	// 3. Set the Data Direction
//	DMA1_Channel7->SxCR |= (1<<4);   // Read From Memory
	DMA1_Stream5->CR &= ~(3<<6);   // Peripheral to Mem
	
	// 4. Enable the circular mode (CIRC)
	DMA1_Stream5->CR |= 1<<8;
	
	// 5. Enable the Memory Increment (MINC)
	DMA1_Stream5->CR |= 1<<10;
	
	// 6. Set the Peripheral data size (PSIZE)
	DMA1_Stream5->CR &= ~(3<<11);  // 00 : 8 Bit Data
	
	// 7. Set the Memory data size (MSIZE)
	DMA1_Stream5->CR &= ~(3<<13);  // 00 : 8 Bit Data
	
	// 8. Set the Priority Level
	DMA1_Stream5->CR &= ~(3<<16);  // PL = 0
	
	// 9. Adding streamX in STM32F4xx(Cortex M4), we need to set CHSEL Reg to select Channel, which map to channel.
	DMA1_Stream5->CR |= (4<<25);  // CHSEL = 4
}



void DMA_Config (uint32_t srcAdd, uint32_t destAdd, uint16_t datasize)
{
	
	// 1. Set the data size in CNDTR Register
	DMA1_Stream5->NDTR = datasize;
	
	// 2. Set the  peripheral address in PAR Register
	DMA1_Stream5->PAR = srcAdd;
	
	// 3. Set the  Memory address in MAR Register
	DMA1_Stream5->M0AR = destAdd;
	
	// 4. Enable the DMA1
	DMA1_Stream5->CR |= 1<<0;
	
}












int main(void)
{
	SysClockConfig();
	//gpio_config();
	uart2_config();
	
	DMA_Init ();
	
	NVIC_SetPriority (DMA1_Stream5_IRQn, 0);
	
	NVIC_EnableIRQ (DMA1_Stream5_IRQn);
	
	DMA_Config ((uint32_t) &USART2->DR, (uint32_t) RxBuf, RXSIZE);
	
	
	int a = 100;
	printf("ABDDD \n");
	
	while(1)
	{

		//printf("ABDDD %d \n", a);
		
		delay(1000);
	}
	
}


