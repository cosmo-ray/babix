# babix

A lighweight micro-kernel

# Dependencies:
  - make 
  - *(amd64 hosts)* GCC i686 Cross-compiler http://newos.org/toolchains/i686-elf-4.9.1-Linux-x86_64.tar.xz 
  - *(i686 hosts)* GCC 4.7, as, ld
  - qemu (for test purposes only)
  
# Installation
*(amd64 hosts)* ```sudo tar -xf i686-elf-4.9.1-Linux-x86_64.tar.xz -C /usr/```

```
make
make test
```
