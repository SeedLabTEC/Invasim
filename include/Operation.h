/**
* @file Operation.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 18/03/19
**/

#ifndef INCLUDE_OPERATION_H_
#define INCLUDE_OPERATION_H_

#include "Debug.h"

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

	private:
		Invasive_Operation operation;
		int parameter;
};

#endif