# include "../include/InterconnectionNetwork.h"

InterconnectionNetwork::InterconnectionNetwork(){
    this->mem0 = new Memory();
    this->mem1 = new Memory();
    this->mem2 = new Memory();
    this->mem3 = new Memory();
}

int InterconnectionNetwork::read_write(bool pRD, bool pWR, int pdirection, int pdata){
    int result;
    switch (pdirection){
        case 0 ... 255:
            result=this->mem0->read_write_Mem(pRD, pWR, pdirection, pdata);
            break;
        case 256 ... 511:
            result=this->mem1->read_write_Mem(pRD, pWR, pdirection, pdata);
            break;
        case 512 ... 767:
            result=this->mem2->read_write_Mem(pRD, pWR, pdirection, pdata);
            break;
        case 768 ... 1023:
            result=this->mem3->read_write_Mem(pRD, pWR, pdirection, pdata);
            break;
        default:
            result=0;
            break;
    }
    return result;
}

void InterconnectionNetwork::pushEvent(msgEvent newMsgEvent){
    eventsCache.push(newMsgEvent);
}

msgEvent InterconnectionNetwork::popEvent(){
    msgEvent tmpEvent = eventsCache.front();
    this->eventsCache.pop();
    return tmpEvent;
}


void InterconnectionNetwork::pushDataMem(msgMem newMsgMem){
    this->accessMem.push(newMsgMem);
}