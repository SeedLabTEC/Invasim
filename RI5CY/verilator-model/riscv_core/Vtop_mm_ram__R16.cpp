// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop_mm_ram__R16.h"
#include "Vtop__Syms.h"

#include "verilated_dpi.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(Vtop_mm_ram__R16) {
    VL_CELL(dp_ram_i, Vtop_dp_ram__A16);
    // Reset internal values
    // Reset structure values
    _ctor_var_reset();
}

void Vtop_mm_ram__R16::__Vconfigure(Vtop__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vtop_mm_ram__R16::~Vtop_mm_ram__R16() {
}

//--------------------
// Internal Methods

void Vtop_mm_ram__R16::_settle__TOP__top__ram_i__1(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_mm_ram__R16::_settle__TOP__top__ram_i__1\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at mm_ram.sv:168
    vlSymsp->TOP__top__ram_i.__PVT__data_rdata_o = 0U;
    if ((0U == (IData)(vlSymsp->TOP__top__ram_i.__PVT__select_rdata_q))) {
	vlSymsp->TOP__top__ram_i.__PVT__data_rdata_o 
	    = vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_b_o;
    } else {
	if (VL_UNLIKELY((2U == (IData)(vlSymsp->TOP__top__ram_i.__PVT__select_rdata_q)))) {
	    VL_WRITEF("out of bounds read from %08x\n",
		      32,vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
	    VL_FINISH_MT("mm_ram.sv",175,"");
	}
    }
    // ALWAYS at mm_ram.sv:81
    vlSymsp->TOP__top__ram_i.__PVT__tests_passed_o = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__tests_failed_o = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__exit_value_o = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__exit_valid_o = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_req = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_we = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_be = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__print_wdata = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__print_valid = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__select_rdata_d = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex) {
	    if (VL_UNLIKELY((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int))) {
		VL_WRITEF("Writing: %x\n",32,vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_req 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp;
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr 
		    = (0x3fffffU & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata 
		    = ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
		        ? ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			    ? ((0xff000000U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 0x18U)) 
			       | (0xffffffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       >> 8U)))
			    : ((0xffff0000U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 0x10U)) 
			       | (0xffffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					     >> 0x10U))))
		        : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			    ? ((0xffffff00U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 8U)) 
			       | (0xffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					   >> 0x18U)))
			    : vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex));
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_we 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex;
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
	    } else {
		if ((0x10000000U == vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		    vlSymsp->TOP__top__ram_i.__PVT__print_wdata 
			= ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			    ? ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			        ? ((0xff000000U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						   << 0x18U)) 
				   | (0xffffffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						   >> 8U)))
			        : ((0xffff0000U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						   << 0x10U)) 
				   | (0xffffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						 >> 0x10U))))
			    : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			        ? ((0xffffff00U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						   << 8U)) 
				   | (0xffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       >> 0x18U)))
			        : vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex));
		    vlSymsp->TOP__top__ram_i.__PVT__print_valid = 1U;
		} else {
		    if ((0x20000000U == vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
			if ((0x75bcd15U == ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
					     ? ((1U 
						 & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
						 ? 
						((0xff000000U 
						  & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						     << 0x18U)) 
						 | (0xffffffU 
						    & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						       >> 8U)))
						 : 
						((0xffff0000U 
						  & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						     << 0x10U)) 
						 | (0xffffU 
						    & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						       >> 0x10U))))
					     : ((1U 
						 & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
						 ? 
						((0xffffff00U 
						  & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						     << 8U)) 
						 | (0xffU 
						    & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						       >> 0x18U)))
						 : vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex)))) {
			    vlSymsp->TOP__top__ram_i.__PVT__tests_passed_o = 1U;
			} else {
			    if ((1U == ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
					 ? ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
					     ? ((0xff000000U 
						 & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						    << 0x18U)) 
						| (0xffffffU 
						   & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						      >> 8U)))
					     : ((0xffff0000U 
						 & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						    << 0x10U)) 
						| (0xffffU 
						   & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						      >> 0x10U))))
					 : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
					     ? ((0xffffff00U 
						 & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						    << 8U)) 
						| (0xffU 
						   & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						      >> 0x18U)))
					     : vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex)))) {
				vlSymsp->TOP__top__ram_i.__PVT__tests_failed_o = 1U;
			    }
			}
		    } else {
			if (VL_UNLIKELY((0x20000004U 
					 == vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int))) {
			    VL_WRITEF("Writing F: %x\n",
				      32,vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
			    vlSymsp->TOP__top__ram_i.__PVT__exit_valid_o = 1U;
			    vlSymsp->TOP__top__ram_i.__PVT__exit_value_o 
				= ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
				    ? ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
				        ? ((0xff000000U 
					    & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 0x18U)) 
					   | (0xffffffU 
					      & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						 >> 8U)))
				        : ((0xffff0000U 
					    & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 0x10U)) 
					   | (0xffffU 
					      & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						 >> 0x10U))))
				    : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
				        ? ((0xffffff00U 
					    & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 8U)) 
					   | (0xffU 
					      & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						 >> 0x18U)))
				        : vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex));
			}
		    }
		}
	    }
	} else {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__select_rdata_d = 0U;
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_req 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp;
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr 
		    = (0x3fffffU & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata 
		    = ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
		        ? ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			    ? ((0xff000000U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 0x18U)) 
			       | (0xffffffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       >> 8U)))
			    : ((0xffff0000U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 0x10U)) 
			       | (0xffffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					     >> 0x10U))))
		        : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			    ? ((0xffffff00U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 8U)) 
			       | (0xffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					   >> 0x18U)))
			    : vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex));
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_we 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex;
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
	    } else {
		vlSymsp->TOP__top__ram_i.__PVT__select_rdata_d = 2U;
	    }
	}
    }
}

VL_INLINE_OPT void Vtop_mm_ram__R16::_sequent__TOP__top__ram_i__2(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_mm_ram__R16::_sequent__TOP__top__ram_i__2\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at mm_ram.sv:180
    if (vlSymsp->TOP__top__ram_i.__PVT__print_valid) {
	if (VL_LIKELY((0U != VL_TESTPLUSARGS_I("verbose")))) {
	    if (((0x20U <= vlSymsp->TOP__top__ram_i.__PVT__print_wdata) 
		 & (0x80U > vlSymsp->TOP__top__ram_i.__PVT__print_wdata))) {
		VL_WRITEF("OUT: '%c'\n",8,(0xffU & vlSymsp->TOP__top__ram_i.__PVT__print_wdata));
	    } else {
		VL_WRITEF("OUT: %3#\n",32,vlSymsp->TOP__top__ram_i.__PVT__print_wdata);
	    }
	} else {
	    VL_WRITEF("%c",8,(0xffU & vlSymsp->TOP__top__ram_i.__PVT__print_wdata));
	}
    }
    // ALWAYS at mm_ram.sv:235
    if (VL_UNLIKELY((((0U != VL_TESTPLUSARGS_I("verbose")) 
		      & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp)) 
		     & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex)))) {
	VL_WRITEF("write addr=0x%08x: data=0x%08x\n",
		  32,vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int,
		  32,((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
		       ? ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			   ? ((0xff000000U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					      << 0x18U)) 
			      | (0xffffffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					      >> 8U)))
			   : ((0xffff0000U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					      << 0x10U)) 
			      | (0xffffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					    >> 0x10U))))
		       : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			   ? ((0xffffff00U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					      << 8U)) 
			      | (0xffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					  >> 0x18U)))
			   : vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex)));
    }
    // ALWAYS at mm_ram.sv:269
    vlSymsp->TOP__top__ram_i.__PVT__select_rdata_q 
	= ((IData)(vlTOPp->rstn_i) ? (IData)(vlSymsp->TOP__top__ram_i.__PVT__select_rdata_d)
	    : 0U);
}

VL_INLINE_OPT void Vtop_mm_ram__R16::_sequent__TOP__top__ram_i__3(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_mm_ram__R16::_sequent__TOP__top__ram_i__3\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at mm_ram.sv:269
    vlSymsp->TOP__top__ram_i.__PVT__instr_rvalid_o 
	= ((IData)(vlTOPp->rstn_i) & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__instr_req_pmp));
    // ALWAYS at mm_ram.sv:269
    vlSymsp->TOP__top__ram_i.__PVT__data_rvalid_o = 
	((IData)(vlTOPp->rstn_i) & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp));
}

VL_INLINE_OPT void Vtop_mm_ram__R16::_combo__TOP__top__ram_i__4(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_mm_ram__R16::_combo__TOP__top__ram_i__4\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at mm_ram.sv:81
    vlSymsp->TOP__top__ram_i.__PVT__tests_passed_o = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__tests_failed_o = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__exit_value_o = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__exit_valid_o = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_req = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_we = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__ram_data_be = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__print_wdata = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__print_valid = 0U;
    vlSymsp->TOP__top__ram_i.__PVT__select_rdata_d = 0U;
    if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp) {
	if (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex) {
	    if (VL_UNLIKELY((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int))) {
		VL_WRITEF("Writing: %x\n",32,vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_req 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp;
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr 
		    = (0x3fffffU & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata 
		    = ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
		        ? ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			    ? ((0xff000000U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 0x18U)) 
			       | (0xffffffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       >> 8U)))
			    : ((0xffff0000U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 0x10U)) 
			       | (0xffffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					     >> 0x10U))))
		        : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			    ? ((0xffffff00U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 8U)) 
			       | (0xffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					   >> 0x18U)))
			    : vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex));
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_we 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex;
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
	    } else {
		if ((0x10000000U == vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		    vlSymsp->TOP__top__ram_i.__PVT__print_wdata 
			= ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			    ? ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			        ? ((0xff000000U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						   << 0x18U)) 
				   | (0xffffffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						   >> 8U)))
			        : ((0xffff0000U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						   << 0x10U)) 
				   | (0xffffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						 >> 0x10U))))
			    : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			        ? ((0xffffff00U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						   << 8U)) 
				   | (0xffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       >> 0x18U)))
			        : vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex));
		    vlSymsp->TOP__top__ram_i.__PVT__print_valid = 1U;
		} else {
		    if ((0x20000000U == vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
			if ((0x75bcd15U == ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
					     ? ((1U 
						 & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
						 ? 
						((0xff000000U 
						  & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						     << 0x18U)) 
						 | (0xffffffU 
						    & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						       >> 8U)))
						 : 
						((0xffff0000U 
						  & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						     << 0x10U)) 
						 | (0xffffU 
						    & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						       >> 0x10U))))
					     : ((1U 
						 & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
						 ? 
						((0xffffff00U 
						  & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						     << 8U)) 
						 | (0xffU 
						    & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						       >> 0x18U)))
						 : vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex)))) {
			    vlSymsp->TOP__top__ram_i.__PVT__tests_passed_o = 1U;
			} else {
			    if ((1U == ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
					 ? ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
					     ? ((0xff000000U 
						 & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						    << 0x18U)) 
						| (0xffffffU 
						   & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						      >> 8U)))
					     : ((0xffff0000U 
						 & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						    << 0x10U)) 
						| (0xffffU 
						   & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						      >> 0x10U))))
					 : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
					     ? ((0xffffff00U 
						 & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						    << 8U)) 
						| (0xffU 
						   & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						      >> 0x18U)))
					     : vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex)))) {
				vlSymsp->TOP__top__ram_i.__PVT__tests_failed_o = 1U;
			    }
			}
		    } else {
			if (VL_UNLIKELY((0x20000004U 
					 == vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int))) {
			    VL_WRITEF("Writing F: %x\n",
				      32,vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
			    vlSymsp->TOP__top__ram_i.__PVT__exit_valid_o = 1U;
			    vlSymsp->TOP__top__ram_i.__PVT__exit_value_o 
				= ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
				    ? ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
				        ? ((0xff000000U 
					    & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 0x18U)) 
					   | (0xffffffU 
					      & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						 >> 8U)))
				        : ((0xffff0000U 
					    & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 0x10U)) 
					   | (0xffffU 
					      & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						 >> 0x10U))))
				    : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
				        ? ((0xffffff00U 
					    & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 8U)) 
					   | (0xffU 
					      & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
						 >> 0x18U)))
				        : vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex));
			}
		    }
		}
	    }
	} else {
	    if ((0x400000U > vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int)) {
		vlSymsp->TOP__top__ram_i.__PVT__select_rdata_d = 0U;
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_req 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_req_pmp;
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_addr 
		    = (0x3fffffU & vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_wdata 
		    = ((2U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
		        ? ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			    ? ((0xff000000U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 0x18U)) 
			       | (0xffffffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       >> 8U)))
			    : ((0xffff0000U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 0x10U)) 
			       | (0xffffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					     >> 0x10U))))
		        : ((1U & (IData)(vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__wdata_offset))
			    ? ((0xffffff00U & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					       << 8U)) 
			       | (0xffU & (vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex 
					   >> 0x18U)))
			    : vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__alu_operand_c_ex));
		vlSymsp->TOP__top__ram_i.__PVT__ram_data_we 
		    = vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__data_we_ex;
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
	    } else {
		vlSymsp->TOP__top__ram_i.__PVT__select_rdata_d = 2U;
	    }
	}
    }
}

VL_INLINE_OPT void Vtop_mm_ram__R16::_multiclk__TOP__top__ram_i__5(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_mm_ram__R16::_multiclk__TOP__top__ram_i__5\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // ALWAYS at mm_ram.sv:168
    vlSymsp->TOP__top__ram_i.__PVT__data_rdata_o = 0U;
    if ((0U == (IData)(vlSymsp->TOP__top__ram_i.__PVT__select_rdata_q))) {
	vlSymsp->TOP__top__ram_i.__PVT__data_rdata_o 
	    = vlSymsp->TOP__top__ram_i__dp_ram_i.__PVT__rdata_b_o;
    } else {
	if (VL_UNLIKELY((2U == (IData)(vlSymsp->TOP__top__ram_i.__PVT__select_rdata_q)))) {
	    VL_WRITEF("out of bounds read from %08x\n",
		      32,vlSymsp->TOP__top.__PVT__riscv_core_i__DOT__load_store_unit_i__DOT__data_addr_int);
	    VL_FINISH_MT("mm_ram.sv",175,"");
	}
    }
}

void Vtop_mm_ram__R16::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop_mm_ram__R16::_ctor_var_reset\n"); );
    // Body
    __PVT__clk_i = VL_RAND_RESET_I(1);
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
    __PVT__irq_id_i = VL_RAND_RESET_I(5);
    __PVT__irq_ack_i = VL_RAND_RESET_I(1);
    __PVT__irq_id_o = VL_RAND_RESET_I(5);
    __PVT__irq_o = VL_RAND_RESET_I(1);
    __PVT__tests_passed_o = VL_RAND_RESET_I(1);
    __PVT__tests_failed_o = VL_RAND_RESET_I(1);
    __PVT__exit_valid_o = VL_RAND_RESET_I(1);
    __PVT__exit_value_o = VL_RAND_RESET_I(32);
    __PVT__select_rdata_d = VL_RAND_RESET_I(2);
    __PVT__select_rdata_q = VL_RAND_RESET_I(2);
    __PVT__ram_data_req = VL_RAND_RESET_I(1);
    __PVT__ram_data_addr = VL_RAND_RESET_I(22);
    __PVT__ram_data_wdata = VL_RAND_RESET_I(32);
    __PVT__ram_data_we = VL_RAND_RESET_I(1);
    __PVT__ram_data_be = VL_RAND_RESET_I(4);
    __PVT__print_wdata = VL_RAND_RESET_I(32);
    __PVT__print_valid = VL_RAND_RESET_I(1);
}
