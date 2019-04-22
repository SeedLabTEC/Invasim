/**
* @file SequenceIlet.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 19/04/19
**/

#ifndef INCLUDE_SEQUENCEILET_H_
#define INCLUDE_SEQUENCEILET_H_

#include <vector>
#include <stdlib.h> 
#include "Utils.h"

#include "Clock.h"
#include "ManyCoreArch.h"
#include "ILet.h"

#define MAX_CLOCKS 10
#define MAX_INFECTIONS 1
#define MAX_INVASIONS 1
#define MAX_LOADS 10
#define MAX_RESOURCES 0.50

enum Sequence_Type
{
	RANDOM,
	ATTACK
};

class SequenceIlet 
{
	public: 
		SequenceIlet(Clock * _clk_instance, ManyCoreArch * _manycore_ptr, float _decision_probability, int _seed);
		SequenceIlet(Sequence_Type _seq_type, Clock * _clk_instance, ManyCoreArch * _manycore_ptr, float _decision_probability, int _seed);

		void set_generation_parameters(int _max_clocks, int _max_infections, int _max_invasions, int _max_loads, float _max_resources);

		void start();

		JSON * monitoring();

	private:
		pthread_t seq_thread;

		Sequence_Type seq_type;
		Clock * clk_instance;
		ManyCoreArch * manycore_ptr;
		std::vector<ILet *> created_ilets;

		float decision_probability;
		int seed;
		int max_clocks;
		int max_infections;
		int max_invasions;
		int max_loads;
		int max_resources;

		ILet * generate_ilet(int index);

		void init(Clock * _clk_instance, ManyCoreArch * _manycore_ptr, float _decision_probability, int _seed);
		static void *generate(void *obj);
};

#endif