/**
* @file CacheMemory.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 29/03/19
**/

#ifndef INCLUDE_CACHEMEMORY_H_
#define INCLUDE_CACHEMEMORY_H_

#define DEFAULT_BlOCKS 32

#include "Clock.h"

/**
 * @brief Struct cache line representation
 */
struct cache_line 
{
	int data;
	bool valid;
};

#include "Utils.h"

class CacheMemory 
{
	public: 
		CacheMemory(int _x, int _y);

	private:
		coordinate pu_coordinate;
		cache_line * blocks;

		Clock * clk_intance;
};

#endif