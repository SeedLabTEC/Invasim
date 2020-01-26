#ifndef INCLUDE_CACHEMEMORY_H_
#define INCLUDE_CACHEMEMORY_H_

#define DEFAULT_BlOCKS 64

#include "Utils.h"

/**
 * @brief Struct cache line representation
 */
struct cache_line
{
	int tag;
	int data;
};

/**
* @file CacheMemory.h
* @brief Cache memory class declaration
* @author Jairo Ortega Calderon
* @date 20/09/19
**/
class CacheMemory{
	private:
		cache_line *blocks;
	public:
		/**
		 * @brief Construct a new Cache Memory object
		 */
		CacheMemory();
		/**
		 * @brief Write on cache
		 * @param _index Line in the cache
		 * @param _addr Address of data
		 * @param _data Data
		 */
		void write(int _index, int _addr, int _data);
		/**
		 * @brief Read from cache
		 * @param _index Line of cache
		 * @return int value of line
		 */
		int read(int _index);
		/**
		 * @brief Read the tag of the line
		 * @param _index Line in the cache
		 * @return int value of line (tag)
		 */
		int readTag(int _index);
};

#endif