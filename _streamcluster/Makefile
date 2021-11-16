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
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -g -o bin/streamcluster_serial src/streamcluster.cpp
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/streamcluster_serial > bin/streamcluster_serial.dump

vector:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -o bin/streamcluster_vector src/streamcluster.cpp
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/streamcluster_vector > bin/streamcluster_vector.dump

serial_O2:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -O2 -g -o bin/streamcluster_serial_O2 src/streamcluster.cpp
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/streamcluster_serial_O2 > bin/streamcluster_serial_O2.dump

vector_O2:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -O2 -g -o bin/streamcluster_vector_O2 src/streamcluster.cpp
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/streamcluster_vector_O2 > bin/streamcluster_vector_O2.dump

clean:
	rm -rf bin/
	rm -rf output/

runqemu :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/streamcluster_serial 3 10 128 128 128 10 none ./output/output_serial.txt 1
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/streamcluster_vector 3 10 128 128 128 10 none ./output/output_vector.txt 1

runqemu_O2 :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/streamcluster_serial_O2 3 10 128 128 128 10 none ./output/output_serial.txt 1
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/streamcluster_vector_O2 3 10 128 128 128 10 none ./output/output_vector.txt 1
