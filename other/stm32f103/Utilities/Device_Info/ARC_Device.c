/**
  ******************************************************************************
  * @file    ARC_Device.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides ADC middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_Device.h"
#include <stdio.h>

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_DEVICE
  * @{
  */ 

/** @defgroup ARC_DEVICE_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_DEVICE_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_DEVICE_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_DEVICE_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup ARC_DEVICE_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_DEVICE_Private_Functions
  * @{
  */
  
/**
  * @brief  Get the unique serial number of the chip.
  * @param  None
  * @retval None
  */
void ARC_Get_SerialNum(void)
{
    uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

    Device_Serial0 = *(__I uint32_t*)(0x1FFFF7E8);
    Device_Serial1 = *(__I uint32_t*)(0x1FFFF7EC);
    Device_Serial2 = *(__I uint32_t*)(0x1FFFF7F0);
    printf("ST device ID: 0x%08X", Device_Serial0);
    printf("%08X", Device_Serial1);
    printf("%08X\n", Device_Serial2);
}

/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */  
/******************* (C) www.armrunc.com *****END OF FILE****/
