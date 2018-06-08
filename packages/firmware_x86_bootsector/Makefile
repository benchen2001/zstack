CC = gcc
LD = ld

CFLAGS  = -c -m32 -g -nostdinc -fno-builtin -Wall
LDFLAGS = -Ttext=0x7c00 -e start --oformat binary -melf_i386 -nostdlib

all: bootsector.bin

bootsector.bin: bootsector.S
	$(CC) $(CFLAGS) $<
	$(LD) $(LDFLAGS) -o $@ bootsector.o

clean:
	@rm -f *.bin *.o

