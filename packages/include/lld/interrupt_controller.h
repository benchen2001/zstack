#ifndef LLD_INTERRUPT_CONTROLLER_H
#define LLD_INTERRUPT_CONTROLLER_H

extern void interrupt_controller_init (void);
extern void interrupt_controller_enable (int irq);
extern void interrupt_controller_ack (void);

#endif
