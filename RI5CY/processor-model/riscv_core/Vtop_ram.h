// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef _Vtop_ram_H_
#define _Vtop_ram_H_

#include "verilated_heavy.h"
#include "Vtop__Dpi.h"

class Vtop__Syms;
class Vtop_dp_ram__A16;

//----------

VL_MODULE(Vtop_ram) {
  public:
    // CELLS
    Vtop_dp_ram__A16*  	dp_ram_i;
    
    // PORTS
    // Begin mtask footprint  all: 
    VL_IN8(__PVT__clk,0,0);
    VL_IN8(__PVT__rst_ni,0,0);
    VL_IN8(__PVT__instr_req_i,0,0);
    VL_OUT8(__PVT__instr_rvalid_o,0,0);
    VL_OUT8(__PVT__instr_gnt_o,0,0);
    VL_IN8(__PVT__data_req_i,0,0);
    VL_IN8(__PVT__data_we_i,0,0);
    VL_IN8(__PVT__data_be_i,3,0);
    VL_OUT8(__PVT__data_rvalid_o,0,0);
    VL_OUT8(__PVT__data_gnt_o,0,0);
    VL_OUT8(__PVT__exit_valid_o,0,0);
    VL_IN(__PVT__instr_addr_i,21,0);
    VL_OUTW(__PVT__instr_rdata_o,127,0,4);
    VL_IN(__PVT__data_addr_i,31,0);
    VL_IN(__PVT__data_wdata_i,31,0);
    VL_OUT(__PVT__data_rdata_o,31,0);
    VL_OUT(__PVT__exit_value_o,31,0);
    
    // LOCAL SIGNALS
    // Begin mtask footprint  all: 
    VL_SIG8(__PVT__select_rdata_d,1,0);
    VL_SIG8(__PVT__select_rdata_q,1,0);
    VL_SIG8(__PVT__ram_data_req,0,0);
    VL_SIG8(__PVT__ram_data_we,0,0);
    VL_SIG8(__PVT__ram_data_be,3,0);
    VL_SIG(__PVT__ram_data_addr,21,0);
    VL_SIG(__PVT__ram_data_wdata,31,0);
    
    // LOCAL VARIABLES
    
    // INTERNAL VARIABLES
  private:
    Vtop__Syms* __VlSymsp;  // Symbol table
  public:
    
    // PARAMETERS
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop_ram);  ///< Copying not allowed
  public:
    Vtop_ram(const char* name="TOP");
    ~Vtop_ram();
    
    // API METHODS
    
    // INTERNAL METHODS
    void __Vconfigure(Vtop__Syms* symsp, bool first);
    static void _combo__TOP__top__ram_i__4(Vtop__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _multiclk__TOP__top__ram_i__5(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__top__ram_i__2(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__top__ram_i__3(Vtop__Syms* __restrict vlSymsp);
    static void _settle__TOP__top__ram_i__1(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(128);

#endif // guard
