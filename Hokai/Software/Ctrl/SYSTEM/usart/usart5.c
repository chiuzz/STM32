#include "sys.h"
#include "usart5.h"	
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos 使用	  
#endif



//初始化IO 串口5
//bound:波特率
void uart5_init(u32 bound){
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//使能USART1时钟

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOC时钟
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //上拉
		GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化GPIOB11，和GPIOB10

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //使能GPIOA时钟
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //上拉
		GPIO_Init(GPIOD,&GPIO_InitStructure); //初始化GPIOB11，和GPIOB10

		GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5); //GPIOB11复用为USART5
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5); //GPIOB10复用为USART5	
		
    //USART1 初始化设置
    USART_InitStructure.USART_BaudRate = bound;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(UART5, &USART_InitStructure); //初始化串口1

    USART_Cmd(UART5, ENABLE);  //使能串口1 

    USART_ClearFlag(UART5, USART_FLAG_TC);

    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启相关中断

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;//串口5中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

}


void Uart5SendData(uint8_t *pdata, uint8_t len)
{
    uint8_t i;
    for(i=0;i<len;i++)
    {
			USART_SendData(UART5, pdata[i]);
			while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);
    }
}


u8 USART5_TxBuffer[pagedataLen_TX]={0};
u8 USART5_RxBuffer[pagedataLen_RX]={0};
u8 MSG_RxBuffer[MSG_DataLen_RX]		={0};

u8 MSG_RX_START_FLAG=0;	
u8 MSG_RX_END_FLAG=0;		
u8 MSG_Rx_CNT=0;			 
u8 USART5_Rx=0;			  	
u8 USART5_RX_Flag=0;	  
u8 USART5_TX_Flag=0;	


void UART5_IRQHandler(void)                	//串口5中断服务程序
{
	
    if(USART_GetITStatus(UART5,USART_IT_RXNE) != RESET)
		{
			USART_ClearITPendingBit(USART2,USART_IT_RXNE);			
			USART5_RxBuffer[USART5_Rx++]=USART_ReceiveData(USART2);

			
			if(	(USART5_RxBuffer[USART5_Rx-0] == 0x90) && (USART5_RxBuffer[USART5_Rx-1] == 0xEB)	&&
					(USART5_RxBuffer[USART5_Rx-2] == 0x90) && (USART5_RxBuffer[USART5_Rx-3] == 0xEB))	
			{
				MSG_RX_START_FLAG++;
				MSG_Rx_CNT=0;
			}		
			if(MSG_RX_START_FLAG == 1)
			{
				MSG_RxBuffer[MSG_Rx_CNT++]=USART_ReceiveData(UART5);
				if((MSG_RxBuffer[MSG_Rx_CNT-1] == 0x0A) && (MSG_RxBuffer[MSG_Rx_CNT-2] == 0x0D))
				{
					MSG_RX_END_FLAG++;
					MSG_RX_START_FLAG=0;
				}
			}					
			if(USART5_Rx >= pagedataLen_RX)		USART5_Rx =0;			
			if(USART5_Rx >= MSG_DataLen_RX)		MSG_Rx_CNT=0;		
		}	
		
	  USART_ClearFlag(UART5, USART_FLAG_TC);     		
} 


