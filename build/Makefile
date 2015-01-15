include ${PDIR}/config.mk

${ARCH}: FORCE
	 ${MAKE} $@ PDIR=../${PDIR}
FORCE:

clean:
	@rm -fv *.o
	${MAKE} ${ARCH} clean PDIR=../${PDIR}

