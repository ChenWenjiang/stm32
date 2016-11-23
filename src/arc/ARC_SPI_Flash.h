/**
  ******************************************************************************
  * @file    ARC_SPI_FLASH.h
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   Header files for middleware.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ARC_SPI_FLASH_H
#define __ARC_SPI_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "ARC_SPI.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_SPI_FLASH
  * @{
  */

/** @defgroup ARC_SPI_FLASH_Exported_Types
  * @{
  */

/**
  * @}
  */
 
/** @defgroup ARC_SPI_FLASH_Exported_Constants
  * @{
  */

#define FLASH_WIP_FLAG           0x01  /*!< Write In Progress (WIP) flag */

#define FLASH_DUMMY_BYTE         0xA5

#define FLASH_W25X16             0xEF3015
#define FLASH_W25X40             0xEF3013
#define FLASH_W25Q16             0xEF4015

typedef struct 
{
    uint8_t   flash_cmd_rdid;   /*!< Read flash id instruction */
    uint32_t  flash_id; 
    char      *flash_desc;
    uint8_t   flash_cmd_write;  /*!< Page program instruction */
    uint8_t   flash_cmd_wren;   /*!< Write enable instruction */  
    uint8_t   flash_cmd_read;   /*!< Read from Memory instruction */
    uint8_t   flash_cmd_rdsr;   /*!< Read Status Register instruction  */
    uint8_t   flash_cmd_se;     /*!< Sector Erase instruction */
    uint8_t   flash_cmd_be;     /*!< Block Erase instruction */
    uint8_t   flash_cmd_ce;     /*!< Chip Erase instruction */
    uint16_t  flash_spi_pagesize;
}SPI_FLASH_CMD;

/**
  * @}
  */
                                                        
/** @defgroup ARC_SPI_FLASH_Exported_Variables
  * @{
  */
  
extern uint32_t volatile spi_flash_index;
extern uint8_t volatile spi_flash_found;        
extern SPI_FLASH_CMD spi_flash_list[];

/**
  * @}
  */

/** @defgroup ARC_SPI_FLASH_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_SPI_FLASH_Exported_Functions
  * @{
  */
  
void ARC_FLASH_EraseSector(uint32_t FlashAddr); 
void ARC_FLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void ARC_FLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void ARC_SPI_FLASH_ID_check(void);
void ARC_SPI_Flash_Init(void);
/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_SPI_FLASH_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/******************* (C) www.armrunc.com *****END OF FILE****/
