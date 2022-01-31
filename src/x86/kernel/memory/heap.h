#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>


void heap_init(void* begin, size_t _limit);
void* kmalloc(size_t size);
void kfree(void* data);
size_t get_mem_alloc();


#endif
