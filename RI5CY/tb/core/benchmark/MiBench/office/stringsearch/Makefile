# RISCV toolchain install path
RISCV                    ?= /opt/riscv32-pulp
RISCV_EXE_PREFIX         = $(RISCV)/bin/riscv32-unknown-elf-

#Source files
SRC = bmhasrch.c  bmhisrch.c  bmhsrch.c  pbmsrch_small.c 

# Create hex file with Verilog bfd
search_small.hex: search_small.elf Makefile
	$(RISCV_EXE_PREFIX)objcopy -O verilog $< $@

search_small.elf: $(SRC)
	$(RISCV_EXE_PREFIX)gcc -march=rv32imafc -o $@ -w -Os -g -nostdlib \
		-T ../../link.ld  \
		-static \
		../../crt0.S \
		$(SRC) ../../syscalls.c ../../vectors.S \
		-I $(RISCV)/riscv32-unknown-elf/include \
		-L $(RISCV)/riscv32-unknown-elf/lib \
		-lm -lc -lgcc

clean:
	rm -rf search_small.elf search_small.hex
