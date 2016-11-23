/**
  ******************************************************************************
  * @file    DAM_main.c 
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
#include "ARC_USART.h"
#include "ARC_DMA.h"
#include "ARC_SysTick.h"
#include "stdio.h"

/** @addtogroup ARC_Examples
  * @{
  */

/** @addtogroup ARC_DAM
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, Memory to USART DMA example.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint8_t CharDMA[] = "Memory to USART DMA example\n";
    uint32_t CharCount = sizeof(CharDMA) - 1;

    ARC_COM_Init();
    USART_Cmd(USART1, ENABLE);
    ARC_DMA1_RCC_Init();
    ARC_DMA1_Ch4_Param_Init(CharDMA, CharCount);

    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

    DMA_Cmd(DMA1_Channel4, ENABLE);

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
