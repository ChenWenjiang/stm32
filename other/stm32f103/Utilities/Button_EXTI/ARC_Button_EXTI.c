/**
  ******************************************************************************
  * @file    ARC_Button_EXTI.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides button EXTI middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_Button_EXTI.h"
#include "ARC_GPIO.h"
#include "ARC_RCC.h"
#include "ARC_EXTI.h"
#include "ARC_NVIC_API.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_Button_EXTI
  * @{
  */ 

/** @defgroup ARC_Button_EXTI_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_Button_EXTI_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_Button_EXTI_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_Button_EXTI_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup ARC_Button_EXTI_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_Button_EXTI_Private_Functions
  * @{
  */
  
/**
  * @brief  Initialize Button_EXTI. 
  * @param  None
  * @retval None
  */
void ARC_Button_Init()
{
    ARC_Button_RCC_Init();
    ARC_Button_GPIO_Init();
    ARC_Button_NVIC_Init();
    ARC_Button_EXTI_Init();
}

/**
  * @brief  get the state of button. 
  * @param  Button: the button which you want to get the state from.
  * @retval the state of the button.
  */
uint8_t ARC_Button_State(uint8_t Button)
{
    if (Button == 0)
        return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);
    else
        return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);
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
