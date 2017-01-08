#include "stm32f10x.h"   
#include "stm32f10x_it.h"  
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"  
#include "stm32f10x_tim.h" 
#include "stm32f10x_usart.h"

unsigned char buf[128];
int ptr=0;
void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
        buf[ptr++]=USART_ReceiveData(USART1);
    }
    if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(USART2,USART_FLAG_ORE);
        USART_ReceiveData(USART1);
    }
}
//1s定时，芯片正在运行的指示灯，闪烁表示正在运行，不闪烁表示有问题，程序没有运行
uint8_t gLedFlag;
uint32_t gOutput1;
uint32_t gOutput2;
uint8_t gPwr;
void TIM4_IRQHandler(void){
    if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET){
        TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
        if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)){
            GPIO_ResetBits(GPIOD,GPIO_Pin_2);
        }else{
            GPIO_SetBits(GPIOD,GPIO_Pin_2);
        }
        if(gLedFlag==0){
            //gOutput2 = 0xaaaaaaaa;
            //gOutput1 = 0xaaaaaaaa;
            //gPwr = 0xaa;
            gOutput2 = 0x55555555;
            gOutput1 = 0x55555555;
            gPwr = 0x55;
            gLedFlag = 1;
        }
    }
}
//1ms定时，将LED状态输:出。

#define SETSHIFTCLK      GPIO_SetBits(GPIOE,GPIO_Pin_0)
#define RESETSHIFTCLK    GPIO_ResetBits(GPIOE,GPIO_Pin_0)
#define SETSHIFTDAT      GPIO_SetBits(GPIOE,GPIO_Pin_2)
#define RESETSHIFTDAT    GPIO_ResetBits(GPIOE,GPIO_Pin_2)
#define SETLATCH         GPIO_SetBits(GPIOE,GPIO_Pin_1)
#define RESETLATCH       GPIO_ResetBits(GPIOE,GPIO_Pin_1)

static uint8_t cnt = 0; //整体计数，0～72，用来控制数据信号
static uint8_t icnt = 0; //内部计数，0～1，用来控制时钟和锁存信号
void TIM5_IRQHandler(void){
    if(TIM_GetITStatus(TIM5,TIM_IT_Update)!=RESET){
        TIM_ClearITPendingBit(TIM5,TIM_IT_Update);//清中断
        if(gLedFlag){
            if(icnt){   //时钟下降沿,锁存上升沿,数据移位
                if(cnt==71){
                    SETLATCH;
                }else{
                    RESETLATCH;
                    if(cnt<32){
                        if(gOutput1&(1<<cnt))
                            SETSHIFTDAT;
                        else
                            RESETSHIFTDAT;
                    }else if(cnt<64){
                        if(gOutput2&(1<<(cnt-32)))
                            SETSHIFTDAT;
                        else
                            RESETSHIFTDAT;
                    }else{
                        if(gPwr&(1<<(cnt-64)))
                            SETSHIFTDAT;
                        else
                            RESETSHIFTDAT;
                    }   
                }
                RESETSHIFTCLK;
                if(cnt==72){
                    cnt=0;
                    gLedFlag = 0;
                }else
                    cnt++;
                icnt = 0;
            }else{        //时钟上升沿,锁存下降沿
                if(cnt==72){
                    RESETSHIFTCLK;
                }else{
                    SETSHIFTCLK;
                }
                RESETLATCH;
                icnt=1;
            }
        }
    }
}
/*
void TIM5_IRQHandler(void)  
{  
    uint8_t i = 0;
    uint16_t iData = 0;
    TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
    //led 
    shiftCnt = (shiftCnt+1)%68; //34 leds
    //clock
    if((shiftCnt%2)==1)  //odd
        SETSHIFTCLK;
    else  //even
    {
        //clock
        RESETSHIFTCLK;
        //ds
        if(shiftCnt<=62)
        {
            if(output & (1<<(shiftCnt/2)))
                //GPIO_SetBits(,);  //high
                SETSHIFTDAT;
            else
                RESETSHIFTDAT;
                //GPIO_ResetBits(,);  //low
        }
        else if(shiftCnt==64)
        {
            if(gPwr & 0x01)
                SETSHIFTDAT;
                //GPIO_SetBits(,);
            else
                RESETSHIFTDAT;
                //GPIO_ResetBits(,);

        }
        else if(shiftCnt==66)
        {
            if(gPwr & 0x02)
                SETSHIFTDAT;
            //    GPIO_SetBits(,);
            else
                RESETSHIFTDAT;
               // GPIO_ResetBits(,);
        }
    }
    //lock the value to set led
    if(shiftCnt==0)
        GPIO_SetBits(GPIOE,GPIO_Pin_1);//high
    if(shiftCnt==1)
        GPIO_ResetBits(GPIOE,GPIO_Pin_1);//low

    // rx count,if rxbuf's size don't change,then receive a frame
    if(rxBuff.size!=0 && rxsize == rxBuff.size)
        gRxCnt++;
    else
        gRxCnt = 0;
    rxsize = rxBuff.size;
}    

*/
/*
#define SETSCL      GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define RESETSCL    GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define SETSDA      GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define RESETSDA    GPIO_ResetBits(GPIOA,GPIO_Pin_2)
void TIM4_IRQHandler(void)
{*/
/*
    if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
    {
        TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
        USART_SendData(USART1,'c');
        while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2))
            GPIO_ResetBits(GPIOA,GPIO_Pin_2);
        else
            GPIO_SetBits(GPIOA,GPIO_Pin_2);
        if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1))
            GPIO_SetBits(GPIOA,GPIO_Pin_1);
        else
            GPIO_ResetBits(GPIOA,GPIO_Pin_1);
    }*/
/*    static int i2cCnt = 0;
    static int i2cByteCnt = 0;

    int i;
    if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
    {
        TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
        //addr
        if(i2cByteCnt==0)
        {
            if(i2cCnt==0)
            {
                SETSCL;
                SETSDA;
            }
            else if(i2cCnt==1)    //start 
            {
                RESETSDA;
            }
            else if(i2cCnt==2)
            {
                RESETSCL;
            } 
            else if(i2cCnt < 27) //data
            {
                if(i2cCnt%3==0)
                {
                    i = i2cCnt/3;
                    RESETSCL;
                    if(gI2cData[i2cByteCnt] & (1<< (8-i)))  //data
                        SETSDA;
                    else
                        RESETSDA;
                }
                else if(i2cCnt%3==1)
                {
                    SETSCL;
                }
                else //(i2cCnt%3==2)
                {
                    RESETSCL;
                }
            }
            else if(i2cCnt==27)
            {
                SETSDA;
                SETSCL;
            }
            else if(i2cCnt==28)
            {
                gI2cAck = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
                if(gI2cAck)
                {
                    i2cCnt = 29;
                    i2cByteCnt = gI2cNBytes - 1;
                    gI2cErr = -2;
                }
            }
            else if(i2cCnt==29)    //ack
            {
                RESETSCL;
                RESETSDA;
                i2cCnt = -1;
                i2cByteCnt++;
            }
            else if(i2cByteCnt==30)
            {
                RESETSCL;
                RESETSDA;
            }
            else if(i2cCnt==31)
            {
                SETSCL;
            }
            else if(i2cCnt==32)
            {
                SETSDA;
                i2cCnt = -1;
                i2cByteCnt = 0;
                //TODO turn off timer
            }
        }
        // 以上是设备地址写入
        else if(gI2cRW==0)
        {
            if(i2cCnt<24) //data
            {
                if(i2cCnt%3==0)
                {
                    i = i2cCnt/3;
                    RESETSCL;
                    if(gI2cData[i2cByteCnt] & (1<< (7-i)))  //data
                        SETSDA;
                    else
                        RESETSDA;
                }
                else if(i2cCnt%3==1)
                {
                    SETSCL;
                }
                else //(i2cCnt%3==2)
                {
                    RESETSCL;
                }
            }
            else if(i2cCnt==24)
            {
                SETSDA;
                SETSCL;
            }
            else if(i2cCnt==25)
            {
                gI2cAck = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
                if(gI2cAck)
                {
                    i2cCnt=26;
                    i2cByteCnt = gI2cNBytes - 1;
                    gI2cErr = -3;
                }
            }
            else if(i2cCnt==26)    //ack
            {
                RESETSCL;
                RESETSDA;
            }
            else if(i2cCnt==27)
            {
                if(i2cByteCnt+1==gI2cNBytes)
                {
                    RESETSCL;
                    RESETSDA;
                }
                else
                {
                    i2cByteCnt++;
                    i2cCnt = -1;
                }
            }
            else if(i2cCnt==28)
            {
                SETSCL;
            }
            else if(i2cCnt==29)
            {
                SETSDA;
                i2cByteCnt = 0;
                i2cCnt = -1;
                //TODO turn off timer
            }
        }
        else 
        {            
            if(i2cCnt<24) //data
            {
                if(i2cCnt%3==0)
                {
                    SETSCL;
                    //GPIO_SetBits(,);//TODO clk
                }
                else if(i2cCnt%3==1)
                {
                    i = i2cCnt/3;
                    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2))
                        gI2cData[i2cByteCnt] |= (1<<(7-i));
                    else
                        gI2cData[i2cByteCnt] &= ~(1<<(7-i));
                }
                else
                {
                    RESETSCL;
                }
            }
            else if(i2cCnt==24)
            {
                if(i2cByteCnt+1==gI2cNBytes)
                    SETSDA;
                else
                    RESETSDA;               //ack
            }
            else if(i2cCnt==25)
            {
                SETSCL;
            }
            else if(i2cCnt==26)
            {
                RESETSCL;
            }
            else if(i2cCnt==27)
            {
                RESETSDA;
            }
            else if(i2cCnt==28)
            {
                if(i2cByteCnt+1==gI2cNBytes)
                    SETSCL;
                else
                {
                    i2cByteCnt++;
                    i2cCnt = -1;
                }
            }
            else if(i2cCnt==29)
            {
                SETSDA;
                i2cByteCnt = 0;
                i2cCnt = -1;
                //TODO turn off timer
            }
        }
        i2cCnt++;
    }
}*/
