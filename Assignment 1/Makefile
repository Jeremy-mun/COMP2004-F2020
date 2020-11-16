# CFLAGS=-Wall -Wextra -Wpedantic --debug -lm
# CC=gcc
CFLAGS=-Weverything --debug
CC=clang

SRC=$(wildcard *.c) ../log.c/src/log.c
OBJS=$(SRC:%.c=%.o)
PROGS=q1 q2 q3

all: $(PROGS)

$(OBJS): $(SRC)

q2: q2.o ../log.c/src/log.o

q3: q3.o ../log.c/src/log.o pointnode.o

%: %.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) $(PROGS)