#ifndef __ESP8266_H
#define __ESP8266_H

#include "sys.h"


extern u8 ID_JM[14][20];

void ESP8266_Init(void);//WIFI模块初始化
void checkin(void);/*发送登录信息*/
void checkout(void);/*退出登录*/
void check_status(void);/*检查当前登录状态*/
void say(char *toID, char *content);/*发送指令到目标单位*/
void update1(char *did, char *inputid, float value);/*上传一个接口的实时数据*/
void update2(char *did, char *inputid1,char *inputid2, float value1,float value2);/*上传二个接口的实时数据*/
u8 WiFi_Jm(u8* RX_BUF,u16* RX_STA);//解析单片机收到esp8266的信息   




#endif

