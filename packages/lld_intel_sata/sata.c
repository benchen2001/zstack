
int intel_disk_controller_is_ready(void)
{
    return (inb(HD_STATUS) & 0xC0 == 0x40);
}

