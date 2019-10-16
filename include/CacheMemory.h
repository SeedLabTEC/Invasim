/**
* @file CacheMemory.h
* @brief Cache memory class declaration
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

/**
 * @brief Cache memory representation with a clock and a chunk of memory
 * 
 */
class CacheMemory 
{
	public: 
		CacheMemory(int _x, int _y);

		int readData(int address, int priority);
		void writeData(int address, int data, int priority);

	private:
		/**
		 * @brief Coordinate of cache
		 * 
		 */
		coordinate pu_coordinate;
		/**
		 * @brief Chunck of memory
		 * 
		 */
		cache_line * blocks;

		/**
		 * @brief Clock instance
		 * 
		 */
		Clock * clk_intance;
};

#endif