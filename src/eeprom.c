#include "eeprom.h"
#include "globalvar.h"

uint8_t eeprom_store_history(void){
    uint8_t err;
    if(gHistoryPointer_backup==gHistoryPointer)
        return 0;
    if(gHistoryPointer < gHistoryPointer_backup){
        err = Write(0xa0,gHistoryPointer_backup,
                gHistory+gHistoryPointer_backup,
                256-gHistoryPointer_backup);
        if(err!=0)
            return err;
        if(gHistoryPointer!=0){
            err = Write(0xa0,0,gHistory,gHistoryPointer);
            if(err!=0)
                return err;
        }
    }else{
        err = Write(0xa0,gHistoryPointer_backup,
                gHistory+gHistoryPointer_backup,
                gHistoryPointer-gHistoryPointer_backup);
        if(err!=0)
            return err;
    }
    gHistoryPointer_backup = gHistoryPointer;
    err = Single_Write(0xa2,0,gHistoryPointer);
    if(err!=0)
        return err;
    err = Write(0xa2,7,(uint8_t *)(&gHistoryNum),2);
    return err;
}

uint8_t  eeprom_load(void){
    uint8_t err;
    uint8_t tmp[9] = {0};
    err = Read(0xa0,0,gHistory,256);
    if(err!=0)
        return err;
    err = Read(0xa2,0,tmp,9);
    if(err!=0)
        return err;
    gHistoryPointer = tmp[0];
    gColor = tmp[1]+(tmp[2]<<8)+(tmp[3]<<16)+(tmp[4]<<24);
    gRS485Config = tmp[5];
    gModbusAddr = tmp[6];
    gHistoryNum = tmp[8];
    gHistoryNum = tmp[7] + (gHistoryNum<<8);
    return 0;
}

uint8_t  eeprom_store_color(void){
    return Write(0xa2,1,(uint8_t *)(&gColor),4);
}

uint8_t eeprom_store_rs485config(uint8_t newConfig){
    return Single_Write(0xa2,5,newConfig);
}

uint8_t eeprom_store_modbusaddr(uint8_t newAddr){
    return Single_Write(0xa2,6,newAddr);
}
uint8_t eeprom_clear_history(void){
    int i = 0;
    uint8_t err = 0;
    for(i=0;i<256;i++)
        gHistory[i] = 0;
    gHistoryPointer = 0;
    gHistoryPointer_backup = 0;
    gHistoryNum = 0;

    err =  Write(0xa0,0,gHistory,256);
    if(err!=0)
        return err;
    err = Single_Write(0xa2,0,gHistoryPointer);
    if(err!=0)
        return err;
    return Write(0xa2,7,(uint8_t *)(&gHistoryNum),2);
}
