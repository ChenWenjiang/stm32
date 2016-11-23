/**
  ******************************************************************************
  * @file    RTC_main.c 
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
#include "stm32f10x_usart.h"
#include "ARC_LED.h"
#include "ARC_RTC.h"
#include "ARC_SysTick.h"
#include "ARC_USART.h"
#include "stdio.h"
/** @addtogroup ARC_Examples
  * @{
  */

/** @addtogroup ARC_GPIO
  * @{
  */

/** @addtogroup ARC_GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, RTC example.
  * @param  None
  * @retval None
  */
int main(void)
{
    RTC_t rtc;
    ARC_RTC_Init();
    ARC_SysTick_Init();
    ARC_COM_Init();
    USART_Cmd(USART1, ENABLE);
    while (1)
    {
        ARC_RTC_gettime(&rtc);
        ARC_SysTick_Delay(1000);
        printf("%d-%d-%d %d:%d:%d\n", rtc.year, rtc.month, rtc.mday, rtc.hour, rtc.min, rtc.sec);
    }
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
