/**
* @file ProcessingUnit.h
* @brief Processing unit class declaration.
* @author Dennis Porras Barrantes
* @date 11/02/19
**/

#ifndef INCLUDE_PROCESSINGUNIT_H_
#define INCLUDE_PROCESSINGUNIT_H_

#include <pthread.h>
#include "Utils.h"
#include <sstream>
#include "json.hpp"
using JSON = nlohmann::json;

//Components
#include "Clock.h"
#include "ILet.h"
#include "CacheMemory.h"

/**
 * @brief Processing unit representation with the basic attributes, also supports the invasive computing operations 
 * 
 */
class ProcessingUnit
{
  public:
	ProcessingUnit(int _x, int _y, Clock *_clk_instance);

	void start();

	void invade(ILet *_new_iLet);
	void infect();
	void retreat();

	coordinate get_coodinate();
	Invasive_States get_state();
	
	JSON * monitoring();

  private:
	pthread_t pu_exe_thread;
	pthread_mutex_t pu_mutex = PTHREAD_MUTEX_INITIALIZER;

	/**
	 * @brief State register
	 * 
	 */
	Invasive_States pu_state;
	/**
	 * @brief Coordinate register
	 * 
	 */
	coordinate pu_coordenate;

	/**
	 * @brief Cache memory instance
	 * 
	 */
	CacheMemory * cache_mem;
	

	/**
	 * @brief Workload
	 * 
	 */
	int current_load;
	/**
	 * @brief Used
	 * 
	 */
	int current_used;
	/**
	 * @brief Assigned iLet
	 * 
	 */
	ILet * iLet_ptr;

	/**
	 * @brief Clock instance
	 * 
	 */
	Clock *clk_instance;

	/**
	 * @brief Registers instance
	 * 
	 */
	JSON registers;

	static void *executing(void *obj);
};

#endif