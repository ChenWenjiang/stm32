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
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    //sda
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    //led
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    //key
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC,&GPIO_InitStructure);
}

void RCC_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB
                     |RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC
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

    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_Prescaler = 3600-1; //20k
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 20;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2,ENABLE);
}
void TIM4_Config(void)
{

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_Prescaler = 3600-1; //2k
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 200;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM4,TIM_FLAG_Update);
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
}
/*
extern int gI2cNBytes;
extern int gI2cTransFlag;
extern int gI2cAddr;
extern int gI2cRW;
extern unsigned char gI2cData[256];
extern int gI2cAck;
extern int gI2cOp;
extern int gI2cErr;
int eeprom_read(unsigned char page,unsigned char addr, int length)
{
    gI2cData[0] = page | 1;
    gI2cData[1] = addr;
    gI2cNBytes = 2;
    gI2cRW = 0;
    gI2cOp = 1;
    gI2cErr = 0;
    TIM_Cmd(TIM2,ENABLE);
    
    while(gI2cOp);
    if(gI2cErr!=0)
        return gI2cErr;
    gI2cData[0] = page & 0xfe;
    gI2cRW = 1;
    gI2cNBytes = length + 1;
    gI2cOp = 1;
    gI2cErr = 0;
    TIM_Cmd(TIM2,ENABLE);
    while(gI2cOp);
    if(gI2cErr!=0)
        return gI2cErr;
    return 0;
}
int eeprom_write(unsigned char page,unsigned char addr,int length)
{
    gI2cData[0] = page; 
    gI2cData[1] = addr;
    gI2cRW = 0;
    gI2cNBytes = length + 2;
    gI2cOp = 1;
    gI2cErr = 0;
    TIM_Cmd(TIM2,ENABLE);
    while(!gI2cOp);
    if(gI2cErr!=0)
        return gI2cErr;
    return 0;
}*/
int main(void)
{
    SystemInit();
    RCC_Config();
    GPIO_Config();
    TIM2_Config();
    NVIC_Config();
    while(1);
    return 0;
}

