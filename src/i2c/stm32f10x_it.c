#include "stm32f10x.h"   
#include "stm32f10x_it.h"  
#include "stm32f10x_usart.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"  
#include "stm32f10x_tim.h"  
  
#define TxBufferSize1 128 
#define RxBufferSize1 128

uint8_t TxBuffer1[TxBufferSize1];
uint8_t RxBuffer1[RxBufferSize1];
uint8_t rec_f;
__IO uint8_t TxCounter1 = 0x00;
__IO uint8_t RxCounter1 = 0x00;

uint8_t NbrOfDataToTransfer1 = TxBufferSize1;
uint8_t NbrOfDataToRead1 = RxBufferSize1;


void TIM3_IRQHandler(void)  
{  
}


void USART1_IRQHandler(void)
{

    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {
        RxBuffer1[0] = USART_ReceiveData(USART1);
        USART_ITConfig(USART1,USART_IT_TXE,ENABLE);
    }
    if(USART_GetITStatus(USART1,USART_IT_TXE)!=RESET)
    {
        USART_SendData(USART1,'\n');
        USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
    }
}
#define EEPROMDEVADDR 5
int gI2cAddr = 0;
int gI2cRW = 0;
unsigned char gI2cData[256] ={0} ;//TODO
int gI2cAck = 0;
int gI2cNBytes = 1;
int gI2cDevAddr = 0;
volatile int gI2cErr = 0;
volatile int gI2cWriteFinished = 0;
volatile int gI2cReadFinished = 0;
#define SETSCL      GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define RESETSCL    GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define SETSDA      GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define RESETSDA    GPIO_ResetBits(GPIOA,GPIO_Pin_2)
void TIM2_IRQHandler(void)
{
    static int i2cCnt = 0;
    static int i2cByteCnt = 0;
    int i;

    if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
    {
/*        if((i2cCnt++)%2)
        {
            SETSCL;
            RESETSDA;
        }
        else
        {
            RESETSDA;
            SETSDA;
        }*/
        //addr
        if(i2cByteCnt==0)
        {
            //gI2cWriteFinished = 0;
            //gI2cReadFinished = 0;
            //gI2cErr = 0;
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
                //gI2cAck = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
                
                gI2cAck = 0;
                if(gI2cAck)
                {
                    i2cCnt = 29;
                    i2cByteCnt = gI2cNBytes - 1;
                    gI2cErr = -2; //write device address failed
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
                gI2cWriteFinished = 1;
                //TODO turn off timer
                TIM_Cmd(TIM2,DISABLE);
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
                gI2cAck = 0;
                //gI2cAck = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
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
                gI2cWriteFinished = 1;
                //TODO turn off timer
                TIM_Cmd(TIM2,DISABLE);
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
                gI2cReadFinished = 1;
                //TODO turn off timer
                TIM_Cmd(TIM2,DISABLE);
            }
        }
        i2cCnt++;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}
