/**
* @file Clock.h
* @brief Clack class declaration
* @author Dennis Porras Barrantes
* @date 15/02/19
**/

#ifndef INCLUDE_CLOCK_H_
#define INCLUDE_CLOCK_H_

#include "Utils.h"
#include <string>

//Wait miliseconds
#define WAIT_SEC 250

#include <pthread.h>
#include <unistd.h>
#include <chrono>
#include <thread>

/**
 * @brief Clock class representation that generates signals to all components using a instance.
 * 
 */
class Clock
{
public:
	Clock();

	pthread_mutex_t *get_cycle_mutex_ptr();

	pthread_cond_t *get_cycle_cond_ptr();

	pthread_mutex_t *get_monitor_mutex_ptr();

	pthread_cond_t *get_monitor_cond_ptr();

	void next_cycle();

	int get_cycle();

private:
	pthread_mutex_t cycle_mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_cond_t cycle_cond = PTHREAD_COND_INITIALIZER;
	
	pthread_mutex_t monitor_mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_cond_t monitor_cond = PTHREAD_COND_INITIALIZER;

	/**
	 * @brief Cycle counter
	 * 
	 */
	int cycle;
};

#endif
