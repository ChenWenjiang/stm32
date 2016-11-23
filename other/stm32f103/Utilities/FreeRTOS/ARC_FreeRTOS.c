/**
  ******************************************************************************
  * @file    ARC_FreeRTOS.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @date    10/21/2011
  * @brief   ARC middle layer. 
  *          This file provides FreeRTOS middle layer functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "ARC_LED.h"
#include "ARC_FreeRTOS.h"
#include "ARC_SysTick.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_FREE_RTOS
  * @{
  */ 

/** @defgroup ARC_FREE_RTOS_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_FREE_RTOS_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_FREE_RTOS_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_FREE_RTOS_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup ARC_FREE_RTOS_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_FREE_RTOS_Private_Functions
  * @{
  */

/**
  * @brief  Toggle LED0/LED1.
  * @param  *pvParameters: the task parameters.
  * @retval None
  */
void vTask( void *pvParameters )
{
    /* As per most tasks, this task is implemented in an infinite loop. */
    while(1)
    {
        ARC_LED_Toggle(0);
        ARC_SysTick_Delay(800);
    }
}

/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
    /* This function will only be called if an API call to create a task, queue
       or semaphore fails because there is too little heap RAM remaining - and
       configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. */
        while(1)
        {
        }
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
    /* This function will only be called if a task overflows its stack.  Note
       that stack overflow checking does slow down the context switch
       implementation and will only be performed if configCHECK_FOR_STACK_OVERFLOW
       is set to either 1 or 2 in FreeRTOSConfig.h. */
    while(1)
    {
    }
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
    /* This example does not use the idle hook to perform any processing.  The
       idle hook will only be called if configUSE_IDLE_HOOK is set to 1 in 
       FreeRTOSConfig.h. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
    /* This example does not use the tick hook to perform any processing.   The
       tick hook will only be called if configUSE_TICK_HOOK is set to 1 in
       FreeRTOSConfig.h. */
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
