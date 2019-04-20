/**
* @file Operation.cpp
* @brief Description
* @author Dennis Porras Barrantes
* @date 18/03/19
**/

#include "../include/Operation.h"

/**
* @brief Constructor
**/
Operation::Operation(Invasive_Operation _operation, int _parameter)
{
    this->operation = _operation;
    this->parameter = _parameter;
}

Invasive_Operation Operation::get_operation()
{
    return this->operation;
}

int Operation::get_parameter()
{
    return this->parameter;
}
