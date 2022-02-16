/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define number1_arti_Pin GPIO_PIN_0
#define number1_arti_GPIO_Port GPIOC
#define number1_eksi_Pin GPIO_PIN_1
#define number1_eksi_GPIO_Port GPIOC
#define number2_arti_Pin GPIO_PIN_2
#define number2_arti_GPIO_Port GPIOC
#define number2_eksi_Pin GPIO_PIN_3
#define number2_eksi_GPIO_Port GPIOC
#define sum_bcd1_1_Pin GPIO_PIN_0
#define sum_bcd1_1_GPIO_Port GPIOA
#define sum_bcd1_2_Pin GPIO_PIN_1
#define sum_bcd1_2_GPIO_Port GPIOA
#define sum_bcd1_3_Pin GPIO_PIN_2
#define sum_bcd1_3_GPIO_Port GPIOA
#define sum_bcd1_4_Pin GPIO_PIN_3
#define sum_bcd1_4_GPIO_Port GPIOA
#define sum_bcd2_1_Pin GPIO_PIN_4
#define sum_bcd2_1_GPIO_Port GPIOA
#define sum_bcd2_2_Pin GPIO_PIN_5
#define sum_bcd2_2_GPIO_Port GPIOA
#define sum_bcd2_3_Pin GPIO_PIN_6
#define sum_bcd2_3_GPIO_Port GPIOA
#define sum_bcd2_4_Pin GPIO_PIN_7
#define sum_bcd2_4_GPIO_Port GPIOA
#define sum_Pin GPIO_PIN_4
#define sum_GPIO_Port GPIOC
#define bcd1_1_Pin GPIO_PIN_0
#define bcd1_1_GPIO_Port GPIOB
#define bcd1_2_Pin GPIO_PIN_1
#define bcd1_2_GPIO_Port GPIOB
#define bcd1_3_Pin GPIO_PIN_2
#define bcd1_3_GPIO_Port GPIOB
#define bcd1_4_Pin GPIO_PIN_3
#define bcd1_4_GPIO_Port GPIOB
#define bcd2_1_Pin GPIO_PIN_4
#define bcd2_1_GPIO_Port GPIOB
#define bcd2_2_Pin GPIO_PIN_5
#define bcd2_2_GPIO_Port GPIOB
#define bcd2_3_Pin GPIO_PIN_6
#define bcd2_3_GPIO_Port GPIOB
#define bcd2_4_Pin GPIO_PIN_7
#define bcd2_4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
