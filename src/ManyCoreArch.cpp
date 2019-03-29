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
ManyCoreArch::ManyCoreArch(int _x_dim, int _y_dim, Clock * _clk_instance)
{
    dprintf("MANYCOREARCH: Manycore Architecture instance created.\n\t- Dimension: (%d, %d).\n\n", _x_dim, _y_dim);
    
    this->pu_array = new ProcessingUnit**[_x_dim];

    dprintf("MANYCOREARCH: Instanciating processing units in matrix.\n");
    int id_gen = 0;
    for(int i = 0; i < _x_dim; i++)
    {
        this->pu_array[i] = new ProcessingUnit *[_y_dim];
        for(int j = 0; j < _y_dim; j++)
        {
            this->pu_array[i][j] = new ProcessingUnit(id_gen, _clk_instance);
            id_gen++;
        }

    } 

    this->x_dim = _x_dim;
    this->y_dim = _y_dim;
    this->clk_instance = _clk_instance;  
    this->ram = new RandomAccessMemory();

}

void ManyCoreArch::start()
{
    dprintf("MANYCOREARCH: Starting processing units.");
    for(int i = 0; i < this->x_dim; i++)
    {
        for(int j = 0; j < this->y_dim; j++)
        {
            this->pu_array[i][j]->start();
        }
        
    }
    
}

std::vector<int> ManyCoreArch::invade(ILet * new_ilet)
{
    std::vector<int> ret;
    return ret;
}

void ManyCoreArch::infect(ILet * new_ilet)
{

}

void ManyCoreArch::retread(ILet * invaded_ilet)
{

}

JSON * ManyCoreArch::monitoring()
{
    JSON * json_info = new JSON;
	*json_info = {
			{"ID", 1},
			{"State", "In Progress..."}
	};
	return json_info;
}