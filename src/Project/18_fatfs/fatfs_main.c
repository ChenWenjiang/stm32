/**
  ******************************************************************************
  * @file    Fatfs_main.c 
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
#include "ARC_Fatfs.h"
#include "ARC_SD.h"
#include "ARC_USART.h"
#include "ARC_SysTick.h"
#include "ARC_SPI_Flash.h"
#include "ARC_TouchScreen.h"
#include "ARC_RCC.h"
#include "diskio.h"
#include <stdio.h>

/** @addtogroup ARC_Examples
  * @{
  */

/** @addtogroup ARC_SD
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, SD card SPI interface read example.
  * @param  None
  * @retval None
  */
int main(void)
{
    ARC_SysTick_Init();
    ARC_COM_Init();
    USART_Cmd(USART1, ENABLE);
    
    ARC_SD_SPI_Init();
    
    SPI_Cmd(SPI1, ENABLE); /*!< SD_SPI enable */
    
    ARC_DMA1_RCC_Init();
    
    while (1)
    {
        ARC_fat_menu_init();
        ARC_SysTick_Delay(1000);
    }  
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) www.armrunc.com *****END OF FILE****/
