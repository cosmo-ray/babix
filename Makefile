include config.mk

all:	Makefile link

kernel: FORCE
	make -C $@ PDIR=..

boot:	FORCE
	make -C $@ PDIR=..

link:	kernel boot  
	make -C build PDIR=..

clean:
	make -C kernel clean PDIR=..
	make -C boot clean PDIR=..
fclean: clean
	make -C build clean PDIR=..
FORCE:
