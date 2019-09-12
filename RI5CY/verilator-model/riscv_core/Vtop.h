// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _Vtop_H_
#define _Vtop_H_

#include "verilated_heavy.h"
#include "Vtop__Dpi.h"

class Vtop__Syms;
class Vtop_top;

//----------

VL_MODULE(Vtop) {
  public:
    // CELLS
    // Public to allow access to /*verilator_public*/ items;
    // otherwise the application code can consider these internals.
    Vtop_top*          	top;
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    // Begin mtask footprint  all: 
    VL_IN8(clk_i,0,0);
    VL_IN8(rstn_i,0,0);
    VL_IN8(irq_i,0,0);
    VL_IN8(irq_id_i,4,0);
    VL_OUT8(irq_ack_o,0,0);
    VL_OUT8(irq_id_o,4,0);
    VL_IN8(irq_sec_i,0,0);
    VL_OUT8(sec_lvl_o,0,0);
    VL_IN8(debug_req_i,0,0);
    VL_IN8(fetch_enable_i,0,0);
    VL_OUT8(core_busy_o,0,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    // Begin mtask footprint  all: 
    VL_SIG8(__Vclklast__TOP__clk_i,0,0);
    VL_SIG8(__Vclklast__TOP__rstn_i,0,0);
    VL_SIG8(__Vclklast__TOP__top____PVT__riscv_core_i__DOT__clk,0,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__ex_ready,0,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__lsu_ready_ex,0,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__lsu_ready_wb,0,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__data_req_pmp,0,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__instr_req_pmp,0,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__if_stage_i__DOT__valid,0,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__if_stage_i__DOT__fetch_valid,0,0);
    VL_SIGW(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__alu_i__DOT__alu_ff_i__DOT__index_nodes,159,0,5);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__i_arbiter__DOT__genblk2__DOT__gnt_nodes,2,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__i_arbiter__DOT__genblk2__DOT__req_nodes,2,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__0__KET____DOT__i_opgroup_block__DOT__i_arbiter__DOT__genblk2__DOT__gnt_nodes,6,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__0__KET____DOT__i_opgroup_block__DOT__i_arbiter__DOT__genblk2__DOT__req_nodes,6,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__0__KET____DOT__i_opgroup_block__DOT__gen_merged_slice__DOT__i_multifmt_slice__DOT__gen_num_lanes__BRA__0__KET____DOT__active_lane__DOT__lane_instance__DOT__i_fpnew_fma_multi__DOT__regular_status,4,0);
    VL_SIGW(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__0__KET____DOT__i_opgroup_block__DOT__gen_merged_slice__DOT__i_multifmt_slice__DOT__gen_num_lanes__BRA__0__KET____DOT__active_lane__DOT__lane_instance__DOT__i_fpnew_fma_multi__DOT__i_lzc__DOT__index_nodes,383,0,12);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__1__KET____DOT__i_opgroup_block__DOT__i_arbiter__DOT__genblk2__DOT__req_nodes,6,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__2__KET____DOT__i_opgroup_block__DOT__i_arbiter__DOT__genblk2__DOT__gnt_nodes,6,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__2__KET____DOT__i_opgroup_block__DOT__i_arbiter__DOT__genblk2__DOT__req_nodes,6,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__3__KET____DOT__i_opgroup_block__DOT__i_arbiter__DOT__genblk2__DOT__gnt_nodes,6,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__3__KET____DOT__i_opgroup_block__DOT__i_arbiter__DOT__genblk2__DOT__req_nodes,6,0);
    VL_SIG8(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__3__KET____DOT__i_opgroup_block__DOT__gen_merged_slice__DOT__i_multifmt_slice__DOT__gen_num_lanes__BRA__0__KET____DOT__active_lane__DOT__genblk1__DOT__genblk1__DOT__genblk1__DOT__lane_instance__DOT__i_fpnew_cast_multi__DOT__fp_regular_status,4,0);
    VL_SIGW(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__3__KET____DOT__i_opgroup_block__DOT__gen_merged_slice__DOT__i_multifmt_slice__DOT__gen_num_lanes__BRA__0__KET____DOT__active_lane__DOT__genblk1__DOT__genblk1__DOT__genblk1__DOT__lane_instance__DOT__i_fpnew_cast_multi__DOT__i_lzc__DOT__index_nodes,159,0,5);
    VL_SIG(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__alu_i__DOT__alu_ff_i__DOT__sel_nodes,31,0);
    VL_SIG(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__mult_i__DOT__short_op_a,16,0);
    VL_SIG(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__mult_i__DOT__short_op_b,16,0);
    VL_SIG(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__3__KET____DOT__i_opgroup_block__DOT__gen_merged_slice__DOT__i_multifmt_slice__DOT__gen_num_lanes__BRA__0__KET____DOT__active_lane__DOT__genblk1__DOT__genblk1__DOT__genblk1__DOT__lane_instance__DOT__i_fpnew_cast_multi__DOT__i_lzc__DOT__sel_nodes,31,0);
    VL_SIGW(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__i_arbiter__DOT__genblk2__DOT__data_nodes,113,0,4);
    VL_SIGW(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__0__KET____DOT__i_opgroup_block__DOT__i_arbiter__DOT__genblk2__DOT__data_nodes,272,0,9);
    VL_SIG64(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__0__KET____DOT__i_opgroup_block__DOT__gen_merged_slice__DOT__i_multifmt_slice__DOT__gen_num_lanes__BRA__0__KET____DOT__active_lane__DOT__lane_instance__DOT__i_fpnew_fma_multi__DOT__i_lzc__DOT__sel_nodes,63,0);
    VL_SIGW(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__1__KET____DOT__i_opgroup_block__DOT__i_arbiter__DOT__genblk2__DOT__data_nodes,272,0,9);
    VL_SIGW(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__2__KET____DOT__i_opgroup_block__DOT__i_arbiter__DOT__genblk2__DOT__data_nodes,272,0,9);
    VL_SIGW(__Vchglast__TOP__top__riscv_core_i__DOT__ex_stage_i__DOT__genblk1__DOT__genblk2__DOT__i_fpnew_bulk__DOT__gen_operation_groups__BRA__3__KET____DOT__i_opgroup_block__DOT__i_arbiter__DOT__genblk2__DOT__data_nodes,272,0,9);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vtop__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vtop(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vtop();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vtop__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vtop__Syms* symsp, bool first);
  private:
    static QData _change_request(Vtop__Syms* __restrict vlSymsp);
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vtop__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _multiclk__TOP__4(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__3(Vtop__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(128);

#endif // guard
