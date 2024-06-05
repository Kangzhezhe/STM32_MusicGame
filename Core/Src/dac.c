/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dac.c
  * @brief   This file provides code for the configuration
  *          of the DAC instances.
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
/* Includes ------------------------------------------------------------------*/
#include "dac.h"

/* USER CODE BEGIN 0 */
#include "tim.h"
uint16_t DAC_buff[DAC_BUF_LEN]; 
//210个点
//u16 TriWave_Value[]={0 ,
//39 ,78 ,117 ,156 ,195 ,234 ,273 ,312 ,351 ,390 ,429 ,468 ,507 ,546 ,585 ,624 ,663 ,702 ,741 ,780 ,819 ,858 ,897 ,936 ,975 ,
//1014 ,1053 ,1092 ,1131 ,1170 ,1209 ,1248 ,1287 ,1326 ,1365 ,1404 ,1443 ,1482 ,1521 ,1560 ,1599 ,1638 ,1677 ,1716 ,1755 ,1794 ,1833 ,1872 ,1911 ,1950 ,
//1989 ,2028 ,2067 ,2106 ,2145 ,2184 ,2223 ,2262 ,2301 ,2340 ,2379 ,2418 ,2457 ,2496 ,2535 ,2574 ,2613 ,2652 ,2691 ,2730 ,2769 ,2808 ,2847 ,2886 ,2925 ,
//2964 ,3003 ,3042 ,3081 ,3120 ,3159 ,3198 ,3237 ,3276 ,3315 ,3354 ,3393 ,3432 ,3471 ,3510 ,3549 ,3588 ,3627 ,3666 ,3705 ,3744 ,3783 ,3822 ,3861 ,3900 ,
//3939 ,3978 ,4017 ,4056 ,4095 ,4056 ,4017 ,3978 ,3939 ,3900 ,3861 ,3822 ,3783 ,3744 ,3705 ,3666 ,3627 ,3588 ,3549 ,3510 ,3471 ,3432 ,3393 ,3354 ,3315 ,
//3276 ,3237 ,3198 ,3159 ,3120 ,3081 ,3042 ,3003 ,2964 ,2925 ,2886 ,2847 ,2808 ,2769 ,2730 ,2691 ,2652 ,2613 ,2574 ,2535 ,2496 ,2457 ,2418 ,2379 ,2340 ,
//2301 ,2262 ,2223 ,2184 ,2145 ,2106 ,2067 ,2028 ,1989 ,1950 ,1911 ,1872 ,1833 ,1794 ,1755 ,1716 ,1677 ,1638 ,1599 ,1560 ,1521 ,1482 ,1443 ,1404 ,1365 ,
//1326 ,1287 ,1248 ,1209 ,1170 ,1131 ,1092 ,1053 ,1014 ,975 ,936 ,897 ,858 ,819 ,780 ,741 ,702 ,663 ,624 ,585 ,546 ,507 ,468 ,429 ,390 ,
//351 ,312 ,273 ,234 ,195 ,156 ,117 ,78 ,39};
/* USER CODE END 0 */

DAC_HandleTypeDef hdac;
DMA_HandleTypeDef hdma_dac1;

/* DAC init function */
void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */

  /** DAC Initialization
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_T2_TRGO;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */
	//HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,0);
	//HAL_DAC_Start(&hdac,DAC_CHANNEL_1);
	//HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1,(u32*)TriWave_Value,210,DAC_ALIGN_12B_R);
	HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1,(u32*)DAC_buff,2000,DAC_ALIGN_12B_L);
  /* USER CODE END DAC_Init 2 */

}

void HAL_DAC_MspInit(DAC_HandleTypeDef* dacHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(dacHandle->Instance==DAC)
  {
  /* USER CODE BEGIN DAC_MspInit 0 */

  /* USER CODE END DAC_MspInit 0 */
    /* DAC clock enable */
    __HAL_RCC_DAC_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**DAC GPIO Configuration
    PA4     ------> DAC_OUT1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* DAC DMA Init */
    /* DAC1 Init */
    hdma_dac1.Instance = DMA1_Stream5;
    hdma_dac1.Init.Channel = DMA_CHANNEL_7;
    hdma_dac1.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_dac1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_dac1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_dac1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_dac1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_dac1.Init.Mode = DMA_CIRCULAR;
    hdma_dac1.Init.Priority = DMA_PRIORITY_MEDIUM;
    hdma_dac1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_dac1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(dacHandle,DMA_Handle1,hdma_dac1);

    /* DAC interrupt Init */
    HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 15, 0);
    HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
  /* USER CODE BEGIN DAC_MspInit 1 */
	__HAL_DMA_ENABLE_IT(&hdma_dac1, DMA_IT_HT | DMA_IT_TC | DMA_IT_TE);
  /* USER CODE END DAC_MspInit 1 */
  }
}

void HAL_DAC_MspDeInit(DAC_HandleTypeDef* dacHandle)
{

  if(dacHandle->Instance==DAC)
  {
  /* USER CODE BEGIN DAC_MspDeInit 0 */

  /* USER CODE END DAC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DAC_CLK_DISABLE();

    /**DAC GPIO Configuration
    PA4     ------> DAC_OUT1
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);

    /* DAC DMA DeInit */
    HAL_DMA_DeInit(dacHandle->DMA_Handle1);

    /* DAC interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
  /* USER CODE BEGIN DAC_MspDeInit 1 */

  /* USER CODE END DAC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
//设置通道1输出电压
//vol:0~3300,代表0~3.3V
void Dac1_Set_Vol(u16 vol)
{
	double temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,temp);
}
#define   CNT_FREQ          50000000      // TIM2 counter clock (prescaled APB1)

void DAC_DMA_Clean(void)
{
    for (int i = 0; i < DAC_BUF_LEN; i++){
        DAC_buff[i] = 32768;
    }
}

//配置DAC采样率和DMA数据长度，并启动DMA DAC
void DAC_DMA_Start(uint32_t freq, uint16_t len)
{
	HAL_TIM_Base_Stop(&htim2);
	//设置DMA缓冲长度需要停止DMA
	HAL_DAC_Stop_DMA(&hdac,DAC_CHANNEL_1);
    DAC_DMA_Clean();
	HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1,(u32*)DAC_buff,len,DAC_ALIGN_12B_L);
    
	//设置定时器
	__HAL_TIM_SetAutoreload(&htim2,(u32)((CNT_FREQ)/freq));
	HAL_TIM_Base_Start(&htim2);
}

//void DAC_Out(uint16_t dat)
//{
//	HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,dat);
//}

//void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef *hdac)
//{
//    /*翻转RED_LED引脚状态*/
//    HAL_GPIO_TogglePin(LED_ON_Board_GPIO_Port,LED_ON_Board_Pin);
//}
//void HAL_DAC_ConvHalfCpltCallbackCh1(DAC_HandleTypeDef *hdac){
//		HAL_GPIO_TogglePin(LED_ON_Board_GPIO_Port,LED_ON_Board_Pin);
//}
/* USER CODE END 1 */
