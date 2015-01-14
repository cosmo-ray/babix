TARGET:=	babix
ARCH:=		i686

CC:=		/usr/i686-elf-4.9.1-Linux-x86_64/bin/i686-elf-gcc
CFLAGS:=	-march=${ARCH}\
		-std=gnu99\
		-ffreestanding\
		-O2 -ggdb\
		-Wall -Wextra -Werror\

AS:=		/usr/i686-elf-4.9.1-Linux-x86_64/bin/i686-elf-gcc
ASFLAGS:=	-ggdb 

LD:=		/usr/i686-elf-4.9.1-Linux-x86_64/bin/i686-elf-gcc
LDFLAGS:=	-march=${ARCH}\
		-ffreestanding\
		-O2 -ggdb\
		-nostdlib -lgcc

MAKE:= 		@make --no-print-directory -C

BUILDD:=	build/${ARCH}

QEMU:=		qemu-i386

GZIP:=		gzip

INCLUDE:=	include
