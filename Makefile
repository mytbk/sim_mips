CFLAGS=-g -Wall
OBJS=main.o mmu.o mips.o mipsinst.o syscall.o debugger.o

all: main

main: $(OBJS)

.PHONY: clean
clean:
	rm -f main $(OBJS)
	make -C libs clean
	make -C example clean

