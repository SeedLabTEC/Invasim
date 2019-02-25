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

#include "Clock.h"
#include "WorkPackage.h"

enum Invasive_States { INVADED, INFECTED, FREE };

class ProcessingUnit {
public: 
	ProcessingUnit(int p_pu_id, Clock * _clk_instance);

	void start();

	void new_task(WorkPackage * _new_workload);
private:
	pthread_t pu_exe_thread;

	//Registers
	Invasive_States pu_state;
	int pu_id;

	//Workload
	WorkPackage * current_workload;

	//Clock
	Clock * clk_instance;

	//Thread Methods
	static void * executing(void * obj);
};

#endif