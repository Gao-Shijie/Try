#include "usart.h"
#include "esp8266.h"
#include "delay.h"
#include "stdio.h"

//------------------------------------------//

char  *WIFI_ID = "CMCC-SIAS1";//需要连接WIFI的名字
char  *WIFI_Passward ="56565656";//需要连接WIFI的密码

char *DEVICEID = "5570";//连接云端设备ID
char *APIKEY = "cb8b2b7d0";// 连接云端设备密码

//char *did = "5570";//连接云端设备ID
//char	*inputid = "5021";//数据接口ID
//char	*value = "555";//自定义数字

//------------------------------------------//

void ESP8266_Init(void)
{
	checkout();//登出8266，防止其之前在线
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
	
	
	printf("ATE0\r\n");//关闭命令回显
	delay_ms(1000);
	
	printf("AT+CWMODE=1\r\n");//设置WiFi应用模式为Station
	delay_ms(1000);
	delay_ms(1000);
	//连接到无线路由器 AT+CWJAP="FAST_SXM","lcx123456"\r\n
	printf("AT+CWJAP=\"%s\",\"%s\"\r\n",WIFI_ID,WIFI_Passward);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	
	
	//连接贝壳物联服务器
	printf("AT+CIPSTART=\"TCP\",\"www.bigiot.net\",8181\r\n");
	delay_ms(1000);//6000
	delay_ms(1000);
	
	 //设置模块传输模式为透传模式
	printf("AT+CIPMODE=1\r\n");
	delay_ms(1000);//3000
	delay_ms(1000);
	//进入透传模式
	printf("AT+CIPSEND\r\n");
	delay_ms(1000);//3000
	printf("+++");
	delay_ms(600);//6000
	printf("\r\n");
	delay_ms(1000);//4000
	//退出透传模式，重启
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

/*发送登录信息*/
void checkin(void)
{
    printf("{\"M\":\"checkin\",\"ID\":\"%s\",\"K\":\"%s\"}\n", DEVICEID, APIKEY);
}
/*退出登录*/
void checkout(void)
{
    printf("{\"M\":\"checkout\",\"ID\":\"%s\",\"K\":\"%s\"}\n", DEVICEID, APIKEY);
}
/*检查当前登录状态*/
void check_status(void)
{
    printf("{\"M\":\"status\"}\n");
}
/*发送指令到目标单位*/
void say(char *toID, char *content)
{
    printf("{\"M\":\"say\",\"ID\":\"%s\",\"C\":\"%s\"}\n", toID, content);
}
/*上传一个接口的实时数据*/
void update1(char *did, char *inputid, float value) 
{
    printf("{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%f\"}}\n", did, inputid, value);
}
/*上传二个接口的实时数据*/
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



