CFLAGS=-g -Wall
OBJS=main.o mmu.o mips.o mipsinst.o syscall.o

all: main

main: $(OBJS)

.PHONY: clean
clean:
	rm main $(OBJS)
