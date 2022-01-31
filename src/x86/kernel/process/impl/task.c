#include "../task.h"

// Currently running thread.
volatile static thread_t* cur_thread;
// Start of task linked list.
volatile static thread_t* ready_queue;

static unsigned int _pid = 1;
unsigned int page_dir = 0;

void init_tasking() {
    __asm__ __volatile__("cli");
    cur_thread = (thread_t*)kmalloc(sizeof(thread_t));
    ready_queue = (thread_t*)kmalloc(sizeof(thread_t));
    cur_thread->id = _pid++;
    cur_thread->esp = 0;
    cur_thread->ebp = 0;
    cur_thread->eip = 0;
    cur_thread->page_dir = page_dir;
    cur_thread->next = 0;
    __asm__ __volatile__("sti");
}


void* get_curthread_addr() {
    return (void*)cur_thread;
}
