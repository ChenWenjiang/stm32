/**
  ******************************************************************************
  * @file    ARC_RTC.h
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
#ifndef __ARC_RTC_H
#define __ARC_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_RTC
  * @{
  */

/** @defgroup ARC_RTC_Exported_Types
  * @{
  */
typedef struct 
{
    uint16_t year;  /* 1..4095 */
    uint8_t  month; /* 1..12 */
    uint8_t  mday;  /* 1..31 */
    uint8_t  wday;  /* 0..6, Sunday = 0*/
    uint8_t  hour;  /* 0..23 */
    uint8_t  min;   /* 0..59 */
    uint8_t  sec;   /* 0..59 */
    //uint8_t  dst;   /* 0 Winter, !=0 Summer */
} RTC_t;

/**
  * @}
  */

/** @defgroup ARC_RTC_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_RTC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_RTC_Exported_Functions
  * @{
  */
void ARC_RTC_Init(void); 
void ARC_RTC_gettime (RTC_t*);              /* Get time */
void ARC_RTC_settime (const RTC_t*);        /* Set time */

 
/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_RTC_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 
/******************* (C) www.armrunc.com *****END OF FILE****/
