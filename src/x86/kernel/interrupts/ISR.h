#ifndef ISR_H
#define ISR_H

#include "IDT.h"
#include "../drivers/IO.h"

void _irq0();
void _irq1();
void _irq2();
void _irq3();
void _irq4();
void _irq5();
void _irq6();
void _irq7();
void _irq8();
void _irq9();
void _irq10();
void _irq11();
void _irq12();
void _irq13();
void _irq14();
void _irq15();

void irq_install_isr(int irq, void (*isr)(regs_t*));
void irq_uninstall_isr(int irq);
void irq_install();

#endif
