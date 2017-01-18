#include "alarm_input_config.h"
#include "globalvar.h"

static void Alarm_Input_RCC_Config(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|
            RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|
            RCC_APB2Periph_GPIOG,ENABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
}

static void Alarm_Input_GPIO_Config(void){
     //alarm input
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = (gMap[0].loc)|(gMap[1].loc)|(gMap[2].loc);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
                          
    GPIO_InitStructure.GPIO_Pin = (gMap[3].loc)|(gMap[15].loc)|(gMap[16].loc)|
        (gMap[17].loc)|(gMap[18].loc)|(gMap[26].loc)|(gMap[27].loc)|
        (gMap[ACK_IN].loc)|(gMap[RST_IN].loc);
    GPIO_Init(GPIOC,&GPIO_InitStructure);
                                                        
    GPIO_InitStructure.GPIO_Pin = (gMap[4].loc)|(gMap[5].loc)|(gMap[6].loc)|
        (gMap[7].loc)|(gMap[8].loc)|(gMap[9].loc)|(gMap[10].loc)|
        (gMap[11].loc)|(gMap[12].loc)|(gMap[13].loc)|(gMap[14].loc)|
        (gMap[31].loc);
    GPIO_Init(GPIOF,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = (gMap[19].loc)|(gMap[20].loc)|(gMap[21].loc)|
        (gMap[22].loc)|(gMap[23].loc)|(gMap[24].loc)|(gMap[25].loc)|
        (gMap[TEST_IN].loc)|(gMap[MEM_IN].loc);
    GPIO_Init(GPIOA,&GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin = (gMap[ACK].loc)|(gMap[RST].loc);
    GPIO_Init(GPIOG,&GPIO_InitStructure);
                          
    GPIO_InitStructure.GPIO_Pin = (gMap[TEST].loc)|(gMap[ENT].loc)
        |(gMap[MEM].loc)|(gMap[MOV].loc)|(gMap[ADD].loc)|/* button  input */
        (gMap[28].loc)|(gMap[29].loc)|(gMap[30].loc);//alarm input
    GPIO_Init(GPIOB,&GPIO_InitStructure);
}
static void TIM3_Config(void){
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
         
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
    TIM_TimeBaseStructure.TIM_Period = 20;    // 20K/20 = 1000
    TIM_TimeBaseStructure.TIM_Prescaler = 3600-1;   // 72M/3600 = 20K
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
                                            
    TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM3,ENABLE);
}
static void TIM3_NVIC_Config(void){
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority  = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void Alarm_Input_Config(void){
    Alarm_Input_RCC_Config();
    Alarm_Input_GPIO_Config();
    TIM3_Config();
    TIM3_NVIC_Config();
}

