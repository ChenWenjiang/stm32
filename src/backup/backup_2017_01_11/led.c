#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "led.h"
#include "globalvar.h"

//uint8_t gSetCnt;

void inputInit(void)
{
    gMap[0].addr = GPIOE;
    gMap[0].loc = GPIO_Pin_4;
    gMap[0].ledloc = 0;

    gMap[1].addr = GPIOE;
    gMap[1].loc = GPIO_Pin_5;
    gMap[1].ledloc = 1;
    
    gMap[2].addr = GPIOE;
    gMap[2].loc = GPIO_Pin_6;
    gMap[2].ledloc = 2;
    
    gMap[3].addr = GPIOC;
    gMap[3].loc = GPIO_Pin_13;
    gMap[3].ledloc = 3;
    
    gMap[4].addr = GPIOF;
    gMap[4].loc = GPIO_Pin_0;
    gMap[4].ledloc = 4;
    
    gMap[5].addr = GPIOF;
    gMap[5].loc = GPIO_Pin_1;
    gMap[5].ledloc = 5;
    
    gMap[6].addr = GPIOF;
    gMap[6].loc = GPIO_Pin_2;
    gMap[6].ledloc = 6;
    
    gMap[7].addr = GPIOF;
    gMap[7].loc = GPIO_Pin_3;
    gMap[7].ledloc = 7;
    
    gMap[8].addr = GPIOF;
    gMap[8].loc = GPIO_Pin_4;
    gMap[8].ledloc = 8;
    
    gMap[9].addr = GPIOF;
    gMap[9].loc = GPIO_Pin_5;
    gMap[9].ledloc = 9;
    
    gMap[10].addr = GPIOF;
    gMap[10].loc = GPIO_Pin_6;
    gMap[10].ledloc = 10;
    
    gMap[11].addr = GPIOF;
    gMap[11].loc = GPIO_Pin_7;
    gMap[11].ledloc = 11;
    
    gMap[12].addr = GPIOF;
    gMap[12].loc = GPIO_Pin_8;
    gMap[12].ledloc = 12;
    
    gMap[13].addr = GPIOF;
    gMap[13].loc = GPIO_Pin_9;
    gMap[13].ledloc = 13;
    
    gMap[14].addr = GPIOF;
    gMap[14].loc = GPIO_Pin_10;
    gMap[14].ledloc = 14;
    
    gMap[15].addr = GPIOC;
    gMap[15].loc = GPIO_Pin_0;
    gMap[15].ledloc = 15;
    
    gMap[16].addr = GPIOC;
    gMap[16].loc = GPIO_Pin_1;
    gMap[16].ledloc = 16;
    
    gMap[17].addr = GPIOC;
    gMap[17].loc = GPIO_Pin_2;
    gMap[17].ledloc = 17;
    
    gMap[18].addr = GPIOC;
    gMap[18].loc = GPIO_Pin_3;
    gMap[18].ledloc = 18;
    
    gMap[19].addr = GPIOA;
    gMap[19].loc = GPIO_Pin_1;
    gMap[19].ledloc = 19;
    
    gMap[20].addr = GPIOA;
    gMap[20].loc = GPIO_Pin_2;
    gMap[20].ledloc = 20;
    
    gMap[21].addr = GPIOA;
    gMap[21].loc = GPIO_Pin_3;
    gMap[21].ledloc = 21;
    
    gMap[22].addr = GPIOA;
    gMap[22].loc = GPIO_Pin_4;
    gMap[22].ledloc = 22;
    
    gMap[23].addr = GPIOA;
    gMap[23].loc = GPIO_Pin_5;
    gMap[23].ledloc = 23;
    
    gMap[24].addr = GPIOA;
    gMap[24].loc = GPIO_Pin_6;
    gMap[24].ledloc = 24;
    
    gMap[25].addr = GPIOA;
    gMap[25].loc = GPIO_Pin_7;
    gMap[25].ledloc = 25;
    
    gMap[26].addr = GPIOC;
    gMap[26].loc = GPIO_Pin_4;
    gMap[26].ledloc = 26;
    
    gMap[27].addr = GPIOC;
    gMap[27].loc = GPIO_Pin_5;
    gMap[27].ledloc = 27;
    
    gMap[28].addr = GPIOB;
    gMap[28].loc = GPIO_Pin_0;
    gMap[28].ledloc = 28;
    
    gMap[29].addr = GPIOB;
    gMap[29].loc = GPIO_Pin_1;
    gMap[29].ledloc = 29;
    
    gMap[30].addr = GPIOB;
    gMap[30].loc = GPIO_Pin_2;
    gMap[30].ledloc = 30;
    
    gMap[31].addr = GPIOF;
    gMap[31].loc = GPIO_Pin_11;
    gMap[31].ledloc = 31;
    
    gMap[ACK].addr = GPIOG;
    gMap[ACK].loc = GPIO_Pin_14;
    gMap[ACK].ledloc = ACK;

    gMap[RST].addr = GPIOG;
    gMap[RST].loc = GPIO_Pin_15;
    gMap[RST].ledloc = RST;

    gMap[TEST].addr = GPIOB;
    gMap[TEST].loc = GPIO_Pin_3;
    gMap[TEST].ledloc = TEST;

    gMap[MEM].addr = GPIOB;
    gMap[MEM].loc = GPIO_Pin_5;
    gMap[MEM].ledloc = MEM;

    gMap[MOV].addr = GPIOB;
    gMap[MOV].loc = GPIO_Pin_9;
    gMap[MOV].ledloc = MOV;
    
    gMap[ADD].addr = GPIOB;
    gMap[ADD].loc = GPIO_Pin_8;
    gMap[ADD].ledloc = ADD;

    gMap[ENT].addr = GPIOB;
    gMap[ENT].loc = GPIO_Pin_4;
    gMap[ENT].ledloc = ENT;
}
void setState(void)
{
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
        gTwink |= regs[5].val;
        gLight |= gTwink;
    }
    else 
    {
      if((gButtonInputFlag & 0x0A)==0x0a)//RST MEM
      {
          gState = SNORMAL;
          gLight = 0;
          gTwink = 0;
          gButtonInputFlag &=(~(0x0a));
       //   clearMem();
      }
      else if(gButtonInputFlag & 2)  //RST is pushed
      {
        gState = SNORMAL;
        gLight = 0;
        gTwink = 0;
        gButtonInputFlag &= 0xfffffffd;
      } 
      else if((gButtonInputFlag & 0x50)==0x50) //MOV ENT
      {/*
          gState = SSET;
          gSetCnt=0;*/
          gState = SNORMAL;
          gLight = 0;
          gTwink = 0;
          gButtonInputFlag &= (~(0x50));
      }
      else if((gState==SALARM)&&(gButtonInputFlag & 1)) //if state is alarm and ACK is pushed
      {
        gState = SACK;
        gTwink = 0;
        gButtonInputFlag &=0xfffffffe;
      }
      else if(gButtonInputFlag & 4)//TEST
      {
          gState = STEST;
          gLight = 0xffffffff;
          gTwink = 0xffffffff;
      }
      else if(gButtonInputFlag & 8)//MEM
      {
         // gState = SMEM;
         gState = SNORMAL;
          gLight = 0;
          gTwink = 0;
      }
/*      else if(gButtonInputFlag & 0x10)//MOV
      {
          if(gState == SSET)
          {
              gSetCnt++;
          }
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
      }
      else if(gButtonInputFlag & 0x40)//ENT
      {
          if(gState==SSET)
          {
              gState = SNORMAL;
        //      storeLedColor();
          }
      }*/
   }
}
/*
void ledInit(void)
{
    uint8_t i = 0;
    
    gLight = 0;
    gTwink = 0;
    //TODO read from eeprom to set color
    gColor = loadLedColor();
}
*/
/*
STATUS setState(void)
{
    uint8_t i = 0;*/
    /*
    for(i=0;i<ALARMNUM;i++)
    {
        if(gInputFlag[i])
            gState = SALARM;
        return OK;
    }*/
/*    if(regs[5].val)
    {
        gState = SALARM;
        return OK;
    }

    if(gState==SALARM)
    {
        if(gButtonInputFlag & 1)//ACK
        {
            gState = SACK;
            return OK;
        }
    }
    else
    {
        if(gButtonInputFlag & 0x0A )//RST MEM
        {
            clearMem();
        }
        else if(gButtonInputFlag & 0x50) //MOV ENT
        {
            gState = SSET;
            gSetCnt=0;
        }
        else if(gButtonInputFlag & 2)//RST
        {
            gState = SNORMAL;
        }
        else if(gButtonInputFlag & 4)//TEST
        {
            gState = STEST;
        }
        else if(gButtonInputFlag & 8)//MEM
        {
            gState = SMEM;
        }
        else if(gButtonInputFlag & 0x10)//MOV
        {
            if(gState == SSET)
            {
                gSetCnt++;
            }
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
        }
        else if(gButtonInputFlag & 0x40)//ENT
        {
            if(gState==SSET)
            {
                gState = SNORMAL;
                storeLedColor();
            }
        }
    }
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
            for(i=0;i<ALARMNUM;i++)
            {
                if(gInputFlag[i] && (gTwink & (1<<gInput[i].ledloc)))
                {
                    gTwink |= (1<<gInput[i].ledloc);
                    storeAlarmHistory(i);
                }
            }
            gLight |= gTwink;
            break;
        case SMEM:
            //TODO global variable
            i = loadAlarmHistory(gPushCnt);
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
*/
