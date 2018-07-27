#ifndef __ESP8266_H
#define __ESP8266_H

#include "sys.h"


extern u8 ID_JM[14][20];

void ESP8266_Init(void);//WIFIģ���ʼ��
void checkin(void);/*���͵�¼��Ϣ*/
void checkout(void);/*�˳���¼*/
void check_status(void);/*��鵱ǰ��¼״̬*/
void say(char *toID, char *content);/*����ָ�Ŀ�굥λ*/
void update1(char *did, char *inputid, float value);/*�ϴ�һ���ӿڵ�ʵʱ����*/
void update2(char *did, char *inputid1,char *inputid2, float value1,float value2);/*�ϴ������ӿڵ�ʵʱ����*/
u8 WiFi_Jm(u8* RX_BUF,u16* RX_STA);//������Ƭ���յ�esp8266����Ϣ   




#endif

