/**
  ******************************************************************************
  * @file    ARC_LCD.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides LCD middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_LCD.h"
#include "ARC_SysTick.h"
#include "ARC_Retarget.h"
#include "ARC_Font.h"
#include "ARC_GPIO.h"
#include "ARC_RCC.h"
#if (defined ARC_UCGUI && defined ARC_FREERTOS)
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "GUIDebug.h"
#include <string.h>
#endif

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_LCD
  * @{
  */ 

/** @defgroup ARC_LCD_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_LCD_Private_Defines
  * @{
  */
#define ARC_LCD_CS_SET()        GPIOD->BSRR = GPIO_Pin_2    /* chip select pin */
#define ARC_LCD_RD_SET()        GPIOC->BSRR = GPIO_Pin_10   /* register select pin */
#define ARC_LCD_WR_SET()        GPIOC->BSRR = GPIO_Pin_11   /* read strobe signal, low active */ 
#define ARC_LCD_RS_SET()        GPIOC->BSRR = GPIO_Pin_12   /* write strobe signal, low active */

#define ARC_LCD_CS_RESET()      GPIOD->BRR = GPIO_Pin_2     
#define ARC_LCD_RD_RESET()      GPIOC->BRR = GPIO_Pin_10       
#define ARC_LCD_WR_RESET()      GPIOC->BRR = GPIO_Pin_11   
#define ARC_LCD_RS_RESET()      GPIOC->BRR = GPIO_Pin_12     

#define ARC_LCD_BL_RESET()      GPIOC->BRR = GPIO_Pin_5
#define ARC_LCD_BL_SET()        GPIOC->BSRR = GPIO_Pin_5

#define ARC_LCD_OUT(PortVal)    GPIOB->ODR = PortVal
#define ARC_LCD_IN(PortVal)     PortVal = GPIOB->IDR

#define ARC_LCD_FLOAT_INPUT()\
{\
    GPIOB->CRH = 0x44444444;\
    GPIOB->CRL = 0x44444444;\
}

#define ARC_LCD_PP_OUTPUT()\
{\
    GPIOB->CRH = 0x33333333;\
    GPIOB->CRL = 0x33333333;\
}

/**
  * @}
  */ 

/** @defgroup ARC_LCD_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_LCD_Private_Variables
  * @{
  */
static ARC_LCD_Params ARC_LCD_Param;

/**
  * @}
  */

/** @defgroup ARC_LCD_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_LCD_Private_Functions
  * @{
  */

/**
  * @brief  get the pointer to the LCD parameters.
  * @param  None
  * @retval the pointer to the LCD parameters
  */
ARC_LCD_Params *ARC_LCD_get_param(void)
{
    return &ARC_LCD_Param;
}
/**
  * @brief  write register index.
  * @param  irData, the index register value to be written.
  * @retval None
  */
#define ARC_LCD_WriteRegIndex(irData)\
{\
    ARC_LCD_CS_RESET();\
    ARC_LCD_RS_RESET();\
    ARC_LCD_RD_SET();\
    ARC_LCD_OUT(irData);\
    ARC_LCD_WR_RESET();\
    ARC_LCD_WR_SET();\
    ARC_LCD_RS_SET();\
    ARC_LCD_CS_SET();\
}

/**
  * @brief  write register data.
  * @param  Data, the data to be written.
  * @retval None
  */
#define ARC_LCD_WriteRegData(RegData)\
{\
    ARC_LCD_CS_RESET();\
    ARC_LCD_OUT(RegData);\
    ARC_LCD_WR_RESET();\
    ARC_LCD_WR_SET();\
    ARC_LCD_CS_SET();\
}

/**
  * @brief  write register data, becareful, no CS operattion to speed up.
  * @param  Data, the data to be written.
  * @retval None
  */
#define ARC_LCD_WriteRegData_NoCS(RegData)\
{\
    ARC_LCD_OUT(RegData);\
    ARC_LCD_WR_RESET();\
    ARC_LCD_WR_SET();\
}


/**
  * @brief  read register data, becareful.
  * @param  Data, the data read from IR.
  * @retval None
  */
#define ARC_LCD_ReadRegData(RegData)\
{\
    ARC_LCD_CS_RESET();\
    ARC_LCD_RD_RESET();\
    __NOP();\
    __NOP();\
    ARC_LCD_RD_SET();\
    ARC_LCD_IN(RegData);\
    ARC_LCD_CS_SET();\
}

/**
  * @brief  read GRAM data, becareful, no CS or RD operation.
  * @param  Data, the data read from IR.
  * @retval None
  */

#define ARC_LCD_ReadGRAMData(GRAMData)\
{\
    ARC_LCD_ReadRegData(GRAMData)\
    ARC_LCD_ReadRegData(GRAMData)\
}

/**
  * @brief  Sets the cursor position.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position. 
  * @retval None
  */
__inline void ARC_LCD_SetCursor(uint16_t x, uint16_t y)
{
    if(ARC_LCD_Param.LCD_Type == LCD_HX8347A)
    {
        ARC_LCD_WriteReg(LCD_REG_03H, x & 0xff);
        ARC_LCD_WriteReg(LCD_REG_02H, (x >> 8) & 0xff);
        ARC_LCD_WriteReg(LCD_REG_07H, y & 0xff);
        ARC_LCD_WriteReg(LCD_REG_06H, (y >> 8) & 0xff);
    }
    else
    {
        ARC_LCD_WriteReg(LCD_REG_20H, x);
        ARC_LCD_WriteReg(LCD_REG_21H, y);
    }
}

/**
  * @brief  Write LCD register.
  * @param  LCD_Index, the register index to be written.
  * @param  LCD_Data, value to be written.
  * @retval None.
  */
/************************************************************************
 **                                                                    **
 ** nCS       ----\__________________________________________/-------  **
 ** RS        ------\____________/-----------------------------------  **
 ** nRD       -------------------------------------------------------  **
 ** nWR       --------\_______/--------\_____/-----------------------  **
 ** DB[0:15]  ---------[index]----------[data]-----------------------  **
 **                                                                    **
 ************************************************************************/

__inline void ARC_LCD_WriteReg(uint16_t LCD_Index, uint16_t LCD_Data)
{
    ARC_LCD_WriteRegIndex(LCD_Index);
    ARC_LCD_WriteRegData(LCD_Data);
}

/**
  * @brief  Write to the LCD RAM a number of value.
  * @param  *LCD_RegValue, the pointers to the values to be written.
  * @param  NumValue, the number of values to be written.
  * @retval None.
  */
__inline void ARC_LCD_WriteGRAM(const uint16_t *LCD_RegValue, uint32_t NumValue)
{
    ARC_LCD_WriteRegIndex(LCD_REG_22H);
    
    ARC_LCD_CS_RESET();
    for(; NumValue; NumValue--)
    {
        ARC_LCD_WriteRegData_NoCS(*LCD_RegValue);
        LCD_RegValue++;
    }
    ARC_LCD_CS_SET();
}

/**
  * @brief  Write to the LCD RAM a number of value.
  * @param  LCD_RegValue, the values to be written.
  * @param  NumValue, the number of values to be written.
  * @retval None.
  */
__inline void ARC_LCD_WriteGRAM_Same(uint16_t LCD_RegValue, uint32_t NumValue)
{
    ARC_LCD_WriteRegIndex(LCD_REG_22H);

    ARC_LCD_CS_RESET();
    for(; NumValue; NumValue--)
    {
        ARC_LCD_WriteRegData_NoCS(LCD_RegValue);
    }
    ARC_LCD_CS_SET();
}

/**
  * @brief  Write to the LCD RAM a number of value.
  * @param  *LCD_RegValue, the pointers to the values to be written.
  * @param  NumValue, the number of values to be written.
  * @retval None.
  */
__inline void ARC_LCD_SetMultiPixelsIndex(uint16_t x, uint16_t y, uint16_t const *LCD_RegValue, uint32_t NumValue)
{
    ARC_LCD_SetCursor(x, y);
    ARC_LCD_WriteGRAM(LCD_RegValue, NumValue);
}

/**
  * @brief  Read LCD register.
  * @param  LCD_Reg, the register index to be read.
  * @retval value read from LCD.
  */
__inline uint16_t ARC_LCD_ReadReg(uint16_t LCD_Index)
{
    uint16_t LCD_Value;
    ARC_LCD_WriteRegIndex(LCD_Index);
    /* Configure port B as foating input */
    ARC_LCD_FLOAT_INPUT();
    ARC_LCD_ReadRegData(LCD_Value);
    ARC_LCD_PP_OUTPUT();
    return LCD_Value;
}

/**
  * @brief  Sets a display window
  * @param  x1: specifies the X top left position.
  * @param  y1: specifies the Y top left position.
  * @param  x2: specifies the X buttom right position.
  * @param  y2: specifies the Y buttom right position.
  * @retval None
  */
__inline void ARC_LCD_SetDisplayWindow(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1)
{
    
    if(ARC_LCD_Param.LCD_Type == LCD_HX8347A)
    {
        /* Horizontal GRAM Start Address */
        ARC_LCD_WriteReg(LCD_REG_03H, x0 & 0xff);
        ARC_LCD_WriteReg(LCD_REG_02H, (x0 >> 8) & 0xff);
        /* Horizontal GRAM End Address */
        ARC_LCD_WriteReg(LCD_REG_05H, x1 & 0xff);
        ARC_LCD_WriteReg(LCD_REG_04H, (x1 >> 8) & 0xff);
        /* Vertical GRAM Start Address */
        ARC_LCD_WriteReg(LCD_REG_07H, y0 & 0xff);\
        ARC_LCD_WriteReg(LCD_REG_06H, (y0 >> 8) & 0xff);
        /* Vertical GRAM End Address */
        ARC_LCD_WriteReg(LCD_REG_09H, y1 & 0xff);
        ARC_LCD_WriteReg(LCD_REG_08H, (y1 >> 8) & 0xff);
    }
    else
    {
        /* Horizontal GRAM Start Address */
        ARC_LCD_WriteReg(LCD_REG_50H, x0);
        /* Horizontal GRAM End Address */
        ARC_LCD_WriteReg(LCD_REG_51H, x1);
        /* Vertical GRAM Start Address */
        ARC_LCD_WriteReg(LCD_REG_52H, y0);
        /* Vertical GRAM End Address */
        ARC_LCD_WriteReg(LCD_REG_53H, y1);
        ARC_LCD_SetCursor(x0, y0);
    }
}

/**
  * @brief  initialize panel.
  * @param  None.
  * @retval None
  */
void ARC_HX8347A_Init(LCD_Direction_TypeDef lcd_dir)
{   
    //=========Initial HX8347  for INL2.8"QVGA Panel======// 
    ARC_SysTick_Delay(10); // Delay 1ms 
    ARC_SysTick_Delay(10); // Delay 10ms  
    ARC_SysTick_Delay(150); // Delay 150 ms 

    ARC_LCD_WriteReg(0x0042,0x0008);   
    //Gamma setting  
    ARC_LCD_WriteReg(0x0046,0x00B4); 
    ARC_LCD_WriteReg(0x0047,0x0043); 
    ARC_LCD_WriteReg(0x0048,0x0013); 
    ARC_LCD_WriteReg(0x0049,0x0047); 
    ARC_LCD_WriteReg(0x004A,0x0014); 
    ARC_LCD_WriteReg(0x004B,0x0036); 
    ARC_LCD_WriteReg(0x004C,0x0003); 
    ARC_LCD_WriteReg(0x004D,0x0046); 
    ARC_LCD_WriteReg(0x004E,0x0005);  
    ARC_LCD_WriteReg(0x004F,0x0010);  
    ARC_LCD_WriteReg(0x0050,0x0008);  
    ARC_LCD_WriteReg(0x0051,0x000a);  

    //Window Setting 
    ARC_LCD_WriteReg(0x0002,0x0000); 
    ARC_LCD_WriteReg(0x0003,0x0000); 
    ARC_LCD_WriteReg(0x0004,0x0000); 
    ARC_LCD_WriteReg(0x0005,0x00EF); 
    ARC_LCD_WriteReg(0x0006,0x0000); 
    ARC_LCD_WriteReg(0x0007,0x0000); 
    ARC_LCD_WriteReg(0x0008,0x0001); 
    ARC_LCD_WriteReg(0x0009,0x003F); 

    ARC_SysTick_Delay(10); 

    ARC_LCD_WriteReg(0x0001,0x0006); 
    ARC_LCD_WriteReg(0x0016,0x00C8);   
    ARC_LCD_WriteReg(0x0023,0x0095); 
    ARC_LCD_WriteReg(0x0024,0x0095); 
    ARC_LCD_WriteReg(0x0025,0x00FF); 
    ARC_LCD_WriteReg(0x0027,0x0002); 
    ARC_LCD_WriteReg(0x0028,0x0002); 
    ARC_LCD_WriteReg(0x0029,0x0002); 
    ARC_LCD_WriteReg(0x002A,0x0002); 
    ARC_LCD_WriteReg(0x002C,0x0002); 
    ARC_LCD_WriteReg(0x002D,0x0002); 

    ARC_LCD_WriteReg(0x003A,0x0001);  
    ARC_LCD_WriteReg(0x003B,0x0001);  
    ARC_LCD_WriteReg(0x003C,0x00F0);    
    ARC_LCD_WriteReg(0x003D,0x0000); 

    ARC_SysTick_Delay(20); 

    ARC_LCD_WriteReg(0x0035,0x0038); 
    ARC_LCD_WriteReg(0x0036,0x0078); 
    ARC_LCD_WriteReg(0x003E,0x0038); 
    ARC_LCD_WriteReg(0x0040,0x000F); 
    ARC_LCD_WriteReg(0x0041,0x00F0);  

    ARC_LCD_WriteReg(0x0038,0x0000); 

    // Power Setting 
    ARC_LCD_WriteReg(0x0019,0x0049);  
    ARC_LCD_WriteReg(0x0093,0x000A); 

    ARC_SysTick_Delay(10); 

    ARC_LCD_WriteReg(0x0020,0x0020);   
    ARC_LCD_WriteReg(0x001D,0x0003);   
    ARC_LCD_WriteReg(0x001E,0x0000);  

    ARC_LCD_WriteReg(0x001F,0x0009);   

    ARC_LCD_WriteReg(0x0044,0x0053);  
    ARC_LCD_WriteReg(0x0045,0x0010);   


    ARC_SysTick_Delay(10);  

    ARC_LCD_WriteReg(0x001C,0x0004);  

    ARC_SysTick_Delay(20); 

    ARC_LCD_WriteReg(0x0043,0x0080);    

    ARC_SysTick_Delay(5); 

    ARC_LCD_WriteReg(0x001B,0x000a);    

    ARC_SysTick_Delay(40);  

    ARC_LCD_WriteReg(0x001B,0x0012);    

    ARC_SysTick_Delay(40);   
    //Display On Setting 

    ARC_LCD_WriteReg(0x0090,0x007F); 
    ARC_LCD_WriteReg(0x0026,0x0004); 

    ARC_SysTick_Delay(40);  

    ARC_LCD_WriteReg(0x0026,0x0024); 
    ARC_LCD_WriteReg(0x0026,0x002C); 

    ARC_SysTick_Delay(40);   
    ARC_LCD_WriteReg(0x0070,0x0008); 
    ARC_LCD_WriteReg(0x0026,0x003C);  
    ARC_LCD_WriteReg(0x0057,0x0002); 
    ARC_LCD_WriteReg(0x0055,0x0000); 
    ARC_LCD_WriteReg(0x0057,0x0000);
 } 

/**
  * @brief  initialize panel.
  * @param  None.
  * @retval None
  */
void ARC_ILI9325_Init(LCD_Direction_TypeDef lcd_dir)
{
    /* Start Initial Sequence ------------------------------------------------*/
    ARC_LCD_WriteReg(LCD_REG_00H, 0x0001); /* Start internal OSC. */
    ARC_LCD_WriteReg(LCD_REG_01H, 0x0100); /* Set SS and SM bit */
    ARC_LCD_WriteReg(LCD_REG_02H, 0x0700); /* Set 1 line inversion */
    ARC_LCD_WriteReg(LCD_REG_03H, (1<<12)|(3<<4)|(0<<3)); /* Set GRAM write direction and BGR=1. */
    ARC_LCD_WriteReg(LCD_REG_04H, 0x0000); /* Resize register */
    ARC_LCD_WriteReg(LCD_REG_08H, 0x0202); /* Set the back porch and front porch */
    ARC_LCD_WriteReg(LCD_REG_09H, 0x0000); /* Set non-display area refresh cycle ISC[3:0] */
    ARC_LCD_WriteReg(LCD_REG_0AH, 0x0000); /* FMARK function */
    ARC_LCD_WriteReg(LCD_REG_0CH, 0x0000); /* RGB interface setting */
    ARC_LCD_WriteReg(LCD_REG_0DH, 0x0000); /* Frame marker Position */
    ARC_LCD_WriteReg(LCD_REG_0FH, 0x0000); /* RGB interface polarity */

    /* Power On sequence -----------------------------------------------------*/
    ARC_LCD_WriteReg(LCD_REG_10H, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    ARC_LCD_WriteReg(LCD_REG_11H, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
    ARC_LCD_WriteReg(LCD_REG_12H, 0x0000); /* VREG1OUT voltage */
    ARC_LCD_WriteReg(LCD_REG_13H, 0x0000); /* VDV[4:0] for VCOM amplitude */
    ARC_SysTick_Delay(200);                      /* Dis-charge capacitor power voltage (200ms) */
    ARC_LCD_WriteReg(LCD_REG_10H, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    ARC_LCD_WriteReg(LCD_REG_11H, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
    ARC_SysTick_Delay(50);                       /* Delay 50 ms */
    ARC_LCD_WriteReg(LCD_REG_12H, 0x0139); /* VREG1OUT voltage */
    ARC_SysTick_Delay(50);                       /* Delay 50 ms */
    ARC_LCD_WriteReg(LCD_REG_13H, 0x1d00); /* VDV[4:0] for VCOM amplitude */
    ARC_LCD_WriteReg(LCD_REG_29H, 0x0013); /* VCM[4:0] for VCOMH */
    ARC_SysTick_Delay(50);                       /* Delay 50 ms */
    ARC_LCD_WriteReg(LCD_REG_20H, 0x0000); /* GRAM horizontal Address */
    ARC_LCD_WriteReg(LCD_REG_21H, 0x0000); /* GRAM Vertical Address */

    /* Adjust the Gamma Curve (ILI9325)---------------------------------------*/
    ARC_LCD_WriteReg(LCD_REG_30H, 0x0007);
    ARC_LCD_WriteReg(LCD_REG_31H, 0x0302);
    ARC_LCD_WriteReg(LCD_REG_32H, 0x0105);
    ARC_LCD_WriteReg(LCD_REG_35H, 0x0206);
    ARC_LCD_WriteReg(LCD_REG_36H, 0x0808);
    ARC_LCD_WriteReg(LCD_REG_37H, 0x0206);
    ARC_LCD_WriteReg(LCD_REG_38H, 0x0504);
    ARC_LCD_WriteReg(LCD_REG_39H, 0x0007);
    ARC_LCD_WriteReg(LCD_REG_3CH, 0x0105);
    ARC_LCD_WriteReg(LCD_REG_3DH, 0x0808);

    /* Set GRAM area ---------------------------------------------------------*/
    ARC_LCD_WriteReg(LCD_REG_50H, 0x0000); /* Horizontal GRAM Start Address */
    ARC_LCD_WriteReg(LCD_REG_51H, 0x00EF); /* Horizontal GRAM End Address */
    ARC_LCD_WriteReg(LCD_REG_52H, 0x0000); /* Vertical GRAM Start Address */
    ARC_LCD_WriteReg(LCD_REG_53H, 0x013F); /* Vertical GRAM End Address */

    ARC_LCD_WriteReg(LCD_REG_60H,  0xA700); /* Gate Scan Line(GS=1, scan direction is G320~G1) */
    ARC_LCD_WriteReg(LCD_REG_61H,  0x0001); /* NDL,VLE, REV */
    ARC_LCD_WriteReg(LCD_REG_6AH, 0x0000); /* set scrolling line */

    /* Partial Display Control -----------------------------------------------*/
    ARC_LCD_WriteReg(LCD_REG_80H, 0x0000);
    ARC_LCD_WriteReg(LCD_REG_81H, 0x0000);
    ARC_LCD_WriteReg(LCD_REG_82H, 0x0000);
    ARC_LCD_WriteReg(LCD_REG_83H, 0x0000);
    ARC_LCD_WriteReg(LCD_REG_84H, 0x0000);
    ARC_LCD_WriteReg(LCD_REG_85H, 0x0000);

    /* Panel Control ---------------------------------------------------------*/
    ARC_LCD_WriteReg(LCD_REG_90H, 0x0010);
    ARC_LCD_WriteReg(LCD_REG_92H, 0x0000);
    ARC_LCD_WriteReg(LCD_REG_93H, 0x0003);
    ARC_LCD_WriteReg(LCD_REG_95H, 0x0110);
    ARC_LCD_WriteReg(LCD_REG_97H, 0x0000);
    ARC_LCD_WriteReg(LCD_REG_98H, 0x0000);

    /* set GRAM write direction and BGR = 1 */
    /* I/D=00 (Horizontal : increment, Vertical : decrement) */
    /* AM=1 (address is updated in vertical writing direction) */
    ARC_LCD_WriteReg(LCD_REG_03H, (1<<12)|(3<<4)|(0<<3));

    ARC_LCD_WriteReg(LCD_REG_07H, 0x0133); /* 262K color and display ON */
}

/**
  * @brief  initialize panel.
  * @param  None.
  * @retval None
  */
void ARC_ILI9320_Init(LCD_Direction_TypeDef lcd_dir)
{
    ARC_SysTick_Delay(50); /* Delay 50 ms */
    /* Start Initial Sequence ------------------------------------------------*/
    ARC_LCD_WriteReg(LCD_REG_E5H, 0x8000); /* Set the internal vcore voltage */
    ARC_LCD_WriteReg(LCD_REG_00H,  0x0001); /* Start internal OSC. */
    ARC_LCD_WriteReg(LCD_REG_01H,  0x0100); /* set SS and SM bit */
    ARC_LCD_WriteReg(LCD_REG_02H,  0x0700); /* set 1 line inversion */
    ARC_LCD_WriteReg(LCD_REG_03H,  (1<<12)|(3<<4)|(0<<3)); /* set GRAM write direction and BGR=1. */
    ARC_LCD_WriteReg(LCD_REG_04H,  0x0000); /* Resize register */
    ARC_LCD_WriteReg(LCD_REG_08H,  0x0202); /* set the back porch and front porch */
    ARC_LCD_WriteReg(LCD_REG_09H,  0x0000); /* set non-display area refresh cycle ISC[3:0] */
    ARC_LCD_WriteReg(LCD_REG_0AH, 0x0000); /* FMARK function */
    ARC_LCD_WriteReg(LCD_REG_0CH, 0x0000); /* RGB interface setting */
    ARC_LCD_WriteReg(LCD_REG_0DH, 0x0000); /* Frame marker Position */
    ARC_LCD_WriteReg(LCD_REG_0FH, 0x0000); /* RGB interface polarity */
    /* Power On sequence -----------------------------------------------------*/
    ARC_LCD_WriteReg(LCD_REG_10H, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    ARC_LCD_WriteReg(LCD_REG_11H, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
    ARC_LCD_WriteReg(LCD_REG_12H, 0x0000); /* VREG1OUT voltage */
    ARC_LCD_WriteReg(LCD_REG_13H, 0x0000); /* VDV[4:0] for VCOM amplitude */
    ARC_SysTick_Delay(200);                      /* Dis-charge capacitor power voltage (200ms) */
    ARC_LCD_WriteReg(LCD_REG_10H, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
    ARC_LCD_WriteReg(LCD_REG_11H, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
    ARC_SysTick_Delay(50);                       /* Delay 50 ms */
    ARC_LCD_WriteReg(LCD_REG_12H, 0x0139); /* VREG1OUT voltage */
    ARC_SysTick_Delay(50);                       /* Delay 50 ms */
    ARC_LCD_WriteReg(LCD_REG_13H, 0x1d00); /* VDV[4:0] for VCOM amplitude */
    ARC_LCD_WriteReg(LCD_REG_29H, 0x0013); /* VCM[4:0] for VCOMH */
    ARC_SysTick_Delay(50);                       /* Delay 50 ms */
    ARC_LCD_WriteReg(LCD_REG_20H, 0x0000); /* GRAM horizontal Address */
    ARC_LCD_WriteReg(LCD_REG_21H, 0x0000); /* GRAM Vertical Address */
    /* Adjust the Gamma Curve ------------------------------------------------*/
    ARC_LCD_WriteReg(LCD_REG_30H, 0x0006);
    ARC_LCD_WriteReg(LCD_REG_31H, 0x0101);
    ARC_LCD_WriteReg(LCD_REG_32H, 0x0003);
    ARC_LCD_WriteReg(LCD_REG_35H, 0x0106);
    ARC_LCD_WriteReg(LCD_REG_36H, 0x0b02);
    ARC_LCD_WriteReg(LCD_REG_37H, 0x0302);
    ARC_LCD_WriteReg(LCD_REG_38H, 0x0707);
    ARC_LCD_WriteReg(LCD_REG_39H, 0x0007);
    ARC_LCD_WriteReg(LCD_REG_3CH, 0x0600);
    ARC_LCD_WriteReg(LCD_REG_3DH, 0x020b);
  
    /* Set GRAM area ---------------------------------------------------------*/
    ARC_LCD_WriteReg(LCD_REG_50H, 0x0000); /* Horizontal GRAM Start Address */
    ARC_LCD_WriteReg(LCD_REG_51H, 0x00EF); /* Horizontal GRAM End Address */
    ARC_LCD_WriteReg(LCD_REG_52H, 0x0000); /* Vertical GRAM Start Address */
    ARC_LCD_WriteReg(LCD_REG_53H, 0x013F); /* Vertical GRAM End Address */
    ARC_LCD_WriteReg(LCD_REG_60H,  0x2700); /* Gate Scan Line */
    ARC_LCD_WriteReg(LCD_REG_61H,  0x0001); /* NDL,VLE, REV */
    ARC_LCD_WriteReg(LCD_REG_6AH, 0x0000); /* set scrolling line */
    /* Partial Display Control -----------------------------------------------*/
    ARC_LCD_WriteReg(LCD_REG_80H, 0x0000);
    ARC_LCD_WriteReg(LCD_REG_81H, 0x0000);
    ARC_LCD_WriteReg(LCD_REG_82H, 0x0000);
    ARC_LCD_WriteReg(LCD_REG_83H, 0x0000);
    ARC_LCD_WriteReg(LCD_REG_84H, 0x0000);
    ARC_LCD_WriteReg(LCD_REG_85H, 0x0000);
    /* Panel Control ---------------------------------------------------------*/
    ARC_LCD_WriteReg(LCD_REG_90H, 0x0010);
    ARC_LCD_WriteReg(LCD_REG_92H, 0x0000);
    ARC_LCD_WriteReg(LCD_REG_93H, 0x0003);
    ARC_LCD_WriteReg(LCD_REG_95H, 0x0110);
    ARC_LCD_WriteReg(LCD_REG_97H, 0x0000);
    ARC_LCD_WriteReg(LCD_REG_98H, 0x0000);
    /* Set GRAM write direction and BGR = 1 */
    /* I/D=01 (Horizontal : increment, Vertical : decrement) */
    /* AM=1 (address is updated in vertical writing direction) */
    ARC_LCD_WriteReg(LCD_REG_03H, (1<<12)|(3<<4)|(0<<3));
    ARC_LCD_WriteReg(LCD_REG_07H, 0x0173); /* 262K color and display ON */
}

/**
  * @brief  initialize panel.
  * @param  None.
  * @retval None
  */
void ARC_SPFD5408_Init(LCD_Direction_TypeDef lcd_dir)
{
    ARC_LCD_WriteReg(LCD_REG_01H,0x0100);                                
    ARC_LCD_WriteReg(LCD_REG_02H,0x0700); //LCD Driving Waveform Contral 
    ARC_LCD_WriteReg(LCD_REG_03H,0x1030); //Entry Mode setting    
    ARC_LCD_WriteReg(LCD_REG_04H,0x0000); //Scalling Control register     
    ARC_LCD_WriteReg(LCD_REG_08H,0x0207); //Display Control 2 
    ARC_LCD_WriteReg(LCD_REG_09H,0x0000); //Display Control 3   
    ARC_LCD_WriteReg(LCD_REG_0AH,0x0000); //Frame Cycle Control     
    ARC_LCD_WriteReg(LCD_REG_0CH,0x0000); //External Display Interface Control 1 
    ARC_LCD_WriteReg(LCD_REG_0DH,0x0000); //Frame Maker Position        
    ARC_LCD_WriteReg(LCD_REG_0FH,0x0000); //External Display Interface Control 2 
    ARC_SysTick_Delay(20);
    ARC_LCD_WriteReg(LCD_REG_10H,0x16B0); //0x14B0 //Power Control 1
    ARC_LCD_WriteReg(LCD_REG_11H,0x0001); //0x0007 //Power Control 2
    ARC_LCD_WriteReg(LCD_REG_17H,0x0001); //0x0000 //Power Control 3
    ARC_LCD_WriteReg(LCD_REG_12H,0x0138); //0x013B //Power Control 4
    ARC_LCD_WriteReg(LCD_REG_13H,0x0800); //0x0800 //Power Control 5
    ARC_LCD_WriteReg(LCD_REG_29H,0x0009); //NVM read data 2
    ARC_LCD_WriteReg(LCD_REG_2AH,0x0009); //NVM read data 3
    ARC_LCD_WriteReg(LCD_REG_A4H,0x0000);   
    ARC_LCD_WriteReg(LCD_REG_50H,0x0000); //Horizontal GRAM Start Address
    ARC_LCD_WriteReg(LCD_REG_51H,0x00EF); //Horizontal GRAM End Address
    ARC_LCD_WriteReg(LCD_REG_52H,0x0000); //Vertical GRAM Start Address
    ARC_LCD_WriteReg(LCD_REG_53H,0x013F); //Vertical GRAM End Address
    ARC_LCD_WriteReg(LCD_REG_60H,0xA700); //Driver Output Control
    ARC_LCD_WriteReg(LCD_REG_61H,0x0001); //Driver Output Control
    ARC_LCD_WriteReg(LCD_REG_6AH,0x0000); //Vertical Scroll Control
    ARC_LCD_WriteReg(LCD_REG_80H,0x0000); //Display Position 每 Partial Display 1
    ARC_LCD_WriteReg(LCD_REG_81H,0x0000); //RAM Address Start 每 Partial Display 1
    ARC_LCD_WriteReg(LCD_REG_82H,0x0000); //RAM address End - Partial Display 1
    ARC_LCD_WriteReg(LCD_REG_83H,0x0000); //Display Position 每 Partial Display 2
    ARC_LCD_WriteReg(LCD_REG_84H,0x0000); //RAM Address Start 每 Partial Display 2
    ARC_LCD_WriteReg(LCD_REG_85H,0x0000); //RAM address End 每 Partail Display2
    ARC_LCD_WriteReg(LCD_REG_90H,0x0013); //Frame Cycle Control
    ARC_LCD_WriteReg(LCD_REG_92H,0x0000); //Panel Interface Control 2
    ARC_LCD_WriteReg(LCD_REG_93H,0x0003); //Panel Interface control 3
    ARC_LCD_WriteReg(LCD_REG_95H,0x0110); //Frame Cycle Control
    ARC_LCD_WriteReg(LCD_REG_07H,0x0173);       
    ARC_SysTick_Delay(50);
}

/**
  * @brief  Get the ID of the LCD controller.
  * @param  None
  * @retval The ID of the LCD controller
  */
uint16_t ARC_LCD_ID_Check()
{
    uint16_t DeviceCode = 0xFFFF;
    ARC_SysTick_Delay(100); /* delay 100 ms */
    DeviceCode = ARC_LCD_ReadReg(LCD_REG_00H); 
    if((DeviceCode != 0x9320) && (DeviceCode != 0x9325) && 
       (DeviceCode != 0x9328) && (DeviceCode != 0x5408))
    {
        ARC_SysTick_Delay(100); /* delay 100 ms */
        DeviceCode = ARC_LCD_ReadReg(LCD_REG_67H); 
    }
    return DeviceCode;
}

/**
  * @brief  Initialize LCD.
  * @param  None
  * @retval None
  */
int32_t ARC_LCD_Init(void)
{
    uint16_t DeviceCode;
    
    ARC_LCD_Param.LCD_Type = LCD_OTHER;
    ARC_LCD_Param.LCD_BusType = LCD_I80;
    ARC_LCD_Param.LCD_Direction = LCD_DIR_VERTICAL;
    ARC_LCD_RCC_Init();
    ARC_LCD_GPIO_Init();
    
    DeviceCode = ARC_LCD_ID_Check();

    if(DeviceCode == 0x9320)
    {
        ARC_LCD_Param.LCD_Type = LCD_ILI9320;
        ARC_ILI9320_Init(ARC_LCD_Param.LCD_Direction);
    }
    else if(DeviceCode == 0x9325 || DeviceCode == 0x9328)
    {
        ARC_LCD_Param.LCD_Type = LCD_ILI9325;
        ARC_ILI9325_Init(ARC_LCD_Param.LCD_Direction);
    }
    else if(DeviceCode == 0x5408)
    {
        ARC_LCD_Param.LCD_Type = LCD_SPFD5408;
        ARC_SPFD5408_Init(ARC_LCD_Param.LCD_Direction);
    }
    else if(DeviceCode == 0x47)
    {
        ARC_LCD_Param.LCD_Type = LCD_HX8347A;
        ARC_HX8347A_Init(ARC_LCD_Param.LCD_Direction);
    }
    else
    {
        return 1;
    }
    return 0;
}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void ARC_LCD_On(void)
{
    ARC_LCD_BL_SET();
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void ARC_LCD_Off(void)
{
    ARC_LCD_BL_RESET();
}

/**
  * @brief  set a pixel at position (x, y) with a color ColorIndex.
  * @param  x, the x position of the LCD
  * @param  y, the y position of the LCD
  * @param  ColorIndex, the color to be set to the pixel.
  * @retval None
  */
void ARC_LCD_SetPixelIndex(int32_t x,int32_t y,int32_t ColorIndex)
{
    ARC_LCD_SetCursor(x, y);
    ARC_LCD_WriteReg(LCD_REG_22H, ColorIndex);
}

/**
  * @brief  get a pixel value at position (x, y).
  * @param  x, the x position of the LCD
  * @param  y, the y position of the LCD
  * @retval the pixel value
  */
uint32_t ARC_LCD_GetPixelIndex(int32_t x, int32_t y) 
{
    uint16_t temp;
    ARC_LCD_SetCursor(x, y);
    ARC_LCD_WriteRegIndex(LCD_REG_22H);
    ARC_LCD_ReadGRAMData(temp);
    return  (((temp)  & 0x1f)<<11) + (((temp>>5)  & 0x3f)<<5) + (((temp>>11) & 0x1f));
}

#if (defined ARC_UCGUI && defined ARC_FREERTOS)
/**
  * @brief  draw a line starting from position (x, y).
  */
__inline void  ARC_DrawBitLine1BPP(int32_t x, int32_t y, const uint8_t *p, int32_t Diff, int32_t xsize, const uint16_t *pTrans) 
{
    uint16_t Index0 = *(pTrans + 0);
    uint16_t Index1 = *(pTrans + 1);
    x += Diff;
    switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) 
    {
        case LCD_DRAWMODE_NORMAL:
            do 
            {
                ARC_LCD_SetPixelIndex(x++, y, (*p & (0x80 >> Diff)) ? Index1 : Index0);
                if (++Diff == 8) 
                {
                    Diff = 0;
                    p++;
                }
            } while (--xsize);
            break;
            
        case LCD_DRAWMODE_TRANS:
            do 
            {
                if (*p & (0x80 >> Diff))
                    ARC_LCD_SetPixelIndex(x, y, Index1);
                x++;
                if (++Diff == 8) 
                {
                    Diff = 0;
                    p++;
                }
            } while (--xsize);
            break;
            
        case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
        case LCD_DRAWMODE_XOR:
            do 
            {
                if (*p & (0x80 >> Diff)) 
                {
                    int32_t Pixel = LCD_L0_GetPixelIndex(x, y);
                    ARC_LCD_SetPixelIndex(x, y, LCD_NUM_COLORS - 1 - Pixel);
                }
                x++;
                if (++Diff == 8) 
                {
                    Diff = 0;
                    p++;
                }
            } while (--xsize);
            break;
        default:
            break;
    }
}

/**
  * @brief  draw a line starting from position (x, y).
  */
__inline void  ARC_DrawBitLine2BPP(int32_t x, int32_t y, const uint8_t * p, int32_t Diff, int32_t xsize, const uint16_t * pTrans) 
{
    uint16_t Pixels = *p;
    int32_t CurrentPixel = Diff;
    int32_t Shift;
    uint16_t Index;
    int32_t PixelValue;

    x += Diff;
    switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) 
    {
        case LCD_DRAWMODE_NORMAL:
            do 
            {
                Shift = (3 - CurrentPixel) << 1;
                Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
                PixelValue = pTrans ? (*(pTrans + Index)) : Index;
            
                ARC_LCD_SetPixelIndex(x++, y, PixelValue);
                if (++CurrentPixel == 4) 
                {
                    CurrentPixel = 0;
                    Pixels = *(++p);
                }
            } while (--xsize);
            break;
            
        case LCD_DRAWMODE_TRANS:
            do 
            {
                Shift = (3 - CurrentPixel) << 1;
                Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
                
                if (Index) 
                {
                    PixelValue = pTrans ? (*(pTrans + Index)) : Index;
                    ARC_LCD_SetPixelIndex(x, y, PixelValue);
                }
                x++;
                if (++CurrentPixel == 4) 
                {
                    CurrentPixel = 0;
                    Pixels = *(++p);
                }
            } while (--xsize);
            break;
            
            default:
                break;
    }
}

/**
  * @brief  draw a line starting from position (x, y).
  */
__inline void  ARC_DrawBitLine4BPP(int32_t x, int32_t y, uint8_t const  * p, int32_t Diff, int32_t xsize, const uint16_t * pTrans) 
{
    uint16_t Pixels = *p;
    int32_t CurrentPixel = Diff;
    int32_t Shift;
    uint16_t Index;
    int32_t PixelValue;

    x += Diff;
    switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) 
    {
        case LCD_DRAWMODE_NORMAL:
            do 
            {
                Shift = (1 - CurrentPixel) << 2;
                Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
                PixelValue = pTrans ? (*(pTrans + Index)) : Index;
                
                ARC_LCD_SetPixelIndex(x++, y, PixelValue);
                if (++CurrentPixel == 2) 
                {
                    CurrentPixel = 0;
                    Pixels = *(++p);
                }
            } while (--xsize);
            break;
            
        case LCD_DRAWMODE_TRANS:
            do 
            {
                Shift = (1 - CurrentPixel) << 2;
                Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
                
                if (Index) 
                {
                    PixelValue = pTrans ? (*(pTrans + Index)) : Index;
                    ARC_LCD_SetPixelIndex(x, y, PixelValue);
                }
                x++;
                if (++CurrentPixel == 2) 
                {
                    CurrentPixel = 0;
                    Pixels = *(++p);
                }
            } while (--xsize);
            break;
            
        default:
            break;
    }
}

/**
  * @brief  draw a line starting from position (x, y).
  */
__inline void  ARC_DrawBitLine8BPP(int32_t x, int32_t y, uint8_t const  * p, int32_t xsize, const uint16_t * pTrans) 
{
    int32_t PixelValue;
    switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) 
    {
        case LCD_DRAWMODE_NORMAL:
            for (; xsize > 0; xsize--, x++, p++) 
            {
                
                PixelValue = pTrans ? *(pTrans + *p) : *p;
                ARC_LCD_SetPixelIndex(x, y, PixelValue);
            }
            break;
        case LCD_DRAWMODE_TRANS:
            for (; xsize > 0; xsize--, x++, p++) 
            {
                if (*p) 
                {
                    PixelValue = pTrans ? *(pTrans + *p) : *p;
                    ARC_LCD_SetPixelIndex(x, y, PixelValue);
                }
            }
            break;
        default:
            break;
    }
}

/**
  * @brief  draw a line starting from position (x, y).
  */
__inline void  ARC_DrawBitLine16BPP(int32_t x, int32_t y, const uint16_t *p, int32_t xsize, const uint16_t *pTrans)
{
    const  uint16_t *PixelIndex;
    if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) == LCD_DRAWMODE_NORMAL) 
    {
        PixelIndex = pTrans ? (pTrans + *p) : p;
        ARC_LCD_SetMultiPixelsIndex(x, y, PixelIndex, xsize);
    } 
    else 
    {
        for (; xsize > 0; xsize--, x++, p++)
        {
            if (*p) 
            {
                PixelIndex = pTrans ? (pTrans + *p) : p;
                ARC_LCD_SetPixelIndex(x, y, *PixelIndex);
            }
        }
    }
}

/**
  * @brief  draw a bitmap.
  */
void ARC_LCD_DrawBitmap(int32_t x0, int32_t y0, int32_t xsize, int32_t ysize, int32_t BitsPerPixel, int32_t BytesPerLine,
                        const uint8_t * pData, int32_t Diff, const uint16_t* pTrans)
{
    int32_t i;
    for (i = 0; i < ysize; i++) 
    {
        switch (BitsPerPixel) 
        {
            case 1:
                ARC_DrawBitLine1BPP(x0, i + y0, pData, Diff, xsize, pTrans);
                break;
            case 2:
                ARC_DrawBitLine2BPP(x0, i + y0, pData, Diff, xsize, pTrans);
                break;
            case 4:
                ARC_DrawBitLine4BPP(x0, i + y0, pData, Diff, xsize, pTrans);
                break;
            case 8:
                ARC_DrawBitLine8BPP(x0, i + y0, pData, xsize, pTrans);
                break;
            case 16:
                ARC_DrawBitLine16BPP(x0, i + y0, (const uint16_t *)pData, xsize, pTrans);
                break;
        }
        pData += BytesPerLine;
    }
}

/**
  * @brief  draw a horizontal line.
  */
void ARC_LCD_DrawHLine  (int32_t x0, int32_t y,  int32_t x1)
{
    ARC_LCD_SetCursor(x0, y);
    ARC_LCD_WriteGRAM_Same(LCD_COLORINDEX, (x1 - x0 + 1));
}

/**
  * @brief  draw a vertical line.
  */
void ARC_LCD_DrawVLine  (int32_t x, int32_t y0,  int32_t y1) 
{
    uint16_t i;
    for(i = y0; i <= y1; i ++)
        ARC_LCD_SetPixelIndex(x, i, LCD_COLORINDEX);
}

/**
  * @brief  fill a rectangle.
  */
void ARC_LCD_FillRect  (int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
    ARC_LCD_SetDisplayWindow(x0, y0, x1, y1);
    ARC_LCD_WriteGRAM_Same(LCD_COLORINDEX, ((x1 - x0 + 1) * (y1 - y0 + 1) - 1));
    ARC_LCD_SetDisplayWindow(0, 0, LCD_XSIZE - 1, LCD_YSIZE - 1);
}

/**
  * @brief  xor a pixel.
  */
void ARC_LCD_XorPixel(int32_t x, int32_t y) 
{
    uint16_t Index = ARC_LCD_GetPixelIndex(x,y);
    ARC_LCD_SetPixelIndex(x, y, LCD_NUM_COLORS - 1 - Index);
}

/**
  * @brief  dummy function.
  */
void ARC_LCD_SetOrg(uint8_t Pos, uint32_t color)
{
}

/**
  * @brief  dummy function.
  */
void ARC_LCD_SetLUTEntry(void)
{
}

/**
  * @brief  dummy function.
  */
void * ARC_LCD_GetDevFunc(int32_t Index)
{
    GUI_USE_PARA(Index);
    return NULL;
}

int32_t LCD_L0_Init(void) __attribute__ (( alias ("ARC_LCD_Init")));
void LCD_L0_On(void)  __attribute__ (( alias ("ARC_LCD_On")));
void LCD_L0_DrawBitmap(int32_t x0, int32_t y0, int32_t xsize, int32_t ysize, int32_t BitsPerPixel, int32_t BytesPerLine,
                       const uint8_t GUI_UNI_PTR * pData, int32_t Diff, const uint16_t* pTrans) __attribute__ (( alias ("ARC_LCD_DrawBitmap")));
void LCD_L0_DrawHLine (int32_t x0, int32_t y,  int32_t x1) __attribute__ (( alias ("ARC_LCD_DrawHLine")));
void LCD_L0_DrawVLine (int32_t x0, int32_t y,  int32_t x1) __attribute__ (( alias ("ARC_LCD_DrawVLine")));
void LCD_L0_FillRect (int32_t x0, int32_t y0, int32_t x1, int32_t y1) __attribute__ (( alias ("ARC_LCD_FillRect")));
void LCD_L0_SetPixelIndex(int32_t x, int32_t y, int32_t ColorIndex)  __attribute__ (( alias ("ARC_LCD_SetPixelIndex")));
void LCD_L0_XorPixel(int32_t x, int32_t y)   __attribute__ (( alias ("ARC_LCD_XorPixel")));
uint32_t LCD_L0_GetPixelIndex(int32_t x, int32_t y)   __attribute__ (( alias ("ARC_LCD_GetPixelIndex")));
void LCD_L0_SetOrg(int32_t x, int32_t y)   __attribute__ (( alias ("ARC_LCD_SetOrg")));
void LCD_L0_SetLUTEntry(uint8_t Pos, LCD_COLOR color) __attribute__ (( alias ("ARC_LCD_SetLUTEntry")));
void * LCD_L0_GetDevFunc(int32_t Index) __attribute__ (( alias ("ARC_LCD_GetDevFunc")));
#else

/**
  * @brief  draw a big point (3 x 3) on the specific position on the LCD screen.
  * @param  x: the center x position.
  * @param  y: the center y position.
  * @param  pointColor: the big point color.
  * @retval None
  */
void ARC_LCD_DrawBigPoint(uint16_t x,uint16_t y, uint16_t pointColor)
{
    uint8_t i, j;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            ARC_LCD_SetPixelIndex(x - 1 + i, y - 1 + j, pointColor);
}

/**
  * @brief  draw a cross on the specific position on the LCD screen.
  * @param  x: the center x position.
  * @param  y: the center y position.
  * @param  pointColor: the point color of the cross.
  * @retval None
  */
void ARC_LCD_DrawCross(uint16_t x, uint16_t y, uint16_t pointColor)
{
    int8_t i;
    for(i = -5; i <= 5; i++)
        ARC_LCD_SetPixelIndex(x + i, y, pointColor);
    
    for(i = -5; i <= 5; i++)
        ARC_LCD_SetPixelIndex(x, y + i, pointColor);
}


/**
  * @brief  show a character on the LCD screen.
  * @param  *LCDParam, the LCD parameters.
  * @retval None
  */
void ARC_LCD_ShowChar(int32_t x, int32_t y, const uint8_t *lcd_font)
{   
    uint8_t point;
    uint8_t v, h;
    uint8_t font;

    font = *(lcd_font) - ' ';
    
    for(v = 0; v < 12; v++)
    {
        point = asc2_1206[font][v]; /* using 1206 font */
        for(h = 0; h < (12 / 2); h++)
        {                 
            if(point & 0x01)
                ARC_LCD_SetPixelIndex(x + h, y + v, LCD_COLOR_WHITE);

            point >>= 1; 
        }
    }
}  

/**
  * @brief  show strings on the LCD screen.
  * @param  *LCDParam, the LCD parameters.
  * @retval None
  */
void ARC_LCD_ShowString(int32_t x, int32_t y, const uint8_t *lcd_font)
{
    while(*lcd_font != '\0')
    {       
        ARC_LCD_ShowChar(x, y, lcd_font);
        x += 12 / 2;
        lcd_font++;
    }  
}

void ARC_LCD_Clear  (uint16_t lcdColor)
{
    ARC_LCD_SetCursor(0, 0);
    ARC_LCD_WriteGRAM_Same(lcdColor, 240 * 320);
}

#endif

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
