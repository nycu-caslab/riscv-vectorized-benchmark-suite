#makefile

GCC_TOOLCHAIN_DIR := /opt/RISCV/

start:
	rm -rf bin/
	mkdir bin

serial:
	for entry in src/*.c ; do \
		${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -flax-vector-conversions -static -g -c -o $$entry.o $$entry; \
	done
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -flax-vector-conversions -static -g -o bin/axpy_serial src/*.c.o -lm; \
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/axpy_serial > bin/axpy_serial.dump; \
	rm src/*.o;

vector:
	for entry in src/*.c ; do \
		${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -c -o $$entry.o $$entry; \
	done
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -o bin/axpy_vector src/*.c.o -lm; \
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/axpy_vector > bin/axpy_vector.dump; \
	rm src/*.o;

clean:
	rm -rf bin/

runqemu :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/axpy_serial 256
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/axpy_vector 256
