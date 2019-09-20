// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop_ram.h"
#include "Vtop__Syms.h"

#include "verilated_dpi.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(Vtop_ram) {
    VL_CELL(dp_ram_i, Vtop_dp_ram__A16);
    // Reset internal values
    // Reset structure values
    _ctor_var_reset();
}

void Vtop_ram::__Vconfigure(Vtop__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vtop_ram::~Vtop_ram() {
}

//--------------------
// Internal Methods

void Vtop_ram::_settle__TOP__top__ram_i__1(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_ram::_settle__TOP__top__ram_i__1\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at ram.sv:107
    vlSymsp->TOP__top__ram_i.__PVT__data_rdata_o = 0U;
    if ((0U == (IData)(vlSymsp->TOP__top__ram_i.__PVT__select_rdata_q))) {
	vlSymsp->TOP__top__ram_i.__PVT__data_rdata_o 
	    = vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_b_o;
    } else {
	if (VL_UNLIKELY((2U == (IData)(vlSymsp->TOP__top__ram_i.__PVT__select_rdata_q)))) {
	    VL_WRITEF("out of bounds read from %08x\n",
		      32,vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
	    VL_FINISH_MT("ram.sv",114,"");
	}
    }
    // ALWAYS at ram.sv:61
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_we = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex) {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_we 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex;
	    }
	} else {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_we 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex;
	    }
	}
    }
    // ALWAYS at ram.sv:61
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex) {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr 
		    = (0x3fffffU & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
	    }
	} else {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr 
		    = (0x3fffffU & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
	    }
	}
    }
    // ALWAYS at ram.sv:61
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_req = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex) {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_req 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp;
	    }
	} else {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_req 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp;
	    }
	}
    }
    // ALWAYS at ram.sv:61
    vlSymsp->TOP__top__ram_i.__PVT__exit_valid_o = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex) {
	    if ((0x400000U <= vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		if ((0x20000004U == vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		    vlSymsp->TOP__top__ram_i.__PVT__exit_valid_o = 1U;
		}
	    }
	}
    }
    // ALWAYS at ram.sv:61
    vlSymsp->TOP__top__ram_i.__PVT__select_rdata_d = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if ((1U & (~ (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex)))) {
	    vlSymsp->TOP__top__ram_i.__PVT__select_rdata_d 
		= ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
		    ? 0U : 2U);
	}
    }
    // ALWAYS at ram.sv:61
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_be = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex) {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_be 
		    = ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_type_ex))
		        ? ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
			    ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
			        ? 8U : 4U) : ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					       ? 2U
					       : 1U))
		        : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_type_ex))
			    ? ((IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_misaligned_ex)
			        ? 1U : ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					 ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					     ? 8U : 0xcU)
					 : ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					     ? 6U : 3U)))
			    : ((IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_misaligned_ex)
			        ? ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				    ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				        ? 7U : 3U) : 
				   ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				     ? 1U : 0U)) : 
			       ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				 ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				     ? 8U : 0xcU) : 
				((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				  ? 0xeU : 0xfU)))));
	    }
	} else {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_be 
		    = ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_type_ex))
		        ? ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
			    ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
			        ? 8U : 4U) : ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					       ? 2U
					       : 1U))
		        : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_type_ex))
			    ? ((IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_misaligned_ex)
			        ? 1U : ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					 ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					     ? 8U : 0xcU)
					 : ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					     ? 6U : 3U)))
			    : ((IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_misaligned_ex)
			        ? ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				    ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				        ? 7U : 3U) : 
				   ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				     ? 1U : 0U)) : 
			       ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				 ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				     ? 8U : 0xcU) : 
				((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				  ? 0xeU : 0xfU)))));
	    }
	}
    }
    // ALWAYS at ram.sv:61
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex) {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_wdata;
	    }
	} else {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_wdata;
	    }
	}
    }
}

VL_INLINE_OPT void Vtop_ram::_sequent__TOP__top__ram_i__2(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_ram::_sequent__TOP__top__ram_i__2\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at ram.sv:147
    vlSymsp->TOP__top__ram_i.__PVT__select_rdata_q 
	= ((IData)(vlTOPp->rstn_i) ? (IData)(vlSymsp->TOP__top__ram_i.__PVT__select_rdata_d)
	    : 0U);
}

VL_INLINE_OPT void Vtop_ram::_sequent__TOP__top__ram_i__3(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_ram::_sequent__TOP__top__ram_i__3\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at ram.sv:147
    vlSymsp->TOP__top__ram_i.__PVT__instr_rvalid_o 
	= ((IData)(vlTOPp->rstn_i) & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__instr_req_pmp));
    // ALWAYS at ram.sv:147
    vlSymsp->TOP__top__ram_i.__PVT__data_rvalid_o = 
	((IData)(vlTOPp->rstn_i) & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp));
}

VL_INLINE_OPT void Vtop_ram::_combo__TOP__top__ram_i__4(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_ram::_combo__TOP__top__ram_i__4\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at ram.sv:61
    vlSymsp->TOP__top__ram_i.__PVT__exit_valid_o = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex) {
	    if ((0x400000U <= vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		if ((0x20000004U == vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		    vlSymsp->TOP__top__ram_i.__PVT__exit_valid_o = 1U;
		}
	    }
	}
    }
    // ALWAYS at ram.sv:61
    vlSymsp->TOP__top__ram_i.__PVT__select_rdata_d = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if ((1U & (~ (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex)))) {
	    vlSymsp->TOP__top__ram_i.__PVT__select_rdata_d 
		= ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
		    ? 0U : 2U);
	}
    }
    // ALWAYS at ram.sv:61
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_be = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex) {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_be 
		    = ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_type_ex))
		        ? ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
			    ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
			        ? 8U : 4U) : ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					       ? 2U
					       : 1U))
		        : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_type_ex))
			    ? ((IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_misaligned_ex)
			        ? 1U : ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					 ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					     ? 8U : 0xcU)
					 : ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					     ? 6U : 3U)))
			    : ((IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_misaligned_ex)
			        ? ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				    ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				        ? 7U : 3U) : 
				   ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				     ? 1U : 0U)) : 
			       ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				 ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				     ? 8U : 0xcU) : 
				((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				  ? 0xeU : 0xfU)))));
	    }
	} else {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_be 
		    = ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_type_ex))
		        ? ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
			    ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
			        ? 8U : 4U) : ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					       ? 2U
					       : 1U))
		        : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_type_ex))
			    ? ((IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_misaligned_ex)
			        ? 1U : ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					 ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					     ? 8U : 0xcU)
					 : ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
					     ? 6U : 3U)))
			    : ((IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_misaligned_ex)
			        ? ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				    ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				        ? 7U : 3U) : 
				   ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				     ? 1U : 0U)) : 
			       ((2U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				 ? ((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				     ? 8U : 0xcU) : 
				((1U & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)
				  ? 0xeU : 0xfU)))));
	    }
	}
    }
    // ALWAYS at ram.sv:61
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex) {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_wdata;
	    }
	} else {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_wdata;
	    }
	}
    }
    // ALWAYS at ram.sv:61
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_req = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex) {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_req 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp;
	    }
	} else {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_req 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp;
	    }
	}
    }
    // ALWAYS at ram.sv:61
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_we = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex) {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_we 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex;
	    }
	} else {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_we 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex;
	    }
	}
    }
    // ALWAYS at ram.sv:61
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex) {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr 
		    = (0x3fffffU & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
	    }
	} else {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr 
		    = (0x3fffffU & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
	    }
	}
    }
}

VL_INLINE_OPT void Vtop_ram::_multiclk__TOP__top__ram_i__5(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_ram::_multiclk__TOP__top__ram_i__5\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at ram.sv:107
    vlSymsp->TOP__top__ram_i.__PVT__data_rdata_o = 0U;
    if ((0U == (IData)(vlSymsp->TOP__top__ram_i.__PVT__select_rdata_q))) {
	vlSymsp->TOP__top__ram_i.__PVT__data_rdata_o 
	    = vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_b_o;
    } else {
	if (VL_UNLIKELY((2U == (IData)(vlSymsp->TOP__top__ram_i.__PVT__select_rdata_q)))) {
	    VL_WRITEF("out of bounds read from %08x\n",
		      32,vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
	    VL_FINISH_MT("ram.sv",114,"");
	}
    }
}

void Vtop_ram::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_ram::_ctor_var_reset\n"); );
    // Body
    __PVT__clk = VL_RAND_RESET_I(1);
    __PVT__rst_ni = VL_RAND_RESET_I(1);
    __PVT__instr_req_i = VL_RAND_RESET_I(1);
    __PVT__instr_addr_i = VL_RAND_RESET_I(22);
    VL_RAND_RESET_W(128,__PVT__instr_rdata_o);
    __PVT__instr_rvalid_o = VL_RAND_RESET_I(1);
    __PVT__instr_gnt_o = VL_RAND_RESET_I(1);
    __PVT__data_req_i = VL_RAND_RESET_I(1);
    __PVT__data_addr_i = VL_RAND_RESET_I(32);
    __PVT__data_we_i = VL_RAND_RESET_I(1);
    __PVT__data_be_i = VL_RAND_RESET_I(4);
    __PVT__data_wdata_i = VL_RAND_RESET_I(32);
    __PVT__data_rdata_o = VL_RAND_RESET_I(32);
    __PVT__data_rvalid_o = VL_RAND_RESET_I(1);
    __PVT__data_gnt_o = VL_RAND_RESET_I(1);
    __PVT__exit_valid_o = VL_RAND_RESET_I(1);
    __PVT__exit_value_o = VL_RAND_RESET_I(32);
    __PVT__select_rdata_d = VL_RAND_RESET_I(2);
    __PVT__select_rdata_q = VL_RAND_RESET_I(2);
    __PVT__ram_data_req = VL_RAND_RESET_I(1);
    __PVT__ram_data_addr = VL_RAND_RESET_I(22);
    __PVT__ram_data_wdata = VL_RAND_RESET_I(32);
    __PVT__ram_data_we = VL_RAND_RESET_I(1);
    __PVT__ram_data_be = VL_RAND_RESET_I(4);
}
