/******************************************************************************
 * File Name   : MX_Device.h
 * Date        : 27/03/2022 09:19:01
 * Description : STM32Cube MX parameter definitions
 * Note        : This file is generated by STM32CubeMX (DO NOT EDIT!)
 ******************************************************************************/

#ifndef __MX_DEVICE_H
#define __MX_DEVICE_H

/*---------------------------- Clock Configuration ---------------------------*/

#define MX_LSI_VALUE                            32000
#define MX_LSE_VALUE                            32768
#define MX_HSI_VALUE                            16000000
#define MX_HSE_VALUE                            8000000
#define MX_EXTERNAL_CLOCK_VALUE                 12288000
#define MX_PLLCLKFreq_Value                     72000000
#define MX_SYSCLKFreq_VALUE                     72000000
#define MX_HCLKFreq_Value                       72000000
#define MX_FCLKCortexFreq_Value                 72000000
#define MX_CortexFreq_Value                     72000000
#define MX_AHBFreq_Value                        72000000
#define MX_APB1Freq_Value                       36000000
#define MX_APB2Freq_Value                       72000000
#define MX_APB1TimFreq_Value                    72000000
#define MX_APB2TimFreq_Value                    72000000
#define MX_48MHZClocksFreq_Value                36000000
#define MX_EthernetFreq_Value                   72000000
#define MX_I2SClocksFreq_Value                  48000000
#define MX_RTCFreq_Value                        32000
#define MX_WatchDogFreq_Value                   32000
#define MX_MCO1PinFreq_Value                    16000000
#define MX_MCO2PinFreq_Value                    72000000

/*-------------------------------- SYS        --------------------------------*/

#define MX_SYS                                  1

/* GPIO Configuration */

/*-------------------------------- TIM2       --------------------------------*/

#define MX_TIM2                                 1

/* GPIO Configuration */

/* NVIC Configuration */

/* NVIC TIM2_IRQn */
#define MX_TIM2_IRQn_interruptPremptionPriority 0
#define MX_TIM2_IRQn_PriorityGroup              NVIC_PRIORITYGROUP_4
#define MX_TIM2_IRQn_Subriority                 0

/*-------------------------------- NVIC       --------------------------------*/

#define MX_NVIC                                 1

/*-------------------------------- GPIO       --------------------------------*/

#define MX_GPIO                                 1

/* GPIO Configuration */

/* Pin PA1 */
#define MX_PA1_Pin                              PA1
#define MX_PA1_GPIOx                            GPIOA
#define MX_PA1_GPIO_PuPd                        GPIO_PULLUP
#define MX_PA1_GPIO_Pin                         GPIO_PIN_1
#define MX_PA1_GPIO_Mode                        GPIO_MODE_INPUT

/* Pin PA5 */
#define MX_PA5_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PA5_Pin                              PA5
#define MX_PA5_GPIOx                            GPIOA
#define MX_PA5_PinState                         GPIO_PIN_RESET
#define MX_PA5_GPIO_PuPd                        GPIO_NOPULL
#define MX_PA5_GPIO_Pin                         GPIO_PIN_5
#define MX_PA5_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

#endif  /* __MX_DEVICE_H */

