//#include "stm32f10x.h"
#include "led.h"
#include "globalvar.h"
#include "eeprom.h"
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
    gInput[0].loc = 0;
    gInput[0].ledloc = 0;
    //TODO ...
    //...
    //...
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
    for(i=0;i<ALARMNUM;i++)
    {
        if(gInputFlag[i])
            gState = SALARM;
        return OK;
    }
    if(gState==SALARM)
    {
        if(gInputFlag[ACK])//ACK
        {
            gState = SACK;
            return OK;
        }
    }
    else
    {
        if(gInputFlag[RST] && gInputFlag[MEM])//RST MEM
        {
            clearMem();
        }
        else if(gInputFlag[MOV] && gInputFlag[ENT]) //MOV ENT
        {
            gState = SSET;
            gSetCnt=0;
        }
        else if(gInputFlag[RST])//RST
        {
            gState = SNORMAL;
        }
        else if(gInputFlag[TEST])//TEST
        {
            gState = STEST;
        }
        else if(gInputFlag[MEM])//MEM
        {
            gState = SMEM;
        }
        else if(gInputFlag[MOV])//MOV
        {
            if(gState == SSET)
            {
                gSetCnt++;
            }
        }
        else if(gInputFlag[ADD])//ADD
        {
            if(gState==SSET)
            {
                if(gColor & (1<<gSetCnt))
                    gColor &= (~(1<<gSetCnt));
                else
                    gColor |= (1<<gSetCnt);
            }
        }
        else if(gInputFlag[ENT])//ENT
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

