# RISC-V Vectorized Bencmark Suite

This repository is forked from https://github.com/RALC88/riscv-vectorized-benchmark-suite. The original implementation is based on rvv-0.7.1 and it has been updated to be based on rvv-1.0 in this repository.

## Overview

The RISC-V Vectorized Benchmark Suite is a collection composed of seven data-parallel applications from different domains. The suite focuses on benchmarking vector microarchitectures; nevertheless, it can be used as well for Multimedia SIMD microarchitectures. Current implementation is targeting RISC-V Architectures; however, it can be easily ported to any Vector/SIMD ISA thanks to a wrapper library which we developed to map vector intrinsics and math functions to the target architecture.

The benchmark suite with all its applications and input sets is available as open source free of charge. Some of the benchmark programs have their own licensing terms which might limit their use in some cases.

The implementation is based on the working draft of the proposed [RISC-V V vector extension v1.0 Spec](https://github.com/riscv/riscv-v-spec) and [intrinsic API](https://github.com/riscv/rvv-intrinsic-doc).

If you use this software or a modified version of it for your research, please cite the paper:
Cristóbal Ramirez, César Hernandez, Oscar Palomar, Osman Unsal, Marco Ramírez, and Adrián Cristal. 2020. A RISC-V Simulator and Benchmark Suite for Designing and Evaluating Vector Architectures. ACM Trans. Archit. Code Optim. 17, 4, Article 38 (October 2020), 29 pages. https://doi.org/10.1145/3422667



## Pakage Structure

    Vectorized_Benchmark_Suite/ : The Vectorized Benchmark Suite
        _axpy/                  : axpy main folder
        ...../src               : axpy sources
        ...../bin               : axpy binary
        blackscholes/           : Blackscholes main folder
        ...../src               : Blackscholes sources
        ...../bin               : Blackscholes binary
        canneal/                : canneal main folder
        ...../src               : canneal sources
        ...../bin               : canneal binary
        _jacobi-2d/             : jacobi-2d main folder
        ...../src               : jacobi-2d sources
        ...../bin               : jacobi-2d binary
        particlefilter/         : particlefilter main folder
        ...../src               : particlefilter sources
        ...../bin               : particlefilter binary
        pathfinder/             : pathfinder main folder
        ...../src               : pathfinder sources
        ...../bin               : pathfinder binary
        streamcluster/          : streamcluster main folder
        ...../src               : streamcluster sources
        ...../bin               : streamcluster binary
        swaptions/              : swaptions main folder
        ...../src               : swaptions sources
        ...../bin               : swaptions binary
        common/                 : intrinsics defines & Math functions

## Building Vectorized Applications 

The RISC-V Vectorized Bencmark Suite has been successfully tested on QEMU Simulator of the **rvv-intrinsic** branch of [RISC-V GNU toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain) and the **benchmark** branch of [plct-gem5](https://github.com/plctlab/plct-gem5)

### Setting up the environment

The Suite includes a makefile to compile every application. In order to use it, you must [Build RISC-V GNU toolchain](./Build_RISCV_GNU_toolchain.md) and define the path to it.

Setting RISC-V GNU toolchain path
```
export GCC_TOOLCHAIN_DIR := /opt/RISCV/
```

Currently, the Suite can only be compiled by the **rvv-intrinsic** branch of [RISC-V GNU toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain).

### Compile using RISC-V GNU toolchain for RISCV Vector Version

To compile any application you can run the command make followed by the application name
```
make $application
```
For example to compile blackscholes:
```
make blackscholes 
```
The same for the other applications ...

To compile all applications you can run
```
make all
```

To compile with the "-O2" optimization option you can run the command with "\_O2" suffix. For example:
```
make all_O2
```
or
```
make blackscholes_O2
```

### Running applications

The Suite includes a makefile to compile every application. In order to use it, you must [build QEMU Simulator of RISC-V GNU toolchain](./Build_RISCV_GNU_toolchain.md) or [plct-gem5](https://github.com/plctlab/plct-gem5) and define the path to it.

Setting path of gem5 and benchmark:
```
export GEM5_DIR := /git/plct-gem5/
export BENCHMARK_DIR := /git/riscv-vectorized-benchmark-suite/
```

To run any application you first enter in the subfolder and run the running command.
```
cd _$application
make runqemu
```
or
```
cd _$application
make rungem5
```

For example:
```
cd _blackscholes
make runqemu
```
or
```
cd _blackscholes
make rungem5
```

To run the version with "-O2" optimization option you can run the command with "\_O2" suffix.
```
cd _$application
make runqemu_O2
```
or
```
cd _$application
make rungem5_O2
```

To run all applications you can:
```
make runqemu_all{_O2}
```
or
```
make rungem5_all{_O2}
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
${GCC_TOOLCHAIN_DIR}bin/qemu-riscv64 -cpu rv64,x-v=true bin/$application_bin $application_args
```
or
```
cd _$application
${GEM5_DIR}build/RISCV/gem5.opt ${GEM5_DIR}configs/example/riscv_vector_engine.py --cmd="${BENCHMARK_DIR}_$application/bin/$application_bin $application_args"
```

## Contributors and Contacts
Yin Zhang   zhangyin2018@iscas.ac.cn
Chunyu Liao chunyu@iscas.ac.cn

Original author:
Cristóbal Ramírez Lazo: cristobal.ramirez@bsc.es
PhD. Student at UPC Barcelona   
BSC - Barcelona Supercomputing Center

