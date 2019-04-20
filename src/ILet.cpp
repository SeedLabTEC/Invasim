/**
* @file ILet.cpp
* @brief Description
* @author Dennis Porras Barrantes
* @date 18/03/19
**/

#include "../include/ILet.h"

/**
* @brief Constructor
**/
ILet::ILet(Type_ILet _type, int _id)
{
	this->type = _type;
	this->state = WAITING;
	this->id_ilet = _id;
	this->resources = new std::vector<coordinate>();
	this->current_operation = NULL;
}

ILet::~ILet()
{
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

int ILet::get_id()
{
	return this->id_ilet;
}

void ILet::add_operation(Invasive_Operation _operation, int _parameter)
{
	Operation *tmp_op = new Operation(_operation, _parameter);
	this->pending_operations.push(tmp_op);
}

void ILet::pop_operation()
{
	this->current_operation = this->pending_operations.front();
	this->pending_operations.pop();
}

int ILet::execute_operation()
{
	int is_exe = rand() % 2;
	return is_exe;
}

int ILet::finish_operation()
{
	int is_finished = rand() % 2;
	return is_finished;
}

Operation *ILet::get_current_operation()
{
	return this->current_operation;
}

std::vector<coordinate> *ILet::get_resources()
{
	return this->resources;
}

State_ILet ILet::get_state()
{
	return this->state;
}

void ILet::set_state(State_ILet new_state)
{
	this->state = new_state;
}

pthread_mutex_t *ILet::get_mutex()
{
	return &this->pu_mutex;
}