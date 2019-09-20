// Copyright 2017 Embecosm Limited <www.embecosm.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Simple Verilator model test bench
// Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>
// Contributor Graham Markall <graham.markall@embecosm.com>


#include "verilated.h"
#include "Vtop.h"
#include "Vtop__Syms.h"

#include <iostream>
#include <cstdint>
#include <cstdlib>

#include <fstream>
#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include <vector>

#include <stdio.h>

#define STARTprogrammADDR   0x80

using std::cout;
using std::cerr;
using std::endl;

using namespace std;

// Count of clock ticks

static vluint64_t cpuTime = 0;

static uint64_t mCycleCnt = 0;

Vtop *cpu;

unsigned int OLDREGFILE[32]={0},
             REGFILE[32]={0};

void REGfilePrint()
{
      unsigned int changeregfile=0;
      for (int alfa=0;alfa<32;alfa++)
      {
          REGFILE[alfa]=cpu->top->readREGfile(alfa);
          if (REGFILE[alfa]!=OLDREGFILE[alfa])
          {
             changeregfile|=(1<<alfa);
          }
      }
      
      printf("\n           %s",std::string(9*8+2,'-').c_str());
      printf("\n           |%4d %8d %8d %8d %8d %8d %8d %8d     |",0,1,2,3,4,5,6,7);
      printf("\n       %s",std::string(9*8+2+4,'-').c_str());
      //printf("\e[102m"); //green
      printf("\n       | 0 |%.8s ","--zero--");
      for (int alfa=1;alfa<8;alfa++)
      {
          if(changeregfile & (1<<alfa))
          {
             printf("\e[30;42m%.8x\e[39;0m ",cpu->top->readREGfile(alfa));
          }
          else
          {
             printf("%.8x ",cpu->top->readREGfile(alfa));
          }

      }
      printf("| R f\n       | 8 |");
      for (int alfa=8;alfa<16;alfa++)
      {
          if(changeregfile & (1<<alfa))
          {
             printf("\e[30;42m%.8x\e[39;0m ",cpu->top->readREGfile(alfa));
          }
          else
          {
             printf("%.8x ",cpu->top->readREGfile(alfa));
          }
      }
      printf("| E i\n       |16 |");
      for (int alfa=16;alfa<24;alfa++)
      {
          if(changeregfile & (1<<alfa))
          {
             printf("\e[30;42m%.8x\e[39;0m ",cpu->top->readREGfile(alfa));
          }
          else
          {
             printf("%.8x ",cpu->top->readREGfile(alfa));
          }
      }
      printf("| G l\n       |24 |");
      for (int alfa=24;alfa<32;alfa++)
      {
          if(changeregfile & (1<<alfa))
          {
             printf("\e[30;42m%.8x\e[39;0m ",cpu->top->readREGfile(alfa));
          }
          else
          {
             printf("%.8x ",cpu->top->readREGfile(alfa));
          }
      }
      for (int alfa=1;alfa<32;alfa++)
      {
         OLDREGFILE[alfa]=REGFILE[alfa];
      }
      
      printf("|   e");
      printf("\n       %s",std::string(9*8+2+4,'-').c_str());
      //printf("\e[49m"); //default
}
// Clock the CPU for a given number of cycles, dumping to the trace file at
// each clock edge.
void clockSpin(uint32_t cycles)
{
  for (uint32_t i = 0; i < cycles; i++)
  {
      cpu->clk_i = 0;
      cpu->eval ();
      cpuTime += 5;
      cpu->clk_i = 1;
      cpu->eval ();
      cpuTime += 5;
      mCycleCnt++;
      
      // printf("   test: %7.2f ns. pc_i f d e: ",sc_time_stamp()); 
 
      // if( (cpu->top->readADDtestPC_IF()&0xFF0000) == 0x0A0000 )
      // 	printf("\e[7m0x%.8x\e[27m   ", cpu->top->readADDtestPC_IF());
      // else
      //   printf("0x%.8x   ", cpu->top->readADDtestPC_IF());

      // if( (cpu->top->readADDtestPC_ID()&0xFF0000) == 0x0A0000 )
      // 	printf("\e[7m0x%.8x\e[27m   ", cpu->top->readADDtestPC_ID());
      // else
      //   printf("0x%.8x   ", cpu->top->readADDtestPC_ID());

      // if( (cpu->top->readADDtestPC_EX()&0xFF0000) == 0x0A0000 )
      // 	printf("\e[7m0x%.8x\e[27m   "   , cpu->top->readADDtestPC_EX());
      // else
      //   printf("0x%.8x   ", cpu->top->readADDtestPC_EX());

      // cout << endl;
      // //REGfilePrint();

      // cout << "Signal: " << (int)cpu->core_busy_o << endl;
  }
}



// Write some program code into memory:
//
// ; Store a word to memory first:
// li a5, 64
// li a4, 102
// sw a4, 0(a5)
// ; Repeated <repeat_factor> times (20 at present)
//
// ; Then do something a bit like _exit(0)
// li a1, 0
// li a2, 0
// li a3, 0
// li a7, 93
// ecall
//
// Execution begins at 0x80, so that's where we write our code.
// void loadProgram(uint32_t addr)
// {
//   //uint32_t addr = 0x80;
//   cout << "\e[93m   Start program address : 0x" << std::hex << addr << "\e[39m" <<endl;
    
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x0, 0x93);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x1, 0x07);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x2, 0x00);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x3, 0x04);

//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x4, 0x13);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x5, 0x07);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x6, 0x60);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x7, 0x06);

//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x8, 0x23);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x9, 0xa0);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0xa, 0xe7);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0xb, 0x00);

//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0xc, 0x03);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0xd, 0xa8);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0xe, 0x07);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0xf, 0x00);

//   addr+=16;
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x0, 0x93);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x1, 0x05);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x2, 0x00);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x3, 0x00);

//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x4, 0x13);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x5, 0x06);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x6, 0x00);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x7, 0x00);

//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x8, 0x93);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x9, 0x06);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0xa, 0x00);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0xb, 0x00);

//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0xc, 0x93);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0xd, 0x08);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0xe, 0xd0);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0xf, 0x05);

//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x10, 0x73);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x11, 0x00);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x12, 0x00);
//   cpu->top->ram_i->dp_ram_i->writeByte (addr + 0x13, 0x00);
//   addr+=20;
// printf("addr end: %d\n",addr);
 
// // print Instruc MEM
//    for(unsigned int alfa=0x80; alfa < addr; alfa+=4)
//    {
//      printf("INSTR MEM: %.4d (0x%.4x)   0x%2.2x%2.2x_%2.2x%2.2x\n",alfa,
//                                                                    alfa,
//                                                                    cpu->top->ram_i->dp_ram_i->readByte(alfa+3),
//                                                                    cpu->top->ram_i->dp_ram_i->readByte(alfa+2),
//                                                                    cpu->top->ram_i->dp_ram_i->readByte(alfa+1),
//                                                                    cpu->top->ram_i->dp_ram_i->readByte(alfa+0) 
//      );
//    }
// }

void
loadProgram(uint32_t addr, const vector<char>& v)
{
   cout << "\e[93m   Start program address : 0x" << std::hex << addr << "\e[39m" << endl;
   unsigned int offset = 0;
   for (int i = 0; i < v.size(); ++i)
   {
      cpu->top->ram_i->dp_ram_i->writeByte (addr + offset, (unsigned char) v[i]);
      if (addr == 0x80 || addr == (0x80 + 1) || addr == (0x80 + 2) || addr == (0x80 + 3))
      {
         printf("Offset: %d\n", offset);
         printf("Addr: 0x%.8x\n", addr + offset);
         printf("Data: 0x%.2x\n", (unsigned char) v[i]);
      }
      if ((i+1) % 4 == 0)
      {
         offset = 0;
         addr += 4;
      }
      else 
         offset++;
   }
   printf("addr end: 0x%.8x\n",addr);
 
   // print Instruc MEM
   // for(unsigned int alfa=0x80; alfa < addr; alfa+=4)
   // {
   //   printf("INSTR MEM: %.4d (0x%.4x)   0x%2.2x%2.2x_%2.2x%2.2x\n",alfa,
   //                                                                 alfa,
   //                                                                 cpu->top->ram_i->dp_ram_i->readByte(alfa+3),
   //                                                                 cpu->top->ram_i->dp_ram_i->readByte(alfa+2),
   //                                                                 cpu->top->ram_i->dp_ram_i->readByte(alfa+1),
   //                                                                 cpu->top->ram_i->dp_ram_i->readByte(alfa+0) 
   //   );
   // }
}

int
main (int    argc,
      char * argv[])
{
  Verilated::commandArgs(argc, argv);
  // Instantiate the model
  cpu = new Vtop;

  char * bin_file_path = argv[1];
  int cycles = atoi(argv[2]);
  
  ifstream ifd(bin_file_path, ios::binary | ios::ate);
  int size = ifd.tellg();
  ifd.seekg(0, ios::beg);
  vector<char> buffer;
  buffer.resize(size); // << resize not reserve
  ifd.read(buffer.data(), size);

  cout << "\e[32m"; //green
  cout << " irq_i            = 0\n";
  cout << " debug_req_i      = 0\n";
  cout << " fetch_enable_i   = 0\n";
  cout << "\e[39m"; //default

  // Fix some signals for now.
  cpu->irq_i          = 0;
  cpu->debug_req_i    = 0;
  cpu->fetch_enable_i = 0;
  cpu->program_exit   = 0; 


  cout << "\e[33mLoad Programm to ram:\e[39m\n";
  // Put a few instructions in memory
  loadProgram(0, buffer);

  // Cycle through reset
  cpu->rstn_i = 0;
  clockSpin(5);
  cpu->rstn_i = 1;

  // Let things run for a few cycles while the CPU 
  clockSpin(5);


  cout << "\e[34mTest resume\e[39m" << endl;

  //fetch enable:
  cout << "\e[32m"; //green
  cout << " fetch_enable_i   = 1\n";
  cout << "\e[39m"; //default
  cpu->fetch_enable_i = 1;
  

  cout << "Cycling clock to run for a few instructions" << endl;
  int i = 0;
  while (cpu->program_exit != 1)
  {
    clockSpin(1000);
    i++;
  }
  printf("Se terminó en %d\n", i);
  REGfilePrint();
  cout << endl;
 
  // Tidy up
  delete cpu;

}

//! Function to handle $time calls in the Verilog

double
sc_time_stamp ()
{
  return cpuTime;

}

// Local Variables:
// mode: C++
// c-file-style: "gnu"
// show-trailing-whitespace: t
// End:
