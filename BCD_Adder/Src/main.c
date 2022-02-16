/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t number1=0;
uint16_t number2=0;
uint16_t number1artiState=0;
uint16_t number1eksiState=0;
uint16_t number2artiState=0;
uint16_t number2eksiState=0;
uint16_t sumButtonState=0;
uint16_t firstDigit=0;
uint16_t secondDigit=0;
uint16_t result=0;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		number1artiState=HAL_GPIO_ReadPin(GPIOC,number1_arti_Pin);
		number1eksiState=HAL_GPIO_ReadPin(GPIOC,number1_eksi_Pin);
		number2artiState=HAL_GPIO_ReadPin(GPIOC,number2_arti_Pin);
		number2eksiState=HAL_GPIO_ReadPin(GPIOC,number2_eksi_Pin);
		sumButtonState=HAL_GPIO_ReadPin(GPIOC,sum_Pin);
		
		if(number1artiState){
			if(number1!=9){
				number1++;
			}
		
		}
		if(number1eksiState){
			if(number1>0){
				number1--;
			}
		
		}
		
		if(number2artiState){
			if(number2!=9){
				number2++;
			}
		
		}
		if(number2eksiState){
			if(number2>0){
				number2--;
			}
		
		}
		
		GPIOB->ODR=number1 | (number2<<4);
		GPIOA->ODR=firstDigit | (secondDigit<<4);
		result=number1+number2;
		
		if(sumButtonState){
			firstDigit=result%10;
			secondDigit=result/10;
      GPIOA->ODR=firstDigit | (secondDigit<<4);
		}
		HAL_Delay(150);
		
		
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, sum_bcd1_1_Pin|sum_bcd1_2_Pin|sum_bcd1_3_Pin|sum_bcd1_4_Pin 
                          |sum_bcd2_1_Pin|sum_bcd2_2_Pin|sum_bcd2_3_Pin|sum_bcd2_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, bcd1_1_Pin|bcd1_2_Pin|bcd1_3_Pin|bcd1_4_Pin 
                          |bcd2_1_Pin|bcd2_2_Pin|bcd2_3_Pin|bcd2_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : number1_arti_Pin number1_eksi_Pin number2_arti_Pin number2_eksi_Pin 
                           sum_Pin */
  GPIO_InitStruct.Pin = number1_arti_Pin|number1_eksi_Pin|number2_arti_Pin|number2_eksi_Pin 
                          |sum_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : sum_bcd1_1_Pin sum_bcd1_2_Pin sum_bcd1_3_Pin sum_bcd1_4_Pin 
                           sum_bcd2_1_Pin sum_bcd2_2_Pin sum_bcd2_3_Pin sum_bcd2_4_Pin */
  GPIO_InitStruct.Pin = sum_bcd1_1_Pin|sum_bcd1_2_Pin|sum_bcd1_3_Pin|sum_bcd1_4_Pin 
                          |sum_bcd2_1_Pin|sum_bcd2_2_Pin|sum_bcd2_3_Pin|sum_bcd2_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : bcd1_1_Pin bcd1_2_Pin bcd1_3_Pin bcd1_4_Pin 
                           bcd2_1_Pin bcd2_2_Pin bcd2_3_Pin bcd2_4_Pin */
  GPIO_InitStruct.Pin = bcd1_1_Pin|bcd1_2_Pin|bcd1_3_Pin|bcd1_4_Pin 
                          |bcd2_1_Pin|bcd2_2_Pin|bcd2_3_Pin|bcd2_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
