#ifndef INCLUDE_CACHECONTROLLER_H_
#define INCLUDE_CACHECONTROLLER_H_

#include "CacheMemory.h"
#include "ResourceAdmin.h"
#include "InterconnectionNetwork.h"
#include "StateMachineMSI.h"
#include "Utils.h"
#include <string>

#define DEFAULT_BlOCKS 64

struct cache_line_state{
    enum States state;
    int tag;
};


class CacheController
{
    private:
		/**
		 * @brief Coordinate of cache
		 * 
		 */
		coordinate pu_coordinate;
        CacheMemory * cache;
        ResourceAdmin * admin;
        InterconnectionNetwork * intNetw;
        StateMachineMSI * msi;
        cache_line_state * states;
        bool flagRead;
        int data;
        msgEvent event;
        msgMem dataToMem;

    public:
        CacheController(ResourceAdmin * _admin, InterconnectionNetwork * _intNetw, int _x, int _y);
        int getData(int _addr);
        enum States getBlocksState(int _ind);
        int readData(int _address);
        int readDataAux();
        void sendEvent(int paddress, bool ptype, std::string paction);
        void writeData(int _address, int _data);
        int readDataEvent(event _event);
        void writeDataEvent(event _event);

};
#endif
