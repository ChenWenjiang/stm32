/**
  ******************************************************************************
  * @file    ARC_EXTI.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides EXTI middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"

#include "ARC_GPIO.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_EXTI
  * @{
  */ 

/** @defgroup ARC_EXTI_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_EXTI_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_EXTI_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_EXTI_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup ARC_EXTI_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_EXTI_Private_Functions
  * @{
  */

/**
  * @brief  Initialize EXTI of push button.
  * @param  None
  * @retval None
  */
void ARC_Button_EXTI_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;

    /* Connect Button EXTI Line to Button GPIO Pin */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);

    /* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Connect Button EXTI Line to Button GPIO Pin */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);

    /* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_Init(&EXTI_InitStructure);
}


/**
  * @brief  Initialize EXTI of touch screen.
  * @param  None
  * @retval None
  */
void ARC_TouchScreen_EXTI_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;

    /* Connect Button EXTI Line to Button GPIO Pin */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource6);

    /* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line = EXTI_Line6;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

/**
  * @brief  Initialize EXTI of USB.
  * @param  None
  * @retval None
  */
void ARC_USB_EXTI_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    
    /* Configure the EXTI line 18 connected internally to the USB IP */
    EXTI_ClearITPendingBit(EXTI_Line18);
    EXTI_InitStructure.EXTI_Line = EXTI_Line18;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
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
