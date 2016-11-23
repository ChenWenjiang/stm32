//#include "stm32f10x.h"
#include "led.h"
uint8_t gSetCnt;
LED gLed[ALLLEDNUM];

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
    for(;i<SIGLEDNUM;i++)
    {
        gLed[i].type = SIG;
        gLed[i].light = FALSE;
        gLed[i].color = YELLOW;
        gLed[i].ledstate = STABLE;
        gLed[i].location= i;
    }
//    i=32;
    for(;i<ALLLEDNUM;i++)
    {
        gLed[i].type = PWR;
        gLed[i].color = RED;
        gLed[i].ledstate = STABLE;
        gLed[i].location = i;
        if()//TODO pwr0 or pwr1 pin is hight
            gLed[i].light = TRUE;
        else
            gLed[i].light = FALSE;
    }
    
}


STATUS setColor(uint8_t locat,COLOR col)
{
    if(gLed[locat].location!=locat)
        return ERROR;
    gLed[locat].color = col;
    return OK;
}

STATUS setColorAll(COLOR col)
{
    uint8_t i=0;
    for(;i<SIGLEDNUM;i++)
    {
        if(setColor(i,col)==ERROR)
            return ERROR;
    }
    return OK;
}

STATUS setLedState(uint8_t locat,LEDSTATE st)
{
    if(gLed[locat].location !=locat)
        return ERROR;
    gLed[locat].ledstate = st;
}

STATUS setLedStateAll(LEDSTATE st)
{
    uint8_t i=0;
    for(;i<SIGLEDNUM;i++)
    {
        if(setLedState(i,st)==ERROR)
            return ERROR;
    }
    return OK;
}

STATUS turnOn(uint8_t locat)
{
    if(gLed[locat].location!=locat)
        return ERROR;
    gLed[locat].light=TRUE;
    return OK;
}

STATUS turnOff(uint8_t locat)
{
    if(gLed[locat].location!=locat)
        return ERROR;
    gLed[locat].light = FALSE;
    return OK;
}

STATUS turnOnAll(void)
{
    uint8_t i=0;
    for(;i<SIGLEDNUM;i++)
        if(turnOn(i)==ERROR)
            return ERROR;
    return OK;
}

STATUS turnOffAll(void)
{
    uint8_t i=0;
    for(;i<SIGLEDNUM;i++)
        if(turnOff(i)==ERROR)
            return ERROR;
    return OK;
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
                if(gLed[gSetCnt].color==RED)
                    gLed[gSetCnt].color = YELLOW;
                else
                    gLed[gSetCnt].color = RED;
            }
        }
        else if(gInputFlag[ENT])//ENT
        {
            if(gState==SSET)
                gState = SNORMAL;
        }
    }
}
STATUS setLed(void)
{
    uint8_t i=0;
    switch(gState)
    {
        case SNORMAL:
            for(i=0;i<SIGLEDNUM;i++)
            {
                gLed[i].ledstate = STABLE;
                gLed[i].light = FALSE;
            }
            break;
        case STEST:
            for(i = 0;i<SIGLEDNUM;i++)
            {
                gLed[i].ledstate = TWINK;
                gLed[i].light = TRUE;
            }
            break;
        case SACK:
            for(i=0;i<SIGLEDNUM;i++)
            {
                if(gLed[i].ledstate==TWINK)
                {
                    gLed[i].ledstate = STABLE;
                    gLed[i].light = TRUE;
                }
            }
            break;
        case SALARM:
            for(i=0;i<ALARMNUM;i++)
            {
                if(gInputFlag[i])
                {
                    gLed[gInput[i].ledloc].ledstate = TWINK;
                    gLed[gInput[i].ledloc].light = TRUE;
                    gInputFlag[i] = 0;
                }
                else
                {
                    gLed[gInput[i].ledloc].ledstate = STABLE;
                    gLed[gInput[i].ledloc].light = FALSE;
                }
            }
            break;
        case SMEM:
            for(i=0;i<SIGLEDNUM;i++)
            {
                //TODO
            }
            break;
        case SSET:
            for(i=0;i<SIGLEDNUM;i++)
            {
                gLed[gInput[i].ledloc].ledstate = STABLE;
                gLed[gInput[i].ledloc].light = FALSE;
            }
            gLed[gInput[gSetCnt].ledloc].ledstate = TWINK;
            gLed[gInput[gSetCnt].ledloc].light = TRUE;
            break;
        default:
            gState = SNORMAL;
            return ERROR;
    }
    return OK;
}


void show(void)
{
    //TODO:show led panel
}
