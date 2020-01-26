/**
* @file CacheMemory.cpp
* @brief Cache memory source
* @author Jairo Ortega Calderon
* @date 20/09/19
**/

#include "../include/CacheController.h"

CacheController::CacheController(InterconnectionNetwork *&_intNetw, int _x, int _y)
{
    this->cache = new CacheMemory();
    this->msio = new StateMachineMSIO();
    this->pu_coordinate.x = _x;
    this->pu_coordinate.y = _y;
    this->flagRead = false;
    this->flagWrite = false;
    this->data = 0;
    this->AMAT = 0;
    this->states = new cache_line_state[DEFAULT_BlOCKS];
    for (int iterator = 0; iterator < DEFAULT_BlOCKS; iterator++)
    {
        this->states[iterator].tag = 0;
        this->states[iterator].state = invalid;
    }
    this->intNetw = _intNetw;
    this->event.cacheDir = pu_coordinate;
    this->dataToMem.cacheDir = pu_coordinate;
}

dataMem CacheController::readData(int _address, int _priority)
{
    dataMem memoryInfo;
    dprintf("Read_data-> x: %d, y: %d.", this->pu_coordinate.x, this->pu_coordinate.y);
    if (this->states[(_address % DEFAULT_BlOCKS)].tag == _address)
    {
        if (this->states[(_address % DEFAULT_BlOCKS)].state != invalid)
        { // read hit
            memoryInfo.data = this->cache->read(_address % DEFAULT_BlOCKS);
            memoryInfo.AMAT = 1;
            return memoryInfo;
        }
        else
        {
            sendEvent(_address, false, "miss", _priority); //place RM
            this->states[(_address % DEFAULT_BlOCKS)].tag = _address;
            this->states[(_address % DEFAULT_BlOCKS)].state = this->msio->getState(readMissCPU, this->states[(_address % DEFAULT_BlOCKS)].state);
            while (!(getFlagRead()))
            {
            }
            setFlagRead(false);
            this->cache->write((_address % DEFAULT_BlOCKS), _address, data);
            memoryInfo.data = data;
            memoryInfo.AMAT = AMAT + 1;
            return memoryInfo;
        }
    }
    else
    {
        if ((this->states[(_address % DEFAULT_BlOCKS)].state == invalid) ||
            (this->states[(_address % DEFAULT_BlOCKS)].state == shared))
        {
            sendEvent(_address, false, "miss", _priority); //place RM
        }
        else
        {
            this->dataToMem.data = this->cache->read(_address % DEFAULT_BlOCKS);
            this->dataToMem.addr = this->cache->readTag(_address % DEFAULT_BlOCKS);
            this->dataToMem.priority = _priority;
            this->dataToMem.type = true;
            this->intNetw->pushDataMem(dataToMem);         //WB
            sendEvent(_address, false, "miss", _priority); //place RM
        }
        while (!(getFlagRead()))
        {
        }
        setFlagRead(false);
        this->cache->write((_address % DEFAULT_BlOCKS), _address, data);
        memoryInfo.data = data;
        memoryInfo.AMAT = AMAT + 1;
        this->states[(_address % DEFAULT_BlOCKS)].tag = _address;
        this->states[(_address % DEFAULT_BlOCKS)].state =
            this->msio->getState(readMissCPU, this->states[(_address % DEFAULT_BlOCKS)].state);
        return memoryInfo;
    }
}

dataMem CacheController::writeData(int _address, int _data, int _priority)
{
    dataMem memoryInfo;
    dprintf("Write_data-> x: %d, y: %d.", this->pu_coordinate.x, this->pu_coordinate.y);
    if (this->states[(_address % DEFAULT_BlOCKS)].tag == _address)
    {
        if (this->states[(_address % DEFAULT_BlOCKS)].state == modified)
        {
            this->cache->write((_address % DEFAULT_BlOCKS), _address, _data);
        }
        else
        {
            this->cache->write((_address % DEFAULT_BlOCKS), _address, _data);
            sendEvent(_address, true, "invalidate", _priority);
            while (!(getFlagWrite()))
            {
            }
            setFlagWrite(false);
        }
        this->states[(_address % DEFAULT_BlOCKS)].tag = _address;
        this->states[(_address % DEFAULT_BlOCKS)].state =
            this->msio->getState(writeHitCPU, this->states[(_address % DEFAULT_BlOCKS)].state);
        memoryInfo.data = 0;
        memoryInfo.AMAT = 1;
        return memoryInfo;
    }
    else
    {
        if ((this->states[(_address % DEFAULT_BlOCKS)].state == invalid) ||
            (this->states[(_address % DEFAULT_BlOCKS)].state == shared))
        {
            this->cache->write((_address % DEFAULT_BlOCKS), _address, _data);
            this->states[(_address % DEFAULT_BlOCKS)].tag = _address;
            this->states[(_address % DEFAULT_BlOCKS)].state =
                this->msio->getState(writeMissCPU, this->states[(_address % DEFAULT_BlOCKS)].state);
            sendEvent(_address, true, "miss", _priority);
            while (!(getFlagWrite()))
            {
            }
            setFlagWrite(false);
            memoryInfo.data = 0;
            memoryInfo.AMAT = AMAT + 1;
            return memoryInfo;
        }
        else
        {
            this->dataToMem.data = this->cache->read(_address % DEFAULT_BlOCKS);
            this->dataToMem.addr = this->cache->readTag(_address % DEFAULT_BlOCKS);
            ;
            this->dataToMem.priority = _priority;
            this->dataToMem.type = true;
            this->intNetw->pushDataMem(dataToMem); //WB
            if (this->states[(_address % DEFAULT_BlOCKS)].state == owned)
                sendEvent(_address, true, "invalidate", _priority); // Invalidate owner
            else
                sendEvent(_address, true, "miss", _priority);
            while (!(getFlagWrite()))
            {
            }
            setFlagWrite(false);
            this->states[(_address % DEFAULT_BlOCKS)].tag = _address;
            this->states[(_address % DEFAULT_BlOCKS)].state =
                this->msio->getState(writeMissCPU, this->states[(_address % DEFAULT_BlOCKS)].state);
            memoryInfo.data = 0;
            memoryInfo.AMAT = 1;
            return memoryInfo;
        }
    }
}

int CacheController::readDataEvent(msgEvent _event)
{
    dprintf("Read_data_bus-> x: %d, y: %d.", this->pu_coordinate.x, this->pu_coordinate.y);
    if (this->states[(_event.tag % DEFAULT_BlOCKS)].tag == _event.tag)
    {
        if (this->states[(_event.tag % DEFAULT_BlOCKS)].state == modified)
        {
            this->states[(_event.tag % DEFAULT_BlOCKS)].state =
                this->msio->getState(readMissBUS, this->states[(_event.tag % DEFAULT_BlOCKS)].state);
            return this->cache->read(_event.tag % DEFAULT_BlOCKS);
        }
        else if (this->states[(_event.tag % DEFAULT_BlOCKS)].state == owned)
        {
            return this->cache->read(_event.tag % DEFAULT_BlOCKS);
        }
        else
            return -1;
    }
    else
    {
        return -1;
    }
}

void CacheController::writeDataEvent(msgEvent _event)
{
    dprintf("Write_data_bus-> x: %d, y: %d.", this->pu_coordinate.x, this->pu_coordinate.y);
    if (this->states[(_event.tag % DEFAULT_BlOCKS)].tag == _event.tag)
    {
        if (_event.action == "invalidate")
        {
            this->states[(_event.tag % DEFAULT_BlOCKS)].state =
                this->msio->getState(invalidateBUS, this->states[(_event.tag % DEFAULT_BlOCKS)].state);
        }
        else
        {
            if (this->states[(_event.tag % DEFAULT_BlOCKS)].state == shared)
            {
                this->states[(_event.tag % DEFAULT_BlOCKS)].state =
                    this->msio->getState(writeMissBUS, this->states[(_event.tag % DEFAULT_BlOCKS)].state);
            }
            else if (this->states[(_event.tag % DEFAULT_BlOCKS)].state == owned)
            {
                this->states[(_event.tag % DEFAULT_BlOCKS)].state =
                    this->msio->getState(writeMissBUS, this->states[(_event.tag % DEFAULT_BlOCKS)].state);
                this->dataToMem.data = this->cache->read((_event.tag % DEFAULT_BlOCKS));
                this->dataToMem.addr = _event.tag;
                this->dataToMem.type = true;
                this->intNetw->pushDataMem(dataToMem); //WB
            }
        }
    }
}

void CacheController::sendEvent(int paddress, bool ptype, std::string paction, int _priority)
{
    this->event.tag = paddress;
    this->event.type = ptype;
    this->event.action = paction;
    this->event.priority = _priority;
    this->intNetw->pushEvent(event);
}

void CacheController::setFlagRead(bool _flagRead)
{
    this->flagRead = _flagRead;
}
bool CacheController::getFlagRead()
{
    return this->flagRead;
}
void CacheController::setFlagWrite(bool _flagWrite)
{
    this->flagWrite = _flagWrite;
}
bool CacheController::getFlagWrite()
{
    return this->flagWrite;
}