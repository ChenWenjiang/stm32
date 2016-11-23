/**
  ******************************************************************************
  * @file    I2C_main.c 
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
#include "ARC_I2C.h"
#include "ARC_EEPROM.h"
#include "ARC_USART.h"
#include "ARC_SysTick.h"
#include <stdio.h>

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
  * @brief  Main program, write, read EEPROM example.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint8_t TxBuffer[] = "ARC STM32, I2C example.";
    uint8_t RxBuffer[100] = "EEPROM not present\n";
    uint16_t Buffer_Size = sizeof(TxBuffer) / sizeof(*(TxBuffer));

    
    ARC_SysTick_Init();
    ARC_COM_Init();
    USART_Cmd(USART1, ENABLE);
    ARC_I2C_Init();
    I2C_Cmd(I2C1, ENABLE);
    
    ARC_EEPROM_Write(TxBuffer, 0, Buffer_Size);
    
    ARC_EEPROM_Read(RxBuffer, 0, Buffer_Size);
      
    while(1)
    {
        printf("TX: %s\n", TxBuffer);
        printf("RX: %s\n", RxBuffer);
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
