#!/bin/bash
echo "Testing all programs in processor model"

./testbench ../tb/core/benchmark/codes/adpcm/adpcm.bin
./testbench ../tb/core/benchmark/codes/aes/aes.bin
./testbench ../tb/core/benchmark/codes/fft/fft.bin
./testbench ../tb/core/benchmark/codes/matrixmultiply/matrixmultiply.bin
./testbench ../tb/core/benchmark/MiBench/office/stringsearch/search_small.bin
#./testbench ../tb/core/benchmark/MiBench/automotive/basicmath/basicmath.bin