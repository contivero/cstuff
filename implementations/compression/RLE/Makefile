include config.mk

SRC = run-length.c
OBJ = ${SRC:.c=.o}

all: options run-length

options:
	@echo run-length build options:
	@echo "CC       = ${CC}"
	@echo "CFLAGS   = ${CFLAGS}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.mk

run-length: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f run-length ${OBJ}

.PHONY: options clean run-length
