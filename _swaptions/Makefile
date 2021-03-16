#makefile

GCC_TOOLCHAIN_DIR := /root/RISCV/Bin/riscv64/riscv-elf
SYSROOT_DIR := $(GCC_TOOLCHAIN_DIR)/riscv64-unknown-elf

LLVM := /root/RISCV/Bin/llvm
SPIKE := /root/RISCV/Bin/riscv64/riscv-elf/bin/spike
PK := /root/RISCV/Bin/riscv64/riscv-elf/riscv64-unknown-elf/bin/pk


target = bin/rvv-test

start:
	mkdir bin; \
	rm bin/*.*

serial:
	for entry in src/*.cpp ; do \
		${LLVM}/bin/clang++   -Wall --target=riscv64-unknown-elf -march=rv64gcv1p0 -menable-experimental-extensions --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR) -O2 -c -o  $$entry.o  $$entry ; \
	done
	${LLVM}/bin/clang++   -Wall --target=riscv64-unknown-elf  -march=rv64gcv1p0 -menable-experimental-extensions --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR)  -O2  -o $(target)  src/*.cpp.o -lm;	\
	rm src/*.o; \
	${LLVM}/bin/llvm-objdump -D --mattr=+experimental-v ./bin/rvv-test > ./bin/dump_serial

x86:
	for entry in src/*.cpp ; do \
        ${LLVM}/bin/clang++   -Wall -O2 -c -o  $$entry.o  $$entry ; \
    done
	${LLVM}/bin/clang++   -Wall  -O2  -o $(target)  src/*.cpp.o -lm
	$(target) -ns 8 -sm 512 -nt 1

vector:
	${LLVM}/bin/clang++  -Wall --target=riscv64-unknown-elf -DUSE_RISCV_VECTOR -march=rv64gcv1p0 -menable-experimental-extensions --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR)  -O2 -c -o src/CumNormalInv.o src/CumNormalInv.cpp
	${LLVM}/bin/clang++  -Wall --target=riscv64-unknown-elf -DUSE_RISCV_VECTOR -march=rv64gcv1p0 -menable-experimental-extensions --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR)  -O2 -c -o src/MaxFunction.o src/MaxFunction.cpp	
	${LLVM}/bin/clang++  -Wall --target=riscv64-unknown-elf -DUSE_RISCV_VECTOR -march=rv64gcv1p0 -menable-experimental-extensions --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR) -O2 -c -o src/RanUnif.o src/RanUnif.cpp
	${LLVM}/bin/clang++  -Wall --target=riscv64-unknown-elf -DUSE_RISCV_VECTOR -march=rv64gcv1p0 -menable-experimental-extensions --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR)  -O2 -c -o src/nr_routines.o src/nr_routines.cpp
	${LLVM}/bin/clang++  -Wall --target=riscv64-unknown-elf -DUSE_RISCV_VECTOR -march=rv64gcv1p0 -menable-experimental-extensions --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR) -O2 -c -o src/icdf.o src/icdf.cpp
	${LLVM}/bin/clang++  -Wall --target=riscv64-unknown-elf -DUSE_RISCV_VECTOR -march=rv64gcv1p0 -menable-experimental-extensions --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR)  -O2 -c -o src/HJM_SimPath_Forward_Blocking.o src/HJM_SimPath_Forward_Blocking.cpp
	${LLVM}/bin/clang++  -Wall --target=riscv64-unknown-elf -DUSE_RISCV_VECTOR -march=rv64gcv1p0 -menable-experimental-extensions --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR) -O2 -c -o src/HJM.o src/HJM.cpp
	${LLVM}/bin/clang++  -Wall --target=riscv64-unknown-elf -DUSE_RISCV_VECTOR -march=rv64gcv1p0 -menable-experimental-extensions --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR) -O2 -c -o src/HJM_Swaption_Blocking.o src/HJM_Swaption_Blocking.cpp
	${LLVM}/bin/clang++  -Wall --target=riscv64-unknown-elf -DUSE_RISCV_VECTOR -march=rv64gcv1p0 -menable-experimental-extensions --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR) -O2 -c -o src/HJM_Securities.o src/HJM_Securities.cpp
	${LLVM}/bin/clang++  -Wall --target=riscv64-unknown-elf -DUSE_RISCV_VECTOR -march=rv64gcv1p0 -menable-experimental-extensions --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR) -O2   -o $(target)  src/*.o -lm
	rm src/*.o
	${LLVM}/bin/llvm-objdump -D --mattr=+experimental-v ./bin/rvv-test > ./bin/dump_vector

runspike :
	$(SPIKE) --isa=rv64gcv $(PK) $(target) -ns 8 -sm 512 -nt 1

host:
	for entry in src/*.cpp ; do \
		g++ -O2 -g -funroll-loops -fprefetch-loop-arrays -fpermissive -fno-exceptions -static-libgcc -c -o  $$entry.o  $$entry ; \
	done
	g++ -O2 -g -funroll-loops -fprefetch-loop-arrays -fpermissive -fno-exceptions -static-libgcc -o  bin/swaptions_host.exe  src/*.o  -lm;
	rm src/*.o;

copy:
	rm -r ../../Test/_swaptions/bin/*.exe; \
	cp -r bin/*exe ../../Test/_swaptions/bin/;

clean:
	rm bin/*.dump
	rm bin/*.exe
