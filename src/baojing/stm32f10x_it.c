/**
  ******************************************************************************
  * @file    stm32_it.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "stm32_it.h"
#include "usb_lib.h"
#include "usb_istr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/******************************************************************************/
/*            Cortex-M Processor Exceptions Handlers                         */
/******************************************************************************/

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : MemManage_Handler
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFault_Handler
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFault_Handler
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : SVC_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVC_Handler(void)
{
}

/*******************************************************************************
* Function Name  : DebugMon_Handler
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMon_Handler(void)
{
}

/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
}

/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{
}

/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB Low Priority interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
#if defined(STM32L1XX_MD) || defined(STM32L1XX_HD)|| defined(STM32L1XX_MD_PLUS)|| defined (STM32F37X)
void USB_LP_IRQHandler(void)
#else
void USB_LP_CAN1_RX0_IRQHandler(void)
#endif
{
  USB_Istr();
}

/*******************************************************************************
* Function Name  : EVAL_COM1_IRQHandler
* Description    : This function handles EVAL_COM1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EVAL_COM1_IRQHandler(void)
{
  if (USART_GetITStatus(EVAL_COM1, USART_IT_RXNE) != RESET)
  {
    /* Send the received data to the PC Host*/
    USART_To_USB_Send_Data();
  }

  /* If overrun condition occurs, clear the ORE flag and recover communication */
  if (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_ORE) != RESET)
  {
    (void)USART_ReceiveData(EVAL_COM1);
  }
}

/*******************************************************************************
* Function Name  : USB_FS_WKUP_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

#if defined(STM32L1XX_MD) || defined(STM32L1XX_HD)|| defined(STM32L1XX_MD_PLUS)
void USB_FS_WKUP_IRQHandler(void)
#else
void USBWakeUp_IRQHandler(void)
#endif
{
  EXTI_ClearITPendingBit(EXTI_Line18);
}

/******************************************************************************/
/*                 STM32 Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32xxx.s).                                            */
/******************************************************************************/

/*******************************************************************************
* Function Name  : PPP_IRQHandler
* Description    : This function handles PPP interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*void PPP_IRQHandler(void)
{
}*/
extern STATE gState;
void EXTI0_IRQHandler(void)  
{
}


void EXTI1_IRQHandler(void) //ACK
{
}


void EXTI2_IRQHandler(void) //test
{
}


void EXTI3_IRQHandler(void)
{
    uint8_t i=0;
    if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
    {
        //TODO:which port used for keys.
        if(GPIO_ReadInputDataBit(GPIO/**/,GPIO_Pin_/**/)==Bit_SET)
        {
            if(gState==ALARM)
            {
                for(;i<32;i++)
                {
                    gLed[i].ledstate = STABLE;
                }
                gState = ACK;
            }
        }
        else if(gState!=ALARM)
        {
            if()//TODO: confirm test
            {   for(;i<32;++i)
                {
                    gLed[i].ledstate = TWINK;
                }
                gState = TEST;
            }
            else if(gState==TEST)
            {
                
            }
        }
        //TODO
        // confirm
        if(gState!=ALARM)
        {  
            if(gState==TEST)
            {
                for(;i<32;i++)
                {
                    gLed[i].ledstate = STABLE;
                }
            }
            gState = NORMAL;
        }
        //TODO
        //clear int
        uint8_t i=0;
        delay();
        //TODO
        // confirm
        if(gState!=ALARM)
        {
            if(gState==TEST)
            {
                for(;i<32;i++)
                {
                    gLed[i].ledstate = STABLE;
                }
            }
            gState = MEM;
    
            //TODO:read from eeprom and 
            //mem
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line3);
}

extern uint8_t setLoc;
void EXTI4_IRQHandler(void) //set
{
    uint8_t i = 0;
    delay();
    //TODO
    // confirm
    if(gState!=ALARM)
    {
        if(gState!=SET)
        {
            if()//TODO:ent && mov
            {
                gState = SET;
                setLoc = 0;
                gLed[setLoc].ledstate = TWINK;
            }
        }
        else
        {
            if()//TODO:ent
            {
                gState = NORMAL;
                gLed[setLoc].ledstate = STABLE;
            }
            else if() //TODO:mov
            {
                if(setLoc==31)
                    setLoc = 0;
                setLoc++;
                gLed[setLoc].ledstate = TWINK;
            }
            else if() //TODO:+
            {
                if(gLed[setLoc].color==RED)
                    gLed[setLoc].color = YELLOW;
                else
                    gLed[setLoc].color = RED;
            }
        }
    }

    //TODO
    //clear int
}



void EXTI9_5_IRQHandler(void)
{
}
//high priority,alarm signal
void EXTI15_10_IRQHandler(void)
{
    delay();
    gState = ALARM;
    //TODO:find the source 
    //set ledstate to TWINK
    //TODO
    //clear interrupt flag
}
void EXTI15_10_IRQHandler(void)
{
    delay();
    gState = ALARM;
    //TODO:find the source 
    //set ledstate to TWINK
    //TODO
    //clear interrupt flag
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

