#makefile

GCC_TOOLCHAIN_DIR := /opt/RISCV/

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
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -g -o bin/pathfinder_serial src/pathfinder.cpp
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/pathfinder_serial > bin/pathfinder_serial.dump

vector:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -o bin/pathfinder_vector src/pathfinder.cpp
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/pathfinder_vector > bin/pathfinder_vector.dump

serial_O2:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -O2 -g -o bin/pathfinder_serial_O2 src/pathfinder.cpp
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/pathfinder_serial_O2 > bin/pathfinder_serial_O2.dump

vector_O2:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -O2 -g -o bin/pathfinder_vector_O2 src/pathfinder.cpp
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/pathfinder_vector_O2 > bin/pathfinder_vector_O2.dump

clean:
	rm -rf bin/
	rm -rf output/

runqemu :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/pathfinder_serial 32 32 ./output/output_serial.txt
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/pathfinder_vector 32 32 ./output/output_vector.txt

runqemu_O2 :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/pathfinder_serial_O2 32 32 ./output/output_serial.txt
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/pathfinder_vector_O2 32 32 ./output/output_vector.txt
