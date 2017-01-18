#include "rs485_config.h"

static void RS485_UART4_Config(void)
{
    USART_Cmd(UART4,DISABLE);

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;

    USART_InitStructure.USART_HardwareFlowControl = 
        USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | 
        USART_Mode_Rx;
    USART_Init(UART4,&USART_InitStructure);
    USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
    USART_ClearFlag(UART4,USART_FLAG_TC);
    USART_Cmd(UART4,ENABLE);

}
static void RS485_RCC_Config(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|
            RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
}

static void RS485_GPIO_Config(void){

    GPIO_InitTypeDef GPIO_InitStructure;
//tx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC,&GPIO_InitStructure);
//rx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC,&GPIO_InitStructure);
//control    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}

static void RS485_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void RS485_Config(void){
    RS485_RCC_Config();
    RS485_GPIO_Config();
    RS485_UART4_Config();
    RS485_NVIC_Config();
}

int print(uint8_t * str,int len){
    int i = 0;
    for(;i<len;i++){
        if(str[i]=='\0')
            break;
        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
        USART_SendData(UART4,str[i]);
    }
    while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    USART_SendData(UART4,'\n');
    while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    USART_SendData(UART4,'\r');
    while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET);
    return (i+2);
}
