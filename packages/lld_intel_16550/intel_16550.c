#include <io.h>
#include <string.h>

static void init(int port)
{
    outb_p(0x80,port+3);    /* set DLAB of line control reg */              
    outb_p(0x30,port);      /* LS of divisor (48 -> 2400 bps */             
    outb_p(0x00,port+1);    /* MS of divisor */                             
    outb_p(0x03,port+3);    /* reset DLAB */                                
    outb_p(0x0b,port+4);    /* set DTR,RTS, OUT_2 */                        
    outb_p(0x0d,port+1);    /* enable all intrs but writes */               
}     

void serial_init(void)
{
    init(0x03F8);
}

void puts(const char *s)
{
    int i;

    int len = strlen(s);

    for (i=0; i<len; i++) {
        outb_p(s[i], 0x3F8);
    }
}

void putc(const char c)
{
    if ('\n' == c) {
        outb_p('\r', 0x3F8);
    }
    outb_p(c, 0x3F8);
}

