# CFLAGS=-Wall -Wextra -Wpedantic --debug -lm
# CC=gcc
CFLAGS=-Weverything --debug -Wno-padded
CC=clang

SRC=$(wildcard *.c)
OBJS=$(SRC:%.c=%.o)
PROGS=q13-solution

all: $(PROGS)

$(OBJS): $(SRC)

%: %.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) $(PROGS)
