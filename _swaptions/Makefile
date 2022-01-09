export GCC_TOOLCHAIN_DIR= /opt/riscv-gnu-toolchain/
export CLANG_DIR= /opt/llvm/
export GEM5_DIR= /opt/gem5/
export QEMU_DIR= /opt/qemu/

export llvm_dump_options?= -d --mattr=experimental-v

start:
	if [ ! -d bin ]; then \
		mkdir bin; \
	else \
		echo bin dir exist; \
	fi

serial:
	for entry in src/*.cpp ; do \
		${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -g -c -o $$entry.o $$entry; \
	done
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -g -o bin/swaptions_serial src/*.cpp.o -lm; \
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/swaptions_serial > bin/swaptions_serial.dump; \
	rm src/*.o;

vector:
	for entry in src/*.cpp ; do \
		${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -c -o $$entry.o $$entry; \
	done
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -o bin/swaptions_vector src/*.cpp.o -lm; \
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/swaptions_vector > bin/swaptions_vector.dump; \
	rm src/*.o;

serial_O2:
	for entry in src/*.cpp ; do \
		${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -O2 -g -c -o $$entry.o $$entry; \
	done
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -O2 -g -o bin/swaptions_serial_O2 src/*.cpp.o -lm; \
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/swaptions_serial_O2 > bin/swaptions_serial_O2.dump; \
	rm src/*.o;

vector_O2:
	for entry in src/*.cpp ; do \
		${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -O2 -g -c -o $$entry.o $$entry; \
	done
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -O2 -g -o bin/swaptions_vector_O2 src/*.cpp.o -lm; \
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/swaptions_vector_O2 > bin/swaptions_vector_O2.dump; \
	rm src/*.o;

serial_clang:
	for entry in src/*.cpp ; do \
		${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -g -c -w -o $$entry.o $$entry; \
	done
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -g -w -o bin/swaptions_serial src/*.cpp.o -lm; \
	${CLANG_DIR}bin/llvm-objdump ${llvm_dump_options} bin/swaptions_serial > bin/swaptions_serial.dump; \
	rm src/*.o;

vector_clang:
	for entry in src/*.cpp ; do \
		${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -static -g -c -w -o $$entry.o $$entry; \
	done
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -static -g -w -o bin/swaptions_vector src/*.cpp.o -lm; \
	${CLANG_DIR}bin/llvm-objdump ${llvm_dump_options} bin/swaptions_vector > bin/swaptions_vector.dump; \
	rm src/*.o;

serial_O2_clang:
	for entry in src/*.cpp ; do \
		${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -O2 -g -c -w -o $$entry.o $$entry; \
	done
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -O2 -g -w -o bin/swaptions_serial_O2 src/*.cpp.o -lm; \
	${CLANG_DIR}bin/llvm-objdump ${llvm_dump_options} bin/swaptions_serial_O2 > bin/swaptions_serial_O2.dump; \
	rm src/*.o;

vector_O2_clang:
	for entry in src/*.cpp ; do \
		${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -static -O2 -g -c -w -o $$entry.o $$entry; \
	done
	${CLANG_DIR}bin/clang++ --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -static -O2 -g -w -o bin/swaptions_vector_O2 src/*.cpp.o -lm; \
	${CLANG_DIR}bin/llvm-objdump ${llvm_dump_options} bin/swaptions_vector_O2 > bin/swaptions_vector_O2.dump; \
	rm src/*.o;

clean:
	rm -rf bin/

runqemu :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/swaptions_vector -ns 8 -sm 512 -nt 1

runqemu_O2 :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/swaptions_vector_O2 -ns 8 -sm 512 -nt 1

rungem5 :
	${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="${PWD}/bin/swaptions_vector -ns 8 -sm 512 -nt 1"

rungem5_O2 :
	${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="${PWD}/bin/swaptions_vector_O2 -ns 8 -sm 512 -nt 1"