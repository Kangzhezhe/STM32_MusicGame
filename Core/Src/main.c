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
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
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
#include "stdio.h"
#include "ctype.h"
#include "string.h"
#include "key.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//sd
#define BLOCK_START_ADDR 0 /* Block start address */
#define NUM_OF_BLOCKS 1 /* Total number of blocks */
#define BUFFER_WORDS_SIZE ((BLOCKSIZE * NUM_OF_BLOCKS) >> 2) /* Total data size in bytes */
uint8_t Buffer_Tx[512],Buffer_Rx[512] = { 
   0};
uint32_t i;
HAL_StatusTypeDef Return_Status;
extern DMA_HandleTypeDef hdma_sdio;
HAL_StatusTypeDef SDIO_ReadBlocks_DMA(SD_HandleTypeDef *hsd, uint8_t *pData, uint32_t BlockAdd, uint32_t NumberOfBlocks);
HAL_StatusTypeDef SDIO_WriteBlocks_DMA(SD_HandleTypeDef *hsd, uint8_t *pData, uint32_t BlockAdd, uint32_t NumberOfBlocks);
	 
//fs
FIL file;
UINT br,bw;
uint16_t rBuffer[20];      //��SD�������ݣ����뵽������
uint16_t WBuffer[20] ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

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
//�����Ļ�������Ͻ���ʾ"RST"
void Load_Drow_Dialog(void)
{
	GBK_LibFont_Test();//�ֿ���ʾ����
//	LCD_Clear(WHITE);	//����   
 	POINT_COLOR=RED;	//��������Ϊ��ɫ 
	LCD_ShowString(lcddev.width-24,0,200,16,16,RED,"RST");//��ʾ��������
  POINT_COLOR=RED;	//���û�����ɫ 
	
}

void rtp_test(void)
{
//	u8 key;
//	u8 i=0;	  
	while(1)
	{
		
	 	//key=KEY_Scan(0);
		
		tp_dev.scan(0); 	
		
		if(tp_dev.sta&TP_PRES_DOWN)			//������������
		{	
		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{	
				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)
					Load_Drow_Dialog();//���
				else 
					TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//��ͼ	  			   
			}
		}
		else delay_ms(10);	//û�а������µ�ʱ�� 	  
		
//		if(key==KEY0_PRES)	//KEY0����,��ִ��У׼����
//		{
//			LCD_Clear(WHITE);  //����
//		  TP_Adjust();  	   //��ĻУ׼  
//			Load_Drow_Dialog();
//		}
		
//		i++;
//		if(i%20==0)
//		{
//		  LED1=!LED1;//LED������ָʾϵͳ������
//		}
		
	}
}

void my_tptest(){
		LCD_ShowString(16,20,200,16,16,RED,"mcudev STM32F4");	
	LCD_ShowString(16,40,200,16,16,RED,"TOUCH TEST");	
	LCD_ShowString(16,60,200,16,16,RED,"mcudev.taobao.com");
	LCD_ShowString(16,80,200,16,16,RED,"2019/1/15");
   
//	LCD_ShowString(30,100,200,16,16,RED,"Press KEY0 to Adjust");
	
  //ʹ�����ֿ���Ļ�����Խ���������ʾ
		
	GBK_Show_Str(16,120,240,32,"�ֿ����-32",32,BLUE,WHITE,0);	
	GBK_Show_Str(16,160,240,24,"2.8/3.2��Һ����-24",24,BLUE,WHITE,0);	
	GBK_Show_Str(16,190,240,16,"��ƣ���Խ����-16",16,BLUE,WHITE,0);	
	GBK_Show_Str(16,210,240,12,"From: mcudev.taobao.com-12",12,BLUE,WHITE,0);	
  
	LCD_ShowString(16,230,240,16,16,RED,"Press KEY0 to Adjust");//����������ʾ
	
	delay_ms(1500);
 	Load_Drow_Dialog();	 	
	

	rtp_test(); 					//����������
}

void SD_test(void){
	printf("Micro SD Card Test...\r\n");
		/* ����SD���Ƿ��������������ݴ���ģʽ�Ĵ���״̬�� */
		if(HAL_SD_GetCardState(&hsd) == HAL_SD_CARD_TRANSFER)
		{ 
					
		printf("Initialize SD card successfully!\r\n");
		// ��ӡSD����������
		printf(" SD card information! \r\n");
		printf(" CardCapacity : %llu \r\n", (unsigned long long)hsd.SdCard.BlockSize * hsd.SdCard.BlockNbr);// ��ʾ����
		printf(" CardBlockSize : %d \r\n", hsd.SdCard.BlockSize);   // �����
		printf(" LogBlockNbr : %d \r\n", hsd.SdCard.LogBlockNbr);	// �߼������Y
		printf(" LogBlockSize : %d \r\n", hsd.SdCard.LogBlockSize);// �߼������
		printf(" RCA : %d \r\n", hsd.SdCard.RelCardAdd);  // ����Ե؈}
		printf(" CardType : %d \r\n", hsd.SdCard.CardType);    // ������
		// ��ȡ����ӡSD����CID��Ϣ
		HAL_SD_CardCIDTypeDef sdcard_cid;
		HAL_SD_GetCardCID(&hsd,&sdcard_cid);
		printf(" ManufacturerID: %d \r\n",sdcard_cid.ManufacturerID);
		}
		else
		{ 

		printf("SD card init fail!\r\n" );
		}
#if 0
		/* ����SD���� */
		printf("------------------- Block Erase -------------------------------\r\n");
		if(HAL_SD_Erase(&hsd, BLOCK_START_ADDR, NUM_OF_BLOCKS) == HAL_OK)
		{ 

		/* Wait until SD cards are ready to use for new operation */
		while(HAL_SD_GetCardState(&hsd) != HAL_SD_CARD_TRANSFER)
		{ 

		}
		printf("\r\nErase Block Success!\r\n");
		}
		else
		{ 

		printf("\r\nErase Block Failed!\r\n");					
		}
#endif
#if 0
		/* ��仺�������� */
		memset(Buffer_Tx, 0x22, sizeof(Buffer_Tx));
		/* ��SD����д������ */
		printf("------------------- Write SD card block data Test ------------------\r\n");
		SDIO_WriteBlocks_DMA(&hsd,Buffer_Tx, BLOCK_START_ADDR, NUM_OF_BLOCKS);
		printf("write status :%d\r\n",Return_Status);
		/* ��ȡSD�������� */	
		Return_Status=SDIO_ReadBlocks_DMA(&hsd,Buffer_Rx, BLOCK_START_ADDR, NUM_OF_BLOCKS);
		printf("read status :%d\r\n",Return_Status);
		for(i = 0; i < sizeof(Buffer_Rx); i++)
		{ 

		printf("0x%02x:%02x ", i, Buffer_Rx[i]);
		}
#endif
}

void fs_test(void){
	#if 1  //����ϵͳ
  retSD = f_mount(&SDFatFS,"0:",1);
	switch(retSD)
	{
		case FR_NO_FILESYSTEM :   //���û���ļ�ϵͳ������и�ʽ��
		{
			retSD = f_mkfs("0:",0,0,rBuffer,sizeof(rBuffer));
			if(retSD != FR_OK )   //�����ʽ�����ɹ�������
			{
				printf("mkfs error %d\r\n",retSD);	
			}
		}
		break;
		case FR_OK :
		{
			printf("mount successful\r\n");
#if 0 //�����ļ���д����
			retSD = f_open(&file,"0:State.txt",FA_CREATE_ALWAYS | FA_WRITE);  //�жϴ�������ļ��Ƿ�ɹ�
			if(retSD == FR_OK)
			{
				printf("open successful\r\n");
				//retSD = f_write(&file,(const void *)State,sizeof(WBuffer),&bw);
				retSD = f_write(&file,(uint8_t *)WBuffer,sizeof(WBuffer),&bw);
				if(retSD == FR_OK)  //�ж�д�������Ƿ�ɹ�
				{
					printf("write successful\r\n");
					f_close(&file);   //�ر��ļ�
				}
				else
				{
					printf("write error %d\r\n",retSD);
				}
			}
			else
			{
				printf("open error %d\r\n",retSD);
			}
#endif
		}	
		break;
		default :
			printf("other error %d\r\n",retSD);
		break;
	}
#if 0   //��λ��ȡSD������
	retSD = f_open(&file,"0:Temperature_Probe_1.txt",FA_OPEN_EXISTING | FA_READ);
	if(retSD == FR_OK)
	{
		printf("open successful\r\n");
		retSD =  f_lseek(&file,f_tell(&file)+ 4); //�������������λ��f_tell�����ǻ�ȡ�ļ��׵�ַ�ĺ���
		if(retSD == FR_OK)
		{
			retSD = f_read(&file,(void *)rBuffer,6,&br);
			if(retSD == FR_OK)  //�ж϶�ȡ�ļ������Ƿ�ɹ�
			{
				printf("read successful\r\n");
				uint8_t j = 0;
				for(uint16_t i = 0;i < 2000;i++)  //��forѭ�����ڽ����������ݴ�ӡ������
				{
					j++;
					printf("%d ",rBuffer[i]);
					if(j == 10)
					{
						printf("\r\n");
						j = 0;
					}
				}
				f_close(&file);
			}
		}
		else
		{
			printf("open error %d\r\n",retSD);
		}
	}
#endif
#if 0  //��ȡSD��������
	retSD = f_open(&file,"0:State.txt",FA_OPEN_EXISTING | FA_READ);
	if(retSD == FR_OK)
	{
		printf("open successful\r\n");
		retSD = f_read(&file,(uint8_t *)rBuffer,sizeof(rBuffer),&br);
		if(retSD == FR_OK)
		{
			printf("read successful\r\n");
			uint8_t j = 0;
			for(uint16_t i = 0;i < 20;i++)
			{
				j++;
				printf("%d ",rBuffer[i]);
				if(j == 10)
				{
					printf("\r\n");
					j = 0;
				}
			}
			f_close(&file);
		}
		else
		{
			printf("read error %d\r\n",retSD);
		}
	}
	else
	{
		printf("open error %d\r\n",retSD);
	}
#endif
#endif

}

void W25QXX_test(void){
	POINT_COLOR=RED; 
	
	while(W25QXX_ReadID()!=W25Q16)								//��ⲻ��W25QXX
	{
		LCD_ShowString(30,150,200,16,16,RED,"W25Q16 Check Failed!");
		delay_ms(500);
		LCD_ShowString(30,150,200,16,16,RED,"Please Check!      ");
		delay_ms(500);
		HAL_GPIO_TogglePin(LED_ON_Board_GPIO_Port,LED_ON_Board_Pin);
	}
	LCD_ShowString(30,150,200,16,16,RED,"W25Q16 Ready!"); 
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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_FSMC_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_SDIO_SD_Init();
  MX_FATFS_Init();
  MX_ADC1_Init();
  MX_DAC_Init();
  /* USER CODE BEGIN 2 */
	
	
	SD_test();
	fs_test();
	delay_init(100);
	LCD_Init();
	W25QXX_Init();			//W25QXX��ʼ��
	W25QXX_test();
	
	GBK_Lib_Init();       //Ӳ��GBK�ֿ��ʼ��--(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ��ʼ���� 
	
	tp_dev.init();				//��������ʼ��
	
	LCD_Clear(WHITE);//�����Ļ
	
	//lvgl
	HAL_TIM_Base_Start_IT(&htim1); 
	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();
	lv_example_get_started_1();
	
	u16 adcx;
	float temp;
 	u8 t=0;	 
	u16 dacval=0;
	u8 key;	
	
	while(1)
	{
		t++;
		key=KEY_Scan(0);			  
		if(key==WKUP_PRES)
		{		 
			if(dacval<4000)dacval+=200;
			HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,dacval);//����DACֵ
		}else if(key==2)
		{
			if(dacval>200)dacval-=200;
			else dacval=0;
			HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,dacval);//����DACֵ
		}	 
		if(t==10||key==KEY1_PRES||key==WKUP_PRES) 	//WKUP/KEY1������,���߶�ʱʱ�䵽��
		{	  
			adcx = HAL_DAC_GetValue(&hdac,DAC_CHANNEL_1);
			LCD_ShowxNum(94,150,adcx,4,16,BLUE,0);     	   //��ʾDAC�Ĵ���ֵ
			temp=(float)adcx*(3.3/4096);			         //�õ�DAC��ѹֵ
			adcx=temp;
 			LCD_ShowxNum(94,170,temp,1,16,BLUE,0);     	   //��ʾ��ѹֵ��������
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(110,170,temp,3,16,BLUE,0X80); 	   //��ʾ��ѹֵ��С������
 			adcx=Get_Adc_Average(10);		//�õ�ADCת��ֵ	  
			temp=(float)adcx*(3.3/4096);			        //�õ�ADC��ѹֵ
			adcx=temp;
 			LCD_ShowxNum(94,190,temp,1,16,BLUE,0);     	  //��ʾ��ѹֵ��������
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(110,190,temp,3,16,BLUE,0X80); 	  //��ʾ��ѹֵ��С������
			//LED1=!LED1;	   
			t=0;
		}	    
		delay_ms(10);	 
	}	

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
  RCC_OscInitStruct.PLL.PLLQ = 9;
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

HAL_StatusTypeDef SDIO_ReadBlocks_DMA(SD_HandleTypeDef *hsd, uint8_t *pData, uint32_t BlockAdd, uint32_t NumberOfBlocks)
{ 

HAL_StatusTypeDef Return_Status;
HAL_SD_CardStateTypeDef SD_Card_Status;
do
{ 

SD_Card_Status = HAL_SD_GetCardState(hsd);
}while(SD_Card_Status != HAL_SD_CARD_TRANSFER );
/* SDIO DMA DeInit */
/* SDIO DeInit */
HAL_DMA_DeInit(&hdma_sdio);
/* SDIO DMA Init */
/* SDIO Init */
hdma_sdio.Instance = DMA2_Stream3;
hdma_sdio.Init.Direction = DMA_PERIPH_TO_MEMORY;
hdma_sdio.Init.PeriphInc = DMA_PINC_DISABLE;
hdma_sdio.Init.MemInc = DMA_MINC_ENABLE;
hdma_sdio.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
hdma_sdio.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
hdma_sdio.Init.Mode = DMA_NORMAL;
hdma_sdio.Init.Priority = DMA_PRIORITY_LOW;
if (HAL_DMA_Init(&hdma_sdio) != HAL_OK)
{ 

Error_Handler();
}
__HAL_LINKDMA( hsd,hdmarx,hdma_sdio);
Return_Status = HAL_SD_ReadBlocks_DMA( hsd,pData, BlockAdd, NumberOfBlocks);
return Return_Status;
}

HAL_StatusTypeDef SDIO_WriteBlocks_DMA(SD_HandleTypeDef *hsd, uint8_t *pData, uint32_t BlockAdd, uint32_t NumberOfBlocks)
{ 

HAL_StatusTypeDef Return_Status;
HAL_SD_CardStateTypeDef SD_Card_Status;
do
{ 

SD_Card_Status = HAL_SD_GetCardState(hsd);
}while(SD_Card_Status != HAL_SD_CARD_TRANSFER );
/* SDIO DMA DeInit */
/* SDIO DeInit */
HAL_DMA_DeInit(&hdma_sdio);
/* SDIO DMA Init */
/* SDIO Init */
hdma_sdio.Instance = DMA2_Stream3;
hdma_sdio.Init.Direction = DMA_MEMORY_TO_PERIPH;
hdma_sdio.Init.PeriphInc = DMA_PINC_DISABLE;
hdma_sdio.Init.MemInc = DMA_MINC_ENABLE;
hdma_sdio.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
hdma_sdio.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
hdma_sdio.Init.Mode = DMA_NORMAL;
hdma_sdio.Init.Priority = DMA_PRIORITY_LOW;
if (HAL_DMA_Init(&hdma_sdio) != HAL_OK)
{ 

Error_Handler();
}
__HAL_LINKDMA(hsd,hdmatx,hdma_sdio);	
Return_Status = HAL_SD_WriteBlocks_DMA(hsd,pData, BlockAdd, NumberOfBlocks);
return Return_Status;
}

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

int fputc(int ch, FILE *f)
{ 

HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
return ch;
}
/** * @brief �ض���c�⺯��getchar,scanf��USARTx * @retval None */
int fgetc(FILE *f)
{ 

uint8_t ch = 0;
HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
return ch;
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
