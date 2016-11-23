/**
  ******************************************************************************
  * @file    LED_main.c 
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
#include "ARC_LED.h"
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
  * @brief  Main program, flash LED0 and LED1.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint32_t i;
    ARC_LED_Init();
    while (1)
    {
        ARC_LED_Set(0, 1);
        ARC_LED_Set(1, 0);
        for( i = 0; i < 5000000; i++);        
        ARC_LED_Set(0, 0);
        ARC_LED_Set(1, 1);
        for( i = 0; i < 5000000; i++);        
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
