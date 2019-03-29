/**
* @file Environment.cpp
* @brief Description
* @author Dennis Porras Barrantes
* @date 09/02/19
**/

#include "../include/Environment.h"

/**
* @brief Constructor
**/
Environment::Environment()
{
    dprintf("ENVIRONMENT: Environment created.\n\t- Cores: %d.\n\n", DEFAULT_CORES);
    this->cpu_cores = DEFAULT_CORES;
    this->init();
}

/**
 * @brief 
**/
Environment::Environment(int _cpu_cores)
{
    dprintf("ENVIRONMENT: Environment created.\n\t- Cores: %d.\n\n", _cpu_cores);
    this->cpu_cores = _cpu_cores;
    this->init();
}

/**
 * @brief
 * */
void Environment::init()
{
    dprintf("ENVIRONMENT: Instanciating environment clock.\n");
    this->clk_instance = new Clock();
    dprintf("ENVIRONMENT: Instanciating Many Core Architecture.\n");
    this->many_core_instance = new ManyCoreArch(this->cpu_cores, this->cpu_cores, this->clk_instance);
}

/**
 * @brief
 * */
void Environment::start_environment()
{
    dprintf("ENVIRONMENT: Starting processing units.");
    this->many_core_instance->start();
}

/**
 * @brief
 * */
void Environment::step(int steps)
{
    for (int i = 0; i < steps; i++)
    {
        this->clk_instance->next_cycle();
    }
}

/**
 * @brief 
**/
int Environment::get_cpu_cores()
{
    return this->cpu_cores;
}

/**
 * @brief 
**/
void Environment::set_cpu_cores(int _cpu_cores)
{
    this->cpu_cores = _cpu_cores;
}