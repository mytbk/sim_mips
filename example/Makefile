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

bin/libtest: libtest/libtest.o ../libs/libs.a
	$(LD) -o bin/libtest libtest/libtest.o ../libs/libs.a

matrix/matrix01.o: matrix/matrix.c
	$(CC) $(CFLAGS) -DMATRIX01 -c -o matrix/matrix01.o matrix/matrix.c
matrix/matrix02.o: matrix/matrix.c
	$(CC) $(CFLAGS) -DMATRIX02 -c -o matrix/matrix02.o matrix/matrix.c

bin/matrix01: matrix/matrix01.o ../libs/libs.a
	$(LD) -o bin/matrix01 matrix/matrix01.o ../libs/libs.a
bin/matrix02: matrix/matrix02.o ../libs/libs.a
	$(LD) -o bin/matrix02 matrix/matrix02.o ../libs/libs.a

gensort:
	cd quicksort &&	./gendata.sh | sort -n > sorted.txt
quicksort/qsort.o: gensort
bin/qsort: quicksort/qsort.o  ../libs/libs.a
	$(LD) -o bin/qsort quicksort/qsort.o ../libs/libs.a

bin/array: array/array.o ../libs/libs.a
	$(LD) -o bin/array array/array.o ../libs/libs.a

../libs/libs.a:
	make -C ../libs

.PHONY: clean
clean:
	find -name '*.o' -delete
	rm bin/*

