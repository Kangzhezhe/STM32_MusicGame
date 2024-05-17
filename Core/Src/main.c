/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "delay.h"
#include "lcd.h"
#include "w25qxx.h"
#include "touch.h"
#include "GBK_LibDrive.h"	
#include "lv_port_disp.h"
#include "lvgl.h"
#include "lv_port_indev.h"
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//清空屏幕并在右上角显示"RST"
void Load_Drow_Dialog(void)
{
	GBK_LibFont_Test();//字库显示测试
//	LCD_Clear(WHITE);	//清屏   
 	POINT_COLOR=RED;	//设置字体为蓝色 
	LCD_ShowString(lcddev.width-24,0,200,16,16,RED,"RST");//显示清屏区域
  POINT_COLOR=RED;	//设置画笔蓝色 
	
}

void rtp_test(void)
{
//	u8 key;
//	u8 i=0;	  
	while(1)
	{
		
	 	//key=KEY_Scan(0);
		
		tp_dev.scan(0); 	
		
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{	
		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{	
				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)
					Load_Drow_Dialog();//清除
				else 
					TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//画图	  			   
			}
		}
		else delay_ms(10);	//没有按键按下的时候 	  
		
//		if(key==KEY0_PRES)	//KEY0按下,则执行校准程序
//		{
//			LCD_Clear(WHITE);  //清屏
//		  TP_Adjust();  	   //屏幕校准  
//			Load_Drow_Dialog();
//		}
		
//		i++;
//		if(i%20==0)
//		{
//		  LED1=!LED1;//LED灯闪，指示系统在运行
//		}
		
	}
}

void my_tptest(){
		LCD_ShowString(16,20,200,16,16,RED,"mcudev STM32F4");	
	LCD_ShowString(16,40,200,16,16,RED,"TOUCH TEST");	
	LCD_ShowString(16,60,200,16,16,RED,"mcudev.taobao.com");
	LCD_ShowString(16,80,200,16,16,RED,"2019/1/15");
   
//	LCD_ShowString(30,100,200,16,16,RED,"Press KEY0 to Adjust");
	
  //使用有字库屏幕，可以进行下面显示
		
	GBK_Show_Str(16,120,240,32,"字库测试-32",32,BLUE,WHITE,0);	
	GBK_Show_Str(16,160,240,24,"2.8/3.2寸液晶屏-24",24,BLUE,WHITE,0);	
	GBK_Show_Str(16,190,240,16,"设计：大越电子-16",16,BLUE,WHITE,0);	
	GBK_Show_Str(16,210,240,12,"From: mcudev.taobao.com-12",12,BLUE,WHITE,0);	
  
	LCD_ShowString(16,230,240,16,16,RED,"Press KEY0 to Adjust");//电阻屏才显示
	
	delay_ms(1500);
 	Load_Drow_Dialog();	 	
	

	rtp_test(); 					//电阻屏测试
}



static lv_obj_t * label;

static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);

    /*Refresh the text*/
    lv_label_set_text_fmt(label, "%"LV_PRId32, lv_slider_get_value(slider));
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
}

/**
 * Create a slider and write its value on a label.
 */
void lv_example_get_started_1(void)
{
    /*Create a slider in the center of the display*/
    lv_obj_t * slider = lv_slider_create(lv_screen_active());
    lv_obj_set_width(slider, 200);                          /*Set the width*/
    lv_obj_center(slider);                                  /*Align to the center of the parent (screen)*/
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);     /*Assign an event function*/

    /*Create a label above the slider*/
    label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "0");
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
	
}

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
  MX_USART1_UART_Init();
  MX_FSMC_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim1); 
	delay_init(100);
	LCD_Init();
	W25QXX_Init();			//W25QXX初始化
	
  POINT_COLOR=RED; 
	
	while(W25QXX_ReadID()!=W25Q16)								//检测不到W25QXX
	{
		LCD_ShowString(30,150,200,16,16,RED,"W25Q16 Check Failed!");
		delay_ms(500);
		LCD_ShowString(30,150,200,16,16,RED,"Please Check!      ");
		delay_ms(500);
		HAL_GPIO_TogglePin(LED_ON_Board_GPIO_Port,LED_ON_Board_Pin);
	}
	LCD_ShowString(30,150,200,16,16,RED,"W25Q16 Ready!"); 
	
	GBK_Lib_Init();       //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化） 
	
	tp_dev.init();				//触摸屏初始化
	
	LCD_Clear(WHITE);//清除屏幕
	
	//lvgl
	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();
	lv_example_get_started_1();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//		delay_ms(1000);
//		
//		HAL_GPIO_TogglePin(LED_ON_Board_GPIO_Port,LED_ON_Board_Pin);
		
		lv_timer_handler();
    HAL_Delay(1);
		//HAL_GPIO_TogglePin(LED_ON_Board_GPIO_Port,LED_ON_Board_Pin);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 200;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//5ms
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if(htim->Instance == TIM1){
//        static u32 cnt = 0;
//        if (cnt++>=200)
//        {
//            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
//            cnt = 0;
//        }
        lv_tick_inc(5);
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
