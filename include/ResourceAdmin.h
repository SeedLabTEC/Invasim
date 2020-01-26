/**
* @file ResourceAdmin.h
* @brief Resource administrator class declaration.
* @author Dennis Porras Barrantes
* @date 29/03/19
**/

#ifndef INCLUDE_RESOURCEADMIN_H_
#define INCLUDE_RESOURCEADMIN_H_

#define DEFAULT_MAX_ILETS 10

#include "ProcessingUnit.h"
#include "ILet.h"

#include "json.hpp"
using JSON = nlohmann::json;

#include <pthread.h>
#include <queue>
#include "Utils.h"

/**
 * @brief Resource administrator class representation that handles the incomming requests for resources.
 * 
 */
class ResourceAdmin 
{
	public: 
		ResourceAdmin(ProcessingUnit *** _pu_array_ptr, int _x_dim, int _y_dim, Clock * _clk_instance);

		ResourceAdmin(ProcessingUnit *** _pu_array_ptr, int _x_dim, int _y_dim, int _max_iLets, Clock * _clk_instance);

		void start();

		void add_iLet(ILet * new_ilet);

		JSON * monitoring();

		std::vector<ILet *> get_invaded();

		int getPriority(int iletID, int programID);

		int assignResources(int iletReq);
		
	private:
		pthread_t pu_exe_thread;
		/**
		 * @brief Mutex variable for handling petitions
		*/
		pthread_mutex_t ilet_mutex = PTHREAD_MUTEX_INITIALIZER;

		/**
		 * @brief Clock instance
		 * 
		 */
		Clock * clk_instance;
		/**
		 * @brief Max amount of iLets (x*y)
		 * 
		 */
		unsigned int max_iLets;
		/**
		 * @brief x dimensions of manycore
		 * 
		 */
		int x_dim;
		/**
		 * @brief y dimensions of manycore
		 * 
		 */
		int y_dim;
		/**
		 * @brief Available resources
		 * 
		 */
		int available;
		/**
		 * @brief Control of process on programs
		 * 
		 */
		JSON resourcesUse;

		/**
		 * @brief Matrix of processing units pointer
		 * 
		 */
		ProcessingUnit *** pu_array_ptr;
		/**
		 * @brief Incomming iLets queue
		 * 
		 */
		std::queue<ILet *> incomming_ilets;
		/**
		 * @brief Invaded iLets vector
		 * 
		 */
		std::vector<ILet *> invaded_ilets;
		/**
		 * @brief Executing iLets vector
		 * 
		 */
		std::vector<ILet *> execute_ilets;
		

		void init(ProcessingUnit *** _pu_array_ptr, int _x_dim, int _y_dim, Clock * _clk_instance);

		void invade(int resources_amount, std::vector<coordinate> *resources, ILet * ilet);

		void infect(ILet * ilet);

		void retreat(ILet * ilet);

		bool verify_ilet(ILet * ilet);

		static void * managing(void * obj);

		void resourcesCalcByProgram(int prog, int clock, int add);

};

#endif