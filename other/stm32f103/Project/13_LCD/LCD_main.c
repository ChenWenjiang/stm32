/**
  ******************************************************************************
  * @file    LCD_main.c 
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

/** @addtogroup ARC_Examples
  * @{
  */

/** @addtogroup ARC_LCD
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, show strings on LCD screen.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint16_t x = 0;
    ARC_SysTick_Init();
    
    ARC_COM_Init();
    USART_Cmd(USART1, ENABLE);
    
    ARC_LCD_Init();
    ARC_LCD_On();
    while(1) 
    {
        switch(x)
        {
            case 0:
                ARC_LCD_Clear(LCD_COLOR_BLACK);
                break;
            case 1:
                ARC_LCD_Clear(LCD_COLOR_MAGENTA);
                break;
            case 2:
                ARC_LCD_Clear(LCD_COLOR_GREEN);
                break;
            case 3:
                ARC_LCD_Clear(LCD_COLOR_RED);
                break;
            case 4:
                ARC_LCD_Clear(LCD_COLOR_BLUE);
                break;
        }
        
        x++;
        x = (x > 4) ? 0 : x;

        ARC_LCD_ShowString(30, 50, "ARC STM32");

        ARC_LCD_ShowString(30, 70, "TFT LCD Example");
        
        ARC_LCD_ShowString(30, 90, "www.armrunc.com");
        
        ARC_LCD_ShowString(30, 110, "http://armrunc.taobao.com");
        ARC_SysTick_Delay(2000);
    }                                               
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) www.armrunc.com *****END OF FILE****/
