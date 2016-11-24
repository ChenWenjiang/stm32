#ifndef _GLOBALVAR_H_
#define _GLOBALVAR_H_

#include "rngbuff.h"
#include "types.h"
#include "reg.h"

extern modreg_t regs[74];
extern unsigned char  gModbusAddr; //TODO read from eeprom
extern STATE gState = SNORMAL;

extern BUF rxBuf;
extern BUF txBuf;

extern INPUT gMap[INPUTNUM];
extern uint8_t gButtonInputFlag;
//led
extern uint32_t gLight;    //0:dark 1:light
extern uint32_t gTwink;    //0:stable 1:twink
extern uint32_t gColor;    //0:yellow 1:red

extern uint8_t gPwr; //
//button
extern uint8_t gButton;  //1:pushed

//
extern int gRxCnt;
//flags
extern int gI2cNBytes;
extern int gI2cErr;
extern int gI2cRW;
extern unsigned char gI2cData[256];
extern int gI2cAck;


#endif
