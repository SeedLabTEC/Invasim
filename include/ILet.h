/**
* @file ILet.h
* @brief Ilet class declaration.
* @author Dennis Porras Barrantes
* @date 18/03/19
**/

#ifndef INCLUDE_ILET_H_
#define INCLUDE_ILET_H_

#include <queue>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <random>
#include "Utils.h"

#include "Operation.h"

/**
 * @brief Enum type to classify iLets
 * 
 */
enum Type_ILet
{
	NORMAL,
	MALICIOUS
};

/**
 * @brief Enum for all the states that an iLet can have.
 * 
 */
enum State_ILet
{
	WAITING,
	EXECUTING,
	DONE
};

/**
 * @brief iLet class representation which is a package all task that a processing unit can execute.
 * 
 */
class ILet 
{
	public: 
		ILet(Type_ILet _type, int _id, float _decision_probability, int idProgram, int priority_ilet);
		~ILet();

		int get_id();

		void add_operation(Invasive_Operation _operation, int _parameter);
		void add_operation(Invasive_Operation _operation, int _parameter, std::vector<subProcess> _codeOperation);

		void pop_operation();

		int execute_operation();

		int finish_operation();

		Operation * get_current_operation();

		std::vector<coordinate> * get_resources();

		State_ILet get_state();
		
		void set_state(State_ILet new_state);

		int get_id_program();
		int get_priority();

		void pop_one_resource(coordinate popPU);

	private:
		/**
		 * @brief Current operation of an iLet.
		 * 
		 */
		Operation * current_operation;
		/**
		 * @brief Pending operation queue of an iLet.
		 * 
		 */
		std::queue<Operation *> pending_operations;
		/**
		 * @brief Done operation queue of an iLet.
		 * 
		 */
		std::queue<Operation *> done_operations;
		/**
		 * @brief Assigned resources coodinates to an iLet.
		 * 
		 */
		std::vector<coordinate> * resources;

		/**
		 * @brief Bernoulli distribution generator
		 * 
		 */
		std::default_random_engine generator;
  		std::bernoulli_distribution distribution;
		
		/**
		 * @brief Type of iLet
		 * 
		 */
		Type_ILet type;
		/**
		 * @brief State of iLet
		 * 
		 */
		State_ILet state;

		/**
		 * @brief iLet identifier.
		 * 
		 */
		int id_ilet;
		/**
		 * @brief Program identifier.
		 * 
		 */
		int id_program;
		/**
		 * @brief ilet priority
		 * 
		 */
		int priority_ilet;
};

#endif