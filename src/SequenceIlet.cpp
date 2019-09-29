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
void SequenceIlet::set_generation_parameters(int _max_clocks, int _max_loads, float _max_resources)
{
    this->max_clocks = _max_clocks;
    this->max_loads = _max_loads;
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
    this->max_loads = MAX_LOADS;
    this->max_resources = float(this->manycore_ptr->get_procs()) * float(MAX_RESOURCES);
}

/**
 * @brief Function that generates a new iLet
 * 
 * @param index 
 * @return ILet* 
 */
ILet *SequenceIlet::generate_ilet(int index, std::vector<std::string> codeFlow)
{
    //Generate a iLet according to the parameters
    ILet *new_ilet = new ILet(NORMAL, index, this->decision_probability);

    // HERE WE NEED TO CHANGE THE
    int resources = rand() % (this->max_resources + 1) + 1;
    new_ilet->add_operation(INVADE, resources, codeFlow); // add operation invade

    //int load = rand() % (this->max_loads + 1) + 1;
    int load = codeFlow.size();
    new_ilet->add_operation(INFECT, load, codeFlow); // add operation infect

    new_ilet->add_operation(RETREAT, 0, codeFlow); // add operation retreat

    //Store in info json
    JSON ilet_info = {
        {"Id", index},
        {"Operations", {{{"Operation", STRING_OPERATIONS[INVADE]}, {"Parameter", resources}}, {{"Operation", STRING_OPERATIONS[INFECT]}, {"Parameter", load}, {"FirstInst", codeFlow[0]}}, {{"Operation", STRING_OPERATIONS[RETREAT]}, {"Parameter", 0}}}}};
    //Set data in pointer
    *this->ilets_info = ilet_info;
    //Set flag that an iLet has been created
    this->ilet_check = true;

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
    //Assign await clocks for generation of blocks
    int await_clocks_between_blocks = 0;
    // to manipulate the ilets
    int go_block_ilets = -1;
    int go_block_ilets_count = 0;

    std::vector<std::vector<std::vector<std::string>>> iletsCode = current->getBlocksCode();
    int iletsCount = iletsCode[0].size(); // temporal code where number of blocks == ilets

    while (1)
    {
        //Await clock signal
        pthread_cond_wait(clk_cycle_cond, clk_cycle_mutex);

        //Verify if there are no clocks to wait
        if (await_clocks == 0)
        {
            //Verify if max amount of iLet in manycore
            if ((current->created_ilets.size() <= current->manycore_ptr->get_max_ilets()) && (go_block_ilets_count < iletsCount))
            {
                if (await_clocks_between_blocks == 0)
                {
                    go_block_ilets++; // go to next block of ilets
                    await_clocks_between_blocks = current->calcBlocks(iletsCode[go_block_ilets]);
                    iletsCount = iletsCode[go_block_ilets].size();
                    go_block_ilets_count = 0;
                }

                //Create an iLet and invade in manycore
                ILet *new_ilet = current->generate_ilet(i, iletsCode[go_block_ilets][go_block_ilets_count]); // change here
                current->created_ilets.push_back(new_ilet);
                current->manycore_ptr->invade(new_ilet);
                i++;
                go_block_ilets_count++;
                //generate await clocks
                await_clocks = rand() % (current->max_clocks + 1);
                // add the await clocks between two ilets
                await_clocks_between_blocks = await_clocks_between_blocks + await_clocks;
            }
        }
        else
        {
            //Discount clock
            await_clocks--;
            await_clocks_between_blocks--;
        }
    }
    return NULL;
}

std::vector<std::vector<std::vector<std::string>>> SequenceIlet::getBlocksCode()
{
    pugi::xml_document doc;
    doc.load_file("/home/gabriel/Documents/Proyectos/Invasim/src/flowAnalyzer/analyzerResults/flow.xml");
    pugi::xml_node blocks = doc.child("Blocks");
    std::vector<std::vector<std::vector<std::string>>> iletsCode;
    
    for (pugi::xml_node block = blocks.first_child(); block; block = block.next_sibling()) // go over blocks
    {
        std::vector<std::vector<std::string>> temporalBlock;
        for (pugi::xml_node ilet = block.first_child(); ilet; ilet = ilet.next_sibling()) // go over instructions of blocks
        {
            std::vector<std::string> temporalIlet;
            for (pugi::xml_node instruction = ilet.first_child(); instruction; instruction = instruction.next_sibling()) // go over instructions of blocks
            {
                std::string nodeName = instruction.name();
                if (nodeName == "instruction")
                {
                    temporalIlet.push_back((std::string)instruction.first_child().value()); // push instruction to temporal list
                }
            }
            std::reverse(std::begin(temporalIlet), std::end(temporalIlet)); // reverse because processing unit go back on instructions
            temporalBlock.push_back(temporalIlet);
        }
        iletsCode.push_back(temporalBlock); // push the vector of charts to principal list
    }
    return iletsCode;
}

int SequenceIlet::calcBlocks(std::vector<std::vector<std::string>> calcBlock)
{
    return 4;
}