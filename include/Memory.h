#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

class Memory
{
private:
    int chunk [256] = {};
public:
    Memory();
    int read_write_Mem(bool pRD, bool pWR, int pdirection, int pdata);
};



#endif