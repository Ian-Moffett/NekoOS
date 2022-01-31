#include "../strings.h"


size_t strlen(const char* const STR) {
    size_t len = 0;
    while (STR[len++]); return len;
}



unsigned char* strncpy(unsigned char* dst, const unsigned char* src, const unsigned char len) {
    for (unsigned char i = 0; src[i] && i < len; i++)
        dst[i] = src[i];

    return dst;
}
