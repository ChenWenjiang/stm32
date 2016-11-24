#include "types.h"
#include "reg.h"

modreg_t regs[74];
unsigned char  gModbusAddr = 0; //TODO read from eeprom
STATE gState = SNORMAL;

BUF rxBuf;
BUF txBuf;

INPUT gMap[SIGLEDNUM];
uint8_t gButtonInputFlag;

//led
uint32_t gLight = 0;    //0:dark 1:light
uint32_t gTwink = 0;    //0:stable 1:twink
uint32_t gColor = 0;    //0:yellow 1:red

uint8_t gPwr = 0; //
//button
uint8_t gButton = 0;  //1:pushed

//
int gRxCnt = 0;
//flags
int gI2cRW = 0;
int gI2cNBytes = 0;
int gI2cErr = 0;
unsigned char  gI2cData[256] = {0};
int gI2cAck = 0;

