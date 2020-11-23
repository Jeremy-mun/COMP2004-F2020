# CFLAGS=-Wall -Wextra -Wpedantic --debug -lm
# CC=gcc
CFLAGS=-Weverything --debug
CC=clang

SRC=$(wildcard *.c) ../log.c/src/log.c
OBJS=$(SRC:%.c=%.o)
PROGS=q1-loops q2-filecopy q3-path

all: $(PROGS)

$(OBJS): $(SRC)

q2-filecopy: ../log.c/src/log.o

q3-path: ../log.c/src/log.o pointnode.o

%: %.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) $(PROGS)