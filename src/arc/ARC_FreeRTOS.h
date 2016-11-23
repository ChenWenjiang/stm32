/**
  ******************************************************************************
  * @file    ARC_FreeRTOS.h
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @date    10/21/2011
  * @brief   Header files for middleware.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ARC_FREE_RTOS_H
#define __ARC_FREE_RTOS_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_FREE_RTOS
  * @{
  */

/** @defgroup ARC_FREE_RTOS_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_FREE_RTOS_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_FREE_RTOS_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_FREE_RTOS_Exported_Functions
  * @{
  */

void vTask( void *pvParameters );

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_FREE_RTOS_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/******************* (C) www.armrunc.com *****END OF FILE****/
