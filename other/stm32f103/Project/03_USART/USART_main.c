/**
  ******************************************************************************
  * @file    USART_main.c 
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
#include "ARC_USART.h"
#include "ARC_SysTick.h"
#include "ARC_Retarget.h"

/** @addtogroup ARC_Examples
  * @{
  */

/** @addtogroup ARC_USART
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, retargeting the standard C printf and scanf
            to  UART output.
  * @param  None
  * @retval None
  */
int main(void)
{
    char str[80];
    ARC_COM_Init();
    /* Enable USART */
    USART_Cmd(USART1, ENABLE);

    while (1)
    {
        printf("\ninput your string, max: 80\n");
        scanf("%[^\n]",str);
        printf("your input string is\n%s\n", str);
    }  
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) www.armrunc.com *****END OF FILE****/
