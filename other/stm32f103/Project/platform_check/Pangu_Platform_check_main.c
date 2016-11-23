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
#include "ARC_LED.h"
#include "ARC_TIM_PWM.h"
#include "ARC_RTC.h"
#include "ARC_EEPROM.h"
#include "ARC_I2C.h"
#include "ARC_SD.h"
#include "ARC_Device.h"
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
#include <string.h>


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
    uint8_t TxBuffer[] = "ARC STM32, I2C example.";
    uint8_t RxBuffer[100] = "EEPROM not present\n";
    uint16_t Buffer_Size = sizeof(TxBuffer) / sizeof(*(TxBuffer));
    uint32_t cur_time, i;
    portBASE_TYPE task_error;
    SD_Card_Type SD_CT = SD_Unknown;
    
    ARC_Button_Init();
    ARC_LED_Init();

    ARC_COM_Init();
    USART_Cmd(USART1, ENABLE);
    
    ARC_TIM_PWM_Init();
    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);
    
    ARC_RTC_Init();

    ARC_I2C_Init();
    I2C_Cmd(I2C1, ENABLE);

    ARC_LED_Set(1, 0);
    printf("UART test OK\n");

    ARC_Get_SerialNum();

    cur_time = RTC_GetCounter();
    printf("time: 0X%X\n", cur_time);

    
    ARC_EEPROM_Write(TxBuffer, 0, Buffer_Size);
    
    ARC_EEPROM_Read(RxBuffer, 0, Buffer_Size);
    
    I2C_Cmd(I2C1, DISABLE);
    if (strcmp((char*)TxBuffer, (char*)RxBuffer) == 0)
        printf("EEPROM tested OK\n");
    else
    {
        printf("EEPROM test failed\n");
        while(1);
    }

    ARC_SD_SPI_Init();
        
    SPI_Cmd(SPI1, ENABLE); /*!< SD_SPI enable */

    for (i = 0; i < 3; i++)
    {
        SD_CT = ARC_SD_SPI_Start();
        if (SD_CT != SD_Unknown)
            break;
    }
    
    if(SD_CT == SD_Unknown)
    {
        printf("Unknown SD card or SD card not present\n");
    }
    else
    {
        printf("SD card type: 0x%X\n", (int)SD_CT);
    }
    SPI_Cmd(SPI1, DISABLE); /*!< SD_SPI enable */
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
    task_error = xTaskCreate(InitTask, "Init task", (200), NULL, 5, NULL );
    
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
