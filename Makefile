include config.mk

all:	Makefile link

kernel: FORCE
	${MAKE} $@ PDIR=..

boot:	FORCE
	${MAKE} $@ PDIR=..

link:	kernel boot  
	${MAKE} build PDIR=..

re:	clean all 
clean:
	${MAKE} kernel clean PDIR=..
	${MAKE} boot clean PDIR=..
fclean: clean
	${MAKE} build clean PDIR=..


test:	all
	qemu -kernel ${BUILDD}/${TARGET}


FORCE:
