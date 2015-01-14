include ${PDIR}/config.mk

${ARCH}: FORCE
	 make -C $@ PDIR=../${PDIR}
FORCE:

clean:
	make -C ${ARCH} clean PDIR=../${PDIR}

