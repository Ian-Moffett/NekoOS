#ifndef TASK_H
#define TASK_H

#include "../memory/heap.h"


typedef struct _Thread {
    int id;
    unsigned int esp, ebp;
    unsigned int eip;
    unsigned int page_dir;
    struct _Thread* next;
} __attribute__((packed)) thread_t;


void init_tasking();
void task_switch();
int fork();
int getpid();
void* get_curthread_addr();

#endif
