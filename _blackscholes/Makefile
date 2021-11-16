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
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -g -o bin/blackscholes_serial src/blackscholes.cpp
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/blackscholes_serial > bin/blackscholes_serial.dump


vector:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -o bin/blackscholes_vector src/blackscholes.cpp
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/blackscholes_vector > bin/blackscholes_vector.dump

serial_O2:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -O2 -g -o bin/blackscholes_serial_O2 src/blackscholes.cpp
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/blackscholes_serial_O2 > bin/blackscholes_serial_O2.dump


vector_O2:
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -O2 -g -o bin/blackscholes_vector_O2 src/blackscholes.cpp
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/blackscholes_vector_O2 > bin/blackscholes_vector_O2.dump

clean:
	rm -rf bin/
	rm -rf output/

runqemu :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/blackscholes_serial 1 ./input/in_64K.input ./output/output_serial.txt
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/blackscholes_vector 1 ./input/in_64K.input ./output/output_vector.txt

runqemu_O2 :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/blackscholes_serial_O2 1 ./input/in_64K.input ./output/output_serial.txt
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/blackscholes_vector_O2 1 ./input/in_64K.input ./output/output_vector.txt
