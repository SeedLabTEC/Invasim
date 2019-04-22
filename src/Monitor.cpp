/**
* @file Monitor.cpp
* @brief Description
* @author Dennis Porras Barrantes
* @date 31/03/19
**/

#include "../include/Monitor.h"

/**
* @brief Constructor
**/
Monitor::Monitor(ManyCoreArch *_manycore_ptr, SequenceIlet *_seq_ilet_ptr, Clock *_clk_instance)
{
	getcwd(this->path_files, PATH_MAX);
	this->init(_manycore_ptr, _seq_ilet_ptr, _clk_instance);
}

Monitor::Monitor(ManyCoreArch *_manycore_ptr, SequenceIlet *_seq_ilet_ptr, std::string _path_files, Clock *_clk_instance)
{
	strcpy(this->path_files, _path_files.c_str());
	this->init(_manycore_ptr, _seq_ilet_ptr, _clk_instance);
}

void Monitor::init(ManyCoreArch *_manycore_ptr, SequenceIlet *_seq_ilet_ptr, Clock *_clk_instance)
{
	this->manycore_ptr = _manycore_ptr;
	this->clk_instance = _clk_instance;
	this->seq_ilet_ptr = _seq_ilet_ptr;
	dprintf("MONITOR: Monitor created in directory %s\n", this->path_files);
}

/**
 * @brief Start method which initializes main thread 
 * */
void Monitor::start()
{
	//create threads
	pthread_create(&this->monitor_thread, NULL, Monitor::monitoring, (void *)this);
	//detach threads
	pthread_detach(this->monitor_thread);
}

void Monitor::write_components(JSON * info)
{
	std::string path = "";
	
	path.append(this->path_files);
	path.append(RES_FILE);
	this->write_disk(path, (*info)["Components"][0].dump().c_str());
	path.clear();

	path.append(this->path_files);
	int procs = this->manycore_ptr->get_procs();
	for(int i = 1; i <= procs; i++)
	{
		std::string tmp = path;
		tmp.append(PREFIX_PU);
		tmp.append(std::to_string(i));
		tmp.append(SUFIX_PU);

		this->write_disk(tmp, (*info)["Components"][i].dump().c_str());
		tmp.clear();
	}
}
void Monitor::write_system(JSON * info)
{
	std::string path = "";
	
	path.append(this->path_files);
	path.append(MANY_FILE);
	this->write_disk(path, (*info)["System"].dump().c_str());
	path.clear();
}

void Monitor::write_ilets(JSON * info)
{
	std::string path = "";
	
	path.append(this->path_files);
	path.append(ILET_FILE);
	this->write_disk(path, (*info).dump().c_str());
	path.clear();
}

void Monitor::write_disk(std::string path, const char * data)
{
	std::ofstream resources_file (path.c_str());
	resources_file << data << std::endl;
	resources_file.close();
}

void *Monitor::monitoring(void *obj)
{
	Monitor *current = (Monitor *)obj;
	dprintf("MONITOR: Monitor started.\n");
	pthread_mutex_t *clk_monitor_mutex = current->clk_instance->get_monitor_mutex_ptr();
	pthread_cond_t *clk_monitor_cond = current->clk_instance->get_monitor_cond_ptr();
	while (1)
	{
		pthread_cond_wait(clk_monitor_cond, clk_monitor_mutex);
		JSON *system_info = current->manycore_ptr->monitoring();
		JSON *ilet_info = current->seq_ilet_ptr->monitoring();
		std::cout << "MONITOR: System information: \n" << system_info->dump(4).c_str() << std::endl;;
		current->write_system(system_info);
		current->write_components(system_info);
		current->write_ilets(ilet_info);
		delete system_info;
		delete ilet_info;
	}
	return NULL;
}