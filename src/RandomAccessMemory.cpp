/**
* @file RandomAccessMemory.cpp
* @brief Memory class declaration
* @author Jairo Ortega Calderon
* @date 20/09/19
**/

#include "../include/RandomAccessMemory.h"


RandomAccessMemory::RandomAccessMemory()
{
}

int RandomAccessMemory::read_write_Mem(bool pRD, bool pWR, int pdirection, int pdata)
{
    if (pRD)
        return this->chunk[pdirection];
    else if (pWR)
        this->chunk[pdirection] = pdata;
    return 0;
}
