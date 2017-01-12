/*
 */
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_i2c.h"
#include "misc.h"
#include "globalvar.h"
#include "print.h"
#include "gpio_i2c.h"
//declare

void USART_Configuration(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);

void TIM3_Configuration(void);
void TIM4_Configuration(void);
void TIM5_Configuration(void);
void I2C_Configuration(void);

extern uint8_t d;

extern uint8_t cnt; //整体计数，0～72，用来控制数据信号
extern uint8_t icnt; //内部计数，0～1，用来控制时钟和锁存信号
extern int8_t outputLock;
extern uint32_t output1;//低16位
extern uint32_t output2;//高16位
void conv(uint32_t out,uint32_t color);

int main(void)
{
    int i = 0;
//    uint8_t string[] = "ChenWenjiang\n\r";
//    uint8_t write_succeed[] = "Write Succeed!\n\r";
//    uint8_t write_failed[] = "Write failed!\n\r";
//    uint8_t read_succeed[] = "Read Succeed!\n\r";
//    uint8_t read_failed[] = "Read failed!\n\r";
 //   int i = 0;
    uint8_t slaveaddr = 0xa0;
 //   uint32_t out = 0;
//    static uint8_t twinkFlag = 0;
    uint8_t data = 0x1;
  //  uint8_t data2 = 0x55;
  //  uint8_t dataToString[7]="0x01\n\r";
    inputInit(); 
    SystemInit();
    RCC_Configuration();
    GPIO_Configuration();
    USART_Configuration();
//  TIM3_Configuration();
    TIM4_Configuration();
//    TIM5_Configuration();
//    I2C_Configuration();
    NVIC_Configuration();
    
    gLight = 0x80000000;
    gColor = 0;
    gTwink = gLight;
//    cnt = 0;
//    icnt = 1;
//    outputLock = 1;
//    while(outputLock);
    GPIO_ResetBits(GPIOE,GPIO_Pin_3);
    while(i++<10000000){
   /*     if(i++==20){
            i = 0;
            while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
            USART_SendData(USART3,'\n');
            while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
            USART_SendData(USART3,'\r');
        }else{
            while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
            USART_SendData(USART3,d);
        }*/
//        if(outputLock==0){
//            twinkFlag++;
//            twinkFlag %= 2;
//            if(twinkFlag==0){
//               /* if(gLight==0)
//                    gLight = 0x80000000;
//                else
//                    gLight >>=1;*/
//                gLight = regs[5].val;
//                gTwink = 0;
//                out = gLight;
//            }else
//                out =gTwink ^ gLight; 
//            conv(out,gColor);
//            cnt = 0;
//            icnt = 1;
//            outputLock = 1;
//        }      
        uint8_t a = 0xff;
        uint8_t success[] = "success";
        uint8_t error[] = "error";
        uint8_t num[5] = "5";
        a = Single_Write(slaveaddr,0,data++);
        if(a==0)
            print(success,10);
        else if(a==1){
            num[0] = '1';
            print(num,10);
        }else if(a==2){
            num[0] = '2';
            print(num,10);
        }else if(a==3){
            num[0] = '3';
            print(num,10);
        }else
            print(error,10);
        num[0] = '\n';
        num[1] = '\r';
        num[2] = '\0';
        print(num,10);
    //       uint8_t tmp = ((data2>>4)&0x0f);
      //      dataToString[2] = tmp>9?(tmp+'a'):(tmp+'0');
      //      tmp = (data & 0x0f);
      //      dataToString[3] = tmp>9?(tmp+'a'-10):(tmp+'0');
      //      print(dataToString,10);

       
//        print(string,30);
    }
    return 0;
}

void I2C_Configuration(void){
    I2C_InitTypeDef I2C_InitStructure;
    
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 5000;
    I2C_Init(I2C1,&I2C_InitStructure);
}

void USART_Configuration(void)
{
    // added
    USART_Cmd(USART3,DISABLE);



    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART3,&USART_InitStructure);
    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART3,ENABLE);
}
void RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|
            RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|
            RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO,
            ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4|
            RCC_APB1Periph_USART3|/*RCC_APB1Periph_I2C1|*/RCC_APB1Periph_TIM5,
            ENABLE);
}

void GPIO_Configuration(void)
{
    //TODO
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    // 改变指定管脚的映射 GPIO_Remap_SWJ_Disable SWJ 完全禁用（JTAG+SW-DP）
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
    // 改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，JTAG-DP 禁用 + SW-DP 使能

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //| GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
    
// button input
    GPIO_InitStructure.GPIO_Pin = /*GPIO_Pin_14;*/(gMap[ACK].loc)|(gMap[RST].loc);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOG,&GPIO_InitStructure);

   
    GPIO_InitStructure.GPIO_Pin = (gMap[TEST].loc)|(gMap[ENT].loc)|(gMap[MEM].loc)
        |(gMap[MOV].loc)|(gMap[ADD].loc)|/* button  input */
        (gMap[28].loc)|(gMap[29].loc)|(gMap[30].loc);//alarm input
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    //alarm input
    GPIO_InitStructure.GPIO_Pin = (gMap[0].loc)|(gMap[1].loc)|(gMap[2].loc);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = (gMap[3].loc)|(gMap[15].loc)|(gMap[16].loc)|
        (gMap[17].loc)|(gMap[18].loc)|(gMap[26].loc)|(gMap[27].loc);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = (gMap[4].loc)|(gMap[5].loc)|(gMap[6].loc)|
        (gMap[7].loc)|(gMap[8].loc)|(gMap[9].loc)|(gMap[10].loc)|
        (gMap[11].loc)|(gMap[12].loc)|(gMap[13].loc)|(gMap[14].loc)|
        (gMap[31].loc);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOF,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = (gMap[19].loc)|(gMap[20].loc)|(gMap[21].loc)|
        (gMap[22].loc)|(gMap[23].loc)|(gMap[24].loc)|(gMap[25].loc);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
        
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
/*       //USART1 Tx(PA.09)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    //USART1 Rx(PA.10)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
*/    
/*    //scl
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    //sda
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB,&GPIO_InitStructure);  
*/
    I2C_GPIO_Config();
    
}
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority  = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
 
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority  = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority  = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
/*
    NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);*/
}
// 1ms
void TIM3_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
    //TODO 
    TIM_TimeBaseStructure.TIM_Period = 2;    // 2K/2 = 1000
    TIM_TimeBaseStructure.TIM_Prescaler = 36000-1;   // 72M/36000 = 2K
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);

    TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM3,ENABLE);
}
// 1s
void TIM4_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
    //TODO 
    TIM_TimeBaseStructure.TIM_Period = 1000;    // 2K/1000 = 2
    TIM_TimeBaseStructure.TIM_Prescaler = 36000-1;   // 72M/36000 = 2K
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);

    TIM_ITConfig(TIM4, TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM4,ENABLE);
}
// 1ms 
void TIM5_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
    //TODO 
    TIM_TimeBaseStructure.TIM_Period = 10;    // 20K/10 = 2000
    TIM_TimeBaseStructure.TIM_Prescaler = 3600-1;   // 72M/3600 = 20K
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);

    TIM_ITConfig(TIM5, TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM5,ENABLE);
}
