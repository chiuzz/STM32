/* Includes ------------------------------------------------------------------*/
#include "Iiclib.h"

/* Private variables ---------------------------------------------------------*/
#define RXBUFFERSIZE  2 
uint8_t aRxBuffer[RXBUFFERSIZE];

/* Private function prototypes -----------------------------------------------*/
static void TimeOut_UserCallback(void);
static uint16_t DataProcess(uint8_t* pdata)
{
    uint16_t ret=0;
    ret = (pdata[0]<<8) + pdata[1];
    return ret;
}

uint16_t ReceiveI2cDmaData(uint8_t SlaveAddr)
{
    I2C_InitTypeDef  I2C_InitStructure;
    __IO uint32_t TimeOut = 0x0;
    /*************************************Master Code****************************/
    /* I2C Struct Initialize */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DUTYCYCLE;
    I2C_InitStructure.I2C_OwnAddress1 = 0xA0;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_ClockSpeed = I2C_SPEED;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    /* I2C Initialize */
    I2C_Init(I2Cx, &I2C_InitStructure);

    /* Master Receiver ---------------------------------------------------------*/ 
    /* Enable DMA NACK automatic generation */
    I2C_DMALastTransferCmd(I2Cx, ENABLE);
    /* Send I2Cx START condition */
    I2C_GenerateSTART(I2Cx, ENABLE);
    /* Test on I2Cx EV5 and clear it or time out*/
    TimeOut = USER_TIMEOUT;
    while ((!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))&&(TimeOut != 0x00))
    {}
    if(TimeOut == 0)
    {
        TimeOut_UserCallback();
    }
    /* Send I2Cx slave Address for write */
    I2C_Send7bitAddress(I2Cx, SlaveAddr, I2C_Direction_Receiver);
    /* Test on I2Cx EV6 and clear it or time out */
    TimeOut = USER_TIMEOUT;
    while ((!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))&&(TimeOut != 0x00))
    {}
    if(TimeOut == 0)
    {
        TimeOut_UserCallback();
    }
    /* I2Cx DMA Enable */
    I2C_DMACmd(I2Cx, ENABLE);
    /* Enable DMA RX Channel */
    DMA_Cmd(I2Cx_DMA_STREAM_RX, ENABLE);
    /* Wait until I2Cx_DMA_STREAM_RX enabled or time out */
    TimeOut = USER_TIMEOUT;
    while ((DMA_GetCmdStatus(I2Cx_DMA_STREAM_RX)!= ENABLE)&&(TimeOut != 0x00))
    {}  
    if(TimeOut == 0)
    {
        TimeOut_UserCallback();
    }
    /* Transfer complete or time out */
    TimeOut = USER_TIMEOUT;
    while ((DMA_GetFlagStatus(I2Cx_DMA_STREAM_RX,I2Cx_RX_DMA_TCFLAG)==RESET)&&(TimeOut != 0x00))
    {}
    if(TimeOut == 0)
    {
        TimeOut_UserCallback();
    }
    /* Send I2Cx STOP Condition */
    I2C_GenerateSTOP(I2Cx, ENABLE);
    /* Disable DMA RX Channel */
    DMA_Cmd(I2Cx_DMA_STREAM_RX, DISABLE);
    /* Wait until I2Cx_DMA_STREAM_RX disabled or time out */
    TimeOut = USER_TIMEOUT;
    while ((DMA_GetCmdStatus(I2Cx_DMA_STREAM_RX)!= DISABLE)&&(TimeOut != 0x00))
    {}  
    if(TimeOut == 0)
    {
        TimeOut_UserCallback();
    }
    /* Disable I2C DMA request */  
    I2C_DMACmd(I2Cx,DISABLE);
    /* Clear any pending flag on Rx Stream  */
    DMA_ClearFlag(I2Cx_DMA_STREAM_RX, I2Cx_RX_DMA_TCFLAG | I2Cx_RX_DMA_FEIFLAG | I2Cx_RX_DMA_DMEIFLAG | \
            I2Cx_RX_DMA_TEIFLAG | I2Cx_RX_DMA_HTIFLAG);
    return DataProcess(aRxBuffer);

}


/**
 * @brief  Enables the I2C Clock and configures the different GPIO ports.
 * @param  None
 * @retval None
 */
void I2C_INIT(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    DMA_InitTypeDef  DMA_InitStructure;

    /* RCC Configuration */
    RCC_APB1PeriphClockCmd(I2Cx_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(I2Cx_SDA_GPIO_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(I2Cx_SCL_GPIO_CLK, ENABLE);

    RCC_APB1PeriphResetCmd(I2Cx_CLK, ENABLE);
    RCC_APB1PeriphResetCmd(I2Cx_CLK, DISABLE);
    RCC_AHB1PeriphClockCmd(DMAx_CLK, ENABLE);

    /* GPIO Configuration */
    /*Configure I2C SCL pin */
    GPIO_InitStructure.GPIO_Pin = I2Cx_SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(I2Cx_SCL_GPIO_PORT, &GPIO_InitStructure);

    /*Configure I2C SDA pin */
    GPIO_InitStructure.GPIO_Pin = I2Cx_SDA_PIN;
    GPIO_Init(I2Cx_SDA_GPIO_PORT, &GPIO_InitStructure);

    /* Connect PXx to I2C_SCL */
    GPIO_PinAFConfig(I2Cx_SCL_GPIO_PORT, I2Cx_SCL_SOURCE, I2Cx_SCL_AF);
    /* Connect PXx to I2C_SDA */
    GPIO_PinAFConfig(I2Cx_SDA_GPIO_PORT, I2Cx_SDA_SOURCE, I2Cx_SDA_AF);

    /* DMA Configuration */
    /* Clear any pending flag on Tx Stream  */
    DMA_ClearFlag(I2Cx_DMA_STREAM_TX, I2Cx_TX_DMA_TCFLAG | I2Cx_TX_DMA_FEIFLAG | I2Cx_TX_DMA_DMEIFLAG | \
            I2Cx_TX_DMA_TEIFLAG | I2Cx_TX_DMA_HTIFLAG);
    /* Clear any pending flag on Rx Stream  */
    DMA_ClearFlag(I2Cx_DMA_STREAM_RX, I2Cx_RX_DMA_TCFLAG | I2Cx_RX_DMA_FEIFLAG | I2Cx_RX_DMA_DMEIFLAG | \
            I2Cx_RX_DMA_TEIFLAG | I2Cx_RX_DMA_HTIFLAG);
    /* Disable the I2C Tx DMA stream */
    DMA_Cmd(I2Cx_DMA_STREAM_TX, DISABLE);
    /* Configure the DMA stream for the I2C peripheral TX direction */
    DMA_DeInit(I2Cx_DMA_STREAM_TX);
    /* Disable the I2C Rx DMA stream */
    DMA_Cmd(I2Cx_DMA_STREAM_RX, DISABLE);

    /* Configure the DMA stream for the I2C peripheral RX direction */
    DMA_DeInit(I2Cx_DMA_STREAM_RX);
    DMA_InitStructure.DMA_Channel = I2Cx_DMA_CHANNEL;
    DMA_InitStructure.DMA_PeripheralBaseAddr = I2Cx_DR_ADDRESS;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

    /* Init DMA for Reception */
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)aRxBuffer;
    DMA_InitStructure.DMA_BufferSize = RXBUFFERSIZE;
    DMA_DeInit(I2Cx_DMA_STREAM_RX);
    DMA_Init(I2Cx_DMA_STREAM_RX, &DMA_InitStructure);

    /* Configure I2C Filters */
    I2C_AnalogFilterCmd(I2Cx,ENABLE);
    I2C_DigitalFilterConfig(I2Cx,0x0F);

    /* I2C ENABLE */
    //I2C_Cmd(I2Cx, ENABLE);
}

/**
 * @brief  Basic management of the timeout situation.
 * @param  None.
 * @retval None.
 */
static void TimeOut_UserCallback(void)
{
    /* User can add his own implementation to manage TimeOut Communication failure */
    /* Block communication and all processes */
    while (1)
    {   
    }
}
