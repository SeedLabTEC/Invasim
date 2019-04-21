/**
* @file Operation.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 18/03/19
**/

#ifndef INCLUDE_OPERATION_H_
#define INCLUDE_OPERATION_H_

#include "Utils.h"

enum Invasive_Operation
{
	INVADE,
	INFECT,
	RETREAT
};

class Operation 
{
	public: 
		Operation(Invasive_Operation _operation, int _parameter);
		
		Invasive_Operation get_operation();

		int get_parameter();

	private:
		Invasive_Operation operation;
		int parameter;
};

#endif