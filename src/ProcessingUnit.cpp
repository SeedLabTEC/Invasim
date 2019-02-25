/**
* @file ProcessingUnit.cpp
* @brief Description
* @author Dennis Porras Barrantes
* @date 11/02/19
**/

#include "../include/ProcessingUnit.h"

/**
* @brief Constructor
**/
ProcessingUnit::ProcessingUnit(int _pu_id, Clock * _clk_instace){
    dprintf("CPU: New processing unit id = %d\n", _pu_id);
    this->pu_state = FREE;
    this->pu_id = _pu_id;
    this->current_workload = NULL;
    this->clk_instance = _clk_instace;
}

/**
 * @brief Start method which initializes main thread 
 * */
void ProcessingUnit::start(){
    //create threads
	pthread_create( &this->pu_exe_thread, NULL, ProcessingUnit::executing, (void*)this);
    //detach threads
	pthread_detach(this->pu_exe_thread);
}

void * ProcessingUnit::executing(void * obj){
	ProcessingUnit *  current = (ProcessingUnit *)obj;
    dprintf("CPU: New processing unit started id = %d.\n", current->pu_id);
	pthread_mutex_t * clk_cycle_mutex = current->clk_instance->get_cycle_mutex_ptr();
	pthread_cond_t *  clk_cycle_cond = current->clk_instance->get_cycle_cond_ptr();
    int i = 0;
    while(1)
    {
        pthread_cond_wait(clk_cycle_cond, clk_cycle_mutex);
        dprintf("CPU: Cycle, id = %d i = %d.\n", current->pu_id, i);
        i++;
    }
    return NULL;
}