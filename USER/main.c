#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "esp8266.h"
#include "string.h"
#include "usart2.h"

char *Equipment_id = "5570";//�����豸ID
char *Data_id = "5021" ;//�������ݽӿ�ID

 	
int main(void)
{	 
	u8 i=0;
	float j=0;
	
//	u8 lcd_id[12];			//���LCD ID�ַ���
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	uart2_init(9600);
	
	ESP8266_Init();
	checkin();
	update1(Equipment_id,Data_id,123); 
	LCD_Init();
	LCD_Clear(BLACK);//�޸ı���ɫ
	POINT_COLOR=GREEN;	 //�޸Ļ�����ɫ 
	
	delay_ms(1000);
	
	Uart_SendCMD(0x03 , 0 , 0x02);//���ſ����ļ�
	 
	delay_ms(300);
	
	Uart_SendCMD(0x03 , 0 , 0x02);//���ſ����ļ�
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	
	LCD_ShowString(0,0,210,24,24,"PM2.5:"); 
	LCD_ShowString(0,24,200,24,24,"T&H: ");
	LCD_ShowString(0,48,200,24,24,"Lux: ");
	LCD_ShowString(0,72,200,24,24,"CH4: ");		//��ʾLCD ID
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
		
		WiFi_Jm(USART_RX_BUF,&USART_RX_STA);//���մ�����
		
		if(i == 30)
		{
			j++;
			update1(Equipment_id,Data_id,j);//��������ƶ˷��������Ե���
			i=0;
		}
		
		if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5731")))//PM2.5���
		{
			LCD_ShowString(80,0,200,24,24,ID_JM[7]);
			
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5763")))//��ʪ�ȼ��
		{
			if((!strcmp((char*)ID_JM[11],"T")))
				LCD_ShowString(60,24,200,24,24,ID_JM[7]);
			else if((!strcmp((char*)ID_JM[11],"H")))
				LCD_ShowString(160,24,200,24,24,ID_JM[7]);
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5764")))//�������ȼ��
		{
			if((!strcmp((char*)ID_JM[11],"L")))
				LCD_ShowString(60,48,200,24,24,ID_JM[7]);
			
			if((strcmp((char*)ID_JM[7],"10"))<0)
			{
				Uart_SendCMD(0x03 , 0 , 0x03);//�������Ȳ���
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
			}
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5850")))//������
		{
			
			LCD_ShowString(60,72,200,24,24,ID_JM[7]);
			
			if(!(strcmp((char*)ID_JM[7],"Warning")))
			{
				Uart_SendCMD(0x03 , 0 , 0x06);//������Ȼ��й©����
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
			}
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5851")))//�������
		{
			if((!strcmp((char*)ID_JM[11],"GXY")))
				LCD_ShowString(40,96,200,24,24,ID_JM[7]);
			else if((!strcmp((char*)ID_JM[11],"DXY")))
				LCD_ShowString(140,96,200,24,24,ID_JM[7]);
			else if((!strcmp((char*)ID_JM[11],"XL")))
				LCD_ShowString(60,120,200,24,24,ID_JM[7]);
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5883")))//�õ������
		{
			LCD_ShowString(60,144,200,24,24,ID_JM[7]);
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5899")))//©ˮģ��
		{
			LCD_ShowString(80,168,200,24,24,ID_JM[7]);
			
			if(!(strcmp((char*)ID_JM[7],"WARING")))
			{
				Uart_SendCMD(0x03 , 0 , 0x04);//����©ˮ����
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
			}
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5904")))//�ſ������
		{
			LCD_ShowString(80,192,200,24,24,ID_JM[7]);
			
			if(!(strcmp((char*)ID_JM[7],"WARING")))
			{
				Uart_SendCMD(0x03 , 0 , 0x05);//�����ſ�������
				delay_ms(1000);
				delay_ms(1000);
				delay_ms(1000);
			}
		}
		else if((!strcmp((char*)ID_JM[1],"say"))&&(!strcmp((char*)ID_JM[3],"D5905")))//�����������
		{
			LCD_ShowString(95,216,200,24,24,ID_JM[7]);
			
			if(!(strcmp((char*)ID_JM[7],"WARING")))
			{
				Uart_SendCMD(0x03 , 0 , 0x01);//���Ŵ���������
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
//			case 4:LCD_Clear(MAGENTA);break;      //��ɫ
//			case 5:LCD_Clear(GREEN);break;        //��ɫ
//			case 6:LCD_Clear(CYAN);break;
//			case 7:LCD_Clear(YELLOW);break;
//			case 8:LCD_Clear(BRRED);break;
//			case 9:LCD_Clear(GRAY);break;
//			case 10:LCD_Clear(LGRAY);break;
//			case 11:LCD_Clear(BROWN);break;
			//WHITE	BLACK	BLUE		
//		}




