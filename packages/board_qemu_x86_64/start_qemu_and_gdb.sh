#!/bin/sh

#qemu-system-arm -machine lm3s811evb -kernel image -S -gdb tcp::9000
qemu-system-i386 zstack -S -gdb tcp::9000
