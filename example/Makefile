COMPILE_PREFIX=mipsel-unknown-linux-gnu-
CC=$(COMPILE_PREFIX)gcc
LD=$(COMPILE_PREFIX)ld
AS=$(COMPILE_PREFIX)as
CFLAGS += -I../libs

DHRY2_OBJS=dhrystone2/dhry_1.o dhrystone2/dhry_2.o dhrystone2/cpuidc.o

bin/hello: hello/hello.o ../libs/libs.a
	$(LD) hello/hello.o ../libs/libs.a -o bin/hello

bin/dhrystone2: $(DHRY2_OBJS) ../libs/libs.a
	$(LD) -o bin/dhrystone2 $(DHRY2_OBJS) ../libs/libs.a

hello.o: hello/hello.c
	$(CC) -c -o hello.o hello/hello.c

../libs/libs.a:
	make -C ../libs
