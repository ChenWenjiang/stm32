/**
  ******************************************************************************
  * @file    ARC_LED.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides LED middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_LED.h"
#include "ARC_RCC.h"
#include "ARC_GPIO.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_LED
  * @{
  */ 

/** @defgroup ARC_LED_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_LED_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_LED_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_LED_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup ARC_LED_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_LED_Private_Functions
  * @{
  */
  
/**
  * @brief  Initialize LED.
  * @param  None
  * @retval None
  */
void ARC_LED_Init()
{
    ARC_LED_RCC_Init();
    ARC_LED_GPIO_Init();
}

/**
  * @brief  set/reset LED0/LED1.
  * @param  LED: Indicate the LED number, either 0 or 1.
  * @param  value: the output of LED0/LED1, either 0 or 1.
  * @retval None
  */
void ARC_LED_Set(uint8_t LED, uint8_t value)
{
    if (LED == 0)
    {
        if (value == 0)
            GPIO_ResetBits(GPIOA, GPIO_Pin_1);
        else if (value == 1)
            GPIO_SetBits(GPIOA, GPIO_Pin_1);
    }
    else if (LED == 1)
    {
        if (value == 0)
            GPIO_ResetBits(GPIOA, GPIO_Pin_2);
        else if (value == 1)
            GPIO_SetBits(GPIOA, GPIO_Pin_2);
    }
}

/**
  * @brief  Toggle LED0/LED1.
  * @param  LED: Indicate the LED number, either 0 or 1.
  * @retval None
  */
void ARC_LED_Toggle(uint8_t LED)
{
    if(LED == 0)
        GPIOA->ODR ^= GPIO_Pin_1;
    else if (LED == 1)
        GPIOA->ODR ^= GPIO_Pin_2;
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
