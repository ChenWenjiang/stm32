/**
  ******************************************************************************
  * @file    LcdHal.h
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    11-July-2011
  * @brief   This file contains all the LCD functions whose
  *          implementation depends on the LCD Type used in your Application.
  *          You only need to change these functions implementations
  *          in order to reuse this code with other LCD
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion ---------------------------------------*/
#ifndef __LCD_HAL_H
#define __LCD_HAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32HAL.h"
#include "ARC_LCD_ST.h"
#include "ARC_SysTick.h"
#include "graphicObjectTypes.h"

/** @addtogroup Embedded_GUI_Library
  * @{
  */

/** @addtogroup LcdHal 
  * @{
  */ 

/** @defgroup LcdHal_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup LcdHal_Imported_Variables
  * @{
  */
/**
  * @}
  */

/** @defgroup LcdHal_Exported_Constants
  * @{
  */

#define GL_Clear                        ARC_LCD_Clear
#define GL_LCD_DrawCharTransparent      ARC_LCD_DrawCharTransparent
#define GL_DisplayAdjStringLine         ARC_LCD_DisplayAdjStringLine
#define GL_LCD_DisplayChar              ARC_LCD_DisplayChar
#define GL_SetDisplayWindow             ARC_LCD_SetDisplayWindow
#define GL_DrawLine                     ARC_LCD_DrawLine
#define GL_LCD_DrawRect                 ARC_LCD_DrawRect
#define GL_LCD_DrawCircle               ARC_LCD_DrawCircle
#define GL_DrawBMP                      ARC_LCD_DrawBMP
#define GL_SetFont                      ARC_LCD_SetFont
#define GL_BackLightSwitch              ARC_LCD_BackLightSwitch
#define GL_LCD_Init                     ARC_LCD_Init
#define GL_LCD_WindowModeDisable        ARC_LCD_WindowModeDisable
#define LCD_PutPixel                    ARC_LCD_PutPixel
#define LCD_GetPixel                    ARC_LCD_GetPixel
#define GL_LCD_DrawChar                 ARC_LCD_DrawChar
#define GL_LCD_ReadRAM                  ARC_LCD_ReadRAM
#define LCD_Change_Direction            ARC_LCD_Change_Direction
#define LCD_WriteChar                   ARC_LCD_WriteChar
#define LCD_PrintChar                   ARC_LCD_PrintChar
#define LCD_PrintStringLine             ARC_LCD_PrintStringLine
#define LCD_DrawMonoBMP                 ARC_LCD_DrawMonoBMP
#define LCD_FillArea                    ARC_LCD_FillArea
#define LCD_DrawColorBMP                ARC_LCD_DrawColorBMP
#define GL_SetBackColor                 ARC_LCD_SetBackColor
#define GL_LCD_GetTextColor             ARC_LCD_GetTextColor
#define GL_SetTextColor                 ARC_LCD_SetTextColor

#define GL_OFF                          LCD_BACKLIGHT_OFF
#define GL_ON                           LCD_BACKLIGHT_ON

/* LCD color */
#define GL_White                        LCD_COLOR_WHITE
#define GL_Black                        LCD_COLOR_BLACK
#define GL_Grey                         LCD_COLOR_GREY
#define GL_Blue                         LCD_COLOR_BLUE
#define GL_Blue2                        LCD_COLOR_BLUE2
#define GL_Red                          LCD_COLOR_RED
#define GL_Magenta                      LCD_COLOR_MAGENTA
#define GL_Green                        LCD_COLOR_GREEN
#define GL_Cyan                         LCD_COLOR_CYAN
#define GL_Yellow                       LCD_COLOR_YELLOW

#define GL_Horizontal                   LCD_DIR_HORIZONTAL
#define GL_Vertical                     LCD_DIR_VERTICAL

#define GL_FONT_BIG                     LCD_FONT_BIG
#define GL_FONT_SMALL                   LCD_FONT_SMALL
#define GL_FONT_BIG_WIDTH               LCD_FONT_BIG_WIDTH
#define GL_FONT_BIG_HEIGHT              LCD_FONT_BIG_HEIGHT
#define GL_FONT_SMALL_WIDTH             LCD_FONT_SMALL_WIDTH
#define GL_FONT_SMALL_HEIGHT            LCD_FONT_SMALL_HEIGHT

#define FirstPixel                      LCD_FirstPixel
#define MiddlePixel                     LCD_MiddlePixel
#define LastPixel                       LCD_LastPixel
#define SinglePixel                     LCD_SinglePixel

/**
  * @}
  */

/** @defgroup LcdHal_Exported_Variables
  * @{
  */
/**
  * @}
  */

/** @defgroup LcdHal_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LcdHal_Exported_Functions
  * @{
  */

#ifdef __cplusplus
}
#endif

#endif /*__LCD_HAL_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
