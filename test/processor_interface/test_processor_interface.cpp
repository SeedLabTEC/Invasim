#include "../../include/RI5CY.h"
#include <fstream>
#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include <vector>
#include <ctime>

using namespace std;

RI5CY *cpu_;

#define BENCHMARK_ "../../RI5CY/tb/core/benchmark/"

string programs[] = {
    // "codes/adpcm/adpcm.bin",
    // "codes/aes/aes.bin",
    // "codes/fft/fft.bin",
    //"codes/matrixmultiply/matrixmultiply.bin"};//,
    "MiBench/automotive/basicmath/basicmath.bin"};
    // "MiBench/office/stringsearch/search_small.bin"};

void read_program(int index)
{
    string bin_file_path = BENCHMARK_ + programs[index];
    ifstream ifd(bin_file_path, ios::binary | ios::ate);
    int size = ifd.tellg();
    ifd.seekg(0, ios::beg);
    vector<char> buffer;
    buffer.resize(size); // << resize not reserve
    ifd.read(buffer.data(), size);
    cpu_->load_program(0, buffer);
}

int main(int argc, char const *argv[])
{
    cpu_ = new RI5CY(1);

    

    cpu_->init_processor();

    for (int i = 0; i < 5; i++)
    {
        dprintf("Runnig program: %s\n", programs[i].c_str());

        cpu_->stop_fetching();
        cpu_->reset_processor();
        read_program(i);
        cpu_->start_fetching();

        while (!cpu_->is_done())
        {
            //clock_t begin = clock();
            cpu_->clock_spin(1);
            //clock_t end = clock();
            //double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            //dprintf("Este ciclo dura: %f s\n", elapsed_secs);
        }

        dprintf("%s- execution finished in at %f ns!\n", programs[i].c_str(), sc_time_stamp());

        cpu_->print_regfile();

    }

    return 0;
}

double
sc_time_stamp()
{
    return cpu_->cpuTime;
}
