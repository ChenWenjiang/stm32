#include <iostream>
#include <string>

using namespace std;

unsigned int output1;
unsigned int output2;


void conv(unsigned int out,unsigned int color){
    int i = 0;
    output1 = 0;
    output2 = 0;
    for(i=0;i<16;i++){
        if(out&(1<<i)){
            if(color&(1<<i))
                output1 += (2<<(i<<1));
            else
                output1 += (1<<(i<<1));
        }
    }
    for(i=0;i<16;i++){
        if(out&(1<<(i+16))){
            if(color&(1<<(i+16)))
                output2 += (2<<(i<<1));
            else
                output2 += (1<<(i<<1));
        }
    }
}
int main(void){
    unsigned int gLight = 0xffffffff;
    unsigned int gColor = 0xffffffff;
    conv(gLight,gColor);
    cout <<hex <<  output1 << endl;
    cout <<hex <<  output2 << endl;
    gColor = 0;
    conv(gLight,gColor);
    cout <<hex <<  output1 << endl;
    cout <<hex <<  output2 << endl;
    gColor = 0xffff;
    conv(gLight,gColor);
    cout <<hex <<  output1 << endl;
    cout <<hex <<  output2 << endl;
    return 0;
}
