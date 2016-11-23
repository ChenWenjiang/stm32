#ifndef _TYPES_H_
#define _TYPES_H_

typedef enum{FALSE,TRUE} BOOLEN;

#define OK (0)
#define ERROR (-1)
#define I2C_ADDRACKERR  (-2)
#define I2C_DATAACKERR  (-2)

typedef int STATUS;

typedef enum{SNORMAL,STEST,SALARM,SACK,SMEM,SSET} STATE;

typedef struct{
    int tail;
    int head;
    unsigned char buf[256];
}BUF;

#endif

