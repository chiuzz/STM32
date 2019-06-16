/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * 文件名  ：led.c
 * 描述    ：led 应用函数库
 * 实验平台：野火STM32开发板
 * 硬件连接：-----------------
 *          |   PC3 - LED1     |
 *          |   PC4 - LED2     |
 *          |   PC5 - LED3     |
 *           -----------------
 * 库版本  ：ST3.0.0
 * 作者    ：wildfire team
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/

#include "led.h"
#include "common.h"
/*
 * 函数名：LED_GPIO_Config
 * 描述  ：配置LED用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
void LED_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //按键列
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	//使能时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //喇叭
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	//使能时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_8);

//   //显示屏
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

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	//使能时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);	//vol3
    GPIO_SetBits(GPIOB, GPIO_Pin_8);	//vol2
    GPIO_SetBits(GPIOB, GPIO_Pin_9);	//VOL1

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	//使能时钟
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_0); //CTRL_LED
//	GPIO_ResetBits(GPIOB,GPIO_Pin_1); //CTRL_ALM
//	GPIO_ResetBits(GPIOB,GPIO_Pin_2); //CTRL_SC

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	//使能时钟
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
//		printf("A0 ON 减\r\n");//减
        key |= BIT0;
    }
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1))
    {
//		printf("A1 ON 加\r\n");//加
        key |= BIT1;
    }
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2))
    {
//		printf("A2 ON 液路II\r\n");//液路II
        key |= BIT2;
    }
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))
    {
//		printf("A3 ON 体温II\r\n");//体温II
        key |= BIT3;
    }
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4))
    {
//		printf("A4 ON 制冷热\r\n");//制冷热
        key |= BIT4;
    }
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5))
    {
//		printf("A5 ON 液温I\r\n");//液温I
        key |= BIT5;
    }
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6))
    {
//		printf("A6 ON 液路I\r\n");//液路I
        key |= BIT6;

    }
    if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7))
    {
//		printf("A7 ON 体温I \r\n");//体温I
        key |= BIT7;
    }
    return key;
}

void SetAlarmLevel(u8 index)
{
    switch(index)
    {
    case 1:
        GPIO_ResetBits(GPIOA, GPIO_Pin_11); //W2  低级报警
        GPIO_SetBits(GPIOA, GPIO_Pin_12); //W1
        break;
    case 2:
        GPIO_SetBits(GPIOA, GPIO_Pin_11); //W2  中级报警
        GPIO_ResetBits(GPIOA, GPIO_Pin_12); //W1
        break;
    case 3:
        GPIO_SetBits(GPIOA, GPIO_Pin_11); //W2  高级报警
        GPIO_SetBits(GPIOA, GPIO_Pin_12); //W1
        break;
    default:
        GPIO_ResetBits(GPIOA, GPIO_Pin_11); //W2  无报警
        GPIO_ResetBits(GPIOA, GPIO_Pin_12); //W1
        break;
    }
}

void SetAlarmVolum(u8 index)
{
    switch(index)
    {
    case 1:
        GPIO_ResetBits(GPIOB, GPIO_Pin_8); //VOL2 //低音
        GPIO_SetBits(GPIOB, GPIO_Pin_9); //VOL1
        break;
    case 2:
        GPIO_SetBits(GPIOB, GPIO_Pin_8); //VOL2 //中音
        GPIO_ResetBits(GPIOB, GPIO_Pin_9); //VOL1
        break;
    case 3:
        GPIO_SetBits(GPIOB, GPIO_Pin_8); //VOL2 //高音
        GPIO_SetBits(GPIOB, GPIO_Pin_9); //VOL1
        break;
    default:
        break;
    }
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
//********************************************************************************************************
//* 函 数 名 : write_lcd_data(unsigned short int address,unsigned  char _data,Bool _cs)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 向芯片1写入一个数据
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : unsigned short int address      写入数据的地址
//			   unsigned short int data		   写入的数据
//			   Bool _cs						   驱动芯片
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : None
//**------------------------------------------------------------------------------------------------------
//* 返    回 : None
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
//* 函 数 名 : send_lcd_command(unsigned char command,Bool _cs)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 向芯片1发送一个命令
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : unsigned char command    发生的命令
//			   Bool _cs					驱动芯片
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : None
//**------------------------------------------------------------------------------------------------------
//* 返    回 : None
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
//* 函 数 名 : void lcd_init(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 芯片初始化
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : None
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : None
//**------------------------------------------------------------------------------------------------------
//* 返    回 : None
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
//* 函 数 名 : BuzzeOn(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 蜂鸣器开
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : None
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : None
//**------------------------------------------------------------------------------------------------------
//* 返    回 : None
//********************************************************************************************************
void BuzzeOn(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}

//********************************************************************************************************
//* 函 数 名 : BuzzeOn(void)
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 蜂鸣器关
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : None
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : None
//**------------------------------------------------------------------------------------------------------
//* 返    回 : None
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
//* 函 数 名 : void disp_all()
//**------------------------------------------------------------------------------------------------------
//* 描    述 :  全屏点亮
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : None
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : None
//**------------------------------------------------------------------------------------------------------
//* 返    回 : None
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
//* 函 数 名 : void disp_clear()
//**------------------------------------------------------------------------------------------------------
//* 描    述 : 清屏
//**------------------------------------------------------------------------------------------------------
//* 输入参数 : None
//**------------------------------------------------------------------------------------------------------
//* 输出参数 : None
//**------------------------------------------------------------------------------------------------------
//* 返    回 : None
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
