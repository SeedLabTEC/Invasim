// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef _Vtop_dp_ram__A16_H_
#define _Vtop_dp_ram__A16_H_

#include "verilated_heavy.h"
#include "Vtop__Dpi.h"

class Vtop__Syms;

//----------

VL_MODULE(Vtop_dp_ram__A16) {
  public:
    
    // PORTS
    // Begin mtask footprint  all: 
    VL_IN8(__PVT__clk,0,0);
    VL_IN8(__PVT__en_a_i,0,0);
    VL_IN8(__PVT__we_a_i,0,0);
    VL_IN8(__PVT__be_a_i,3,0);
    VL_IN8(__PVT__en_b_i,0,0);
    VL_IN8(__PVT__we_b_i,0,0);
    VL_IN8(__PVT__be_b_i,3,0);
    VL_IN(__PVT__addr_a_i,21,0);
    VL_IN(__PVT__wdata_a_i,31,0);
    VL_OUTW(__PVT__rdata_a_o,127,0,4);
    VL_IN(__PVT__addr_b_i,21,0);
    VL_IN(__PVT__wdata_b_i,31,0);
    VL_OUT(__PVT__rdata_b_o,31,0);
    
    // LOCAL SIGNALS
    // Begin mtask footprint  all: 
    VL_SIG8(__PVT__mem[4194304],7,0);
    
    // LOCAL VARIABLES
    // Begin mtask footprint  all: 
    VL_SIG8(__Vdlyvval__mem__v0,7,0);
    VL_SIG8(__Vdlyvset__mem__v0,0,0);
    VL_SIG8(__Vdlyvval__mem__v1,7,0);
    VL_SIG8(__Vdlyvset__mem__v1,0,0);
    VL_SIG8(__Vdlyvval__mem__v2,7,0);
    VL_SIG8(__Vdlyvset__mem__v2,0,0);
    VL_SIG8(__Vdlyvval__mem__v3,7,0);
    VL_SIG8(__Vdlyvset__mem__v3,0,0);
    VL_SIG(__Vdlyvdim0__mem__v0,21,0);
    VL_SIG(__Vdlyvdim0__mem__v1,21,0);
    VL_SIG(__Vdlyvdim0__mem__v2,21,0);
    VL_SIG(__Vdlyvdim0__mem__v3,21,0);
    
    // INTERNAL VARIABLES
  private:
    Vtop__Syms* __VlSymsp;  // Symbol table
  public:
    
    // PARAMETERS
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop_dp_ram__A16);  ///< Copying not allowed
  public:
    Vtop_dp_ram__A16(const char* name="TOP");
    ~Vtop_dp_ram__A16();
    
    // API METHODS
    
    // INTERNAL METHODS
    void __Vconfigure(Vtop__Syms* symsp, bool first);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _sequent__TOP__top__ram_i__dp_ram_i__1(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__top__ram_i__dp_ram_i__2(Vtop__Syms* __restrict vlSymsp);
    uint32_t readByte(uint32_t byte_addr);
    void writeByte(uint32_t byte_addr, uint32_t val);
} VL_ATTR_ALIGNED(128);

#endif // guard
