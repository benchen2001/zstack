#include <armv7-m/exception.h>
#include <init.h>

void exception_pre_process(int type)
{
    if (CORE_EXCEPTION_RESET == type) {
        arch_init();
        while (1);
    }
    else {
        while (1);
    }
}

