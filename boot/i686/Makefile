include ${PDIR}/config.mk
include deps.mk

SUBDIRS	= ${shell find . -mindepth 1 -maxdepth 1 -not -empty -type d}
#sub build dir (not used)
#SUBBDIR	= ${PDIR}/${BUILDD}/$(notdir $(shell pwd))

OBJS = $(subst .s,.o, $(addprefix ${PDIR}/${BUILDD}/, $(SRCS)))

all: ${OBJS}

${PDIR}/${BUILDD}/%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	@rm -vf ${OBJS}
