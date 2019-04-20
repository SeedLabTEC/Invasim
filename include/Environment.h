/**
* @file Environment.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 09/02/19
**/

#ifndef INCLUDE_ENVIRONMENT_H_
#define INCLUDE_ENVIRONMENT_H_

#include "Debug.h"

#include "ManyCoreArch.h"
#include "Monitor.h"
#include "SequenceIlet.h"
#include "Clock.h"

#define DEFAULT_CORES 8

class Environment
{
  public:
	Environment();

	Environment(int _cpu_cores);

	void set_cpu_cores(int _cpu_cores);

	int get_cpu_cores();

	void start_environment();

	void step(int steps);

  private:
	int cpu_cores;

	ManyCoreArch * many_core_instance;
	Monitor * env_monitor;
	SequenceIlet * seq_ilet;
	

	Clock *clk_instance;

	void init();
};

#endif