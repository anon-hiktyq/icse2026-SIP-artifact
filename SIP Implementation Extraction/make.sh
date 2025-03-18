#!/bin/bash
cd dependency/llvm/
mkdir build 
cd build
cmake -DLLVM_ENABLE_RTTI=ON -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install ../llvm
make
make install
cd ../../../

mkdir -p build
if cd build; then
    cmake -G "Unix Makefiles" \
          -DLLVM_DIR=./dependency/llvm/install/lib/cmake/llvm/ \
          -DCMAKE_INSTALL_PREFIX=../install/ \
          -DZ3_DIR=./dependency/z3_install/ \
          -DSVF_DIR=./dependency/svf_install/ \
          ../
    if [ $? -eq 0 ]; then
        make
    else
        echo "CMake 配置失败" >&2
        exit 1
    fi
else
    echo "进入 'build' 目录失败" >&2
    exit 1
fi

if [ $? -eq 0 ]; then
    echo "构建完成"
else
    echo "构建失败" >&2
    exit 1
fi
