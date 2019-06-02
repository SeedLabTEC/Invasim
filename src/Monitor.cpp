/**
* @file Monitor.cpp
* @brief Monitor source
* @author Dennis Porras Barrantes
* @date 31/03/19
**/

#include "../include/Monitor.h"

/**
 * @brief Construct a new Monitor:: Monitor object
 * 
 * @param _manycore_ptr 
 * @param _seq_ilet_ptr 
 * @param _clk_instance 
 */
Monitor::Monitor(ManyCoreArch *_manycore_ptr, SequenceIlet *_seq_ilet_ptr, Clock *_clk_instance)
{
	getcwd(this->path_files, PATH_MAX);
	this->init(_manycore_ptr, _seq_ilet_ptr, _clk_instance);
}

/**
 * @brief Construct a new Monitor:: Monitor object
 * 
 * @param _manycore_ptr 
 * @param _seq_ilet_ptr 
 * @param _path_files 
 * @param _clk_instance 
 */
Monitor::Monitor(ManyCoreArch *_manycore_ptr, SequenceIlet *_seq_ilet_ptr, std::string _path_files, Clock *_clk_instance)
{
	strcpy(this->path_files, _path_files.c_str());
	this->init(_manycore_ptr, _seq_ilet_ptr, _clk_instance);
}

/**
 * @brief Function that initialize pointers in monitor
 * 
 * @param _manycore_ptr 
 * @param _seq_ilet_ptr 
 * @param _clk_instance 
 */
void Monitor::init(ManyCoreArch *_manycore_ptr, SequenceIlet *_seq_ilet_ptr, Clock *_clk_instance)
{
	this->manycore_ptr = _manycore_ptr;
	this->clk_instance = _clk_instance;
	this->seq_ilet_ptr = _seq_ilet_ptr;
	dprintf("MONITOR: Monitor created in directory %s\n", this->path_files);
}


/**
 * @brief Start method which initializes main thread 
 * 
 */
void Monitor::start()
{
	//create threads
	pthread_create(&this->monitor_thread, NULL, Monitor::monitoring, (void *)this);
	//detach threads
	pthread_detach(this->monitor_thread);
}
/**
 * @brief Getter for working directory as std::string
 * 
 * @return std::string 
 */
std::string Monitor::get_working_dir()
{
	std::string path = this->path_files;
	return path;
}

/**
 * @brief Function that extracts the components info in disk
 * 
 * @param info 
 */
void Monitor::write_components(JSON *info)
{
	//Creating path for resources infor
	std::string path = "";
	path.append(this->path_files);
	path.append(RES_FILE);

	//Verify if file exists
	if (this->first_components)
	{
		JSON array = JSON::array();
		array.push_back((*info)["Components"][0]);
		this->write_disk(path, array, false);
	}
	else
	{
		this->write_disk(path, (*info)["Components"][0], true);
	}
	path.clear();

	//Create path for processing units
	path.append(this->path_files);
	int procs = this->manycore_ptr->get_procs();
	//Iterate in all processors
	for (int i = 1; i <= procs; i++)
	{
		//Append name of unit json file
		std::string tmp = path;
		tmp.append(PREFIX_PU);
		tmp.append(std::to_string(i));
		tmp.append(SUFIX_PU);

		//Verify if file exists
		if (this->first_components)
		{
			JSON array = JSON::array();
			array.push_back((*info)["Components"][i]);
			this->write_disk(tmp, array, false);
		}
		else
		{
			this->write_disk(tmp, (*info)["Components"][i], true);
		}

		tmp.clear();
	}
	//Set flag that files are created
	if (this->first_components)
	{
		this->first_components = false;
	}
	
}

/**
 * @brief Function that writes system information
 * 
 * @param info 
 */
void Monitor::write_system(JSON *info)
{
	std::string path = "";

	path.append(this->path_files);
	path.append(MANY_FILE);
	this->write_disk(path, (*info)["System"], false);
	
	path.clear();
}

/**
 * @brief Function that writes iLets info
 * 
 * @param info 
 */
void Monitor::write_ilets(JSON *info)
{
	//Create path for iLet files
	std::string path = "";
	path.append(this->path_files);
	path.append(ILET_FILE);
	//Verify if file exists
	if (this->first_ilets)
	{
		JSON array = JSON::array();
		array.push_back((*info)[0]);
		this->write_disk(path, array, false);
		this->first_ilets = false;
	}
	else
	{
		this->write_disk(path, (*info)[0], true);
	}
	path.clear();
}

/**
 * @brief Funtion that writes a json in disk, with a flag that allows to append data
 * 
 * @param path 
 * @param data 
 * @param append 
 */
void Monitor::write_disk(std::string path, JSON data, bool append)
{
	//Data to write
	std::string data_w;
	//Verify if needs to append
	if (append)
	{
		//Read json file from disk
		std::string line;
		std::ifstream r_file(path.c_str());
		std::getline(r_file, line);
		r_file.close();
		
		//Append data and create string
		JSON old = JSON::parse(line);
		old.push_back(data);
		data_w = old.dump();
	}
	else
	{
		//Create string with no append
		data_w = data.dump();
	}
	
	//Write in disk
	std::ofstream resources_file(path.c_str());
	resources_file << data_w << std::endl;
	resources_file.close();
}

/**
 * @brief Execution function that is executed by thread, it starts a loop that awaits the clock signal to request data from the components and write in disk.
 * 
 * @param obj 
 * @return void* 
 */
void *Monitor::monitoring(void *obj)
{
	Monitor *current = (Monitor *)obj;
	dprintf("MONITOR: Monitor started.\n");
	//Get mutex and conditional variable from clock
	pthread_mutex_t *clk_monitor_mutex = current->clk_instance->get_monitor_mutex_ptr();
	pthread_cond_t *clk_monitor_cond = current->clk_instance->get_monitor_cond_ptr();
	//Component loop
	while (1)
	{
		//Await clock signal
		pthread_cond_wait(clk_monitor_cond, clk_monitor_mutex);

		//Request components information
		JSON *system_info = current->manycore_ptr->monitoring();
		JSON *ilet_info = current->seq_ilet_ptr->monitoring();
		
		//Write data in disk
		current->write_system(system_info);
		current->write_components(system_info);
		//Verify if there are new iLets to write
		if (ilet_info->size() > 0)
		{
			current->write_ilets(ilet_info);
		}

		//Deallocate mempry
		delete system_info;
	}
	return NULL;
}