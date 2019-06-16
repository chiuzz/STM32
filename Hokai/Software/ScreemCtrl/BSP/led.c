/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * �ļ���  ��led.c
 * ����    ��led Ӧ�ú�����
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ�-----------------
 *          |   PC3 - LED1     |
 *          |   PC4 - LED2     |
 *          |   PC5 - LED3     |
 *           -----------------
 * ��汾  ��ST3.0.0
 * ����    ��wildfire team
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/

#include "led.h"
#include "common.h"
/*
 * ��������LED_GPIO_Config
 * ����  ������LED�õ���I/O��
 * ����  ����
 * ���  ����
 */
void LED_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //������
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	//ʹ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //����
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	//ʹ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_8);

//   //��ʾ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // GPIO_Mode_Out_OD;//
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
    GPIO_SetBits(GPIOB, GPIO_Pin_13);
    GPIO_SetBits(GPIOB, GPIO_Pin_14);
    GPIO_SetBits(GPIOB, GPIO_Pin_15);
    //

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	//ʹ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);	//vol3
    GPIO_SetBits(GPIOB, GPIO_Pin_8);	//vol2
    GPIO_SetBits(GPIOB, GPIO_Pin_9);	//VOL1

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	//ʹ��ʱ��
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_0); //CTRL_LED
//	GPIO_ResetBits(GPIOB,GPIO_Pin_1); //CTRL_ALM
//	GPIO_ResetBits(GPIOB,GPIO_Pin_2); //CTRL_SC

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	//ʹ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_ResetBits(GPIOA, GPIO_Pin_11);
    GPIO_ResetBits(GPIOA, GPIO_Pin_12);
}

bool GetKey0Sta()
{
    bool ret = FALSE;
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))ret = TRUE;
    return ret;
}
bool GetKey1Sta()
{
    bool ret = FALSE;
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))ret = TRUE;
    return ret;
}
bool GetKey2Sta()
{
    bool ret = FALSE;
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2))ret = TRUE;
    return ret;
}
bool GetKey3Sta()
{
    bool ret = FALSE;
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))ret = TRUE;
    return ret;
}
bool GetKey4Sta()
{
    bool ret = FALSE;
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4))ret = TRUE;
    return ret;
}
bool GetKey5Sta()
{
    bool ret = FALSE;
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5))ret = TRUE;
    return ret;
}
bool GetKey6Sta()
{
    bool ret = FALSE;
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6))ret = TRUE;
    return ret;
}
bool GetKey7Sta()
{
    bool ret = FALSE;
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7))ret = TRUE;
    return ret;
}
u8 GetButtomValue()
{
    u8 key = 0;
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
    {
//		printf("A0 ON ��\r\n");//��
        key |= BIT0;
    }
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
    {
//		printf("A1 ON ��\r\n");//��
        key |= BIT1;
    }
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2))
    {
//		printf("A2 ON Һ·II\r\n");//Һ·II
        key |= BIT2;
    }
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))
    {
//		printf("A3 ON ����II\r\n");//����II
        key |= BIT3;
    }
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4))
    {
//		printf("A4 ON ������\r\n");//������
        key |= BIT4;
    }
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5))
    {
//		printf("A5 ON Һ��I\r\n");//Һ��I
        key |= BIT5;
    }
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6))
    {
//		printf("A6 ON Һ·I\r\n");//Һ·I
        key |= BIT6;

    }
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7))
    {
//		printf("A7 ON ����I \r\n");//����I
        key |= BIT7;
    }
    return key;
}

void SetAlarmLevel(u8 index)
{
    switch(index)
    {
    case 1:
        GPIO_ResetBits(GPIOA, GPIO_Pin_11); //W2  �ͼ�����
        GPIO_SetBits(GPIOA, GPIO_Pin_12); //W1
        break;
    case 2:
        GPIO_SetBits(GPIOA, GPIO_Pin_11); //W2  �м�����
        GPIO_ResetBits(GPIOA, GPIO_Pin_12); //W1
        break;
    case 3:
        GPIO_SetBits(GPIOA, GPIO_Pin_11); //W2  �߼�����
        GPIO_SetBits(GPIOA, GPIO_Pin_12); //W1
        break;
    default:
        GPIO_ResetBits(GPIOA, GPIO_Pin_11); //W2  �ޱ���
        GPIO_ResetBits(GPIOA, GPIO_Pin_12); //W1
        break;
    }
}

void SetAlarmVolum(u8 index)
{
    switch(index)
    {
    case 1:
        GPIO_ResetBits(GPIOB, GPIO_Pin_8); //VOL2 //����
        GPIO_SetBits(GPIOB, GPIO_Pin_9); //VOL1
        break;
    case 2:
        GPIO_SetBits(GPIOB, GPIO_Pin_8); //VOL2 //����
        GPIO_ResetBits(GPIOB, GPIO_Pin_9); //VOL1
        break;
    case 3:
        GPIO_SetBits(GPIOB, GPIO_Pin_8); //VOL2 //����
        GPIO_SetBits(GPIOB, GPIO_Pin_9); //VOL1
        break;
    default:
        break;
    }
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
//********************************************************************************************************
//* �� �� �� : write_lcd_data(unsigned short int address,unsigned  char _data,Bool _cs)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ��оƬ1д��һ������
//**------------------------------------------------------------------------------------------------------
//* ������� : unsigned short int address      д�����ݵĵ�ַ
//			   unsigned short int data		   д�������
//			   Bool _cs						   ����оƬ
//**------------------------------------------------------------------------------------------------------
//* ������� : None
//**------------------------------------------------------------------------------------------------------
//* ��    �� : None
//********************************************************************************************************

void HT1621Wr_Data(u8 dat, u8 dat_lengh)
{
    u8 i;
    for(i = 0; i < dat_lengh; i ++)
    {
        if((dat & 0x80) == 0)
        {
            LCDDATA_LOW;
        }
        else
        {
            LCDDATA_HIGH;
        }
        LCDWR_LOW
//			delay_us(20);
        LCDWR_HIGH;
//			delay_us(20);
        dat <<= 1;
    }

}
//********************************************************************************************************
//* �� �� �� : send_lcd_command(unsigned char command,Bool _cs)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ��оƬ1����һ������
//**------------------------------------------------------------------------------------------------------
//* ������� : unsigned char command    ����������
//			   Bool _cs					����оƬ
//**------------------------------------------------------------------------------------------------------
//* ������� : None
//**------------------------------------------------------------------------------------------------------
//* ��    �� : None
//********************************************************************************************************
void HT1621WrCmd(u8 Cmd, u8 WhichCS)
{
    if(WhichCS == IC1_PIN)
    {
        LCDCS1_LOW;
//		delay_us(20);
        HT1621Wr_Data(0x80, 4);
        HT1621Wr_Data(Cmd, 8);
//		delay_us(20);
        LCDCS1_HIGH;
    }
    else if(WhichCS == IC2_PIN)
    {
        LCDCS2_LOW;
//		delay_us(20);
        HT1621Wr_Data(0x80, 4);
        HT1621Wr_Data(Cmd, 8);
//		delay_us(20);
        LCDCS2_HIGH
    }

}

//********************************************************************************************************
//* �� �� �� : void lcd_init(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : оƬ��ʼ��
//**------------------------------------------------------------------------------------------------------
//* ������� : None
//**------------------------------------------------------------------------------------------------------
//* ������� : None
//**------------------------------------------------------------------------------------------------------
//* ��    �� : None
//********************************************************************************************************
void HT1621B_Init(void)
{
    LCDCS1_HIGH;
    LCDCS2_HIGH;
    LCDWR_HIGH;
    LCDDATA_HIGH;

//	delay_ms(1);
    HT1621WrCmd(0x00, IC1_PIN);
    HT1621WrCmd(0x04, IC1_PIN);
    HT1621WrCmd(0x30, IC1_PIN);
    HT1621WrCmd(0x02, IC1_PIN);
    HT1621WrCmd(0x06, IC1_PIN);
    HT1621WrCmd(0x52, IC1_PIN);
    HT1621WrCmd(0x80, IC1_PIN);

    HT1621WrCmd(0x00, IC2_PIN);
    HT1621WrCmd(0x04, IC2_PIN);
    HT1621WrCmd(0x30, IC2_PIN);
    HT1621WrCmd(0x02, IC2_PIN);
    HT1621WrCmd(0x06, IC2_PIN);
    HT1621WrCmd(0x52, IC2_PIN);
    HT1621WrCmd(0x80, IC2_PIN);
//	delay_ms(1);

}

void HT1621B_InitiIC1(void)
{
    LCDCS1_HIGH;
    LCDCS2_HIGH;
    LCDWR_HIGH;
    LCDDATA_HIGH;

//	delay_ms(1);
    HT1621WrCmd(0x00, IC1_PIN);
    HT1621WrCmd(0x04, IC1_PIN);
    HT1621WrCmd(0x30, IC1_PIN);
    HT1621WrCmd(0x02, IC1_PIN);
    HT1621WrCmd(0x06, IC1_PIN);
    HT1621WrCmd(0x52, IC1_PIN);
    HT1621WrCmd(0x80, IC1_PIN);
//	delay_ms(20);

}
//********************************************************************************************************
//* �� �� �� : BuzzeOn(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ��������
//**------------------------------------------------------------------------------------------------------
//* ������� : None
//**------------------------------------------------------------------------------------------------------
//* ������� : None
//**------------------------------------------------------------------------------------------------------
//* ��    �� : None
//********************************************************************************************************
void BuzzeOn(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}

//********************************************************************************************************
//* �� �� �� : BuzzeOn(void)
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ��������
//**------------------------------------------------------------------------------------------------------
//* ������� : None
//**------------------------------------------------------------------------------------------------------
//* ������� : None
//**------------------------------------------------------------------------------------------------------
//* ��    �� : None
//********************************************************************************************************
void BuzzeOff(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_8);
}

void HT1621WrOneData(u8 Addr, u8 Data, u8 WhichIC)
{
    if(WhichIC == IC1_PIN)
    {
        LCDCS1_LOW;
//			delay_ms(1);
        HT1621Wr_Data(0xa0, 3); //??????101
        HT1621Wr_Data(Addr << 2, 6); //??????
        HT1621Wr_Data(Data << 4, 4); //????
        LCDCS1_HIGH;//
//			delay_ms(1);
    }
    else if(WhichIC == IC2_PIN)
    {
        LCDCS2_LOW;
//			delay_ms(1);
        HT1621Wr_Data(0xa0, 3); //??????101
        HT1621Wr_Data(Addr << 2, 6); //??????
        HT1621Wr_Data(Data << 4, 4); //????
        LCDCS2_HIGH;//
//			delay_ms(1);
    }


}

//********************************************************************************************************
//* �� �� �� : void disp_all()
//**------------------------------------------------------------------------------------------------------
//* ��    �� :  ȫ������
//**------------------------------------------------------------------------------------------------------
//* ������� : None
//**------------------------------------------------------------------------------------------------------
//* ������� : None
//**------------------------------------------------------------------------------------------------------
//* ��    �� : None
//********************************************************************************************************
void disp_all()
{
    char i;
    for(i = 0; i < 31; i++)
    {
        HT1621WrOneData(i, 0xff, IC1_PIN);
        HT1621WrOneData(i, 0xff, IC2_PIN);
    }
}

//********************************************************************************************************
//* �� �� �� : void disp_clear()
//**------------------------------------------------------------------------------------------------------
//* ��    �� : ����
//**------------------------------------------------------------------------------------------------------
//* ������� : None
//**------------------------------------------------------------------------------------------------------
//* ������� : None
//**------------------------------------------------------------------------------------------------------
//* ��    �� : None
//********************************************************************************************************
void disp_clear()
{
    char i;
    for(i = 0; i < 31; i++)
    {
        HT1621WrOneData(i, 0x0, IC1_PIN);
        HT1621WrOneData(i, 0x0, IC2_PIN);
    }
}

void delay_us(u32 us)
{
//	 u16 i=0;

//	 while(us--)

//	 {
//			i=10;
//			while(i--) ;
//	 }
}

void delay_ms(u32 ms)
{
//	     u16 i=0;
//			 while(ms--)

//			 {
//					i=12000;
//					while(i--) ;
//			 }

}
void delay_1us(void)
{
//	u8 i=0;
//  i++;i++;
//  i++;i++;
//  i++;i++;
//  i++;i++;
//  i++;i++;
//  i++;i++;
//	i++;i++;
//	i++;i++;
//	i++;i++;
}
