/**
* @file ProcessingUnit.cpp
* @brief Processing unit source
* @author Dennis Porras Barrantes
* @date 11/02/19
**/

#include "../include/ProcessingUnit.h"

/**
 * @brief Construct a new Processing Unit:: Processing Unit object
 * 
 * @param _x 
 * @param _y 
 * @param _clk_instance 
 */
ProcessingUnit::ProcessingUnit(int _x, int _y, Clock *_clk_instance)
{
	dprintf("PU = (%d, %d): New processing unit coordenate.\n", _x, _y);
	this->pu_state = FREE;
	this->pu_coordenate.x = _x;
	this->pu_coordenate.y = _y;
	this->current_load = 0;
	this->iLet_ptr = NULL;
	this->current_used = -1;
	this->clk_instance = _clk_instance;

	//Memory features
	this->cache_mem = new CacheMemory(this->pu_coordenate.x, this->pu_coordenate.y);
}

/**
 * @brief Method that starts main thread
 * 
 */
void ProcessingUnit::start()
{
	//create threads
	pthread_create(&this->pu_exe_thread, NULL, ProcessingUnit::executing, (void *)this);
	//detach threads
	pthread_detach(this->pu_exe_thread);
}

/**
 * @brief Function that change the state of unit and assigns an iLet
 * 
 * @param _new_iLet 
 */
void ProcessingUnit::invade(ILet *_new_iLet)
{
	pthread_mutex_lock(&this->pu_mutex);
	dprintf("PU = (%d, %d): New iLet assiged.\n", this->pu_coordenate.x, this->pu_coordenate.y);
	this->iLet_ptr = _new_iLet;
	this->pu_state = INVADED;
	pthread_mutex_unlock(&this->pu_mutex);
}

/**
 * @brief Function thta sets a workload and changes the state
 * 
 */
void ProcessingUnit::infect()
{
	pthread_mutex_lock(&this->pu_mutex);
	this->current_load = this->iLet_ptr->get_current_operation()->get_parameter();
	this->pu_state = INFECTED;
	pthread_mutex_unlock(&this->pu_mutex);
}

/**
 * @brief Function that remove the iLet and changes state
 * 
 */
void ProcessingUnit::retreat()
{
	pthread_mutex_lock(&this->pu_mutex);
	this->pu_state = FREE;
	this->iLet_ptr = NULL;
	this->current_used = -1;
	pthread_mutex_unlock(&this->pu_mutex);
}

/**
 * @brief Coodinate getter
 * 
 * @return coordinate 
 */
coordinate ProcessingUnit::get_coodinate()
{
	return this->pu_coordenate;
}

/**
 * @brief State getter
 * 
 * @return Invasive_States 
 */
Invasive_States ProcessingUnit::get_state()
{
	pthread_mutex_lock(&this->pu_mutex);
	Invasive_States tmp_state = this->pu_state;
	pthread_mutex_unlock(&this->pu_mutex);
	return tmp_state;
}

/**
 * @brief Funciton that gets all information of processing unit
 * 
 * @return JSON* 
 */
JSON *ProcessingUnit::monitoring()
{
	JSON *json_info = new JSON;
	//Json contruction
	*json_info = {
		{"Coordenate_x", this->pu_coordenate.x},
		{"Coordenate_y", this->pu_coordenate.y},
		{"Load", this->current_load},
		{"State", STRING_STATES[this->pu_state]}};
	//Set if in ilet;
	if (this->iLet_ptr != NULL)
	{
		(*json_info)["ILet"] = this->iLet_ptr->get_id();
	}
	else
	{
		//When it has no ilet assigned
		(*json_info)["ILet"] = -1;
	}
	return json_info;
}

/**
 * @brief Exceuting thread function. Awaits for the clock signal to execute its different states
 * 
 * @param obj 
 * @return void* 
 */
void *ProcessingUnit::executing(void *obj)
{
	ProcessingUnit *current = (ProcessingUnit *)obj;
	dprintf("PU = (%d, %d): New processing unit started.\n", current->pu_coordenate.x, current->pu_coordenate.y);
	//Get clock signal and mutex
	pthread_mutex_t *clk_cycle_mutex = current->clk_instance->get_cycle_mutex_ptr();
	pthread_cond_t *clk_cycle_cond = current->clk_instance->get_cycle_cond_ptr();

	//Start component loop
	while (1)
	{
		//Await signal
		pthread_cond_wait(clk_cycle_cond, clk_cycle_mutex);

		//get current state
		Invasive_States current_state = current->get_state();
		switch (current_state)
		{
		case INVADED:
			//Invaded state
			dprintf("PU = (%d, %d): Invaded processor by ILet = %d.\n",
					current->pu_coordenate.x,
					current->pu_coordenate.y,
					current->iLet_ptr->get_id());
			break;
		case INFECTED:
			//Reduce wokload
			dprintf("PU = (%d, %d): Infected processor by ILet = %d.\n",
					current->pu_coordenate.x,
					current->pu_coordenate.y,
					current->iLet_ptr->get_id());
			pthread_mutex_lock(&current->pu_mutex);
			////////////////////////////////////////////////////////////////////////////////////////////////

			if ( (current->current_used == -1) )
			{
				for (int spi = 0; spi < (int)current->iLet_ptr->get_current_operation()->get_subProcess().size(); spi++)
				{
					if (!current->iLet_ptr->get_current_operation()->get_subProcess()[spi].state)
					{
						current->iLet_ptr->get_current_operation()->set_codeOperation(spi, current->get_coodinate());
						current->current_used = spi;
						current->current_load = current->iLet_ptr->get_current_operation()->get_subProcess()[current->current_used].puWork;
						break;
					}
				}
			}
			else
			{
				current->current_load = current->iLet_ptr->get_current_operation()->get_subProcess()[current->current_used].puWork;
			}

			if ((current->iLet_ptr->get_current_operation()->get_subProcess()[current->current_used].puWork >= 0) && (current->current_used != -1))
			{
				//std::cout << "current->current_load "<<current->current_load << std::endl;
				//std::cout << "current->current_used  "<<current->current_used << std::endl;
				std::cout << (int)current->iLet_ptr->get_current_operation()->get_subProcess().size() << " ON ILET " << current->iLet_ptr->get_id() << " PROGRAM " << current->iLet_ptr->get_program_id() << " PROCESS " << current->current_used << " ON UNIT " << current->get_coodinate().x << " CURRENT LOAD " << current->current_load - 1 << " " << current->iLet_ptr->get_current_operation()->get_codeOperation(current->current_used, current->current_load - 1) << std::endl; // execute code
				current->iLet_ptr->get_current_operation()->reduce_WorkOfProcess(current->current_used);
				//std::cout<<"ON ILET "<< current->iLet_ptr->get_id()<<" ON UNIT "<< current->get_coodinate().x << std::endl;
				current->current_load--;
			}
			else
			{
				//End execution
				dprintf("PU = (%d, %d): Execution Done by ILet = %d.\n",
						current->pu_coordenate.x,
						current->pu_coordenate.y,
						current->iLet_ptr->get_id());
				current->pu_state = INVADED;
				//std::cout << (int)current->iLet_ptr->get_current_operation()->get_subProcess().size() << " ON FINISHED ILET " << current->iLet_ptr->get_id() << " PROGRAM " << current->iLet_ptr->get_program_id() << " PROCESS " << current->current_used << " ON UNIT " << current->get_coodinate().x << " CURRENT LOAD " << current->current_load << std::endl; // execute code
																																																																																																																							 // set finished
			}

			////////////////////////////////////////////////////////////////////////////////////////////////
			pthread_mutex_unlock(&current->pu_mutex);
			break;
		case FREE:
			//Free state
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