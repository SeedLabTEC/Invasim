// #include "include/RI5CY.h"
// #include <fstream>
// #include <cstring> // for std::strlen
// #include <cstddef> // for std::size_t -> is a typedef on an unsinged int
// #include <vector>

// using namespace std;

// RI5CY *cpu_;

// #define BENCHMARK "/home/dennis/Documents/Invasim/RI5CY/tb/core/benchmark/"

// string programs[] = {
//     "codes/adpcm/adpcm.bin",
//     "codes/aes/aes.bin",
//     "codes/fft/fft.bin",
//     "codes/matrixmultiply/matrixmultiply.bin",
//     //"MiBench/automotive/automotive.bin",
//     "MiBench/office/stringsearch/search_small.bin"};

// void read_program(int index)
// {
//     string bin_file_path = BENCHMARK + programs[index];
//     ifstream ifd(bin_file_path, ios::binary | ios::ate);
//     int size = ifd.tellg();
//     ifd.seekg(0, ios::beg);
//     vector<char> buffer;
//     buffer.resize(size); // << resize not reserve
//     ifd.read(buffer.data(), size);
//     cpu_->load_program(0, buffer);
// }

// int main(int argc, char const *argv[])
// {
//     cpu_ = new RI5CY(1);

    

//     cpu_->init_processor();

//     for (int i = 0; i < 5; i++)
//     {
//         dprintf("Runnig program: %s\n", programs[i].c_str());

//         cpu_->stop_fetching();
//         cpu_->reset_processor();
//         read_program(i);
//         cpu_->start_fetching();

//         while (!cpu_->is_done())
//         {
//             cpu_->clock_spin(5);
//         }

//         dprintf("%d- execution finished in at %f ns!\n", i + 1, sc_time_stamp());

//         cpu_->print_regfile();

//     }

//     return 0;
// }

// double
// sc_time_stamp()
// {
//     return cpu_->cpuTime;
// }

#include "include/Environment.h"

int main(int argc, char const *argv[])
{
    dprintf("\nInvasive Computing Simulator\n\n\n");

    srand(1);

    Environment *env_0 = new Environment(atoi(argv[1]),
                                         atoi(argv[2]),
                                         0.80,
                                         "/home/dennis/Documents/Invasim/bin",
                                         1);
    env_0->start_environment();

    dprintf("DEBUG: Running %s steps...\n", argv[3]);
    env_0->step(atoi(argv[3]));

    return 0;
}
// // Remove a file
// #include <iostream>
// #include <fstream>
// #include <stdio.h> //for remove( ) and rename( )

// int main(void)
// {
//     std::string file;
//     std::cout << "Enter name of file to delete: ";
//     std::cin >> file;
//     if (remove(file.c_str()) != 0)
//         std::cout << "Remove operation failed" << std::endl;
//     else
//         std::cout << file << " has been removed." << std::endl;
//     return 0;
// }