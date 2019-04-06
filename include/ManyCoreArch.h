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
#include "Debug.h"

class ManyCoreArch 
{
	public: 
		ManyCoreArch(int _x_dim, int _y_dim, Clock * _clk_instance);

		void start();

		void add_iLet(ILet * new_iLet);

		std::vector<int> invade(ILet * new_ilet);

		void infect(ILet * invaded_ilet);

		void retread(ILet * invaded_ilet);

		int get_procs();
		
		JSON * monitoring();

	private:
		int x_dim;
		int y_dim;

		Clock * clk_instance;
		ProcessingUnit *** pu_array;
		RandomAccessMemory * ram;
		ResourceAdmin * resource_manager;

};

#endif