/**
  ******************************************************************************
  * @file    ARC_EEPROM.h
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
#ifndef __ARC_EEPROM_H
#define __ARC_EEPROM_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_EEPROM
  * @{
  */

/** @defgroup ARC_EEPROM_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_EEPROM_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_EEPROM_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_EEPROM_Exported_Functions
  * @{
  */
  
void ARC_EEPROM_Write(uint8_t *EEPBuff, uint32_t SubAdd, uint32_t EEPSize);
void ARC_EEPROM_Read(uint8_t *RXEEPBuff, uint32_t SubAdd, uint32_t EEPSize);
/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_EEPROM_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/******************* (C) www.armrunc.com *****END OF FILE****/
