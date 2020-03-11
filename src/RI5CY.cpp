/**
* @file RI5CY.cpp
* @brief Description
* @author Dennis Porras Barrantes
* @date 23/08/19
**/

#include "../include/RI5CY.h"

/**
* @brief Constructor
**/
RI5CY::RI5CY(int _id)
{
    this->id = _id;
    this->cpuTime = 0;
    this->mCycleCnt = 0;
    this->cpu = new Vtop;
}

void RI5CY::load_program(uint32_t addr, const std::vector<char> &v)
{
    // dprintf("CORE RI5CY %d: Start program address : 0x%x\n", this->id, addr);
    // std::cout << "Start program address : " << addr << std::endl;
    unsigned int offset = 0;
    for (unsigned int i = 0; i < v.size(); ++i)
    {
        this->cpu->top->ram_i->dp_ram_i->writeByte(addr + offset, (unsigned char)v[i]);
        if ((i + 1) % 4 == 0)
        {
            offset = 0;
            addr += 4;
        }
        else
            offset++;
    }
    // dprintf("addr end: 0x%.8x\n", addr);
}

void RI5CY::clock_spin(uint32_t cycles)
{
    for (uint32_t i = 0; i < cycles; i++)
    {
        this->cpu->clk_i = 0;
        this->cpu->eval();
        this->cpuTime += 5;
        this->cpu->clk_i = 1;
        this->cpu->eval();
        this->cpuTime += 5;
        this->mCycleCnt++;
    }
}

void RI5CY::init_processor()
{
    this->cpu->irq_i = 0;
    this->cpu->debug_req_i = 0;
    this->cpu->program_exit = 0;
    // std::cout << "Processor initialized" << std::endl;
}

void RI5CY::reset_processor()
{
    this->cpuTime = 0;
    this->cpu->rstn_i = 0;
    this->clock_spin(5);
    this->cpu->rstn_i = 1;
    this->clock_spin(5);
    // std::cout << "Done with processor reset" << std::endl;
}

void RI5CY::stop_fetching()
{
    this->cpu->fetch_enable_i = 0;
    // std::cout << "Processor stopped fetching" << std::endl;
}

void RI5CY::start_fetching()
{
    this->cpu->fetch_enable_i = 1;
    // std::cout << "Processor started fetching" << std::endl;
}

bool RI5CY::is_done()
{
    return this->cpu->program_exit == 1;
}

/* For debugging */
void RI5CY::print_regfile()
{
    unsigned int changeregfile = 0;
    for (int alfa = 0; alfa < 32; alfa++)
    {
        this->REGFILE[alfa] = this->cpu->top->readREGfile(alfa);
        if (this->REGFILE[alfa] != this->OLDREGFILE[alfa])
        {
            changeregfile |= (1 << alfa);
        }
    }

    printf("\n           %s", std::string(9 * 8 + 2, '-').c_str());
    printf("\n           |%4d %8d %8d %8d %8d %8d %8d %8d     |", 0, 1, 2, 3, 4, 5, 6, 7);
    printf("\n       %s", std::string(9 * 8 + 2 + 4, '-').c_str());
    //printf("\e[102m"); //green
    printf("\n       | 0 |%.8s ", "--zero--");
    for (int alfa = 1; alfa < 8; alfa++)
    {
        if (changeregfile & (1 << alfa))
        {
            printf("\e[30;42m%.8x\e[39;0m ", this->cpu->top->readREGfile(alfa));
        }
        else
        {
            printf("%.8x ", this->cpu->top->readREGfile(alfa));
        }
    }
    printf("| R f\n       | 8 |");
    for (int alfa = 8; alfa < 16; alfa++)
    {
        if (changeregfile & (1 << alfa))
        {
            printf("\e[30;42m%.8x\e[39;0m ", this->cpu->top->readREGfile(alfa));
        }
        else
        {
            printf("%.8x ", this->cpu->top->readREGfile(alfa));
        }
    }
    printf("| E i\n       |16 |");
    for (int alfa = 16; alfa < 24; alfa++)
    {
        if (changeregfile & (1 << alfa))
        {
            printf("\e[30;42m%.8x\e[39;0m ", this->cpu->top->readREGfile(alfa));
        }
        else
        {
            printf("%.8x ", this->cpu->top->readREGfile(alfa));
        }
    }
    printf("| G l\n       |24 |");
    for (int alfa = 24; alfa < 32; alfa++)
    {
        if (changeregfile & (1 << alfa))
        {
            printf("\e[30;42m%.8x\e[39;0m ", this->cpu->top->readREGfile(alfa));
        }
        else
        {
            printf("%.8x ", this->cpu->top->readREGfile(alfa));
        }
    }
    for (int alfa = 1; alfa < 32; alfa++)
    {
        this->OLDREGFILE[alfa] = this->REGFILE[alfa];
    }

    printf("|   e");
    printf("\n       %s\n", std::string(9 * 8 + 2 + 4, '-').c_str());
    //printf("\e[49m"); //default
}