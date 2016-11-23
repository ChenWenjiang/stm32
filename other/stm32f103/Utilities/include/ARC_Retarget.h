/**
  ******************************************************************************
  * @file    ARC_Retarget.h
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
#ifndef __ARC_RETARGET_H
#define __ARC_RETARGET_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_RETARGET
  * @{
  */

/** @defgroup ARC_RETARGET_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_RETARGET_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_RETARGET_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_RETARGET_Exported_Functions
  * @{
  */
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
int ferror(FILE *f);
void _ttywrch(int ch);
void _sys_exit(int return_code);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_RETARGET_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/******************* (C) www.armrunc.com *****END OF FILE****/
