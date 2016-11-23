/**
  ******************************************************************************
  * @file    ARC_SPI_Flash.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides SPI Flash middleware functions.
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
#include "ARC_GPIO.h"
#include "ARC_RCC.h"
#include "ARC_TouchScreen.h"
#include <stdio.h>

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_SPI
  * @{
  */ 

/** @defgroup ARC_SPI_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_SPI_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_SPI_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_SPI_Private_Variables
  * @{
  */ 

/* SPI flash list, add the flash you want to support here */
SPI_FLASH_CMD spi_flash_list[]=
{
    {
        0x9f,  /*!< Read flash id instruction */
        FLASH_W25Q16,
        "Winbond W25Q16",
        0x02,  /*!< Page program instruction */
        0x06,  /*!< Write enable instruction */
        0x03,  /*!< Read from Memory instruction */
        0x05,  /*!< Read Status Register instruction  */
        0x20,  /*!< Sector Erase instruction */
        0xD8,  /*!< Block Erase instruction */
        0xC7,  /*!< Chip Erase instruction */
        0x100, /*!< Chip page size */
    },
    {
        0x9f,  /*!< Read flash id instruction */
        FLASH_W25X40,
        "Winbond W25X40",
        0x02,  /*!< Page program instruction */
        0x06,  /*!< Write enable instruction */
        0x03,  /*!< Read from Memory instruction */
        0x05,  /*!< Read Status Register instruction  */
        0x20,  /*!< Sector Erase instruction */
        0xD8,  /*!< Block Erase instruction */
        0xC7,  /*!< Chip Erase instruction */
        0x100, /*!< Chip page size */
    }
};

uint32_t volatile spi_flash_index;
uint8_t volatile spi_flash_found;
    
/**
  * @}
  */

/** @defgroup ARC_SPI_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/**
  * @brief  Set flash index and the found status.
  * @param  flash_index: the flash index.
  * @param  flash_found: the found status.
  * @retval None.
  */
void ARC_SPI_FLASH_set_index(uint32_t flash_index, uint8_t flash_found)
{
    spi_flash_index = flash_index;
    spi_flash_found = flash_found;
}

/**
  * @brief  get flash index and the found status.
  * @param  *flash_index: the flash index.
  * @retval the flash found status.
  */
uint8_t ARC_SPI_FLASH_get_index(uint32_t *flash_index)
{
    *flash_index = 0;
    if(spi_flash_found != 0)
        *flash_index = spi_flash_index;
    return spi_flash_found;
}

/**
  * @brief  Check the ID of the flash, including manufacture ID and device ID.
  * @param  None
  * @retval None.
  */
void ARC_SPI_FLASH_ID_check(void)
{
    uint32_t i = 0, flash_list_count = 0;
    uint32_t FlashID = 0;
    
    flash_list_count = sizeof(spi_flash_list)/sizeof(SPI_FLASH_CMD);

    ARC_FLASH_CS_LOW();
    for(i = 0; i < flash_list_count; i++)
    {
        ARC_SPI_SendByte(SPI1, spi_flash_list[i].flash_cmd_rdid);     
        FlashID |= (ARC_SPI_SendByte(SPI1, FLASH_DUMMY_BYTE) & 0xFF) << 16;
        FlashID |= (ARC_SPI_SendByte(SPI1, FLASH_DUMMY_BYTE) & 0xFF) << 8;
        FlashID |= ARC_SPI_SendByte(SPI1, FLASH_DUMMY_BYTE) & 0xFF;
        
        if(spi_flash_list[i].flash_id == FlashID)
        {
            printf("%s found\n", spi_flash_list[i].flash_desc);
            ARC_SPI_FLASH_set_index(i, 1);
            break;
        }
    }
    
    ARC_FLASH_CS_HIGH(); 
    if(i == flash_list_count)
    {
        printf("flash not present or not recognized\n");
        ARC_SPI_FLASH_set_index(0, 0);
    }
}

/**
  * @brief  Initialize SPI flash.
  * @param  None
  * @retval None.
  */
void ARC_SPI_Flash_Init(void)
{
    ARC_SPI_Init();
}

/**
  * @brief  Polls the status of the Write In Progress (WIP) flag in the FLASH's
  *         status register and loop until write opertaion has completed.
  * @param  None
  * @retval None
  */
void ARC_FLASH_WaitForWriteEnd(void)
{
    uint8_t flashstatus = 0;
    
    /*!< Select the FLASH: Chip Select low */
    ARC_FLASH_CS_LOW();

    /*!< Send "Read Status Register" instruction */
    ARC_SPI_SendByte(SPI1, spi_flash_list[spi_flash_index].flash_cmd_rdsr);

    /*!< Loop as long as the memory is busy with a write cycle */
    do
    {
        /*!< Send a dummy byte to generate the clock needed by the FLASH
        and put the value of the status register in FLASH_Status variable */
        flashstatus = ARC_SPI_SendByte(SPI1, FLASH_DUMMY_BYTE);
    }while ((flashstatus & FLASH_WIP_FLAG) == SET); /* Write in progress */

    /*!< Deselect the FLASH: Chip Select high */
    ARC_FLASH_CS_HIGH();
}

/**
  * @brief  Enables the write access to the FLASH.
  * @param  None
  * @retval None
  */
void ARC_Flash_WriteEnable(void)
{
    /*!< Select the FLASH: Chip Select low */
    ARC_FLASH_CS_LOW();

    /*!< Send "Write Enable" instruction */
    ARC_SPI_SendByte(SPI1, spi_flash_list[spi_flash_index].flash_cmd_wren);

    /*!< Deselect the FLASH: Chip Select high */
    ARC_FLASH_CS_HIGH();
}


/**
  * @brief  Erases the specified FLASH sector.
  * @param  SectorAddr: address of the sector to erase.
  * @retval None
  */
void ARC_FLASH_EraseSector(uint32_t FlashAddr)
{
    /*!< Send write enable instruction */
    ARC_Flash_WriteEnable();
    
    /*!< Sector Erase */
    
    /*!< Select the FLASH: Chip Select low */
    ARC_FLASH_CS_LOW();
    /*!< Send Sector Erase instruction */
    ARC_SPI_SendByte(SPI1, spi_flash_list[spi_flash_index].flash_cmd_se);
    /*!< Send SectorAddr high nibble address byte */
    ARC_SPI_SendByte(SPI1, (FlashAddr & 0xFF0000) >> 16);
    /*!< Send SectorAddr medium nibble address byte */
    ARC_SPI_SendByte(SPI1, (FlashAddr & 0xFF00) >> 8);
    /*!< Send SectorAddr low nibble address byte */
    ARC_SPI_SendByte(SPI1, FlashAddr & 0xFF);
    /*!< Deselect the FLASH: Chip Select high */
    ARC_FLASH_CS_HIGH();

    /*!< Wait the end of Flash writing */
    ARC_FLASH_WaitForWriteEnd();
}

/**
  * @brief  Writes more than one byte to the FLASH with a single WRITE cycle 
  *         (Page WRITE sequence).
  * @note   The number of byte can't exceed the FLASH page size.
  * @param  pBuffer: pointer to the buffer  containing the data to be written
  *         to the FLASH.
  * @param  WriteAddr: FLASH's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the FLASH, must be equal
  *         or less than "FLASH_PAGESIZE" value.
  * @retval None
  */
void ARC_FLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    /*!< Enable the write access to the FLASH */
    ARC_Flash_WriteEnable();
    
    /*!< Select the FLASH: Chip Select low */
    ARC_FLASH_CS_LOW();
    /*!< Send "Write to Memory " instruction */
    ARC_SPI_SendByte(SPI1, spi_flash_list[spi_flash_index].flash_cmd_write);
    /*!< Send WriteAddr high nibble address byte to write to */
    ARC_SPI_SendByte(SPI1, (WriteAddr & 0xFF0000) >> 16);
    /*!< Send WriteAddr medium nibble address byte to write to */
    ARC_SPI_SendByte(SPI1, (WriteAddr & 0xFF00) >> 8);
    /*!< Send WriteAddr low nibble address byte to write to */
    ARC_SPI_SendByte(SPI1, WriteAddr & 0xFF);

    /*!< while there is data to be written on the FLASH */
    while (NumByteToWrite--)
    {
        /*!< Send the current byte */
        ARC_SPI_SendByte(SPI1, *pBuffer);
        /*!< Point on the next byte to be written */
        pBuffer++;
    }

    /*!< Deselect the FLASH: Chip Select high */
    ARC_FLASH_CS_HIGH();

    /*!< Wait the end of Flash writing */
    ARC_FLASH_WaitForWriteEnd();
}

/**
  * @brief  Writes block of data to the FLASH. In this function, the number of
  *         WRITE cycles are reduced, using Page WRITE sequence.
  * @param  pBuffer: pointer to the buffer  containing the data to be written
  *         to the FLASH.
  * @param  WriteAddr: FLASH's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the FLASH.
  * @retval None
  */
void ARC_FLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t num_of_page = 0, num_of_single = 0, offset_in_page = 0, num_remained_in_1st_page = 0, temp = 0;
    uint16_t spi_flash_page_size = spi_flash_list[spi_flash_index].flash_spi_pagesize;
    
    offset_in_page = WriteAddr % spi_flash_page_size;
    num_remained_in_1st_page = spi_flash_page_size - offset_in_page;
    num_of_page =  NumByteToWrite / spi_flash_page_size;
    num_of_single = NumByteToWrite % spi_flash_page_size;

    if (offset_in_page == 0) /*!< WriteAddr is FLASH_PAGESIZE aligned  */
    {
        if (num_of_page == 0) /*!< NumByteToWrite < FLASH_PAGESIZE */
        {
            ARC_FLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
        }
        else /*!< NumByteToWrite > FLASH_PAGESIZE */
        {
            while (num_of_page--)
            {
                ARC_FLASH_WritePage(pBuffer, WriteAddr, spi_flash_page_size);
                WriteAddr +=  spi_flash_page_size;
                pBuffer += spi_flash_page_size;
            }

            if (num_of_single != 0)
            {
                ARC_FLASH_WritePage(pBuffer, WriteAddr, num_of_single);
            }
        }
    }
    else /*!< WriteAddr is not FLASH_PAGESIZE aligned  */
    {
        if (num_of_page == 0) /*!< NumByteToWrite < FLASH_PAGESIZE */
        {
            if (num_of_single > num_remained_in_1st_page) /*!< (NumByteToWrite + WriteAddr) > FLASH_PAGESIZE */
            {
                temp = num_of_single - num_remained_in_1st_page;

                ARC_FLASH_WritePage(pBuffer, WriteAddr, num_remained_in_1st_page);
                WriteAddr +=  num_remained_in_1st_page;
                pBuffer += num_remained_in_1st_page;

                ARC_FLASH_WritePage(pBuffer, WriteAddr, temp);
            }
            else
            {
                ARC_FLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else /*!< NumByteToWrite > FLASH_PAGESIZE */
        {
            NumByteToWrite -= num_remained_in_1st_page;
            num_of_page =  NumByteToWrite / spi_flash_page_size;
            num_of_single = NumByteToWrite % spi_flash_page_size;

            ARC_FLASH_WritePage(pBuffer, WriteAddr, num_remained_in_1st_page);
            WriteAddr +=  num_remained_in_1st_page;
            pBuffer += num_remained_in_1st_page;

            while (num_of_page--)
            {
                ARC_FLASH_WritePage(pBuffer, WriteAddr, spi_flash_page_size);
                WriteAddr +=  spi_flash_page_size;
                pBuffer += spi_flash_page_size;
            }

            if (num_of_single != 0)
            {
                ARC_FLASH_WritePage(pBuffer, WriteAddr, num_of_single);
            }
        }
    }
}

/**
  * @brief  Reads a block of data from the FLASH.
  * @param  pBuffer: pointer to the buffer that receives the data read from the FLASH.
  * @param  ReadAddr: FLASH's internal address to read from.
  * @param  NumByteToRead: number of bytes to read from the FLASH.
  * @retval None
  */
void ARC_FLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    /*!< Select the FLASH: Chip Select low */
    ARC_FLASH_CS_LOW();

    /*!< Send "Read from Memory " instruction */
    ARC_SPI_SendByte(SPI1, spi_flash_list[spi_flash_index].flash_cmd_read);

    /*!< Send ReadAddr high nibble address byte to read from */
    ARC_SPI_SendByte(SPI1, (ReadAddr & 0xFF0000) >> 16);
    /*!< Send ReadAddr medium nibble address byte to read from */
    ARC_SPI_SendByte(SPI1, (ReadAddr& 0xFF00) >> 8);
    /*!< Send ReadAddr low nibble address byte to read from */
    ARC_SPI_SendByte(SPI1, ReadAddr & 0xFF);

    while (NumByteToRead--) /*!< while there is data to be read */
    {
        /*!< Read a byte from the FLASH */
        *pBuffer = ARC_SPI_SendByte(SPI1, FLASH_DUMMY_BYTE);
        /*!< Point to the next location where the byte read will be saved */
        pBuffer++;
    }

    /*!< Deselect the FLASH: Chip Select high */
    ARC_FLASH_CS_HIGH();
}

/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */  
    
/******************* (C) www.armrunc.com *****END OF FILE****/
