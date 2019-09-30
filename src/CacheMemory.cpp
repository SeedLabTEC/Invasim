/**
* @file CacheMemory.cpp
* @brief Cache memory source
* @author Jairo Ortega Calderon
* @date 20/09/19
**/

#include "../include/CacheMemory.h"


/**
 * @brief Construct a new Cache Memory:: Cache Memory object
 * 
 * @param _x dimension
 * @param _y dimension
 */
CacheMemory::CacheMemory(){
    this->blocks = new cache_line [DEFAULT_BlOCKS];
    for(int x = 0; x < DEFAULT_BlOCKS; x++){
        this->blocks[x].tag = 0;
        this->blocks[x].data = 0; 

    }
}


void CacheMemory::write(int _index, int _addr, int _data){
    this->blocks[_index].tag = _addr;
    this->blocks[_index].data = _data; 

}

int CacheMemory::read (int _index){
    return this->blocks[_index].data;
}