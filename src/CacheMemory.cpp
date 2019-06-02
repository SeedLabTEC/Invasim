/**
* @file CacheMemory.cpp
* @brief Cache memory source
* @author Dennis Porras Barrantes
* @date 29/03/19
**/

#include "../include/CacheMemory.h"

/**
 * @brief Construct a new Cache Memory:: Cache Memory object
 * 
 * @param _x dimension
 * @param _y dimension
 */
CacheMemory::CacheMemory(int _x, int _y)
{
    this->pu_coordinate.x = _x;
    this->pu_coordinate.y = _y;
    this->blocks = NULL;
    this->clk_intance = NULL;
}