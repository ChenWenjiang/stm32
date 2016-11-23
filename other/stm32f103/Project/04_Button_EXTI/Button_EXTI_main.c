/**
  ******************************************************************************
  * @file    Button_EXTI_main.c 
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
#include "ARC_Button_EXTI.h"

/** @addtogroup ARC_Examples
  * @{
  */

/** @addtogroup ARC_Button_EXTI
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, EXTI example.
  * @param  None
  * @retval None
  */
int main(void)
{     
    ARC_LED_Init();
    ARC_Button_Init();  
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
