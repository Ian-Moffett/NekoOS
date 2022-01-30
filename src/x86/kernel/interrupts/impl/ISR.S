bits 32
global _irq0_isr
extern ticks
extern irq0_handler

_irq0_isr:   
    add [ticks], byte 1
    call irq0_handler
    mov al, 0x20
    out 0x20, al
    iret
