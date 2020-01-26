/**
* @file InterconnectionNetwork.cpp
* @brief Interconnection network class declaration
* @author Jairo Ortega Calderon
* @date 20/09/19
**/

#include "../include/InterconnectionNetwork.h"

InterconnectionNetwork::InterconnectionNetwork()
{
    this->mem0 = new RandomAccessMemory();
    this->mem1 = new RandomAccessMemory();
    this->mem2 = new RandomAccessMemory();
    this->mem3 = new RandomAccessMemory();
}

dataMem InterconnectionNetwork::read_write(bool pRD, bool pWR, int pdirection, int pdata)
{
    dataMem memoryInfo;
    int result;
    switch (pdirection)
    {
    case 0 ... 255:
        result = this->mem0->read_write_Mem(pRD, pWR, pdirection, pdata);
        break;
    case 256 ... 511:
        result = this->mem1->read_write_Mem(pRD, pWR, pdirection, pdata);
        break;
    case 512 ... 767:
        result = this->mem2->read_write_Mem(pRD, pWR, pdirection, pdata);
        break;
    case 768 ... 1023:
        result = this->mem3->read_write_Mem(pRD, pWR, pdirection, pdata);
        break;
    default:
        result = 0;
        break;
    }
    memoryInfo.AMAT = 3;
    memoryInfo.data = result;
    return memoryInfo;
}

void InterconnectionNetwork::pushEvent(msgEvent newMsgEvent)
{
    eventsCache.push(newMsgEvent);
}

msgEvent InterconnectionNetwork::popMsgMem()
{
    msgEvent tmpEvent = eventsCache.front();
    this->eventsCache.pop();
    return tmpEvent;
}

void * InterconnectionNetwork::consumeEvent()
{
    msgEvent tmpEvent;
    int tmpResult = -1;
    CacheController *tmpCache;
    msgMem tmpMsg;
    while (true)
    {
        if (!eventsCache.empty())
        {
            tmpEvent = popMsgMem();
            if (tmpEvent.type == true)
            {
                for (std::list<CacheController *>::iterator it = caches.begin(); it != caches.end(); ++it)
                {
                    if(((*it)->pu_coordinate.x !=  tmpEvent.cacheDir.x) || ((*it)->pu_coordinate.y !=  tmpEvent.cacheDir.y))
                        (*it)->writeDataEvent(tmpEvent);
                }
                tmpCache = returnRequester(tmpEvent.cacheDir);
                tmpCache->setFlagWrite(true);
            }
            else
            {
                for (std::list<CacheController *>::iterator it = caches.begin(); it != caches.end(); ++it)
                {
                    if(((*it)->pu_coordinate.x !=  tmpEvent.cacheDir.x) || ((*it)->pu_coordinate.y !=  tmpEvent.cacheDir.y)){
                        tmpResult = (*it)->readDataEvent(tmpEvent);
                        if (tmpResult != -1)
                        {
                            tmpCache = returnRequester(tmpEvent.cacheDir);
                            tmpCache->data = tmpResult;
                            tmpCache->AMAT = 1;
                            tmpCache->setFlagRead(true);
                            break;
                        }
                    }
                }
                if (tmpResult == -1)
                {
                    tmpMsg.addr = tmpEvent.tag;
                    tmpMsg.cacheDir = tmpEvent.cacheDir;
                    tmpMsg.data = 0;
                    tmpMsg.priority = tmpEvent.priority;
                    tmpMsg.type = tmpEvent.type;
                    pushDataMem(tmpMsg);
                }
            }
        }
    }
}

void * InterconnectionNetwork::consumeRequest()
{
    dataMem memoryInfo;
    msgMem tmpMsg;
    CacheController *tmpCache;
    bool flagRead = false;
    while (true)
    {
        if (!priority5.empty())
        {
            tmpMsg = this->priority5.front();
            this->priority5.pop();
            flagRead = true;
        }
        else if (!priority4.empty())
        {
            tmpMsg = this->priority4.front();
            this->priority4.pop();
            flagRead = true;
        }
        else if (!priority3.empty())
        {
            tmpMsg = this->priority3.front();
            this->priority3.pop();
            flagRead = true;
        }
        else if (!priority2.empty())
        {
            tmpMsg = this->priority2.front();
            this->priority2.pop();
            flagRead = true;
        }
        else if (!priority1.empty())
        {
            tmpMsg = this->priority1.front();
            this->priority1.pop();
            flagRead = true;
        }
        if(flagRead){
            if (tmpMsg.type == true){
                tmpCache = returnRequester(tmpMsg.cacheDir);
                memoryInfo = read_write(false, true, tmpMsg.addr, tmpMsg.data);
                tmpCache->data = memoryInfo.data;
                tmpCache->AMAT = memoryInfo.AMAT;
                tmpCache->setFlagWrite(true);
            }
            else{
                memoryInfo = read_write(true, false, tmpMsg.addr, tmpMsg.data);
                tmpCache = returnRequester(tmpMsg.cacheDir);
                tmpCache->data = memoryInfo.data;
                tmpCache->AMAT = memoryInfo.AMAT;
                tmpCache->setFlagRead(true);
            }
            flagRead=false;
        }
    }
}


void InterconnectionNetwork::pushDataMem(msgMem newMsgMem)
{
    switch (newMsgMem.priority)
    {
    case 1:
        this->priority1.push(newMsgMem);
        break;
    case 2:
        this->priority2.push(newMsgMem);
        break;
    case 3:
        this->priority3.push(newMsgMem);
        break;
    case 4:
        this->priority4.push(newMsgMem);
        break;
    case 5:
        this->priority5.push(newMsgMem);
        break;
    default:
        break;
    }
}

CacheController *InterconnectionNetwork::returnRequester(coordinate requester)
{
    CacheController * tempCC;
    for (std::list<CacheController *>::iterator it = caches.begin(); it != caches.end(); ++it)
    {
        if ((requester.x == (*it)->pu_coordinate.x) && (requester.y == (*it)->pu_coordinate.y)){
            tempCC = *&(*it);
            break;
        }
    }
    return tempCC;
    
}
 
void InterconnectionNetwork::insertCC(CacheController*& _cc){
    this->caches.push_back(_cc);

}

JSON InterconnectionNetwork::monitoring()
{
	JSON json_info0;
    JSON json_info1;
    JSON json_info2;
    JSON json_info3;
    JSON tmpjson0;
    JSON tmpjson1;
    JSON tmpjson2;
    JSON tmpjson3;

    JSON array = JSON::array();
    array.push_back(JSON::array());
	for(int i = 0; i<256 ; i++){
        tmpjson0["address"]=i;
        tmpjson0["data"]=this->mem0->read_write_Mem(true, false,i,0);
        json_info0.push_back(tmpjson0);
        tmpjson1["address"]=i;
        tmpjson1["data"]=this->mem1->read_write_Mem(true, false,i,0);
        json_info1.push_back(tmpjson1);
        tmpjson2["address"]=i;
        tmpjson2["data"]=this->mem2->read_write_Mem(true, false,i,0);
        json_info2.push_back(tmpjson2);
        tmpjson3["address"]=i;
        tmpjson3["data"]=this->mem3->read_write_Mem(true, false,i,0);
        json_info3.push_back(tmpjson3);
    }
    array[0]=(json_info0);
    array[1]=(json_info1);
    array[2]=(json_info2);
    array[3]=(json_info3);
	return array;
}

void InterconnectionNetwork::setRunEvents(bool _runEvent){
    this->runEvent = _runEvent;
}

void InterconnectionNetwork::setRunRequests(bool _runRequest){
    this->runRequest = _runRequest;
}