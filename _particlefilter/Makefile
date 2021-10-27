#makefile

GCC_TOOLCHAIN_DIR := /opt/RISCV/

start:
	rm -rf bin/
	mkdir bin

serial:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -flax-vector-conversions -static -g -c -o src/particlefilter_serial.o src/particlefilter.c
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -flax-vector-conversions -static -g -o bin/particlefilter_serial src/particlefilter_serial.o -lm
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/particlefilter_serial > bin/particlefilter_serial.dump
	rm src/*.o

vector:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -c -O2 -o src/particlefilter_vector.o src/particlefilter.c
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-gcc -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -O2 -o bin/particlefilter_vector src/*.o -lm
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/particlefilter_vector > bin/particlefilter_vector.dump
	rm src/*.o

clean:
	rm -rf bin/

runqemu :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/particlefilter_serial -x 128 -y 128 -z 2 -np 256
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/particlefilter_vector -x 128 -y 128 -z 2 -np 256
	
