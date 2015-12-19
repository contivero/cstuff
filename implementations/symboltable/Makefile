include config.mk

SRC = ../util.c test.c symtab.c
OBJ = util.o test.o symtab.o

all: options symtab

options:
	@echo symtab build options:
	@echo "CC       = ${CC}"
	@echo "CFLAGS   = ${CFLAGS}"

${OBJ}: config.mk

symtab: ${OBJ} .o
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

.o: ${SRC}
	@echo cc $<
	@${CC} -c ${CFLAGS} $<

clean:
	@echo cleaning
	@rm -f symtab ${OBJ}

.PHONY: all options clean
