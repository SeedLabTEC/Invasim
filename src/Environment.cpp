/**
* @file Environment.cpp
* @brief Environmnet source
* @author Dennis Porras Barrantes
* @date 09/02/19
**/

#include "../include/Environment.h"
/**
 * @brief Construct a new Environment:: Environment object
 * 
 */
Environment::Environment()
{
    dprintf("ENVIRONMENT: Environment created.\n\t- Cores: %d.\n", DEFAULT_CORES);
    this->ai = true;
    this->x_dim = DEFAULT_CORES;
    this->y_dim = DEFAULT_CORES;
    this->decision_probability = DEFAULT_PROBABILITY;
    this->seed = DEFAULT_SEED;
    
    this->intNet = new InterconnectionNetwork();
    res_thread_requests=pthread_create(&thread_requests, NULL, (THREADFUNCPTR) &InterconnectionNetwork::consumeRequest, intNet);
	if(res_thread_requests!=0){
		perror("pthread_create error");
		exit(1);
	}

	res_thread_events=pthread_create(&thread_events, NULL, (THREADFUNCPTR) &InterconnectionNetwork::consumeEvent, intNet);
	if(res_thread_events!=0){
		perror("pthread_create error");
		exit(1);
    }
    char path_files[PATH_MAX];
    getcwd(path_files, PATH_MAX);
    this->init(path_files);
    this->env_monitor = new Monitor(this->many_core_instance, this->seq_ilet, this->clk_instance, this->intNet);
    this->write_params();
}

/**
 * @brief Construct a new Environment:: Environment object
 * 
 * @param _x_dim dimension
 * @param _y_dim dimension
 * @param _decision_probability iLet decision
 * @param _working_dir working directory
 * @param _seed to generate random numbers
 */
Environment::Environment(int _x_dim, int _y_dim, float _decision_probability, int ai, std::string _working_dir, int _seed)
{
    dprintf("ENVIRONMENT: Environment created.\n\t- Cores: (%d, %d).\n", _x_dim, _y_dim);
    if (_x_dim * _y_dim > 1000)
    {
        std::cerr << "ERROR: Processing units can't exceed 1000." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    this->ai = ai;
    this->x_dim = _x_dim;
    this->y_dim = _y_dim;
    this->decision_probability = _decision_probability;
    this->seed = _seed;
    dprintf("ENVIRONMENT: Instanciating interconnection network.\n");
    this->intNet = new InterconnectionNetwork();
    res_thread_requests=pthread_create(&thread_requests, NULL, (THREADFUNCPTR) &InterconnectionNetwork::consumeRequest, intNet);
    if(res_thread_requests!=0){
        perror("pthread_create error");
        exit(1);
    }

    res_thread_events=pthread_create(&thread_events, NULL, (THREADFUNCPTR) &InterconnectionNetwork::consumeEvent, intNet);
    if(res_thread_events!=0){
        perror("pthread_create error");
        exit(1);
    }

    this->init(_working_dir);
    this->env_monitor = new Monitor(this->many_core_instance, this->seq_ilet , _working_dir, this->clk_instance, this->intNet);
    this->write_params();
}

/**
 * @brief Function that initialize the components of environment.
 * 
 */
void Environment::init(std::string _working_dir)
{
    dprintf("ENVIRONMENT: Instanciating environment clock.\n");
    this->clk_instance = new Clock();
    dprintf("ENVIRONMENT: Instanciating Many Core Architecture.\n");
    this->many_core_instance = new ManyCoreArch(this->x_dim, this->y_dim, ai, this->clk_instance, this->intNet);
    this->seq_ilet = new SequenceIlet(this->clk_instance, this->many_core_instance, this->decision_probability, this->seed, _working_dir);
}

/**
 * @brief Function that starts the components of the system
 * 
 */
void Environment::start_environment()
{
    dprintf("ENVIRONMENT: Starting environment components.\n");
    this->many_core_instance->start();
    //Wait for components to start
    std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_SEC));
    this->seq_ilet->start();
    this->env_monitor->start();

}

/**
 * @brief Function to advance in time
 * 
 * @param steps 
 */
void Environment::step(int steps)
{
    for (int i = 0; i < steps; i++)
    {
        this->clk_instance->next_cycle();
    }
}

/**
 * @brief Funtion to write the parameters of environment in disk
 * 
 */
void Environment::write_params()
{
    //Create path
    std::string path = "";
    path.append(this->env_monitor->get_working_dir());
    path.append(PARAMS_FILE);

    //Params json
    JSON params = {
        {"x", this->x_dim},
        {"y", this->y_dim},
        {"probability", this->decision_probability},
        {"seed", this->seed},
        {"working_dir", this->env_monitor->get_working_dir()}
    };

    this->env_monitor->write_disk(path, params, false);
}
