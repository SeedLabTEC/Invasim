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
    this->x_dim = DEFAULT_CORES;
    this->y_dim = DEFAULT_CORES;
    this->decision_probability = DEFAULT_PROBABILITY;
    this->seed = DEFAULT_SEED;
    this->init();
    this->env_monitor = new Monitor(this->many_core_instance, this->seq_ilet, this->clk_instance);
}

/**
 * @brief 
**/
Environment::Environment(int _x_dim, int _y_dim, float _decision_probability, std::string _working_dir, int _seed)
{
    dprintf("ENVIRONMENT: Environment created.\n\t- Cores: (%d, %d).\n", _x_dim, _y_dim);
    if (_x_dim * _y_dim > 1000)
    {
        std::cerr << "ERROR: Processing units can't exceed 1000." << std::endl;
        exit(EXIT_FAILURE);
    }

    this->x_dim = _x_dim;
    this->y_dim = _y_dim;
    this->decision_probability = _decision_probability;
    this->seed = _seed;
    this->init();
    this->env_monitor = new Monitor(this->many_core_instance, this->seq_ilet, _working_dir, this->clk_instance);
}

/**
 * @brief
 * */
void Environment::init()
{
    dprintf("ENVIRONMENT: Instanciating environment clock.\n");
    this->clk_instance = new Clock();
    dprintf("ENVIRONMENT: Instanciating Many Core Architecture.\n");
    this->many_core_instance = new ManyCoreArch(this->x_dim, this->y_dim, this->clk_instance);
    this->seq_ilet = new SequenceIlet(this->clk_instance, this->many_core_instance, this->decision_probability, this->seed);
}

/**
 * @brief
 * */
void Environment::start_environment()
{
    #ifdef TEST
    if (this->x_dim * this->y_dim <= 1000 && this->many_core_instance->get_procs() <= 1000)
    {
        std::cout << "TEST[AMN-02]: PASS" << std::endl;
    }
    else
    {
        std::cout << "TEST[AMN-02]: FAIL" << std::endl;
    }
    #endif
    
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