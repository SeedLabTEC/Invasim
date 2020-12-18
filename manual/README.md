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

### Installation
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

In Invasim, it is found in folder **RI5CY**, and to generate the model run the following command in **verilator_model**:
```bash
Invasim/verilator_model $: make
```
## OR-Tools
In order to use the multiobjective obtimization method for resource allocation, you must install OR-Tools library on your system. To do that you can follow the instructions in the [google developers documentation page](https://developers.google.com/optimization/install/cpp/source_linux). Once you finish the **prerequisites**, **Download the source code**, **Build third parties** and **Build the source code** sections, you can go directly to the [Installing OR-Tools on your operating system](https://developers.google.com/optimization/install/cpp/source_linux#installing-or-tools-on-your-operating-system) section