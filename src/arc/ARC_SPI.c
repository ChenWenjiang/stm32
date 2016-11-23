/**
  ******************************************************************************
  * @file    ARC_SPI.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides SPI middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_SPI.h"
#include "ARC_GPIO.h"
#include "ARC_RCC.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_SPI
  * @{
  */ 

/** @defgroup ARC_SPI_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_SPI_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_SPI_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_SPI_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup ARC_SPI_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_SPI_Private_Functions
  * @{
  */
  
/**
  * @brief  Initialize SPI parameters
  * @param  *SPIx: the SPI device ID.
  * @retval None
  */
void ARC_SPI_PARAM_Init(SPI_TypeDef *SPIx)
{
    SPI_InitTypeDef  SPI_InitStructure;
    SPI_I2S_DeInit(SPI1);

    /*!< SPI configuration */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = ARC_SPI_DEFAULT_SPEED;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPIx, &SPI_InitStructure);
    
    SPI_CalculateCRC(SPI1, DISABLE);
}

/**
  * @brief  Initialize SPI.
  * @param  None
  * @retval None.
  */
void ARC_SPI_Init(void)
{
    ARC_SPI_RCC_Init();
    ARC_SPI_GPIO_Init();
    ARC_SPI_PARAM_Init(SPI1);
    ARC_FLASH_CS_HIGH();
    ARC_SD_CS_HIGH();
    ARC_TS_CS_HIGH();
}


/**
  * @brief  Sends a byte through the SPI interface and return the byte received
  *         from the SPI bus.
  * @param  *SPIx: the SPI device ID.
  * @param  byte: byte to send.
  * @retval The value of the received byte.
  */
uint8_t ARC_SPI_SendByte(SPI_TypeDef *SPIx, uint8_t byte)
{
    /*!< Loop while DR register in not empty */
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);

    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPIx, byte);

    /*!< Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);

    /*!< Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(SPIx);
}

/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */  
    
/******************* (C) www.armrunc.com *****END OF FILE****/
