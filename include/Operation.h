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
		Operation(Invasive_Operation _operation, int _parameter);
		Operation(Invasive_Operation _operation, std::vector<char> * _parameter);
		
		Invasive_Operation get_operation();

		std::vector<char> * get_program();

		int get_parameter();

		std::string get_program_name();

		void set_program_name(std::string _name);


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
		 * @brief Pointer to program that is loaded in memory
		 * 
		 **/
		std::vector<char> * buffer;
		/**
		 * @brief Name of the program that infection will copy
		 **/
		std::string program_name;

};

#endif