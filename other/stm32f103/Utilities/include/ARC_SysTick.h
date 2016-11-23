/**
  ******************************************************************************
  * @file    ARC_SysTick.h
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   Header files for middleware.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ARC_SYSTICK_H
#define __ARC_SYSTICK_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
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

/** @defgroup SYSTICK_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup SYSTICK_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup SYSTICK_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup SYSTICK_Exported_Functions
  * @{
  */
#ifndef ARC_FREERTOS
void ARC_SysTick_Delay(__IO uint32_t nTime);
void ARC_SysTick_Init(void);
void ARC_Set_TimingDelay(uint32_t __IO timing_Delay);
uint32_t ARC_Get_TimingDelay(void);
void ARC_Decrease_TimingDelay(void);
#else
#define ARC_SysTick_Delay vTaskDelay
#endif
/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_SYSTICK_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/******************* (C) www.armrunc.com *****END OF FILE****/
