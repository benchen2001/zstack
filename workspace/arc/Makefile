REPO = /home/jzhuan1x/github.com/jinfeng-zhuang/zstack/packages

include $(REPO)/lld_arc/basic.list

#--------------------------------------------------------------------------------------------------
PREFIX = arc-zephyr-elf

CC = $(PREFIX)-gcc
LD = $(PREFIX)-ld
OBJCOPY = $(PREFIX)-objcopy
OBJDUMP = $(PREFIX)-objdump

CFLAGS  = -c -g -nostdinc -fno-builtin -Wall -I$(REPO)/include -include config -std=c99
LDFLAGS = -T $(REPO)/board_jellyfish_em7d/layout.lds -nostdlib
#--------------------------------------------------------------------------------------------------

all: zstack.elf

zstack.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^
	$(OBJDUMP) -S $@ > zstack.dump
	$(OBJDUMP) -t $@ > zstack.symbol

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

