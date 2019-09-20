/**
* @file SequenceIlet.cpp
* @brief iLet sequencer source
* @author Dennis Porras Barrantes
* @date 19/04/19
**/

#include "../include/SequenceIlet.h"

/**
 * @brief Construct a new Sequence Ilet:: Sequence Ilet object
 * 
 * @param _clk_instance 
 * @param _manycore_ptr 
 * @param _decision_probability 
 * @param _seed 
 */
SequenceIlet::SequenceIlet(Clock *_clk_instance, ManyCoreArch *_manycore_ptr, float _decision_probability, int _seed)
{
    this->seq_type = RANDOM;
    this->init(_clk_instance, _manycore_ptr, _decision_probability, _seed);
}

/**
 * @brief Construct a new Sequence Ilet:: Sequence Ilet object
 * 
 * @param _seq_type 
 * @param _clk_instance 
 * @param _manycore_ptr 
 * @param _decision_probability 
 * @param _seed 
 */
SequenceIlet::SequenceIlet(Sequence_Type _seq_type, Clock *_clk_instance, ManyCoreArch *_manycore_ptr, float _decision_probability, int _seed)
{
    this->seq_type = _seq_type;
    this->init(_clk_instance, _manycore_ptr, _decision_probability, _seed);
}

/**
 * @brief Function that sets the generation of iLet parameters
 * 
 * @param _max_clocks 
 * @param _max_loads 
 * @param _max_resources 
 */
void SequenceIlet::set_generation_parameters(int _max_clocks, float _max_resources)
{
    this->max_clocks = _max_clocks;
    this->max_resources = float(this->manycore_ptr->get_procs()) * _max_resources;
}

/**
 * @brief Function that starts the thread
 * 
 */
void SequenceIlet::start()
{
    //create threads
    pthread_create(&this->seq_thread, NULL, SequenceIlet::generate, (void *)this);
    //detach threads
    pthread_detach(this->seq_thread);
}

/**
 * @brief Function that gets the information of the generated iLets
 * 
 * @return JSON* 
 */
JSON *SequenceIlet::monitoring()
{
    JSON *array_info = new JSON;
    *array_info = JSON::array();

    //Check if there are any new iLet
    if (this->ilet_check)
    {
        array_info->push_back(*this->ilets_info);
        this->ilet_check = false;
    }

    return array_info;
}

/**
 * @brief Function that initialize the components and pointers
 * 
 * @param _clk_instance 
 * @param _manycore_ptr 
 * @param _decision_probability 
 * @param _seed 
 */
void SequenceIlet::init(Clock *_clk_instance, ManyCoreArch *_manycore_ptr, float _decision_probability, int _seed)
{
    this->seed = _seed;
    srand(this->seed);
    this->decision_probability = _decision_probability;
    this->clk_instance = _clk_instance;
    this->manycore_ptr = _manycore_ptr;
    this->ilets_info = new JSON;
    this->max_clocks = MAX_CLOCKS;
    this->max_resources = float(this->manycore_ptr->get_procs()) * float(MAX_RESOURCES);

    this->load_programs();
}

/**
 * @brief Hacer xD
 * 
 **/
void SequenceIlet::load_programs()
{
    for (unsigned int i = 0; i < STRING_PROGRAMS.size(); i++)
    {
        std::string bin_file_path = BENCHMARK + STRING_PROGRAMS.at(i);
        std::ifstream ifd(bin_file_path, std::ios::binary | std::ios::ate);
        int size = ifd.tellg();
        ifd.seekg(0, std::ios::beg);
        std::vector<char> * buffer = new std::vector<char>();
        buffer->resize(size); // << resize not reserve
        ifd.read(buffer->data(), size);

        this->programs.push_back(buffer);
    }
}

/**
 * @brief Function that generates a new iLet
 * 
 * @param index 
 * @return ILet* 
 */
ILet *SequenceIlet::generate_ilet(int index)
{
    //Generate a iLet according to the parameters
    ILet *new_ilet = new ILet(NORMAL, index, this->decision_probability);
    int resources = rand() % (this->max_resources + 1) + 1;
    new_ilet->add_operation(INVADE, resources);
    int program_index = rand() % this->programs.size();
    new_ilet->add_operation(INFECT, this->programs.at(program_index));
    new_ilet->add_operation(RETREAT, 0);

    //Store in info json
    JSON ilet_info = {
        {"Id", index},
        {"Operations", {{{"Operation", STRING_OPERATIONS[INVADE]}, {"Parameter", resources}}, {{"Operation", STRING_OPERATIONS[INFECT]}, {"Parameter", STRING_PROGRAMS[program_index]}}, {{"Operation", STRING_OPERATIONS[RETREAT]}, {"Parameter", 0}}}}};
    //Set data in pointer
    *this->ilets_info = ilet_info;
    //Set flag that an iLet has been created
    this->ilet_check = true;
    std::cout << "New iLet: " << ilet_info.dump(4) << std::endl;
    return new_ilet;
}

/**
 * @brief Executing thread function that generates and execute iLets in manycore architecture
 * 
 * @param obj 
 * @return void* 
 */
void *SequenceIlet::generate(void *obj)
{
    SequenceIlet *current = (SequenceIlet *)obj;
    dprintf("SequenceIlet: Ilet sequencer started.\n");
    //Get clock mutex and conditional variable
    pthread_mutex_t *clk_cycle_mutex = current->clk_instance->get_cycle_mutex_ptr();
    pthread_cond_t *clk_cycle_cond = current->clk_instance->get_cycle_cond_ptr();
    //Counter to assign identifier
    int i = 0;
    //Assign await clocks for generation
    int await_clocks = 0;
    while (1)
    {
        //Await clock signal
        pthread_cond_wait(clk_cycle_cond, clk_cycle_mutex);
        //Verify if there are no clocks to wait
        if (await_clocks == 0)
        {
            //Verify if max amount of iLet in manycore
            if (current->created_ilets.size() < 1)
            {
                //Create an iLet and invade in manycore
                ILet *new_ilet = current->generate_ilet(i);
                current->created_ilets.push_back(new_ilet);
                current->manycore_ptr->invade(new_ilet);
                i++;
                //generate await clocks
                await_clocks = rand() % (current->max_clocks + 1);
            }
        }
        else
        {
            //Discount clock
            await_clocks--;
        }
    }
    return NULL;
}