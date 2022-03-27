#include <stdint.h>
#include <math.h>
#include "i2c.h"
#include "i2c_lcd1602a.h"
#include "stm32f411xe.h"


void lcd1602a_send_cmd(char _cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (_cmd&0xf0);
	data_l = ((_cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd1602a_send_data(char _data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (_data&0xf0);
	data_l = ((_data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=1
	data_t[1] = data_u|0x09;  //en=0, rs=1
	data_t[2] = data_l|0x0D;  //en=1, rs=1
	data_t[3] = data_l|0x09;  //en=0, rs=1
	HAL_I2C_Master_Transmit (&hi2c1, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}


void lcd1602a_init(void)
{
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	lcd1602a_send_cmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	lcd1602a_send_cmd (0x30);
	HAL_Delay(1);  // wait for >100us
	lcd1602a_send_cmd (0x30);
	HAL_Delay(10);
	lcd1602a_send_cmd (0x20);  // 4bit mode
	HAL_Delay(10);

  // dislay initialisation
	lcd1602a_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd1602a_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd1602a_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd1602a_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd1602a_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}


void lcd_clear (void)
{
	lcd1602a_send_cmd (0x80);
	for (int i=0; i<70; i++)
	{
		lcd1602a_send_data (' ');
	}
}

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd1602a_send_cmd (col);
}

void lcd_send_string (char *str)
{
	while (*str) lcd1602a_send_data (*str++);
}