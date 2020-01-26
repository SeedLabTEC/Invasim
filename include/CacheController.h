#ifndef INCLUDE_CACHECONTROLLER_H_
#define INCLUDE_CACHECONTROLLER_H_

#include <string>

#include "Utils.h"
#include "CacheMemory.h"
#include "StateMachineMSIO.h"
#include "InterconnectionNetwork.h"

#define DEFAULT_BlOCKS 64

/**
 * @brief Struct that represents a cache's line
 * 
 */
struct cache_line_state
{
    enum States state;
    int tag;
};

/**
 * @brief Declares that class to use it. It is because InterconnectionNetwork also needs CacheController 
 */
class InterconnectionNetwork;

/**
* @file CacheCOntroller.h
* @brief Cache controller class declaration
* @author Jairo Ortega Calderon
* @date 20/09/19
**/
class CacheController{
    private:
        CacheMemory *cache;
        StateMachineMSIO *msio;
        cache_line_state *states;
        InterconnectionNetwork *intNetw;
        msgEvent event;
        msgMem dataToMem;
        bool flagRead;
        bool flagWrite;
        /**
         * @brief Send at event to the interconnection network like write-miss or read-miss.
         * @param paddress Address of the event
         * @param ptype true=write, false=read
         * @param paction kind of action (miss or invalidate)
         * @param _priority Priority of request
         */
        void sendEvent(int paddress, bool ptype, std::string paction, int _priority);

    public:
        coordinate pu_coordinate;
        int AMAT;
        int data;
        /**
         * @brief Construct a new Cache Controller object
         * @param _intNetw pointer to interconnectionNetwork
         * @param _x x position of processor's CC
         * @param _y y position of processor's CC
         */
        CacheController(InterconnectionNetwork *&_intNetw, int _x, int _y);
        /**
         * @brief Request to read data
         * @param _address Address to read
         * @param _priority Priority of request
         * @return dataMem struct with data and AMAT
         */
        dataMem readData(int _address, int _priority);
        /**
         * @brief Request to write data
         * @param _address Memory address to write
         * @param _data Data to write
         * @param _priority Priority of request
         * @return dataMem struct with AMAT (data is 0, don't care for write)
         */
        dataMem writeData(int _address, int _data, int _priority);
        /**
         * @brief IntNet calls this when a read event happens.
         * @param _event Event information
         * @return int -1 for no data or data value
         */
        int readDataEvent(msgEvent _event);
        /**
         * @brief IntNet calls this when a write event happens.
         * @param _event Event information
         */
        void writeDataEvent(msgEvent _event);
        /**
         * @brief Set the Flag Read
         * @param _flagRead 
         */
        void setFlagRead(bool _flagRead);
        /**
         * @brief Get the Flag Read
         * @return true 
         * @return false 
         */
        bool getFlagRead();
        /**
         * @brief Set the Flag write
         * @param _flagWrite 
         */
        void setFlagWrite(bool _flagWrite);
        /**
         * @brief Get the Flag Write object
         * @return true 
         * @return false 
         */
        bool getFlagWrite();
};
#endif
