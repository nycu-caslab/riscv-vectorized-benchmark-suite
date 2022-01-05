# Build RISC-V GNU toolchain

Here is a step by step guide on how to compile the RISCV-GNU-Toolchain on macOS 10.15.3. The process of trying to compile is not smooth, so I think this may be useful to others.


```bash
git clone https://github.com/riscv-collab/riscv-gnu-toolchain.git -b rvv-intrinsic
cd riscv-gnu-toolchain
```

> macOS's file system is case insensitive by default, this will cause problems with `git clone`, you can create a new APFS case sensitive volume in the `Disk Utility.app` to solve this.




Next, edit `.gitmodules` file, change `[submodule "riscv-glibc"]` section to:

```ini
[submodule "riscv-glibc"]
        path = riscv-glibc
        url = https://github.com/riscvarchive/riscv-glibc.git
        branch = riscv-glibc-2.29
```

Next, run following command to download submodules:

```bash
git submodule sync
git -c http.sslVerify=false submodule update --init --recursive --force
```



Next, run following command to compile the whole thing:

```bash
./configure --prefix=/path/to/riscv-gnu-toolchain/build/ --with-arch=rv64gcv_zfh --with-abi=lp64d
make linux -j$(nproc)
```

>macOS's `ulimit` is 256 by default, this is not enough when compiling glibc, you will get a `Too many open files` error, run `ulimit -n 2048` .
>
>If you encounter this problem: `Undefined symbols for architecture x86_64: "_libintl_setlocale", referenced from: _main in cross-rpc_main.o`, you can change riscv-gnu-toolchain/riscv-glibc/sunrpc/Makefile:L178 to`$(BUILD_CC) $^ $(BUILD_LDFLAGS) -L/usr/lib -lintl -o $@`



References:

- https://plctlab.github.io/opencv/Optimize_OpenCV_for_RISC-V.html
- https://github.com/riscv-collab/riscv-gnu-toolchain
- https://crossgcc.s0ufcgwqre.narkive.com/0VohJtc2/libintl-on-mac-os-x