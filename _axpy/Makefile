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

serial:
	for entry in src/*.c ; do \
		${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -flax-vector-conversions -static -g -c -o $$entry.o $$entry; \
	done
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -flax-vector-conversions -static -g -o bin/axpy_serial src/*.c.o -lm; \
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/axpy_serial > bin/axpy_serial.dump; \
	rm src/*.o;

vector:
	for entry in src/*.c ; do \
		${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -c -o $$entry.o $$entry; \
	done
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -o bin/axpy_vector src/*.c.o -lm; \
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/axpy_vector > bin/axpy_vector.dump; \
	rm src/*.o;

serial_O2:
	for entry in src/*.c ; do \
		${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -flax-vector-conversions -static -O2 -g -c -o $$entry.o $$entry; \
	done
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -flax-vector-conversions -static -O2 -g -o bin/axpy_serial_O2 src/*.c.o -lm; \
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/axpy_serial_O2 > bin/axpy_serial_O2.dump; \
	rm src/*.o;

vector_O2:
	for entry in src/*.c ; do \
		${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -O2 -static -g -c -o $$entry.o $$entry; \
	done
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -O2 -static -g -o bin/axpy_vector_O2 src/*.c.o -lm; \
	${GCC_TOOLCHAIN_DIR}bin/riscv64-unknown-linux-gnu-objdump -d bin/axpy_vector_O2 > bin/axpy_vector_O2.dump; \
	rm src/*.o;

serial_clang:
	for entry in src/*.c ; do \
		${CLANG_DIR}bin/clang --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -g -c -w -o $$entry.o $$entry; \
	done
	${CLANG_DIR}bin/clang --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -g -w -o bin/axpy_serial src/*.c.o -lm; \
	${CLANG_DIR}bin/llvm-objdump -d bin/axpy_serial > bin/axpy_serial.dump; \
	rm src/*.o;

vector_clang:
	for entry in src/*.c ; do \
		${CLANG_DIR}bin/clang --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -static -g -c -w -o $$entry.o $$entry; \
	done
	${CLANG_DIR}bin/clang --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -static -g -w -o bin/axpy_vector src/*.c.o -lm; \
	${CLANG_DIR}bin/llvm-objdump -d bin/axpy_vector > bin/axpy_vector.dump; \
	rm src/*.o;

serial_O2_clang:
	for entry in src/*.c ; do \
		${CLANG_DIR}bin/clang --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -O2 -g -c -w -o $$entry.o $$entry; \
	done
	${CLANG_DIR}bin/clang --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -static -O2 -g -w -o bin/axpy_serial_O2 src/*.c.o -lm; \
	${CLANG_DIR}bin/llvm-objdump -d bin/axpy_serial_O2 > bin/axpy_serial_O2.dump; \
	rm src/*.o;

vector_O2_clang:
	for entry in src/*.c ; do \
		${CLANG_DIR}bin/clang --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -O2 -static -g -c -w -o $$entry.o $$entry; \
	done
	${CLANG_DIR}bin/clang --target=riscv64-unknown-linux-gnu -march=rv64gcv0p10 -menable-experimental-extensions --gcc-toolchain=${GCC_TOOLCHAIN_DIR} --sysroot=${GCC_TOOLCHAIN_DIR}sysroot -flax-vector-conversions -DUSE_RISCV_VECTOR -O2 -static -g -w -o bin/axpy_vector_O2 src/*.c.o -lm; \
	${CLANG_DIR}bin/llvm-objdump -d bin/axpy_vector_O2 > bin/axpy_vector_O2.dump; \
	rm src/*.o;

clean:
	rm -rf bin/

runqemu :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/axpy_vector 256

runqemu_O2 :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/axpy_vector_O2 256

rungem5 :
	${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="${PWD}/bin/axpy_vector 256"

rungem5_O2 :
	${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="${PWD}/bin/axpy_vector_O2 256"