/**
  ******************************************************************************
  * @file    ARC_USART.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides USART middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_USART.h"
#include "ARC_RCC.h"
#include "ARC_GPIO.h"
#include <stdio.h>

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_USART
  * @{
  */ 

/** @defgroup ARC_USART_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_USART_Private_Defines
  * @{
  */
 
/**
  * @}
  */ 

/** @defgroup ARC_USART_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_USART_Private_Variables
  * @{
  */ 
  
/**
  * @}
  */

/** @defgroup ARC_USART_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_USART_Private_Functions
  * @{
  */
 
/**
  * @brief  Configures COM port parameters.
  * @param  None 
  * @retval None
  */
void ARC_COM_PARAM_Init()
{
    /* USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
    */
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* USART configuration */
    USART_Init(USART1, &USART_InitStructure);
}

/**
  * @brief  Initialize COM port.
  * @param  None 
  * @retval None
  */
void ARC_COM_Init()
{
    ARC_COM_RCC_Init();
    ARC_COM_GPIO_Init();
    ARC_COM_PARAM_Init();
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
