# RISCV toolchain install path
RISCV                    ?= /opt/riscv32-pulp
RISCV_EXE_PREFIX         = $(RISCV)/bin/riscv32-unknown-elf-

# Create bin file
fft.bin: fft.hex Makefile
	$(RISCV_EXE_PREFIX)objcopy -O binary fft.elf $@

# Create hex file with Verilog bfd
fft.hex: fft.elf Makefile
	$(RISCV_EXE_PREFIX)objcopy -O verilog $< $@

# Build the program with RISCV toolchain
fft.elf: fft.c
	$(RISCV_EXE_PREFIX)gcc -march=rv32imafc -o $@ -w -Os -g -nostdlib \
		-T ../link.ld  \
		-static \
		../crt0.S \
		$^ ../syscalls.c ../vectors.S \
		-I $(RISCV)/riscv32-unknown-elf/include \
		-L $(RISCV)/riscv32-unknown-elf/lib \
		-lc -lm -lgcc

# Clean binaries
clean:
	rm -f fft.elf fft.hex fft.bin