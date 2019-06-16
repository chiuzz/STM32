#include "usart3.h"
#include "stm32f10x_dma.h"

static BOOLEAN  m_DMATxflg = TRUE;
uint8_t SendBuff[SENDBUFF_SIZE];

/*
 * ��������USART1_Config
 * ����  ��USART1 GPIO ����,����ģʽ���á�115200 8-N-1
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void uart3_init(u32 bound) {
    //GPIO�˿�����
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
//void USART3_IRQHandler(void)                	//����1�жϷ������
//{
//	  printf("USART3_IRQHandler");
//    u8 Res;
//    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�
//    {
//        USART_ClearITPendingBit(USART3,USART_IT_RXNE);
//        Res =USART_ReceiveData(USART3);//(USART1->DR);	//��ȡ���յ�������
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
 * ��������DMA_Config
 * ����  ��DMA ���ڵĳ�ʼ������
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void DMA_UART_Config(int len)
{
    DMA_InitTypeDef DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//����DMAʱ��
    DMA_DeInit(DMA1_Channel2);
    /*����DMAԴ���ڴ��ַ&�������ݼĴ�����ַ*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR;
    /*�ڴ��ַ(Ҫ����ı�����ָ��)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
    /*���򣺴��ڴ浽����*/
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    /*�����СDMA_BufferSize=SENDBUFF_SIZE*/
    DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
    /*�����ַ����*/
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    /*�ڴ��ַ����*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    /*�������ݵ�λ*/
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    /*�ڴ����ݵ�λ 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    /*DMAģʽ��һ�δ��䣬ѭ��*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
    /*���ȼ�����*/
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    /*��ֹ�ڴ浽�ڴ�Ĵ���	*/
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    /*����DMA1��4ͨ��*/
    DMA_Init(DMA1_Channel2, &DMA_InitStructure);
    DMA_Cmd (DMA1_Channel2,ENABLE);					//ʹ��DMA
    DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,ENABLE);  //����DMA������ɺ�����ж�
}

uint16_t UartReceiveData()
{
    while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
    return USART_ReceiveData(USART3);
}


/*
 * ��������NVIC_Config
 * ����  ��DMA �ж�����
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
static void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure one bit for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0	);

    /* ����P[A|B|C|D|E]0Ϊ�ж�Դ */
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

