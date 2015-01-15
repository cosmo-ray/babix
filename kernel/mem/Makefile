include ${PDIR}/config.mk
include deps.mk

SUBBDIRS	= ${shell find . -mindepth 1 -maxdepth 1 -not -empty -type d}
#sub build dir (not used)
#SUBBDIR	= ${PDIR}/${BUILDD}/$(notdir $(shell pwd))

OBJS = $(subst .c,.o, $(addprefix ${PDIR}/${BUILDD}/, $(SRCS)))

all: ${OBJS} ${SUBBDIRS} ${SUBBDIR}

${PDIR}/${BUILDD}/%.o: %.c
	$(CC) $(CFLAGS) -I ${PDIR}/$(INCLUDE) -c $< -o $@

${SUBBDIRS}: FORCE
	${MAKE} $@ PDIR=../${PDIR}

clean:
	@rm -vf ${OBJS}
FORCE:
