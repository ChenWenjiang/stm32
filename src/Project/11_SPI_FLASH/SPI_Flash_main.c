/**
  ******************************************************************************
  * @file    SPI_FLASH_main.c 
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
#include "ARC_SPI_Flash.h"
#include "ARC_USART.h"
#include "ARC_LCD.h"
#include "ARC_SysTick.h"
#include "stdio.h"

/** @addtogroup ARC_Examples
  * @{
  */

/** @addtogroup ARC_SPI_FLASH
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program, SPI flash write/read example.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint8_t  Tx_Buffer[] = "ARC SPI FLASH Example";
    uint8_t  Rx_Buffer[512] = "flash not present or not recognized\n";
    uint16_t BufferSize = sizeof(Tx_Buffer) / sizeof(*Tx_Buffer);
    uint32_t FlashAddr = 0x0;

    /* initialize SysTick for exact time delay */
    ARC_SysTick_Init();
    
    /* initialize UART */
    ARC_COM_Init();
    USART_Cmd(USART1, ENABLE);

    /* initialize SPI flash */
    ARC_SPI_Flash_Init();
    SPI_Cmd(SPI1, ENABLE);

    /* check if flash recognized */
    ARC_SPI_FLASH_ID_check();
    
    if (spi_flash_found)
    {
        /* Erase SPI FLASH Sector to be written */
        ARC_FLASH_EraseSector(FlashAddr);
    
        /* Write data in Tx_Buffer to SPI FLASH memory */
        ARC_FLASH_WriteBuffer(Tx_Buffer, FlashAddr, BufferSize);
    
        /* Read data from SPI FLASH memory */
        ARC_FLASH_ReadBuffer(Rx_Buffer, FlashAddr, BufferSize);
    }

    while (1)
    {        
        printf("Tx: %s\n", Tx_Buffer);
        printf("Rx: %s\n", Rx_Buffer);
        
        /* delay one second */
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
