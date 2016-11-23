/*******************************************************************************
* @file		: uiframework.c
* @author	: IMS Systems LAB & Technical Marketing
* @version	: V1.0.0
* @date		: 12-May-2012
* @brief	: Screen Code
*******************************************************************************/
/* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
*******************************************************************************
*/ 
/*includes----------------------------------------------------------------------*/
#include "uiframework.h"
#include "uiappuser.h"
#include "float.h"
#include "LcdHal.h"
#include "TscHal.h"
#include "pictures.h"

GL_Page_TypeDef *CurrentScreen;

/** @addtogroup Embedded_GUI_Example
  * @{
  */

/** @defgroup UI_Framework
  * @brief This file contains functions to configure the screens and controls
  * @{
  */

/* External variables ----------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------*/
/* Private defines -------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------*/
GL_Page_TypeDef Iphone;
/* Private function prototypes -------------------------------------------------*/
/* Private functions -----------------------------------------------------------*/
/**
  * @brief Create and configure screen object
  * @note This control creates the screen object and configures contained controls
  * @param None
  * @retval None
  */
void Create_Iphone() 
{ 

	GL_PageControls_TypeDef* DesignIcon06= NewIcon (1,DesignIcon06_Image,204,204,Iphone_DesignIcon06_Click);
	GL_PageControls_TypeDef* DesignLabel01= NewLabel(2,"Compass",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel01Color);
	Create_PageObj( &Iphone ); 
	AddPageControlObj(263,8,DesignIcon06,&Iphone);
	AddPageControlObj(191,216,DesignLabel01,&Iphone);
}




/**
  * @brief Show screen object
  * @note This control displayed the specified screen object
  * @param None
  * @retval None
  */
void Show_Iphone()
{ 
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	GL_Clear(65535);
	GL_SetTextColor(63488);
	Iphone.ShowPage(&Iphone, GL_TRUE);
	CurrentScreen=&Iphone; 
} 

/**
  * @brief Controls home screen
  * @param None
  * @retval None
  */
void Show_HomeScreen()
{
	Create_Iphone();
	CurrentScreen = &Iphone;
	GL_Clear(65535);
	GL_SetTextColor(63488);
	Iphone.ShowPage(&Iphone,GL_TRUE);
}

/**
  * @}
  */

/**
  * @}
  */


/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/ 

