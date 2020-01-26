/**
* @file CacheMemory.h
* @brief Cache memory class declaration
* @author Jairo Ortega Calderon
* @date 20/09/19
**/

#ifndef INCLUDE_CACHEMEMORY_H_
#define INCLUDE_CACHEMEMORY_H_

#define DEFAULT_BlOCKS 64

#include "Clock.h"
#include "Utils.h"

/**
 * @brief Struct cache line representation
 */
struct cache_line{
	int tag;
	int data;
};



/**
 * @brief Cache memory representation with a clock and a chunk of memory
 * 
 */
class CacheMemory 
{
	public: 
		CacheMemory();
		void write (int _index, int _addr, int _data);
		int read(int _index);

	private:
		/**
		 * @brief Chunck of memory
		 * 
		 */ 
		cache_line * blocks;
};

#endif