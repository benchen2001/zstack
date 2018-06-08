#if 0
void callstack_dump(void)
{
    unsigned int ebp;
    unsigned int *pEBP;
    unsigned int callstack[STACK_DEPTH_MAX];
    int depth = 0;

    asm ("movl %%ebp, %0" : "=r" (ebp));

    pEBP = (unsigned int *)ebp;

    for (int i=0; (i<STACK_DEPTH_MAX) && (NULL != pEBP); i++) {
        callstack[i] = (unsigned int)*(pEBP+1);
        pEBP = (unsigned int *)*pEBP;
        depth++;
    }

    printk("Callstack:\n");
    for (int i=0; i<depth; i++) {
        printk("\t%08X\n", callstack[i]);
    }
}
#endif
