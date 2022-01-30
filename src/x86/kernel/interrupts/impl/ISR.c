#include "../ISR.h"


static void* irq_routines[16] = {(void*)0x0};

void irq_uninstall_isr(int irq) {
    irq_routines[irq] = (void*)0x0;
}



void irq_install_isr(int irq, void (*isr)(regs_t*)) {
    irq_routines[irq] = isr;
}


void irq_install() {
    set_idt_desc(32, _irq0, INT_GATE_FLAGS);
    set_idt_desc(33, _irq1, INT_GATE_FLAGS);
    set_idt_desc(34, _irq2, INT_GATE_FLAGS);
    set_idt_desc(35, _irq3, INT_GATE_FLAGS);
    set_idt_desc(36, _irq4, INT_GATE_FLAGS);
    set_idt_desc(37, _irq5, INT_GATE_FLAGS);
    set_idt_desc(38, _irq6, INT_GATE_FLAGS);
    set_idt_desc(39, _irq7, INT_GATE_FLAGS);
    set_idt_desc(40, _irq8, INT_GATE_FLAGS);
    set_idt_desc(41, _irq9, INT_GATE_FLAGS);
    set_idt_desc(42, _irq10, INT_GATE_FLAGS);
    set_idt_desc(43, _irq11, INT_GATE_FLAGS);
    set_idt_desc(44, _irq12, INT_GATE_FLAGS);
    set_idt_desc(45, _irq13, INT_GATE_FLAGS);
    set_idt_desc(46, _irq14, INT_GATE_FLAGS);
    set_idt_desc(47, _irq15, INT_GATE_FLAGS);
}


void _irq_handler(regs_t* r) {
    void (*isr)(regs_t*);
    isr = irq_routines[r->int_no - 32];

    if (isr) {
        isr(r);
    }

    if (r->int_no >= 40) {
        outportb(0xA0, 0x20);
    }

    outportb(0x20, 0x20);
}
