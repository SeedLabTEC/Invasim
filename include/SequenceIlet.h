/**
* @file SequenceIlet.h
* @brief iLet generator class declaration.
* @author Dennis Porras Barrantes
* @date 19/04/19
**/

#ifndef INCLUDE_SEQUENCEILET_H_
#define INCLUDE_SEQUENCEILET_H_

#include <vector>
#include <string>
#include <stdlib.h>
#include "Utils.h"
#include <fstream>

#include "Clock.h"
#include "ManyCoreArch.h"
#include "ILet.h"

#include "../libs/cpp/pugiconfig.hpp"
#include "../libs/cpp/pugixml.hpp"

//iLet generation parameters
#define MAX_CLOCKS 10
#define MAX_LOADS 10
#define MAX_RESOURCES 0.50

/**
 * @brief Enum type to classify an iLet sequencer.
 * 
 */
enum Sequence_Type
{
	RANDOM,
	ATTACK
};

/**
 * @brief iLet sequencer that generates different tasks to the manycore architecture, depending on diferents parameters.
 * 
 */
class SequenceIlet
{
public:
	SequenceIlet(Clock *_clk_instance, ManyCoreArch *_manycore_ptr, float _decision_probability, int _seed, std::string _working_dir);
	SequenceIlet(Sequence_Type _seq_type, Clock *_clk_instance, ManyCoreArch *_manycore_ptr, float _decision_probability, int _seed);

	void set_generation_parameters(int _max_clocks, int _max_loads, float _max_resources);

	void start();

	JSON *monitoring();

private:
	pthread_t seq_thread;

	/**
		 * @brief Type of sequencer
		 * 
		 */
	Sequence_Type seq_type;
	/**
		 * @brief Clock instance
		 * 
		 */
	Clock *clk_instance;
	/**
		 * @brief Manycore architecture pointer
		 * 
		 */
	ManyCoreArch *manycore_ptr;
	/**
		 * @brief Created iLets vector
		 * 
		 */
	std::vector<ILet *> created_ilets;
	/**
		 * @brief Json with all iLets
		 * 
		 */
	JSON *ilets_info;

	/**
		 * @brief Decision probability to start and end an iLet
		 * 
		 */
	float decision_probability;
	/**
		 * @brief Seed to generate random parameters
		 * 
		 */
	int seed;
	/**
		 * @brief Max amount of clock that the sequencer waits
		 * 
		 */
	int max_clocks;
	/**
		 * @brief Max amount of load that an ilet can have
		 * 
		 */
	int max_loads;
	/**
		 * @brief Max amount of resources that an iLet can request
		 * 
		 */
	int max_resources;

	/**
		 * @brief Flag that notice when a iLet is created
		 * 
		 */
	bool ilet_check = false;

	std::string loadFlow;

	ILet *generate_ilet(int index, std::vector<subProcess> codeFlow, int _id_Prog, int _priority);
	void init(Clock *_clk_instance, ManyCoreArch *_manycore_ptr, float _decision_probability, int _seed);
	static void *generate(void *obj);
	bool checkTerminated(int prog, std::vector<ILet *> iletsList);
	std::vector<std::vector<subProcess>> getBlocksCode(std::string programID);
	std::vector<std::vector<std::vector<subProcess>>> getPrograms();
};

#endif