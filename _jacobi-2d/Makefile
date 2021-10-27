#makefile

GCC_TOOLCHAIN_DIR := /opt/RISCV/

start:
	rm -rf bin/
	rm -rf output/
	mkdir bin
	mkdir output
	
serial:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -g -o bin/jacobi-2d_serial src/jacobi-2d.cpp
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/jacobi-2d_serial > bin/jacobi-2d_serial.dump

vector:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -o bin/jacobi-2d_vector src/jacobi-2d.cpp
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/jacobi-2d_vector > bin/jacobi-2d_vector.dump

clean:
	rm -rf bin/
	rm -rf output/

runqemu :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/jacobi-2d_serial 200 1 ./output/output_serial.txt
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/jacobi-2d_vector 200 1 ./output/output_vector.txt
