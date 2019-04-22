/**
* @file SequenceIlet.cpp
* @brief Description
* @author Dennis Porras Barrantes
* @date 19/04/19
**/

#include "../include/SequenceIlet.h"

/**
* @brief Constructor
**/
SequenceIlet::SequenceIlet(Clock *_clk_instance, ManyCoreArch *_manycore_ptr, float _decision_probability, int _seed)
{
    this->seq_type = RANDOM;
    this->init(_clk_instance, _manycore_ptr, _decision_probability, _seed);
}

SequenceIlet::SequenceIlet(Sequence_Type _seq_type, Clock *_clk_instance, ManyCoreArch *_manycore_ptr, float _decision_probability, int _seed)
{
    this->seq_type = _seq_type;
    this->init(_clk_instance, _manycore_ptr, _decision_probability, _seed);
}

void SequenceIlet::set_generation_parameters(int _max_clocks, int _max_infections, int _max_invasions, int _max_loads, float _max_resources)
{
    this->max_clocks = _max_clocks;
    this->max_infections = _max_infections;
    this->max_invasions = _max_invasions;
    this->max_loads = _max_loads;
    this->max_resources = float(this->manycore_ptr->get_procs()) * _max_resources;
}

void SequenceIlet::start()
{
    //create threads
    pthread_create(&this->seq_thread, NULL, SequenceIlet::generate, (void *)this);
    //detach threads
    pthread_detach(this->seq_thread);
}

JSON *SequenceIlet::monitoring()
{
    JSON *array_info = new JSON;
    *array_info = JSON::array();

    for (size_t i = 0; i < this->created_ilets.size(); i++)
    {
        ILet *current_ilet = this->created_ilets.at(i);
        JSON ilet_info = {
            {"Id", current_ilet->get_id()},
            {"Current_operation", STRING_OPERATIONS[current_ilet->get_current_operation()->get_operation()]},
            {"Assigned_resources", current_ilet->get_resources()->size()}};
        array_info->push_back(ilet_info);
    }

    return array_info;
}

void SequenceIlet::init(Clock *_clk_instance, ManyCoreArch *_manycore_ptr, float _decision_probability, int _seed)
{
    this->seed = _seed;
    srand(this->seed);
    this->decision_probability = _decision_probability;
    this->clk_instance = _clk_instance;
    this->manycore_ptr = _manycore_ptr;

    this->max_clocks = MAX_CLOCKS;
    this->max_infections = MAX_INFECTIONS;
    this->max_invasions = MAX_INVASIONS;
    this->max_loads = MAX_LOADS;
    this->max_resources = float(this->manycore_ptr->get_procs()) * float(MAX_RESOURCES);
}

ILet *SequenceIlet::generate_ilet(int index)
{
    ILet *new_ilet = new ILet(NORMAL, index, this->decision_probability);
    int invasions = rand() % (this->max_invasions + 1) + 1;   // [1, max]
    int infections = rand() % (this->max_infections + 1) + 1; // [1, max]
    int end = invasions <= infections ? infections : invasions;
    for (int i = 0; i < end; i++)
    {
        if (invasions > 0)
        {
            int resources = rand() % (this->max_resources + 1) + 1;
            new_ilet->add_operation(INVADE, resources);
            invasions--;
        }

        if (infections > 0)
        {
            int load = rand() % (this->max_loads + 1) + 1;
            new_ilet->add_operation(INFECT, load);
            infections--;
        }
    }
    new_ilet->add_operation(RETREAT, 0);
    return new_ilet;
}

void *SequenceIlet::generate(void *obj)
{
    SequenceIlet *current = (SequenceIlet *)obj;
    dprintf("SequenceIlet: Ilet sequencer started.\n");
    pthread_mutex_t *clk_cycle_mutex = current->clk_instance->get_cycle_mutex_ptr();
    pthread_cond_t *clk_cycle_cond = current->clk_instance->get_cycle_cond_ptr();
    int i = 0;
    int await_clocks = 0;
    while (1)
    {
        pthread_cond_wait(clk_cycle_cond, clk_cycle_mutex);
        if (await_clocks == 0)
        {
            if (current->created_ilets.size() <= current->manycore_ptr->get_max_ilets())
            {
                ILet *new_ilet = current->generate_ilet(i);
                current->created_ilets.push_back(new_ilet);
                current->manycore_ptr->invade(new_ilet);
                i++;
                await_clocks = rand() % (current->max_clocks + 1);
            }
        }
    }
    return NULL;
}