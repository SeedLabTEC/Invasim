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
ProcessingUnit::ProcessingUnit(int _x, int _y, Clock *_clk_instance)
{
	dprintf("PU = (%d, %d): New processing unit coordenate.\n", _x, _y);
	this->pu_state = FREE;
	this->pu_coordenate.x = _x;
	this->pu_coordenate.y = _y;
	this->current_load = 0;
	this->iLet_ptr = NULL;
	this->clk_instance = _clk_instance;

	//Memory features
	this->cache_mem = new CacheMemory(this->pu_coordenate.x, this->pu_coordenate.y);
}

/**
 * @brief Start method which initializes main thread 
 * */
void ProcessingUnit::start()
{
	//create threads
	pthread_create(&this->pu_exe_thread, NULL, ProcessingUnit::executing, (void *)this);
	//detach threads
	pthread_detach(this->pu_exe_thread);
}

/**
 * 
 * */
void ProcessingUnit::invade(ILet *_new_iLet)
{
	pthread_mutex_lock(&this->pu_mutex);
	dprintf("PU = (%d, %d): New iLet assiged.\n", this->pu_coordenate.x, this->pu_coordenate.y);
	this->iLet_ptr = _new_iLet;
	this->pu_state = INVADED;
	pthread_mutex_unlock(&this->pu_mutex);
}

void ProcessingUnit::infect(){
	pthread_mutex_lock(&this->pu_mutex);
	this->current_load = this->iLet_ptr->get_current_operation()->get_parameter();
	this->pu_state = INFECTED;
	pthread_mutex_unlock(&this->pu_mutex);
}

void ProcessingUnit::retreat()
{
	pthread_mutex_lock(&this->pu_mutex);
	this->pu_state = FREE;
	this->iLet_ptr = NULL;
	pthread_mutex_unlock(&this->pu_mutex);
}

coordinate ProcessingUnit::get_coodinate()
{
	return this->pu_coordenate;
}

Invasive_States ProcessingUnit::get_state()
{
	pthread_mutex_lock(&this->pu_mutex);
	Invasive_States tmp_state = this->pu_state;
	pthread_mutex_unlock(&this->pu_mutex);
	return tmp_state;
}

/**
 * 
 * */
JSON *ProcessingUnit::monitoring()
{
	JSON *json_info = new JSON;
	*json_info = {
		{"Coordenate_x", this->pu_coordenate.x},
		{"Coordenate_y", this->pu_coordenate.y},
		{"Load", this->current_load},
		{"State", STRING_STATES[this->pu_state]}};
	if (this->iLet_ptr != NULL)
	{
		(*json_info)["ILet"] = this->iLet_ptr->get_id();
	}
	else
	{
		(*json_info)["ILet"] = "NONE";
	}
	return json_info;
}

/**
 * 
 * */
void *ProcessingUnit::executing(void *obj)
{
	ProcessingUnit *current = (ProcessingUnit *)obj;
	dprintf("PU = (%d, %d): New processing unit started.\n", current->pu_coordenate.x, current->pu_coordenate.y);
	pthread_mutex_t *clk_cycle_mutex = current->clk_instance->get_cycle_mutex_ptr();
	pthread_cond_t *clk_cycle_cond = current->clk_instance->get_cycle_cond_ptr();

	while (1)
	{
		pthread_cond_wait(clk_cycle_cond, clk_cycle_mutex);

		Invasive_States current_state = current->get_state();
		switch (current_state)
		{
		case INVADED:
			dprintf("PU = (%d, %d): Invaded processor by ILet = %d.\n",
					current->pu_coordenate.x,
					current->pu_coordenate.y,
					current->iLet_ptr->get_id());
			break;
		case INFECTED:
			dprintf("PU = (%d, %d): Infected processor by ILet = %d.\n",
					current->pu_coordenate.x,
					current->pu_coordenate.y,
					current->iLet_ptr->get_id());
			pthread_mutex_lock(&current->pu_mutex);
			if (current->current_load > 0)
			{
				current->current_load--;
			}
			else
			{
				dprintf("PU = (%d, %d): Execution Done by ILet = %d.\n",
					current->pu_coordenate.x,
					current->pu_coordenate.y,
					current->iLet_ptr->get_id());
				current->pu_state = INVADED;
			}
			pthread_mutex_unlock(&current->pu_mutex);
			break;
		case FREE:
			dprintf("PU = (%d, %d): Free processor.\n",
					current->pu_coordenate.x,
					current->pu_coordenate.y);
			break;
		default:
			break;
		}
	}
	return NULL;
}