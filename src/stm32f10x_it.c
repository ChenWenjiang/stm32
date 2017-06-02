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
        return;
    }
    if(USART_GetFlagStatus(UART4,USART_FLAG_ORE)==SET){
        USART_ClearFlag(UART4,USART_FLAG_ORE);
        USART_ReceiveData(UART4);
    }
    if(USART_GetFlagStatus(UART4,USART_FLAG_NE)!=RESET){
      USART_ClearFlag(UART4,USART_FLAG_NE);
    }
    if(USART_GetFlagStatus(UART4,USART_FLAG_FE)!=RESET){
      USART_ClearFlag(UART4,USART_FLAG_FE);
    }
    if(USART_GetFlagStatus(UART4,USART_FLAG_IDLE)!=RESET){
      USART_ClearFlag(UART4,USART_FLAG_IDLE);
    }
    
    if(USART_GetFlagStatus(UART4,USART_FLAG_PE)!=RESET){
/*      CLEARBUF(txBuf);
      PUTINTOBUF(txBuf,0xaa);
      PUTINTOBUF(txBuf,USART_ReceiveData(UART4));
      print(txBuf.buf,txBuf.tail-txBuf.head);
      CLEARBUF(txBuf);*/
      USART_ClearFlag(UART4,USART_FLAG_PE);
    }
    if(USART_GetITStatus(UART4,USART_IT_RXNE)!=RESET){
      PUTINTOBUF(rxBuf,USART_ReceiveData(UART4));    
      if(okToParse()){
        TIM_Cmd(TIM2,DISABLE);
        parse();
        if((txBuf.buf[0]!=0))
          print(txBuf.buf,txBuf.tail-txBuf.head);
        CLEARBUF(txBuf);
      }else{
        timer2Cnt = 0;
        if(rxBuf.tail==1)
          TIM_Cmd(TIM2,ENABLE);
      }
      USART_ClearITPendingBit(UART4,USART_IT_RXNE);
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
//这个宏定义用来定义采样到低电平的次数
#define CNTTIMES 25 
//两秒清除所有的mem
#define CLRMEMCNT 1000   
void TIM3_IRQHandler(void)  
//void timer3(void)
{  
    //const uint8_t CNTTIMES = 50;
    static uint8_t inCnt[INPUTNUM] = {0};
   // static uint8_t releaseCnt[INPUTNUM] = {0};
    static uint16_t clearMemCnt = 0;
    static uint16_t setCnt = 0;
    uint8_t i = 0;
    //如果产生了定时器update中断
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET){
 //input alarm check
        inputLock = 1;
        //检测ALARMNUM个报警输入信号,如果检测到有报警信号，则
        //该报警信号对应的计数值自增。不然自减
       // for(i=0;i<ALARMNUM;i++)
        for(i=0;i<gInputNumber;i++)
        {
            if(GPIO_ReadInputDataBit(gMap[i].addr,
                        gMap[i].loc) ==Bit_RESET){
                if(inCnt[i]<CNTTIMES)
                    inCnt[i]++;
            }else{
                if(inCnt[i]>0)
                    inCnt[i]--;
            }
            //如果计数值大于CNTTIMES-5，则认为有真正的报警输入
            //并设置报警信号对应的“寄存器”（这些寄存器是对于MODBUS来说的）
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
                //对应的输入标志置位
                //对应的释放标志清除
                gInputFlag |= (1<<i);
                gInputReleaseFlag &=(~(1<<i));
                //如果有报警信号，需要产生报警声音
                if(gInputFlag & gColor){
                    regs[3].val = 1;
                    soundAlarm();
                }
                //如果有预报警信号，需要产生预报警声音
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
            else //if(inCnt[i]>=CNTTIMES-5) 如果低于阈值，则清除相应的寄存器值
            {
                regs[i+6].val = 0;
                regs[5].val &= (~(1<<i));
                //如果计数值达到0，则设置释放标志位
                if(inCnt[i]==0)
                    gInputReleaseFlag |= (1<<i);
                else
                    gInputReleaseFlag &=(~(1<<i));
            }
        }
        //regs[3]判断是否有报警信号
        if(regs[5].val!=0)
            regs[3].val = 1;
        else
            regs[3].val = 0;
//button input，按键输入，与报警输入类似
        for(i=ALARMNUM;i<INPUTNUM;i++)
        {
            if(GPIO_ReadInputDataBit(gMap[i].addr,gMap[i].loc)==Bit_RESET){
                if(inCnt[i]<CNTTIMES)
                    inCnt[i]++;
            }else{
                if(inCnt[i]>0)
                    inCnt[i]--;
            }
            if(inCnt[i]>=CNTTIMES-5){ //查过阈值，则输入标志位置1
                gButtonInputFlag |= (1<<(i-ALARMNUM));
            }
            if(inCnt[i]>0)
                gButtonReleaseFlag &= (~(1<<(i-ALARMNUM)));
            else{ //计数等于0，则释放标志位置1
                gButtonReleaseFlag |= (1<<(i-ALARMNUM));
            }
        }
        
        //判断是否有两个按键同时按下，用来清除所有的历史记录
        if(((gButtonInputFlag&0x0a)==0x0a)||
                ((gButtonInputFlag&0x0300)==0x0300)){
            if(clearMemCnt < CLRMEMCNT) 
                clearMemCnt++;
        }
        else if(clearMemCnt>20)  
            clearMemCnt--;
        else
            clearMemCnt = 0;
//两个按键同时按下，设置灯的颜色
        if((gButtonInputFlag&0x0050)==0x0050){
            if(setCnt <CNTTIMES)
                setCnt++;
        }
        else if(setCnt>0)
            setCnt--;
//ent mov
        if(setCnt>CNTTIMES-5){
            gDoubleButtonFlag |= 2;
        }
        //if((gDoubleButtonFlag&2)&&((gButtonReleaseFlag & 0x0050)==0x0050))
        if((gDoubleButtonFlag&2)&&//((gButtonReleaseFlag & 0x0050)==0x0050))
          (inCnt[ENT]==0) && (inCnt[MOV]==0)
          )
            gDoubleButtonReleaseFlag |=2;
        else{
            gDoubleButtonReleaseFlag &=0xfd;
        }
//rst mem
        if(clearMemCnt>CLRMEMCNT-200){
            gDoubleButtonFlag |= 1;
        }
  //      if((gDoubleButtonFlag & 1) 
  //      && ((gButtonReleaseFlag & 0x050a)==0x050a))
        if((gDoubleButtonFlag & 1) && 
            (inCnt[RST]==0) && (inCnt[MEM]==0) && 
            (inCnt[RST_IN]==0) && (inCnt[MEM_IN]==0))
            // && ((gButtonReleaseFlag & 0x050a)==0x050a))
            gDoubleButtonReleaseFlag |= 1;
        else{
            gDoubleButtonReleaseFlag &=0xfe;
        }
        //ent mov
        if((gDoubleButtonFlag & 2)&&(!(gDoubleButtonReleaseFlag & 2))){
          gButtonReleaseFlag &= ~(1<<(ENT-ALARMNUM));
          gButtonReleaseFlag &= ~(1<<(MOV-ALARMNUM));
          gButtonInputFlag &= ~(1<<(ENT-ALARMNUM));
          gButtonInputFlag &= ~(1<<(MOV-ALARMNUM));
        }
        //rst mem
        if((gDoubleButtonFlag & 1) && (!(gDoubleButtonReleaseFlag & 1))){
          gButtonReleaseFlag &= ~(1<<(RST-ALARMNUM));
          gButtonReleaseFlag &= ~(1<<(MEM-ALARMNUM));
          gButtonReleaseFlag &= ~(1<<(RST_IN-ALARMNUM));
          gButtonReleaseFlag &= ~(1<<(MEM_IN-ALARMNUM));
          gButtonInputFlag &= ~(1<<(RST-ALARMNUM));
          gButtonInputFlag &= ~(1<<(MEM-ALARMNUM));
          gButtonInputFlag &= ~(1<<(RST_IN-ALARMNUM));
          gButtonInputFlag &= ~(1<<(MEM_IN-ALARMNUM));
        }
        inputLock = 0;
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
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
