#include "stm32f10x.h"   
#include "stm32f10x_it.h"  
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"  
#include "stm32f10x_tim.h" 
#include "led.h"
#include "reg.h"
#include "globalvar.h"

//extern INPUT  gInput[INPUTNUM];
extern STATE gState;
extern modreg_t regs[74];
//extern uint16_t gInputState[32];
//extern uint32_t gInput;
extern uint32_t gTwink;
extern uint8_t gPwr;
static uint32_t inCnt[INPUTNUM]={0};

static int shiftCnt = 0;
static int twinkCnt = 0;
static uint32_t output;

// rx cnt
extern int gRxCnt = 0;
static int rxsize = 0;

// i2c varables
static int i2cCnt = 0;
extern int gI2cRW;
extern int gI2cData;
extern int gI2cAck;

// 1s interrupt
void TIM2_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    twinkCnt = (twinkCnt+1)%2;
    if(twinkCnt)
        output = regs[38].val;
    else
    {
        gTwink &= regs[38].val;
        output = ~(regs[38].val ^(~(gTwink)));
    }
}
#define SETSHIFTCLK      GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define RESETSHIFTCLK    GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define SETSHIFTDAT      GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define RESETSHIFTDAT    GPIO_ResetBits(GPIOA,GPIO_PIn_2)
//1ms interrupt
void TIM3_IRQHandler(void)  
{  
    
    uint8_t i = 0;
    uint16_t iData = 0;
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    //input alarm check
    for(i=0;i<SIGLEDNUM;i++)
    {
        if(GPIO_ReadInputDataBit(gInput[i].addr,
                    gInput[i].loc) ==Bit_RESET)
            inCnt[i]++;
        else
            inCnt[i]=0;

        if(inCnt[i]>=CNTTIMES)
        {
            regs[i+6].val = 1;
            regs[5].val |= (1<<i);
        }
        else
        {
            regs[i+6].val = 0;
            regs[5].val &= (~(1<<i));
        }
    }
    if(regs[5].val!=0)
        regs[3].val = 1;
    else
        regs[3].val = 0;

    for(i=ALARMNUM;i<INPUTNUM;i++)
    {
        if(GPIO_ReadInputDataBit(gInput[i].addr,gInput[i].loc)==Bit_RESET)
            inCnt[i]++;
        else
            inCnt[i] = 0;
        if(inCnt[i]>=CNTTIMERS)
            gButtonInputFlag |= (1<<i);
        else
            gButtonInputFlag &= (~(1<<i));
    }   
}

//TODO
void TIM5_IRQHandler(void)  
{  
    uint8_t i = 0;
    uint16_t iData = 0;
    TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
    //led 
    shiftCnt = (shiftCnt+1)%68; //34 leds
    //clock
    if((shiftCnt%2)==1)  //even
        SETSHIFTCLK;
        //GPIO_SetBits(/*TODO*/,/*TODO*/);//high 
    else  //odd
    {
        //clock
        RESETSHIFTCLK;
        //GPIO_ResetBits(,);   //low
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
        GPIO_SetBits(,);//high
    if(shiftCnt==1)
        GPIO_ResetBits(,);//low
/*
    // rx count,if rxbuf's size don't change,then receive a frame
    if(rxBuff.size!=0 && rxsize == rxBuff.size)
        gRxCnt++;
    else
        gRxCnt = 0;
    rxsize = rxBuff.size;*/
}    

void USART1_IRQHandler(void)
{
    uint8_t tmp = 0;
    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {
        PUTINTOBUF(rxBuf,USART_ReceiveData(USART1));
        if(txBuf.tail!=txBuf.head)
        {
            USART_ITConfig(USART1,USART_IT_TXE,ENABLE);
        }
    }
    if(USART_GetITStatus(USART1,USART_IT_TXE)!=RESET)
    {
        if(txBuf.tail!=txBuf.head)
        {
            USART_SendData(USART1,GETFROMBUF(txBuf));
        }
        else
        {
            CLEARBUF(txBuf);
            USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
        }
    }
}

#define SETSCL      GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define RESETSCL    GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define SETSDA      GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define RESETSDA    GPIO_ResetBits(GPIOA,GPIO_Pin_2)
void TIM6_IRQHandler(void)
{
    static int i2cCnt = 0;
    static int i2cByteCnt = 0;

    int i;
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
    {
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
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
}
