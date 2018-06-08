    .global start

    .code16

start:

clear_screen_in_text_mode:
    mov $0x0003, %ax
    int $0x10

load_bootloader_start_sector:
    cld

    xor %ax, %ax
    mov %ax, %es
    mov $0x1000, %bx

    movb $0x80, %dl      /* driver 0 */
    movb $0x00, %dh      /* head 0 */
    movb $0x00, %ch      /* track 0 */
    movb $0x02, %cl      /* sector 2 */
    movb $48, %al        /* sectors to read: 0x1000~0x7000 */

    mov $0x02, %ah      /* function: read sector */
    int $0x13           /* BIOS Direct Disk Service */

    ljmp $0x0, $0x1000

.fill 510-(.-start), 1, 0

bootsector_flag:
    .word 0xaa55

