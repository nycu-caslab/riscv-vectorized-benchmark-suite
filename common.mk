# this_path:=$(abspath $(lastword $(MAKEFILE_LIST)))
# ROOT_DIR:=$(notdir $(patsubst %/,%,$(dir $(this_path))))
# ABS_ROOT_DIR=$(abspath $(ROOT_DIR))
# ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

include $(ROOT_DIR)/env.mk


INC:= -I$(ROOT_DIR)/unit_test/common/
RISCV_FLAGS := -march=$(ARCH) -DUSE_RISCV_VECTOR -static -g $(INC)

SRC_C:= $(wildcard src/*.c )
SRC_S:= $(wildcard src/*.S )
SRC_CPP:= $(wildcard src/*.cpp )
SRC_UNITT:= $(wildcard $(ROOT_DIR)/unit_test/common/*.cpp)


OBJ_C:= $(patsubst %.c, %.o, $(SRC_C) )
OBJ_S:= $(patsubst %.S, %.o, $(SRC_S) )
OBJ_CPP:= $(patsubst %.cpp, %.o, $(SRC_CPP))
OBJ_UNITT:= $(patsubst %.cpp, %.o, $(SRC_UNITT))

OBJ:= $(OBJ_C) $(OBJ_S) $(OBJ_CPP) $(OBJ_UNITT)

%.o: %.S
	${RISCV_CC} ${RISCV_FLAGS} -c -o $@ $<

%.o: %.c
	${RISCV_CC} ${RISCV_FLAGS} -c -o $@ $<

%.o: %.cpp
	${RISCV_C++} ${RISCV_FLAGS} -c -o $@ $<

