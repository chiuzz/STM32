#include "usart3.h"
#include "stm32f10x_dma.h"

static BOOLEAN  m_DMATxflg = TRUE;
uint8_t SendBuff[SENDBUFF_SIZE];

/*
 * 函数名：USART1_Config
 * 描述  ：USART1 GPIO 配置,工作模式配置。115200 8-N-1
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void uart3_init(u32 bound) {
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0	);

    /* config USART1 clock */
// 	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3 | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    /* USART1 GPIO config */
    /* Configure USART1 Tx (PA.09) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //GPIO_SetBits(GPIOB,GPIO_Pin_10);
    /* Configure USART1 Rx (PA.10) as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* USART1 mode config */
    USART_InitStructure.USART_BaudRate = 57600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);
    USART_Cmd(USART3, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel =USART3_IRQn;//USART3_IRQHandler;//
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
//
    USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);

}

void Usart3SendData(uint8_t *pdata, uint8_t len)
{
    uint8_t i;
    for(i=0; i<len; i++)
    {
        USART_SendData(USART3, pdata[i]);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    }
}
static u16 Comp_Speed_CNT =0;
//void USART3_IRQHandler(void)                	//串口1中断服务程序
//{
//	  printf("USART3_IRQHandler");
//    u8 Res;
//    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
//    {
//        USART_ClearITPendingBit(USART3,USART_IT_RXNE);
//        Res =USART_ReceiveData(USART3);//(USART1->DR);	//读取接收到的数据
//			   SendUartData(Res);
//				if(Res<65)
//						Comp_Speed_CNT = (u16)(Res*63.6);
//    }
////
////		u8 c;
////  if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)
////  {
////    USART_ClearITPendingBit(USART3,USART_IT_RXNE);
////		c=USART3->DR;
//// 		printf("%d ",c);
////  		printf("%d ",USART_ReceiveData(USART3));
////    SendUartData(c);
//
//}
/*
 * 函数名：DMA_Config
 * 描述  ：DMA 串口的初始化配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void DMA_UART_Config(int len)
{
    DMA_InitTypeDef DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//开启DMA时钟
    DMA_DeInit(DMA1_Channel2);
    /*设置DMA源：内存地址&串口数据寄存器地址*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR;
    /*内存地址(要传输的变量的指针)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
    /*方向：从内存到外设*/
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    /*传输大小DMA_BufferSize=SENDBUFF_SIZE*/
    DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
    /*外设地址不增*/
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    /*内存地址自增*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    /*外设数据单位*/
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    /*内存数据单位 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    /*DMA模式：一次传输，循环*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
    /*优先级：中*/
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    /*禁止内存到内存的传输	*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    /*配置DMA1的4通道*/
    DMA_Init(DMA1_Channel2, &DMA_InitStructure);
    DMA_Cmd (DMA1_Channel2,ENABLE);					//使能DMA
    DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,ENABLE);  //配置DMA发送完成后产生中断
}

uint16_t UartReceiveData()
{
    while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
    return USART_ReceiveData(USART3);
}


/*
 * 函数名：NVIC_Config
 * 描述  ：DMA 中断配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
static void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure one bit for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0	);

    /* 配置P[A|B|C|D|E]0为中断源 */
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void SendIntFlag()
{
    if(m_DMATxflg == FALSE)
        m_DMATxflg = TRUE;
}

void USART3_INIT(void)
{
    //USART3_Config();
//		DMA_UART_Config(SENDBUFF_SIZE);
//		NVIC_Config();
}

