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


void USART1_IRQHandler(void)
{

    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {
        RxBuffer1[0] = USART_ReceiveData(USART1);
        USART_ITConfig(USART1,USART_IT_TXE,ENABLE);
    }
    if(USART_GetITStatus(USART1,USART_IT_TXE)!=RESET)
    {
        USART_SendData(USART1,'\n');
        USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
    }
}
#define EEPROMDEVADDR 5
int gI2cAddr = 0;
int gI2cRW = 0;
unsigned char gI2cData[256] ={0} ;//TODO
int gI2cAck = 0;
int gI2cNBytes = 1;
int gI2cDevAddr = 0;
volatile int gI2cErr = 0;
volatile int gI2cOp = 0;
#define SETSCL      GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define RESETSCL    GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define SETSDA      GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define RESETSDA    GPIO_ResetBits(GPIOA,GPIO_Pin_2)
void TIM2_IRQHandler(void)
{
    static int Cnt = 0;

    if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
    {
        if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==Bit_RESET)
            Cnt++;
        else
            Cnt = 0;
        if(Cnt>50)
            GPIO_SetBits(GPIOA,GPIO_Pin_1);
        else
            GPIO_ResetBits(GPIOA,GPIO_Pin_1);
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}
