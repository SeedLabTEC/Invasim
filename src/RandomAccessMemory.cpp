/**
* @file RandomAccessMemory.cpp
* @brief RAM source
* @author Dennis Porras Barrantes
* @date 29/03/19
**/

#include "../include/RandomAccessMemory.h"

/**
 * @brief Construct a new Random Access Memory:: Random Access Memory object
 * 
 */
RandomAccessMemory::RandomAccessMemory()
{
    this->main_mem = NULL;
    this->clk_instance = NULL;
}