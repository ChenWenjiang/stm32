#include "stm32f10x.h"   
#include "stm32f10x_it.h"  
#include "stm32f10x_usart.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"  
#include "stm32f10x_tim.h"  
  
#define TxBufferSize1 128 
#define RxBufferSize1 128

uint8_t TxBuffer1[TxBufferSize1];
uint8_t RxBuffer1[RxBufferSize1];
uint8_t rec_f;
__IO uint8_t TxCounter1 = 0x00;
__IO uint8_t RxCounter1 = 0x00;

uint8_t NbrOfDataToTransfer1 = TxBufferSize1;
uint8_t NbrOfDataToRead1 = RxBufferSize1;


void TIM3_IRQHandler(void)  
{  
}

void EXTI3_IRQHandler(void)
{
}

void USART1_IRQHandler(void)
{
    uint32_t i;

    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {
        RxBuffer1[0] = USART_ReceiveData(USART1);
        if(RxCounter1==NbrOfDataToRead1)
        {
/*            for(i=0;i<RxCounter1;i++)
                TxBuffer1[i] = RxBuffer1[i];
            rec_f = 1;
            RxCounter1 = 0;
            TxCounter1 = 0;*/
            USART_ITConfig(USART1,USART_IT_TXE,ENABLE);
        }
    }
    if(USART_GetITStatus(USART1,USART_IT_TXE)!=RESET)
    {
        USART_SendData(USART1,TxBuffer1[0]);
/*        if(TxCounter1 == NbrOfDataToTransfer1)*/
            USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
    }
}
