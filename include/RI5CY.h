/**
* @file RI5CY.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 23/08/19
**/

#ifndef INCLUDE_RI5CY_H_
#define INCLUDE_RI5CY_H_

#include "Utils.h"

#include "verilated.h"
#include "Vtop.h"
#include "Vtop__Syms.h"

#include <vector>

#define BOOT_ADDR 0x80

class RI5CY
{
public:
	RI5CY(int _id);

	~RI5CY();

	void load_program(uint32_t addr, const std::vector<char> &v);

	void clock_spin(uint32_t cycles);

	void init_processor();

	void reset_processor();

	void stop_fetching();

	void start_fetching();

	bool is_done();

	void print_regfile();

	vluint64_t cpuTime;

private:
	Vtop *cpu;
	int id;

	/* For debugging */
	unsigned int OLDREGFILE[32] = {0};
	unsigned int REGFILE[32] = {0};

	uint64_t mCycleCnt;
};

#endif