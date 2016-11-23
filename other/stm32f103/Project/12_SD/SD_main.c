/**
  ******************************************************************************
  * @file    SD_main.c 
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
#include "ARC_SD.h"
#include "ARC_USART.h"
#include "ARC_SysTick.h"
#include "ARC_SPI_Flash.h"
#include "ARC_TouchScreen.h"
#include "ARC_RCC.h"
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
    uint16_t i;
    uint8_t resp;
    uint8_t sd_response[5];
    uint8_t RxData[512];
    SD_Card_Type SD_CT = SD_Unknown;
    ARC_SysTick_Init();
    ARC_COM_Init();
    USART_Cmd(USART1, ENABLE);
    
    ARC_SD_SPI_Init();
    
    SPI_Cmd(SPI1, ENABLE); /*!< SD_SPI enable */
    
    ARC_DMA1_RCC_Init();
    
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
    
    while (1)
    {
        resp = ARC_sd_send_command(SD_CMD_READ_SINGLE_BLOCK, 0, R1, sd_response);
        if (resp == 0) /* READ_SINGLE_BLOCK */
        {
            resp = ARC_SD_SPI_ReadBlock(RxData, 512);
            if (resp) 
            {
                for(i = 0; i < 512; i++)
                    printf("0x%02X ", RxData[i]);
                printf("\n\n\n");
            }
            else
            {
                printf("Failed to read block\n"); 
            }
        }
        else
        {
                printf("Failed to send command\n"); 
        }
        ARC_SysTick_Delay(2000);
    }
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) www.armrunc.com *****END OF FILE****/
