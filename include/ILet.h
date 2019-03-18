/**
* @file ILet.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 18/03/19
**/

#ifndef INCLUDE_ILET_H_
#define INCLUDE_ILET_H_

#include <queue>
#include "Debug.h"

#include "Operation.h"

enum Type_ILet
{
	NORMAL,
	MALICIOUS
};

class ILet 
{
	public: 
		ILet(Type_ILet _type, int _id);
		~ILet();

		int get_id();

		void add_operation(Invasive_Operation _operation, int _parameter);

		void pop_operation();

		void finish_operation();
	
	private:
		Operation * current_operation;
		std::queue<Operation *> pending_operations;
		std::queue<Operation *> done_operations;
		
		Type_ILet type;

		int id_ilet;
};

#endif