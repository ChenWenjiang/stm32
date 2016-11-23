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
#include "ARC_LCD.h"
#include "ARC_USART.h"
#include "ARC_TouchScreen.h"
#include "ARC_SPI_Flash.h"
#include "ARC_Button_EXTI.h"
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
    pen_state_struct *pen_st;
    pen_st = ARC_get_penstate();
    ARC_SysTick_Init();
    ARC_COM_Init();
    USART_Cmd(USART1, ENABLE);
    ARC_LCD_Init();
    ARC_LCD_On();
    ARC_TouchScreen_Init();
    SPI_Cmd(SPI1, ENABLE);
    ARC_TouchScreen_start();
    
    ARC_Button_Init();

    ARC_LCD_Clear(LCD_COLOR_RED);
    ARC_LCD_ShowString(3, 3, "clear");
    
    while(1) 
    {
        if (pen_st->force_adjust == 1)
        {
            ARC_TouchScreen_Adjust();
            pen_st->force_adjust = 0;
            ARC_LCD_Clear(LCD_COLOR_RED);
            ARC_LCD_ShowString(3, 3, "clear");
        }
        if (pen_st->pen_pressed == KEY_DOWN)
        {
            pen_st->pen_pressed = KEY_UP;
            while(!ARC_PEN_STATE())
            {
                if(ARC_TouchScreen_Rd_LCD_XY())
                {
                    if((abs(pen_st->x_converted - 20) < 18) && 
                       (abs(pen_st->y_converted - 8) < 6))
                    {
                        ARC_LCD_Clear(LCD_COLOR_RED);
                        ARC_LCD_ShowString(3, 3, "clear");
                    }
                    else if((abs(pen_st->x_converted - LCD_XSIZE / 2) < LCD_XSIZE / 2) && 
                            (abs(pen_st->y_converted - LCD_YSIZE / 2) < LCD_YSIZE / 2))
                    {
                        ARC_LCD_DrawBigPoint(pen_st->x_converted, pen_st->y_converted, LCD_COLOR_WHITE);
                    }
                }
            }
        }
    }                                               
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) www.armrunc.com *****END OF FILE****/
