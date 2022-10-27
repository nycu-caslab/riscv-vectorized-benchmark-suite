CUR_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
ROOT_DIR:=$(CUR_DIR)/../../
include $(ROOT_DIR)/common.mk


MAIN:=vredsum


vector: $(OBJ)
	${RISCV_CC} ${RISCV_FLAGS} -o bin/$(MAIN) $^ -lm; \
	${RISCV_DUMP} -D bin/$(MAIN) > bin/$(MAIN).dump; \
	rm src/*.o;

clean:
	rm -rf bin/

runqemu :
	${QEMU_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true,vlen=128,elen=64,vext_spec=v1.0 ${PWD}/bin/$(MAIN) > qemu.log

# runqemu_O2 :
# 	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/axpy_vector_O2 256

rundgem5 :
	${GEM5_DIR}build/RISCV/gem5.debug \
		--debug-flags=Decode,Exec,VecRegs  \
		${GEM5_DIR}configs/example/se.py --num-cpus 1 \
        --cpu-type MinorCPU \
	--caches \
        --cmd ${PWD}/bin/$(MAIN) \
		--output log \
		2>&1 | tee run.log

rungem5 :
	${GEM5_DIR}build/RISCV/gem5.debug \
		${GEM5_DIR}configs/example/se.py --num-cpus 1 \
        --cpu-type MinorCPU \
	--caches \
        --cmd ${PWD}/bin/$(MAIN) \
		--output log \
		2>&1 | tee run.log

gdb:
	echo --debug-flags=RiscvMisc,Decode \
		${GEM5_DIR}configs/example/se.py --num-cpus 1 \
        --cpu-type MinorCPU \
        --caches \
        --cmd ${PWD}/bin/$(MAIN) \
		--output log \
		2>&1 | tee run.log 
	gdb ${GEM5_DIR}build/RISCV/gem5.debug


# rungem5_O2 :
# 	${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="${PWD}/bin/axpy_vector_O2 256"

