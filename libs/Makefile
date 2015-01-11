PREFIX=mipsel-unknown-linux-gnu-
CC=$(PREFIX)gcc
LD=$(PREFIX)ld
AS=$(PREFIX)as
AR=$(PREFIX)ar
CFLAGS+=-O2
COMMONLIBS=entry.o libc.o libs.o malloc.o string.o printf.o file.o

libs.a: $(COMMONLIBS)
	$(AR) r libs.a $(COMMONLIBS)

entry.o: entry.S
	$(AS) -o entry.o entry.S

libs.o: libs.S
	$(AS) -o libs.o libs.S

.PHONY: clean
clean:
	rm -f $(COMMONLIBS) libs.a
