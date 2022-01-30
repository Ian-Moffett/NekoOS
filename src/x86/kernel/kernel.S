bits 32
global _kentry
extern _start

_kentry:
    call _start
    jmp post_exec

post_exec:
    sti
    hlt
    jmp post_exec
