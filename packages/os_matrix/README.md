# Matrix OS

The OS will be divided into two parts: the master & slave.

The slave core will serve for ONLY one task, or in idle mode.

## Guide

1. software is not set of skills, it support channels for data and manage them.
2. Multi RAM with independent channel are supported, to avoid memory wait, maybe we need a RAM matrix.
3. like json, data should be matrix format, as it can be speed up with coprocessor.

## Slave

The slave is responsible to do ONLY one job.

When the slave is idle, it can receive a task from other slave or master, after change its role, it will receive data and process it.

## Master

The master is responsible to collect and summary all the cores' info, to keep system balance, to improve the system performance.

Multi-master are supported for load and store tasks/data from everywhre.

## Questions

1. How to make a function travel around all the cores?

   Consider to use a simple MMU, this maybe a requirement for SoC design.

2. Where can I get this hardware?

   Graphic Card or FPGA?

