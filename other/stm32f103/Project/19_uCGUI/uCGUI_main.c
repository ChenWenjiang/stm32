/**
  ******************************************************************************
  * @file    uCGUI_main.c 
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
#include "FreeRTOS.h"
#include "task.h"
#include "GUIDEMO.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
  * @brief  Initialize take.
  */
void InitTask ( void *pvParameters )
{
    portBASE_TYPE task_error;
    ARC_Button_Init();
    ARC_COM_Init();
    USART_Cmd(USART1, ENABLE);
    
    task_error = xTaskCreate(uCGUI, "uCGUI task", (1 * 1024), NULL, 8, NULL );
    assert( task_error == pdPASS);
    
    vTaskDelete(NULL);
}

/**
  * @brief  Main program, the touch screen example.
  * @param  None
  * @retval None
  */
int main(void)
{
    
    portBASE_TYPE task_error;
    task_error = xTaskCreate(InitTask, "Init task", (200), NULL, 0, NULL );
    
    assert( task_error == pdPASS);
    vTaskStartScheduler();
    assert(0);
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) www.armrunc.com *****END OF FILE****/
