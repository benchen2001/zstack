#include <io.h>
#include <string.h>
#include <stdio.h>
#include <printk.h>
#include <stdint.h>

void os_start(void)
{
    first_task_setup();

    while(1);
}

