#makefile

GCC_TOOLCHAIN_DIR := /opt/RISCV/
CLANG_DIR := /git/llvm-project/build/
GEM5_DIR := /git/plct-gem5/
BENCHMARK_DIR := /git/riscv-vectorized-benchmark-suite/

start:
	if [ ! -d bin ]; then \
		mkdir bin; \
	else \
		echo bin dir exist; \
	fi
	if [ ! -d output ]; then \
		mkdir output; \
	else \
		echo output dir exist; \
	fi

serial:
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -g -o bin/pathfinder_serial src/pathfinder.cpp
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/pathfinder_serial > bin/pathfinder_serial.dump

vector:
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -o bin/pathfinder_vector src/pathfinder.cpp
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/pathfinder_vector > bin/pathfinder_vector.dump

serial_O2:
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -O2 -g -o bin/pathfinder_serial_O2 src/pathfinder.cpp
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/pathfinder_serial_O2 > bin/pathfinder_serial_O2.dump

vector_O2:
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -O2 -g -o bin/pathfinder_vector_O2 src/pathfinder.cpp
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/pathfinder_vector_O2 > bin/pathfinder_vector_O2.dump

serial_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -g -o bin/pathfinder_serial src/pathfinder.cpp
	${CLANG_DIR}bin/llvm-objdump -d bin/pathfinder_serial > bin/pathfinder_serial.dump

vector_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -static -g -o bin/pathfinder_vector src/pathfinder.cpp
	${CLANG_DIR}bin/llvm-objdump -d bin/pathfinder_vector > bin/pathfinder_vector.dump

serial_O2_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -O2 -g -o bin/pathfinder_serial_O2 src/pathfinder.cpp
	${CLANG_DIR}bin/llvm-objdump -d bin/pathfinder_serial_O2 > bin/pathfinder_serial_O2.dump

vector_O2_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -static -O2 -g -o bin/pathfinder_vector_O2 src/pathfinder.cpp
	${CLANG_DIR}bin/llvm-objdump -d bin/pathfinder_vector_O2 > bin/pathfinder_vector_O2.dump

clean:
	rm -rf bin/
	rm -rf output/

runqemu :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/pathfinder_vector 32 32 ./output/output_vector.txt

runqemu_O2 :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/pathfinder_vector_O2 32 32 ./output/output_vector.txt

rungem5 :
	${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="${BENCHMARK_DIR}_pathfinder/bin/pathfinder_vector 1 100 300 input/100.nets 8"

rungem5_O2 :
	${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="${BENCHMARK_DIR}_pathfinder/bin/pathfinder_vector_O2 1 100 300 input/100.nets 8"