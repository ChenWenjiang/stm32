#ifndef _REG_H_
#define _REG_H_

#include "stm32f10x.h"

typedef struct
{
    uint32_t addr;
    uint32_t val;
    uint32_t len; //bytes
    uint32_t mod; //0:ro 1:wo 2:rw
} modreg_t;


void regHashTableInit(void);
#endif
