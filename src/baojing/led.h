/****************************************************************************
 * Filename: head.h
 * Description: define some kinds of data types will be used.
 * Author: ChenWenjiang
 * Created: 2016-10-18 09:25
 * History:
 *
 * **************************************************************************/

#ifndef _HEAD_H_
#define _HEAD_H_

#define ALARMNUM 32
//ACK RST TEST MEM MOV ADD ENT
#define KEYNUM 7   
#define INPUTNUM (ALARMNUM+KEYNUM)
#define SIGLEDNUM (ALARMNUM)
#define ALLLEDNUM (SIGLEDNUM+2)

#define CNTTIMES 10
#define ACK     (ALARMNUM)
#define RST     (ALARMNUM+1)
#define TEST    (ALARMNUM+2)
#define MEM     (ALARMNUM+3)
#define MOV     (ALARMNUM+4)
#define ADD     (ALARMNUM+5)
#define ENT     (ALARMNUM+6)
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef struct{
    uint32_t addr;      //
    uint16_t loc;       //数组中的位置
    uint8_t ledloc;     //
} INPUT;

typedef enum{SNORMAL,STEST,SALARM,SACK,SMEM,SSET} STATE;


typedef enum{FALSE,TRUE} BOOLEN; 

typedef enum{PWR,SIG} LEDTYPE;

typedef enum{RED,YELLOW} COLOR;

typedef enum{TWINK,STABLE} LEDSTATE;

typedef int  STATUS;

#define OK (0)
#define ERROR (-1)

typedef struct{
    LEDTYPE type;   //led类型，信号还是电源
    BOOLEN light;   //是否发光
    COLOR color;    //灯的颜色
    LEDSTATE ledstate;  //是否闪烁
    uint8_t location;   //??
} LED;

void ledInit(void);

STATUS setColor(uint8_t locat,COLOR col);

STATUS setLedState(uint8_t locat,LEDSTATE st);

STATUS setColorAll(COLOR col);

STATUS setLedStateAll(LEDSTATE st);

STATUS turnOn(uint8_t locat);

STATUS turnOff(uint8_t locat);

STATUS turnOnAll(void);

STATUS turnOffAll(void);

STATUS setState(void);

void show(void);

extern uint8_t gInputFlag[];
extern STATE gState;
extern INPUT gInput[];
#endif
