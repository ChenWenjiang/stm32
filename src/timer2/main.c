#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "misc.h"

void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //scl
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    //sda
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    //led
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void RCC_Config(void)
{
  //  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 |    //
  //  RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB
                     |RCC_APB2Periph_GPIOA
          |RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
}

/*
void USART1_Config(void)
{
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1,&USART_InitStructure);
    USART_ITConfig(USART1,USART_IT_TXE,ENABLE);
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART1,ENABLE);
}
*/
void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
void TIM2_Config(void)
{

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);

//    TIM_DeInit(TIM4);
//    TIM_InternalClockConfig(TIM4);
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_Prescaler = 36000-1; //2k
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 2000;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
//    TIM_ClearFlag(TIM2,TIM_FLAG_Update);
//    TIM_ARRPreloadConfig(TIM4,ENABLE);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2,ENABLE);
}
void TIM4_Config(void)
{

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
//    TIM_ClearITPendingBit(TIM4,TIM_IT_Update);

//    TIM_DeInit(TIM4);
//    TIM_InternalClockConfig(TIM4);
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_Prescaler = 36000-1; //2k
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 2000;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM4,TIM_FLAG_Update);
//    TIM_ARRPreloadConfig(TIM4,ENABLE);
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
}
int main(void)
{
    SystemInit();
    RCC_Config();
    GPIO_Config();
    TIM2_Config();
    NVIC_Config();
//    USART1_Config();
    while(1);
    return 0;
}

