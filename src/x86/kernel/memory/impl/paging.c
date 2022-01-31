#include "../paging.h"


__attribute__((aligned(4096))) static unsigned int page_dir[1024] = {0x00000002};
__attribute__((aligned(4096))) static unsigned int kpage_tbl[1024];

void _init_paging(void* _pge_dir);

void init_paging() {
    for (int i = 0; i < 1024; ++i) {
        kpage_tbl[i] = (i * 0x1000) | 0x3;
    }

    page_dir[0] = (unsigned int)&kpage_tbl | 0x3;
    _init_paging((void*)&page_dir);
}
