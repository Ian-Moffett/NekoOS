#ifndef IDT_H
#define IDT_H

#define INT_GATE_FLAGS 0x8E
#define TRAP_GATE_FLAGS 0x8F


typedef struct {
    unsigned short base_low;
    unsigned short sel;
    unsigned char reserved;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed)) idt_entry_t;


typedef struct {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) idt_ptr_t;


typedef struct {
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
    unsigned int sp;
    unsigned int ss;
} __attribute__((packed)) int_frame_t;


void set_idt_entry(unsigned char entry, void* isr, unsigned char flags);
void idt_install();

#endif
