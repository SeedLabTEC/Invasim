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

std::vector<coordinate> ResourceAdmin::free_sides(coordinate pu_free)
{
}

void ResourceAdmin::invade(int resources_amount, std::vector<coordinate> *resources, ILet *ilet)
{
    for (int i = 0; i < this->x_dim; i++)
    {
        for (int j = 0; j < this->y_dim; j++)
        {
            if (this->pu_array_ptr[i][j]->get_state() == FREE)
            {
                coordinate free_pu = this->pu_array_ptr[i][j]->get_coodinate();
                dprintf("ResourceAdmin: Found a processor free coordenate (%d, %d)\n", free_pu.x, free_pu.y);
                resources->push_back(free_pu);
                this->pu_array_ptr[i][j]->invade(ilet);
            }
        }
    }
}

void ResourceAdmin::infect(ILet *ilet)
{
    ilet->set_state(EXECUTING);
}

void ResourceAdmin::retread(ILet *ilet)
{
    unsigned int resoruces = ilet->get_resources()->size();
    for(unsigned int i = 0; i < resoruces; i++)
    {
        coordinate position = ilet->get_resources()->at(i);
        this->pu_array_ptr[position.x][position.y]->free_processor();
    }
    this->available += resoruces;
}

JSON *ResourceAdmin::monitoring()
{
    JSON *array_info = new JSON;
    *array_info = JSON::array();

    JSON resource_admin_info = {
        {"Current_Ilets", this->incomming_ilets.size()},
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
        /*
        ILet *current_ilet = NULL;
        if (current->incomming_ilets.size() > 0)
        {
            pthread_mutex_lock(&current->ilet_mutex);
            current_ilet = current->incomming_ilets.front();
            current->incomming_ilets.pop();
            pthread_mutex_unlock(&current->ilet_mutex);

            current_ilet->pop_operation();
            if (current_ilet->get_current_operation()->get_parameter() <= current->available)
            {
                current->invaded_ilets.push_back(current_ilet);
            }
            else
            {
                pthread_mutex_lock(&current->ilet_mutex);
                current->incomming_ilets.push(current_ilet);
                pthread_mutex_unlock(&current->ilet_mutex);
            }
        }

        if (current->infected_ilets.size() > 0)
        {
            for (size_t i = 0; i < current->infected_ilets.size(); i++)
            {
                current_ilet = current->infected_ilets.at(i);
                switch (current_ilet->get_state())
                {
                case WAITING:
                {
                    int start = current_ilet->execute_operation();
                    if (start)
                    {
                        current->infect(current_ilet);
                    }
                }
                break;

                case EXECUTING:
                {
                    int terminate = current_ilet->finish_operation();
                    if (terminate)
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
                            current->infected_ilets.erase(current->infected_ilets.begin() + i);
                        }
                        else
                        {
                            current_ilet->set_state(WAITING);
                        }
                    }
                }
                break;

                case DONE:
                {
                    current->retread(current_ilet);
                    delete current_ilet;
                    current->infected_ilets.erase(current->infected_ilets.begin() + i);
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
                    current->infected_ilets.push_back(current_ilet);
                    current->invaded_ilets.erase(current->invaded_ilets.begin() + i);
                }
            }
        }
        */
    }
    return NULL;
}