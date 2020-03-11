CC = g++
V = -std=c++17
SRC = ../../src/
BIN = ./
TOP = top

CMAIN = test_processor_interface.cpp
CFILES = $(SRC)RI5CY.cpp
CFLAGS = -Wall

VDIR = ../../RI5CY/processor-model/riscv_core
VOBJS = $(VDIR)/verilated.o 
VLIB = $(VDIR)/V$(TOP)__ALL.a

CINC = 	-I$(VDIR) -I/usr/local/share/verilator/include/ \
		-I/usr/local/share/verilator/include/vltstd

APP = processor_test

$(APP): programs processor_model Makefile
	$(CC) $(V) -o $(BIN)$(APP) $(CINC) $(CFILES) $(VOBJS) $(VLIB) $(CMAIN) $(CFLAGS)

programs:
	$(MAKE) -C ../../RI5CY/tb/core/benchmark/

processor_model:
	$(MAKE) -C ../../RI5CY/processor-model/

clean:
	rm $(BIN)$(APP)
	$(MAKE) -C RI5CY/processor-model/ clean
