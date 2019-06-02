/**
* @file Monitor.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 31/03/19
**/

#ifndef INCLUDE_MONITOR_H_
#define INCLUDE_MONITOR_H_

#define MANY_FILE "/manycore.json"
#define RES_FILE "/resources.json"
#define ILET_FILE "/ilets.json"

#define PREFIX_PU "/unit_"
#define SUFIX_PU ".json"

#include <linux/limits.h>
#include <iostream>
#include <fstream>

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

		Clock * clk_instance;
		char path_files[PATH_MAX];
		ManyCoreArch *manycore_ptr;
		SequenceIlet *seq_ilet_ptr;

		bool first_components = true;
		bool first_ilets = true;

		void init(ManyCoreArch *_manycore_ptr, SequenceIlet *_seq_ilet_ptr, Clock * _clk_instance);

		void write_components(JSON * info);
		void write_system(JSON * info);
		void write_ilets(JSON * info);

		static void *monitoring(void *obj);


};

#endif