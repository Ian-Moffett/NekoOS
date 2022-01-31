#include "drivers/VGA.h"
#include "drivers/PIT.h"
#include "drivers/IO.h"
#include "interrupts/IDT.h"
#include "interrupts/exceptions.h"

#define HALT __asm__ __volatile__("hlt")

char* vga_main = (char*)0xB8000;
int cursor_y = 0;
int cursor_x = 0;

void panic(const char* const PANIC_MESSAGE) {
    clearScreen(&vga_main, 0x4, 0xFE);
    kputs(PANIC_MESSAGE, &vga_main, 1);
    __asm__ __volatile__("cli; hlt");
}


#ifdef OUTPUT_TICKS
void irq0_handler() {
    extern unsigned int ticks;
    if (ticks >= 5000) {
        ticks = 0;
    }

    kputs("TICKS: ", &vga_main, 1);
    kputs_dec(ticks, &vga_main, 1);
    ++cursor_y;
    
    if (cursor_y > 10) {
        cursor_y = 0;
        vga_main = (char*)0xB8000;
    }

    update_cursor(cursor_x, cursor_y);
}
#else 
void irq0_handler() {}
#endif

void _irq0_isr();


static void IRQ_clear_mask(unsigned char IRQline) {
    unsigned short port;
    unsigned char value;
 
    if(IRQline < 8) {
        port = 0x21;
    } else {
        port = 0xA1;
        IRQline -= 8;
    }
    value = inportb(port) & ~(1 << IRQline);
    outportb(port, value);        
}

int _start() {
    // Remap PIC.
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);

    idt_install();
     // Setup exceptions.
    set_idt_entry(0x0, div_0_ex, TRAP_GATE_FLAGS);
    set_idt_entry(0x4, overflow_ex, TRAP_GATE_FLAGS);
    set_idt_entry(0x5, bre_ex, TRAP_GATE_FLAGS);
    set_idt_entry(0x6, invld_opcode_ex, TRAP_GATE_FLAGS);
    set_idt_entry(0x7, dev_na_ex, TRAP_GATE_FLAGS);
    set_idt_entry(0x8, double_fault_ex, TRAP_GATE_FLAGS);
    set_idt_entry(0x9, cso_ex, TRAP_GATE_FLAGS);
    set_idt_entry(0xA, invld_tss_ex, TRAP_GATE_FLAGS);
    set_idt_entry(0xB, seg_np_ex, TRAP_GATE_FLAGS);
    set_idt_entry(0xC, ss_fault_ex, TRAP_GATE_FLAGS);
    set_idt_entry(0xD, gp_fault_ex, TRAP_GATE_FLAGS);
    set_idt_entry(0xF, float_ex, TRAP_GATE_FLAGS);

    timer_set_freq(5);

    set_idt_entry(0x20, _irq0_isr, INT_GATE_FLAGS);
    IRQ_clear_mask(0x0);
    __asm__ __volatile__("sti");

    clearScreen(&vga_main, 0x1, 0xE);
    
    #ifndef OUTPUT_TICKS
    for (int i = 3; i > -1; --i) {
        kputs("Hello Master!~ This text goes away in: ", &vga_main, 0); 
        kputs_dec(i, &vga_main, 0);
        sleep(30);
        clearScreen(&vga_main, 0x1, 0xE);
    }

    clearScreen(&vga_main, 0x1, 0xE); 
    #endif

    return 0;
}
