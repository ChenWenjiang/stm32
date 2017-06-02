#include "hw_config.h"
#include "globalvar.h"
#include "led.h"
#include "eeprom.h"
#include "rtu.h"
#include "switch.h"
extern uint32_t memColor;
extern uint32_t testColor;

extern uint8_t uart4_data[10];
extern uint8_t inputLock;
extern uint8_t cnt; //整体计数，0～72，用来控制数据信号
extern uint8_t icnt; //内部计数，0～1，用来控制时钟和锁存信号
extern int8_t outputLock;
extern uint32_t output1;
extern uint32_t output2;
//void timer3(void);
void conv(uint32_t out,uint32_t color){
    int i = 0;
    output1 = 0;
    output2 = 0;
    for(i=0;i<16;i++){//低16位
        if(out&(1<<i)){
            if(color&(1<<i))//red
                output1 +=(1<<(i<<1)); 
            else   //yellow
                output1 +=(2<<(i<<1));
        }
    }
    for(i=0;i<16;i++){//高16位
        if(out&(1<<(i+16))){
            if(color&(1<<(16+i)))//red
                output2 +=(1<<(i<<1));
            else 
                output2 +=(2<<(i<<1));
        }
    }
}

void printHistoryNum(void){
    uint8_t ch[3] = {0}; 
    ch[0]=  '0'+gHistoryNum/100;
    ch[1] = '0'+(gHistoryNum/10)%10;
    ch[2] = '0'+gHistoryNum%10;
    print(ch,3);
    ch[0] = '\n';
    ch[1] = '\r';
    print(ch,2);
}
int main()
{
//    uint8_t errchar = '0';
//    uint8_t err = 0;
    inputInit();

    HW_Config();
    RS485_RX_ENABLE;
//    err = eeprom_store_modbusaddr(0xc);
//    err = eeprom_clear_history();
//    if(err!=0){
//        errchar += err;
//        print(&errchar,1);
//    }
//    err = eeprom_load();
//    if(err!=0){
//        errchar += err;
//        print(&errchar,1);
//    }
//    gColor = 0x00000000;
//    err = eeprom_store_color();
//    if(err!=0){
//        errchar += err;
//        print(&errchar,1);
//    }
    while(1){
        static uint8_t twinkFlag = 0;
        uint32_t out = 0;
        uint32_t color = 0;
        if(outputLock==0){
            twinkFlag++;
            twinkFlag %= 2;
            if(twinkFlag==0){
                out = gLight;
            }else{
                out =gTwink ^ gLight;
            }
            if(gState==SMEM){
                color = memColor;
            }else if(gState==STEST){
              color = testColor;
            }else{
              color = gColor;
            }
            conv(out,color);
            cnt = 0;
            icnt = 1;
            outputLock = 1;
        }
        setState();
        //arg = Read_Set_Arg_Switch();  
        //if(arg&2){
        //  regs[1].val = 2;
        //  regs[2].val = 2;
        //}
        new_config_from_rtu();
    }
    return 0;
}
