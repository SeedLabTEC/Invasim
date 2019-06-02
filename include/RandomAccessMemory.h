/**
* @file RandomAccessMemory.h
* @brief RAM class declaration.
* @author Dennis Porras Barrantes
* @date 29/03/19
**/

#ifndef INCLUDE_RANDOMACCESSMEMORY_H_
#define INCLUDE_RANDOMACCESSMEMORY_H_

#define DEFAULT_SIZE 16

#include "Clock.h"

#include "Utils.h"

/**
 * @brief Random Access Memory class representation with a clock and chuck of memory.
 * 
 */
class RandomAccessMemory 
{
	public: 
		RandomAccessMemory();

	private:
		int * main_mem;
		Clock * clk_instance;

};

#endif