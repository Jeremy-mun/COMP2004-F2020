CFLAGS=-Wall -Wextra -Wpedantic
CC=gcc

SRC=$(wildcard *.c)
OBJS=$(SRC:%.c=%.o)
PROGS=helloworld 1.2Celsius-to-Farhenheit 1.3Celsius-to-Farhenheit-FOR 1.6arrays


all: $(PROGS)

$(OBJS): $(SRC)

%: %.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) $(PROGS)