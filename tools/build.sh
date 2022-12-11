#!/bin/sh
set -e

cmake -B build \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_CXX_FLAGS="-stdlib=libc++" \
    -DCMAKE_EXE_LINKER_FLAGS="-lc++ -lc++abi -flto=thin -fuse-ld=lld"
make -j12 -C build

