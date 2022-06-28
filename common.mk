# this_path:=$(abspath $(lastword $(MAKEFILE_LIST)))
# ROOT_DIR:=$(notdir $(patsubst %/,%,$(dir $(this_path))))
# ABS_ROOT_DIR=$(abspath $(ROOT_DIR))
# ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

include $(ROOT_DIR)/env.mk


RISCV_FLAGS := -march=$(ARCH) -DUSE_RISCV_VECTOR -static -g

SRC_C:= $(wildcard src/*.c )
SRC_S:= $(wildcard src/*.S )
SRC_CPP:= $(wildcard src/*.cpp )

OBJ_C:= $(patsubst %.c, %.o, $(SRC_C) )
OBJ_S:= $(patsubst %.S, %.o, $(SRC_S) )
OBJ_CPP:= $(patsubst %.cpp, %.o, $(SRC_CPP) )

OBJ:= $(OBJ_C) $(OBJ_S) $(OBJ_CPP)

%.o: %.S
	${RISCV_CC} ${RISCV_FLAGS} -c -o $@ $<

%.o: %.c
	${RISCV_CC} ${RISCV_FLAGS} -c -o $@ $<

%.o: %.cpp
	${RISCV_C++} ${RISCV_FLAGS} -c -o $@ $<

