/**
  ******************************************************************************
  * @file    ARC_DAM.h
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
#ifndef __ARC_DAM_H
#define __ARC_DAM_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_DAM
  * @{
  */

/** @defgroup ARC_DAM_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_DAM_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_DAM_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_DAM_Exported_Functions
  * @{
  */
void ARC_DMA1_Ch2_Param_Init(const uint8_t *MemoryBaseAddr, uint32_t BufferSize);
void ARC_DMA1_Ch3_Param_Init(const uint8_t *MemoryBaseAddr, uint32_t BufferSize, uint32_t memIncEnable);
void ARC_DMA1_Ch4_Param_Init(const uint8_t *MemoryBaseAddr, uint32_t BufferSize);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_DAM_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/******************* (C) www.armrunc.com *****END OF FILE****/
