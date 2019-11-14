/**
* @file ManyCoreArch.cpp
* @brief Manycore architecture source
* @author Dennis Porras Barrantes
* @date 27/03/19
**/

#include "../include/ManyCoreArch.h"

/**
 * @brief Construct a new Many Core Arch:: Many Core Arch object
 * 
 * @param _x_dim 
 * @param _y_dim 
 * @param _clk_instance 
 */
ManyCoreArch::ManyCoreArch(int _x_dim, int _y_dim, Clock *_clk_instance)
{
    dprintf("MANYCOREARCH: Manycore Architecture instance created.\n\t- Dimension: (%d, %d).\n", _x_dim, _y_dim);

    this->programs_registers = {};
    this->ptr_registers = &this->programs_registers;

    this->init(_x_dim, _y_dim, _clk_instance);
    this->resource_manager = new ResourceAdmin(this->pu_array, this->x_dim,
                                               this->y_dim, this->clk_instance);
    this->max_ilets = _x_dim * _y_dim;
}

/**
 * @brief Construct a new Many Core Arch:: Many Core Arch object
 * 
 * @param _x_dim 
 * @param _y_dim 
 * @param _clk_instance 
 * @param _max_ilets 
 */
ManyCoreArch::ManyCoreArch(int _x_dim, int _y_dim, Clock *_clk_instance, int _max_ilets)
{
    dprintf("MANYCOREARCH: Manycore Architecture instance created.\n\t- Dimension: (%d, %d).\n", _x_dim, _y_dim);
    this->programs_registers = {};
    this->ptr_registers = &this->programs_registers;

    this->init(_x_dim, _y_dim, _clk_instance);
    this->resource_manager = new ResourceAdmin(this->pu_array, this->x_dim,
                                               this->y_dim, _max_ilets,
                                               this->clk_instance);
    this->max_ilets = _x_dim * _y_dim;
}

/**
 * @brief Function that starts the processing unit and resource administrator
 * 
 */
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

/**
 * @brief Function that create a new JSON of registers for an program
 * 
 */
void ManyCoreArch::newRegisterJson()
{
    JSON nr = {{"zero", 0}, {"ra", 0}, {"sp", 0}, {"gp", 0}, {"tp", 0}, {"t0", 0}, {"t1", 0}, {"t2", 0}, {"s0", 0}, {"fp", 0}, {"s1", 0}, {"a0", 0}, {"a1", 0}, {"a2", 0}, {"a3", 0}, {"a4", 0}, {"a5", 0}, {"a6", 0}, {"a7", 0}, {"s2", 0}, {"s3", 0}, {"s4", 0}, {"s5", 0}, {"s6", 0}, {"s7", 0}, {"s8", 0}, {"s9", 0}, {"s10", 0}, {"s11", 0}, {"t3", 0}, {"t4", 0}, {"t5", 0}, {"t6", 0}};
    this->programs_registers.push_back(nr);
}

/**
 * @brief Function that invades resources from resource admin
 * 
 * @param new_iLet 
 */
void ManyCoreArch::invade(ILet *new_iLet)
{
    this->resource_manager->add_iLet(new_iLet);
}

/**
 * @brief Getter for the amoun of processing units
 * 
 * @return int 
 */
int ManyCoreArch::get_procs()
{
    return this->x_dim * this->y_dim;
}

/**
 * @brief Getter for the max amount of iLets
 * 
 * @return unsigned int 
 */
unsigned int ManyCoreArch::get_max_ilets()
{
    return this->max_ilets;
}

/**
 * @brief Function that gets the state of every component's state
 * 
 * @return JSON* with info
 */
JSON *ManyCoreArch::monitoring()
{
    //New json for info
    JSON *arch_info = new JSON;

    //Get resource admin and processing units info
    JSON *resources_info = this->resource_manager->monitoring();

    //Json contruciton
    *arch_info = {
        {"System",
         {{"Processor",
           {{"x", this->x_dim}, {"y", this->y_dim}}},
          {"Cycle", this->clk_instance->get_cycle()}}},
        {"Components", *resources_info}};
    //Deallocate useless memory
    delete resources_info;
    return arch_info;
}

/**
 * @brief Function that initialize components in system
 * 
 * @param _x_dim 
 * @param _y_dim 
 * @param _clk_instance 
 */
void ManyCoreArch::init(int _x_dim, int _y_dim, Clock *_clk_instance)
{
    this->pu_array = new ProcessingUnit **[_x_dim];

    dprintf("MANYCOREARCH: Instanciating processing units in matrix.\n");
    for (int i = 0; i < _x_dim; i++)
    {
        this->pu_array[i] = new ProcessingUnit *[_y_dim];
        for (int j = 0; j < _y_dim; j++)
        {
            this->pu_array[i][j] = new ProcessingUnit(i, j, _clk_instance, this->ptr_registers);
        }
    }

    this->x_dim = _x_dim;
    this->y_dim = _y_dim;
    this->clk_instance = _clk_instance;
    this->ram = new RandomAccessMemory();
}

/**
 * @brief Getter of list of ilets on invaded
 * 
 * @param obj 
 * @return std::vector<ILet *>
 */
std::vector<ILet *> ManyCoreArch::get_invaded()
{
    return this->resource_manager->get_invaded();
}

/**
 * @brief Request a variable priority for one ilet
 * 
 * @param iletID ID of ilet if we want to keep a control 
 * @param programID ID of program if we want to keep a control 
 * @return int Between 0-4
 */
int ManyCoreArch::getPriority(int iletID, int programID)
{
    return this->resource_manager->getPriority(iletID, programID);
}

/**
 * @brief Request for the resourses to use for Ilets
 * 
 * @param iletReq Quantity of resources required from ilet
 * @return int Random between 1 to quantity of processors
 */
int ManyCoreArch::getResourcesFromAdmin(int iletReq)
{
    return this->resource_manager->assignResources(iletReq);
}