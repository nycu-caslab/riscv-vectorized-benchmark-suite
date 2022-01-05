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
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -g -o bin/blackscholes_serial src/blackscholes.cpp
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/blackscholes_serial > bin/blackscholes_serial.dump


vector:
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -o bin/blackscholes_vector src/blackscholes.cpp
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/blackscholes_vector > bin/blackscholes_vector.dump

serial_O2:
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -O2 -g -o bin/blackscholes_serial_O2 src/blackscholes.cpp
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/blackscholes_serial_O2 > bin/blackscholes_serial_O2.dump


vector_O2:
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -O2 -g -o bin/blackscholes_vector_O2 src/blackscholes.cpp
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/blackscholes_vector_O2 > bin/blackscholes_vector_O2.dump

serial_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -g -w -o bin/blackscholes_serial src/blackscholes.cpp
	${CLANG_DIR}bin/llvm-objdump -d bin/blackscholes_serial > bin/blackscholes_serial.dump


vector_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -static -g -w -o bin/blackscholes_vector src/blackscholes.cpp
	${CLANG_DIR}bin/llvm-objdump -d bin/blackscholes_vector > bin/blackscholes_vector.dump

serial_O2_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -O2 -g -w -o bin/blackscholes_serial_O2 src/blackscholes.cpp
	${CLANG_DIR}bin/llvm-objdump -d bin/blackscholes_serial_O2 > bin/blackscholes_serial_O2.dump


vector_O2_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -static -O2 -g -w -o bin/blackscholes_vector_O2 src/blackscholes.cpp
	${CLANG_DIR}bin/llvm-objdump -d bin/blackscholes_vector_O2 > bin/blackscholes_vector_O2.dump

clean:
	rm -rf bin/
	rm -rf output/

runqemu :
	${QEMU_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/blackscholes_vector 1 input/in_512.input output_prices.txt

runqemu_O2 :
	${QEMU_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/blackscholes_vector_O2 1 input/in_512.input output_prices.txt

rungem5 :
	${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="./_blackscholes/bin/blackscholes_vector 1 input/in_512.input output_prices.txt"

rungem5_O2 :
	${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="./_blackscholes/bin/blackscholes_vector_O2 1 input/in_512.input output_prices.txt"