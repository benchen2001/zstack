/*
 * Attention
 *   Barrier is implemented by coprocessor in ARMv6 and ealier version.
 *
 * Reference
 *  https://stackoverflow.com/questions/14950614/working-of-asm-volatile-memory
 */

#ifndef ARM_BARRIER_H
#define ARM_BARRIER_H

#define isb() __asm__ volatile ("isb" : : : "memory")
#define dsb() __asm__ volatile ("dsb" : : : "memory")
#define dmb() __asm__ volatile ("dmb" : : : "memory")

#endif

