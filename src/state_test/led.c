#if defined(__cplusplus)||defined(c_plusplus)
extern "C"{
#endif
#include "stm32f10x.h"
#include "led.h"
#include "globalvar.h"
#include <stdio.h>
static unsigned int loadLedColor(void)
{
    return 0x12345678;
    printf("loadLedColor\n");
}
void ledInit(void)
{
    uint8_t i = 0;
    
    gLight = 0;
    gTwink = 0;
    //TODO read from eeprom to set color
    gColor = loadLedColor();
}
static void clearMem(void)
{
    printf("clearMem\n");
}
static void storeLedColor(void)
{
    printf("storeLedColor\n");
}
STATUS setState(void)
{
    uint8_t i = 0;
    /*
    for(i=0;i<ALARMNUM;i++)
    {
        if(gInputFlag[i])
            gState = SALARM;
        return OK;
    }*/
    if(regs[5].val)
    {
        gState = SALARM;
        return OK;
    }
    else 
    {
      if((gButtonInputFlag & 0x0A)==0x0a)//RST MEM
      {
          clearMem();
          return OK;
      }
      else if(gButtonInputFlag & 2)  //RST is pushed
      {
        gState = SNORMAL;
        return OK;
      } 
      else if((gButtonInputFlag & 0x50)==0x50) //MOV ENT
      {
          gState = SSET;
          gSetCnt=0;
          return OK;
      }
      else if((gState==SALARM)&&(gButtonInputFlag & 1)) //if state is alarm and ACK is pushed
      {
        gState = SACK;
        return OK;
      }
      else if(gButtonInputFlag & 4)//TEST
      {
          gState = STEST;
          return OK;
      }
      else if(gButtonInputFlag & 8)//MEM
      {
          gState = SMEM;
          return OK;
      }
      else if(gButtonInputFlag & 0x10)//MOV
      {
          if(gState == SSET)
          {
              gSetCnt++;
          }
          return OK;
      }
      else if(gButtonInputFlag & 0x20)//ADD
      {
          if(gState==SSET)
          {
              if(gColor & (1<<gSetCnt))
                  gColor &= (~(1<<gSetCnt));
              else
                  gColor |= (1<<gSetCnt);
          }
          return OK;
      }
      else if(gButtonInputFlag & 0x40)//ENT
      {
          if(gState==SSET)
          {
              gState = SNORMAL;
              storeLedColor();
          }
          return OK;
      }
   }
}
static void storeAlarmHistory(unsigned char a)
{
    printf("storeAlarmHistory\n");
}
static int loadAlarmHistory(void)
{
    printf("loadAlarmHistory\n");
    return 1;
}
STATUS setLed(void)
{
    uint8_t i=0;
    switch(gState)
    {
        case SNORMAL:
            gLight = 0;
            gTwink = 0;
            break;
        case STEST:
            gLight = 0xffffffff;
            gTwink = 0xffffffff;
            break;
        case SACK:
            gLight |=gTwink;
            gTwink = 0;
            break;
        case SALARM:
            gTwink |= regs[5].val;
            /*
            for(i=0;i<ALARMNUM;i++)
            {
                if(gTwink & (1<<i))
                    continue;
               // if(regs[gInput[i].ledloc+6].val && (gTwink & (1<<gInput[i].ledloc)))
                else{
                    gTwink |= (1<<i);
                   // storeAlarmHistory(gInput[i].ledloc);
                }
            }*/
            gLight |= gTwink;
            break;
        case SMEM:
            //TODO global variable
            
            i = loadAlarmHistory();
            gTwink = 1<<i;
            gLight = 1<<i;
            break;
        case SSET:
            gTwink = (1<<gInput[gSetCnt].ledloc);
            gLight = gTwink;
            break;
        default:
            gState = SNORMAL;
            return ERROR;
    }
    return OK;
}
#if defined(__cplusplus)||defined(c_plusplus)
}
#endif
