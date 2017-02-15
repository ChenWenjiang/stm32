#ifndef _GLOBALVAR_H_
#define _GLOBALVAR_H_

#include "ringbuf.h"
#include "types.h"
#include "led.h"

extern modreg_t regs[76];
extern STATE gState ;

extern BUF rxBuf;
extern BUF txBuf;

extern uint16_t gButtonInputFlag;
extern uint16_t gButtonReleaseFlag;
extern uint8_t gDoubleButtonReleaseFlag;
extern uint8_t gDoubleButtonFlag;
extern INPUT gMap[INPUTNUM];
extern uint32_t gSetCnt;
extern uint32_t gInputFlag;
extern uint32_t gInputReleaseFlag;
//led
extern volatile  uint32_t gLight;    //0:dark 1:light
extern volatile uint32_t gTwink;    //0:stable 1:twink
extern volatile uint32_t gColor;    //0:yellow 1:red

extern uint8_t gPwr; //
//
extern int gRxCnt;
extern uint16_t gHistoryNum;
extern uint8_t gHistoryPointer;
extern uint8_t gHistoryPointer_backup;
extern uint8_t gHistory[256];

extern uint8_t gRS485Config;
extern uint8_t gModbusAddr;

//ringbuf
extern BUF ringBuf;
extern int gTimeOut;
#endif
