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
 
Operation::Operation(Invasive_Operation _operation, int _parameter)
{
    this->operation = _operation;
    this->parameter = _parameter;
}*/

/**
 * @brief Construct a new Operation:: Operation object
 * 
 * @param _operation 
 * @param _parameter 
 * @param _codeOperation 
 */
Operation::Operation(Invasive_Operation _operation, int _parameter, std::vector<std::string> _codeOperation)
{
    this->operation = _operation;
    this->parameter = _parameter;
    this->codeOperation = _codeOperation;
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
 * @brief Getter for execution one instruction of code
 * 
 * @return std::string
 */
std::string Operation::get_codeOperation(int inst)
{
    return this->codeOperation[inst];
}
