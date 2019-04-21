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
SequenceIlet::SequenceIlet(Clock *_clk_instance, ManyCoreArch *_manycore_ptr, float _decision_probability)
{
    this->seq_type = RANDOM;
    this->init(_clk_instance, _manycore_ptr, _decision_probability);
}

SequenceIlet::SequenceIlet(Sequence_Type _seq_type, Clock *_clk_instance, ManyCoreArch *_manycore_ptr, float _decision_probability)
{
    this->seq_type = _seq_type;
    this->init(_clk_instance, _manycore_ptr, _decision_probability);
}

void SequenceIlet::start()
{
    //create threads
    pthread_create(&this->seq_thread, NULL, SequenceIlet::generate, (void *)this);
    //detach threads
    pthread_detach(this->seq_thread);
}

void SequenceIlet::init(Clock *_clk_instance, ManyCoreArch *_manycore_ptr, float _decision_probability)
{
    this->decision_probability = _decision_probability;
    this->clk_instance = _clk_instance;
    this->manycore_ptr = _manycore_ptr;
}

void *SequenceIlet::generate(void *obj)
{
    SequenceIlet *current = (SequenceIlet *)obj;
    dprintf("SequenceIlet: Ilet sequencer started.\n");
    pthread_mutex_t *clk_cycle_mutex = current->clk_instance->get_cycle_mutex_ptr();
    pthread_cond_t *clk_cycle_cond = current->clk_instance->get_cycle_cond_ptr();
    int i = 0;
    while (1)
    {
        pthread_cond_wait(clk_cycle_cond, clk_cycle_mutex);

        if (current->created_ilets.size() <= current->manycore_ptr->get_max_ilets() && i < 3)
        {

            ILet *new_ilet = new ILet(NORMAL, i, current->decision_probability);
            new_ilet->add_operation(INVADE, 4);
            new_ilet->add_operation(INFECT, 1);
            new_ilet->add_operation(RETREAT, 0);
            current->created_ilets.push_back(new_ilet);
            current->manycore_ptr->invade(new_ilet);
            i++;
        }
    }
    return NULL;
}