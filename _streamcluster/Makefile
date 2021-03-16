#makefile
GCC_TOOLCHAIN_DIR := /root/RISCV/Bin/riscv64/riscv-elf
SYSROOT_DIR := $(GCC_TOOLCHAIN_DIR)/riscv64-unknown-elf

LLVM := /root/RISCV/Bin/llvm
SPIKE := /root/RISCV/Bin/riscv64/riscv-elf/bin/spike
PK := /root/RISCV/Bin/riscv64/riscv-elf/riscv64-unknown-elf/bin/pk


target = bin/rvv-test

serial:
	${LLVM}/bin/clang++ --target=riscv64-unknown-elf -march=rv64gcv1p0 -menable-experimental-extensions --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR) -O2 -o $(target) src/streamcluster.cpp -lm
	${LLVM}/bin/llvm-objdump -D --mattr=+experimental-v ./bin/rvv-test > ./bin/dump_serial

vector:
	${LLVM}/bin/clang++ --target=riscv64-unknown-elf -DUSE_RISCV_VECTOR   -march=rv64gcv1p0 -menable-experimental-extensions --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR)  -O2 -o $(target)  src/streamcluster.cpp -lm
	${LLVM}/bin/llvm-objdump -D --mattr=+experimental-v ./bin/rvv-test > ./bin/dump_vector

runspike :
	echo >output.txt; \
	$(SPIKE) --isa=rv64gcv $(PK) $(target) 3 10 128 128 128 10 none output.txt 1
