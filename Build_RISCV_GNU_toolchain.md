# Build RISC-V GNU toolchain

## Prerequisites
```
apt-get update
apt-get install gcc g++ git make cmake python python3 gcc-multilib vim autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev pkg-config libglib2.0-dev
```

## Build RISC-V GNU toolchain and QEMU Simulator for rvv-intrinsic branch
```
git clone git@github.com:riscv/riscv-gnu-toolchain.git -b rvv-intrinsic
cd riscv-gnu-toolchain
git submodule update --init --recursive
./configure --prefix=/opt/RISCV --with-arch=rv64gcv_zfh --with-abi=lp64d
make linux -j$(nproc)
make build-qemu -j$(nproc)
```
