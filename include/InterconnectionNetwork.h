#ifndef INCLUDE_INTERCONNECTIONNETWORK_H_
#define INCLUDE_INTERCONNECTIONNETWORK_H_

#include <queue>
#include <list>
#include <unistd.h>

#include "Utils.h"
#include "CacheController.h"
#include "RandomAccessMemory.h"

#include "json.hpp"
using JSON = nlohmann::json;

/**
 * @brief Declares that class to use it. It is because CacheController also needs InterconnectionNetwork 
 */
class CacheController;

/**
* @file InterconnectionNetwork.h
* @brief Interconnection network class declaration
* @author Jairo Ortega Calderon
* @date 20/09/19
**/
class InterconnectionNetwork
{
    private:
        RandomAccessMemory *mem0, *mem1, *mem2, *mem3;
        std::queue<msgEvent> eventsCache;
        std::queue<msgMem> priority5;
        std::queue<msgMem> priority4;
        std::queue<msgMem> priority3;
        std::queue<msgMem> priority2;
        std::queue<msgMem> priority1;
        std::list<CacheController *> caches;
        bool runEvent, runRequest, stopEvent, stopRequest; 

    public:
        /**
         * @brief Construct a new Interconnection Network object
         */
        InterconnectionNetwork();
        /**
         * @brief Retrieve information for the gui
         * @return JSON Information
         */
        JSON monitoring();
        /**
         * @brief Insert a cache controller object to communicate with it.
         * @param _cc Cache controller
         */
        void insertCC(CacheController*& _cc);
        /**
         * @brief Write on memory or read from it
         * @param pRD Flag for read
         * @param pWR Flag for write
         * @param pdirection Address
         * @param pdata Data to write
         * @return dataMem Struct with data and AMAT
         */
        dataMem read_write(bool pRD, bool pWR, int pdirection, int pdata);
        /**
         * @brief Push an event in the queue
         * @param newMsgEvent Event
         */
        void pushEvent(msgEvent newMsgEvent);
        /**
         * @brief Push a request for the memory
         * @param newMsgMem information
         */
        void pushDataMem(msgMem newMsgMem);
        /**
         * @brief Pop a message to access in the memory
         * @return msgEvent event
         */
        msgEvent popMsgMem();
        /**
         * @brief Consume a request for the memory
         * @return void* Never returns, only is for the thread
         */
        void * consumeRequest();
        /**
         * @brief Consume a request for an event
         * @return void* Never returns, only is for the thread
         */
        void * consumeEvent();
        /**
         * @brief Returns which CC made the request
         * @param requester x and y position
         * @return CacheController* CC pointer to the specific x and y processor
         */
        CacheController *returnRequester(coordinate requester);
        /**
         * @brief Set the Run Events
         * @param _runEvent 
         */
        void setRunEvents(bool _runEvent);
        /**
         * @brief Set the Run Requests
         * @param _runRequest 
         */
        void setRunRequests(bool _runRequest);
};

#endif