/**
  ******************************************************************************
  * @file    ARC_USART.h
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
#ifndef __ARC_USART_H
#define __ARC_USART_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
//#include <stdio.h>

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_USART
  * @{
  */

/** @defgroup ARC_USART_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_USART_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_USART_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_USART_Exported_Functions
  * @{
  */
void ARC_COM_Init(void);
#ifdef USART1_IRQ
void ARC_COM_NVIC_Init(void);
#endif
/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_USART_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/******************* (C) www.armrunc.com *****END OF FILE****/
