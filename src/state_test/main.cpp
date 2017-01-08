#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#if defined(__cplusplus)||defined(c_plusplus)
extern "C"{
#endif

#include "stm32f10x.h"
#include "types.h"
#include "reg.h"
#include "led.h"
#include "globalvar.h"
#include "ringbuf.h"

#if defined(__cplusplus)||defined(c_plusplus)
}
#endif
#include <unistd.h>
#include <csignal>
using namespace std;
static int input[INPUTNUM]={0};
#define CNTTIMERS 5
static int inCnt[INPUTNUM]={0};
//1ms interrupt
void TIM3_IRQHandler(void)  
{  
    
    uint8_t i = 0;
    uint16_t iData = 0;
   // TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    //input alarm check
    for(i=0;i<SIGLEDNUM;i++)
    {
     //   if(GPIO_ReadInputDataBit(gInput[i].addr,
       //             gInput[i].loc) ==Bit_RESET)
       if(input[i]==true)
            inCnt[i]++;
        else
            inCnt[i]=0;

        if(inCnt[i]>=CNTTIMES)
        {
            regs[i+6].val = 1;
            regs[5].val |= (1<<i);
            putIntoRingBuf(&ringBuf,i+6);
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

    for(i=ALARMNUM;i<INPUTNUM;i++) //push button
    {
    //    if(GPIO_ReadInputDataBit(gInput[i].addr,gInput[i].loc)==Bit_RESET)
        if(input[i])
            inCnt[i]++;
        else
            inCnt[i] = 0;
        if(inCnt[i]>=CNTTIMERS)
            gButtonInputFlag |= (1<<i);
        else
            gButtonInputFlag &= (~(1<<i));
    }   
}

void timer(int sig)
{
  if(sig==SIGALRM)
  {
    TIM3_IRQHandler();  
    alarm(1);
  }
}


void showInputStruct(INPUT* t)
{
    cout <<hex<<"0x"<<t->addr<<" 0x"<<hex<<t->loc<<" "<<t->ledloc<<endl;
}
void showRegs(modreg_t* t)
{
    cout << hex << t->addr << " " << t->val << " " << t->len << " " << t->mod << endl;
}
void showGlobal(void)
{
    cout <<"gButtonInputFlag = " <<  hex << gButtonInputFlag << endl; 
    for(int i = 0;i<ALARMNUM;i++)
    {
        showInputStruct(gInput+i);
    }
    for(int i=0;i<74;i++)
    {
        showRegs(regs+i);
    }
    cout << "gLight=" << hex << gLight <<endl;
    cout << "gTwink=" << hex << gTwink << endl;
    cout << "gColor=" << hex << gColor << endl;
}

void showState(void)
{
  cout << "gState=";
  switch(gState)
  {
  case SNORMAL:
    cout << "NORMAL";
    break;
  case STEST:
    cout << "TEST";
    break;
  case SALARM:
    cout << "ALARM";
    break;
  case SACK:
    cout << "ACK";
    break;
  case SMEM:
    cout << "MEM";
    break;
  case SSET:
    cout << "SET";
    break;
  default:
    cout << "This is not correct state!";
  }
  cout << endl;
}

void setInput(unsigned int input,unsigned char button)
{
//  if(input!=0)
//  {
//    for(int i=0;i<32;i++)
//    {
//      if(input & (1<<i)!=0)
//      {
//        regs[5].val |=(1<<i);
//        regs[6+i].val = 1;          
//      }
//      else
//      {
//        regs[5].val &=~(1<<i);
//        regs[6+i].val = 0;
//      }
//    }
//  }
  regs[5].val = input;
  gButtonInputFlag = button;
}

int main(void)
{
    inputInit();
    ledInit();
    regsInit();
    ringbufInit(&ringBuf);
    signal(SIGALRM,timer);
    alarm(1);

//    showGlobal();
    showState();
    while(1){
      int a;
      unsigned int c;
      cout << "32 input:";
      cin >> a;
      cout << "button:";
      cin >> c;
      setInput(a,c);
      setState();
      showState();
    }
    return 0;
}
