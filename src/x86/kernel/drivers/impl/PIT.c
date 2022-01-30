#include "../PIT.h"

void panic(const char* const PANIC_MESSAGE);

static void _test() {
    panic("TEST");
}


void init_timer(unsigned int frequency) { 
    unsigned int divisor = 1193182 / frequency;
    outportb(0x43, 0x34);             // Command byte.
    outportb(0x40, divisor & 0xFF);   // Divisor low byte.
    outportb(0x40, divisor >> 8);     // Divisor high byte.
    irq_install_isr(0x0, _test);   
} 
