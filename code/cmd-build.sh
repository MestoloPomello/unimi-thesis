    make LLVM=-14 olddefconfig
    make -j"$(nproc)" LLVM=-14 prepare modules_prepare scripts