/**
* @file Environment.h
* @brief Environment class declaration.
* @author Dennis Porras Barrantes
* @date 09/02/19
**/

#ifndef INCLUDE_ENVIRONMENT_H_
#define INCLUDE_ENVIRONMENT_H_

#include "Utils.h"

//Components of environment
#include "ManyCoreArch.h"
#include "Monitor.h"
#include "SequenceIlet.h"
#include "Clock.h"
#include "CacheController.h"
#include "InterconnectionNetwork.h"

#include <pthread.h>

#define DEFAULT_CORES 8
#define DEFAULT_PROBABILITY 0.80
#define DEFAULT_SEED 1

#define PARAMS_FILE "/params.json"

/**
 * @brief Environment class that containt the diferent components of the platform and its parameters.
 * 
 */
class Environment
{
  public:
	Environment();

	Environment(int _x_dim, int _y_dim, float _decision_probability, int ai, std::string _working_dir, int _seed);

	void start_environment();

	void step(int steps);

  private:
  /**
	 * @brief using artificial intelligence to assign resources.
	 * 
	 */
	bool ai;
	/**
	 * @brief x dimension of manycore architrecture.
	 * 
	 */
	int x_dim;
	/**
	 * @brief y dimension of manycore architecture
	 * 
	 */
	int y_dim;
	/**
	 * @brief Seed for random number generation in iLet generator.
	 * 
	 */
	int seed;
	/**
	 * @brief Decision probability of every iLet.
	 * 
	 */
	float decision_probability;
	/**
	 * @brief Working directory path
	 * 
	 */
	std::string working_dir;

	/**
	 * @brief Manycore instance
	 * 
	 */
	ManyCoreArch * many_core_instance;
	/**
	 * @brief Monitor instance
	 * 
	 */
	Monitor * env_monitor;
	/**
	 * @brief Sequencer iLet instance
	 * 
	 */
	SequenceIlet * seq_ilet;
	
	/**
	 * @brief Clock instance
	 * 
	 */
	Clock *clk_instance;

	void init(std::string _working_dir);
	void write_params();

	InterconnectionNetwork * intNet;
	
	typedef void * (*THREADFUNCPTR)(void *);
	pthread_t thread_events, thread_requests;
	int res_thread_events, res_thread_requests;
};

#endif