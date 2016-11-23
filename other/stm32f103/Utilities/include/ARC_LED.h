/**
  ******************************************************************************
  * @file    ARC_LED.h
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
#ifndef __ARC_LED_H
#define __ARC_LED_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_LED
  * @{
  */

/** @defgroup ARC_LED_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_LED_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_LED_Exported_Macros
  * @{
  */
  
/**
  * @}
  */

/** @defgroup ARC_LED_Exported_Functions
  * @{
  */
  
void ARC_LED_Init(void); 
void ARC_LED_Set(uint8_t LED, uint8_t value);
void ARC_LED_Toggle(uint8_t LED);


/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_LED_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/******************* (C) www.armrunc.com *****END OF FILE****/
