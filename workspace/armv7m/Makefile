REPO = /home/jinfeng/zstack/packages

include $(REPO)/lld_armv7m/basic.list

OBJECTS += main.o

#--------------------------------------------------------------------------------------------------
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

CFLAGS  = -c -mthumb -march=armv7-m -g -nostdinc -fno-builtin -Wall -I$(REPO)/include
LDFLAGS = -T $(REPO)/board_lm3s811evb/layout.lds -nostdlib
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
