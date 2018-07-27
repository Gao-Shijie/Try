#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "esp8266.h"
#include "string.h"
#include "usart2.h"

char *Equipment_id = "5570";//主机设备ID
char *Data_id = "5021" ;//主机数据接口ID

 	
int main(void)
{	 
	u8 i=0;
	float j=0;
	
//	u8 lcd_id[12];			//存放LCD ID字符串
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	
	
	uart_init(115200);	 	//串口初始化为115200
	uart2_init(9600);
	
	ESP8266_Init();
	checkin();
	update1(Equipment_id,Data_id,123); 
	LCD_Init();
	LCD_Clear(BLACK);//修改背景色
	POINT_COLOR=GREEN;	 //修改画笔颜色 
	
	delay_ms(1000);
	
	Uart_SendCMD(0x03 , 0 , 0x02);//播放开启文件
	 
	delay_ms(300);
	
	Uart_SendCMD(0x03 , 0 , 0x02);//播放开启文件
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	
	LCD_ShowString(0,0,210,24,24,"PM2.5:"); 
	LCD_ShowString(0,24,200,24,24,"T&H: ");
	LCD_ShowString(0,48,200,24,24,"Lux: ");
	LCD_ShowString(0,72,200,24,24,"CH4: ");		//显示LCD ID
	LCD_ShowString(0,96,200,24,24,"BP: ");
	LCD_ShowString(0,120,200,24,24,"BPM: ");
	LCD_ShowString(0,144,200,24,24,"KWh: ");
	LCD_ShowString(0,168,200,24,24,"Water: ");
	LCD_ShowString(0,192,200,24,24,"DOOR: ");
	LCD_ShowString(0,216,200,24,24,"Windows: ");
	
	LCD_ShowString(0,280,200,24,24,"2018 /6/3"); 
	 
	
	
	
  	while(1) 
	{	
		i++;
		
		WiFi_Jm(USART_RX_BUF,&USART_RX_STA);//接收处理函数
		
		if(i == 30)
		{
			j++;
			update1(Equipment_id,Data_id,j);//不间断向云端发送数据以掉线
			i=0;
		}
		
		if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5731")))//PM2.5检测
		{
			LCD_ShowString(80,0,200,24,24,ID_JM[7]);
			
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5763")))//温湿度检测
		{
			if((!strcmp((char*)ID_JM[11],"T")))
				LCD_ShowString(60,24,200,24,24,ID_JM[7]);
			else if((!strcmp((char*)ID_JM[11],"H")))
				LCD_ShowString(160,24,200,24,24,ID_JM[7]);
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5764")))//环境亮度检测
		{
			if((!strcmp((char*)ID_JM[11],"L")))
				LCD_ShowString(60,48,200,24,24,ID_JM[7]);
			
			if((strcmp((char*)ID_JM[7],"10"))<0)
			{
				Uart_SendCMD(0x03 , 0 , 0x03);//播放亮度播报
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
			}
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5850")))//甲烷检测
		{
			
			LCD_ShowString(60,72,200,24,24,ID_JM[7]);
			
			if(!(strcmp((char*)ID_JM[7],"Warning")))
			{
				Uart_SendCMD(0x03 , 0 , 0x06);//播放天然气泄漏播报
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
			}
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5851")))//体征检测
		{
			if((!strcmp((char*)ID_JM[11],"GXY")))
				LCD_ShowString(40,96,200,24,24,ID_JM[7]);
			else if((!strcmp((char*)ID_JM[11],"DXY")))
				LCD_ShowString(140,96,200,24,24,ID_JM[7]);
			else if((!strcmp((char*)ID_JM[11],"XL")))
				LCD_ShowString(60,120,200,24,24,ID_JM[7]);
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5883")))//用电量检测
		{
			LCD_ShowString(60,144,200,24,24,ID_JM[7]);
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5899")))//漏水模组
		{
			LCD_ShowString(80,168,200,24,24,ID_JM[7]);
			
			if(!(strcmp((char*)ID_JM[7],"WARING")))
			{
				Uart_SendCMD(0x03 , 0 , 0x04);//播放漏水播报
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
			}
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5904")))//门开启检测
		{
			LCD_ShowString(80,192,200,24,24,ID_JM[7]);
			
			if(!(strcmp((char*)ID_JM[7],"WARING")))
			{
				Uart_SendCMD(0x03 , 0 , 0x05);//播放门开启播报
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
			}
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5905")))//窗户开启检测
		{
			LCD_ShowString(95,216,200,24,24,ID_JM[7]);
			
			if(!(strcmp((char*)ID_JM[7],"WARING")))
			{
				Uart_SendCMD(0x03 , 0 , 0x01);//播放窗开启播报
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
			}
		}
		
		delay_ms(100);

	} 
}
 




//		switch(x)
//		{
//			case 0:LCD_Clear(WHITE);break;
//			case 1:LCD_Clear(BLACK);break;
//			case 2:LCD_Clear(BLUE);break;
//			case 3:LCD_Clear(RED);break;
//			case 4:LCD_Clear(MAGENTA);break;      //紫色
//			case 5:LCD_Clear(GREEN);break;        //青色
//			case 6:LCD_Clear(CYAN);break;
//			case 7:LCD_Clear(YELLOW);break;
//			case 8:LCD_Clear(BRRED);break;
//			case 9:LCD_Clear(GRAY);break;
//			case 10:LCD_Clear(LGRAY);break;
//			case 11:LCD_Clear(BROWN);break;
			//WHITE	BLACK	BLUE		
//		}




