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
    this->id_ilet = _id;
    this->current_operation = NULL;
}

ILet::~ILet()
{
    for(size_t i = 0; i < this->pending_operations.size(); i++)
    {
        delete this->pending_operations.front();
        this->pending_operations.pop();
    }
    for(size_t i = 0; i < this->done_operations.size(); i++)
    {
        delete this->done_operations.front();
        this->done_operations.pop();
    }
    if (this->current_operation != NULL)
        delete this->current_operation;
    
}

int ILet::get_id()
{
    return this->id_ilet;
}

void ILet::add_operation(Invasive_Operation _operation, int _parameter)
{
    Operation * tmp_op = new Operation(_operation, _parameter);
    this->pending_operations.push(tmp_op);
}

void ILet::pop_operation()
{
    this->current_operation = this->pending_operations.front();
    this->pending_operations.pop();
}

void ILet::finish_operation()
{
    this->done_operations.push(this->current_operation);
    this->current_operation = NULL;
}