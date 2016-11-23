/**
  ******************************************************************************
  * @file    ARC_Debug.c
  * @author  MCD Application Team
  * @version V4.3.0
  * @date    10/15/2010
  * @brief   STM32xx-EVAL abstraction layer. 
  *          This file should be added to the main application to use the provided
  *          functions that manage Leds, push-buttons, COM ports and low level 
  *          HW resources initialization of the different modules available on
  *          STM32 evaluation boards from STMicroelectronics.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_DEBUG
  * @{
  */ 

/** @defgroup ARC_DEBUG_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_DEBUG_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_DEBUG_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_DEBUG_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup ARC_DEBUG_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_DEBUG_Private_Functions
  * @{
  */
  
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
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
    
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
