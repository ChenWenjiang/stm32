/**
  ******************************************************************************
  * @file    ARC_SD.h
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
#ifndef __ARC_SD_H
#define __ARC_SD_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_SD
  * @{
  */

/** @defgroup ARC_SD_Exported_Types
  * @{
  */

typedef enum
{
    SD_RESPONSE_NO_ERROR    = 0x00,
    SD_IN_IDLE_STATE        = 0x01,
    SD_ERASE_RESET          = 0x02,
    SD_ILLEGAL_COMMAND      = 0x04,
    SD_COM_CRC_ERROR        = 0x08,
    SD_ERASE_SEQUENCE_ERROR = 0x10,
    SD_ADDRESS_ERROR        = 0x20,
    SD_PARAMETER_ERROR      = 0x40,
    SD_RESPONSE_FAILURE     = 0xFF
}SD_Response_status;

typedef enum
{
    SD_MMC_Ver3      = 0x01,
    SD_Ver1          = 0x02,
    SD_SDSC          = 0x04,
    SD_SDHC          = 0x08,
    SD_SDC           = (SD_Ver1 | SD_SDSC | SD_SDHC),
    SD_Ver2          = (SD_SDSC | SD_SDHC),
    SD_Unknown       = 0xFF
}SD_Card_Type;

typedef enum
{
    SD_Status_NotInit   = 0x01, /* Drive not initialized */
    SD_Status_NoDisk    = 0x02, /* No medium in the drive or not recognized */
    SD_Status_Protect   = 0x04  /* Write protected */
}SD_Card_Status;

typedef struct
{
    SD_Card_Type   sd_ct;
    SD_Card_Status sd_stat;
}SD_Card_Info;

typedef enum 
{
    R1,
    R1B,
    R2,
    R3,
    R7
} SD_Response;

/**
  * @}
  */

/** @defgroup ARC_SD_Exported_Constants
  * @{
  */

#define SD_BLOCKSIZE_NBITS    9
#define SD_BLOCK_SIZE         512


#define SD_DUMMY_BYTE   0xFF

/**
  * Start Data tokens:
  * Tokens (necessary because at nop/idle (and CS active) only 0xff is 
  * on the data/command line)  
  */
#define SD_START_DATA_SINGLE_BLOCK_READ    0xFE  /*!< Data token start byte, Start Single Block Read */
#define SD_START_DATA_MULTIPLE_BLOCK_READ  0xFE  /*!< Data token start byte, Start Multiple Block Read */
#define SD_START_DATA_SINGLE_BLOCK_WRITE   0xFE  /*!< Data token start byte, Start Single Block Write */
#define SD_START_DATA_MULTIPLE_BLOCK_WRITE 0xFD  /*!< Data token start byte, Start Multiple Block Write */
#define SD_STOP_DATA_MULTIPLE_BLOCK_WRITE  0xFD  /*!< Data toke stop byte, Stop Multiple Block Write */


/* Commands: CMDxx = CMD-number | 0x40 */
#define SD_CMD_GO_IDLE_STATE                       ((uint8_t)0)
#define SD_CMD_SEND_OP_COND                        ((uint8_t)1)
#define SD_CMD_ALL_SEND_CID                        ((uint8_t)2)
#define SD_CMD_SET_REL_ADDR                        ((uint8_t)3) /*!< SDIO_SEND_REL_ADDR for SD Card */
#define SD_CMD_SET_DSR                             ((uint8_t)4)
#define SD_CMD_SDIO_SEN_OP_COND                    ((uint8_t)5)
#define SD_CMD_HS_SWITCH                           ((uint8_t)6)
#define SD_CMD_SEL_DESEL_CARD                      ((uint8_t)7)
#define SD_CMD_SEND_IF_COND                        ((uint8_t)8)
#define SD_CMD_SEND_CSD                            ((uint8_t)9)
#define SD_CMD_SEND_CID                            ((uint8_t)10)
#define SD_CMD_READ_DAT_UNTIL_STOP                 ((uint8_t)11) /*!< SD Card doesn't support it */
#define SD_CMD_STOP_TRANSMISSION                   ((uint8_t)12)
#define SD_CMD_SEND_STATUS                         ((uint8_t)13)
#define SD_CMD_HS_BUSTEST_READ                     ((uint8_t)14)
#define SD_CMD_GO_INACTIVE_STATE                   ((uint8_t)15)
#define SD_CMD_SET_BLOCKLEN                        ((uint8_t)16)
#define SD_CMD_READ_SINGLE_BLOCK                   ((uint8_t)17)
#define SD_CMD_READ_MULT_BLOCK                     ((uint8_t)18)
#define SD_CMD_HS_BUSTEST_WRITE                    ((uint8_t)19)
#define SD_CMD_WRITE_DAT_UNTIL_STOP                ((uint8_t)20) /*!< SD Card doesn't support it */
#define SD_CMD_SET_BLOCK_COUNT                     ((uint8_t)23) /*!< SD Card doesn't support it */
#define SD_CMD_WRITE_SINGLE_BLOCK                  ((uint8_t)24)
#define SD_CMD_WRITE_MULT_BLOCK                    ((uint8_t)25)
#define SD_CMD_PROG_CID                            ((uint8_t)26) /*!< reserved for manufacturers */
#define SD_CMD_PROG_CSD                            ((uint8_t)27)
#define SD_CMD_SET_WRITE_PROT                      ((uint8_t)28)
#define SD_CMD_CLR_WRITE_PROT                      ((uint8_t)29)
#define SD_CMD_SEND_WRITE_PROT                     ((uint8_t)30)
#define SD_CMD_SD_ERASE_GRP_START                  ((uint8_t)32) /*!< To set the address of the first write
                                                                  block to be erased. (For SD card only) */
#define SD_CMD_SD_ERASE_GRP_END                    ((uint8_t)33) /*!< To set the address of the last write block of the
                                                                  continuous range to be erased. (For SD card only) */
#define SD_CMD_ERASE_GRP_START                     ((uint8_t)35) /*!< To set the address of the first write block to be erased.
                                                                  (For MMC card only spec 3.31) */

#define SD_CMD_ERASE_GRP_END                       ((uint8_t)36) /*!< To set the address of the last write block of the
                                                                  continuous range to be erased. (For MMC card only spec 3.31) */

#define SD_CMD_ERASE                               ((uint8_t)38)
#define SD_CMD_FAST_IO                             ((uint8_t)39) /*!< SD Card doesn't support it */
#define SD_CMD_GO_IRQ_STATE                        ((uint8_t)40) /*!< SD Card doesn't support it */
#define SD_CMD_LOCK_UNLOCK                         ((uint8_t)42)
#define SD_CMD_APP_SEND_OP_COND                    ((uint8_t)41)
#define SD_CMD_APP_CMD                             ((uint8_t)55)
#define SD_CMD_GEN_CMD                             ((uint8_t)56)
#define SD_CMD_READ_OCR                            ((uint8_t)58)
#define SD_CMD_CRC_ON_OFF                          ((uint8_t)59)
#define SD_CMD_NO_CMD                              ((uint8_t)64)

#define SD_ACMD_APP_SEND_OP_COND                   ((uint8_t)(41 + 0x80))
#define SD_ACMD_APP_SET_WR_BLK_ERASE_COUNT         ((uint8_t)(0xC0 + 23))
#define SD_ACMD_APP_SD_STATUS                      ((uint8_t)(0xC0 + 13))

/* Data response error */
#define    SD_DATA_OK               0x05
#define    SD_DATA_CRC_ERROR        0x0B
#define    SD_DATA_WRITE_ERROR      0x0D
#define    SD_DATA_OTHER_ERROR      0xFF

#define    SD_ERROR                 0x01
#define    SD_OK                    0x00 

#define SD_PRESENT                  0x01
#define SD_NOT_PRESENT              0x00

#define SD_TRANSFER_OK              0x00
#define SD_TRANSFER_BUSY            0x01
#define SD_TRANSFER_ERROR           0x03



/**
  * @}
  */

/** @defgroup ARC_SD_Exported_Macros
  * @{
  */
  
/**
  * @}
  */

/** @defgroup ARC_SD_Exported_Functions
  * @{
  */

void ARC_SD_SPI_Init(void);
SD_Card_Type ARC_SD_SPI_Start(void);
uint8_t ARC_sd_send_command(uint8_t, uint32_t, SD_Response, uint8_t *);
uint8_t ARC_SD_SPI_ReadBlock(uint8_t *buff, uint32_t byteTransfer);

/**
  * @}
  */


#ifdef __cplusplus
}
#endif


#endif /* __ARC_SD_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
 

/******************* (C) www.armrunc.com *****END OF FILE****/
