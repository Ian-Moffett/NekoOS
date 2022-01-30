#include "../IDT.h"


static idt_entry_t idt[256] = {0};
static idt_ptr_t idtr;


void set_idt_entry(unsigned char entry, void* isr, unsigned char flags) {
    idt_entry_t* descriptor = &idt[entry];
    descriptor->base_low = (unsigned int)isr & 0xFFFF;
    descriptor->sel = 0x08;
    descriptor->reserved = 0x0;
    descriptor->flags = flags;
    descriptor->base_high = ((unsigned int)isr >> 16) & 0xFFFF;
}


void idt_install() {
    idtr.limit = (unsigned short)sizeof(idt);
    idtr.base = (unsigned int)&idt;
    __asm__ __volatile__("lidt %0" : : "memory"(idtr));
}
