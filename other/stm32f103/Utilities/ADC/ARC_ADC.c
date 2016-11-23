/**
  ******************************************************************************
  * @file    ARC_ADC.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides ADC middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_ADC.h"
#include "ARC_GPIO.h"
#include "ARC_RCC.h"
#include "ARC_NVIC_API.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_ADC
  * @{
  */ 

/** @defgroup ARC_ADC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_ADC_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_ADC_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_ADC_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup ARC_ADC_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_ADC_Private_Functions
  * @{
  */

/**
  * @brief  Configures the ADC parameters.
  * @param  None
  * @retval None
  */
void ARC_ADC_PARAM_Init()
{
    ADC_InitTypeDef ADC_InitStructure;

    /* ADC1 configuration ------------------------------------------------------*/
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
}

/**
  * @brief  Initialize ADC.
  * @param  None
  * @retval None
  */
void ARC_ADC_Init()
{
    ARC_ADC_RCC_Init();
    ARC_ADC_GPIO_Init();
    ARC_ADC_PARAM_Init();
    ARC_ADC_NVIC_Init();
    /* ADC1 regular channels configuration */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 1, ADC_SampleTime_55Cycles5);
    /* Enable ADC1 EOC interrupt */
    ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
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
