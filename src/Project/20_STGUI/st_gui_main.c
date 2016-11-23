/**
  ******************************************************************************
  * @file    TouchScreen_main.c 
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   main program body.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_SysTick.h"
#include "ARC_LCD_ST.h"
#include "ARC_USART.h"
#include "ARC_TouchScreen.h"
#include "ARC_SPI_Flash.h"
#include "ARC_Button_EXTI.h"
#include "graphicObject.h"
#include "JoyHal.h"
#include "cursor.h"
#include "uiframework.h"
#include <stdio.h>
#include <stdlib.h>

/** @addtogroup ARC_Examples
  * @{
  */

/** @addtogroup ARC_TS
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, the touch screen example.
  * @param  None
  * @retval None
  */
int main(void)
{
    ARC_SysTick_Init();
    ARC_COM_Init();
    USART_Cmd(USART1, ENABLE);
    ARC_LCD_Init();
    CursorInit(GL_NULL);
    Show_HomeScreen();
    CursorShow(200, 20);

    while(1) 
    {
    }                                               
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) www.armrunc.com *****END OF FILE****/
