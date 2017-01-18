#include "other_hw_config.h"

static void USART3_GPIO_Config(void){
}
static void USART3_RCC_Config(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
}
static void USART3_Config(void){
    USART_Cmd(USART3,DISABLE);
         
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl=
        USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART3,&USART_InitStructure);
    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART3,ENABLE);
}
static void USART3_NVIC_Config(void){
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
              
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void Other_HW_Config(void){
    USART3_RCC_Config();
    USART3_GPIO_Config();
    USART3_Config();
    USART3_NVIC_Config();
}
