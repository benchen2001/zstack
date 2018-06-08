
/*
 * ARMv7-M Registers (see APCS for more information):
 *      R0-R12
 *      R13  : SP, stack top
 *      R14  : LR, next instruction
 *      R15  : PC, current instruction
 *      CPSR
 *      SPSR
 *
 * Before call context_switch, kernel has already sync the TCB.
 *
 * We need put all the registers to stack and then record the stack top to 
 * current TCB's first word.
 * Then get the next TCB's first word and resume all the registers.
 * Some registers need to help up do these job, so we should push them first,
 * it seems like we defined some variables.
 *
 * The stack for context switch like this:
 *      R0  - first
 *      R1  - first
 *      R2
 *      R3
 *      R4
 *      ...
 *      R12
 *      R14 - LR, next instruction for PC
 *
 * Note:
 *      CPSR and SPSR are synced automatically. 
 *      PC needn't to store as it will be resume from LR value.
 *      R13 needn't to push to stack, as it will be stored to TCB's first word.
 *
 * Question:
 *      Should I use ISB/DSB internal ?
 */
void context_switch(void *current, void *next)
{
    push {r0, r1}

    mov r0, sp
    stmdb r0!, {r2-r12, r14}

    ldr r1, [current, #0]
    str r0, [current, #0]

    ldr r0, [next, #0]

    ldmia.w r0!, [r2-r12, r14]
    mov sp, r0

    pop {r0, r1}
    
    bx lr // load pc
}

