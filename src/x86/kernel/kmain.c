#include "drivers/VGA.h"
#include "drivers/PIT.h"
#include "interrupts/IDT.h"

char* vga_main = (char*)0xB8000;

void panic(const char* const PANIC_MESSAGE) {
    outportb(0x3D4, 0x0A);
    outportb(0x3D5, 0x20);
    clearScreen(&vga_main, 0x4, 0xF);
    kputs("*** KERNEL PANIC ***", &vga_main, 2);
    kputs(PANIC_MESSAGE, &vga_main, 0);
    __asm__ __volatile__("cli; hlt");
}


static void _test() {
    panic("FUCK!");
}


void init_PIT();

int _start() {
    init_idt();

    set_idt_desc(0x32, _test, TRAP_GATE_FLAGS);

    clearScreen(&vga_main, 0x1, 0xE);
    kputs("Hello UwU", &vga_main, 2); 
    return 0;
}
