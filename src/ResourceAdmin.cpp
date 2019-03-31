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
}

void ResourceAdmin::start()
{
    //create threads
    pthread_create(&this->pu_exe_thread, NULL, ResourceAdmin::managing, (void *)this);
    //detach threads
    pthread_detach(this->pu_exe_thread);
}

void ResourceAdmin::add_iLet(ILet * new_iLet)
{
    pthread_mutex_lock(&this->ilet_mutex);
    this->iLet_queue.push(new_iLet);
    pthread_mutex_unlock(&this->ilet_mutex);
}

std::vector<coordinate> ResourceAdmin::invade()
{
    std::vector<coordinate> ret;

    for(int i = 0; i < this->x_dim; i++)
    {
        for(int j = 0; j < this->y_dim; j++)
        {
            if (this->pu_array_ptr[i][j]->get_state() == FREE)
            {
                coordinate free_pu = this->pu_array_ptr[i][j]->get_coodinate();
                dprintf("ResourceAdmin: Found a processor free coordenate (%d, %d)\n", free_pu.x, free_pu.y);
                return ret;
            }
        }
        
    }
    

    return ret;
}

void ResourceAdmin::infect()
{
}

void ResourceAdmin::retread()
{
}

JSON *ResourceAdmin::monitoring()
{
    JSON *array_info = new JSON;
    *array_info = JSON::array();
    
    JSON resource_admin_info = {
        {"Current_Ilets", this->iLet_queue.size()},
        {"Max_Ilets", this->max_iLets}
    };

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
        //dprintf("ResourceAdmin: %s.\n", current->monitoring()->dump(4).c_str());
        current->invade();
    }
    return NULL;
}