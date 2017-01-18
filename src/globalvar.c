#if defined(__cplusplus)||defined(c_plusplus)
extern "C"{
#endif
#include "led.h"
#include "types.h"
#include "reg.h"
volatile modreg_t regs[74];
STATE gState = SNORMAL;

BUF rxBuf;
BUF txBuf;

volatile uint16_t gButtonInputFlag = 0;
volatile uint16_t gButtonReleaseFlag = 0;
volatile uint8_t gDoubleButtonFlag = 0;
volatile uint8_t gDoubleButtonReleaseFlag = 0;
//bit 0:ACK    0x0001
//bit 1:RST    0x0002
//bit 2:TEST   0x0004
//bit 3:MEM    0x0008
//bit 4:MOV    0x0010
//bit 5:ADD    0x0020
//bit 6:ENT    0x0040
//
//bit 7:ACK_IN   0x0080
//BIT 8:RST_IN   0x0100
//BIT 9:TEST_IN  0x0200
//BIT 10:MEM_IN  0x0400
INPUT gMap[INPUTNUM];
uint32_t gSetCnt;
uint32_t gInputReleaseFlag;
//led
volatile uint32_t gLight = 0;    //0:dark 1:light
volatile uint32_t gTwink = 0;    //0:stable 1:twink
volatile uint32_t gColor = 0xffffffff;    //0:yellow 1:red

uint8_t gPwr = 0; //

volatile uint16_t gHistoryNum = 0;
volatile uint8_t gHistoryPointer = 0;
volatile uint8_t gHistoryPointer_backup = 0;
volatile uint8_t gHistory[256] = {0};

uint8_t gRS485Config = 0;
uint8_t gModbusAddr = 0;
//ringbuf
BUF ringBuf;

#if defined(__cplusplus)||defined(c_plusplus)
}
#endif
