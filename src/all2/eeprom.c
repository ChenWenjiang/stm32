#include "eeprom.h"
static STATUS eeprom_read(unsigned char page,unsigned char addr,int length)
{
    //TODO gI2cData[0]
    gI2cData[1] = addr;
    gI2cNBytes = 2;
    gI2cRW = 0;
    //TODO turn on timer;
    if(gI2cErr!=0)
        return gI2cErr;
    
    //TODO gI2cData[0]
    gI2cRW = 1;
    gI2cNBytes = length + 1;
    //TODO turn on timer
    return gI2cErr;
}

static STATUS eeprom_write(unsigned char page,unsigned char addr,int length)
{
    //TODO gI2cData[0]
    gI2cData[1] = addr;
    gI2cRW = 0;
    gI2cNBytes = length+2;
    //TODO turn of timer

    return gI2cErr;
}

unsigned int loadLedColor(void)
{
    int i = 0;
    unsigned int tmp = 0;
    if(eeprom_read(1,1,4)!=0)
        return (unsigned int)(gI2cErr);
    for(i=1;i<5;i++)
    {
        tmp = (tmp << 8) + gI2cData[i];
    }
    return tmp;
}
STATUS storeLedColor(void)
{
    int i = 0;
    gI2cData[2] = (gColor>>24)&(0x0ff);
    gI2cData[3] = (gColor>>16)&(0x0ff);
    gI2cData[4] = (gColor>>8) &(0x0ff);
    gI2cData[5] = gColor & 0x0ff;
    if(eeprom_write(1,1,4)!=0)
        return gI2cErr;
    else 
        return OK;
}

unsigned char loadAlarmListHead(void)
{
    if(eeprom_read(1,0,1)!=0)
        return (unsigned char)(gI2cErr);
    else
        return gI2cData[1];
}

unsigned char loadAlarmHistory(unsigned char Nbefore)
{
    unsigned int i = 0;
    if(0!=eeprom_read(1,0,1))   //alarm history head
        return (unsigned char)(gI2cErr);
    i = gI2cData[1];
    if(i<Nbefore)
        i = i+256 - Nbefore;
    if(0!=eeprom_read(0,i,1))
        return (unsigned char)(gI2cErr);
    return gI2cData[1];
}


STATUS storeAlarmHistory(unsigned char alarmLoc)
{
    unsigned char i = 0;
    if(eeprom_read(1,0,1)!=0)
        return gI2cErr;
    i = gI2cData[1];
    gI2cData[2] = alarmLoc;
    i = i+1;
    if(eeprom_write(0,i,1)!=0)   //dev addr + reg addr + data
        return gI2cErr;
    gI2cData[2] = i;
    if(eeprom_write(1,0,1)!=0)
        return gI2cErr;
    return OK;
}

unsigned char loadUSARTConfiguration(void)
{
    if(eeprom_read(1,5,1)!=0)
        return (unsigned char)(gI2cErr);
    return gI2cData[1];
}

STATUS storeUSARTConfiguration(unsigned char config)
{
    gI2cData[2] = config;
    if(eeprom_write(1,5,1)!=0)
        return gI2cErr;
    return OK;
}


unsigned char loadModbusAddr(void)
{
    if(eeprom_read(1,6,1)!=0)
        return (unsigned char)(gI2cErr);
    return gI2cData[1];
}

STATUS storeModbusAddr(unsigned char addr)
{
    gI2cData[2] = addr;
    if(eeprom_write(1,6,1)!=0)
        return gI2cErr;
    return OK;
}


