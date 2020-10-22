# CFLAGS=-Wall -Wextra -Wpedantic --debug -lm
# CC=gcc
CFLAGS=-Weverything --debug
CC=clang

SRC=$(wildcard *.c) ../log.c/src/log.c
OBJS=$(SRC:%.c=%.o)
PROGS=fork
PROGS+=shm-producer shm-consumer shm-fork
PROGS+=unixpipes

all: $(PROGS)

$(OBJS): $(SRC)

shm-fork: shm-fork.o ../log.c/src/log.o

%: %.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) $(PROGS)