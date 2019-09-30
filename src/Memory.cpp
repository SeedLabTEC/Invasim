#include "../include/Memory.h"



Memory::Memory(){
}

int Memory::read_write_Mem(bool pRD, bool pWR, int pdirection, int pdata)
{
    if (pRD)
        return this->chunk[pdirection];
    else if (pWR)
        this->chunk[pdirection] = pdata;
    return 0;    
}