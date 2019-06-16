#include "sys.h"
#include "usart4.h"	
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos 使用	  
#endif


//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
/* u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节. */
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
/* u16 USART_RX_STA=0;       //接收状态标记	 */

//初始化IO 串口1 
//bound:波特率
void uart4_init(u32 bound){
     			GPIO_InitTypeDef GPIO_InitStructure;        
			NVIC_InitTypeDef NVIC_InitStructure;        
			USART_InitTypeDef USART_InitStructure;
			
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); 
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);

			
			GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); 
			GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); 
			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOC6  GPIOC7 
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         //50MHz 
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
			
			GPIO_Init(GPIOC,&GPIO_InitStructure); // PC6 PC7         //USART6         
			
			USART_InitStructure.USART_BaudRate = 57600;
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;
			USART_InitStructure.USART_StopBits = USART_StopBits_1;
			USART_InitStructure.USART_Parity = USART_Parity_No; 
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			
			USART_Init(UART4, &USART_InitStructure); 
			
			USART_Cmd(UART4, ENABLE); 
			USART_ClearFlag(UART4, USART_FLAG_TC); 
			USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
			
			
			NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =2;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;                         
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                 
			NVIC_Init(&NVIC_InitStructure); 

}

void Uart4SendData(uint8_t *pdata, uint8_t len)
{
    uint8_t i;
    for(i=0;i<len;i++)
    {
        USART_SendData(UART4, pdata[i]);
        while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
    }
}

extern void SendUartData(uint16_t data);
void UART4_IRQHandler(void)                	//串口1中断服务程序
{
//    uint16_t Res;
    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //接收中断
    {
        USART_ClearITPendingBit(UART4,USART_IT_RXNE); 
//        Res = USART_ReceiveData(UART4);//(USART1->DR);	//读取接收到的数据
//				printf("0x%x ",Res);			
			  SendUartData( USART_ReceiveData(UART4) );

    } 
} 

