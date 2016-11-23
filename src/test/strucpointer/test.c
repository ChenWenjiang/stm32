#include <stdio.h>

typedef struct 
{
    unsigned int low;
    unsigned int high;
} uint64_t;


int main(void)
{
    uint64_t tmp;
    printf("%p,%p\n",&(tmp.low),&(tmp.high));
    return 0;
}
