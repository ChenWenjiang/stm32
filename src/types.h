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
    uint16_t addr;
    uint16_t val;
    uint16_t mod; //0:ro 1:wo 2:rw
} modreg_t;

typedef struct {
    uint8_t alarm_loc;
    uint8_t alarm_color;
} alarm_history_t;
#endif

