/**
* @file Clock.cpp
* @brief Description
* @author Dennis Porras Barrantes
* @date 15/02/19
**/

#include "../include/Clock.h"

/**
* @brief Constructor
**/
Clock::Clock() 
{
    this->cycle = 0;
}

pthread_mutex_t *Clock::get_cycle_mutex_ptr()
{
    return &this->cycle_mutex;
}

pthread_cond_t *Clock::get_cycle_cond_ptr()
{
    return &this->cycle_cond;
}

pthread_mutex_t *Clock::get_monitor_mutex_ptr()
{
    return &this->monitor_mutex;
}

pthread_cond_t *Clock::get_monitor_cond_ptr()
{
    return &this->monitor_cond;
}

void Clock::next_cycle()
{
    pthread_cond_broadcast(&this->cycle_cond);
    sleep(WAIT_SEC);
    this->cycle++;
    pthread_cond_signal(&this->monitor_cond);
    sleep(WAIT_SEC);
}

int Clock::get_cycle()
{
    return this->cycle;
}