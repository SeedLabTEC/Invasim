/**
* @file Clock.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 15/02/19
**/

#ifndef INCLUDE_CLOCK_H_
#define INCLUDE_CLOCK_H_

#include "Utils.h"
#include <string>

#define WAIT_SEC 1

#include <pthread.h>
#include <unistd.h>

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

	int cycle;
};

#endif