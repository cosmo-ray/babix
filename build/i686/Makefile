include ${PDIR}/config.mk

OBJS:=	$(wildcard *.o)

${TARGET}: ${OBJS}
	${LD} -T ./linker.ld -o $@ ${LDFLAGS} $^

clean: 
	@rm -vf ${TARGET}

