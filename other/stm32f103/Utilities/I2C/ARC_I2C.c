/**
  ******************************************************************************
  * @file    ARC_I2C.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides I2C middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_I2C.h"
#include "ARC_SysTick.h"
#include "ARC_GPIO.h"
#include "ARC_RCC.h"
#include "ARC_EXTI.h"
#include "ARC_NVIC_API.h"


/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_I2C
  * @{
  */ 

/** @defgroup ARC_I2C_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_I2C_Private_Defines
  * @{
  */
  
/**
  * @}
  */ 

/** @defgroup ARC_I2C_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_I2C_Private_Variables
  * @{
  */ 

static I2C_param_struct __IO I2C_Device;

/**
  * @}
  */

/** @defgroup ARC_I2C_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_I2C_Private_Functions
  * @{
  */

/**
  * @brief  get the I2C Device parameters.
  * @param  None
  * @retval the I2C device parameters
  */
I2C_param_struct __IO *ARC_get_I2C_param()
{
    return &I2C_Device;
}

/**
  * @brief  Configure the I2C parameters.
  * @param  None
  * @retval None
  */
void ARC_I2C_PARAM_Init()
{
    I2C_InitTypeDef I2C1_InitStructure;

    /* IOE_I2C configuration */
    I2C1_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C1_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C1_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C1_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C1_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C1_InitStructure.I2C_ClockSpeed = 20000;

    I2C_Init(I2C1, &I2C1_InitStructure);
}

/**
  * @brief  Configure the I2C Peripheral.
  * @param  None
  * @retval None
  */
void ARC_I2C_Init()
{
    I2C_DeInit(I2C1);
    ARC_I2C_RCC_Init();
    ARC_I2C_GPIO_Init();
    ARC_I2C_PARAM_Init();
    ARC_I2C_NVIC_Init();
}

/**
  * @brief  Deinitialize  the I2C Peripheral.
  * @param  None
  * @retval None
  */
void ARC_I2C_DeInit()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    I2C_DeInit(I2C1);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief  @brief I2C write function.
  * @param  *I2Cx: I2C device ID.
  * @param  *I2C_param: I2C parameters.
  * @retval None
  */
void ARC_I2C_Read(I2C_TypeDef *I2Cx, I2C_param_struct __IO *I2C_param)
{    
    /* Enable I2C errors interrupts */
    I2Cx->CR2 |= I2C_IT_ERR;
    /* Enable EVT IT*/
    I2Cx->CR2 |= I2C_IT_EVT;
    /* Enable BUF IT */
    I2Cx->CR2 |= I2C_IT_BUF;

    I2C_GenerateSTART(I2Cx, ENABLE);
    
    /* Wait until BUSY flag is reset (until a STOP is generated) */
    while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
    /* Enable Acknowledgement to be ready for another reception */
    I2C_AcknowledgeConfig(I2Cx, ENABLE);
}

/**
  * @brief  @brief I2C write function.
  * @param  *I2Cx: I2C device ID.
  * @param  *I2C_param: I2C parameters.
  * @retval None
  */
void ARC_I2C_Write(I2C_TypeDef *I2Cx, I2C_param_struct __IO *I2C_param)
{
    /* Enable Error IT */
    I2C_ITConfig(I2Cx, I2C_IT_ERR, ENABLE);
    /* Enable EVT IT*/
    I2C_ITConfig(I2Cx, I2C_IT_EVT, ENABLE);
    /* Enable BUF IT */
    I2C_ITConfig(I2Cx, I2C_IT_BUF, ENABLE);

    /* Wait until BUSY flag is reset: a STOP has been generated on the bus signaling the end
    of transmission */
    while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

    /* Send START condition */
    I2C_GenerateSTART(I2Cx, ENABLE);

    /* Wait until BUSY flag is reset: a STOP has been generated on the bus signaling the end
    of transmission */
    while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
    if(I2C_param->TX_Generate_stop == 0)
        I2C_AcknowledgeConfig(I2C1, ENABLE);
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
