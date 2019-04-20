/**
* @file ManyCoreArch.cpp
* @brief Description
* @author Dennis Porras Barrantes
* @date 27/03/19
**/

#include "../include/ManyCoreArch.h"

/**
* @brief Constructor
**/
ManyCoreArch::ManyCoreArch(int _x_dim, int _y_dim, Clock *_clk_instance)
{
    dprintf("MANYCOREARCH: Manycore Architecture instance created.\n\t- Dimension: (%d, %d).\n", _x_dim, _y_dim);
    this->init(_x_dim, _y_dim, _clk_instance);
    this->resource_manager = new ResourceAdmin(this->pu_array, this->x_dim,
                                               this->y_dim, this->clk_instance);
    this->max_ilets = DEFAULT_MAX_ILETS;
}

ManyCoreArch::ManyCoreArch(int _x_dim, int _y_dim, Clock *_clk_instance, int _max_ilets)
{
    dprintf("MANYCOREARCH: Manycore Architecture instance created.\n\t- Dimension: (%d, %d).\n", _x_dim, _y_dim);
    this->init(_x_dim, _y_dim, _clk_instance);
    this->resource_manager = new ResourceAdmin(this->pu_array, this->x_dim,
                                               this->y_dim, _max_ilets, 
                                               this->clk_instance);
    this->max_ilets = _max_ilets;
}

void ManyCoreArch::start()
{
    dprintf("MANYCOREARCH: Starting processing units.\n");
    for (int i = 0; i < this->x_dim; i++)
    {
        for (int j = 0; j < this->y_dim; j++)
        {
            this->pu_array[i][j]->start();
        }
    }
    this->resource_manager->start();
}

void ManyCoreArch::invade(ILet *new_iLet)
{
    this->resource_manager->add_iLet(new_iLet);
}

int ManyCoreArch::get_procs()
{
    return this->x_dim * this->y_dim;
}

int ManyCoreArch::get_max_ilets()
{
    return this->max_ilets;
}

JSON *ManyCoreArch::monitoring()
{
    JSON *arch_info = new JSON;
    JSON *resources_info = this->resource_manager->monitoring();
    *arch_info = {
        {"System",
         {{"Processor",
           {{"x", this->x_dim}, {"y", this->y_dim}}},
          {"Cycle", this->clk_instance->get_cycle()}}},
        {"Components", *resources_info}};
    delete resources_info;
    return arch_info;
}

void ManyCoreArch::init(int _x_dim, int _y_dim, Clock *_clk_instance)
{
    this->pu_array = new ProcessingUnit **[_x_dim];

    dprintf("MANYCOREARCH: Instanciating processing units in matrix.\n");
    for (int i = 0; i < _x_dim; i++)
    {
        this->pu_array[i] = new ProcessingUnit *[_y_dim];
        for (int j = 0; j < _y_dim; j++)
        {
            this->pu_array[i][j] = new ProcessingUnit(i, j, _clk_instance);
        }
    }

    this->x_dim = _x_dim;
    this->y_dim = _y_dim;
    this->clk_instance = _clk_instance;
    this->ram = new RandomAccessMemory();
}