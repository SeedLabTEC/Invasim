/**
* @file CacheMemory.cpp
* @brief Cache memory source
* @author Jairo Ortega Calderon
* @date 20/09/19
**/

#include "../include/CacheController.h"


CacheController::CacheController(ResourceAdmin * _admin, InterconnectionNetwork * _intNetw,  int _x, int _y)
{
    this->admin = _admin;
    this->intNetw = _intNetw;
    this->pu_coordinate.x = _x;
    this->pu_coordinate.y = _y;
    this->cache = new CacheMemory();
    this->msi = new StateMachineMSI();
    this->flagRead = false;
    this->data = 0;
    this->states = new cache_line_state [DEFAULT_BlOCKS];
    for(int x = 0; x < DEFAULT_BlOCKS; x++){
        this->states[x].tag = 0;
        this->states[x].state = invalid; 

    }
    this->event.cacheDir=pu_coordinate;
}

int CacheController::getData(int _addr){
    return 0;
}

enum States CacheController::getBlocksState(int _ind){
    return this->msi[_ind].getActualState();
}

int CacheController::readData(int _address){
    if(this->states[(_address % DEFAULT_BlOCKS)].tag == _address){
        if(this->states[(_address % DEFAULT_BlOCKS)].state != invalid) // read hit
            return this->cache->read(_address % DEFAULT_BlOCKS);
        else{
            endEvent(_address, false, "miss"); //place RM
            this->states[(_address % DEFAULT_BlOCKS)].tag=_address;
            this->states[(_address % DEFAULT_BlOCKS)].state=this->msi->getState(readMissCPU, this->states[(_address % DEFAULT_BlOCKS)].state);
            return this->readDataAux();                        
        }
    }
    else{
        if((this->states[(_address % DEFAULT_BlOCKS)].state == invalid) || (this->states[(_address % DEFAULT_BlOCKS)].state == shared)){
            sendEvent(_address, false, "miss");//place RM
        }
        else{
            this->dataToMem.data = this->cache->read(_address);
            this->dataToMem.addr = _address;
            this->intNetw->pushDataMem(dataToMem); //WB
            sendEvent(_address, false, "miss"); //place RM
        }
        this->states[(_address % DEFAULT_BlOCKS)].tag=_address;
        this->states[(_address % DEFAULT_BlOCKS)].state=this->msi->getState(readMissCPU, this->states[(_address % DEFAULT_BlOCKS)].state);
        return this->readDataAux();
    }
}

int CacheController::readDataAux(){
    while (!flagRead);
    flagRead = false;
    return data;
}


void CacheController::writeData(int _address, int _data){
    if(this->states[(_address % DEFAULT_BlOCKS)].tag == _address){
        if(this->states[(_address % DEFAULT_BlOCKS)].state == modified){
            this->cache->write((_address % DEFAULT_BlOCKS),_address, _data);
        }
        else{
            sendEvent(_address, true, "invalidate");
            this->cache->write((_address % DEFAULT_BlOCKS),_address, _data);                        
        }
        this->states[(_address % DEFAULT_BlOCKS)].tag = _address;
        this->states[(_address % DEFAULT_BlOCKS)].state = this->msi->getState(writeHitCPU, this->states[(_address % DEFAULT_BlOCKS)].state);
            
    }
    else{
        if((this->states[(_address % DEFAULT_BlOCKS)].state == invalid) || (this->states[(_address % DEFAULT_BlOCKS)].state == shared)){
            this->cache->write((_address % DEFAULT_BlOCKS),_address, _data);
        }
        else{
            this->dataToMem.data = this->cache->read(_address);
            this->dataToMem.addr = _address;
            this->intNetw->pushDataMem(dataToMem); //WB

        }
        sendEvent(_address, true, "miss");
        this->states[(_address % DEFAULT_BlOCKS)].tag =_address;
        this->states[(_address % DEFAULT_BlOCKS)].state = this->msi->getState(writeMissCPU, this->states[(_address % DEFAULT_BlOCKS)].state);
    }
}



void CacheController::sendEvent(int paddress, bool ptype, std::string paction){
    this->event.tag = paddress;
    this->event.type = ptype;
    this->event.action = paction;
    this->intNetw->pushEvent(event);
}