# Invasim: A Manycore Simulation Plarform

The following manual shown the different tools that need to be install in order to successfully run Invasim.

## Verilator
Verilator is the fastest free Verilog HDL simulator, and outperforms most commercial simulators. Verilator compiles synthesizable SystemVerilog (generally not test-bench code), plus some SystemVerilog and Synthesis assertions into single- or multithreaded C++ or SystemC code. 
In Invasim, Verilator is used to generate the RISC-V processof model from the System Verilog RTL and then used it as a core in the simulation platform. It allows to execute RISC-V machine code.

### Installation
It is recommended to build it from **Git**:
```bash
sudo apt-get install git make autoconf g++ flex bison   # First time prerequisites 
sudo apt-get install libfl2  # Ubuntu only (ignore if gives error)
sudo apt-get install libfl-dev  # Ubuntu only (ignore if gives error)
git clone http://git.veripool.org/git/verilator   # Only first time
unset VERILATOR_ROOT  # For bash
cd verilator
git pull        # Make sure we're up-to-date
git tag         # See what versions exist
git checkout stable      # Use most recent release
#git checkout v{version}  # Switch to specified release version if stable doesn't work in project
autoconf        # Create ./configure script
./configure
make
sudo make install
# Now see "man verilator"
```

**NOTE:** The project was developed in Verilator 4.016 2019-06-16 rev UNKNOWN_REV

## RISC-V GNU Compiler Toolchain
This is the RISC-V C and C++ cross-compiler. It supports two build modes: a generic ELF/Newlib toolchain and a more sophisticated Linux-ELF/glibc toolchain.

## Installation
In order to install the toolchain correctly, there are some prerequisites that need to be install before On Ubuntu:
```bash
sudo apt-get install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev
```
On Fedora/CentOS/RHEL OS:
```bash
sudo yum install autoconf automake libmpc-devel mpfr-devel gmp-devel gawk  bison flex texinfo patchutils gcc gcc-c++ zlib-devel
```
### Sources
To download all necessary sources run:
```bash
git clone https://github.com/pulp-platform/pulp-riscv-gnu-toolchain
cd pulp-riscv-gnu-toolchain
git submodule update --init --recursive
```
### Pulp
To build the Newlib cross-compiler for all pulp variants, pick an install path. If you choose, say, `/opt/riscv`, then add `/opt/riscv/bin` to your `PATH` now. Then, simply run the following command:
```bash
./configure --prefix=/opt/riscv --with-arch=rv32imc --with-cmodel=medlow --enable-multilib
make
```
This will use the multilib support to build the libraries for the various cores (**riscy**, zeroriscy and so on). The right libraries will be selected depending on which compiler options you use. Invasim uses **riscy**.

## RI5CY: RISC-V Core
RI5CY is a small 4-stage RISC-V core. RI5CY fully implements the RV32IMFC instruction set and many custom instruction set extensions that improve its performance for signal processing applications. The core was developed as part of the [PULP platform](http://pulp.ethz.ch/) for energy-efficient computing and is currently used as the processing core for PULP and PULPino.
### Sources
To download all necessary sources run:
```bash
git clone https://github.com/pulp-platform/riscv.git
```

In Invasim, it is found in folder **RI5CY**, and to generate the model run the following command in **RI5CY/verilator_model**:
```bash
Invasim/RI5CY/verilator_model $: make
```

This will generate the processor model in C++ to be used in Invasim.

### Basic Testbech
**RI5CY** has a set of testbenches, in order to run them RISC-V toolchain path must be exported in RISCV:
```bash
export RISCV=/opt/riscv-pulp
```
To run the basic test called **core**, which is in folder **Invasim/RI5CY/tb/core**, run the next commands:
```bash
cd RI5CY/tb/core
make
```
This will generate the models and compile tests, and then run all tests in the processor.
### Custom programs
In order to run custom programs in the model, the previous test should be run or at least compiled. In the same path, there is a folder called **custom** which contains a simple hello world in C. 
To compile this program, run the following command:
```bash
make custom/hello_world.hex
```
This will generate a hexadecimal file with Verilog' BCD, this should be loaded in memory running the testbench previously compiled:
```bash
./testbench_verilator "+firmware=custom/hello_world.hex"
```
This starts the processor with the custom program. That program can be edited to explore other programs, and to create complex programs the *Makefile* shown how to compile them so they can be loaded in memory.
