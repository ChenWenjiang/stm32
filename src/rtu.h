#ifndef _RTU_H_
#define _RTU_H_

#include "types.h"
#include "globalvar.h"

//void showBuf(void);
void regsInit(uint8_t,uint8_t,uint8_t);
void crc16(uint8_t,uint16_t*);
int address(uint16_t);

void exceptAns(uint8_t func,uint8_t exCode);
int okToParse(void);
void parse(void);
void new_config_from_rtu(void);

#define PUTINTOBUF(Buf,var) (Buf).buf[(Buf).tail++] = (unsigned char)var
#define GETFROMBUF(Buf) ((Buf).buf[(Buf).head++])
#define CLEARBUF(Buf) (Buf).tail = 0;(Buf).head = 0

#endif
