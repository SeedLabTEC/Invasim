/**
* @file ResourceAdmin.cpp
* @brief Resource administrator source
* @author Dennis Porras Barrantes
* @date 29/03/19
**/

#include "../include/ResourceAdmin.h"

/**
 * @brief Construct a new Resource Admin:: Resource Admin object
 * 
 * @param _pu_array_ptr 
 * @param _x_dim 
 * @param _y_dim 
 * @param _clk_instance 
 */
ResourceAdmin::ResourceAdmin(ProcessingUnit ***_pu_array_ptr, int _x_dim, int _y_dim, Clock *_clk_instance)
{
	this->max_iLets = DEFAULT_MAX_ILETS;
	this->init(_pu_array_ptr, _x_dim, _y_dim, _clk_instance);
}

/**
 * @brief Construct a new Resource Admin:: Resource Admin object
 * 
 * @param _pu_array_ptr 
 * @param _x_dim 
 * @param _y_dim 
 * @param _max_iLets 
 * @param _clk_instance 
 */
ResourceAdmin::ResourceAdmin(ProcessingUnit ***_pu_array_ptr, int _x_dim, int _y_dim, int _max_iLets, Clock *_clk_instance)
{
	this->max_iLets = _max_iLets;
	this->init(_pu_array_ptr, _x_dim, _y_dim, _clk_instance);
}

/**
 * @brief Function that initialize components and pointers
 * 
 * @param _pu_array_ptr 
 * @param _x_dim 
 * @param _y_dim 
 * @param _clk_instance 
 */
void ResourceAdmin::init(ProcessingUnit ***_pu_array_ptr, int _x_dim, int _y_dim, Clock *_clk_instance)
{
	this->pu_array_ptr = _pu_array_ptr;
	this->clk_instance = _clk_instance;
	this->x_dim = _x_dim;
	this->y_dim = _y_dim;
	this->available = this->x_dim * this->y_dim;
}

/**
 * @brief Function that starts the component thread
 * 
 */
void ResourceAdmin::start()
{
	//create threads
	pthread_create(&this->pu_exe_thread, NULL, ResourceAdmin::managing, (void *)this);
	//detach threads
	pthread_detach(this->pu_exe_thread);
}

/**
 * @brief Add a new iLet to the queue
 * 
 * @param new_iLet 
 */
void ResourceAdmin::add_iLet(ILet *new_iLet)
{
	pthread_mutex_lock(&this->ilet_mutex);
	this->incomming_ilets.push(new_iLet);
	pthread_mutex_unlock(&this->ilet_mutex);
}

/**
 * @brief Function that gets information of component and processing units
 * 
 * @return JSON* array
 */
JSON *ResourceAdmin::monitoring()
{
	JSON *array_info = new JSON;
	//List to return
	*array_info = JSON::array();

	//Json construction
	JSON resource_admin_info = {
		{"Incomming_Ilets", this->incomming_ilets.size()},
		{"Waiting_Ilets", this->invaded_ilets.size()},
		{"Executing_Ilets", this->execute_ilets.size()},
		{"Max_Ilets", this->max_iLets}};

	//Push data
	array_info->push_back(resource_admin_info);

	//Get information of every processing unit
	for (int i = 0; i < this->x_dim; i++)
	{
		for (int j = 0; j < this->y_dim; j++)
		{
			JSON *pu_info_ptr = pu_array_ptr[i][j]->monitoring();
			//Push unit info
			array_info->push_back(*pu_info_ptr);
			delete pu_info_ptr;
		}
	}

	return array_info;
}

/**
 * @brief Function that assings resoruces to an ilet as they are available
 * 
 * @param resources_amount 
 * @param resources 
 * @param ilet 
 */
void ResourceAdmin::invade(int resources_amount, std::vector<coordinate> *resources, ILet *ilet)
{
	//Flag when they are assigned
	bool found = false;
	//Assigned resources
	int invaded_resources = 0;

	//Iterate all processing units
	for (int i = 0; i < this->x_dim; i++)
	{
		for (int j = 0; j < this->y_dim; j++)
		{
			if (this->pu_array_ptr[i][j]->get_state() == FREE)
			{
				//When a resource is found it the coordinate is assigned
				coordinate new_pu = this->pu_array_ptr[i][j]->get_coodinate();
				//Vector thta has to be filled with coodinates
				resources->push_back(new_pu);
				this->pu_array_ptr[i][j]->invade(ilet);
				invaded_resources++;
				//Finish when assignment is done
				if (invaded_resources == resources_amount)
				{
					found = true;
					break;
				}
			}
		}
		if (found)
		{
			break;
		}
	}
	//Discount available resources
	this->available -= resources_amount;
}

/**
 * @brief Funciton that infects all the resources in an iLet
 * 
 * @param ilet 
 */
void ResourceAdmin::infect(ILet *ilet)
{
	unsigned int resources = ilet->get_resources()->size();
	for (unsigned int i = 0; i < resources; i++)
	{
		coordinate position = ilet->get_resources()->at(i);
		this->pu_array_ptr[position.x][position.y]->infect();
	}
	ilet->set_state(EXECUTING);
}

/**
 * @brief Funciton that retreats all the resources in an iLet
 * 
 * @param ilet 
 */
void ResourceAdmin::retreat(ILet *ilet)
{
	unsigned int resources = ilet->get_resources()->size();
	for (unsigned int i = 0; i < resources; i++)
	{
		coordinate position = ilet->get_resources()->at(i);
		this->pu_array_ptr[position.x][position.y]->retreat();
	}
	this->available += resources;
}

/**
 * @brief Funciton that verify if an iLet has finished 
 * 
 * @param ilet 
 * @return true 
 * @return false 
 */
bool ResourceAdmin::verify_ilet(ILet *ilet)
{
	bool is_done = true;

	unsigned int resources = ilet->get_resources()->size();
	//Iterate resources in iLet

	for (unsigned int i = 0; i < resources; i++)
	{
		coordinate position = ilet->get_resources()->at(i);
		//If a processing unit is infected the iLet is not done

		if (this->pu_array_ptr[position.x][position.y]->get_state() == INFECTED)
		{
			is_done = false;
			break;
		}
	}
	//std::cout << " VALUE HERE "<< is_done << std::endl;

	for (int spi = 0; spi < (int)ilet->get_current_operation()->get_subProcess().size(); spi++)
	{
		if (!ilet->get_current_operation()->get_subProcess()[spi].state)
		{
			is_done = false;
			//std::cout << " VALUE FALSE HERE "<< is_done << std::endl;
			break;
		}
	}

	return is_done;
}

/**
 * @brief Getter of list of ilets on invaded
 * 
 * @param obj 
 * @return std::vector<ILet *>
 */
std::vector<ILet *> ResourceAdmin::get_invaded()
{
	//std::cout << "lsReAd " << this->invaded_ilets.size() << std::endl;
	//std::cout << "lsReAd " << this->execute_ilets.size() << std::endl;

	return this->execute_ilets;
}

/**
 * @brief Execution thread function that handles all requests with its resources
 * 
 * @param obj 
 * @return void* 
 */
void *ResourceAdmin::managing(void *obj)
{
	ResourceAdmin *current = (ResourceAdmin *)obj;
	dprintf("ResourceAdmin: The resource administrator is started.\n");
	//Get clock mutex and conditional variable
	pthread_mutex_t *clk_cycle_mutex = current->clk_instance->get_cycle_mutex_ptr();
	pthread_cond_t *clk_cycle_cond = current->clk_instance->get_cycle_cond_ptr();
	//Component loop
	while (1)
	{
		//Await to clock signal
		pthread_cond_wait(clk_cycle_cond, clk_cycle_mutex);
		dprintf("ResourceAdmin: %s.\n", current->monitoring()->dump().c_str());

		ILet *current_ilet = NULL;

		//Verify if there is any incomming iLet
		if (current->incomming_ilets.size() > 0)
		{
			pthread_mutex_lock(&current->ilet_mutex);
			//Get front of queue and pop
			current_ilet = current->incomming_ilets.front();
			current->incomming_ilets.pop();
			pthread_mutex_unlock(&current->ilet_mutex);
			dprintf("ResourceAdmin: Managing incomming Ilet = %d.\n", current_ilet->get_id());
			//Verify if it is an iLet that need more resources so the operationg has to be poped
			if (current_ilet->get_state() == WAITING)
			{
				current_ilet->pop_operation();
			}
			//Verify if there are resources to be assigned
			if (current_ilet->get_current_operation()->get_parameter() <= current->available)
			{
				dprintf("ResourceAdmin: Found resources to Ilet = %d.\n", current_ilet->get_id());
				//Set state to waiting for resources and push to invaded vector
				current_ilet->set_state(WAITING);
				current->invaded_ilets.push_back(current_ilet);
			}
			else
			{
				//If there are not enough resources, then is queued again
				dprintf("ResourceAdmin: Not enough resources to Ilet = %d.\n", current_ilet->get_id());
				pthread_mutex_lock(&current->ilet_mutex);
				current_ilet->set_state(EXECUTING);
				current->incomming_ilets.push(current_ilet);
				pthread_mutex_unlock(&current->ilet_mutex);
			}
		}
		//Verify if there are any executing iLet
		if (current->execute_ilets.size() > 0)
		{
			//Iterate those executing iLets
			for (size_t i = 0; i < current->execute_ilets.size(); i++)
			{
				//Get an iLet
				current_ilet = current->execute_ilets.at(i);
				switch (current_ilet->get_state())
				{
				case WAITING:
				{
					//When waiting ask if it has to infect
					int start = current_ilet->execute_operation();
					if (start)
					{

						dprintf("ResourceAdmin: Infecting resources to Ilet = %d.\n", current_ilet->get_id());
						current->infect(current_ilet);
					}
				}
				break;

				case EXECUTING:
				{
					//When executing ask if it has to be terminted
					int terminate = 1;
					if (!terminate)
					{
						dprintf("ResourceAdmin: Ilet = %d to be terminated.\n", current_ilet->get_id());
						current_ilet->set_state(DONE);
					} //If not terminated verify if it is done
					else if (current_ilet->get_current_operation()->get_operation() == INFECT)
					{
						bool is_done = current->verify_ilet(current_ilet);
						if (is_done)
						{
							dprintf("ResourceAdmin: Ilet = %d is done.\n", current_ilet->get_id());
							std::cout << "DONE ILET " << current_ilet->get_id() << std::endl;
							current_ilet->set_state(DONE);
						}
						else // free units with completation subprocess and infect if is neccesary
						{
							for (int spi = 0; spi < (int)current_ilet->get_current_operation()->get_subProcess().size(); spi++)
							{
								if ((current_ilet->get_current_operation()->get_subProcess()[spi].puWork == 0))
								{
									current_ilet->get_current_operation()->reduce_WorkOfProcess(spi); // reduce to avoid pass here again
									coordinate position = current_ilet->get_current_operation()->get_subProcess()[spi].SPxPU;
									//current_ilet->pop_one_resource(position); // pop resurce
									current->pu_array_ptr[position.x][position.y]->retreat();
									//current->available += 1;

									current->pu_array_ptr[position.x][position.y]->invade(current_ilet);
									current->pu_array_ptr[position.x][position.y]->infect();
								}
							}

							//current->invade(1, current_ilet->get_resources(), current_ilet);
						}
					}
				}
				break;

				case DONE:
				{
					//When it is done pop the operation or verify if it will retreat
					if (current_ilet->get_current_operation()->get_operation() == RETREAT)
					{
						dprintf("ResourceAdmin: Ilet = %d terminated.\n", current_ilet->get_id());
						current->retreat(current_ilet);
						current->execute_ilets.erase(current->execute_ilets.begin() + i);
					}
					else
					{
						//Pop operation in case it is not a retreat
						current_ilet->pop_operation();
						if (current_ilet->get_current_operation()->get_operation() == RETREAT)
						{
							current_ilet->set_state(DONE);
						} //If operation is invade then is has to be queued
						else if (current_ilet->get_current_operation()->get_operation() == INVADE)
						{
							current_ilet->set_state(WAITING);
							current->invaded_ilets.push_back(current_ilet);
							current->execute_ilets.erase(current->execute_ilets.begin() + i);
						}
						else
						{
							//In case if it is an infection
							current_ilet->set_state(WAITING);
						}
					}
				}
				break;

				default:
					break;
				}
			}
		}

		//Verify if there are iLet that has to invade
		if (current->invaded_ilets.size() > 0)
		{
			//Iterate those iLets
			for (size_t i = 0; i < current->invaded_ilets.size(); i++)
			{
				//Get an iLet
				current_ilet = current->invaded_ilets.at(i);
				//Invade resources
				current->invade(current_ilet->get_current_operation()->get_parameter(),
								current_ilet->get_resources(),
								current_ilet);

				current_ilet->pop_operation();
				//Verify it will invade more resources
				if (current_ilet->get_current_operation()->get_operation() != INVADE)
				{
					//To proceed infection
					current->execute_ilets.push_back(current_ilet);
					current->invaded_ilets.erase(current->invaded_ilets.begin() + i);
				}
			}
		}
	}
	return NULL;
}
