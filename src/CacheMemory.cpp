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
CacheMemory::CacheMemory(int _pu_id)
{
    this->pu_id = _pu_id;
    this->blocks = NULL;
    this->clk_intance = NULL;
}