/**
* @file ResourceAdmin.h
* @brief Description
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
#include <vector>
#include <queue>
#include "Debug.h"

class ResourceAdmin 
{
	public: 
		ResourceAdmin(ProcessingUnit *** _pu_array_ptr, int _x_dim, int _y_dim, Clock * _clk_instance);

		ResourceAdmin(ProcessingUnit *** _pu_array_ptr, int _x_dim, int _y_dim, int _max_iLets, Clock * _clk_instance);

		void start();

		void add_iLet(ILet * new_ilet);

		JSON * monitoring();

	private:
		pthread_t pu_exe_thread;
		/**
		 * @brief Mutex variable for handling petitions
		*/
		pthread_mutex_t ilet_mutex = PTHREAD_MUTEX_INITIALIZER;
		/**
		 * @brief Mutex variable for reading notifications
		*/
		//pthread_mutex_t control_bus_mutex = PTHREAD_MUTEX_INITIALIZER;

		Clock * clk_instance;
		
		int max_iLets;
		int x_dim;
		int y_dim;
		int available;

		ProcessingUnit *** pu_array_ptr;
		std::queue<ILet *> incomming_ilets;
		std::vector<ILet *> invaded_ilets;
		std::vector<ILet *> infected_ilets;
		

		void init(ProcessingUnit *** _pu_array_ptr, int _x_dim, int _y_dim, Clock * _clk_instance);
		
		std::vector<coordinate> free_sides(coordinate pu_free);

		void invade(int resources_amount, std::vector<coordinate> *resources, ILet * ilet);

		void infect(ILet * ilet);

		void retread(ILet * ilet);

		static void * managing(void * obj);

};

#endif