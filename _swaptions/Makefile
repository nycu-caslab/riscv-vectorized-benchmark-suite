#makefile

GCC_TOOLCHAIN_DIR := /opt/RISCV/

start:
	if [ ! -d bin ]; then \
		mkdir bin; \
	else \
		echo bin dir exist; \
	fi

serial:
	for entry in src/*.cpp ; do \
		${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -g -c -o $$entry.o $$entry; \
	done
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -g -o bin/swaptions_serial src/*.cpp.o -lm; \
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/swaptions_serial > bin/swaptions_serial.dump; \
	rm src/*.o;

vector:
	for entry in src/*.cpp ; do \
		${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -c -o $$entry.o $$entry; \
	done
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -g -o bin/swaptions_vector src/*.cpp.o -lm; \
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/swaptions_vector > bin/swaptions_vector.dump; \
	rm src/*.o;

serial_O2:
	for entry in src/*.cpp ; do \
		${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -O2 -g -c -o $$entry.o $$entry; \
	done
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -flax-vector-conversions -static -O2 -g -o bin/swaptions_serial_O2 src/*.cpp.o -lm; \
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/swaptions_serial_O2 > bin/swaptions_serial_O2.dump; \
	rm src/*.o;

vector_O2:
	for entry in src/*.cpp ; do \
		${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -O2 -g -c -o $$entry.o $$entry; \
	done
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-g++ -march=rv64gcv_zfh -DUSE_RISCV_VECTOR -flax-vector-conversions -static -O2 -g -o bin/swaptions_vector_O2 src/*.cpp.o -lm; \
	${GCC_TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-gnu-objdump -d bin/swaptions_vector_O2 > bin/swaptions_vector_O2.dump; \
	rm src/*.o;

clean:
	rm -rf bin/

runqemu :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/swaptions_serial -ns 8 -sm 512 -nt 1
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/swaptions_vector -ns 8 -sm 512 -nt 1

runqemu_O2 :
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/swaptions_serial_O2 -ns 8 -sm 512 -nt 1
	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/swaptions_vector_O2 -ns 8 -sm 512 -nt 1
