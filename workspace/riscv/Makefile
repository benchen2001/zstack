LINK_SCRIPT = $(REPO)/board_riscv_spike/layout.lds 

include $(REPO)/lld_riscv/basic.list
include $(REPO)/libmisc/basic.list
include $(REPO)/libc/basic.list
include $(REPO)/os_light/basic.list
include $(REPO)/app_simple_task/basic.list

#--------------------------------------------------------------------------------------------------
CC = riscv64-unknown-elf-gcc
LD = riscv64-unknown-elf-ld
OBJCOPY = riscv64-unknown-elf-objcopy
OBJDUMP = riscv64-unknown-elf-objdump

WARNING = 			\
	-Wall 			\
	-Wextra			\
	-Wshadow 		\
	-Wpointer-arith		\
	-Wbad-function-cast	\
	-Wcast-align		\
	-Wsign-compare		\
	-Waggregate-return 	\
	-Wstrict-prototypes 	\
	-Wmissing-prototypes 	\
	-Wmissing-declarations	\
	-Wunused

CFLAGS  =			\
	-c -g			\
	-nostdinc 		\
	-fno-builtin 		\
	$(WARNING) 		\
	-I$(REPO)/include 	\
	-fomit-frame-pointer 	\
	-fno-strict-aliasing 	\
	-mcmodel=medany 	\
	-D__gracefulExit	\
	-include config

LDFLAGS = -nostdlib -T $(LINK_SCRIPT)
#--------------------------------------------------------------------------------------------------

all: zstack.img

zstack.img: zstack.elf
	$(OBJCOPY) -O binary zstack.elf zstack.bin
	@dd if=/dev/zero of=zstack.img bs=512 count=48
	@dd if=zstack.bin of=zstack.img bs=512 count=48 conv=notrunc

zstack.elf: $(OBJECTS) $(LINK_SCRIPT)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)
	$(OBJDUMP) -S zstack.elf > zstack.dump
	$(OBJDUMP) -t zstack.elf > zstack.symbol

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
	spike zstack.elf

start_spike:
	spike --rbb-port=9824 zstack.elf

start_openocd:
	openocd -f spike.cfg

start_gdb:
	riscv64-unknown-elf-gdb zstack.elf
