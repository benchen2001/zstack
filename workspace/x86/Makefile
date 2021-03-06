include $(REPO)/lld_x86/baremetal.list
include $(REPO)/lld_intel_8259a/basic.list
include $(REPO)/lld_intel_16550/basic.list
include $(REPO)/lld_intel_82540em/basic.list
include $(REPO)/lld_intel_pci/basic.list
include $(REPO)/libmisc/basic.list
include $(REPO)/libc/basic.list
include $(REPO)/app_baremetal/basic.list

#--------------------------------------------------------------------------------------------------
CC = gcc
LD = ld
OBJCOPY = objcopy
OBJDUMP = objdump

CFLAGS  = -c -m32 -g -nostdinc -fno-builtin -Wall -I$(REPO)/include -include config
LDFLAGS = -T $(REPO)/board_qemu_x86_64/layout.lds -nostdlib -melf_i386
#--------------------------------------------------------------------------------------------------

all: zstack.img

zstack.img: zstack.elf bootsector.bin
	$(OBJCOPY) -O binary zstack.elf zstack.bin
	@dd if=/dev/zero of=zstack.img bs=512 count=49
	@dd if=bootsector.bin of=zstack.img bs=512 count=1 conv=notrunc
	@dd if=zstack.bin of=zstack.img seek=1 bs=512 count=48 conv=notrunc

zstack.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^
	$(OBJDUMP) -S $@ > zstack.dump

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
	@qemu-system-x86_64 -nographic -monitor null -serial stdio zstack.img

start_qemu:
	@qemu-system-x86_64 -monitor stdio zstack.img -s -S
