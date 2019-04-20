/**
* @file ILet.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 18/03/19
**/

#ifndef INCLUDE_ILET_H_
#define INCLUDE_ILET_H_

#include <queue>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "Debug.h"

#include "Operation.h"

enum Type_ILet
{
	NORMAL,
	MALICIOUS
};

enum State_ILet
{
	WAITING,
	EXECUTING,
	DONE
};

class ILet 
{
	public: 
		ILet(Type_ILet _type, int _id);
		~ILet();

		int get_id();

		void add_operation(Invasive_Operation _operation, int _parameter);

		void pop_operation();

		int execute_operation();

		int finish_operation();

		Operation * get_current_operation();

		std::vector<coordinate> * get_resources();

		State_ILet get_state();
		
		void set_state(State_ILet new_state);

	private:
		Operation * current_operation;
		std::queue<Operation *> pending_operations;
		std::queue<Operation *> done_operations;
		std::vector<coordinate> * resources;
		
		Type_ILet type;
		State_ILet state;

		int id_ilet;
};

#endif