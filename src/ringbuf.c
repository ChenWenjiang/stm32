#if defined(__cplusplus)||defined(c_plusplus)
extern "C"{
#endif
#include "ringbuf.h"


void putIntoRingBuf(BUF* pbuf,unsigned char var)
{
    pbuf->buf[pbuf->head] = var;
    if(pbuf->head==255)
        pbuf->head = 0;
    else
        pbuf->head++;
}
unsigned char getFromRingBuf(BUF* pbuf)
{
    unsigned char tmp = pbuf->buf[pbuf->tail];
    if(pbuf->tail == 255)
        pbuf->tail = 0;
    else
        pbuf->tail++;
    return tmp;
}

void ringbufInit(BUF* pbuf)
{
    pbuf->head = 1;
    pbuf->tail = 0;
}
#if defined(__cplusplus)||defined(c_plusplus)
}
#endif
