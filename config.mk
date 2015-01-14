TARGET:=	babix
ARCH:=		i686

CC:=		/usr/i686-elf-4.9.1-Linux-x86_64/bin/i686-elf-gcc
CFLAGS:=	-march=${ARCH}\
		-std=gnu99\
		-ffreestanding\
		-O2\
		-Wall -Wextra -Werror\
		-nostdlib\
		-lgcc

AS:=		/usr/i686-elf-4.9.1-Linux-x86_64/bin/i686-elf-as
ASFLAGS:=

LD:=		/usr/i686-elf-4.9.1-Linux-x86_64/bin/i686-elf-gcc
LDFLAGS:=	-march=i386 -ffreestanding -O2 -nostdlib -lgcc

BUILDD:=	build

QEMU:=		qemu-i386

GZIP:=		gzip

INCLUDE:=	includes
