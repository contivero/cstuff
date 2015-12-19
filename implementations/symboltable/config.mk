# Uncomment to statically link with musl
#CC      = musl-gcc
#LDFLAGS = -static -s
#CFLAGS  = -std=c99 -pedantic -Ofast \

CC      = gcc
LDFLAGS = -s
#CFLAGS  = -std=c99 -pedantic -Ofast

CFLAGS = -std=c99 -pedantic -Wall -Wextra \
	-Wno-missing-braces -Wno-missing-field-initializers -Wformat=2 \
	-Wswitch-default -Wswitch-enum -Wcast-align -Wpointer-arith \
	-Wbad-function-cast -Wstrict-overflow=5 -Wstrict-prototypes -Winline \
	-Wundef -Wnested-externs -Wcast-qual -Wshadow -Wunreachable-code \
	-Wlogical-op -Wfloat-equal -Wstrict-aliasing=2 -Wredundant-decls \
	-Wold-style-definition -Werror \
	-O0 \
 	# -Wunused-macros \

