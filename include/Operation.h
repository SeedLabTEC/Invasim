/**
* @file Operation.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 18/03/19
**/

#ifndef INCLUDE_OPERATION_H_
#define INCLUDE_OPERATION_H_

#include "Utils.h"
#include <vector>

/**
 * @brief Enum of invasive computing operations
 * 
 */
enum Invasive_Operation
{
	INVADE,
	INFECT,
	RETREAT
};

/**
 * @brief Array asociated with the enum Invasive_Operation
 * 
 */
static const std::string STRING_OPERATIONS[] = 
{
	"Invade",
	"Infect",
	"Retreat"
};

/**
 * @brief Operation representation with its corresponding parameter.
 * 
 */
class Operation 
{
	public: 
		
		//Operation::Operation(Invasive_Operation _operation, int _parameter);
	
		Operation(Invasive_Operation _operation, int _parameter, std::vector<subProcess> _codeOperation);
		
		Invasive_Operation get_operation();

		int get_parameter();

		std::string get_codeOperation(int sub, int inst);

	private:
		/**
		 * @brief Invasive operation
		 * 
		 */
		Invasive_Operation operation;
		/**
		 * @brief Parameter of operation
		 * 
		 */
		int parameter;
		/**
		 * @brief Parameter of all code of operation
		 * 
		 */
		std::vector<subProcess> codeOperation;
};

#endif