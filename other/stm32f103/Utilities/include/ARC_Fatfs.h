/**
  ******************************************************************************
  * @file    ARC_Fatfs.h
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
#ifndef __ARC_FATFS_H
#define __ARC_FATFS_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_FATFS
  * @{
  */

/** @defgroup ARC_FATFS_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_FATFS_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_FATFS_Exported_Macros
  * @{
  */
#define FI 1
#define DI 2
/**
  * @}
  */

/** @defgroup ARC_FATFS_Exported_Functions
  * @{
  */

void ARC_fat_menu_init(void);

void ARC_Sys_Soft_Reset(void);

void ARC_format_disk(void);
void ARC_creat_file(void);
void ARC_delete_file(void);
void ARC_list_file(void);
void ARC_get_disk_info(void);
void ARC_creat_dir(void);
void ARC_edit_file(void);
void ARC_read_file(void);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_FATFS_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) www.armrunc.com *****END OF FILE****/
