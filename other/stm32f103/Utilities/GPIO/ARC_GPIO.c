/**
  ******************************************************************************
  * @file    ARC_GPIO.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides GPIO middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "arc_GPIO.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_GPIO
  * @{
  */ 
      
/** @defgroup ARC_GPIO_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_GPIO_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_GPIO_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_GPIO_Private_Variables
  * @{
  */ 
  
/**
  * @}
  */

/** @defgroup ARC_GPIO_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_GPIO_Private_Functions
  * @{
  */

/**
  * @brief  Configures LED GPIO ports.
  * @param  None
  * @retval None
  */
  
/*
        --------------
        | LED0 | PA1 |
        --------------
        | LED1 | PA2 |
        --------------
*/
void ARC_LED_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Configure the LED0 pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure the LED1 pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/**
  * @brief  Configures Button GPIO ports.
  * @param  None
  * @retval None
  */
  
/*
        ------------------
        | button0 | PC2 |
        ------------------
        | button1 | PC3 |
        ------------------
*/
void ARC_Button_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Configure the Button0 pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Configure the Button1 pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}


/**
  * @brief  Configures SPI GPIO ports.
  * @param  None
  * @retval None
  */
  
/*
        -------------------
        | CLK      | PA5  |
        -------------------
        | MISO     | PA6  |
        -------------------
        | MOSI     | PA7  |
        -------------------
        | FLASH CS | PA4  |
        -------------------
        | SD CS    | PA8  |
        -------------------
        | TS CS    | PC7  |
        -------------------
*/
void ARC_SPI_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*!< Configure FLASH_SPI pins: SCK */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*!< Configure FLASH_SPI pins: MOSI */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*!< Configure FLASH_SPI pins: MISO */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*!< Configure FLASH_CS_PIN pin: FLASH CS pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /*!< Configure SD_CS_PIN pin: SD CS pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /*!< Configure TouchScreen CS pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

  
/**
  * @brief  Configures LCD GPIO ports.
  * @param  None
  * @retval None
  */
 
/*
        ----------------------
        | DATA OUTPUT | PB   |
        ----------------------
        | LCD_RD      | PC12 |
        ----------------------
        | LCD_WR      | PC11 |
        ----------------------
        | LCD_RS      | PC10 |
        ----------------------
        | LCD_CS      | PD2  |
        ----------------------
        | LCD_BL      | PC5  |
        ----------------------
*/ 
void ARC_LCD_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure as push-pull output */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | 
                                  GPIO_Pin_12 | GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
   
    /* disable JTAG, SW still enabled */
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    /* Configure port B as push-pull output */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief  Configures I2C GPIO ports.
  * @param  None
  * @retval None
  */
  
/*
        -------------
        | SCL | PB6 |
        -------------
        | SDA | PB7 |
        -------------
*/ 
void ARC_I2C_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* I2C SCL pin configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* I2C SDA pin configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOB, &GPIO_InitStructure);  
}

/**
  * @brief  Configures Touch screen GPIO ports.
  * @param  None
  * @retval None
  */
  
/*
        ---------------
        | PEN  | PC6  |
        ---------------
*/
void ARC_TouchScreen_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /*!< Configure PEN interrupt pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
  * @brief  Configures TIM PWM GPIO ports.
  * @param  None
  * @retval None
  */
  
/*
        ------------------
        | TIM2 CH2 | PA1 |
        ------------------
*/

void ARC_TIM_PWM_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOA.1 Configuration:TIM2 Channel 2 as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * @brief  Configures UART GPIO ports.
  * @param  None
  * @retval None
  */
  
/*
        -------------
        | TX | PA9  |
        -------------
        | RX | PA10 |
        -------------
*/
void ARC_COM_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure USART Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USART Rx as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * @brief  Configures ADC GPIO ports.
  * @param  None
  * @retval None
  */
/*
        --------------------
        | ADC_IN_1 | PC2  |
        --------------------
*/
void ARC_ADC_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure PC.02 (ADC Channel2) as analog input -------------------------*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
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
