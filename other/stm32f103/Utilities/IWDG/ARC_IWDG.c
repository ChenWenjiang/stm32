/**
  ******************************************************************************
  * @file    ARC_IWDG.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides IWDG middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_IWDG.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_IWDG
  * @{
  */ 

/** @defgroup ARC_IWDG_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_IWDG_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_IWDG_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_IWDG_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup ARC_IWDG_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_IWDG_Private_Functions
  * @{
  */

/**
  * @brief  Initialize IWDG.
  * @param  None
  * @retval None
  */
void ARC_IWDG_Init(uint8_t IWDG_Prescaler, uint16_t Reload)
{
    /* IWDG timeout equal to (Reload / (40KHz(LSI) / IWDG_Prescaler)) ms 
     (the timeout may varies due to LSI frequency dispersion) */
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    /* IWDG counter clock: 40KHz(LSI) / IWDG_Prescaler */
    IWDG_SetPrescaler(IWDG_Prescaler);

    /* Set counter reload value to Reload */
    IWDG_SetReload(Reload);

    /* Reload IWDG counter */
    IWDG_ReloadCounter();
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
