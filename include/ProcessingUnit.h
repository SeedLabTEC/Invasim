/**
* @file ProcessingUnit.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 11/02/19
**/

#ifndef INCLUDE_PROCESSINGUNIT_H_
#define INCLUDE_PROCESSINGUNIT_H_

#include <pthread.h>
#include "Debug.h"

#include "json.hpp"
using JSON = nlohmann::json;

#include "Clock.h"
#include "ILet.h"
#include "CacheMemory.h"

class ProcessingUnit
{
  public:
	ProcessingUnit(int _x, int _y, Clock *_clk_instance);

	void start();

	void new_task(ILet *_new_iLet);

	coordinate get_coodinate();
	Invasive_States get_state();

	JSON * monitoring();

  private:
	pthread_t pu_exe_thread;

	//Registers
	Invasive_States pu_state;
	coordinate pu_coordenate;

	//Memory
	CacheMemory * cache_mem;
	

	//Workload
	int current_load;
	ILet * iLet_ptr;

	//Clock
	Clock *clk_instance;

	//Thread Methods
	static void *executing(void *obj);
};

#endif