CUR_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
ROOT_DIR:=$(CUR_DIR)/../
include $(ROOT_DIR)/common.mk

MAIN:=axpy

vector: $(OBJ)
	${RISCV_CC} ${RISCV_FLAGS} -o bin/$(MAIN) $^ -lm; \
	${RISCV_DUMP} -D bin/$(MAIN) > bin/$(MAIN).dump; \
	rm src/*.o;

clean:
	rm -rf bin/


runqemu :
	${QEMU_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true,vlen=128,elen=64,vext_spec=v1.0 ${PWD}/bin/$(MAIN)


rungem5 :
	${GEM5_DIR}build/RISCV/gem5.opt \
		${GEM5_DIR}configs/example/se.py --num-cpus 1 \
        --cpu-type MinorCPU \
        --caches \
        --cmd ${PWD}/bin/$(MAIN) \
		--output log
		2>&1 | tee run.log
