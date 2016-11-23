/**
  ******************************************************************************
  * @file    ARC_RCC.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides RCC middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_RCC.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_RCC
  * @{
  */ 

/** @defgroup ARC_RCC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_RCC_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_RCC_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_RCC_Private_Variables
  * @{
  */ 

/**
  * @}
  */

/** @defgroup ARC_RCC_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_RCC_Private_Functions
  * @{
  */

/**
  * @brief  Configures LED clocks.
  * @param  None
  * @retval None
  */
void ARC_LED_RCC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   
}

/**
  * @brief  Configures Button clocks.
  * @param  None
  * @retval None
  */
void ARC_Button_RCC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);    
}

/**
  * @brief  Configures SPI Flash clocks.
  * @param  None
  * @retval None
  */
void ARC_SPI_RCC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

    /*!< FLASH_SPI Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
}

/**
  * @brief  Configures LCD clocks.
  * @param  None
  * @retval None
  */
void ARC_LCD_RCC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | 
                           RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
}

/**
  * @brief  Configures I2C clocks.
  * @param  None
  * @retval None
  */
void ARC_I2C_RCC_Init(void)
{  
    /* Enable I2C and I2C_PORT & Alternate Function clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
}

/**
  * @brief  Configures Touch screen clocks.
  * @param  None
  * @retval None
  */
void ARC_TouchScreen_RCC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}

/**
  * @brief  Configures TIM PWM clocks.
  * @param  None
  * @retval None
  */
void ARC_TIM_PWM_RCC_Init(void)
{
    /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* GPIOA clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
}

/**
  * @brief  Configures COM clocks.
  * @param  None
  * @retval None
  */
void ARC_COM_RCC_Init(void)
{
    /* Enable GPIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
}

/**
  * @brief  Configures ADC clocks.
  * @param  None
  * @retval None
  */
void ARC_ADC_RCC_Init(void)
{
    /* ADCCLK = PCLK2/4 */
    RCC_ADCCLKConfig(RCC_PCLK2_Div4); 

    /* Enable ADC1 and GPIOC clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
}

/**
  * @brief  Configures DMA clocks.
  * @param  None
  * @retval None
  */
void ARC_DMA1_RCC_Init(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}

/**
  * @brief  Configures USB clocks.
  * @param  None
  * @retval None
  */
void ARC_USB_RCC_Init(void)
{
    /* Select USBCLK source */
    RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);

    /* Enable the USB clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
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
