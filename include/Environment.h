/**
* @file Environment.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 09/02/19
**/

#ifndef INCLUDE_ENVIRONMENT_H_
#define INCLUDE_ENVIRONMENT_H_

#include "Utils.h"

#include "ManyCoreArch.h"
#include "Monitor.h"
#include "SequenceIlet.h"
#include "Clock.h"

#define DEFAULT_CORES 8
#define DEFAULT_PROBABILITY 0.80
#define DEFAULT_SEED 1

#define PARAMS_FILE "/params.json"

class Environment
{
  public:
	Environment();

	Environment(int _x_dim, int _y_dim, float _decision_probability, std::string _working_dir, int _seed);

	void start_environment();

	void step(int steps);

  private:
	int x_dim;
	int y_dim;
	int seed;
	float decision_probability;
	std::string working_dir;

	ManyCoreArch * many_core_instance;
	Monitor * env_monitor;
	SequenceIlet * seq_ilet;
	

	Clock *clk_instance;

	void init();
	void write_params();
};

#endif