/**
* @file Operation.cpp
* @brief Operation source
* @author Dennis Porras Barrantes
* @date 18/03/19
**/

#include "../include/Operation.h"

/**
 * @brief Construct a new Operation:: Operation object
 * 
 * @param _operation 
 * @param _parameter 
 */
Operation::Operation(Invasive_Operation _operation, int _parameter)
{
    this->operation = _operation;
    this->parameter = _parameter;
    this->buffer = NULL;
}

Operation::Operation(Invasive_Operation _operation, std::vector<char> * _parameter)
{
    this->operation = _operation;
    this->parameter = 0;
    this->buffer = _parameter;
}

/**
 * @brief Getter for operation
 * 
 * @return Invasive_Operation 
 */
Invasive_Operation Operation::get_operation()
{
    return this->operation;
}

/**
 * @brief Getter for parameter
 * 
 * @return int 
 */
int Operation::get_parameter()
{
    return this->parameter;
}

/**
 * @brief Getter for program buffer
 **/
std::vector<char> * Operation::get_program()
{
    return this->buffer;
}
