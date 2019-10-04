/**
* @file ManyCoreArch.h
* @brief Manycore architecture class declaration.
* @author Dennis Porras Barrantes
* @date 27/03/19
**/

#ifndef INCLUDE_MANYCOREARCH_H_
#define INCLUDE_MANYCOREARCH_H_

#include "Clock.h"
#include "ILet.h"
#include "ProcessingUnit.h"
#include "RandomAccessMemory.h"
#include "ResourceAdmin.h"

//Json library include and declaration
#include "json.hpp"
using JSON = nlohmann::json;

#include <vector>
#include "Utils.h"

/**
 * @brief Manycore architecture class that contains the matrix of processors and the resource administrator.
 * 
 */
class ManyCoreArch 
{
	public: 
		ManyCoreArch(int _x_dim, int _y_dim, Clock * _clk_instance);

		ManyCoreArch(int _x_dim, int _y_dim, Clock * _clk_instance, int _max_ilets);

		void start();

		void invade(ILet * new_iLet);

		int get_procs();

		unsigned int get_max_ilets();
		
		JSON * monitoring();

		std::vector<ILet *> get_invaded();

	private:
		/**
		 * @brief x dimension of manycore architrecture.
		 * 
		 */
		int x_dim;
		/**
		 * @brief y dimension of manycore architecture
		 * 
		 */
		int y_dim;
		/**
		 * @brief Max amount of iLets supported
		 * 
		 */
		unsigned int max_ilets;

		/**
		 * @brief Componets instances
		 * 
		 */
		Clock * clk_instance;
		/**
		 * @brief Processing unit matrix
		 * 
		 */
		ProcessingUnit *** pu_array;
		/**
		 * @brief RAM instance
		 * 
		 */
		RandomAccessMemory * ram;
		/**
		 * @brief Resource administrator instance
		 * 
		 */
		ResourceAdmin * resource_manager;

		void init(int _x_dim, int _y_dim, Clock * _clk_instance);
};

#endif