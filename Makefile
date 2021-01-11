# ##############################################################################
# ARCH -- what architecture are we compiling for?
ARCH = riscv

# ##############################################################################
# Internal configuration.

# compiler flags
flags-debug    = -O2 -Wall -Werror -g -Wdeclaration-after-statement
flags-api      = -D_XOPEN_SOURCE=600 -D_GNU_SOURCE

# where to find header files
headers =  -Iinclude
includes = include
src = src

# combine options
CPPFLAGS = ${flags-api} -DARCH=${ARCH} ${headers}
CFLAGS   = ${flags-debug}
LDFLAGS  = ${flags-${ARCH}}

CC = g++
CROSS_COMPILE = riscv64-linux-gnu-

# incorporate cross-compiler (if any)
CC  := ${CROSS_COMPILE}${CC}

# ##############################################################################
# Targets
TARGETS = runt test1 runmini

.PHONY: ${TARGETS}
all: ${TARGETS}

runt: runt.o
	${CC} ${CPPFLAGS} $^ -o $@

run: main.o dsid_direct_lib.o
	${CC} ${CPPFLAGS} $^ -o $@

test1: test1.o
	${CC} ${CPPFLAGS} $^ -o $@

runmini: runmini.o
	${CC} ${CPPFLAGS} $^ -o $@

runmini.o: ${src}/runmini.c
	${CC} ${CPPFLAGS} -c $^

runt.o: ${src}/runt.c
	${CC} ${CPPFLAGS} -c $^

test1.o: ${src}/test1.c
	${CC} ${CPPFLAGS} -c $^

main.o: ${src}/main.c
	${CC} ${CPPFLAGS} -c $^

dsid_direct_lib.o: ${src}/dsid_direct_lib.c
	${CC} ${CPPFLAGS} -c $^

clean:
	rm -f ${TARGETS}
	rm -f *.o *.d *.a 
