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

		void start();

	private:
		pthread_t seq_thread;

		Sequence_Type seq_type;
		Clock * clk_instance;
		ManyCoreArch * manycore_ptr;
		std::vector<ILet *> created_ilets;
		std::minstd_rand0 generator;

		float decision_probability;
		int seed;
		int max_clocks;
		int max_infections;
		int max_invasions;
		int max_loads;
		float max_resources;

		void init(Clock * _clk_instance, ManyCoreArch * _manycore_ptr, float _decision_probability, int _seed);
		static void *generate(void *obj);
};

#endif