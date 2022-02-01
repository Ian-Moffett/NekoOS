bits 32
global _lm_entry

_lm_entry:
    ; Zero out _l4_page_tbl.
    mov edi, _l4_page_tbl
    push edi
    xor eax, eax
    mov ecx, 1024
    rep stosd

    ; Zero out _l3_page_tbl.
    mov edi, _l3_page_tbl
    mov ecx, 1024
    rep stosd

    pop edi
    mov cr3, edi   ; Tell CPU where page table is.

    mov eax, _l3_page_tbl
    add eax, 3
    mov [edi], eax
    xor eax, eax
    mov eax, 3 | (1 << 7) | (1 << 2)    ; Setting entry in l3_page table.
    mov [_l3_page_tbl], eax
    mov ebx, _l4_page_tbl
    mov ecx, _l3_page_tbl

    ; Enable paging.
    mov eax, cr4
    or eax, 1 << 4
    mov cr4, eax
    cli
    hlt

GDT64:                           ; Global Descriptor Table (64-bit).
    .Null: equ $ - GDT64         ; The null descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 1                         ; Granularity.
    db 0                         ; Base (high).
    .Code: equ $ - GDT64         ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).
    .Data: equ $ - GDT64         ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).
    .UserCode: equ $ - GDT64         ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 11111010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).
    .UserData: equ $ - GDT64         ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 11110010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).
    Pointer:                    ; The GDT-pointer.
    dw $ - GDT64 - 1             ; Limit.
    dq GDT64

align 4096
section .bss
_l4_page_tbl: resb 4096
_l3_page_tbl: resb 4096
