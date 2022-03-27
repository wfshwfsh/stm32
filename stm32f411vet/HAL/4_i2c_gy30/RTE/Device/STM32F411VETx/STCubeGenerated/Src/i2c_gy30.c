#include <stdint.h>
#include <math.h>
#include "i2c.h"
#include "i2c_gy30.h"
#include "stm32f411xe.h"

#define GY30_CMD_SET(i2c_h, _cmd) \
{ \
	uint8_t cmd = _cmd; \
	HAL_I2C_Master_Transmit(i2c_h, BH_AddrWrite, (uint8_t *)&cmd, 1, 1000); \
}

void gy30_init(void)
{
	//printf("addr r = %x\n", BH_AddrRead);
	//printf("addr r = %x\n", BH_AddrWrite);
	
	uint8_t cmd;
	
	//init flow: Power-down, Power-on, Reset
	GY30_CMD_SET(&hi2c1, BH_PowerDown);
	GY30_CMD_SET(&hi2c1, BH_PowerOn);
	GY30_CMD_SET(&hi2c1, BH_Reset);
	
	//set measure mode to Continuously H-Resolution Mode 
	GY30_CMD_SET(&hi2c1, BH_ModeH1);

	//wait 180 ms for mode complete
	HAL_Delay(200);
}

double gy30_read(void)
{
	uint8_t buf[2];
	double val=0;
	
	HAL_I2C_Master_Receive(&hi2c1, BH_AddrRead, (uint8_t *)buf, 2, 0xff);
	//printf("val[0] = %02x\n", val[0]);
	//printf("val[1] = %02x\n", val[1]);
	
	val = (double)((buf[0] << 8) | (buf[1])) / 1.2;
	
	//printf("val = %f\n", val);
	return val;
}

