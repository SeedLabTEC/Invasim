// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vtop__Syms_H_
#define _Vtop__Syms_H_

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "Vtop.h"
#include "Vtop_top.h"
#include "Vtop_mm_ram__R16.h"
#include "Vtop___024unit.h"
#include "Vtop_dp_ram__A16.h"

// DPI TYPES for DPI Export callbacks (Internal use)

// SYMS CLASS
class Vtop__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vtop*                          TOPp;
    Vtop_top                       TOP__top;
    Vtop_mm_ram__R16               TOP__top__ram_i;
    Vtop_dp_ram__A16               TOP__top__ram_i__dp_ram_i;
    
    // CREATORS
    Vtop__Syms(Vtop* topp, const char* namep);
    ~Vtop__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(64);

#endif  // guard
