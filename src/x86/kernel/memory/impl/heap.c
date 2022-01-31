#include "../heap.h"

#define FLAG_FREE 0x1


typedef struct _MEMBLOCK {
    struct _MEMBLOCK* next;
    size_t size;
    unsigned char flags;
} __attribute__((packed)) memblock_t;


#define DATA_START(mem_block) (((char*) mem_block) + sizeof(memblock_t))


static memblock_t* mem_head = NULL;
static memblock_t* mem_tail = NULL;
static size_t limit = 0;
static size_t allocated = 0;

void heap_init(void* begin, size_t _limit) {
    mem_head = (memblock_t*)begin;
    mem_head->next = NULL;
    mem_head->size = 0;
    mem_head->flags = 0;
    mem_tail = mem_head;
    limit = _limit;
    allocated = 0;
}

size_t get_mem_alloc() {
    return allocated;
}

static memblock_t* _first_fit(size_t size) {
    memblock_t* curFrame = mem_head;

    while (curFrame != NULL) {
        if (curFrame->flags & FLAG_FREE && curFrame->size >= size) {
            return curFrame;    // Yay, we found a block of memory!
        }

        curFrame = curFrame->next;
    }

    return NULL;        // No memory was found :(
}


void* kmalloc(size_t size) {
    if (allocated + size > limit) {
        return NULL;        // Too much memory requested.
    }

    memblock_t* region = _first_fit(size);
    if (region == NULL) {
        char* next = DATA_START(mem_tail) + mem_tail->size;
        mem_tail->next = (memblock_t*)next;
        region = mem_tail->next;
        region->size = size;
        region->flags = 0x0;
        region->next = NULL;
        mem_tail = region;
        allocated += size;
    }

    return DATA_START(region);
}


void kfree(void* addr) {
    memblock_t* curFrame = mem_head;

    while (curFrame != NULL && addr != DATA_START(curFrame)) {
        curFrame->flags |= FLAG_FREE;
        curFrame = curFrame->next;
    }
}
