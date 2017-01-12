#include "print.h"
int print(uint8_t* string,int length){
    uint32_t i = 0;
    while(string[i] !='\0' && i<=length){
        while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
        USART_SendData(USART3,string[i]);
        i++;
    }
    return i;
}
