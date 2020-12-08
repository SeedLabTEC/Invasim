#include "include/json.hpp"
#include <string>
#include <iostream>
#include <fstream>

#define PROG_ID 0

using JSON = nlohmann::json;

int main() {
    std::string path = "bin/1.000000.json";

    //Read json file from disk
    std::string line;
    std::ifstream r_file(path.c_str());    
    std::getline(r_file, line);
    r_file.close();
    
    //Append data and create string
    JSON old_content = JSON::parse(line);

    float value = old_content[0]["lambda"];

    std::cout << std::to_string(value) << std::endl;

    float new_value = 1;

    old_content[0]["lambda"] = new_value;

    std::string data_w = old_content.dump();
    //Write in disk
	std::ofstream resources_file(path.c_str());
	resources_file << data_w << std::endl;
	resources_file.close();

    // for (JSON::iterator it = old_content.begin(); it != old_content.end(); ++it) {
    //     std::cout << "Program -- " << *it << '\n';

    //     /*if((*it)["Id"] == PROG_ID) {
    //         (*it)["lambda"] = 0.3;
    //     }*/

    //     //std::string program_str = (*it).dump();

    //     JSON program = (*it);

    //     /*std::string data_w = "[";
    //     data_w.append(program.dump());
    //     data_w.append("]");*/

    //     JSON array = JSON::array();
	// 	array.push_back(program);

    //     std::string data_w = array.dump();

    //     std::cout << "JSON: " << data_w << std::endl;

    //     //Write in disk
    //     std::string path_new = "bin/";
    //     path_new.append(std::to_string((float)((*it)["Id"])));
    //     path_new.append(".json");
    //     std::ofstream resources_file(path_new.c_str());
    //     resources_file << data_w << std::endl;
    //     resources_file.close();
    // }

    /*std::cout << "---------------------" << std::endl;

    for (auto& element : old_content) {
        std::cout << element << '\n';
    }
    
    std::string data_w = old_content.dump();
    //Write in disk
	std::ofstream resources_file(path.c_str());
	resources_file << data_w << std::endl;
	resources_file.close();*/
}