# CFLAGS=-Wall -Wextra -Wpedantic --debug
# CC=gcc-10
CFLAGS=-Weverything --debug
CC=clang

SRC=$(wildcard *.c)
OBJS=$(SRC:%.c=%.o)
PROGS=q2-solution q3

all: $(PROGS)

q3: pidmanager.o q3.o

$(OBJS): $(SRC)

%: %.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) $(PROGS)