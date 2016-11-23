/**
  ******************************************************************************
  * @file    TIM_PWM_main.c 
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
#include "ARC_TIM_PWM.h"

/** @addtogroup ARC_Examples
  * @{
  */

/** @addtogroup ARC_TIM_PWM
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, configure TIM2 as PWM output, to drive LED0.
  * @param  None
  * @retval None
  */
int main(void)
{
    ARC_TIM_PWM_Init();
    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);
    
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
