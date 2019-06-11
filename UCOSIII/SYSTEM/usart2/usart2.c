#include "sys.h"
#include "usart2.h"
//////////////////////////////////////////////////////////////////////////////////
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif


#if EN_USART2_RX   //如果使能了接收
//串口2中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误
u8 USART_RX_BUF2[USART_REC_LEN2];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA2=0;       //接收状态标记

//初始化IO 串口2
//bound:波特率
void uart2_init(u32 bound) {
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟

    //串口2对应引脚复用映射
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2复用为USART2
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3复用为USART2

    //USART2端口配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2与GPIOA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
    GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA2，PA3

    //USART2 初始化设置
    USART_InitStructure.USART_BaudRate = bound;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART2, &USART_InitStructure); //初始化串口2

    USART_Cmd(USART2, ENABLE);  //使能串口2

    USART_ClearFlag(USART2, USART_FLAG_TC);

#if EN_USART2_RX
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断

    //Usart2 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口2中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

#endif

}


void USART2_IRQHandler(void)                	//串口2中断服务程序
{
    u8 Res;
#if SYSTEM_SUPPORT_OS  //使用UCOS操作系统
    OSIntEnter();				//进入中断管理
#endif
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
    {
        Res =USART_ReceiveData(USART2);//(USART2->DR);	//读取接收到的数据

        if((USART_RX_STA2&0x8000)==0)//接收未完成
        {
            if(USART_RX_STA2&0x4000)//接收到了0x0d
            {
                if(Res!=0x0a)USART_RX_STA2=0;//接收错误,重新开始
                else USART_RX_STA2|=0x8000;	//接收完成了
            }
            else //还没收到0X0D
            {
                if(Res==0x0d)USART_RX_STA2|=0x4000;
                else
                {
                    USART_RX_BUF2[USART_RX_STA2&0X3FFF]=Res ;
                    USART_RX_STA2++;
                    if(USART_RX_STA2>(USART_REC_LEN2-1))USART_RX_STA2=0;//接收数据错误,重新开始接收
                }
            }
        }
    }

#if SYSTEM_SUPPORT_OS
    OSIntExit();    	//退出中断管理
#endif
}
#endif





