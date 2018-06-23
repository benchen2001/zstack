REPO = /home/jinfeng/zstack/packages

include $(REPO)/lld_armv7m/basic.list
include $(REPO)/lld_arm_nvic/basic.list
include $(REPO)/lld_ti_uart/basic.list
include $(REPO)/libmisc/basic.list
include $(REPO)/libc/basic.list
include $(REPO)/os_light/basic.list
include $(REPO)/app_simple_task/basic.list

#--------------------------------------------------------------------------------------------------
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

CFLAGS  = -c -mthumb -mcpu=cortex-m3 -g -nostdinc -fno-builtin -Wall -I$(REPO)/include -include config -std=c99
LDFLAGS = -T $(REPO)/board_lm3s811evb/layout.lds -nostdlib
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

run:
	@qemu-system-arm -machine lm3s811evb -kernel zstack.elf

start_qemu:
	@qemu-system-arm -machine lm3s811evb -kernel zstack.elf -s -S

start_gdb:
	@gdb-multiarch zstack.elf

