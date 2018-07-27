#ifndef __USART2_H
#define __USART2_H

#include "stdio.h"	
#include "sys.h" 


extern u16 Out_Buff;//接收PM2.5数据缓存
extern u8 Out_Printf[20];//将PM2.5的计算的值通过sprintf函数打印到此数组中



void uart2_init(u32 bound);//串口2初始化函数

void USART2_Send_String(u8 *P);//串口2发送字符串
void USART2_Send_char(u8 ch);//发送字符
void SendCmd(u8 len);//串口发送一帧数据
void DoSum( u8 *Str, u8 len);//求和校验
void Uart_SendCMD(u8 CMD ,u8 feedback , u16 dat);//串口向外发送命令[包括控制和查询]

#endif

