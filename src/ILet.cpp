/**
* @file ILet.cpp
* @brief iLet source
* @author Dennis Porras Barrantes
* @date 18/03/19
**/

#include "../include/ILet.h"

/**
 * @brief Construct a new ILet::ILet object
 * 
 * @param _type 
 * @param _id 
 * @param _decision_probability 
 */
ILet::ILet(Type_ILet _type, int _id, float _decision_probability)
{
	this->type = _type;
	this->state = WAITING;
	this->id_ilet = _id;
	this->resources = new std::vector<coordinate>();
	this->current_operation = NULL;
	this->distribution = std::bernoulli_distribution(_decision_probability);
}

/**
 * @brief Destroy the ILet::ILet object
 * 
 */
ILet::~ILet()
{
	//Delete all memory requested
	for (size_t i = 0; i < this->pending_operations.size(); i++)
	{
		delete this->pending_operations.front();
		this->pending_operations.pop();
	}
	for (size_t i = 0; i < this->done_operations.size(); i++)
	{
		delete this->done_operations.front();
		this->done_operations.pop();
	}
	if (this->current_operation != NULL)
		delete this->current_operation;
	delete this->resources;
}

/**
 * @brief Id getter
 * 
 * @return int 
 */
int ILet::get_id()
{
	return this->id_ilet;
}

/**
 * @brief Add operation in iLet
 * 
 * @param _operation 
 * @param _parameter 
 */
void ILet::add_operation(Invasive_Operation _operation, int _parameter)
{
	Operation *tmp_op = new Operation(_operation, _parameter);
	this->pending_operations.push(tmp_op);
}

void ILet::add_operation(Invasive_Operation _operation, std::vector<char> * _parameter)
{
	Operation *tmp_op = new Operation(_operation, _parameter);
	this->pending_operations.push(tmp_op);
}

/**
 * @brief Pop an operation from iLet
 * 
 */
void ILet::pop_operation()
{
	this->current_operation = this->pending_operations.front();
	this->pending_operations.pop();
}

/**
 * @brief Ask if a iLet must be executed, with a Bernoulli distribution.
 * 
 * @return int -> yes or no
 */
int ILet::execute_operation()
{
	int is_exe = this->distribution(this->generator);
	return is_exe;
}

/**
 * @brief Ask if the iLet must be terminated, with a Bernoulli distribution.
 * 
 * @return int -> yes or no
 */
int ILet::finish_operation()
{
	int is_finished = this->distribution(this->generator);
	return is_finished;
}

/**
 * @brief Getter to the current operation of iLet
 * 
 * @return Operation* 
 */
Operation *ILet::get_current_operation()
{
	return this->current_operation;
}

/**
 * @brief Getter for resources vector
 * 
 * @return std::vector<coordinate>* 
 */
std::vector<coordinate> *ILet::get_resources()
{
	return this->resources;
}

/**
 * @brief Getter of iLet state
 * 
 * @return State_ILet 
 */
State_ILet ILet::get_state()
{
	return this->state;
}

/**
 * @brief Setter of iLet state
 * 
 * @param new_state 
 */
void ILet::set_state(State_ILet new_state)
{
	this->state = new_state;
}