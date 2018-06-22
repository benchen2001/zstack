# ZStack

## Feature

* support armv7m, riscv simulate

## Design

* package export symbols, with different set, distinguish by postfix.
* release version: [global design].[package count].[commit count]

## Quick Start

enter workspace/armv7m, workspace/riscv to see more information.

## Build System

## Software Architecture

### LLD Layer

* A NO-STATUS layer, no timeout for polling access currently, IRQ imported complex throws to upper layer
* A EMBEDED layer, Functions are static defined for embed into high-level drivers
* Functions' first parameter must be the IP's base address
* Registers are read write by the BIT operations, or REG operations while access discrete bits simultaniously
* Registers are organized into structure, it is a more readable address expression then MACRO
* DMA inside or outside is a question
* POWER management is upper layer's resposibility
* Return error directly to upper layer
* Contains standard error code.
* BIT operation ONLY support 64bit mode, or distinguish them with suffix/header file is a question

The layer include APIs and low level driver for different IPs, the purpose is for developping drivers
easy! For example, to develop a CMSIS or QMSI standard driver, you don't need to take all the details of
registers, just do a wrapper.

There are many test cases for any IPs, the cases are real low level, however, we can't get them.

Open source IPs projects should be supported, like RISC-V.

There exist 3 method to deal with error:

* return error to upper layer, upper layer MUST check return value if there is a return value
* adjust to nearby correct value, this import complex logic and no change for upper layer for error check
* assert internal, however, assert effect in debug mode, removed in released mode

We currectly adopt the first method.
