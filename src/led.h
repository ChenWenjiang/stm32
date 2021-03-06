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

#include "types.h"

#define ALARMNUM 32
//ACK RST TEST MEM MOV ADD ENT
#define KEYNUM 7   
#define KEYINNUM 4
#define INPUTNUM (ALARMNUM+KEYNUM+KEYINNUM)
#define SIGLEDNUM (ALARMNUM)
#define ALLLEDNUM (SIGLEDNUM+2)

#define ACK     (ALARMNUM)
#define RST     (ALARMNUM+1)
#define TEST    (ALARMNUM+2)
#define MEM     (ALARMNUM+3)
#define MOV     (ALARMNUM+4)
#define ADD     (ALARMNUM+5)
#define ENT     (ALARMNUM+6)

#define ACK_IN  (ALARMNUM+7)
#define RST_IN  (ALARMNUM+8)
#define TEST_IN (ALARMNUM+9)
#define MEM_IN  (ALARMNUM+10)

void ledInit(void);
void inputInit(void);

void setState(void);

STATUS setLed(void);

#endif
