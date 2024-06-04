#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
#include "main.h"
//////////////////////////////////////////////////////////////////////////////////	 
 
//����������������	   
//STM32F4����-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com								  
////////////////////////////////////////////////////////////////////////////////// 	 

/*����ķ�ʽ��ͨ��ֱ�Ӳ����⺯����ʽ��ȡIO*/

#define KEY0 		HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9) //PE4
#define KEY1 		HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)	//PE3 
//#define KEY2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) //PE2
#define WK_UP 	HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)	//PA0

#define C1      HAL_GPIO_ReadPin(C1_GPIO_Port,C1_Pin)
#define C2      HAL_GPIO_ReadPin(C2_GPIO_Port,C2_Pin)
#define C3      HAL_GPIO_ReadPin(C3_GPIO_Port,C3_Pin)
#define K1      HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin)
#define K2      HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)
#define K3      HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)
#define K4      HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)
#define K5      HAL_GPIO_ReadPin(K5_GPIO_Port,K5_Pin)
#define K6      HAL_GPIO_ReadPin(K6_GPIO_Port,K6_Pin)
#define K7      HAL_GPIO_ReadPin(K7_GPIO_Port,K7_Pin)


/*���淽ʽ��ͨ��λ��������ʽ��ȡIO*/
/*
#define KEY0 		PEin(4)   	//PE4
#define KEY1 		PEin(3)		//PE3 
#define KEY2 		PEin(2)		//P32
#define WK_UP 	PAin(0)		//PA0
*/


#define KEY0_PRES 	1
#define KEY1_PRES	2
#define KEY2_PRES	3
#define WKUP_PRES   4

#define K1_PRES 5
#define K2_PRES 6
#define K3_PRES 7
#define K4_PRES 8
#define K5_PRES 9
#define K6_PRES 10
#define K7_PRES 11
#define C1_PRES 12
#define C2_PRES 13
#define C3_PRES 14



//void KEY_Init(void);	//IO��ʼ��
u8 KEY_Scan(u8);  		//����ɨ�躯��	

#endif
