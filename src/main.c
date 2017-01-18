#include "hw_config.h"
#include "globalvar.h"
#include "led.h"
#include "eeprom.h"
extern uint32_t memColor;


extern uint8_t uart4_data[10];
extern uint8_t inputLock;
extern uint8_t cnt; //整体计数，0～72，用来控制数据信号
extern uint8_t icnt; //内部计数，0～1，用来控制时钟和锁存信号
extern int8_t outputLock;
extern uint32_t output1;
extern uint32_t output2;

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
    uint8_t ch = '0'+gHistoryNum;
    print(&ch,1);
}

int main()
{
//    uint8_t edata[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m',
//    'n','o','p','q','r','s','t','u','v','w','x','y','z'};
//    uint8_t edatain[26];
    uint8_t errchar = '0';
    uint8_t err = 0;
    inputInit();
    HW_Config();
//    err = eeprom_clear_history();
    if(err!=0){
        errchar += err;
        print(&errchar,1);
    }
 //   err = eeprom_load();
    if(err!=0){
        errchar += err;
        print(&errchar,1);
    }
    gColor = 0;
    err = eeprom_store_color();
    if(err!=0){
        errchar += err;
        print(&errchar,1);
    }
    while(1){
        static uint8_t twinkFlag = 0;
        uint32_t out = 0;
        uint32_t color = 0;
//        time3();
        if(outputLock==0){
            twinkFlag++;
            twinkFlag %= 2;
            if(twinkFlag==0){
            /* if(gLight==0)
               gLight = 0x80000000;
               else
               gLight >>=1;*/
        //    if(inputLock==0)
        //        gLight = gButtonInputFlag;//regs[5].val;
            //    gTwink = 0;
                out = gLight;
            }else
                out =gTwink ^ gLight;
            if(gState==SMEM)
                color = memColor;
            else
                color = gColor;
            conv(out,color);
            cnt = 0;
            icnt = 1;
            outputLock = 1;
        }
 //       err = Write(0xa0,0,edata,26);
 //       if(0!=err){
 //           errchar +=err;
 //           print(&errchar,1);
 //       }
 //       err = Read(0xa0,0,edatain,26);
 //       
 //       if(0!=err){
 //           errchar +=err;
 //           print(&errchar,1);
 //       }
 //       print(edatain,26);
        setState();
        printHistoryNum();
    //    setState();
    //    uint8_t t = Single_Read(0xa0,0,uart4_data);
    //    static uint8_t i = 0;
    //    if(0==t){
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'r');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'s');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'0'+t);
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,uart4_data[0]);
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'\n');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'\r');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET);
    //    }else{
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'r');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'f');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'0'+t);
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'\n');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'\r');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET);
    //    }
    //    t = Single_Write(0xa0,0,'a'+(i++));
    //    if(i==26)
    //        i = 0;
    //    if(0==t){
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'w');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'s');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'0'+t);
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'\n');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'\r');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET);
    //    }else{
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'w');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'f');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'0'+t);
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'\n');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
    //        USART_SendData(UART4,'\r');
    //        while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET);
    //    }
        //while(j++<10000000);
    }

    return 0;
}
