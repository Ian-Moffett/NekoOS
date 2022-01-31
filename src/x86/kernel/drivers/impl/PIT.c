#include "../PIT.h"

unsigned int ticks = 0;

void timer_set_freq(unsigned int freq) {
    unsigned int divisor = 1193182 / freq;
    outportb(0x43, 0x36);             // Command byte.
    outportb(0x40, divisor & 0xFF);   // Divisor low byte.
    outportb(0x40, divisor >> 8);     // Divisor high byte.
    outportb(0x21, 0xFF);
}


void sleep(unsigned int _ticks) {
    unsigned ticks2Wait = ticks + _ticks;
    while (ticks < ticks2Wait);
}
