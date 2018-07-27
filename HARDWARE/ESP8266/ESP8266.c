#include "usart.h"
#include "esp8266.h"
#include "delay.h"
#include "stdio.h"

//------------------------------------------//

char  *WIFI_ID = "CMCC-SIAS1";//��Ҫ����WIFI������
char  *WIFI_Passward ="56565656";//��Ҫ����WIFI������

char *DEVICEID = "5570";//�����ƶ��豸ID
char *APIKEY = "cb8b2b7d0";// �����ƶ��豸����

//char *did = "5570";//�����ƶ��豸ID
//char	*inputid = "5021";//���ݽӿ�ID
//char	*value = "555";//�Զ�������

//------------------------------------------//

void ESP8266_Init(void)
{
	checkout();//�ǳ�8266����ֹ��֮ǰ����
	delay_ms(1000);
	delay_ms(1000);
	
	printf("+++");
	delay_ms(1000);
	printf("+++");
	delay_ms(1000);
	printf("+++");
	delay_ms(1000);
	
	printf("AT\r\n");
	delay_ms(1000);
	
	
	printf("ATE0\r\n");//�ر��������
	delay_ms(1000);
	
	printf("AT+CWMODE=1\r\n");//����WiFiӦ��ģʽΪStation
	delay_ms(1000);
	delay_ms(1000);
	//���ӵ�����·���� AT+CWJAP="FAST_SXM","lcx123456"\r\n
	printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI_ID,WIFI_Passward);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	
	
	//���ӱ�������������
	printf("AT+CIPSTART=\"TCP\",\"www.bigiot.net\",8181\r\n");
	delay_ms(1000);//6000
	delay_ms(1000);
	
	 //����ģ�鴫��ģʽΪ͸��ģʽ
	printf("AT+CIPMODE=1\r\n");
	delay_ms(1000);//3000
	delay_ms(1000);
	//����͸��ģʽ
	printf("AT+CIPSEND\r\n");
	delay_ms(1000);//3000
	printf("+++");
	delay_ms(600);//6000
	printf("\r\n");
	delay_ms(1000);//4000
	//�˳�͸��ģʽ������
	printf("AT+RST\r\n");
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);

//	USART3_Send_String("{\"M\":\"checkin\",\"ID\":\"5570\",\"K\":\"cb8b2b7d0\"}\r\n");
//	delay_ms(1000);
//	delay_ms(1000);
//	delay_ms(1000);
//	delay_ms(1000);
//	USART3_Send_String("{\"M\":\"update\",\"ID\":\"5570\",\"V\":{\"5021\":\"55555\"}}\r\n");
}

/*���͵�¼��Ϣ*/
void checkin(void)
{
    printf("{\"M\":\"checkin\",\"ID\":\"%s\",\"K\":\"%s\"}\n", DEVICEID, APIKEY);
}
/*�˳���¼*/
void checkout(void)
{
    printf("{\"M\":\"checkout\",\"ID\":\"%s\",\"K\":\"%s\"}\n", DEVICEID, APIKEY);
}
/*��鵱ǰ��¼״̬*/
void check_status(void)
{
    printf("{\"M\":\"status\"}\n");
}
/*����ָ�Ŀ�굥λ*/
void say(char *toID, char *content)
{
    printf("{\"M\":\"say\",\"ID\":\"%s\",\"C\":\"%s\"}\n", toID, content);
}
/*�ϴ�һ���ӿڵ�ʵʱ����*/
void update1(char *did, char *inputid, float value) 
{
    printf("{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%f\"}}\n", did, inputid, value);
}
/*�ϴ������ӿڵ�ʵʱ����*/
void update2(char *did, char *inputid1,char *inputid2, float value1,float value2) 
{
    printf("{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%.2f\",\"%s\":\"%.2f\"}}\n", did, inputid1, value1,inputid2,value2);
}



u8 ID_JM[14][20];

u8 WiFi_Jm(u8* RX_BUF,u16* RX_STA)
{
    u8 WiFi_i = 0,j = 0;
    if(*RX_STA&0x8000)
    {
        while(*(++RX_BUF)!='}')
        {
            while(*(RX_BUF++) != '\"');
            WiFi_i = 0;
            do
            {
                ID_JM[j][WiFi_i++] = *RX_BUF;
            }
            while(*(++RX_BUF) != '\"');
			ID_JM[j][WiFi_i++] ='\0';
			j++;
        }
		*RX_STA = 0;
        return j;
    }
	return 0;
}



