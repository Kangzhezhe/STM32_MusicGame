/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lv_port_disp.h"
#include "lvgl.h"
#include "lv_port_indev.h"
#include "lv_port_fs.h"
 #include "mp3Player.h"
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask_LEDHandle;
osThreadId myTask_lvglHandle;
osThreadId myTask_mp3Handle;
osThreadId start_taskHandle;
osSemaphoreId mutex_lvglHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartTaskLED(void const * argument);
void StartTask_lvgl(void const * argument);
void StartTask_mp3(void const * argument);
void StartTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */
void vApplicationTickHook(void);

/* USER CODE BEGIN 3 */
__weak void vApplicationTickHook( void )
{
   /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */
	lv_tick_inc(1);
}
/* USER CODE END 3 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of mutex_lvgl */
  osSemaphoreDef(mutex_lvgl);
  mutex_lvglHandle = osSemaphoreCreate(osSemaphore(mutex_lvgl), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask_LED */
  osThreadDef(myTask_LED, StartTaskLED, osPriorityIdle, 0, 128);
  myTask_LEDHandle = osThreadCreate(osThread(myTask_LED), NULL);

  /* definition and creation of myTask_lvgl */
  osThreadDef(myTask_lvgl, StartTask_lvgl, osPriorityIdle, 0, 2048);
  myTask_lvglHandle = osThreadCreate(osThread(myTask_lvgl), NULL);

  /* definition and creation of myTask_mp3 */
  osThreadDef(myTask_mp3, StartTask_mp3, osPriorityIdle, 0, 128);
  myTask_mp3Handle = osThreadCreate(osThread(myTask_mp3), NULL);

  /* definition and creation of start_task */
  osThreadDef(start_task, StartTask, osPriorityIdle, 0, 512);
  start_taskHandle = osThreadCreate(osThread(start_task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    vTaskDelay(1);
		//lv_tick_inc(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTaskLED */
/**
* @brief Function implementing the myTask_LED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskLED */
void StartTaskLED(void const * argument)
{
  /* USER CODE BEGIN StartTaskLED */
  /* Infinite loop */
  for(;;)
  {
    vTaskDelay(100);
		HAL_GPIO_TogglePin(LED_ON_Board_GPIO_Port,LED_ON_Board_Pin);
		
  }
  /* USER CODE END StartTaskLED */
}

/* USER CODE BEGIN Header_StartTask_lvgl */
/**
* @brief Function implementing the myTask_lvgl thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_lvgl */
void StartTask_lvgl(void const * argument)
{
  /* USER CODE BEGIN StartTask_lvgl */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
    if(pdTRUE == xSemaphoreTake(mutex_lvglHandle,portMAX_DELAY))    
    {
            lv_timer_handler();        
            xSemaphoreGive(mutex_lvglHandle);
    }
  }
  /* USER CODE END StartTask_lvgl */
}

/* USER CODE BEGIN Header_StartTask_mp3 */
/**
* @brief Function implementing the myTask_mp3 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_mp3 */
void StartTask_mp3(void const * argument)
{
  /* USER CODE BEGIN StartTask_mp3 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
		//mp3PlayerDemo("0:/æ–?æ¡¥æ®‹é›?.MP3");
  }
  /* USER CODE END StartTask_mp3 */
}

/* USER CODE BEGIN Header_StartTask */
/**
* @brief Function implementing the start_task thread.
* @param argument: Not used
* @retval None
*/
void SD_test(void);
void fs_test(void);
u8 scan_files(u8 * path);
#include "fatfs.h"
#include <stdio.h>
void test_fs_read(void) {
    lv_fs_file_t f;
		lv_fs_res_t res;
	res = lv_fs_open(&f, "A:/State.txt", LV_FS_MODE_RD);
	if(res != LV_FS_RES_OK) printf("open err :%d\r\n",res);

		uint32_t read_num;
		u16 buf[20];
		res = lv_fs_read(&f, buf, 40, &read_num);
		if(res != LV_FS_RES_OK || read_num != 40)  printf("read err");
		for (int i=0;i<20;i++){
			printf("%d ",buf[i]);
		}
		lv_fs_close(&f);
}

void test_print_directory_files(const char *path) {
    lv_fs_dir_t dir;
    lv_fs_res_t res = lv_fs_dir_open(&dir, path);
    if (res != LV_FS_RES_OK) {
        printf("Failed to open directory\n");
        return;
    }
    while (true) {
        char fn[256];
        lv_fs_res_t res = lv_fs_dir_read(&dir, fn,256);
        if (res != LV_FS_RES_OK||fn[0] == 0) {
            break;
        }
        printf("%s\r\n", fn);
    }

    lv_fs_dir_close(&dir);
}

void my_piano(void);
#include "lcd.h"
/* USER CODE END Header_StartTask */
void StartTask(void const * argument)
{
  /* USER CODE BEGIN StartTask */
  lv_port_fs_init();
  SD_test();
	my_piano();
    test_print_directory_files("A:/");
	//fs_test();
	// scan_files("0:");
	// mp3PlayerDemo("0:/¶ÏÇÅ²ÐÑ©.MP3");
	
	
	
	vTaskDelete(start_taskHandle);
  /* USER CODE END StartTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
