# CFLAGS=-Wall -Wextra -Wpedantic --debug -lm
# CC=gcc
CFLAGS=-Weverything --debug
CC=clang

SRC=$(wildcard *.c)
OBJS=$(SRC:%.c=%.o)
PROGS=helloworld
PROGS+=1.2Celsius-to-Farhenheit 1.3Celsius-to-Farhenheit-FOR 1.6arrays
PROGS+=4.1grep
PROGS+=5.1pointers 5.2swap 5.6pointerarrays
PROGS+=6.2struct-function 6.6table-lookup 6.point-list
PROGS+=7.1standard-io 7.5file-copy 7.5file-copy-errors

all: $(PROGS)

$(OBJS): $(SRC)

%: %.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) $(PROGS)