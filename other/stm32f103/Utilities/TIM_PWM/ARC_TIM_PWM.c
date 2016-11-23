/**
  ******************************************************************************
  * @file    ARC_TIM_PWM.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides TIM PWM middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_GPIO.h"
#include "ARC_RCC.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_TIM_PWM
  * @{
  */ 

/** @defgroup ARC_TIM_PWM_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_TIM_PWM_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_TIM_PWM_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_TIM_PWM_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup ARC_TIM_PWM_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/**
  * @brief  Initialize TIM PWM parameters.
  * @param  None
  * @retval None
  */
void ARC_TIM_PWM_PARAM_Init()
{
    /* -----------------------------------------------------------------------
    TIM2 Configuration: generate 1 PWM signals:
    The TIM2CLK frequency is set to SystemCoreClock (72MHz), to get TIM2 counter
    clock at 1 MHz the Prescaler is computed as following:
        - Prescaler = (TIM2CLK / TIM2 counter clock) - 1

    The TIM2 is running at 1 KHz: TIM2 Frequency = TIM2 counter clock/(ARR + 1)
                                                  = 1 MHz / (999 + 1) = 1 KHz

    TIM3 Channel2 duty cycle = TIM2_CCR2 / TIM2_ARR = 800 / 999 = 80%

    ----------------------------------------------------------------------- */
    uint16_t PrescalerValue = 0;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef         TIM_OCInitStructure;

    /* Compute the prescaler value */
    PrescalerValue = (uint16_t) (SystemCoreClock / 1000000) - 1;
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 999;
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration: Channel2 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 900;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC2Init(TIM2, &TIM_OCInitStructure);

    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM2, ENABLE);
}

/**
  * @brief  Initialize TIM PWM.
  * @param  None
  * @retval None
  */
void ARC_TIM_PWM_Init()
{
    ARC_TIM_PWM_RCC_Init();
    ARC_TIM_PWM_GPIO_Init();
    ARC_TIM_PWM_PARAM_Init();
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
