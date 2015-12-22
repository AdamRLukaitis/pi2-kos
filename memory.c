#include "memory.h"
#include "io.h"

void memmove(unsigned int src, unsigned int trg, unsigned int bytes) 
{
    while(bytes) 
    {
        mmio_write(trg+bytes, mmio_read(src+bytes));
        bytes--;
    }
}