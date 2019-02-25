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
Clock::Clock() { }

pthread_mutex_t * Clock::get_cycle_mutex_ptr(){
    return &this->cycle_mutex;
}

pthread_cond_t * Clock::get_cycle_cond_ptr(){
    return &this->cycle_cond;
}

void Clock::next_cycle(){
    sleep(WAIT_SEC);
    pthread_cond_broadcast(&this->cycle_cond);
}