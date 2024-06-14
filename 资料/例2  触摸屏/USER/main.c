#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"  

#include "w25qxx.h"
#include "touch.h"
#include "GBK_LibDrive.h"	
 
 
/************************************************************************/

//触摸屏实验   --库函数版本
//STM32F4工程-库函数版本
//淘宝店铺：http://mcudev.taobao.com
 
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/************************************************************************/



//清空屏幕并在右上角显示"RST"
void Load_Drow_Dialog(void)
{
	GBK_LibFont_Test();//字库显示测试
//	LCD_Clear(WHITE);	//清屏   
 	POINT_COLOR=RED;	//设置字体为蓝色 
	LCD_ShowString(lcddev.width-24,0,200,16,16,RED,"RST");//显示清屏区域
  POINT_COLOR=RED;	//设置画笔蓝色 
	
}



/************************************************************************/

//电阻触摸屏测试函数
 
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/************************************************************************/


void rtp_test(void)
{
	u8 key;
	u8 i=0;	  
	while(1)
	{
		
	 	key=KEY_Scan(0);
		
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
		
		if(key==KEY0_PRES)	//KEY0按下,则执行校准程序
		{
			LCD_Clear(WHITE);  //清屏
		  TP_Adjust();  	   //屏幕校准  
			Load_Drow_Dialog();
		}
		
		i++;
		if(i%20==0)
		{
		  LED1=!LED1;//LED灯闪，指示系统在运行
		}
		
	}
}




/************************************************************************/

//电阻触摸屏测试
 
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/************************************************************************/

	
int main(void)
{ 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	
	LED_Init();					//初始化LED 
 	LCD_Init();					//LCD初始化 
	KEY_Init(); 				//按键初始化  
	
	
	W25QXX_Init();			//W25QXX初始化
	
  POINT_COLOR=RED; 
	
	while(W25QXX_ReadID()!=W25Q16)								//检测不到W25QXX
	{
		LCD_ShowString(30,150,200,16,16,RED,"W25Q16 Check Failed!");
		delay_ms(500);
		LCD_ShowString(30,150,200,16,16,RED,"Please Check!      ");
		delay_ms(500);
		LED1=!LED1;		//DS0闪烁
	}
	LCD_ShowString(30,150,200,16,16,RED,"W25Q16 Ready!"); 
	
	GBK_Lib_Init();       //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化） 
	
	tp_dev.init();				//触摸屏初始化
 	
	LCD_Clear(WHITE);//清除屏幕
	
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




















/************************************************************************/

//电阻触摸屏测试
 
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/************************************************************************/

