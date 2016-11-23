/**
  ******************************************************************************
  * @file    ARC_SysTick.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides SysTick middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_SysTick.h"
#ifdef ARC_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_SYSTICK
  * @{
  */ 
      
/** @defgroup SYSTICK_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup SYSTICK_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup SYSTICK_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup SYSTICK_Private_Variables
  * @{
  */ 

static uint32_t __IO TimingDelay;
  
/**
  * @}
  */

/** @defgroup SYSTICK_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup SYSTICK_Private_Functions
  * @{
  */

#ifndef ARC_FREERTOS
/**
  * @brief  Setup SysTick Timer as 1 msec interrupts
  * @param  None
  * @retval None
  */
void ARC_SysTick_Init()
{
    if (SysTick_Config(SystemCoreClock / 1000))
    { 
        /* Capture error */ 
        while (1);
    }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void ARC_SysTick_Delay(__IO uint32_t nTime)
{ 
    ARC_Set_TimingDelay( nTime );

    while(ARC_Get_TimingDelay() != 0);
}

/**
  * @brief  This function sets the static timingDelay variable.
  * @param  timing_Delay
  * @retval None
  */
void ARC_Set_TimingDelay(uint32_t __IO timing_Delay)
{
    TimingDelay = timing_Delay;
}

/**
  * @brief  This function gets the static timingDelay variable.
  * @param  None
  * @retval Current TimingDelay
  */
uint32_t ARC_Get_TimingDelay()
{
    return TimingDelay;
}

/**
  * @brief  This function gets the static timingDelay variable.
  * @param  None
  * @retval Current TimingDelay
  */
void ARC_Decrease_TimingDelay()
{
    TimingDelay--;
}

#endif
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
