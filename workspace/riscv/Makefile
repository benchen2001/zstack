REPO = /home/jinfeng/zstack/packages

include $(REPO)/lld_riscv/basic.list

OBJECTS += main.o

#--------------------------------------------------------------------------------------------------
CC = riscv32-unknown-elf-gcc
LD = riscv32-unknown-elf-ld
OBJCOPY = riscv32-unknown-elf-objcopy
OBJDUMP = riscv32-unknown-elf-objdump

CFLAGS  = -c -g -nostdinc -fno-builtin -Wall -I$(REPO)/include
LDFLAGS = -T $(REPO)/board_spike/layout.lds -nostdlib
#--------------------------------------------------------------------------------------------------

all: zstack.elf

zstack.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) -o $@ $<

%.d: %.c
	$(CC) -M -nostdinc -I$(REPO)/include $< > $@

%.d: %.S
	$(CC) -M -nostdinc -I$(REPO)/include $< > $@

-include $(OBJECTS:.o=.d)

clean:
	@rm -f zstack.* $(OBJECTS) $(OBJECTS:.o=.d)

run:
	@qemu-system-i386 -monitor stdio zstack.img

copy:
	cp zstack.img /mnt/c/Users/Z/
