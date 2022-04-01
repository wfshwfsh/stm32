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

int main(void)
{
	SysClockConfig();
	gpio_config();
	uart2_config();
	
	int a = 100;
	printf("ABDDD %d \n", a);
	
	while(1)
	{
		GPIOA->BSRR |= (1<<5);
		delay(1000);
		
		//GPIOA->BSRR |= ((1<<5) <<16);
		delay(1000);
		
		//UART2_SendString("Hello World\n");
		delay(1000);
	}
	
}


