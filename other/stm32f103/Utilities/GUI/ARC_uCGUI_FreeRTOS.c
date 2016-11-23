/**
  ******************************************************************************
  * @file    ARC_uCGUI_FreeRTOS.c
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
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "GUI_Private.h"
#include "ARC_SysTick.h"
#include <stdio.h>


/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_UCGUI_FREERTOS
  * @{
  */ 

/** @defgroup ARC_UCGUI_FREERTOS_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_UCGUI_FREERTOS_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_UCGUI_FREERTOS_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_UCGUI_FREERTOS_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup ARC_UCGUI_FREERTOS_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_UCGUI_FREERTOS_Private_Functions
  * @{
  */
  
#include "FreeRTOS.h"
#include "GUI_Private.H"
#include <stdio.h>

/*
*********************************************************************************************************
*                                         GLOBAL VARIABLES
*********************************************************************************************************
*/
static xSemaphoreHandle dispSem;
static xSemaphoreHandle dispBinarySem;

/*
*********************************************************************************************************
*                                        TIMING FUNCTIONS
*
* Notes: Some timing dependent routines of uC/GUI require a GetTime and delay funtion. 
*        Default time unit (tick), normally is 1 ms.
*********************************************************************************************************
*/

int  GUI_X_GetTime (void) 
{
    return ((int)xTaskGetTickCount());
}


void  GUI_X_Delay (int period) 
{
    ARC_SysTick_Delay(period);
}


/*
*********************************************************************************************************
*                                          GUI_X_ExecIdle()
*********************************************************************************************************
*/
void GUI_X_ExecIdle (void) 
{
    ARC_SysTick_Delay(1);
}

/*
*********************************************************************************************************
*                                    MULTITASKING INTERFACE FUNCTIONS
*
* Note(1): 1) The following routines are required only if uC/GUI is used in a true multi task environment, 
*             which means you have more than one thread using the uC/GUI API.  In this case the #define 
*             GUI_OS 1   needs to be in GUIConf.h
*********************************************************************************************************
*/

void  GUI_X_InitOS (void)
{
    dispSem = xSemaphoreCreateMutex();
    vSemaphoreCreateBinary( dispBinarySem );
}


void  GUI_X_Lock (void)
{
    xSemaphoreTake(dispSem, portMAX_DELAY);
}


void  GUI_X_Unlock (void)
{ 
    xSemaphoreGive(dispSem);
}


U32  GUI_X_GetTaskId (void) 
{
    return (uint32_t)uxTaskGetTaskNumber(NULL);
}

void GUI_X_WaitEvent(void)
{
    xSemaphoreTake(dispBinarySem, portMAX_DELAY);
}

void GUI_X_SignalEvent(void)
{
    xSemaphoreGive(dispBinarySem);
}

void GUI_X_Init (void) 
{
}

void GUI_X_Log(const char *s) 
{ 
    GUI_USE_PARA(s); 
}

void GUI_X_Warn(const char *s) 
{
    GUI_USE_PARA(s); 
}

void GUI_X_ErrorOut(const char *s)
{ 
    GUI_USE_PARA(s); 
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

