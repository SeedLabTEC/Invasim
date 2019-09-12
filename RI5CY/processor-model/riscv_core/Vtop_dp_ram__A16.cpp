// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop_dp_ram__A16.h"
#include "Vtop__Syms.h"

#include "verilated_dpi.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(Vtop_dp_ram__A16) {
    // Reset internal values
    // Reset structure values
    _ctor_var_reset();
}

void Vtop_dp_ram__A16::__Vconfigure(Vtop__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vtop_dp_ram__A16::~Vtop_dp_ram__A16() {
}

//--------------------
// Internal Methods

uint32_t Vtop_dp_ram__A16::readByte(uint32_t byte_addr) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtop_dp_ram__A16::readByte\n"); );
    // Variables
    VL_OUT8(readByte__Vfuncrtn,7,0);
    Vtop__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    readByte__Vfuncrtn = vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
	[(0x3fffffU & byte_addr)];
    // Final
    return (readByte__Vfuncrtn);
}

void Vtop_dp_ram__A16::writeByte(uint32_t byte_addr, uint32_t val) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtop_dp_ram__A16::writeByte\n"); );
    // Variables
    Vtop__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem[(0x3fffffU 
						   & byte_addr)] 
	= val;
}

VL_INLINE_OPT void Vtop_dp_ram__A16::_sequent__TOP__top__ram_i__dp_ram_i__1(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtop_dp_ram__A16::_sequent__TOP__top__ram_i__dp_ram_i__1\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvset__mem__v0 = 0U;
    vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvset__mem__v1 = 0U;
    vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvset__mem__v2 = 0U;
    vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvset__mem__v3 = 0U;
    // ALWAYS at dp_ram.sv:41
    if (vlSymsp->TOP__top__ram_i.__PVT__ram_data_req) {
	if (vlSymsp->TOP__top__ram_i.__PVT__ram_data_we) {
	    if ((1U & (IData)(vlSymsp->TOP__top__ram_i.__PVT__ram_data_be))) {
		vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvval__mem__v0 
		    = (0xffU & vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata);
		vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvset__mem__v0 = 1U;
		vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvdim0__mem__v0 
		    = (0x3ffffcU & vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr);
	    }
	    if ((2U & (IData)(vlSymsp->TOP__top__ram_i.__PVT__ram_data_be))) {
		vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvval__mem__v1 
		    = (0xffU & (vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata 
				>> 8U));
		vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvset__mem__v1 = 1U;
		vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvdim0__mem__v1 
		    = (0x3fffffU & ((IData)(1U) + (0x3ffffcU 
						   & vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr)));
	    }
	    if ((4U & (IData)(vlSymsp->TOP__top__ram_i.__PVT__ram_data_be))) {
		vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvval__mem__v2 
		    = (0xffU & (vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata 
				>> 0x10U));
		vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvset__mem__v2 = 1U;
		vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvdim0__mem__v2 
		    = (0x3fffffU & ((IData)(2U) + (0x3ffffcU 
						   & vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr)));
	    }
	    if ((8U & (IData)(vlSymsp->TOP__top__ram_i.__PVT__ram_data_be))) {
		vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvval__mem__v3 
		    = (0xffU & (vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata 
				>> 0x18U));
		vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvset__mem__v3 = 1U;
		vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvdim0__mem__v3 
		    = (0x3fffffU & ((IData)(3U) + (0x3ffffcU 
						   & vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr)));
	    }
	}
    }
}

VL_INLINE_OPT void Vtop_dp_ram__A16::_sequent__TOP__top__ram_i__dp_ram_i__2(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtop_dp_ram__A16::_sequent__TOP__top__ram_i__dp_ram_i__2\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at dp_ram.sv:41
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[0U] 
	= ((0xffffff00U & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[0U]) 
	   | vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
	   [(0x3ffff0U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)]);
    if (vlSymsp->TOP__top__ram_i.__PVT__ram_data_req) {
	if ((1U & (~ (IData)(vlSymsp->TOP__top__ram_i.__PVT__ram_data_we)))) {
	    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_b_o 
		= ((0xffffff00U & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_b_o) 
		   | vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
		   [(0x3ffffcU & vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr)]);
	    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_b_o 
		= ((0xffff00ffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_b_o) 
		   | (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
		      [(0x3fffffU & ((IData)(1U) + 
				     (0x3ffffcU & vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr)))] 
		      << 8U));
	    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_b_o 
		= ((0xff00ffffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_b_o) 
		   | (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
		      [(0x3fffffU & ((IData)(2U) + 
				     (0x3ffffcU & vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr)))] 
		      << 0x10U));
	    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_b_o 
		= ((0xffffffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_b_o) 
		   | (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
		      [(0x3fffffU & ((IData)(3U) + 
				     (0x3ffffcU & vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr)))] 
		      << 0x18U));
	}
    }
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[0U] 
	= ((0xffff00ffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[0U]) 
	   | (0xffffff00U & (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
			     [(0x3fffffU & ((IData)(1U) 
					    + (0x3ffff0U 
					       & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))] 
			     << 8U)));
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[0U] 
	= ((0xff00ffffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[0U]) 
	   | (0xffff0000U & (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
			     [(0x3fffffU & ((IData)(2U) 
					    + (0x3ffff0U 
					       & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))] 
			     << 0x10U)));
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[0U] 
	= ((0xffffffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[0U]) 
	   | (0xff000000U & (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
			     [(0x3fffffU & ((IData)(3U) 
					    + (0x3ffff0U 
					       & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))] 
			     << 0x18U)));
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[1U] 
	= ((0xffffff00U & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[1U]) 
	   | vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
	   [(0x3fffffU & ((IData)(4U) + (0x3ffff0U 
					 & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))]);
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[1U] 
	= ((0xffff00ffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[1U]) 
	   | (0xffffff00U & (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
			     [(0x3fffffU & ((IData)(5U) 
					    + (0x3ffff0U 
					       & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))] 
			     << 8U)));
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[1U] 
	= ((0xff00ffffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[1U]) 
	   | (0xffff0000U & (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
			     [(0x3fffffU & ((IData)(6U) 
					    + (0x3ffff0U 
					       & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))] 
			     << 0x10U)));
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[1U] 
	= ((0xffffffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[1U]) 
	   | (0xff000000U & (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
			     [(0x3fffffU & ((IData)(7U) 
					    + (0x3ffff0U 
					       & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))] 
			     << 0x18U)));
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[2U] 
	= ((0xffffff00U & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[2U]) 
	   | vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
	   [(0x3fffffU & ((IData)(8U) + (0x3ffff0U 
					 & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))]);
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[2U] 
	= ((0xffff00ffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[2U]) 
	   | (0xffffff00U & (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
			     [(0x3fffffU & ((IData)(9U) 
					    + (0x3ffff0U 
					       & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))] 
			     << 8U)));
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[2U] 
	= ((0xff00ffffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[2U]) 
	   | (0xffff0000U & (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
			     [(0x3fffffU & ((IData)(0xaU) 
					    + (0x3ffff0U 
					       & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))] 
			     << 0x10U)));
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[2U] 
	= ((0xffffffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[2U]) 
	   | (0xff000000U & (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
			     [(0x3fffffU & ((IData)(0xbU) 
					    + (0x3ffff0U 
					       & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))] 
			     << 0x18U)));
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[3U] 
	= ((0xffffff00U & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[3U]) 
	   | vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
	   [(0x3fffffU & ((IData)(0xcU) + (0x3ffff0U 
					   & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))]);
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[3U] 
	= ((0xffff00ffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[3U]) 
	   | (0xffffff00U & (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
			     [(0x3fffffU & ((IData)(0xdU) 
					    + (0x3ffff0U 
					       & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))] 
			     << 8U)));
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[3U] 
	= ((0xff00ffffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[3U]) 
	   | (0xffff0000U & (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
			     [(0x3fffffU & ((IData)(0xeU) 
					    + (0x3ffff0U 
					       & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))] 
			     << 0x10U)));
    vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[3U] 
	= ((0xffffffU & vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_a_o[3U]) 
	   | (0xff000000U & (vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem
			     [(0x3fffffU & ((IData)(0xfU) 
					    + (0x3ffff0U 
					       & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__if_stage_i__DOT__genblk1__DOT__prefetch_128__DOT__prefetch_buffer_i__DOT__L0_buffer_i__DOT__instr_addr_int)))] 
			     << 0x18U)));
    // ALWAYSPOST at dp_ram.sv:68
    if (vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvset__mem__v0) {
	vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem[vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvdim0__mem__v0] 
	    = vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvval__mem__v0;
    }
    if (vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvset__mem__v1) {
	vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem[vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvdim0__mem__v1] 
	    = vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvval__mem__v1;
    }
    if (vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvset__mem__v2) {
	vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem[vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvdim0__mem__v2] 
	    = vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvval__mem__v2;
    }
    if (vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvset__mem__v3) {
	vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__mem[vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvdim0__mem__v3] 
	    = vlSymsp->TOP__top__ram_i__dp_ram_i.__Vdlyvval__mem__v3;
    }
}

void Vtop_dp_ram__A16::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vtop_dp_ram__A16::_ctor_var_reset\n"); );
    // Body
    __PVT__clk = VL_RAND_RESET_I(1);
    __PVT__en_a_i = VL_RAND_RESET_I(1);
    __PVT__addr_a_i = VL_RAND_RESET_I(22);
    __PVT__wdata_a_i = VL_RAND_RESET_I(32);
    VL_RAND_RESET_W(128,__PVT__rdata_a_o);
    __PVT__we_a_i = VL_RAND_RESET_I(1);
    __PVT__be_a_i = VL_RAND_RESET_I(4);
    __PVT__en_b_i = VL_RAND_RESET_I(1);
    __PVT__addr_b_i = VL_RAND_RESET_I(22);
    __PVT__wdata_b_i = VL_RAND_RESET_I(32);
    __PVT__rdata_b_o = VL_RAND_RESET_I(32);
    __PVT__we_b_i = VL_RAND_RESET_I(1);
    __PVT__be_b_i = VL_RAND_RESET_I(4);
    { int __Vi0=0; for (; __Vi0<4194304; ++__Vi0) {
	    __PVT__mem[__Vi0] = VL_RAND_RESET_I(8);
    }}
    __Vdlyvdim0__mem__v0 = VL_RAND_RESET_I(22);
    __Vdlyvval__mem__v0 = VL_RAND_RESET_I(8);
    __Vdlyvset__mem__v0 = VL_RAND_RESET_I(1);
    __Vdlyvdim0__mem__v1 = VL_RAND_RESET_I(22);
    __Vdlyvval__mem__v1 = VL_RAND_RESET_I(8);
    __Vdlyvset__mem__v1 = VL_RAND_RESET_I(1);
    __Vdlyvdim0__mem__v2 = VL_RAND_RESET_I(22);
    __Vdlyvval__mem__v2 = VL_RAND_RESET_I(8);
    __Vdlyvset__mem__v2 = VL_RAND_RESET_I(1);
    __Vdlyvdim0__mem__v3 = VL_RAND_RESET_I(22);
    __Vdlyvval__mem__v3 = VL_RAND_RESET_I(8);
    __Vdlyvset__mem__v3 = VL_RAND_RESET_I(1);
}
