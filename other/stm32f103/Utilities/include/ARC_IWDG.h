/**
  ******************************************************************************
  * @file    ARC_IWDG.h
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
#ifndef __ARC_IWDG_H
#define __ARC_IWDG_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_IWDG
  * @{
  */

/** @defgroup ARC_IWDG_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_IWDG_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_IWDG_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_IWDG_Exported_Functions
  * @{
  */
void ARC_IWDG_Init(uint8_t IWDG_Prescaler, uint16_t Reload);
 
/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_IWDG_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/******************* (C) www.armrunc.com *****END OF FILE****/
