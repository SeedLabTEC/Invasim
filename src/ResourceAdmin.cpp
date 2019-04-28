/**
* @file ResourceAdmin.cpp
* @brief Description
* @author Dennis Porras Barrantes
* @date 29/03/19
**/

#include "../include/ResourceAdmin.h"

/**
* @brief Constructor
**/
ResourceAdmin::ResourceAdmin(ProcessingUnit ***_pu_array_ptr, int _x_dim, int _y_dim, Clock *_clk_instance)
{
	this->max_iLets = DEFAULT_MAX_ILETS;
	this->init(_pu_array_ptr, _x_dim, _y_dim, _clk_instance);
}

/**
* @brief Constructor
**/
ResourceAdmin::ResourceAdmin(ProcessingUnit ***_pu_array_ptr, int _x_dim, int _y_dim, int _max_iLets, Clock *_clk_instance)
{
	this->max_iLets = _max_iLets;
	this->init(_pu_array_ptr, _x_dim, _y_dim, _clk_instance);
}

void ResourceAdmin::init(ProcessingUnit ***_pu_array_ptr, int _x_dim, int _y_dim, Clock *_clk_instance)
{
	this->pu_array_ptr = _pu_array_ptr;
	this->clk_instance = _clk_instance;
	this->x_dim = _x_dim;
	this->y_dim = _y_dim;
	this->available = this->x_dim * this->y_dim;
}

void ResourceAdmin::start()
{
	//create threads
	pthread_create(&this->pu_exe_thread, NULL, ResourceAdmin::managing, (void *)this);
	//detach threads
	pthread_detach(this->pu_exe_thread);
}

void ResourceAdmin::add_iLet(ILet *new_iLet)
{
	pthread_mutex_lock(&this->ilet_mutex);
	this->incomming_ilets.push(new_iLet);
	pthread_mutex_unlock(&this->ilet_mutex);
}

JSON *ResourceAdmin::monitoring()
{
	JSON *array_info = new JSON;
	*array_info = JSON::array();

	JSON resource_admin_info = {
		{"Incomming_Ilets", this->incomming_ilets.size()},
		{"Waiting_Ilets", this->invaded_ilets.size()},
		{"Executing_Ilets", this->execute_ilets.size()},
		{"Max_Ilets", this->max_iLets}};

	array_info->push_back(resource_admin_info);

	for (int i = 0; i < this->x_dim; i++)
	{
		for (int j = 0; j < this->y_dim; j++)
		{
			JSON *pu_info_ptr = pu_array_ptr[i][j]->monitoring();
			array_info->push_back(*pu_info_ptr);
			delete pu_info_ptr;
		}
	}

	return array_info;
}

void ResourceAdmin::invade(int resources_amount, std::vector<coordinate> *resources, ILet *ilet)
{
	bool found = false;
	coordinate free_pu;
	for (int i = 0; i < this->x_dim; i++)
	{
		for (int j = 0; j < this->y_dim; j++)
		{
			if (this->pu_array_ptr[i][j]->get_state() == FREE)
			{
				free_pu = this->pu_array_ptr[i][j]->get_coodinate();
				dprintf("ResourceAdmin: Found a processor free coordenate (%d, %d)\n", free_pu.x, free_pu.y);
				found = true;
				break;
			}
		}
		if (found)
		{
			break;
		}
	}
	int invaded_resources = 0;
	found = false;
	for (int i = free_pu.x; i < this->x_dim; i++)
	{
		for (int j = free_pu.y; j < this->y_dim; j++)
		{
			coordinate new_pu = this->pu_array_ptr[i][j]->get_coodinate();
			resources->push_back(new_pu);
			this->pu_array_ptr[i][j]->invade(ilet);
			invaded_resources++;
			if (invaded_resources == resources_amount)
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			break;
		}
	}
	this->available -= resources_amount;
}

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

bool ResourceAdmin::verify_ilet(ILet *ilet)
{
	bool is_done = true;
	unsigned int resources = ilet->get_resources()->size();
	for (unsigned int i = 0; i < resources; i++)
	{
		coordinate position = ilet->get_resources()->at(i);
		if (this->pu_array_ptr[position.x][position.y]->get_state() == INFECTED)
		{
			is_done = false;
			break;
		}
	}
	return is_done;
}

void *ResourceAdmin::managing(void *obj)
{
	ResourceAdmin *current = (ResourceAdmin *)obj;
	dprintf("ResourceAdmin: The resource administrator is started.\n");
	pthread_mutex_t *clk_cycle_mutex = current->clk_instance->get_cycle_mutex_ptr();
	pthread_cond_t *clk_cycle_cond = current->clk_instance->get_cycle_cond_ptr();
	while (1)
	{

		pthread_cond_wait(clk_cycle_cond, clk_cycle_mutex);
		dprintf("ResourceAdmin: %s.\n", current->monitoring()->dump().c_str());

		ILet *current_ilet = NULL;

		if (current->incomming_ilets.size() > 0)
		{
			pthread_mutex_lock(&current->ilet_mutex);
			current_ilet = current->incomming_ilets.front();
			current->incomming_ilets.pop();
			pthread_mutex_unlock(&current->ilet_mutex);
			dprintf("ResourceAdmin: Managing incomming Ilet = %d.\n", current_ilet->get_id());
			if (current_ilet->get_state() == WAITING)
			{
				current_ilet->pop_operation();
			}
			if (current_ilet->get_current_operation()->get_parameter() <= current->available)
			{
				dprintf("ResourceAdmin: Found resources to Ilet = %d.\n", current_ilet->get_id());
				current_ilet->set_state(WAITING);
				current->invaded_ilets.push_back(current_ilet);
			}
			else
			{
				dprintf("ResourceAdmin: Not enough resources to Ilet = %d.\n", current_ilet->get_id());
				pthread_mutex_lock(&current->ilet_mutex);
				current_ilet->set_state(EXECUTING);
				current->incomming_ilets.push(current_ilet);
				pthread_mutex_unlock(&current->ilet_mutex);
			}
		}

		if (current->execute_ilets.size() > 0)
		{
			for (size_t i = 0; i < current->execute_ilets.size(); i++)
			{
				current_ilet = current->execute_ilets.at(i);
				switch (current_ilet->get_state())
				{
				case WAITING:
				{
					int start = current_ilet->execute_operation();
					if (start)
					{

						dprintf("ResourceAdmin: Infecting resources to Ilet = %d.\n", current_ilet->get_id());
						current->infect(current_ilet);
						#ifdef TEST
						unsigned int test_resources = current_ilet->get_resources()->size();
						bool test_is_infected = true;
						for (unsigned int i = 0; i < test_resources; i++)
						{
							coordinate position = current_ilet->get_resources()->at(i);
							if (current->pu_array_ptr[position.x][position.y]->get_state() != INFECTED)
							{
								test_is_infected = false;
								break;
							}
						}
						std::cout << "TEST[AMN-06]: "
								  << (test_is_infected ? "PASS" : "FAIL")
								  << std::endl;
						#endif
					}
				}
				break;

				case EXECUTING:
				{
					int terminate = current_ilet->finish_operation();
					if (!terminate)
					{
						dprintf("ResourceAdmin: Ilet = %d to be terminated.\n", current_ilet->get_id());
						current_ilet->set_state(DONE);
					}
					else if (current_ilet->get_current_operation()->get_operation() == INFECT)
					{
						bool is_done = current->verify_ilet(current_ilet);
						if (is_done)
						{
							dprintf("ResourceAdmin: Ilet = %d is done.\n", current_ilet->get_id());
							current_ilet->set_state(DONE);
						}
					}
				}
				break;

				case DONE:
				{
					if (current_ilet->get_current_operation()->get_operation() == RETREAT)
					{
						dprintf("ResourceAdmin: Ilet = %d terminated.\n", current_ilet->get_id());
						current->retreat(current_ilet);
						current->execute_ilets.erase(current->execute_ilets.begin() + i);
					}
					else
					{
						current_ilet->pop_operation();
						if (current_ilet->get_current_operation()->get_operation() == RETREAT)
						{
							current_ilet->set_state(DONE);
						}
						else if (current_ilet->get_current_operation()->get_operation() == INVADE)
						{
							current_ilet->set_state(WAITING);
							current->invaded_ilets.push_back(current_ilet);
							current->execute_ilets.erase(current->execute_ilets.begin() + i);
						}
						else
						{
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

		if (current->invaded_ilets.size() > 0)
		{

			for (size_t i = 0; i < current->invaded_ilets.size(); i++)
			{
				current_ilet = current->invaded_ilets.at(i);
				current->invade(current_ilet->get_current_operation()->get_parameter(),
								current_ilet->get_resources(),
								current_ilet);

				current_ilet->pop_operation();
				if (current_ilet->get_current_operation()->get_operation() != INVADE)
				{
					current->execute_ilets.push_back(current_ilet);
					current->invaded_ilets.erase(current->invaded_ilets.begin() + i);
				}
			}
		}
	}
	return NULL;
}