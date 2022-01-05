# RiVEC Bencmark Suite

This repository is forked from https://github.com/RALC88/riscv-vectorized-benchmark-suite. The original implementation is based on rvv-0.7.1 and it has been updated to be based on rvv-1.0 in this repository.

## Overview

The RiVEC Benchmark Suite is a collection composed of data-parallel applications from different domains. The suite focuses on benchmarking vector microarchitectures; nevertheless, it can be used as well for Multimedia SIMD microarchitectures. Current implementation is targeting RISC-V Architectures; however, it can be easily ported to any Vector/SIMD ISA thanks to a wrapper library which we developed to map vector intrinsics and math functions to the target architecture.

The benchmark suite with all its applications and input sets is available as open source free of charge. Some of the benchmark programs have their own licensing terms which might limit their use in some cases.

The implementation is based on the working draft of the proposed [RISC-V V vector extension v1.0 Spec](https://github.com/riscv/riscv-v-spec) and [intrinsic API](https://github.com/riscv/rvv-intrinsic-doc).

If you use this software or a modified version of it for your research, please cite the paper:
Cristóbal Ramirez, César Hernandez, Oscar Palomar, Osman Unsal, Marco Ramírez, and Adrián Cristal. 2020. A RISC-V Simulator and Benchmark Suite for Designing and Evaluating Vector Architectures. ACM Trans. Archit. Code Optim. 17, 4, Article 38 (October 2020), 29 pages. https://doi.org/10.1145/3422667

## Pakage Structure

    Vectorized_Benchmark_Suite/ : The Vectorized Benchmark Suite
        _axpy/                  : axpy main folder
        ...../src               : axpy sources
        ...../bin               : axpy binary
        _blackscholes/          : Blackscholes main folder
        ...../src               : Blackscholes sources
        ...../bin               : Blackscholes binary
        _canneal/               : canneal main folder
        ...../src               : canneal sources
        ...../bin               : canneal binary
        _jacobi-2d/             : jacobi-2d main folder
        ...../src               : jacobi-2d sources
        ...../bin               : jacobi-2d binary
        _particlefilter/        : particlefilter main folder
        ...../src               : particlefilter sources
        ...../bin               : particlefilter binary
        _pathfinder/            : pathfinder main folder
        ...../src               : pathfinder sources
        ...../bin               : pathfinder binary
        _streamcluster/         : streamcluster main folder
        ...../src               : streamcluster sources
        ...../bin               : streamcluster binary
        _swaptions/             : swaptions main folder
        ...../src               : swaptions sources
        ...../bin               : swaptions binary
        common/                 : intrinsics defines & Math functions

## Building Vectorized Applications

The RISC-V Vectorized Bencmark Suite has been successfully tested on QEMU Simulator of the **rvv-intrinsic** branch of [RISC-V GNU toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain) and the **benchmark** branch of [plct-gem5](https://github.com/plctlab/plct-gem5)

### Setting up the environment

#### Generate binaries using RISC-V GNU toolchain

The Suite includes a makefile to compile every application. In order to use it, you must [Build RISC-V GNU toolchain](./Build_RISCV_GNU_toolchain.md).

Currently, the Suite can only be compiled by the **rvv-intrinsic** branch of [RISC-V GNU toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain).

#### Generate binaries using LLVM

The Suite also can be compiled with LLVM, you need to install the [LLVM Compiler Infrastructure](https://github.com/llvm/llvm-project). Currently LLVM uses RISC-V GNU toolchain to link and generate executable file, so you also need to install it.

### Compile using RISC-V GNU toolchain for RISCV Vector Version

To compile any application you can run the command make followed by the application name:

```bash
make blackscholes
make swaptions
make streamcluster
make canneal
make particlefilter
make pathfinder
make jacobi-2d
make axpy
```

To compile with the "-O2" optimization option you can run the command with `_O2` suffix. For example:

```bash
make blackscholes_O2
```

To compile with LLVM clang, you can run the command with `_clang` suffix:

```bash
make blackscholes_clang
make blackscholes_O2_clang
```

To compile all applications you can run

```bash
make all
make all_O2
# OR
make all_clang
make all_O2_clang
```

Our Makefile comes with default assumption about GNU toolchain and LLVM's install path:

```bash
export GCC_TOOLCHAIN_DIR= /opt/riscv-gnu-toolchain/
export CLANG_DIR= /opt/llvm/
```

If this is wrong path for you, you can change it:

```bash
make all GCC_TOOLCHAIN_DIR=/path/to/toolchain/ CLANG_DIR=/path/to/clang/
```

### Running applications

The Suite includes a makefile to compile every application. In order to use it, you must [build QEMU Simulator of RISC-V GNU toolchain](./Build_RISCV_GNU_toolchain.md) or [plct-gem5](https://github.com/plctlab/plct-gem5).

To run any application .

```bash
make rungem5_blackscholes
make rungem5_blackscholes_O2

make runqemu_blackscholes
make runqemu_blackscholes_O2

make rungem5_all
make rungem5_all_O2

make runqemu_all
make runqemu_all_O2
```

There are provided 4 different simulation sizes (arguments to run the application).

```
simtiny 
simsmall
simmedium
simlarge
```

When you are executing an application, you must write the following arguments to run a predefined simsize.

#### simtiny

```
blackscholes_args   = "1 input/in_512.input output_prices.txt"
canneal_args        = "1 100 300 input/100.nets 8"
streamcluster_args  = "3 10 128 128 128 10 none output.txt 1"
swaptions_args      = "-ns 8 -sm 512 -nt 1"
particlefilter_args = "-x 128 -y 128 -z 2 -np 256"
pathfinder_args     = "32 32 output.txt"
axpy_args           = "256"
```

#### simsmall

```
blackscholes_args   = "1 input/in_4K.input output_prices.txt"
canneal_args        = "1 10000 2000 input/100000.nets 32"
streamcluster_args  = "10 20 128 4096 4096 1000 none output.txt 1"
swaptions_args      = "-ns 8 -sm 4096 -nt 1"
particlefilter_args = "-x 128 -y 128 -z 8 -np 1024"
pathfinder_args     = "1024 128 output.txt"
axpy_args           = "512"
```

#### simmedium

```
blackscholes_args   = "1 input/in_16K.input prices.txt"
canneal_args        = "1 15000 2000 input/200000.nets 64"
streamcluster_args  = "10 20 128 8192 8192 1000 none output.txt 1"
swaptions_args      = "-ns 32 -sm 8192 -nt 1"
particlefilter_args = "-x 128 -y 128 -z 16 -np 4096"
pathfinder_args     = "2048 256 output.txt"
axpy_args           = "1024"
```

#### simlarge

```
blackscholes_args   = "1 input/in_64K.input prices.txt"
canneal_args        = "1 15000 2000 input/400000.nets 128"
streamcluster_args  = "10 20 128 8192 8192 1000 none output.txt 1"
swaptions_args      = "-ns 64 -sm 16384 -nt 1"
particlefilter_args = "-x 128 -y 128 -z 24 -np 8192"
pathfinder_args     = "2048 1024 output.txt"
axpy_args           = "2048"
```

**Simtiny** is used by commands in Makefiles. If you want to run with the other simsize, you can try following commands, too.

```
cd _$application
${QEMU_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/$application_bin $application_args
```

or

```
cd _$application
${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="./_$application/bin/$application_bin $application_args"
```

## Contributors and Contacts

Yin Zhang   zhangyin2018@iscas.ac.cn

Chunyu Liao chunyu@iscas.ac.cn

Original author:

Cristóbal Ramírez Lazo: cristobal.ramirez@bsc.es
PhD. Student at UPC Barcelona   
BSC - Barcelona Supercomputing Center
