/**
* @file Clock.cpp
* @brief Clock source
* @author Dennis Porras Barrantes
* @date 15/02/19
**/

#include "../include/Clock.h"

/**
 * @brief Construct a new Clock:: Clock object
 * 
 */
Clock::Clock() 
{
    this->cycle = 0;
}

/**
 * @brief Clock mutex getter
 * 
 * @return pthread_mutex_t* clock mutex
 */
pthread_mutex_t *Clock::get_cycle_mutex_ptr()
{
    return &this->cycle_mutex;
}

/**
 * @brief Clock conditional variable getter
 * 
 * @return pthread_cond_t* clock cond variable
 */
pthread_cond_t *Clock::get_cycle_cond_ptr()
{
    return &this->cycle_cond;
}

/**
 * @brief Clock monitor mutex getter
 * 
 * @return pthread_mutex_t* Monitor mutex
 */
pthread_mutex_t *Clock::get_monitor_mutex_ptr()
{
    return &this->monitor_mutex;
}

/**
 * @brief Clock monitor conditional variable getter
 * 
 * @return pthread_cond_t* Monitor cond variable
 */
pthread_cond_t *Clock::get_monitor_cond_ptr()
{
    return &this->monitor_cond;
}

/**
 * @brief Funciton that sends a signal to all the components in the platform, to advance one cycle in time. Monitor signal is after components because it needs all the components to finish.
 * 
 */
void Clock::next_cycle()
{
    dprintf("Clock: Cycle = %d--------------------------------\n", this->cycle);
    pthread_cond_broadcast(&this->cycle_cond);
    std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_SEC));
    this->cycle++;
    pthread_cond_signal(&this->monitor_cond);
    std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_SEC));
}

/**
 * @brief Cycle getter
 * 
 * @return int cycle
 */
int Clock::get_cycle()
{
    return this->cycle;
}
