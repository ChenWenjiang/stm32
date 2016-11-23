#include "reg.h"

extern modreg_t regs[74];
void regHashTableInit(void)
{
    int i;
    //bus addr
    regs[0].addr = 0;
    regs[0].val = 0;//
    regs[0].len = 2;
    regs[0].mod = 2;

    //baudrate
    regs[1].addr = 1;
    regs[1].val = 2;
    regs[1].len = 2;
    regs[1].mod = 2;

    //verification
    regs[2].addr = 2;
    regs[2].val = 0;
    regs[2].len = 2;
    regs[2].mod = 2;

    //global alarm
    regs[3].addr = 0x0010;
    regs[3].val = 0;
    regs[3].len = 2;
    regs[3].mod = 0;

    //pre alarm
    regs[4].addr = 0x0011;
    regs[4].val = 0;
    regs[4].len = 2;
    regs[4].mod = 0;

    //input
    regs[5].addr = 0x0100;
    regs[5].val = 0;
    regs[5].len = 4;
    regs[5].mod = 0;

    //input state
    for(i=0;i<32;i++)
    {
        regs[6+i].addr = 0x0101+i;
        regs[6+i].val = 0;
        regs[6+i].len = 2;
        regs[6+i].mod = 0;
    }

    //output
    regs[38].addr = 0x0200;
    regs[38].val = 0;
    regs[38].len = 4;
    regs[38].mod = 0;

    //output state
    for(i=0;i<32;i++)
    {
        regs[39+i].addr = 0x0201+i;
        regs[39+i].val = 0;
        regs[39+i].len = 2;
        regs[39+i].mod = 0;
    }

    //ack
    regs[71].addr = 0x01000;
    regs[71].val = 0;
    regs[71].len = 2;
    regs[71].mod = 2;
    //rst
    regs[72].addr = 0x01001;
    regs[72].val = 0;
    regs[72].len = 2;
    regs[72].mod = 2;
    ///test
    regs[73].addr = 0x01002;
    regs[73].val = 0;
    regs[73].len = 2;
    regs[73].mod = 2;

}
