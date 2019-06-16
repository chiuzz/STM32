#include "sys.h"
#include "usart3.h"	

////////////////////////////////////////////////////////////////////////////////// 	 

void uart3_init(u32 bound){
    //GPIO�˿�����
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOAʱ��
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART1ʱ��


		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOB11��GPIOB10��ʼ��
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
		GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��GPIOB11����GPIOB10

		GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11����ΪUSART3
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10����ΪUSART3	

		//USART1 ��ʼ������
		USART_InitStructure.USART_BaudRate = 57600;//����������
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
		USART_Init(USART3, &USART_InitStructure); //��ʼ������1

		USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���1 

		USART_ClearFlag(USART3, USART_FLAG_TC);

		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�

		//Usart1 NVIC ����
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����1�ж�ͨ��
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

}

void Usart3SendData(uint8_t *pdata, uint8_t len)
{
    uint8_t i;
    for(i=0;i<len;i++)
    {
        USART_SendData(USART3, pdata[i]);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    }
}

extern void SendSrcUartData(uint16_t data); //���������ã�������ѹ�����ݼ��������ְ�
void USART3_IRQHandler(void)                	//����1�жϷ������
{
    u8 temp;
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�
    {
        USART_ClearITPendingBit(USART3,USART_IT_RXNE); 
        temp =USART_ReceiveData(USART3);//(USART1->DR);	//��ȡ���յ�������
			  SendSrcUartData(temp);
		}
} 
