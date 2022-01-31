#include "../paging.h"


__attribute__((aligned(4096))) static unsigned int kernel_pge_dir[1024];
__attribute__((aligned(4096))) static unsigned int dummy_pge_tbl[1024];
__attribute__((aligned(4096))) static unsigned int dummy_pge_tbl1[1024];

void panic(const char* const);
void _init_paging(void* pge_tbl);

void init_paging() {  
    for (int i = 0; i < 1024; ++i) {
        kernel_pge_dir[i] = 0x00000002;
        dummy_pge_tbl[i] = (i * 0x1000) | 0x3;
        dummy_pge_tbl1[i] = (i * 0x1000) | 0x7;
    }

    kernel_pge_dir[0] = (unsigned int)dummy_pge_tbl | 0x3;
    kernel_pge_dir[1] = (unsigned int)dummy_pge_tbl1 | 0x7;

    _init_paging((void*)&kernel_pge_dir);
}


void ch_pge_dir(unsigned int* pge_dir) {
    _init_paging((void*)&pge_dir);
}
