#include "../PIT.h"

void panic(const char* const PANIC_MESSAGE);


void init_timer(unsigned int frequency) {
    /*
    unsigned int divisor = 1193182 / frequency;
    outportb(0x43, 0x34);             // Command byte.
    outportb(0x40, divisor & 0xFF);   // Divisor low byte.
    outportb(0x40, divisor >> 8);     // Divisor high byte.
    irq_install_isr(0x0, _test);   
    */

    outportb(0x70, 0x8A);
	outportb(0x71, 0x20);
	
	outportb(0x70, 0x8B);
	char flags = inportb(0x71);
	outportb(0x70, 0x8B);
	outportb(0x71, flags | 0x40);
	
	//32768>>(5-1) = 2048 hz.  The fastest you can pick is a division rate of
	//3, which gets you a 8192Hz interrupt rate.
	int divisionRate = 8;
	outportb(0x70, 0x8A);
	flags = inportb(0x71);
	outportb(0x70, 0x8A);
	outportb(0x71, (flags & 0xF0) | divisionRate);
} 



void sleep(unsigned int _ticks) {
    extern unsigned int ticks;
    unsigned int maxTicks = ticks + _ticks;
    while (ticks < _ticks);
}
