/**
  ******************************************************************************
  * @file    ARC_NVIC_API.h
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
#ifndef __ARC_NVIC_API_H
#define __ARC_NVIC_API_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_NVIC_API
  * @{
  */

/** @defgroup ARC_NVIC_API_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_NVIC_API_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_NVIC_API_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_NVIC_API_Exported_Functions
  * @{
  */
  
void ARC_NVIC_API_Init(void); 
void ARC_Button_NVIC_Init(void);
void ARC_I2C_NVIC_Init(void);
void ARC_TouchScreen_NVIC_Init(void);
void ARC_USB_NVIC_Init(void);
void ARC_ADC_NVIC_Init(void);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_NVIC_API_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/******************* (C) www.armrunc.com *****END OF FILE****/
