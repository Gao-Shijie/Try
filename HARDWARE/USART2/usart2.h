#ifndef __USART2_H
#define __USART2_H

#include "stdio.h"	
#include "sys.h" 


extern u16 Out_Buff;//����PM2.5���ݻ���
extern u8 Out_Printf[20];//��PM2.5�ļ����ֵͨ��sprintf������ӡ����������



void uart2_init(u32 bound);//����2��ʼ������

void USART2_Send_String(u8 *P);//����2�����ַ���
void USART2_Send_char(u8 ch);//�����ַ�
void SendCmd(u8 len);//���ڷ���һ֡����
void DoSum( u8 *Str, u8 len);//���У��
void Uart_SendCMD(u8 CMD ,u8 feedback , u16 dat);//�������ⷢ������[�������ƺͲ�ѯ]

#endif

