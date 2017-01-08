#if defined(__cplusplus)||defined(c_plusplus)
extern "C"{
#endif
#include "stm32f10x.h"
#include "types.h"
#include "input.h"
void inputInit(void)
{
    uint8_t i=0;
    gInput[0].addr = GPIOA;
    gInput[0].loc = GPIO_Pin_0;
    gInput[0].ledloc = 0;

    gInput[1].addr = GPIOA;
    gInput[1].loc = GPIO_Pin_0;
    gInput[1].ledloc = 1;
    
    gInput[2].addr = GPIOA;
    gInput[2].loc = GPIO_Pin_0;
    gInput[2].ledloc = 2;
    
    gInput[3].addr = GPIOA;
    gInput[3].loc = GPIO_Pin_0;
    gInput[3].ledloc = 3;
    
    gInput[4].addr = GPIOA;
    gInput[4].loc = GPIO_Pin_0;
    gInput[4].ledloc = 4;
    
    gInput[5].addr = GPIOA;
    gInput[5].loc = GPIO_Pin_0;
    gInput[5].ledloc = 5;
    
    gInput[6].addr = GPIOA;
    gInput[6].loc = GPIO_Pin_0;
    gInput[6].ledloc = 6;
    
    gInput[7].addr = GPIOA;
    gInput[7].loc = GPIO_Pin_0;
    gInput[7].ledloc = 7;
    
    gInput[8].addr = GPIOA;
    gInput[8].loc = GPIO_Pin_0;
    gInput[8].ledloc = 8;
    
    gInput[9].addr = GPIOA;
    gInput[9].loc = GPIO_Pin_0;
    gInput[9].ledloc = 9;
    
    gInput[10].addr = GPIOA;
    gInput[10].loc = GPIO_Pin_0;
    gInput[10].ledloc = 10;
    
    gInput[11].addr = GPIOA;
    gInput[11].loc = GPIO_Pin_0;
    gInput[11].ledloc = 11;
    
    gInput[12].addr = GPIOA;
    gInput[12].loc = GPIO_Pin_0;
    gInput[12].ledloc = 12;
    
    gInput[13].addr = GPIOA;
    gInput[13].loc = GPIO_Pin_0;
    gInput[13].ledloc = 13;
    
    gInput[14].addr = GPIOA;
    gInput[14].loc = GPIO_Pin_0;
    gInput[14].ledloc = 14;
    
    gInput[15].addr = GPIOA;
    gInput[15].loc = GPIO_Pin_0;
    gInput[15].ledloc = 15;
    
    gInput[16].addr = GPIOA;
    gInput[16].loc = GPIO_Pin_0;
    gInput[16].ledloc = 16;
    
    gInput[17].addr = GPIOA;
    gInput[17].loc = GPIO_Pin_0;
    gInput[17].ledloc = 17;
    
    gInput[18].addr = GPIOA;
    gInput[18].loc = GPIO_Pin_0;
    gInput[18].ledloc = 18;
    
    gInput[19].addr = GPIOA;
    gInput[19].loc = GPIO_Pin_0;
    gInput[19].ledloc = 19;
    
    gInput[20].addr = GPIOA;
    gInput[20].loc = GPIO_Pin_0;
    gInput[20].ledloc = 20;
    
    gInput[21].addr = GPIOA;
    gInput[21].loc = GPIO_Pin_0;
    gInput[21].ledloc = 21;
    
    gInput[22].addr = GPIOA;
    gInput[22].loc = GPIO_Pin_0;
    gInput[22].ledloc = 22;
    
    gInput[23].addr = GPIOA;
    gInput[23].loc = GPIO_Pin_0;
    gInput[23].ledloc = 23;
    
    gInput[24].addr = GPIOA;
    gInput[24].loc = GPIO_Pin_0;
    gInput[24].ledloc = 24;
    
    gInput[25].addr = GPIOA;
    gInput[25].loc = GPIO_Pin_0;
    gInput[25].ledloc = 25;
    
    gInput[26].addr = GPIOA;
    gInput[26].loc = GPIO_Pin_0;
    gInput[26].ledloc = 26;
    
    gInput[27].addr = GPIOA;
    gInput[27].loc = GPIO_Pin_0;
    gInput[27].ledloc = 27;
    
    gInput[28].addr = GPIOA;
    gInput[28].loc = GPIO_Pin_0;
    gInput[28].ledloc = 28;
    
    gInput[29].addr = GPIOA;
    gInput[29].loc = GPIO_Pin_0;
    gInput[29].ledloc = 29;
    
    gInput[30].addr = GPIOA;
    gInput[30].loc = GPIO_Pin_0;
    gInput[30].ledloc = 30;
    
    gInput[31].addr = GPIOA;
    gInput[31].loc = GPIO_Pin_0;
    gInput[31].ledloc = 31;
}


#if defined(__cplusplus)||defined(c_plusplus)
}
#endif
