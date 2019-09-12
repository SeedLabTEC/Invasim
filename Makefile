CC = g++
V = -std=c++17
SRC = src/
BIN = bin/
TOP = top

CMAIN = main.cpp
CFILES = 	$(SRC)RI5CY.cpp
CFLAGS = -Wall -lpthread 

VDIR = ./RI5CY/processor-model/riscv_core
VOBJS = $(VDIR)/verilated.o       \
        $(VDIR)/verilated_vcd_c.o
VLIB = $(VDIR)/V$(TOP)__ALL.a

CINC = 	-I$(VDIR) -I/usr/local/share/verilator/include/ \
		-I/usr/local/share/verilator/include/vltstd

APP = invasive_simulator

$(APP): programs processor_model Makefile
	$(CC) $(V) -o $(BIN)$(APP) $(CINC) $(CFILES) $(VOBJS) $(VLIB) $(CMAIN) $(CFLAGS)

programs:
	$(MAKE) -C RI5CY/tb/core/benchmark/

processor_model:
	$(MAKE) -C RI5CY/processor-model/

clean:
	rm $(BIN)$(APP)
	$(MAKE) -C RI5CY/processor-model/ clean
