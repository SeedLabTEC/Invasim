/**
* @file ProcessingUnit.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 11/02/19
**/

#ifndef INCLUDE_PROCESSINGUNIT_H_
#define INCLUDE_PROCESSINGUNIT_H_

#include <pthread.h>
#include <string>
#include "Debug.h"

#include "json.hpp"
using JSON = nlohmann::json;

#include "Clock.h"
#include "ILet.h"
#include "CacheMemory.h"

enum Invasive_States
{
	INVADED,
	INFECTED,
	FREE
};

static const std::string STRING_STATES[] = {
	"Invaded",
	"Infected",
	"Free"
};

class ProcessingUnit
{
  public:
	ProcessingUnit(int p_pu_id, Clock *_clk_instance);

	void start();

	void new_task(ILet *_new_iLet);

	JSON * monitoring();

  private:
	pthread_t pu_exe_thread;

	//Registers
	Invasive_States pu_state;
	int pu_id;

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