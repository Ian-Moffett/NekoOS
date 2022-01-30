#ifndef VGA_H
#define VGA_H

#include "../util/strings.h"

void clearScreen(char** vga, unsigned char bg, unsigned char fg);
void kputs(const char* const STR, char** vga, unsigned char newlineDepth);

#endif
