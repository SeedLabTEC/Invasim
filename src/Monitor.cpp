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
Monitor::Monitor(ManyCoreArch *_manycore_ptr, Clock *_clk_instance)
{
	getcwd(this->path_files, PATH_MAX);
	this->init(_manycore_ptr, _clk_instance);
}

Monitor::Monitor(ManyCoreArch *_manycore_ptr, char *_path_files, Clock *_clk_instance)
{
	strcpy(this->path_files, _path_files);
	this->init(_manycore_ptr, _clk_instance);
}

void Monitor::init(ManyCoreArch *_manycore_ptr, Clock *_clk_instance)
{
	this->manycore_ptr = _manycore_ptr;
	this->clk_instance = _clk_instance;
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
	std::ofstream resources_file (path.c_str());
	resources_file << (*info)["Status"][0].dump().c_str() << std::endl;
	resources_file.close();
	
	path.clear();
}
void Monitor::write_system(JSON * info)
{

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
		dprintf("MONITOR: System information: \n%s\n", system_info->dump().c_str());
		current->write_components(system_info);
		delete system_info;
	}
	return NULL;
}