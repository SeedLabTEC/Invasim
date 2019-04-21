/**
* @file ManyCoreArch.h
* @brief Description
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

#include "json.hpp"
using JSON = nlohmann::json;

#include <vector>
#include "Utils.h"

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

	private:
		int x_dim;
		int y_dim;
		unsigned int max_ilets;

		Clock * clk_instance;
		ProcessingUnit *** pu_array;
		RandomAccessMemory * ram;
		ResourceAdmin * resource_manager;

		void init(int _x_dim, int _y_dim, Clock * _clk_instance);
};

#endif