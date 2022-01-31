#include "../exceptions.h"

void panic(const char* const PANIC_MESSAGE);


void div_0_ex(int_frame_t*) {
    panic("DIVIDE ERROR (0x0).");
}

void overflow_ex(int_frame_t*) {
    panic("OVERFLOW (0x4).");
}

void bre_ex(int_frame_t*) {
    panic("BOUND RANGE EXCEEDED (0x5).");
}

void invld_opcode_ex(int_frame_t*) {
    panic("INVALID OPCODE (0x6).");
}

void dev_na_ex(int_frame_t*) {
    panic("DEVICE NOT AVAILABLE (0x7).");
}

void double_fault_ex(int_frame_t*) {
    panic("DOUBLE FAULT (0x8).");
}

void cso_ex(int_frame_t*) {
    panic("COPROSSESOR SEGMENT OVERRUN (0x9).");
}

void invld_tss_ex(int_frame_t*) {
    panic("INVALID TSS (0xA).");
}

void seg_np_ex(int_frame_t*) {
    panic("SEGMENT NOT PRESENT (0xB).");
}

void ss_fault_ex(int_frame_t*) {
    panic("STACK SEGMENT FAULT (0xC).");
}

void gp_fault_ex(int_frame_t*) {
    panic("GENERAL PROTECTION FAULT (0xD).");
}

void page_fault_ex(int_frame_t* regs) {
    char* vga = (char*)0xB8000;
    outportb(0x3D4, 0x0A);
    outportb(0x3D5, 0x20);
    clearScreen(&vga, 0x4, 0xFE);
    kputs("***KERNEL PANIC***", &vga, 1);
    kputs("PAGE FAULT (0xE).", &vga, 2);
    kputs("<=== TECHNICAL INFORMATION ===>", &vga, 2);
    kputs_hex(regs->eflags & 0x1, &vga, 1);
    kputs_hex(regs->eflags & 0x2, &vga, 1);
    kputs_hex(regs->eflags & 0x4, &vga, 1);
    kputs_hex(regs->eflags & 0x8, &vga, 1);
    kputs_hex(regs->eflags & 0x10, &vga, 1);
    __asm__ __volatile__("cli; hlt");
}

void float_ex(int_frame_t*) {
    panic("FLOATING POINT EXCEPTION (0xF).");
}
