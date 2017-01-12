#ifndef _TYPES_H_
#define _TYPES_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

typedef enum{FALSE,TRUE} BOOLEN;

#define I2C_ADDRACKERR  (-2)
#define I2C_DATAACKERR  (-2)

typedef int STATUS;

typedef enum{SNORMAL,STEST,SALARM,SACK,SMEM,SSET} STATE;

typedef struct{
    int tail;
    int head;
    unsigned char buf[256];
}BUF;

typedef struct{
    GPIO_TypeDef* addr;      // GPIO[ABCDEFG]
    uint16_t loc;       // GPIO_Pin_[1-15]
    uint8_t ledloc;     // offset in regs  
} INPUT;

typedef struct
{
    uint32_t addr;
    uint32_t val;
    uint32_t len; //bytes
    uint32_t mod; //0:ro 1:wo 2:rw
} modreg_t;

#endif

