#ifndef __IICDMA_H
#define __IICDMA_H

#ifdef __cplusplus
extern "C" {
#endif 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* To use the I2C at 400 KHz (in fast mode), the PCLK1 frequency (I2C peripheral
   input clock) must be a multiple of 10 MHz */
/* Uncomment the line below if you will use the I2C peripheral in Fast Mode */
#define FAST_I2C_MODE
  
/* Uncomment the line below if you will use the I2C peripheral in 10-bit addressing
   mode */
//#define I2C_10BITS_ADDRESS
  
/* Define I2C Speed ----------------------------------------------------------*/
#ifdef FAST_I2C_MODE
 #define I2C_SPEED 340000
 #define I2C_DUTYCYCLE I2C_DutyCycle_16_9  
#else /* STANDARD_I2C_MODE*/
 #define I2C_SPEED 100000
 #define I2C_DUTYCYCLE  I2C_DutyCycle_2
#endif /* FAST_I2C_MODE*/
  
/* Define Slave Address  -----------------------------------------------------*/
#define SLAVE_ADDRESS 0x93
#define USER_TIMEOUT 0x64
 
#if 1
/* I2Cx Communication boards Interface */
#define I2Cx_DMA                      DMA1
#define I2Cx_DMA_CHANNEL              DMA_Channel_1
#define I2Cx_DR_ADDRESS               ((uint32_t)0x40005410)
#define I2Cx_DMA_STREAM_TX            DMA1_Stream6
#define I2Cx_DMA_STREAM_RX            DMA1_Stream0
#define I2Cx_TX_DMA_TCFLAG            DMA_FLAG_TCIF6
#define I2Cx_TX_DMA_FEIFLAG           DMA_FLAG_FEIF6
#define I2Cx_TX_DMA_DMEIFLAG          DMA_FLAG_DMEIF6
#define I2Cx_TX_DMA_TEIFLAG           DMA_FLAG_TEIF6
#define I2Cx_TX_DMA_HTIFLAG           DMA_FLAG_HTIF6
#define I2Cx_RX_DMA_TCFLAG            DMA_FLAG_TCIF0
#define I2Cx_RX_DMA_FEIFLAG           DMA_FLAG_FEIF0
#define I2Cx_RX_DMA_DMEIFLAG          DMA_FLAG_DMEIF0
#define I2Cx_RX_DMA_TEIFLAG           DMA_FLAG_TEIF0
#define I2Cx_RX_DMA_HTIFLAG           DMA_FLAG_HTIF0
#define DMAx_CLK                      RCC_AHB1Periph_DMA1    

#define I2Cx                          I2C1
#define I2Cx_CLK                      RCC_APB1Periph_I2C1
#define I2Cx_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define I2Cx_SDA_PIN                  GPIO_Pin_9                
#define I2Cx_SDA_GPIO_PORT            GPIOB                       
#define I2Cx_SDA_SOURCE               GPIO_PinSource9
#define I2Cx_SDA_AF                   GPIO_AF_I2C1
 
#define I2Cx_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define I2Cx_SCL_PIN                  GPIO_Pin_8                
#define I2Cx_SCL_GPIO_PORT            GPIOB                    
#define I2Cx_SCL_SOURCE               GPIO_PinSource8
#define I2Cx_SCL_AF                   GPIO_AF_I2C1

#else

/* I2Cx Communication boards Interface */
#define I2Cx_DMA                      DMA1
#define I2Cx_DMA_CHANNEL              DMA_Channel_7
// #define I2Cx_DR_ADDRESS               ((uint32_t)0x40005410) //I2C1的地址
#define I2Cx_DR_ADDRESS               ((uint32_t)0x40005810) //I2C2的地址
#define I2Cx_DMA_STREAM_TX            DMA1_Stream7
#define I2Cx_DMA_STREAM_RX            DMA1_Stream3
#define I2Cx_TX_DMA_TCFLAG            DMA_FLAG_TCIF6
#define I2Cx_TX_DMA_FEIFLAG           DMA_FLAG_FEIF6
#define I2Cx_TX_DMA_DMEIFLAG          DMA_FLAG_DMEIF6
#define I2Cx_TX_DMA_TEIFLAG           DMA_FLAG_TEIF6
#define I2Cx_TX_DMA_HTIFLAG           DMA_FLAG_HTIF6
#define I2Cx_RX_DMA_TCFLAG            DMA_FLAG_TCIF0
#define I2Cx_RX_DMA_FEIFLAG           DMA_FLAG_FEIF0
#define I2Cx_RX_DMA_DMEIFLAG          DMA_FLAG_DMEIF0
#define I2Cx_RX_DMA_TEIFLAG           DMA_FLAG_TEIF0
#define I2Cx_RX_DMA_HTIFLAG           DMA_FLAG_HTIF0
#define DMAx_CLK                      RCC_AHB1Periph_DMA1    

#define I2Cx                          I2C2
#define I2Cx_CLK                      RCC_APB1Periph_I2C2
#define I2Cx_SDA_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define I2Cx_SDA_PIN                  GPIO_Pin_11                
#define I2Cx_SDA_GPIO_PORT            GPIOB                       
#define I2Cx_SDA_SOURCE               GPIO_PinSource11
#define I2Cx_SDA_AF                   GPIO_AF_I2C2
 
#define I2Cx_SCL_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define I2Cx_SCL_PIN                  GPIO_Pin_10                
#define I2Cx_SCL_GPIO_PORT            GPIOB                    
#define I2Cx_SCL_SOURCE               GPIO_PinSource10
#define I2Cx_SCL_AF                   GPIO_AF_I2C2
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
#endif
extern void I2C_INIT(void);
extern uint16_t ReceiveI2cDmaData(uint8_t SlaveAddr);

#ifdef __cplusplus
}
#endif

#endif 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/