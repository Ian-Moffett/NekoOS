#ifndef IDT_H
#define IDT_H

#define TRAP_GATE_FLAGS 0x8F
#define INT_GATE_FLAGS 0x8E

#include "../drivers/IO.h"

typedef struct {
    unsigned short isr_address_low;
    unsigned short kernel_cs;
    unsigned char reserved;
    unsigned char attr;
    unsigned char isr_address_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) idtr_t;


typedef struct {
    unsigned int gs, fs, es, ds;     
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  
    unsigned int int_no, err_code;   
    unsigned int eip, cs, eflags, useresp, ss;  
} regs_t;

typedef struct {
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
    unsigned int sp;
    unsigned int ss;
} __attribute__((packed)) idt_frame_t;

void set_idt_desc(unsigned char entry, void* isr, unsigned char flags);
void init_idt();

#endif
