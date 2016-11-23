/**
  ******************************************************************************
  * @file    ARC_Retarget.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides retarget middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_Retarget.h"
#include <stdio.h>

#pragma import(__use_no_semihosting)

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_RETARGET
  * @{
  */ 

/** @defgroup ARC_RETARGET_Private_TypesDefinitions
  * @{
  */
  
struct __FILE { int handle; /* Add whatever you need here */ };

/**
  * @}
  */

/** @defgroup ARC_RETARGET_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_RETARGET_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_RETARGET_Private_Variables
  * @{
  */ 
  
FILE __stdout;
FILE __stdin;

/**
  * @}
  */

/** @defgroup ARC_RETARGET_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_RETARGET_Private_Functions
  * @{
  */
  
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  ch: the char to be send.
  * @param  *f:
  * @retval the char that send out.
  */
int fputc(int ch, FILE *f) 
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    
    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
    }
    USART_SendData(USART1, (uint8_t) ch);

    return ch;
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  *f
  * @retval the char that received.
  */
int fgetc(FILE *f) 
{
    int ch;
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
    {
    }
    ch = USART_ReceiveData(USART1);
    
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
    }
    USART_SendData(USART1, (uint8_t) ch);
    return ch;
}


int ferror(FILE *f) 
{
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int c) 
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    USART_SendData(USART1, (uint8_t) c);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
    }
}


void _sys_exit(int return_code) 
{
    while(1)
    {
    }
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
