#include "../IO.h"

unsigned char inportb(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
 }


void outportb(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : :"a" (data), "d" (port));
}
