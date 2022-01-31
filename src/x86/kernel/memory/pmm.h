#ifndef PMM_H
#define PMM_H

#include "paging.h"
#include "heap.h"

void alloc_frame(page_t* page, unsigned char isKernel, unsigned char isWritable);
void free_frame(page_t* page);
void init_pmm(unsigned int nFrames);

#endif
