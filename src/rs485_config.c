#include "rs485_config.h"
#include "eeprom.h"

static void RS485_UART4_Config(void)
{
    USART_Cmd(UART4,DISABLE);

    USART_InitTypeDef USART_InitStructure;
//    switch(regs[1].val){
//        case 0:
//            USART_InitStructure.USART_BaudRate = 2400;
//            break;
//        case 1:
//            USART_InitStructure.USART_BaudRate = 4800;
//            break;
//        case 2:
            USART_InitStructure.USART_BaudRate = 9600;
//            break;
//        case 3:
//            USART_InitStructure.USART_BaudRate = 19200;
//            break;
//        case 4:
//            USART_InitStructure.USART_BaudRate = 38400;
//            break;
//        default:
//            USART_InitStructure.USART_BaudRate = 9600;
//            gRS485Config = 0x20 |(gRS485Config & 0x0f);
//            eeprom_store_rs485config();
//    }
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//    switch(regs[2].val){
//        case 0:
//            USART_InitStructure.USART_StopBits = USART_StopBits_1;
//            USART_InitStructure.USART_Parity = USART_Parity_Even;
//            break;
//        case 1:
//            USART_InitStructure.USART_StopBits = USART_StopBits_1;
//            USART_InitStructure.USART_Parity = USART_Parity_Odd;
//            break;
//        case 2:
            USART_InitStructure.USART_StopBits = USART_StopBits_1;
            USART_InitStructure.USART_Parity = USART_Parity_No;
//            break;
//        case 3:
//            USART_InitStructure.USART_StopBits = USART_StopBits_2;
//            USART_InitStructure.USART_Parity = USART_Parity_No;
//            break;
//        default:
//            USART_InitStructure.USART_StopBits = USART_StopBits_1;
//            USART_InitStructure.USART_Parity = USART_Parity_Even;
//            gRS485Config = gRS485Config & 0xf0;
//            eeprom_store_rs485config();
//    }
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
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4|RCC_APB1Periph_TIM2,ENABLE);
}
//用于判断RTU是否超时，3.5个串口字符时间没有接收到即超时
static void RS485_TIM2_Config(void){
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
            //25us 中断 
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    TIM_TimeBaseStructure.TIM_Period = 5;    // 200K/5 = 40k
    TIM_TimeBaseStructure.TIM_Prescaler = 360-1;   // 72M/360 = 200K
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
                                                
    TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
//    TIM_Cmd(TIM2,ENABLE);
    
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

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void RS485_Config(void){
    RS485_RCC_Config();
    RS485_GPIO_Config();
    RS485_UART4_Config();
    RS485_TIM2_Config();
    RS485_NVIC_Config();
}

int print(uint8_t * str,int len){
    int i = 0;
    RS485_TX_ENABLE;
    for(;i<len;i++){
//        if(str[i]=='\0')
//            break;
        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
        USART_SendData(UART4,str[i]);
    }
//    while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
//    USART_SendData(UART4,'\n');
//    while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
//    USART_SendData(UART4,'\r');
    while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET);
    RS485_RX_ENABLE;
    return (i+2);
}
