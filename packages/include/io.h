#ifndef IO_H
#define IO_H

#define inb(port) ({                                    \
    unsigned char _v;                                   \
    __asm__ volatile (                                  \
        "\tinb %%dx, %%al" : "=a" (_v) : "d" (port)     \
    );                                                  \
    _v;                                                 \
    })

#define outb(value, port)                               \
    __asm__ volatile (                                  \
        "\toutb %%al, %%dx" :: "a" (value), "d" (port)  \
    );

#define in(port) ({                                    \
    unsigned int _v;                                   \
    __asm__ volatile (                                  \
        "\tin %%dx, %%eax" : "=a" (_v) : "d" (port)     \
    );                                                  \
    _v;                                                 \
    })

#define out(value, port)                               \
    __asm__ volatile (                                  \
        "\tout %%eax, %%dx" :: "a" (value), "d" (port)  \
    );

#define outb_p(value,port)                              \
    __asm__ volatile (                                  \
        "outb %%al,%%dx\n"                              \
        "\tjmp 1f\n"                                    \
        "1:\tjmp 1f\n"                                  \
        "1:"::"a" (value),"d" (port)                    \
    )
                                                                                   
#define inb_p(port) ({                                  \
    unsigned char _v;                                   \
    __asm__ volatile (                                  \
        "inb %%dx,%%al\n"                               \
        "\tjmp 1f\n"                                    \
        "1:\tjmp 1f\n"                                  \
        "1:":"=a" (_v):"d" (port));                     \
    _v;                                                 \
    })

#define out_p(value,port)                              \
    __asm__ volatile (                                  \
        "out %%eax,%%dx\n"                              \
        "\tjmp 1f\n"                                    \
        "1:\tjmp 1f\n"                                  \
        "1:"::"a" (value),"d" (port)                    \
    )
                                                                                   
#define in_p(port) ({                                  \
    unsigned int _v;                                   \
    __asm__ volatile (                                  \
        "in %%dx,%%eax\n"                               \
        "\tjmp 1f\n"                                    \
        "1:\tjmp 1f\n"                                  \
        "1:":"=a" (_v):"d" (port));                     \
    _v;                                                 \
    })

#endif
