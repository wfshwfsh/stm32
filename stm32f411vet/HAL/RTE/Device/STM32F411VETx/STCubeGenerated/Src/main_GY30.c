/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
	
PUTCHAR_PROTOTYPE
{
HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
return ch;
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define I2C_LCD1602A_ADDR 0x4E

#define BHAddWrite 0x46 //BH address+write reg
#define BHAddRead 0x47 //BH address+read reg
#define BHPowDown 0x00 //power down
#define BHPowOn 0x01  // power on
#define BHReset 0x07 //reset
#define BHSigModeH 0x20 //?????? ?? ??????? PowerDown??
#define BHSigModeH2 0x21 //????

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */


void lcd1602A_sendData(char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	
	data_u = data&0xf0;
	data_l = (data<<4)&0xf0;
	
	data_t[0] = data_u | 0x0D;
	data_t[1] = data_u | 0x09;
	data_t[2] = data_u | 0x0D;
	data_t[3] = data_u | 0x09;
	HAL_I2C_Master_Transmit (&hi2c1, I2C_LCD1602A_ADDR,(uint8_t *) data_t, 4, 100);
}

void lcd1602A_sendCmd(char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	
	data_u = data&0xf0;
	data_l = (data<<4)&0xf0;
	
	data_t[0] = data_u | 0x0C;
	data_t[1] = data_u | 0x08;
	data_t[2] = data_u | 0x0C;
	data_t[3] = data_u | 0x08;
	HAL_I2C_Master_Transmit (&hi2c1, I2C_LCD1602A_ADDR,(uint8_t *) data_t, 4, 100);
}

void lcd1602A_init(void)
{
	HAL_Delay(50);
	lcd1602A_sendCmd(0x30);
	HAL_Delay(5);
	lcd1602A_sendCmd(0x30);
	HAL_Delay(1);
	lcd1602A_sendCmd(0x30);
	HAL_Delay(10);
	lcd1602A_sendCmd(0x20);
	HAL_Delay(10);
	
	//function set
	lcd1602A_sendCmd(0x28);
	HAL_Delay(5);
	
	//display off
	lcd1602A_sendCmd(0x08);
	HAL_Delay(5);
	
	//clear display
	lcd1602A_sendCmd(0x01);
	HAL_Delay(5);
	
	//entry mode set
	lcd1602A_sendCmd(0x06);
	HAL_Delay(5);
	
	lcd1602A_sendCmd(0x0c);
	HAL_Delay(10);
	
}

void lcd_send_string (char *str)
{
	while (*str) lcd1602A_sendData (*str++);
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

	uint8_t Mode;

	// --- GY30_Init() beg
	//Ref: https://www.twblogs.net/a/5d5efa4cbd9eee5327fddbc7
	Mode = BHPowOn;
	HAL_I2C_Master_Transmit(&hi2c1,BHAddWrite,&Mode ,1,0xff);

	Mode = BHReset;
	HAL_I2C_Master_Transmit(&hi2c1,BHAddWrite,&Mode ,1,0xff);
	// --- GY30_Init() end
	//lcd1602A_init();
	//int i=0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		Mode = BHSigModeH2;
		HAL_I2C_Master_Transmit(&hi2c1,BHAddWrite,&Mode ,1,0xff);
		
		uint8_t buff[2]={0,0};
		HAL_I2C_Master_Receive(&hi2c1, BHAddRead, buff, 2, 1000);
		
		/* Data translate:
 		*    High Byte = "1000_0011"
		*    Low Byte  = "1001_0000"
		*    2^15 + 2^9 + 2^8 + 2^7 +2^4 / 1.2 ~ 28067 lx
		*/
		
		uint16_t dis_data;
		dis_data=(buff[0]<<8)+buff[1];
		float temp=(float)dis_data/1.2;
		printf("temp %f\n", temp);
    //printf("\n");
		//lcd_send_string("HELLO WORLD");
		/* USER CODE END WHILE */
		
		//for(i=20;i<100;i++){
		//	lcd1602A_sendData(i);
		//}
		
    /* USER CODE BEGIN 3 */
		HAL_Delay(1000);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
