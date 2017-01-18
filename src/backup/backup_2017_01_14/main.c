/*
 */
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "gpio_i2c.h"
#include "stm32f10x_usart.h"
//#include "reg.h"
//declare
void parse(void);
extern uint8_t uart4_data[10];
//extern modreg_t * regHashTable;
//extern STATE gState;
//extern int gRxCnt;

void USART_Configuration(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void TIM3_Configuration(void);
void TIM2_Configuration(void);
void NVIC_Configuration(void);
void EXTI_Configuration(void);
void UART4_GPIO_Config(void);

void Delay1ms(void){
    volatile int i = 0;
    while(i++<10000);
}
//
//void rs485_print(uint8_t * data){
//    while(*data!='\0'){
//        Delay1ms();  
//        USART_SendData(UART4, *data++);  
//        /* Loop until the end of transmission */  
//        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);  
//        Delay1ms();  
//}
//
int main()
{
    SystemInit();
    RCC_Configuration();
    GPIO_Configuration();
 //   TIM3_Configuration();
 //   TIM2_Configuration();
 //   EXTI_Configuration();
    USART_Configuration();
 //   NVIC_Configuration();
//    inputInit();
//    ledInit();
//    regInit();
    GPIO_ResetBits(GPIOA,GPIO_Pin_10);
    while(1)
    {
        int i = 0;
        if(!GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_10)){
            while(i<10){
                while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET); 
                USART_SendData(UART4,uart4_data[i]);
                i++;
                Delay1ms();
            }
            while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
            USART_SendData(UART4,'\n');
            Delay1ms();
            while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
            USART_SendData(UART4,'\r');
            while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
            Delay1ms();
        //    GPIO_SetBits(GPIOA,GPIO_Pin_10);
        }
//        volatile int i = 0;    
//        
//        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
//        USART_SendData(UART4,'\n');
//        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
//        
//        
//        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
//        uint8_t a = 0,b = '9';
//        a = Single_Write(0xa0,0,'1');
//        while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
//        USART_SendData(USART3,'a'+a);
//        a = Single_Write(0xa0,1,'2');
//        while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
//        USART_SendData(USART3,'a'+a);
//        if(a==0){
//            a = Single_Read(0xa0,0,&b);
//            while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
//            USART_SendData(USART3,'a'+a);
//
//            while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
//            USART_SendData(USART3,b);
//        }
        //        setState();
        //        setLed();
        //        parse();
    }
    return 0;
}

void USART_Configuration(void)
{
    // added
    USART_Cmd(USART3,DISABLE);
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
    USART_Init(USART3,&USART_InitStructure);
    USART_Cmd(USART3,ENABLE);
    USART_Init(UART4,&USART_InitStructure);
    USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
    USART_ClearFlag(UART4,USART_FLAG_TC);
    USART_Cmd(UART4,ENABLE);

}

void EXTI_Configuration(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

void RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //i2c clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3|RCC_APB1Periph_UART4,ENABLE);
//TODO
    
}
void UART4_GPIO_Config(void){

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

void GPIO_Configuration(void)
{
    //TODO
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOC,&GPIO_InitStructure);

    //USART3 Tx(Pb.10)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    //USART3 Rx(Pb.11)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    //USART1 Tx(PA.09)
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_Init(GPIOA,&GPIO_InitStructure);
//    //USART1 Rx(PA.10)
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    I2C_GPIO_Config();
    UART4_GPIO_Config();
}

// 5us  优先级最高
void TIM4_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
    //TODO 
    TIM_TimeBaseStructure.TIM_Period = 1;    // 2K/2K = 1
    TIM_TimeBaseStructure.TIM_Prescaler = 360-1;   // 72M/36000 = 2K
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);

    TIM_ITConfig(TIM4, TIM_IT_Update,ENABLE);
//    TIM_Cmd(TIM4,ENABLE);
}
// 1s
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    //TODO 
    TIM_TimeBaseStructure.TIM_Period = 2000;    // 2K/2K = 1
    TIM_TimeBaseStructure.TIM_Prescaler = 35999;   // 72M/36000 = 2K
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2,ENABLE);
}
// 1ms
void TIM3_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

    TIM_TimeBaseStructure.TIM_Period = 2000;
    TIM_TimeBaseStructure.TIM_Prescaler = 35999;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);

    TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM3,ENABLE);
}


void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority  = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
/*
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
*/
    //TODO priority 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


