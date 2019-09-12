# RISCV toolchain install path
RISCV                    ?= /opt/riscv32-pulp
RISCV_EXE_PREFIX         = $(RISCV)/bin/riscv32-unknown-elf-

# Source files
SRC = rad2deg.c cubic.c isqrt.c basicmath_small.c

# Create bin file
basicmath.bin: basicmath.hex Makefile
	$(RISCV_EXE_PREFIX)objcopy -O binary basicmath.elf $@

# Create hex file with Verilog bfd
basicmath.hex: basicmath.elf Makefile
	$(RISCV_EXE_PREFIX)objcopy -O verilog $< $@

basicmath.elf: $(SRC)
	$(RISCV_EXE_PREFIX)gcc -march=rv32imafc -o $@ -w -Os -g -nostdlib \
		-T ../../link.ld  \
		-static \
		../../crt0.S \
		$(SRC) ../../syscalls.c ../../vectors.S \
		-I $(RISCV)/riscv32-unknown-elf/include \
		-L $(RISCV)/riscv32-unknown-elf/lib \
		-lm -lc -lgcc

clean:
	rm -rf basicmath.elf basicmath.hex basicmath.bin
