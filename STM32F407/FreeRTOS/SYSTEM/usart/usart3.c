#include "sys.h"
#include "usart3.h"
#include "string.h"
#include "..\ESP8266\common.h"

void uart3_init(u32 bound) {
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);

    USART_Cmd(USART3, ENABLE);

    //USART_ClearFlag(USART1, USART_FLAG_TC);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
u8 uart3_sta=0;
u8 uart3_cnt=0;
u8 uart3_buf[200]= {0};
void USART3_IRQHandler(void)
{
    u8 ch;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
    OSIntEnter();
#endif
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        ch =USART_ReceiveData(USART3);
        USART2->DR = ch;
        uart3_buf[uart3_cnt] = ch;
        uart3_cnt++;
    }
    else if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
    {
        ch=USART3->SR;
        ch=USART3->DR;
        uart3_buf[uart3_cnt] = '\0';
        uart3_cnt=0;
        uart3_sta=1;
        string_deal(uart3_buf);
    }

#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
    OSIntExit();
#endif
}

void uart3_send(u8 *ch)
{
    u8 i,num;
    num=strlen((const char *)ch);
    for(i=0; i<num; i++)
    {
        while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
        USART3->DR = *ch;
        ch++;
    }
    while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
    USART3->DR = '\r';
    while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
    USART3->DR = '\n';
}




