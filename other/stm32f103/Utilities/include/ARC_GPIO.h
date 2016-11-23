/**
  ******************************************************************************
  * @file    ARC_GPIO.h
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
#ifndef __ARC_GPIO_H
#define __ARC_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "ARC_LED.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_GPIO
  * @{
  */

/** @defgroup ARC_GPIO_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_GPIO_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_GPIO_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_GPIO_Exported_Functions
  * @{
  */

void ARC_LED_GPIO_Init(void);
void ARC_Button_GPIO_Init(void);
void ARC_SPI_GPIO_Init(void);
void ARC_LCD_GPIO_Init(void);
void ARC_I2C_GPIO_Init(void);
void ARC_TouchScreen_GPIO_Init(void);
void ARC_COM_GPIO_Init(void);
void ARC_SD_GPIO_Init(void);
void ARC_ADC_GPIO_Init(void);
void ARC_TIM_PWM_GPIO_Init(void);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_GPIO_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/******************* (C) www.armrunc.com *****END OF FILE****/
