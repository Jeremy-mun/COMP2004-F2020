# CFLAGS=-Wall -Wextra -Wpedantic --debug
# CC=gcc-10
CFLAGS=-Weverything --debug -Wno-padded
CC=clang

SRC=$(wildcard *.c)
OBJS=$(SRC:%.c=%.o)
PROGS=q3-pidmanager

all: $(PROGS)

$(OBJS): $(SRC)

%: %.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) $(PROGS)