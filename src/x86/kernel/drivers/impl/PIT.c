#include "../PIT.h"


void init_timer(unsigned int frequency) {
    unsigned int divisor = 1193180 / frequency;
    outportb(PIT_CMD, CMD_BINARY | CMD_MODE3 | CMD_RW_BOTH | CMD_COUNTER0);
    outportb(PIT_COUNTER0, divisor);
    outportb(PIT_COUNTER0, divisor >> 8);
}
