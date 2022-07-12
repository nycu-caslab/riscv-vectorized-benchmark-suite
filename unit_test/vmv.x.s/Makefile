CUR_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
ROOT_DIR:=$(CUR_DIR)/../../
include $(ROOT_DIR)/common.mk


MAIN:=vmv_x_s
DIST_DIR = bin

vector: $(OBJ)
	test ! -d $(DIST_DIR) && mkdir $(DIST_DIR); \
	${RISCV_CC} ${RISCV_FLAGS} -o $(DIST_DIR)/$(MAIN) $^ -lm; \
	${RISCV_DUMP} -D $(DIST_DIR)/$(MAIN) > $(DIST_DIR)/$(MAIN).dump; \
	rm src/*.o;

clean:
	rm -rf $(DIST_DIR)/

runqemu :
	${QEMU_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true,vlen=128,elen=64,vext_spec=v1.0 ${PWD}/bin/$(MAIN) > qemu.log

# runqemu_O2 :
# 	${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/axpy_vector_O2 256

rungem5 :
	${GEM5_DIR}build/RISCV/gem5.debug \
		${GEM5_DIR}configs/example/se.py --num-cpus 1 \
        --cpu-type MinorCPU \
        --caches \
        --cmd ${PWD}/$(DIST_DIR)/$(MAIN) \
		--output log
		2>&1 | tee run.log

gdb:
	echo --debug-flags=RiscvMisc,Decode \
		${GEM5_DIR}configs/example/se.py --num-cpus 1 \
        --cpu-type MinorCPU \
        --caches \
        --cmd ${PWD}/$(DIST_DIR)/$(MAIN) \
		--output log \
		2>&1 | tee run.log 
	gdb ${GEM5_DIR}build/RISCV/gem5.debug


# rungem5_O2 :
# 	${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="${PWD}/bin/axpy_vector_O2 256"

