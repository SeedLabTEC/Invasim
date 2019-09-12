// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef _Vtop___024unit_H_
#define _Vtop___024unit_H_

#include "verilated_heavy.h"
#include "Vtop__Dpi.h"

class Vtop__Syms;

//----------

VL_MODULE(Vtop___024unit) {
  public:
    
    // PORTS
    
    // LOCAL SIGNALS
    
    // LOCAL VARIABLES
    
    // INTERNAL VARIABLES
  private:
    Vtop__Syms* __VlSymsp;  // Symbol table
  public:
    
    // PARAMETERS
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop___024unit);  ///< Copying not allowed
  public:
    Vtop___024unit(const char* name="TOP");
    ~Vtop___024unit();
    
    // API METHODS
    
    // INTERNAL METHODS
    void __Vconfigure(Vtop__Syms* symsp, bool first);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
} VL_ATTR_ALIGNED(128);

#endif // guard
