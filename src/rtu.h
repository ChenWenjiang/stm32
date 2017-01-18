#ifndef _RTU_H_
#define _RTU_H_

#include "reg.h"
#include "types.h"
#include "globalvar.h"

#define PUTINTOBUF(Buf,var) Buf.buf[Buf.tail++] = var
#define GETFROMBUF(Buf) (Buf.buf[BUf.head++])
#define CLEARBUF(Buf)   Buf.tail = 0; Buf.head = 0

void parse(void);
#endif
