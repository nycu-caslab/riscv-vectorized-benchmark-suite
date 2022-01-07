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
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -g -c -o src/particlefilter_serial.o src/particlefilter.c
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -g -o bin/particlefilter_serial src/particlefilter_serial.o -lm
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/particlefilter_serial > bin/particlefilter_serial.dump
	rm src/*.o

	/opt/rvv-llvm/bin/clang++ --gcc-toolchain=/opt/RISCV --sysroot=/opt/RISCV/riscv64-unknown-linux-gnu -march=rv64gcv_zfh -flax-vector-conversions -static -g -c -o src/particlefilter_serial.o src/particlefilter.c
vector:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -c -o src/particlefilter_vector.o src/particlefilter.c
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -o bin/particlefilter_vector src/*.o -lm
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/particlefilter_vector > bin/particlefilter_vector.dump
	rm src/*.o

serial_O2:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -O2 -g -c -o src/particlefilter_serial.o src/particlefilter.c
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -O2 -g -o bin/particlefilter_serial_O2 src/particlefilter_serial.o -lm
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/particlefilter_serial_O2 > bin/particlefilter_serial_O2.dump
	rm src/*.o

vector_O2:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -O2 -g -c -o src/particlefilter_vector.o src/particlefilter.c
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -O2 -g -o bin/particlefilter_vector_O2 src/*.o -lm
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/particlefilter_vector_O2 > bin/particlefilter_vector_O2.dump
	rm src/*.o

serial_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -g -w -o bin/particlefilter_serial src/particlefilter.c
	${CLANG_DIR}bin/llvm-objdump -d bin/particlefilter_serial > bin/particlefilter_serial.dump

vector_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -static -g -w -o bin/particlefilter_vector src/particlefilter.c
	${CLANG_DIR}bin/llvm-objdump -d bin/particlefilter_vector > bin/particlefilter_vector.dump

serial_O2_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -O2 -g -w -o bin/particlefilter_serial_O2 src/particlefilter.c
	${CLANG_DIR}bin/llvm-objdump -d bin/particlefilter_serial_O2 > bin/particlefilter_serial_O2.dump

vector_O2_clang:
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -static -O2 -g -w -o bin/particlefilter_vector_O2 src/particlefilter.c
	${CLANG_DIR}bin/llvm-objdump -d bin/particlefilter_vector_O2 > bin/particlefilter_vector_O2.dump


clean:
	rm -rf bin/
	rm -rf output/

runqemu :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/particlefilter_vector -x 128 -y 128 -z 2 -np 256
	
runqemu_O2 :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/particlefilter_vector_O2 -x 128 -y 128 -z 2 -np 256
	
rungem5 :
	${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="${BENCHMARK_DIR}_particlefilter/bin/particlefilter_vector -x 128 -y 128 -z 2 -np 256"

rungem5_O2 :
	${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="${BENCHMARK_DIR}_particlefilter/bin/particlefilter_vector_O2 -x 128 -y 128 -z 2 -np 256"