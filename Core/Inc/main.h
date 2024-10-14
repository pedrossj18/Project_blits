/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#define LED_VERMELHO_Pin GPIO_PIN_13
#define LED_VERMELHO_GPIO_Port GPIOC
#define BT_DIR_Pin GPIO_PIN_3
#define BT_DIR_GPIO_Port GPIOA
#define BT_CIMA_Pin GPIO_PIN_4
#define BT_CIMA_GPIO_Port GPIOA
#define BT_BAIXO_Pin GPIO_PIN_5
#define BT_BAIXO_GPIO_Port GPIOA
#define BT_ESQ_Pin GPIO_PIN_6
#define BT_ESQ_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_13
#define LCD_RS_GPIO_Port GPIOB
#define LCD_E_Pin GPIO_PIN_14
#define LCD_E_GPIO_Port GPIOB
#define LCD_D4_Pin GPIO_PIN_15
#define LCD_D4_GPIO_Port GPIOA
#define LCD_D5_Pin GPIO_PIN_3
#define LCD_D5_GPIO_Port GPIOB
#define LCD_D6_Pin GPIO_PIN_4
#define LCD_D6_GPIO_Port GPIOB
#define LCD_D7_Pin GPIO_PIN_8
#define LCD_D7_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
