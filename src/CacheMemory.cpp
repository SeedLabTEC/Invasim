/**
* @file CacheMemory.cpp
* @brief Description
* @author Dennis Porras Barrantes
* @date 29/03/19
**/

#include "../include/CacheMemory.h"

/**
* @brief Constructor
**/
CacheMemory::CacheMemory(int _x, int _y)
{
    this->pu_coordinate.x = _x;
    this->pu_coordinate.y = _y;
    this->blocks = NULL;
    this->clk_intance = NULL;
}