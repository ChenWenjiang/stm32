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





typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

typedef struct
{
    uint16_t addr;
    uint16_t val;
    uint16_t len;
    uint16_t mod;
}modreg_t;

void showBuf(void);
void regsInit(void);
void crc16(uint8_t,uint16_t*);
int address(int);
int okToParse(void);
void parse(void);

#define PUTINTOBUF(Buf,var) (Buf).buf[(Buf).tail++] = (unsigned char)var
#define GETFROMBUF(Buf) ((Buf).buf[(Buf).head++])
#define CLEARBUF(Buf)   (Buf).tail = 0; (Buf).head = 0



#endif

