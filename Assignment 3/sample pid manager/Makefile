# CFLAGS=-Wall -Wextra -Wpedantic --debug
# CC=gcc-10
CFLAGS=-Weverything --debug -Wno-padded
CC=clang

LDLIBS=-lpthread

SRC=$(wildcard *.c)
OBJS=$(SRC:%.c=%.o)
PROGS=pids

all: $(PROGS)

pids: pidmanager.o

$(OBJS): $(SRC)

main: pidmanager.o

.PHONY: clean
clean:
	rm -f $(OBJS) $(PROGS)