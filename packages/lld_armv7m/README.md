# README

## Overview

See APCS for more.

An ARMv7-M implementation can optiaonally support coprocessor, possible 
coprocessors number from 0 to 15, and are called CP0-CP15. ARM reserves CP8 to
CP15, and CP0 to CP7 are IMPLEMENTATION DEFINED, subject to the constraints of
the coprocessor instructions.

So, coprocessor support are moved to cpu package.

## Reqirement

* init symbol

## BUGs

* qemu crash by exception

    qemu: fatal: Lockup: can't escalate 3 to HardFault (current priority -1)
    ...

  Refer to https://patchwork.kernel.org/patch/9553205/, which is located in
    armv7m_nvic_set_pending
  Which means I don't inited NVIC before trigger exceptions.

  This is because of vector handlers' addresses in vector table is not thumb
  encoded, we should put the .thumb_func before all the function.

## CODE RULEs

* ISB is used to clear pipeline, some instructions will effect the pipeline.
* DSB is used to sync data in cache, some instructions will effect the cache.
* Headers for assembler only need #define INSTRUCTIONs, so we should extract
  enum,... to #define, and include function declarations with __ASSEMBLER__.
* APSR_t is defined in ARMV7M package, it is some different in Cortex-M4, so
  we should undef this type and redef it. Why not control with macro, it will
  makes code flexible, which violate the more important rule.

