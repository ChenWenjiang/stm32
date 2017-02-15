#include "stm32f10x.h"   
#include "stm32f10x_it.h"  
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"  
#include "stm32f10x_tim.h" 
#include "stm32f10x_usart.h"
#include "stm32f10x_i2c.h"
#include "globalvar.h"
#include "rs485_config.h"
#include "rtu.h"
#include "other_hw_config.h"

static int timer2Cnt = 0;
void TIM2_IRQHandler(void){
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET){
        if(timer2Cnt++>gTimeOut){
            TIM_Cmd(TIM2,DISABLE);
            if(rxBuf.tail <2)
                exceptAns(0x03,0x12);
            else
                exceptAns(rxBuf.buf[1],0x12);
            CLEARBUF(rxBuf);
            print(txBuf.buf,txBuf.tail-txBuf.head);
            CLEARBUF(txBuf);
        }
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}

//uint8_t uart4_data[10] = "abcdefghi";
uint8_t ok = 0;
void UART4_IRQHandler(void)
{
//    static int i = 0;
    if(RS485_CAN_NOT_RX){
        USART_ClearITPendingBit(UART4,USART_IT_RXNE);
        goto haha;
    }
    if(USART_GetITStatus(UART4,USART_IT_IDLE)!=RESET){
        USART_ClearITPendingBit(UART4,USART_IT_IDLE);
    }
    if(USART_GetITStatus(UART4,USART_IT_RXNE)!=RESET)
    {
        PUTINTOBUF(rxBuf,USART_ReceiveData(UART4));    
   //     uart4_data[i++] = USART_ReceiveData(UART4);
        //if(i==10){
        //    i = 0;
        if(okToParse()){
            TIM_Cmd(TIM2,DISABLE);
            parse();
            print(txBuf.buf,txBuf.tail-txBuf.head);
            CLEARBUF(txBuf);
        }else{
            timer2Cnt = 0;
            if(rxBuf.tail==1)
                TIM_Cmd(TIM2,ENABLE);
        }
    //    if(okToParse()){
    //        print(txBuf.buf,txBuf.tail-txBuf.head);
    //        CLEARBUF(txBuf);
    //    }
//            RS485_TX_ENABLE;
        USART_ClearITPendingBit(UART4,USART_IT_RXNE);
        //buf[ptr++]=USART_ReceiveData(USART3);
    }
haha:   
    if(USART_GetFlagStatus(UART4,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(UART4,USART_FLAG_ORE);
        USART_ReceiveData(UART4);
    }
}
unsigned char buf[128];
int ptr=0;
uint8_t d='a';
void USART3_IRQHandler(void)
{
    if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
    {
        d = USART_ReceiveData(USART3);
        USART_ClearITPendingBit(USART3,USART_IT_RXNE);
        //buf[ptr++]=USART_ReceiveData(USART3);
    }
    if(USART_GetFlagStatus(USART3,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(USART3,USART_FLAG_ORE);
        USART_ReceiveData(USART3);
    }
}
//1ms定时器，如果连续采样低电平50次，
//则认为已经按下按键。
uint8_t inputLock = 0;
//void TIM3_IRQHandler(void)  
void timer3(void)
{  
    const uint8_t CNTTIMES = 20;
    static uint8_t inCnt[INPUTNUM] = {0};
   // static uint8_t releaseCnt[INPUTNUM] = {0};
    static uint16_t clearMemCnt = 0;
    static uint16_t setCnt = 0;
    uint8_t i = 0;
//    if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET){
 //input alarm check
        inputLock = 1;
        for(i=0;i<ALARMNUM;i++)
        {
            if(GPIO_ReadInputDataBit(gMap[i].addr,
                        gMap[i].loc) ==Bit_RESET){
                if(inCnt[i]<CNTTIMES)
                    inCnt[i]++;
            }else{
                if(inCnt[i]>0)
                    inCnt[i]--;
            }
            if(inCnt[i]>=CNTTIMES-5)
            {
                regs[i+7].val = 1;
                regs[i+41].val = 1;
                if(i<16){
                    regs[5].val |= (1<<i);
                    regs[39].val = regs[5].val;
                }else{
                    regs[6].val |= (1<<i);
                    regs[40].val = regs[6].val;
                }
                gInputFlag |= (1<<i);
                gInputReleaseFlag &=(~(1<<i));
                if(gInputFlag & gColor){
                    regs[3].val = 1;
                    soundAlarm();
                }
                if(gInputFlag & (~gColor)){
                    regs[4].val = 1;
                    soundPreAlarm();
                }
        //        gHistory[gHistoryPointer] = i;
        //        if(gColor & (1<<i))
        //            gHistory[gHistoryPointer] +=32;
        //        gHistoryPointer = (gHistoryPointer+1)%256;
        //        if(gHistoryNum<256)
        //            gHistoryNum++;
            }
            else
            {
                regs[i+6].val = 0;
                regs[5].val &= (~(1<<i));
                if(inCnt[i]==0)
                    gInputReleaseFlag |= (1<<i);
                else
                    gInputReleaseFlag &=(~(1<<i));
            }
        }
        if(regs[5].val!=0)
            regs[3].val = 1;
        else
            regs[3].val = 0;
//button input
        for(i=ALARMNUM;i<INPUTNUM;i++)
        {
            if(GPIO_ReadInputDataBit(gMap[i].addr,gMap[i].loc)==Bit_RESET){
                if(inCnt[i]<CNTTIMES)
                    inCnt[i]++;
            }else{
                if(inCnt[i]>0)
                    inCnt[i]--;
            }
            if(inCnt[i]>=CNTTIMES-5){
                gButtonInputFlag |= (1<<(i-ALARMNUM));
                gButtonReleaseFlag &= (~(1<<(i-ALARMNUM)));
            }
            else if(inCnt[i]>0)
                gButtonReleaseFlag &= (~(1<<(i-ALARMNUM)));
            else
                gButtonReleaseFlag |= (1<<(i-ALARMNUM));
 
        }
        if(((gButtonInputFlag&0x0a)==0x0a)||
                ((gButtonInputFlag&0x0300)==0x0300)){
            if(clearMemCnt <400)
                clearMemCnt++;
        }
        else if(clearMemCnt>20)
            clearMemCnt-=20;
        else
            clearMemCnt = 0;

        if((gButtonInputFlag&0x0050)==0x0050){
            if(setCnt <40)
                setCnt++;
        }
        else if(setCnt>5)
            setCnt-=5;
        else
            setCnt = 0;
//ent mov
        if(setCnt>35){
            gDoubleButtonFlag |= 2;
            gDoubleButtonReleaseFlag &=0xfd;
        }
        else if(setCnt>0)
            gDoubleButtonReleaseFlag &=0xfd;
        else
            gDoubleButtonReleaseFlag |=2;
     
          //  gDoubleButtonFlag &= 0xfd;
//rst mem
        if(clearMemCnt>300){
            gDoubleButtonFlag |= 1;
            gDoubleButtonReleaseFlag &=0xfe;
        }else if(clearMemCnt>0)
            gDoubleButtonReleaseFlag &=0xfe;
        else
            gDoubleButtonReleaseFlag |= 1;
        inputLock = 0;
  //      TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
  //  }
}

//1s定时，芯片正在运行的指示灯，闪烁表示正在运行，不闪烁表示有问题，程序没有运行
volatile int8_t outputLock = 0;
uint32_t output1 = 0;//低16位
uint32_t output2 = 0;//高16位
uint8_t cnt = 0; //整体计数，0～72，用来控制数据信号
uint8_t icnt = 1; //内部计数，0～1，用来控制时钟和锁存信号
void TIM4_IRQHandler(void){
    if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET){
        if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)!=Bit_RESET){
            GPIO_ResetBits(GPIOD,GPIO_Pin_2);
        }else{
            GPIO_SetBits(GPIOD,GPIO_Pin_2);
        }

        TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
    }
}
//1ms定时，将LED状态输:出。

#define SETSHIFTCLK      GPIO_SetBits(GPIOE,GPIO_Pin_0)
#define RESETSHIFTCLK    GPIO_ResetBits(GPIOE,GPIO_Pin_0)
#define SETSHIFTDAT      GPIO_SetBits(GPIOE,GPIO_Pin_2)
#define RESETSHIFTDAT    GPIO_ResetBits(GPIOE,GPIO_Pin_2)
#define SETLATCH         GPIO_SetBits(GPIOE,GPIO_Pin_1)
#define RESETLATCH       GPIO_ResetBits(GPIOE,GPIO_Pin_1)

void TIM5_IRQHandler(void){
    uint8_t pwr = 0x4;
    if(TIM_GetITStatus(TIM5,TIM_IT_Update)!=RESET){
        if(outputLock){
            if(icnt){   //时钟下降沿,锁存上升沿,数据移位
                if(cnt==68){
                    SETLATCH;
                }else{
                    RESETLATCH;
                    if(cnt<4){
                        if(pwr&(1<<(cnt)))
                            SETSHIFTDAT;
                        else
                            RESETSHIFTDAT;
                    }else if(cnt<36){
                        if(output2 & (1<<(35-cnt)))
                            SETSHIFTDAT;
                        else
                            RESETSHIFTDAT;
                    }else{
                        if(output1 & (1<<(67-cnt)))
                            SETSHIFTDAT;
                        else
                            RESETSHIFTDAT;       
                    }   
              /*      }else{
                        if((output>>(cnt-4)) & 1)
                            SETSHIFTDAT;
                        else
                            RESETSHIFTDAT;
                    }*/
                }
                RESETSHIFTCLK;
                if(cnt==69){
                    cnt=0;
                }else{
                    cnt++;
                }
                icnt = 0;
            }else{        //时钟上升沿,锁存下降沿
                if(cnt==69){
                    RESETSHIFTCLK;
                    outputLock = 0;
                }else{
                    SETSHIFTCLK;
                }
                RESETLATCH;
                icnt=1;
            }
        }
       TIM_ClearITPendingBit(TIM5,TIM_IT_Update);//清中断
    }
}
