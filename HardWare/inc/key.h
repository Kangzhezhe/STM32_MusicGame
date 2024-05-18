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

//void KEY_Init(void);	//IO��ʼ��
u8 KEY_Scan(u8);  		//����ɨ�躯��	

#endif
