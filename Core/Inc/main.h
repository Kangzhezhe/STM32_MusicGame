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
#include "stm32f4xx_hal.h"

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
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef uint32_t  u32;
 
typedef uint16_t u16;
 
typedef uint8_t  u8;
 
typedef __IO uint32_t  vu32;
 
typedef __IO uint16_t vu16;
 
typedef __IO uint8_t  vu8;
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TCS_Pin GPIO_PIN_13
#define TCS_GPIO_Port GPIOC
#define LED_ON_Board_Pin GPIO_PIN_10
#define LED_ON_Board_GPIO_Port GPIOF
#define WK_UP_Pin GPIO_PIN_0
#define WK_UP_GPIO_Port GPIOA
#define C1_Pin GPIO_PIN_1
#define C1_GPIO_Port GPIOA
#define C2_Pin GPIO_PIN_2
#define C2_GPIO_Port GPIOA
#define C3_Pin GPIO_PIN_3
#define C3_GPIO_Port GPIOA
#define K2_Pin GPIO_PIN_7
#define K2_GPIO_Port GPIOA
#define K1_Pin GPIO_PIN_4
#define K1_GPIO_Port GPIOC
#define K3_Pin GPIO_PIN_5
#define K3_GPIO_Port GPIOC
#define TSCK_Pin GPIO_PIN_0
#define TSCK_GPIO_Port GPIOB
#define TPEN_Pin GPIO_PIN_1
#define TPEN_GPIO_Port GPIOB
#define TMISO_Pin GPIO_PIN_2
#define TMISO_GPIO_Port GPIOB
#define TMOSI_Pin GPIO_PIN_11
#define TMOSI_GPIO_Port GPIOF
#define K6_Pin GPIO_PIN_13
#define K6_GPIO_Port GPIOF
#define K4_Pin GPIO_PIN_14
#define K4_GPIO_Port GPIOF
#define K7_Pin GPIO_PIN_15
#define K7_GPIO_Port GPIOF
#define K5_Pin GPIO_PIN_0
#define K5_GPIO_Port GPIOG
#define DO_Pin GPIO_PIN_1
#define DO_GPIO_Port GPIOG
#define DI_Pin GPIO_PIN_11
#define DI_GPIO_Port GPIOB
#define W25QXX_CS_Pin GPIO_PIN_14
#define W25QXX_CS_GPIO_Port GPIOB
#define LCD_BL_Pin GPIO_PIN_15
#define LCD_BL_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_8
#define KEY1_GPIO_Port GPIOB
#define KEY0_Pin GPIO_PIN_9
#define KEY0_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
