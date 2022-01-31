#include "../pmm.h"

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))


static unsigned int* frames;
static unsigned int nframes;


void panic(const char* const);


void init_pmm(unsigned int nFrames) {
    frames = (unsigned int*)kmalloc(nFrames);
}

static void _set_frame(unsigned int frame_addr) {
    unsigned int frame = frame_addr / 0x1000;
    unsigned int idx = INDEX_FROM_BIT(frame);
    unsigned int offset = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << offset);
}

static void _clear_frame(unsigned int frame_addr) {
    unsigned int frame = frame_addr / 0x1000;
    unsigned int idx = INDEX_FROM_BIT(frame);
    unsigned int offset = OFFSET_FROM_BIT(frame);
    frames[idx] &= ~(0x1 << offset);
}

static unsigned int _test_frame(unsigned int frame_addr) {
    unsigned int frame = frame_addr / 0x1000;
    unsigned int idx = INDEX_FROM_BIT(frame);
    unsigned int offset = OFFSET_FROM_BIT(frame);
    return frames[idx] & (0x1 << offset);
}

static unsigned int _first_frame() {
    unsigned int i;
    unsigned int j;

    for (i = 0; i < INDEX_FROM_BIT(nframes); ++i) {
        for (j = 0; j < 32; ++j) {
            unsigned int toTest = 0x1 << j;
            if (!(frames[i] & toTest)) {
                return i * 4 * 8 + j;
            }
        }
    }
}

void alloc_frame(page_t* page, unsigned char isKernel, unsigned char isWritable) {
    if (page->frame != 0) {
        // Frame already allocated.
        return;
    }

    unsigned int idx = _first_frame();
    if (idx == (unsigned int) - 1) {
        panic("__FRAME_ALLOC_FAILURE__:0x1C08");
    }

    _set_frame(idx * 0x1000);
    page->present = 1;   // Is being used.
    page->rw = isWritable ? 1 : 0;
    page->user = isKernel ? 0 : 1;
    page->frame = idx;
}


void free_frame(page_t* page) {
    if (!(page->frame)) {
        return;     // Was not allocated.
    }

    _clear_frame(page->frame);
    page->frame = 0x0;
}
