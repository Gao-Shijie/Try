#include "usart2.h"
#include "sys.h"
#include "stm32f10x.h"
#include "stdio.h"	
//#include "ESP8266.h"



u8 Send_buf[20];


u8 Buff[7]={0,0,0,0,0,0,0};
u16 Out_Buff;
u8 Out_Printf[20]={0};


u8 Res;

void uart2_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2,&USART_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART2,ENABLE);
	
}


void USART2_IRQHandler(void)
{
	static u8 aa = 0,i = 0;
	u8 Val;
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{
		Res=USART_ReceiveData(USART2);
		if(Res==0xaa)
			aa=0x80;
		if(aa==0x80)
			Buff[i++]=Res;
		if((i==7)&(Buff[6]==0xff))
		{
			i=0;
			aa=0;
			Val = Buff[1]+Buff[2]+Buff[3]+Buff[4];
			if(Val == Buff[5])
				Out_Buff = (Buff[1]<<8) + Buff[2];
		}
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}


void USART2_Send_String(u8 *P)//发送字符串
{
	
	while(*P)
	{
		USART_SendData(USART2,*P);
		while(!(USART_GetFlagStatus(USART2,USART_FLAG_TC)));
		USART_ClearFlag(USART2,USART_FLAG_TC);		
		P++;
	}
}



void USART2_Send_char(u8 ch)//发送字符
{
	
	
		USART_SendData(USART2,ch);
		while(!(USART_GetFlagStatus(USART2,USART_FLAG_TC)));
		USART_ClearFlag(USART2,USART_FLAG_TC);		
		
}

/*****************************************************************************************************
 - 功能描述： 串口发送一帧数据
 - 隶属模块： 内部 
 - 参数说明： 
 - 返回说明： 
 - 注：无     
*****************************************************************************************************/
void SendCmd(u8 len)
{
    u8 i = 0 ;

    USART2_Send_char(0x7E); //起始
    for(i=0; i<len; i++)//数据
    {
		USART2_Send_char(Send_buf[i]) ;
    }
    USART2_Send_char(0xEF) ;//结束
}

/********************************************************************************************
 - 功能描述：求和校验
 - 隶属模块：
 - 参数说明：
 - 返回说明：
 - 注：      和校验的思路如下
             发送的指令，去掉起始和结束。将中间的6个字节进行累加，最后取反码
             接收端就将接收到的一帧数据，去掉起始和结束。将中间的数据累加，再加上接收到的校验
             字节。刚好为0.这样就代表接收到的数据完全正确。
********************************************************************************************/
void DoSum( u8 *Str, u8 len)
{
    u16 xorsum = 0;
    u8 i;

    for(i=0; i<len; i++)
    {
        xorsum  = xorsum + Str[i];
    }
	xorsum     = 0 -xorsum;
	*(Str+i)   = (u8)(xorsum >>8);
	*(Str+i+1) = (u8)(xorsum & 0x00ff);
}


/********************************************************************************************
 - 功能描述： 串口向外发送命令[包括控制和查询]
 - 隶属模块： 外部
 - 参数说明： CMD:表示控制指令，请查阅指令表，还包括查询的相关指令
              feedback:是否需要应答[0:不需要应答，1:需要应答]
              data:传送的参数
 - 返回说明：
 - 注：       
********************************************************************************************/




void Uart_SendCMD(u8 CMD ,u8 feedback , u16 dat)
{
    Send_buf[0] = 0xff;    //保留字节 
    Send_buf[1] = 0x06;    //长度
    Send_buf[2] = CMD;     //控制指令
    Send_buf[3] = feedback;//是否需要反馈
    Send_buf[4] = (u8)(dat >> 8);//datah
    Send_buf[5] = (u8)(dat);     //datal
    DoSum(&Send_buf[0],6);        //校验
    SendCmd(8);        //发送此帧数据
}



