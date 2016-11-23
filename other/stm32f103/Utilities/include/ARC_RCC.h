/**
  ******************************************************************************
  * @file    ARC_RCC.h
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
#ifndef __ARC_RCC_H
#define __ARC_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_RCC
  * @{
  */

/** @defgroup ARC_RCC_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_RCC_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_RCC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_RCC_Exported_Functions
  * @{
  */
  
void ARC_LED_RCC_Init(void);
void ARC_Button_RCC_Init(void);
void ARC_SPI_RCC_Init(void);
void ARC_LCD_RCC_Init(void);
void ARC_I2C_RCC_Init(void);
void ARC_TouchScreen_RCC_Init(void);
void ARC_TIM_PWM_RCC_Init(void);
void ARC_COM_RCC_Init(void);
void ARC_ADC_RCC_Init(void);
void ARC_DMA1_RCC_Init(void);
void ARC_USB_RCC_Init(void);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_RCC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) www.armrunc.com *****END OF FILE****/
