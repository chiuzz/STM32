#include "sys.h"
#include "usart5.h"	
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ��	  
#endif



//��ʼ��IO ����5
//bound:������
void uart5_init(u32 bound){
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//ʹ��USART1ʱ��

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOCʱ��
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
		GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��GPIOB11����GPIOB10

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //ʹ��GPIOAʱ��
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
		GPIO_Init(GPIOD,&GPIO_InitStructure); //��ʼ��GPIOB11����GPIOB10

		GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5); //GPIOB11����ΪUSART5
		GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5); //GPIOB10����ΪUSART5	
		
    //USART1 ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(UART5, &USART_InitStructure); //��ʼ������1

    USART_Cmd(UART5, ENABLE);  //ʹ�ܴ���1 

    USART_ClearFlag(UART5, USART_FLAG_TC);

    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//��������ж�

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;//����5�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

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


void UART5_IRQHandler(void)                	//����5�жϷ������
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


