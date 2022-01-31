#include "../VGA.h"

void __stack_chk_fail() {}


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


void kputs(const char* string, char** vga, unsigned short nlDepth) {
    const unsigned short VGA_WIDTH = 80;

    for (int i = 0; i < strlen(string); ++i) {
        **vga = string[i];
        *vga += 2;
    }

    if (nlDepth > 0) {
        for (int i = 0; i < VGA_WIDTH - strlen(string); ++i) {
            **vga = ' ';
            *vga += 2;
        }

        if (nlDepth > 1) {
            for (int i = 0; i < nlDepth - 1; ++i) {
                for (int j = 0; j < VGA_WIDTH; ++j) {
                    **vga = ' ';
                    *vga += 2;
                }
            }
        }
    }
}


void kputs_dec(int number, char** vga, unsigned short nlDepth) {
    unsigned char dec_string[80];
    unsigned char i = 0, j, temp;
    unsigned char negative = 0;       // Is number negative?

    if (number == 0) dec_string[i++] = '0'; // If passed in 0, print a 0
    else if (number < 0)  {
        negative = 1;       // Number is negative
        number = -number;   // Easier to work with positive values
    }

    while (number > 0) {
        dec_string[i] = (number % 10) + '0';    // Store next digit as ascii
        number /= 10;                           // Remove last digit
        i++;
    }

    if (negative) dec_string[i++] = '-';    // Add negative sign to front

    dec_string[i] = '\0';   // Null terminate

    // Number stored backwards in dec_string, reverse the string by swapping each end
    //   until they meet in the middle
    i--;    // Skip the null byte
    for (j = 0; j < i; j++, i--) {
        temp          = dec_string[j];
        dec_string[j] = dec_string[i];
        dec_string[i] = temp;
    }

    // Print out result
    kputs(dec_string, vga, nlDepth);
}


void update_cursor(int x, int y) {
	unsigned short pos = y * 80 + x;

	outportb(0x3D4, 0x0F);
	outportb(0x3D5, (unsigned char)(pos & 0xFF));
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}


static unsigned long _iterateDec(unsigned short digit) {
    unsigned long i = 1;
    while (digit--) {
        i *= 10;
    }

    return i;
}


void kputs_hex(int hex_num, char** vga, unsigned short nlDepth) {
    unsigned char hex_string[80];
    unsigned char *ascii_numbers = "0123456789ABCDEF";
    unsigned char nibble;
    unsigned char i = 0, j, temp;
    unsigned char pad = 0;
    
    // If passed in 0, print a 0
    if (hex_num == 0) {
        strncpy(hex_string, "0\0", 2);
        i = 1;
    }

    if (hex_num < 0x10) pad = 1;    // If one digit, will pad out to 2 later

    while (hex_num > 0) {
        // Convert hex values to ascii string
        nibble = (unsigned char)hex_num & 0x0F;  // Get lowest 4 bits
        nibble = ascii_numbers[nibble];    // Hex to ascii 
        hex_string[i] = nibble;             // Move ascii char into string
        hex_num >>= 4;                     // Shift right by 4 for next nibble
        i++;
    }
        
    if (pad) hex_string[i++] = '0';  // Pad out string with extra 0    

    // Add initial "0x" to front of hex string
    hex_string[i++] = 'x';
    hex_string[i++] = '0';
    hex_string[i] = '\0';   // Null terminate string

    // Number is stored backwards in hex_string, reverse the string by swapping ends
    //   until they meet in the middle
    i--;    // Skip null byte
    for (j = 0; j < i; j++, i--) {
        temp = hex_string[j];
        hex_string[j] = hex_string[i];
        hex_string[i] = temp;
    }

    // Print hex string
    kputs(hex_string, vga, nlDepth);
}
