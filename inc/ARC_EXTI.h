/**
  ******************************************************************************
  * @file    ARC_EXTI.h
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
#ifndef __ARC_EXTI_H
#define __ARC_EXTI_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_EXTI
  * @{
  */

/** @defgroup ARC_EXTI_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_EXTI_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_EXTI_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_EXTI_Exported_Functions
  * @{
  */
  
void ARC_Button_EXTI_Init(void);
void ARC_TouchScreen_EXTI_Init(void);
void ARC_USB_EXTI_Init(void);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_EXTI_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/******************* (C) www.armrunc.com *****END OF FILE****/
