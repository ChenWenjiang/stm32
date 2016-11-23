#include <iostream>

using namespace std;

#define EEPROMDEVADDR 5
int gI2cTransFlag = 0;
int gI2cAddr = 0;
int gI2cRW = 0;
unsigned char gI2cData[256] ={0xaa,0x55,0x12,0x34} ;//TODO
int gI2cAck = 0;
int gI2cNBytes = 4;
int gI2cDevAddr = 0;
int scl;
int sda;
/*
#define SETSCL      GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define RESETSCL    GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define SETSDA      GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define RESETSDA    GPIO_ResetBits(GPIOA,GPIO_Pin_2)
*/
#define SETSCL      (scl = 1)  
#define RESETSCL    (scl = 0)
#define SETSDA      (sda = 1)
#define RESETSDA    (sda = 0)

void TIM2_IRQHandler(void)
{
    static int i2cCnt = 0;
    static int i2cByteCnt = 0;

    int i;
//    if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
    {
//        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
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
                gI2cAck = 0;//GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
                if(gI2cAck)
                {
                    i2cCnt = 29;
                }
            }
            else if(i2cCnt==29)    //ack
            {
                RESETSCL;
                RESETSDA;
                i2cCnt = -1;
                i2cByteCnt++;
            }
            else if(i2cCnt==30)  //stop
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
                gI2cAck = 1;
                //gI2cAck = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
                if(gI2cAck)
                {
                    i2cCnt = 26;
                    i2cByteCnt = gI2cNBytes -1;
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
                SETSCL;
            else if(i2cCnt==29)
            {
                SETSDA;
                i2cByteCnt = 0;
                i2cCnt = -1;
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
                    //if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2))
                  //  if(sda)
                  //  gI2cData[i2cByteCnt] |= (1<<(7-i));
                  //  else
                  //      gI2cData[i2cByteCnt] &= ~(1<<(7-i));
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
            }
        }
        i2cCnt++;
        if(i2cCnt==0)
            cout << endl;
    }
}

int main(void)
{
    int i = 0;
    while(i++<200)
    {
        TIM2_IRQHandler();
        cout << scl << " " << sda << endl;
    }
    return 0;
}

