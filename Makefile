CFLAGS=-g -Wall
OBJS=main.o mmu.o mips.o

all: main

main: $(OBJS)

.PHONY: clean
clean:
	rm main $(OBJS)
