/**
  ******************************************************************************
  * @file    stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x.h"
#include "ARC_GPIO.h"
#include "ARC_USART.h"
#include "ARC_I2C.h"
#include "ARC_TouchScreen.h"
#include "ARC_SysTick.h"
#include "ARC_LCD.h"
#ifdef ARC_USB_MOUSE
#include "usb_istr.h"
#endif
#include <stdio.h>

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

#ifdef ARC_ADC
uint16_t volatile ADC1ConvertedValue;
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

#ifndef ARC_FREERTOS
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    if (ARC_Get_TimingDelay() != 0x00)
    { 
        ARC_Decrease_TimingDelay();
    }
}
#endif

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles WWDG interrupt request.
  * @param  None
  * @retval None
  */
void WWDG_IRQHandler(void)
{
}

/**
  * @brief  This function handles PVD interrupt request.
  * @param  None
  * @retval None
  */
void PVD_IRQHandler(void)
{
}

/**
  * @brief  This function handles Tamper interrupt request.
  * @param  None
  * @retval None
  */
void TAMPER_IRQHandler(void)
{
}

/**
  * @brief  This function handles RTC global interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
}

/**
  * @brief  This function handles Flash interrupt request.
  * @param  None
  * @retval None
  */
void FLASH_IRQHandler(void)
{
}

/**
  * @brief  This function handles RCC interrupt request.
  * @param  None
  * @retval None
  */
void RCC_IRQHandler(void)
{
}

/**
  * @brief  This function handles External interrupt Line 0 request..
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
}

/**
  * @brief  This function handles External interrupt Line 1 request.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
}


/**
  * @brief  This function handles External interrupt Line 2 request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{
#ifdef ARC_BUTTON_EXTI
    if(EXTI_GetITStatus(EXTI_Line2) != RESET)
    {
        /* Toggle LED1 and LED2 */
        ARC_LED_Toggle(0);
        ARC_LED_Toggle(1);
        /* Clear the Key Button EXTI line pending bit */
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
#endif

#ifdef ARC_IWDG
    if(EXTI_GetITStatus(EXTI_Line2) != RESET)
    {
        IWDG_ReloadCounter();
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
#endif

#ifdef ARC_TOUCHSCREEN
    pen_state_struct *pen_st;
    if(EXTI_GetITStatus(EXTI_Line2) != RESET)
    {       
        pen_st = ARC_get_penstate();
        pen_st->force_adjust = 1;
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
#endif
}

/**
  * @brief  This function handles External interrupt Line 3 request.
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void)
{
#ifdef ARC_BUTTON_EXTI
    if(EXTI_GetITStatus(EXTI_Line3) != RESET)
    {
        /* Toggle LED1 and LED2 */
        ARC_LED_Toggle(0);
        ARC_LED_Toggle(1);
        /* Clear the Key Button EXTI line pending bit */
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
#endif

#ifdef ARC_IWDG
    if(EXTI_GetITStatus(EXTI_Line3) != RESET)
    {
        IWDG_ReloadCounter();
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
#endif

#ifdef ARC_TOUCHSCREEN
    pen_state_struct *pen_st;
    if(EXTI_GetITStatus(EXTI_Line3) != RESET)
    {       
        pen_st = ARC_get_penstate();
        pen_st->force_adjust = 1;
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
#endif
}

/**
  * @brief  This function handles External interrupt Line 4 request.
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void)
{
}

/**
  * @brief  This function handles DMA1 Channel1 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel1_IRQHandler(void)
{
}

/**
  * @brief  This function handles DMA1 Channel2 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel2_IRQHandler(void)
{
}

/**
  * @brief  This function handles DMA1 Channel3 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel3_IRQHandler(void)
{
}

/**
  * @brief  This function handles DMA1 Channel4 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel4_IRQHandler(void)
{
}

/**
  * @brief  This function handles DMA1 Channel5 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel5_IRQHandler(void)
{
}

/**
  * @brief  This function handles DMA1 Channel6 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel6_IRQHandler(void)
{
}

/**
  * @brief  This function handles DMA1 Channel7 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel7_IRQHandler(void)
{
}


/**
  * @brief  This function handles ADC1 and ADC2 global interrupts requests.
  * @param  None
  * @retval None
  */
void ADC1_2_IRQHandler(void)
{
#ifdef ARC_ADC
	/* Get injected channel13 converted value */
	ADC1ConvertedValue = ADC_GetConversionValue(ADC1);
#endif
}

/**
  * @brief  This function handles USB High Priority or CAN TX interrupts request.
  * @param  None
  * @retval None
  */
void USB_HP_CAN1_TX_IRQHandler(void)
{
    while(1)
    {
    }
}

/**
  * @brief  This function handles USB Low Priority or CAN RX0 interrupts request.
  * @param  None
  * @retval None
  */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
#ifdef ARC_USB_MOUSE
    USB_Istr();
#endif
}

/**
  * @brief  This function handles CAN RX1 interrupt request.
  * @param  None
  * @retval None
  */
void CAN_RX1_IRQHandler(void)
{
}

/**
  * @brief  This function handles CAN SCE interrupt request.
  * @param  None
  * @retval None
  */
void CAN_SCE_IRQHandler(void)
{
}

/**
  * @brief  This function handles External lines 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
#if (defined ARC_TOUCHSCREEN && defined ARC_FREERTOS)
    pen_state_struct *pen_st;
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    if(EXTI_GetITStatus(EXTI_Line6) != RESET)
    {       
        pen_st = ARC_get_penstate();
        pen_st->pen_pressed = KEY_DOWN;
        /* 'Give' the semaphore to unblock the task. */
        xSemaphoreGiveFromISR( xBinarySemaphore_ts, &xHigherPriorityTaskWoken );
    
        /* Clear the software interrupt bit using the interrupt controllers
        Clear Pending register. */
        EXTI_ClearITPendingBit(EXTI_Line6);
    
        /* Giving the semaphore may have unblocked a task - if it did and the
        unblocked task has a priority equal to or above the currently executing
        task then xHigherPriorityTaskWoken will have been set to pdTRUE and
        portEND_SWITCHING_ISR() will force a context switch to the newly unblocked
        higher priority task.
    
        NOTE: The syntax for forcing a context switch within an ISR varies between
        FreeRTOS ports.  The portEND_SWITCHING_ISR() macro is provided as part of
        the Cortex M3 port layer for this purpose.  taskYIELD() must never be called
        from an ISR! */
        portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
    }
#endif
#if (defined ARC_TOUCHSCREEN && !defined ARC_FREERTOS)
    pen_state_struct *pen_st;
    if(EXTI_GetITStatus(EXTI_Line6) != RESET)
    {       
        pen_st = ARC_get_penstate();
        pen_st->pen_pressed = KEY_DOWN;
        EXTI_ClearITPendingBit(EXTI_Line6);
    }
#endif
}

/**
  * @brief  This function handles TIM1 Break interrupt request.
  * @param  None
  * @retval None
  */
void TIM1_BRK_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM1 overflow and update interrupt request.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM1 Trigger and commutation interrupts request.
  * @param  None
  * @retval None
  */
void TIM1_TRG_COM_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM1 capture compare interrupt request.
  * @param  None
  * @retval None
  */
void TIM1_CC_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM2 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM3 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM4 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM4_IRQHandler(void)
{
}

/**
  * @brief  This function handles I2C1 Event interrupt request, tx, rx 
  *         buffer and number of bytes will be changed.
  * @param  None
  * @retval None
  */
void I2C1_EV_IRQHandler(void)
{
#ifdef ARC_I2C_IRQ
    uint32_t i2cEvent;
    I2C_param_struct __IO *pI2C_param;

    pI2C_param = ARC_get_I2C_param();
    i2cEvent = I2C_GetLastEvent(I2C1);
    
    switch (i2cEvent)
    {
        case I2C_EVENT_MASTER_MODE_SELECT:/* EV5 */
            if(pI2C_param->I2C_DIRECTION == ARC_I2C_DIRECTION_TX)
            {
                I2C_Send7bitAddress(I2C1, pI2C_param->DeviceAddr, I2C_Direction_Transmitter);
            }
            else
            {
                I2C_Send7bitAddress(I2C1, pI2C_param->DeviceAddr, I2C_Direction_Receiver);
            }
            break;

        /* Master Transmitter -------------------------------------------------------*/
        case I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED:
            I2C_SendData(I2C1, pI2C_param->SubAddr);
            if(pI2C_param->TxNumOfBytes == 0)
                I2C_ITConfig(I2C1, I2C_IT_BUF, DISABLE);
            break;
           
        case I2C_EVENT_MASTER_BYTE_TRANSMITTING:  /* Without BTF, EV8 */     
            if(pI2C_param->TX_I2C_Index < pI2C_param->TxNumOfBytes)
            {
                I2C_SendData(I2C1, pI2C_param->TxData[pI2C_param->TX_I2C_Index++]);
            }
            else 
            {      
                I2C_ITConfig(I2C1, I2C_IT_BUF, DISABLE);
            }
            break;

        case I2C_EVENT_MASTER_BYTE_TRANSMITTED: /* With BTF EV8-2 */
           if(pI2C_param->TX_Generate_stop == 1)
           {
             I2C_GenerateSTOP(I2C1, ENABLE);
             I2C_ITConfig(I2C1, I2C_IT_EVT, DISABLE);
           }
           else
           {
             pI2C_param->I2C_DIRECTION = ARC_I2C_DIRECTION_RX;
             I2C_ITConfig(I2C1, I2C_IT_BUF, ENABLE);
             I2C_GenerateSTART(I2C1, ENABLE);
           }
           break;

        /* Master Receiver -------------------------------------------------------*/
        case I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED:
            if(pI2C_param->RX_I2C_Index == (pI2C_param->RxNumOfBytes - 1))
            {
                I2C_AcknowledgeConfig(I2C1, DISABLE);
                I2C_GenerateSTOP(I2C1, ENABLE);
            }
            break;

        case I2C_EVENT_MASTER_BYTE_RECEIVED:
            pI2C_param->RxData[pI2C_param->RX_I2C_Index++] = I2C_ReceiveData (I2C1);
            if(pI2C_param->RX_I2C_Index == (pI2C_param->RxNumOfBytes - 1))
            {
                I2C_AcknowledgeConfig(I2C1, DISABLE);
                I2C_GenerateSTOP(I2C1, ENABLE);
            }
            break;

        default:
            break;
    }

#endif
}

/**
  * @brief  This function handles I2C1 Error interrupt request.
  * @param  None
  * @retval None
  */
void I2C1_ER_IRQHandler(void)
{
#ifdef ARC_I2C_IRQ
    uint32_t __IO SR1Register =0;

    /* Read the I2C1 status register */
    SR1Register = I2C1->SR1;
    /* If AF = 1 */
    if ((SR1Register & 0x0400) == 0x0400)
    {
        I2C1->SR1 &= 0xFBFF;
        SR1Register = 0;
    }
    /* If ARLO = 1 */
    if ((SR1Register & 0x0200) == 0x0200)
    {
        I2C1->SR1 &= 0xFBFF;
        SR1Register = 0;
    }
    /* If BERR = 1 */
    if ((SR1Register & 0x0100) == 0x0100)
    {
        I2C1->SR1 &= 0xFEFF;
        SR1Register = 0;
    }
    /* If OVR = 1 */
    if ((SR1Register & 0x0800) == 0x0800)
    {
        I2C1->SR1 &= 0xF7FF;
        SR1Register = 0;
    }
#endif
}

/**
  * @brief  This function handles I2C2 Event interrupt request.
  * @param  None
  * @retval None
  */
void I2C2_EV_IRQHandler(void)
{
}

/**
  * @brief  This function handles I2C2 Error interrupt request.
  * @param  None
  * @retval None
  */
void I2C2_ER_IRQHandler(void)
{
}

/**
  * @brief  This function handles SPI1 global interrupt request.
  * @param  None
  * @retval None
  */
void SPI1_IRQHandler(void)
{
}

/**
  * @brief  This function handles SPI2 global interrupt request.
  * @param  None
  * @retval None
  */
void SPI2_IRQHandler(void)
{
}

/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
}

/**
  * @brief  This function handles USART2 global interrupt request.
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
}

/**
  * @brief  This function handles USART3 global interrupt request.
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
}

/**
  * @brief  This function handles External lines 15 to 10 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
}

/**
  * @brief  This function handles RTCAlarm interrupt request.
  * @param  None
  * @retval None
  */
void RTCAlarm_IRQHandler(void)
{
}

/**
  * @brief  This function handles USBWakeUp interrupt request.
  * @param  None
  * @retval None
  */
void USBWakeUp_IRQHandler(void)
{
#ifdef ARC_USB_MOUSE
    EXTI_ClearITPendingBit(EXTI_Line18);
#endif
}

/**
  * @brief  This function handles TIM8 Break interrupt request.
  * @param  None
  * @retval None
  */
void TIM8_BRK_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM8 overflow and update interrupt 
  * @param  None
  * @retval None
  */
void TIM8_UP_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM8 Trigger and commutation interrupts request.
  * @param  None
  * @retval None
  */
void TIM8_TRG_COM_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM8 capture compare interrupt request.
  * @param  None
  * @retval None
  */
void TIM8_CC_IRQHandler(void)
{
}

/**
  * @brief  This function handles ADC3 global interrupt request.
  * @param  None
  * @retval None
  */
void ADC3_IRQHandler(void)
{
}

/**
  * @brief  This function handles FSMC global interrupt request.
  * @param  None
  * @retval None
  */
void FSMC_IRQHandler(void)
{
}

/**
  * @brief  This function handles SDIO global interrupt request.
  * @param  None
  * @retval None
  */
void SDIO_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM5 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM5_IRQHandler(void)
{
}

/**
  * @brief  This function handles SPI3 global interrupt request.
  * @param  None
  * @retval None
  */
void SPI3_IRQHandler(void)
{
}

/**
  * @brief  This function handles UART4 global interrupt request.
  * @param  None
  * @retval None
  */
void UART4_IRQHandler(void)
{
}

/**
  * @brief  This function handles UART5 global interrupt request.
  * @param  None
  * @retval None
  */
void UART5_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM6 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM6_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM7 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM7_IRQHandler(void)
{
}

/**
  * @brief  This function handles DMA2 Channel 1 interrupt request.
  * @param  None
  * @retval None
  */
void DMA2_Channel1_IRQHandler(void)
{
}

/**
  * @brief  This function handles DMA2 Channel2 interrupt request.
  * @param  None
  * @retval None
  */
void DMA2_Channel2_IRQHandler(void)
{
}

/**
  * @brief  This function handles DMA2 Channel3 interrupt request.
  * @param  None
  * @retval None
  */
void DMA2_Channel3_IRQHandler(void)
{
}

/**
  * @brief  This function handles DMA2 Channel 4 and DMA2 Channel 5
  * @param  None
  * @retval None
  */
void DMA2_Channel4_5_IRQHandler(void)
{
}
/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
