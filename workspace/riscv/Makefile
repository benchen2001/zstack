REPO = /home/jinfeng/zstack/packages

LINK_SCRIPT = $(REPO)/board_riscv_spike/layout.lds 

include $(REPO)/lld_riscv/basic.list

OBJECTS += main.o

#--------------------------------------------------------------------------------------------------
CC = riscv32-unknown-elf-gcc
LD = riscv32-unknown-elf-ld
OBJCOPY = riscv32-unknown-elf-objcopy
OBJDUMP = riscv32-unknown-elf-objdump

CFLAGS  = -c -g -nostdinc -fno-builtin -Wall -I$(REPO)/include
LDFLAGS = -nostdlib -T $(LINK_SCRIPT)
#--------------------------------------------------------------------------------------------------

all: zstack.img

zstack.img: zstack.elf
	$(OBJCOPY) -O binary zstack.elf zstack.bin
	@dd if=/dev/zero of=zstack.img bs=512 count=48
	@dd if=zstack.bin of=zstack.img bs=512 count=48 conv=notrunc

zstack.elf: $(OBJECTS) $(LINK_SCRIPT)
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
	@qemu-system-riscv32 -monitor stdio zstack.img

install:
	cp zstack.img /mnt/c/Users/Z/
