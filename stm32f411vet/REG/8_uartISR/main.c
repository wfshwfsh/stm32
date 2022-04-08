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

char uartRxBufIdx=0;
char uartRxBuf[50];
static int cnt = 0;

void USART2_IRQHandler(void)
{
	cnt++;
	
	uint8_t temp;
	
	
	//check is RXNE bit be set
	if(!(USART2->SR & (1<<5))){
		temp = USART2->DR;  // Read the data. This clears the RXNE interrupt also
		uartRxBuf[uartRxBufIdx] = temp;
		uartRxBufIdx++;
	}
	
	USART2->SR &= ~(1<<5);
	
	
	return;
}

int main(void)
{
	SysClockConfig();
	gpio_config();
	uart2_config();
	

	int a = 100;
	printf("ABDDD %d \n", a);
	
	while(1)
	{

		delay(1000);
	}
	
}


