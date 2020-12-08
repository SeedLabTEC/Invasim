/**
* @file ResourceAdmin.cpp
* @brief Resource administrator source
* @author Dennis Porras Barrantes
* @date 29/03/19
**/

#include "../include/ResourceAdmin.h"

/**
 * @brief Construct a new Resource Admin:: Resource Admin object
 * 
 * @param _pu_array_ptr 
 * @param _x_dim 
 * @param _y_dim 
 * @param _clk_instance 
 */
ResourceAdmin::ResourceAdmin(ProcessingUnit ***_pu_array_ptr, int _x_dim, int _y_dim, Clock *_clk_instance, bool ai)
{
	this->ai = ai;
	this->max_iLets = _x_dim * _y_dim;
	this->init(_pu_array_ptr, _x_dim, _y_dim, _clk_instance);
	this->resourcesUse = {};
}

/**
 * @brief Construct a new Resource Admin:: Resource Admin object
 * 
 * @param _pu_array_ptr 
 * @param _x_dim 
 * @param _y_dim 
 * @param _max_iLets 
 * @param _clk_instance 
 */
ResourceAdmin::ResourceAdmin(ProcessingUnit ***_pu_array_ptr, int _x_dim, int _y_dim, int _max_iLets, Clock *_clk_instance, bool ai)
{
	this->ai = ai;
	this->max_iLets = _x_dim * _y_dim;
	this->init(_pu_array_ptr, _x_dim, _y_dim, _clk_instance);
	this->resourcesUse = {};
}

/**
 * @brief Function that initialize components and pointers
 * 
 * @param _pu_array_ptr 
 * @param _x_dim 
 * @param _y_dim 
 * @param _clk_instance 
 */
void ResourceAdmin::init(ProcessingUnit ***_pu_array_ptr, int _x_dim, int _y_dim, Clock *_clk_instance)
{
	this->pu_array_ptr = _pu_array_ptr;
	this->clk_instance = _clk_instance;
	this->x_dim = _x_dim;
	this->y_dim = _y_dim;
	this->available = this->x_dim * this->y_dim;
}

/**
 * @brief Function that starts the component thread
 * 
 */
void ResourceAdmin::start()
{
	//create threads
	pthread_create(&this->pu_exe_thread, NULL, ResourceAdmin::managing, (void *)this);
	//detach threads
	pthread_detach(this->pu_exe_thread);
}

/**
 * @brief Add a new iLet to the queue
 * 
 * @param new_iLet 
 */
void ResourceAdmin::add_iLet(ILet *new_iLet)
{
	pthread_mutex_lock(&this->ilet_mutex);
	this->incomming_ilets.push(new_iLet);
	pthread_mutex_unlock(&this->ilet_mutex);
}

/**
 * @brief Function that gets information of component and processing units
 * 
 * @return JSON* array
 */
JSON *ResourceAdmin::monitoring()
{
	JSON *array_info = new JSON;
	//List to return
	*array_info = JSON::array();

	//Json construction
	JSON resource_admin_info = {
		{"Incomming_Ilets", this->incomming_ilets.size()},
		{"Waiting_Ilets", this->invaded_ilets.size()},
		{"Executing_Ilets", this->execute_ilets.size()},
		{"Max_Ilets", this->max_iLets},
		{"Programs", this->resourcesUse}};

	//Push data
	array_info->push_back(resource_admin_info);

	//Get information of every processing unit
	for (int i = 0; i < this->x_dim; i++)
	{
		for (int j = 0; j < this->y_dim; j++)
		{
			JSON *pu_info_ptr = pu_array_ptr[i][j]->monitoring();
			//Push unit info
			array_info->push_back(*pu_info_ptr);
			delete pu_info_ptr;
		}
	}
	//array_info->push_back();
	
	return array_info;
}

/**
 * @brief Function that assings resoruces to an ilet as they are available
 * 
 * @param resources_amount 
 * @param resources 
 * @param ilet 
 */
void ResourceAdmin::invade(int resources_amount, std::vector<coordinate> *resources, ILet *ilet)
{
	//Flag when they are assigned
	bool found = false;
	//Assigned resources
	int invaded_resources = 0;

	//Iterate all processing units
	for (int i = 0; i < this->x_dim; i++)
	{
		for (int j = 0; j < this->y_dim; j++)
		{
			if (this->pu_array_ptr[i][j]->get_state() == FREE)
			{
				//When a resource is found it the coordinate is assigned
				coordinate new_pu = this->pu_array_ptr[i][j]->get_coodinate();
				//Vector thta has to be filled with coodinates
				resources->push_back(new_pu);
				this->pu_array_ptr[i][j]->invade(ilet);
				invaded_resources++;
				//Finish when assignment is done
				if (invaded_resources == resources_amount)
				{
					found = true;
					break;
				}
			}
		}
		if (found)
		{
			break;
		}
	}
	//Discount available resources
	this->available -= resources_amount;
}

/**
 * @brief Funciton that infects all the resources in an iLet
 * 
 * @param ilet 
 */
void ResourceAdmin::infect(ILet *ilet)
{
	unsigned int resources = ilet->get_resources()->size();

	for (unsigned int i = 0; i < resources; i++)
	{
		coordinate position = ilet->get_resources()->at(i);
		this->pu_array_ptr[position.x][position.y]->infect();
	}
	ilet->set_state(EXECUTING);
}

/**
 * @brief Funciton that retreats all the resources in an iLet
 * 
 * @param ilet 
 */
void ResourceAdmin::retreat(ILet *ilet)
{
	unsigned int resources = ilet->get_resources()->size();
	for (unsigned int i = 0; i < resources; i++)
	{
		coordinate position = ilet->get_resources()->at(i);
		this->pu_array_ptr[position.x][position.y]->retreat();
	}
	this->available += resources;
}

/**
 * @brief Funciton that verify if an iLet has finished 
 * 
 * @param ilet 
 * @return true 
 * @return false 
 */
bool ResourceAdmin::verify_ilet(ILet *ilet)
{
	bool is_done = true;

	unsigned int resources = ilet->get_resources()->size();
	//Iterate resources in iLet

	for (unsigned int i = 0; i < resources; i++)
	{
		coordinate position = ilet->get_resources()->at(i);
		//If a processing unit is infected the iLet is not done

		if (this->pu_array_ptr[position.x][position.y]->get_state() == INFECTED)
		{
			is_done = false;
			break;
		}
	}
	//std::cout << " VALUE HERE "<< is_done << std::endl;

	for (int spi = 0; spi < (int)ilet->get_current_operation()->get_subProcess().size(); spi++)
	{
		if (!ilet->get_current_operation()->get_subProcess()[spi].state)
		{
			if (ilet->get_current_operation()->get_subProcess()[spi].puWork > 0)
			{
				is_done = false;
				break;
			}
		}
	}

	return is_done;
}

/**
 * @brief Getter of list of ilets on invaded
 * 
 * @param obj 
 * @return std::vector<ILet *>
 */
std::vector<ILet *> ResourceAdmin::get_invaded()
{
	std::queue<ILet *> qc = this->incomming_ilets;
	std::vector<ILet *> r;

	for (int q = 0; q < (int)this->incomming_ilets.size(); q++)
	{
		r.push_back(qc.front());
		qc.pop();
	}

	r.insert(r.end(), this->execute_ilets.begin(), this->execute_ilets.end());

	return r;
}

/**
 * @brief Create a variable priority for one ilet
 * 
 * @param iletID ID of ilet if we want to keep a control 
 * @param programID ID of program if we want to keep a control 
 * @param resourcesRequire Quantity of resources required from ilet
 * @return int Between 1-5
 */
/*int ResourceAdmin::getPriority(int iletID, int programID, int resourcesRequire)
{
	float iletReq_f = (float) resourcesRequire;
	float available_f = (float) this->max_iLets;

	int assign = this->AIassignPriority(iletReq_f, available_f);

	return assign;
}*/

/**
 * @brief Assign resourses to use for Ilets
 * 
 * @param iletReq Quantity of resources required from ilet (cores, priority)
 * @return vector <int> with cores and priority assigned 
 */
std::vector<int> ResourceAdmin::assignResources(int iletID, int progID, int iletReq)
{
	std::chrono::_V2::system_clock::time_point t1;
	std::chrono::_V2::system_clock::time_point t2;

	t1 = std::chrono::high_resolution_clock::now();
	
	float iletReq_f = (float) iletReq;
	float available_f = (float) this->available;

	std::vector<int> result;

	int core_assign = 0;
	int priority_assign = 5;
	// Check if the user is allowing to use artificial intelligence
	if(this->ai) {
		// Using AI
		///////// Cores assign
		if(this->available != 0) {
			core_assign = this->AIassignCores(iletReq_f, available_f);
		}
		///////// Priority assign
		priority_assign = this->AIassignPriority(iletReq_f, available_f);

		///////// Vector result building
		result.push_back(core_assign);
		result.push_back(priority_assign);
	} else {
		// Using Optimization
		result = this->optAssignResources(iletReq_f, available_f, progID);
	}

	t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
	std::cout << "PROGRAM: " << progID << " ; " << "ILET: " << iletID << " ; " << "DURATION: " << duration << "ms" << std::endl;

	return result;
}

/**
 * @brief Function that starts the component thread
 * 
 */
void ResourceAdmin::resourcesCalcByProgram(int prog, int clock, int add)
{
	std::string search = std::to_string(prog);
	auto subjectIdIter = this->resourcesUse.find(search);
	if (subjectIdIter != this->resourcesUse.end())
	{
		//cout << "it is found" << endl;
		int diffClock = clock - (int)this->resourcesUse[search]["clock"]; // calculate the difference between clocks
		int diff = diffClock + add;										  // calculate the new weight using the difference between clocks and extra weight wanted
		this->resourcesUse[search]["clock"] = clock;
		this->resourcesUse[search]["val"] = (int)this->resourcesUse[search]["val"] + diff;
	}
	else
	{
		this->resourcesUse[search] = {{"clock", clock}, {"val", clock}};
	}
	//std::cout << " PROGRAM " + search + " " << this->resourcesUse[search] << std::endl;
}

/**
 * @brief Execution thread function that handles all requests with its resources
 * 
 * @param obj 
 * @return void* 
 */
void *ResourceAdmin::managing(void *obj)
{
	//std::chrono::_V2::system_clock::time_point t1;
	//std::chrono::_V2::system_clock::time_point t2;

	ResourceAdmin *current = (ResourceAdmin *)obj;
	dprintf("ResourceAdmin: The resource administrator is started.\n");
	//Get clock mutex and conditional variable
	pthread_mutex_t *clk_cycle_mutex = current->clk_instance->get_cycle_mutex_ptr();
	pthread_cond_t *clk_cycle_cond = current->clk_instance->get_cycle_cond_ptr();
	//Component loop
	while (1)
	{
		//Await to clock signal
		pthread_cond_wait(clk_cycle_cond, clk_cycle_mutex);
		dprintf("ResourceAdmin: %s.\n", current->monitoring()->dump().c_str());

		ILet *current_ilet = NULL;

		//Verify if there is any incomming iLet
		if (current->incomming_ilets.size() > 0)
		{
			pthread_mutex_lock(&current->ilet_mutex);
			//Get front of queue and pop
			current_ilet = current->incomming_ilets.front();
			current->incomming_ilets.pop();
			pthread_mutex_unlock(&current->ilet_mutex);
			dprintf("ResourceAdmin: Managing incomming Ilet = %d.\n", current_ilet->get_id());
			//Verify if it is an iLet that need more resources so the operationg has to be poped
			if (current_ilet->get_state() == WAITING)
			{
				current_ilet->pop_operation();
			}
			//Verify if there are resources to be assigned
			if ((current_ilet->get_current_operation()->get_parameter()) <= current->available)
			{
				dprintf("ResourceAdmin: Found resources to Ilet = %d.\n", current_ilet->get_id());
				//Set state to waiting for resources and push to invaded vector
				current_ilet->set_state(WAITING);
				current->invaded_ilets.push_back(current_ilet);
			}
			else
			{
				//If there are not enough resources, then is queued again
				dprintf("ResourceAdmin: Not enough resources to Ilet = %d.\n", current_ilet->get_id());
				std::cout << " ResourceAdmin: Not enough resources to Ilet = " << current_ilet->get_id() << std::endl;
				pthread_mutex_lock(&current->ilet_mutex);
				current_ilet->set_state(EXECUTING);
				current->incomming_ilets.push(current_ilet);
				pthread_mutex_unlock(&current->ilet_mutex);
			}
		}
		//Verify if there are any executing iLet
		if (current->execute_ilets.size() > 0)
		{
			//Iterate those executing iLets
			for (size_t i = 0; i < current->execute_ilets.size(); i++)
			{
				//Get an iLet
				current_ilet = current->execute_ilets.at(i);
				switch (current_ilet->get_state())
				{
				case WAITING:
				{
					//current->iLet_ptr->add_clocks_used(1);
					//When waiting ask if it has to infect
					int start = current_ilet->execute_operation();
					if (start)
					{

						dprintf("ResourceAdmin: Infecting resources to Ilet = %d.\n", current_ilet->get_id());
						current->infect(current_ilet);
						//t1 = std::chrono::high_resolution_clock::now();
					}
				}
				break;

				case EXECUTING:
				{
					//When executing ask if it has to be terminted
					int terminate = 1;
					if (!terminate)
					{
						dprintf("ResourceAdmin: Ilet = %d to be terminated.\n", current_ilet->get_id());
						current_ilet->set_state(DONE);
					} //If not terminated verify if it is done
					else if (current_ilet->get_current_operation()->get_operation() == INFECT)
					{
						bool is_done = current->verify_ilet(current_ilet);
						if (is_done)
						{
							dprintf("ResourceAdmin: Ilet = %d is done.\n", current_ilet->get_id());
							//t2 = std::chrono::high_resolution_clock::now();
							//auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
							//std::cout << duration << " us" << std::endl;
							std::cout << "DONE ILET " << current_ilet->get_id() << std::endl;
							current->resourcesCalcByProgram(current_ilet->get_id_program(), current->clk_instance->get_cycle(), current_ilet->get_clocks_used());
							current_ilet->set_state(DONE);
						}
						else // free units with completation subprocess and infect if is neccesary
						{
							for (int spi = 0; spi < (int)current_ilet->get_current_operation()->get_subProcess().size(); spi++)
							{
								if ((current_ilet->get_current_operation()->get_subProcess()[spi].puWork < 0))
								{
									if (current_ilet->get_current_operation()->get_subProcess()[spi].SPxPU.x != -1) // check if was a old subprocess
									{
										current_ilet->get_current_operation()->reduce_WorkOfProcess(spi); // reduce to avoid pass here again
										coordinate position = current_ilet->get_current_operation()->get_subProcess()[spi].SPxPU;
										//current_ilet->pop_one_resource(position); // pop resurce
										current->pu_array_ptr[position.x][position.y]->retreat();
										current_ilet->get_current_operation()->set_codeOperation(spi, {-1, -1});
										//current->available += 1;
										current->pu_array_ptr[position.x][position.y]->invade(current_ilet);
										current->pu_array_ptr[position.x][position.y]->infect();
									}
								}
							}
						}
					}
				}
				break;

				case DONE:
				{
					//When it is done pop the operation or verify if it will retreat
					if (current_ilet->get_current_operation()->get_operation() == RETREAT)
					{
						dprintf("ResourceAdmin: Ilet = %d terminated.\n", current_ilet->get_id());
						current->retreat(current_ilet);
						current->execute_ilets.erase(current->execute_ilets.begin() + i);
					}
					else
					{
						//Pop operation in case it is not a retreat
						current_ilet->pop_operation();
						if (current_ilet->get_current_operation()->get_operation() == RETREAT)
						{
							current_ilet->set_state(DONE);
						} //If operation is invade then is has to be queued
						else if (current_ilet->get_current_operation()->get_operation() == INVADE)
						{
							current_ilet->set_state(WAITING);
							current->invaded_ilets.push_back(current_ilet);
							current->execute_ilets.erase(current->execute_ilets.begin() + i);
						}
						else
						{
							//In case if it is an infection
							current_ilet->set_state(WAITING);
						}
					}
				}
				break;

				default:
					break;
				}
			}
		}

		//Verify if there are iLet that has to invade
		if (current->invaded_ilets.size() > 0)
		{
			//Iterate those iLets
			for (size_t i = 0; i < current->invaded_ilets.size(); i++)
			{
				//Get an iLet
				current_ilet = current->invaded_ilets.at(i);
				//Invade resources
				current->invade(current_ilet->get_current_operation()->get_parameter(),
								current_ilet->get_resources(),
								current_ilet);

				current_ilet->pop_operation();
				//Verify it will invade more resources
				if (current_ilet->get_current_operation()->get_operation() != INVADE)
				{
					//To proceed infection
					current->execute_ilets.push_back(current_ilet);
					current->invaded_ilets.erase(current->invaded_ilets.begin() + i);
				}
			}
		}
	}
	return NULL;
}

/**
 * @brief NN Mathematical model to Assign a certain amount of cores to an ILet.
 * 
 * @param core_require amount of cores require by the ILet
 * @param core_Available amount of cores available right now
 * @return cores assigned
 */
int ResourceAdmin::AIassignCores(float core_require, float core_available) 
{
  // Scale Layer
  float scaled_core_require = 2*(core_require-1)/(50-1)-1;
  float scaled_core_available = 2*(core_available-0)/(50-0)-1;
  // Perceptron 1_1 (layer 1, neuron 1)
  float y_1_1 = (float) (std::tanh(-0.870334-0.879223*scaled_core_require+0.869303*scaled_core_available));
  // Perceptron 1_2 (layer 1, neuron 2)
  float y_1_2 = (float) (std::tanh(0.00730768+0.0713884*scaled_core_require-0.44646*scaled_core_available));
  // Perceptron 2_1 (Output)(layer 2, neuron 1)
  float scaled_core_assign = (float) (-1.02428-0.833818*y_1_1-1.62438*y_1_2);
  // Unscale Layer
  float core_assign = (float) (0.5*(scaled_core_assign+1.0)*(44-0)+0);

  // Bounding layer
  float minimum = 1;
  float maximum = core_require;
  core_assign = std::max(minimum, core_assign);
  core_assign = std::min(maximum, core_assign);

  // Round output (This is because the regression model uses float numbers, and we need integers)
  int core_assign_rounded = std::ceil(core_assign);

  return core_assign_rounded;
}

/**
 * @brief NN Mathematical model to Assign a memeory access priority.
 * 
 * @param core_require amount of cores require by the ILet
 * @param core_Available amount of cores in the system
 * @return priority assigned
 */
int ResourceAdmin::AIassignPriority(float core_require, float core_available) {
  // Scale Layer
  float scaled_resources_available = 2*(core_available-1)/(50-1)-1;
  float scaled_resources_require = 2*(core_require-1)/(50-1)-1;
  // Perceptron 1_1 (layer 1, neuron 1)
  float y_1_1 = (float) (std::tanh(-3.61583+0.969469*scaled_resources_available-4.57267*scaled_resources_require));
  // Perceptron 1_2 (layer 1, neuron 2)
  float y_1_2 = (float) (std::tanh(2.01616-3.26919*scaled_resources_available+4.43776*scaled_resources_require));
  // Perceptron 2_1 (Output)(layer 2, neuron 1)
  float scaled_priority_assign = (float) (0.0542604+0.512467*y_1_1-0.556138*y_1_2);
  // Unscale Layer
  float priority_assign = (float) (0.5*(scaled_priority_assign+1.0)*(5-1)+1);

  // Bounding layer
  float minimum = 1;
  float maximum = 5;
  priority_assign = std::max(minimum, priority_assign);
  priority_assign = std::min(maximum, priority_assign);

  // Round output (This is because the regression model uses float numbers, and we need integers)
  int priority_assign_rounded = (int) std::round(priority_assign);

  return priority_assign_rounded;
}

/**
 * @brief Multiobjective optimization to calculate cores and priority values.
 * 
 * @param core_require amount of cores require by the ILet
 * @param core_Available amount of available cores in the system
 * @param progID Program ID
 * @return vector with resources assigned [cores, priority]
 */
std::vector<int> ResourceAdmin::optAssignResources(float core_require, float core_available, int progID)
{
	int priority_level = 1; // Current priority level
	const int MAX_PRIORITY_LEVEL = 3; // Max priority level to achieve

	std::vector<int> result; // Result vector

	// Cores Upper bound definition
	float x_UB = (core_require > core_available) ? core_available : core_require;

	// Priorities results
	float x_result_1, y_result_1, x_result_2, y_result_2, x_result_3, y_result_3;
	x_result_1 = y_result_1 = x_result_2 = y_result_2 = x_result_3 = y_result_3 = 0;

	// deviation variables results
	float dneg_3_result, dpos_3_result, dneg_2_result, dpos_2_result, dpos_1_result, dneg_1_result;
	dneg_3_result = dpos_3_result = dneg_2_result = dpos_2_result = dpos_1_result = dneg_1_result = 0;

	// Functions coefficients, factors and goals
	// F1
	float x_coef_1 = 1/core_available;
	float y_coef_1 = -1/(core_available*5);
	float goal1 = core_require/core_available;
	// F2
	float x_coef_2 = 1/(core_available*2);
	float y_coef_2 = 1/10;
	float goal2 = core_require/core_available;
	// F3
	float lambda = 1;
	float x_coef_3 = 1;
	float y_coef_3 = 1;

	float goal3_1 = 0;
	float goal3 = 0;
	// Deviation variables coefficients
	float dneg_3_coef, dpos_3_coef, dneg_2_coef, dpos_2_coef, dpos_1_coef, dneg_1_coef;
	dneg_3_coef = dpos_3_coef = dneg_2_coef = dpos_2_coef = dpos_1_coef = dneg_1_coef = 1;

	while(priority_level <= MAX_PRIORITY_LEVEL) {
		if(priority_level == 3)
		{
			// Create the linear solver with the GLOP backend
			operations_research::MPSolver solver("Solver_f1", operations_research::MPSolver::GLOP_LINEAR_PROGRAMMING);

			// Create the objective function
			operations_research::MPObjective* const objective = solver.MutableObjective();

			// Infinity representation constant
			const double infinity = solver.infinity();

			// Create the desition variables with their respective constraints
			operations_research::MPVariable* const x = solver.MakeNumVar(0.0, x_UB, "x"); // Cores
			operations_research::MPVariable* const y = solver.MakeNumVar(1.0, 5.0, "y"); // Mem priority
			operations_research::MPVariable* const dneg_1 = solver.MakeNumVar(0.0, infinity, "dneg_1"); // Negative deviation variable f1
			operations_research::MPVariable* const dpos_1 = solver.MakeNumVar(0.0, infinity, "dpos_1"); // Positive deviation variable f1
			operations_research::MPVariable* const dneg_2 = solver.MakeNumVar(dneg_2_result, dneg_2_result, "dneg_2"); // Negative deviation variable f2
			operations_research::MPVariable* const dpos_2 = solver.MakeNumVar(0.0, infinity, "dpos_2"); // Positive deviation variable f2
			operations_research::MPVariable* const dneg_3 = solver.MakeNumVar(0.0, infinity, "dneg_3"); // Negative deviation variable f3
			operations_research::MPVariable* const dpos_3 = solver.MakeNumVar(dpos_3_result, dpos_3_result, "dpos_3"); // Positive deviation variable f3

			// Funcion restriction
			operations_research::MPConstraint* const ct1 = solver.MakeRowConstraint(goal1, goal1, "ct1");
			ct1->SetCoefficient(x, x_coef_1);
			ct1->SetCoefficient(y, y_coef_1);
			ct1->SetCoefficient(dneg_1, dneg_1_coef);
			ct1->SetCoefficient(dpos_1, -dpos_1_coef);

			operations_research::MPConstraint* const ct2 = solver.MakeRowConstraint(goal2, goal2, "ct2");
			ct2->SetCoefficient(x, x_coef_2);
			ct2->SetCoefficient(y, y_coef_2);
			ct2->SetCoefficient(dneg_2, dneg_2_coef);
			ct2->SetCoefficient(dpos_2, -dpos_2_coef);

			operations_research::MPConstraint* const ct3 = solver.MakeRowConstraint(goal3, goal3, "ct3");
			ct3->SetCoefficient(x, x_coef_3);
			ct3->SetCoefficient(y, y_coef_3);
			ct3->SetCoefficient(dneg_3, dneg_3_coef);
			ct3->SetCoefficient(dpos_3, -dpos_3_coef);

			// Objective function
			objective->SetCoefficient(dpos_1, dpos_1_coef);
			objective->SetCoefficient(x, 0);
			objective->SetCoefficient(y, 0);
			objective->SetCoefficient(dneg_1, 0);
			objective->SetMinimization();

			// Solve
			solver.Solve();

			// Assign result values
			y_result_1 = y->solution_value();
			x_result_1 = x->solution_value();
			dpos_1_result = dpos_1->solution_value();

			// Update total execution time
			float total_time = getDataFromJSON(progID, "TotalExecTime");
			float new_time = total_time + x_coef_1*x_result_1 + y_coef_1*y_result_1;
			this->updateProgramsJSON(progID, new_time, "TotalExecTime");
		}
			
		else if (priority_level == 2)
		{
			// Create the linear solver with the GLOP backend
			operations_research::MPSolver solver("Solver_f2", operations_research::MPSolver::GLOP_LINEAR_PROGRAMMING);

			// Create the objective function
			operations_research::MPObjective* const objective = solver.MutableObjective();

			// Infinity representation constant
			const double infinity = solver.infinity();

			// Create the desition variables with their respective constraints
			operations_research::MPVariable* const x = solver.MakeNumVar(0.0, x_UB, "x"); // Cores
			operations_research::MPVariable* const y = solver.MakeNumVar(1.0, 5.0, "y"); // Mem priority
			operations_research::MPVariable* const dneg_2 = solver.MakeNumVar(0.0, infinity, "dneg_2"); // Negative eviation variable f2
			operations_research::MPVariable* const dpos_2 = solver.MakeNumVar(0.0, infinity, "dpos_2"); // Positive deviation variable f2
			operations_research::MPVariable* const dneg_3 = solver.MakeNumVar(0.0, infinity, "dneg_3"); // Negative deviation variable f3
			operations_research::MPVariable* const dpos_3 = solver.MakeNumVar(dpos_3_result, dpos_3_result, "dpos_3"); // Positive deviation variable f3

			// Funcion restriction
			operations_research::MPConstraint* const ct1 = solver.MakeRowConstraint(goal2, goal2, "ct1");
			ct1->SetCoefficient(x, x_coef_2);
			ct1->SetCoefficient(y, y_coef_2);
			ct1->SetCoefficient(dneg_2, dneg_2_coef);
			ct1->SetCoefficient(dpos_2, -dpos_2_coef);

			operations_research::MPConstraint* const ct2 = solver.MakeRowConstraint(goal3, goal3, "ct2");
			ct2->SetCoefficient(x, x_coef_3);
			ct2->SetCoefficient(y, y_coef_3);
			ct2->SetCoefficient(dneg_3, dneg_3_coef);
			ct2->SetCoefficient(dpos_3, -dpos_3_coef);

			// Objective function
			objective->SetCoefficient(dneg_2, dneg_2_coef);
			objective->SetCoefficient(x, 0);
			objective->SetCoefficient(y, 0);
			objective->SetCoefficient(dpos_2, 0);
			objective->SetMinimization();

			// Solve
			solver.Solve();

			// Assign result values
			y_result_2 = y->solution_value();
			x_result_2 = x->solution_value();
			dneg_2_result = dneg_2->solution_value();
		}
		else if(priority_level == 1)
		{
			// Create the linear solver with the GLOP backend
			operations_research::MPSolver solver("Solver_f3", operations_research::MPSolver::GLOP_LINEAR_PROGRAMMING);

			// Create the objective function
			operations_research::MPObjective* const objective = solver.MutableObjective();

			// Infinity representation constant
			const double infinity = solver.infinity();

			// Create the desition variables with their respective constraints
			operations_research::MPVariable* const x = solver.MakeNumVar(0.0, x_UB, "x"); // Cores
			operations_research::MPVariable* const y = solver.MakeNumVar(1.0, 5.0, "y"); // Mem priority
			operations_research::MPVariable* const dneg_3 = solver.MakeNumVar(0.0, infinity, "dneg_3"); // Negative deviation variable f3
			operations_research::MPVariable* const dpos_3 = solver.MakeNumVar(0.0, infinity, "dpos_3"); // Positive deviation variable f3
			
			lambda = this->getDataFromJSON(progID, "lambda");
			goal3_1 = ( lambda == 0 ? 0 : ( (core_available/core_require) >= 5 ? 5 : std::floor(core_available/core_require) ) ); // Computational resources from mem priority term
			goal3 = std::round(core_require*lambda) + goal3_1;

			// Funcion restriction
			operations_research::MPConstraint* const ct1 = solver.MakeRowConstraint(goal3, goal3, "ct1");
			ct1->SetCoefficient(x, x_coef_3);
			ct1->SetCoefficient(y, y_coef_3);
			ct1->SetCoefficient(dneg_3, dneg_3_coef);
			ct1->SetCoefficient(dpos_3, -dpos_3_coef);

			// Objective function
			objective->SetCoefficient(dpos_3, dpos_3_coef);
			objective->SetCoefficient(x, 0);
			objective->SetCoefficient(y, 0);
			objective->SetCoefficient(dneg_3, 0);
			objective->SetMinimization();

			// Solve
			solver.Solve();

			// Assign result values
			y_result_3 = y->solution_value();
			x_result_3 = x->solution_value();
			dpos_3_result = dpos_3->solution_value();

			// Update lambda factor
			float total_time = getDataFromJSON(progID, "TotalExecTime");
			float new_lambda = lambda - (0.001*total_time);
			float l = (new_lambda >= 0) ? new_lambda : 0;
			this->updateProgramsJSON(progID, l, "lambda");
		}

		priority_level += 1;
	}

	// Build result vector
	int x_result_1_int = (int) std::ceil(x_result_1);
	int y_result_1_int = (int) std::ceil(y_result_1);

	result.push_back(x_result_1_int);
	result.push_back(y_result_1_int);

	return result;
}

/**
 * @brief Get data number from JSON file for programs data.
 * 
 * @param progID Program ID
 * @return parameter value
 */
float ResourceAdmin::getDataFromJSON(int progID, std::string parameter)
{
	std::string path = "bin/";
	path.append("program_");
	path.append(std::to_string(progID));
	path.append(".json");

	float result = 0;

	//Read json file from disk
    std::string line;
    std::ifstream r_file(path.c_str());
    std::getline(r_file, line);
    r_file.close();

	//Append data and create string
    JSON old_content = JSON::parse(line);

	result = old_content[0][parameter];

	return result;
}

/**
 * @brief Update data number to JSON file for programs data.
 * 
 * @param progID Program ID
 */
void ResourceAdmin::updateProgramsJSON(int progID, float dataToUpdate, std::string parameter)
{
	std::string path = "bin/";
	path.append("program_");
	path.append(std::to_string(progID));
	path.append(".json");

	//Read json file from disk
    std::string line;
    std::ifstream r_file(path.c_str());    
    std::getline(r_file, line);
    r_file.close();

	//Append data and create string
    JSON old_content = JSON::parse(line);
	old_content[0][parameter] = dataToUpdate;

	std::string data_w = old_content.dump();
    //Write in disk
	std::ofstream resources_file(path.c_str());
	resources_file << data_w << std::endl;
	resources_file.close();
}