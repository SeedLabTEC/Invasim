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

#define PREFIX_PU "/unit_"
#define SUFIX_PU ".json"

#include <linux/limits.h>
#include <iostream>
#include <fstream>

#include "Clock.h"
#include "ManyCoreArch.h"

#include "Utils.h"

class Monitor 
{
	public: 
		Monitor(ManyCoreArch *_manycore_ptr, Clock * _clk_instance);
		Monitor(ManyCoreArch *_manycore_ptr, std::string  _path_files, Clock * _clk_instance);

		void start();

	private:
		pthread_t monitor_thread;

		Clock * clk_instance;
		char path_files[PATH_MAX];
		ManyCoreArch *manycore_ptr;

		void init(ManyCoreArch *_manycore_ptr, Clock * _clk_instance);

		void write_components(JSON * info);
		void write_system(JSON * info);
		void write_disk(std::string path, const char * data);

		static void *monitoring(void *obj);


};

#endif