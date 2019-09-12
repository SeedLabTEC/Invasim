# Copyright 2017 Embecosm Limited <www.embecosm.com>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Makefile for Verilator model of RI5CY
# Contributor: Jeremy Bennett <jeremy.bennett@embecosm.com>

# Testbench

TESTBENCH = testbench

CC = g++

CCINC = -I./riscv_core -I/usr/local/share/verilator/include/ -I/usr/local/share/verilator/include/vltstd

SOURCE = testbench.cpp 
# Tools

VERILATOR = verilator

# Model

VDIR = riscv_core

# top module name

TOP = top

# Verilator elements

VSRC =  cluster_clock_gating.sv            \
        dp_ram.sv                          \
        mm_ram.sv                             \
        top.sv                             \
        fpnew/src/fpnew_pkg.sv                 \
        ../rtl/include/apu_core_package.sv     \
        ../rtl/include/riscv_defines.sv        \
        ../rtl/include/riscv_tracer_defines.sv \
        ../rtl/register_file_test_wrap.sv      \
        ../rtl/riscv_alu.sv                    \
        ../rtl/riscv_alu_basic.sv              \
        ../rtl/riscv_alu_div.sv                \
        ../rtl/riscv_compressed_decoder.sv     \
        ../rtl/riscv_controller.sv             \
        ../rtl/riscv_cs_registers.sv           \
        ../rtl/riscv_decoder.sv                \
        ../rtl/riscv_int_controller.sv         \
        ../rtl/riscv_ex_stage.sv               \
        ../rtl/riscv_hwloop_controller.sv      \
        ../rtl/riscv_hwloop_regs.sv            \
        ../rtl/riscv_id_stage.sv               \
        ../rtl/riscv_if_stage.sv               \
        ../rtl/riscv_load_store_unit.sv        \
        ../rtl/riscv_mult.sv                   \
        ../rtl/riscv_prefetch_buffer.sv        \
        ../rtl/riscv_prefetch_L0_buffer.sv     \
        ../rtl/riscv_register_file.sv          \
        ../rtl/riscv_core.sv                   \
        ../rtl/riscv_apu_disp.sv               \
        ../rtl/riscv_L0_buffer.sv              \
        ../rtl/riscv_pmp.sv

VINC =  +incdir+../rtl/include +incdir+fpnew/src +incdir+fpnew/src/common_cells/include \
        +incdir+fpnew/src/common_cells/src

VOBJS = $(VDIR)/verilated.o       \
        $(VDIR)/verilated_vcd_c.o

VLIB = $(VDIR)/V$(TOP)__ALL.a

VSMK = V$(TOP).mk
VMK  = $(VDIR)/$(VSMK)

$(TESTBENCH): $(VOBJS)
	$(CC) $(CCINC) $(SOURCE) $(VOBJS) $(VLIB)

$(VOBJS): $(VMK) $(VLIB) Makefile
	for f in $@; \
	do \
		sf=$$(basename $$f); \
		$(MAKE) -C $(VDIR) -f $(VSMK) $$sf; \
	done

$(VLIB): $(VMK) $(VDIR)/$(TOP)
	make -C $(VDIR) -f V$(TOP).mk

$(VDIR)/$(TOP): $(VDIR) $(VMK)
	$(MAKE) -C $(VDIR) -f $(VSMK)

$(VDIR):
	mkdir -p $@

$(VMK): fpnew
	verilator -O3 -Wno-CASEINCOMPLETE -Wno-LITENDIAN -Wno-UNOPT \
	          -Wno-UNOPTFLAT -Wno-WIDTH -Wno-fatal --top-module top \
	          --Mdir $(VDIR) -cc \
	          $(VINC) $(VSRC) +define+SYNTHESIS

# fpnew dependencies
fpnew:
	git clone https://github.com/pulp-platform/fpnew --recurse

.PHONY: clean
clean:
	$(RM) -r $(VDIR)
