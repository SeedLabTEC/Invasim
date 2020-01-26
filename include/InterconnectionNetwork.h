#ifndef INCLUDE_INTERCONNECTIONNETWORK_H_
#define INCLUDE_INTERCONNECTIONNETWORK_H_

#include "Memory.h"
#include <queue> 
#include "Utils.h"

class InterconnectionNetwork
{
private:
    Memory* mem0, *mem1, *mem2, *mem3;
    std::queue <msgEvent> eventsCache; 
    std::queue <msgMem> accessMem;
public:
    InterconnectionNetwork();
    int read_write(bool pRD, bool pWR, int pdirection, int pdata);
    void pushEvent(msgEvent newMsgEvent);
    msgEvent popEvent();
    void pushDataMem(msgMem newMsgMem);
    
};

#endif