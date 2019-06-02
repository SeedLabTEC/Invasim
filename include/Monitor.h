/**
* @file Monitor.h
* @brief Monitor class declaration
* @author Dennis Porras Barrantes
* @date 31/03/19
**/

#ifndef INCLUDE_MONITOR_H_
#define INCLUDE_MONITOR_H_

//Json file names
#define MANY_FILE "/manycore.json"
#define RES_FILE "/resources.json"
#define ILET_FILE "/ilets.json"

#define PREFIX_PU "/unit_"
#define SUFIX_PU ".json"

#include <linux/limits.h>
#include <iostream>
#include <fstream>

//Components
#include "Clock.h"
#include "ManyCoreArch.h"
#include "SequenceIlet.h"

#include "Utils.h"

class Monitor 
{
	public: 
		Monitor(ManyCoreArch *_manycore_ptr, SequenceIlet *_seq_ilet_ptr, Clock * _clk_instance);
		Monitor(ManyCoreArch *_manycore_ptr, SequenceIlet *_seq_ilet_ptr, std::string  _path_files, Clock * _clk_instance);

		void start();
		void write_disk(std::string path, JSON data, bool append);
		std::string get_working_dir();

	private:
		pthread_t monitor_thread;

		/**
		 * @brief Clock instance
		 * 
		 */
		Clock * clk_instance;
		/**
		 * @brief Working directory in monitor
		 * 
		 */
		char path_files[PATH_MAX];
		/**
		 * @brief Manycore pointer
		 * 
		 */
		ManyCoreArch *manycore_ptr;
		/**
		 * @brief Sequencer pointer
		 * 
		 */
		SequenceIlet *seq_ilet_ptr;

		/**
		 * @brief Flag when the components file aren't created
		 * 
		 */
		bool first_components = true;
		/**
		 * @brief Flag when iLet file isn't created
		 * 
		 */
		bool first_ilets = true;

		void init(ManyCoreArch *_manycore_ptr, SequenceIlet *_seq_ilet_ptr, Clock * _clk_instance);

		void write_components(JSON * info);
		void write_system(JSON * info);
		void write_ilets(JSON * info);

		static void *monitoring(void *obj);


};

#endif