#include <stdint.h>
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

#define BH_Addr 0b0100011
#define BH_AddrRead  ((0b0100011<<1) | 1)
#define BH_AddrWrite ((0b0100011<<1) | 0)

#define BH_PowerOn   0x01
#define BH_PowerDown 0x00
#define BH_Reset     0x07 
#define BH_ModeH1    0x10
#define BH_ModeH2    0x11
#define BH_ModeL     0x13
#define BH_SigModeH  0x20
#define BH_SigModeH2 0x21
#define BH_SigModeL  0x23

#define GY30_CMD_SET(_cmd) \
{ \
	uint8_t cmd = _cmd; \
	I2C_Start(); \
	I2C_Address (BH_AddrWrite); \
	I2C_Write(cmd); \
	I2C_Stop (); \
}

void gy30_init(void)
{
	//printf("addr r = %x\n", BH_AddrRead);
	//printf("addr r = %x\n", BH_AddrWrite);
	
	
	//init flow: Power-down, Power-on, Reset
	GY30_CMD_SET(BH_PowerDown);
	GY30_CMD_SET(BH_PowerOn);
	GY30_CMD_SET(BH_Reset);
	
	//set measure mode to Continuously H-Resolution Mode 
	GY30_CMD_SET(BH_ModeH1);

	//wait 180 ms for mode complete
	delay_ms(200);
}

double gy30_read(void)
{
	uint8_t buf[2];
	double val=0;
	
	I2C_Read(BH_AddrRead, (uint8_t *)buf, 2);
	//HAL_I2C_Master_Receive(&hi2c1, BH_AddrRead, (uint8_t *)buf, 2, 0xff);
	//printf("val[0] = %02x\n", val[0]);
	//printf("val[1] = %02x\n", val[1]);
	
	val = (double)((buf[0] << 8) | (buf[1])) / 1.2;
	
	//printf("val = %f\n", val);
	return val;
}


int main(void)
{
	SysClockConfig();
	gpio_config();
	tim2_config();
	uart2_config();
	I2C_Config();
	
	UART2_SendString("Hello World\n");
	int a = 5;
	printf("Hello World222 %d\n", a);
	//GPIOA->BSRR |= (1<<5);
	gy30_init();
	printf("3333 %d\n", a);
	
	while(1)
	{
		//uint32_t val = GPIOA->IDR;
		//if((val & (1<<1))){
		//	GPIOA->BSRR |= (1<<5);
		//}else{
		//	GPIOA->BSRR |= ((1<<5) <<16);
		//}
		GPIOA->BSRR |= (1<<5);
		delay_ms(1000);
		GPIOA->BSRR |= ((1<<5) <<16);
		delay_ms(1000);
	}
}


