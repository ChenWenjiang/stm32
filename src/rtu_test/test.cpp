#include <iostream>
#include <algorithm>
#include <iterator>
#include "types.h"
using namespace std;

extern modreg_t regs[74];
extern BUF rxBuf;
extern BUF txBuf;
void showBuf(void)
{
    int i = 0;
    cout << "txBuf: "<<txBuf.head<<" "<<txBuf.tail << endl;
    for(i=txBuf.head;i<txBuf.tail;i++)
        cout <<hex << (int)txBuf.buf[i] << " ";
    cout << endl;
    cout << "rxBuf: "<<rxBuf.head<<" "<<rxBuf.tail << endl;
    for(i=rxBuf.head;i<rxBuf.tail;i++)
        cout<<hex << (int)rxBuf.buf[i] << " ";
    cout << endl;
}
int main(void)
{
    unsigned short crc=0xffff;
    regsInit();
    showBuf();
    int ch;
    while(cin>>ch){
        PUTINTOBUF(rxBuf,ch);
        crc16(ch,&crc);
    }
    PUTINTOBUF(rxBuf,crc&0x0ff);
    PUTINTOBUF(rxBuf,(crc>>8)&0xff);
    showBuf();

    parse();
    showBuf();
    CLEARBUF(txBuf);
    showBuf();

    return 0;
}

