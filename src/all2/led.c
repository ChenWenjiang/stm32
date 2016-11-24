//#include "stm32f10x.h"
#include "led.h"
#include "globalvar.h"

uint8_t gSetCnt;
extern uint32_t gLight;
extern uint32_t gTwink;
extern uint32_t gColor;

static INPUT gInput[INPUTNUM];

void inputInit(void)
{
    uint8_t i=0;
    gInput[0].addr = GPIOA;
    gInput[0].loc = GPIO_Pin_0;
    gInput[0].ledloc = 0;

    gInput[1].addr = GPIOA;
    gInput[1].loc = GPIO_Pin_0;
    gInput[1].ledloc = 0;
    
    gInput[2].addr = GPIOA;
    gInput[2].loc = GPIO_Pin_0;
    gInput[2].ledloc = 0;
    
    gInput[3].addr = GPIOA;
    gInput[3].loc = GPIO_Pin_0;
    gInput[3].ledloc = 0;
    
    gInput[4].addr = GPIOA;
    gInput[4].loc = GPIO_Pin_0;
    gInput[4].ledloc = 0;
    
    gInput[5].addr = GPIOA;
    gInput[5].loc = GPIO_Pin_0;
    gInput[5].ledloc = 0;
    
    gInput[6].addr = GPIOA;
    gInput[6].loc = GPIO_Pin_0;
    gInput[6].ledloc = 0;
    
    gInput[7].addr = GPIOA;
    gInput[7].loc = GPIO_Pin_0;
    gInput[7].ledloc = 0;
    
    gInput[8].addr = GPIOA;
    gInput[8].loc = GPIO_Pin_0;
    gInput[8].ledloc = 0;
    
    gInput[9].addr = GPIOA;
    gInput[9].loc = GPIO_Pin_0;
    gInput[9].ledloc = 0;
    
    gInput[10].addr = GPIOA;
    gInput[10].loc = GPIO_Pin_0;
    gInput[10].ledloc = 0;
    
    gInput[11].addr = GPIOA;
    gInput[11].loc = GPIO_Pin_0;
    gInput[11].ledloc = 0;
    
    gInput[12].addr = GPIOA;
    gInput[12].loc = GPIO_Pin_0;
    gInput[12].ledloc = 0;
    
    gInput[13].addr = GPIOA;
    gInput[13].loc = GPIO_Pin_0;
    gInput[13].ledloc = 0;
    
    gInput[14].addr = GPIOA;
    gInput[14].loc = GPIO_Pin_0;
    gInput[14].ledloc = 0;
    
    gInput[15].addr = GPIOA;
    gInput[15].loc = GPIO_Pin_0;
    gInput[15].ledloc = 0;
    
    gInput[16].addr = GPIOA;
    gInput[16].loc = GPIO_Pin_0;
    gInput[16].ledloc = 0;
    
    gInput[17].addr = GPIOA;
    gInput[17].loc = GPIO_Pin_0;
    gInput[17].ledloc = 0;
    
    gInput[18].addr = GPIOA;
    gInput[18].loc = GPIO_Pin_0;
    gInput[18].ledloc = 0;
    
    gInput[19].addr = GPIOA;
    gInput[19].loc = GPIO_Pin_0;
    gInput[19].ledloc = 0;
    
    gInput[20].addr = GPIOA;
    gInput[20].loc = GPIO_Pin_0;
    gInput[20].ledloc = 0;
    
    gInput[21].addr = GPIOA;
    gInput[21].loc = GPIO_Pin_0;
    gInput[21].ledloc = 0;
    
    gInput[22].addr = GPIOA;
    gInput[22].loc = GPIO_Pin_0;
    gInput[22].ledloc = 0;
    
    gInput[23].addr = GPIOA;
    gInput[23].loc = GPIO_Pin_0;
    gInput[23].ledloc = 0;
    
    gInput[24].addr = GPIOA;
    gInput[24].loc = GPIO_Pin_0;
    gInput[24].ledloc = 0;
    
    gInput[25].addr = GPIOA;
    gInput[25].loc = GPIO_Pin_0;
    gInput[25].ledloc = 0;
    
    gInput[26].addr = GPIOA;
    gInput[26].loc = GPIO_Pin_0;
    gInput[26].ledloc = 0;
    
    gInput[27].addr = GPIOA;
    gInput[27].loc = GPIO_Pin_0;
    gInput[27].ledloc = 0;
    
    gInput[28].addr = GPIOA;
    gInput[28].loc = GPIO_Pin_0;
    gInput[28].ledloc = 0;
    
    gInput[29].addr = GPIOA;
    gInput[29].loc = GPIO_Pin_0;
    gInput[29].ledloc = 0;
    
    gInput[30].addr = GPIOA;
    gInput[30].loc = GPIO_Pin_0;
    gInput[30].ledloc = 0;
    
    gInput[31].addr = GPIOA;
    gInput[31].loc = GPIO_Pin_0;
    gInput[31].ledloc = 0;
}

void ledInit(void)
{
    uint8_t i = 0;
    
    gLight = 0;
    gTwink = 0;
    //TODO read from eeprom to set color
    gColor = loadLedColor();
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

