/**
  ******************************************************************************
  * @file    IWDG_main.c 
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
#include "ARC_RCC.h"
#include "ARC_EXTI.h"
#include "ARC_GPIO.h"
#include "ARC_NVIC_API.h"
#include "ARC_Button_EXTI.h"
#include "ARC_SysTick.h"
#include "ARC_IWDG.h"
/** @addtogroup ARC_Examples
  * @{
  */

/** @addtogroup ARC_IWDG
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, IWDG example.
  * @param  None
  * @retval None
  */
int main(void)
{
    ARC_LED_Init();
    ARC_Button_Init();
    ARC_SysTick_Init();  
    ARC_IWDG_Init(IWDG_Prescaler_256, (2 * 40000 / 256));
    ARC_LED_Set(0, 1);
    ARC_LED_Set(1, 1);
    ARC_SysTick_Delay(1000);
    ARC_LED_Set(0, 0);
    ARC_LED_Set(1, 0);
    IWDG_Enable();
    while (1)
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
