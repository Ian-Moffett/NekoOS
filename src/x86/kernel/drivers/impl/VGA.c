#include "../VGA.h"


void clearScreen(char** vga, unsigned char bg, unsigned char fg) {
    unsigned short attrib = (bg << 4) | (fg & 0x0F);

    *vga = (char*)0xB8000;

    for (int i = 0; i < 20000; ++i) {
        **vga = ' ';
        *vga += 1;
        **vga = attrib;
        *vga += 1;
    }

    *vga = (char*)0xB8000;
}


void kputs(const char* const STR, char** vga, unsigned char newlineDepth) {
    for (int i = 0; i < strlen(STR); ++i) {
        **vga = STR[i];
        *vga += 2;
    }

    for (int i = 0; i < newlineDepth; ++i) {
       for (int j = 0; j < 80 - strlen(STR); ++i) {
            **vga = ' ';
            *vga += 2;
       }
    }
}
