make -j"$(nproc)" LLVM=-14 \
  CC=gclang HOSTCC=clang-14 HOSTCXX=clang++-14 \
  LD=ld.lld-14 AR=llvm-ar-14 NM=llvm-nm-14 \
  OBJCOPY=llvm-objcopy-14 \
  OBJDUMP=llvm-objdump-14 \
  STRIP=llvm-strip-14 \
  net/vmw_vsock/vsock.o \
  net/vmw_vsock/vmw_vsock_virtio_transport.o \
  net/vmw_vsock/vmw_vsock_virtio_transport_common.o \
  net/vmw_vsock/vsock_loopback.o \
  net/vmw_vsock/vsock_diag.o \
  net/socket.o