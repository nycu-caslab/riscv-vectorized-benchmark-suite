export GCC_TOOLCHAIN_DIR= /opt/riscv-gnu-toolchain/
export CLANG_DIR= /opt/llvm/
export GEM5_DIR= /opt/gem5/
export QEMU_DIR= /opt/qemu

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
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -g -o bin/jacobi-2d_serial src/jacobi-2d.cpp
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/jacobi-2d_serial > bin/jacobi-2d_serial.dump

vector:
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -o bin/jacobi-2d_vector src/jacobi-2d.cpp
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/jacobi-2d_vector > bin/jacobi-2d_vector.dump

serial_O2:
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -O2 -g -o bin/jacobi-2d_serial_O2 src/jacobi-2d.cpp
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/jacobi-2d_serial_O2 > bin/jacobi-2d_serial_O2.dump

vector_O2:
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -O2 -g -o bin/jacobi-2d_vector_O2 src/jacobi-2d.cpp
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/jacobi-2d_vector_O2 > bin/jacobi-2d_vector_O2.dump

serial_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -g -w -o bin/jacobi-2d_serial src/jacobi-2d.cpp
	${CLANG_DIR}bin/llvm-objdump -d bin/jacobi-2d_serial > bin/jacobi-2d_serial.dump

vector_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -static -g -w -o bin/jacobi-2d_vector src/jacobi-2d.cpp
	${CLANG_DIR}bin/llvm-objdump -d bin/jacobi-2d_vector > bin/jacobi-2d_vector.dump

serial_O2_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -O2 -g -w -o bin/jacobi-2d_serial_O2 src/jacobi-2d.cpp
	${CLANG_DIR}bin/llvm-objdump -d bin/jacobi-2d_serial_O2 > bin/jacobi-2d_serial_O2.dump

vector_O2_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -static -O2 -g -w -o bin/jacobi-2d_vector_O2 src/jacobi-2d.cpp
	${CLANG_DIR}bin/llvm-objdump -d bin/jacobi-2d_vector_O2 > bin/jacobi-2d_vector_O2.dump

clean:
	rm -rf bin/
	rm -rf output/

runqemu :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/jacobi-2d_vector 200 1 ./output/output_vector.txt

runqemu_O2 :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/jacobi-2d_vector_O2 200 1 ./output/output_vector.txt

rungem5 :
	${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="./_jacobi-2d/bin/jacobi-2d_vector 200 1 ./output/output_vector.txt"

rungem5_O2 :
	${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="./_jacobi-2d/bin/jacobi-2d_vector_O2 200 1 ./output/output_vector.txt"