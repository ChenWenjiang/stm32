/**
  ******************************************************************************
  * @file    ARC_DAM.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides DMA middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_DAM
  * @{
  */ 

/** @defgroup ARC_DAM_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_DAM_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_DAM_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_DAM_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup ARC_DAM_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_DAM_Private_Functions
  * @{
  */
    
/**
  * @brief  Initialize the parameters of DMA.
  * @param  *MemoryBaseAddr: the base address of memory, it is source.
  * @param  BufferSize: the buffer size to be transferred via DMA.
  * @retval None
  */
void ARC_DMA1_Ch2_Param_Init(const uint8_t *MemoryBaseAddr, uint32_t BufferSize)
{
    DMA_InitTypeDef  DMA_InitStructure;  

    /* DMA1 Channel2 configuration ----------------------------------------------*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)MemoryBaseAddr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = BufferSize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_DeInit(DMA1_Channel2);
    DMA_Init(DMA1_Channel2, &DMA_InitStructure); 
}

/**
  * @brief  Initialize the parameters of DMA.
  * @param  *MemoryBaseAddr: the base address of memory, it is source.
  * @param  BufferSize: the buffer size to be transferred via DMA.
  * @retval None
  */
void ARC_DMA1_Ch3_Param_Init(const uint8_t *MemoryBaseAddr, uint32_t BufferSize, uint32_t memIncEnable)
{
    DMA_InitTypeDef  DMA_InitStructure;  

    /* DMA1 Channel3 configuration ----------------------------------------------*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)MemoryBaseAddr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = BufferSize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_DeInit(DMA1_Channel3);
    DMA_Init(DMA1_Channel3, &DMA_InitStructure); 
}

/**
  * @brief  Initialize the parameters of DMA.
  * @param  *MemoryBaseAddr: the base address of memory, it is source.
  * @param  BufferSize: the buffer size to be transferred via DMA.
  * @retval None
  */
void ARC_DMA1_Ch4_Param_Init(const uint8_t *MemoryBaseAddr, uint32_t BufferSize)
{
    DMA_InitTypeDef  DMA_InitStructure;  

    /* DMA1 Channel4 configuration ----------------------------------------------*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)MemoryBaseAddr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = BufferSize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_DeInit(DMA1_Channel4);
    DMA_Init(DMA1_Channel4, &DMA_InitStructure); 
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
