#ifndef _RINGBUF_H_
#define _RINGBUF_H_
#include "types.h"

#define isEmpty(pbuf) (pbuf->head==pbuf->tail)
#define isFull(pbuf) ((pbuf->head==255 && pbuf->tail==0)\
        ||(pbuf->tail==pbuf->head+1))

void putIntoRingBuf(BUF*,unsigned char);
unsigned char getFromRingBuf(BUF* );
void ringbufInit(BUF* pbuf);

#define clearBuf(pbuf) ringbufInit(pbuf)

#endif
