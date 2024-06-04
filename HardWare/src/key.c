#include "key.h"
#include "delay.h" 
//////////////////////////////////////////////////////////////////////////////////	 
 
//����������������	   
//STM32F4����-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com								  
////////////////////////////////////////////////////////////////////////////////// 	 

//������ʼ������
void KEY_Init(void)
{
	
//	GPIO_InitTypeDef  GPIO_InitStructure;

//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOA,GPIOBʱ��
//    
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9; //KEY1 KEY0 ��Ӧ����
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
//    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��PB8,PB9
//        
//        
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP��Ӧ����PA0
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
//    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA0
 
} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����

//4��WKUP���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1||C1==0||C2==0||C3==0||K1==0||K2==0||K3==0||K4==0||K5==0||K6==0||K7==0))
	{
		delay_ms(10);
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;
		//else if(KEY2==0)return 3;
		else if(WK_UP==1)return 4;
        else if(K1==0)return K1_PRES;
        else if(K2==0)return K2_PRES;
        else if(K3==0)return K3_PRES;
        else if(K4==0)return K4_PRES;
        else if(K5==0)return K5_PRES;
        else if(K6==0)return K6_PRES;
        else if(K7==0)return K7_PRES;
        else if(C1==0)return C1_PRES;
        else if(C2==0)return C2_PRES;
        else if(C3==0)return C3_PRES;
	}else if(~(KEY0==0||KEY1==0||WK_UP==1||C1==0||C2==0||C3==0||K1==0||K2==0||K3==0||K4==0||K5==0||K6==0||K7==0))key_up=1; 	    
 	return 0;// �ް�������
}




















