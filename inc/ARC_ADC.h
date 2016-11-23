/**
  ******************************************************************************
  * @file    ARC_ADC.h
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
#ifndef __ARC_ADC_H
#define __ARC_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_ADC
  * @{
  */

/** @defgroup ARC_ADC_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_ADC_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_ADC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_ADC_Exported_Functions
  * @{
  */
void ARC_ADC_Init(void); 
void ARC_ADC_DMA_Init(uint16_t *MemoryBaseAddr, uint32_t BufferSize);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_ADC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/******************* (C) www.armrunc.com *****END OF FILE****/
