/**
  ******************************************************************************
  * @file    ARC_SPI.h
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
#ifndef __ARC_SPI_H
#define __ARC_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_SPI
  * @{
  */

/** @defgroup ARC_SPI_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_SPI_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_SPI_Exported_Macros
  * @{
  */  
/* Select SD card: Chip Select pin low */
#define ARC_SD_CS_LOW()  GPIO_ResetBits(GPIOA, GPIO_Pin_8)
/* Deselect SD card: Chip Select pin high */
#define ARC_SD_CS_HIGH() GPIO_SetBits(GPIOA, GPIO_Pin_8)

/* Select FLASH: Chip Select pin low */
#define ARC_FLASH_CS_LOW()  GPIO_ResetBits(GPIOA, GPIO_Pin_4)
/* Deselect FLASH: Chip Select pin high */
#define ARC_FLASH_CS_HIGH() GPIO_SetBits(GPIOA, GPIO_Pin_4)   

/* Select FLASH: Chip Select pin low */
#define ARC_TS_CS_LOW()  GPIO_ResetBits(GPIOC, GPIO_Pin_7)
/* Deselect FLASH: Chip Select pin high */
#define ARC_TS_CS_HIGH() GPIO_SetBits(GPIOC, GPIO_Pin_7)

#define ARC_SPI_FLASH_SPEED     SPI_BaudRatePrescaler_4
#define ARC_SPI_XPT2046_SPEED   SPI_BaudRatePrescaler_128
#define ARC_SPI_MAX_SPEED       SPI_BaudRatePrescaler_2
#define ARC_SPI_MIN_SPEED       SPI_BaudRatePrescaler_256
#define ARC_SPI_DEFAULT_SPEED   SPI_BaudRatePrescaler_4

/**
  * @}
  */

/** @defgroup ARC_SPI_Exported_Functions
  * @{
  */
  
uint8_t ARC_SPI_SendByte(SPI_TypeDef *SPIx, uint8_t byte);
void ARC_SPI_Init(void);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_SPI_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/******************* (C) www.armrunc.com *****END OF FILE****/
