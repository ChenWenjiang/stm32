#include "led_output_config.h"

static void LED_Output_RCC_Config(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
}

static void LED_Output_GPIO_Config(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
                            
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_Init(GPIOE,&GPIO_InitStructure);
}

static void LED_Output_TIM5_Config(void){
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
          
    TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
    TIM_TimeBaseStructure.TIM_Period = 2;    // 2K/2 = 1000
    TIM_TimeBaseStructure.TIM_Prescaler = 36000-1;   // 72M/36000 = 2K
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
                                             
    TIM_ITConfig(TIM5, TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM5,ENABLE);               
}

static void LED_Output_NVIC_Config(void){
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
              
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority  = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

void LED_Output_Config(void){
    LED_Output_RCC_Config();
    LED_Output_GPIO_Config();
    LED_Output_TIM5_Config();
    LED_Output_NVIC_Config();
}

