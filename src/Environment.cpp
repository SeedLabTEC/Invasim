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
    dprintf("ENVIRONMENT: Environment created.\n\t- Cores: %d.\n", DEFAULT_CORES);
    this->cpu_cores = DEFAULT_CORES;
    this->init();
}

/**
 * @brief 
**/
Environment::Environment(int _cpu_cores)
{
    dprintf("ENVIRONMENT: Environment created.\n\t- Cores: %d.\n", _cpu_cores);
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
    this->env_monitor = new Monitor(this->many_core_instance, "/home/dennis/Documents/Invasim/bin", this->clk_instance);
    this->seq_ilet = new SequenceIlet(this->clk_instance, this->many_core_instance);
}

/**
 * @brief
 * */
void Environment::start_environment()
{
    dprintf("ENVIRONMENT: Starting environment components.\n");
    this->many_core_instance->start();
    //Wait for components to start
    sleep(WAIT_SEC);
    this->seq_ilet->start();
    this->env_monitor->start();
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