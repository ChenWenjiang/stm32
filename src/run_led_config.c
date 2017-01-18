#include "run_led_config.h"

static void Run_LED_GPIO_Config(void){
    GPIO_InitTypeDef GPIO_InitStructure;
     
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    
    GPIO_Init(GPIOD,&GPIO_InitStructure);
              
}
static void Run_LED_RCC_Config(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
}

static void Run_LED_TIM_Config(void){
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
          
    TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
    TIM_TimeBaseStructure.TIM_Period = 1000;    // 2K/1000 = 2
    TIM_TimeBaseStructure.TIM_Prescaler = 36000-1;   // 72M/36000 = 2K
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
                                             
    TIM_ITConfig(TIM4, TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM4,ENABLE);                                                   
}

static void Run_LED_NVIC_Config(void){
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
               
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void Run_LED_Config(void){
    Run_LED_RCC_Config();
    Run_LED_GPIO_Config();
    Run_LED_TIM_Config();
    Run_LED_NVIC_Config();
}
