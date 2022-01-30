bits 16
org 0x7C00

xor ax, ax
mov ds, ax
mov es, ax
mov ss, ax

mov bp, 0x9C00
mov sp, bp

_start:
    mov [DRIVE_NUM], dl

    mov ah, 0x0
    mov al, 0x2
    int 0x10

    mov si, welcome_msg
    call puts

    mov si, boot_option
    call puts

    mov si, reboot_option
    call puts

    call get_keys

    mov ah, 0x0
    mov al, 0x2
    int 0x10

    mov si, boot_msg
    call puts

     ; Delay.
    mov cx, 0xF
    mov dx, 0x4240
    mov ah, 0x86
    int 0x15

     ; Delay.
    mov cx, 0xF
    mov dx, 0x4240
    mov ah, 0x86
    int 0x15

    mov dl, [DRIVE_NUM]
    call disk_load

    cli
    lgdt [gdt_desc]

    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_pm

    cli
    hlt


DRIVE_NUM: db 0

get_keys:
    hlt     ; Halt until an interrupt happens.
    mov ah, 0x00
    int 0x16
    cmp al, 'r'
    je reboot
    cmp al, 'b'
    je rm_ret
    jmp get_keys


reboot: jmp 0xFFFF:0x0

puts:
    mov ah, 0x0E
    lodsb
    or al, al
    jz rm_ret
    int 0x10
    jmp puts

rm_ret: ret

disk_load:
    mov ah, 0x42
    mov si, dap
    int 0x13
    jc disk_error
    ret

disk_error:
    mov si, disk_error_msg
    call puts
    cli
    hlt

 dap:
    db 0x10     ; DAP size.
    db 0x0      ; Always zero.
    dw 0x7      ; Sectors to read.
    dw 0x1000   ; Dest offset.
    dw 0x0      ; Dest segment.
    dq 0x1      ; Start sector (0 based).


; GDT: It defines what
; memory can be executed (The Code Descriptor),
; and what area contains data (Data Descriptor).

; This is used because everything about memory
; has changed in protected mode.


gdt_start:
    gdt_null:
        dd 0x0
        dd 0x0
    gdt_code:
        ; Type flags:
        ; Present: 1 since we are using code.
        ; Privilege: 00 higest privilige.
        ; Descriptor type: 1 for code/data.
        ; Code: 1.
        ; Conforming: 0 so segments with a lower privilege may not call code in this segment.
        ; Readable: 1.
        ; Accessed: 0.

        ; Other flags:
        ; Granularity: 1 so we can reach father into memory.
        ; 32-bit default: 1 since our segment will have 32-bit code.
        ; 64-bit code segment: 0.
        ; AVL 0.
        ; Limit: 1111.

        dw 0xFFFF       ; Limit.
        dw 0x0          ; Base.
        db 0x0          ; Base.
        db 10011010b    ; 1st flags, type flags.
        db 11001111b    ; 2nd flags, type flags.
        db 0x0
    gdt_data:
        ; Type flags:
        ; Code: 0.
        ; Expand down: 0.
        ; Writable: 0.
        ; Accessed: 0.

        dw 0xFFFF       ; Limit.
        dw 0x0          ; Base.
        db 0x0          ; Base.
        db 10010010b    ; 1st flags, type flags.
        db 11001111b    ; 2nd flags, type flags.
        db 0x0
gdt_end:


gdt_desc:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


welcome_msg: db "Welcome to NekoOS nya~ Please choose an option nya~", 0x0D, 0x0A, 0
boot_msg: db "Booting NekoOS UwU~", 0x0D, 0x0A, 0
boot_option: db 0x0D, 0x0A, "[B]oot", 0x0D, 0x0A, 0
reboot_option: db "[R]eboot", 0x0D, 0x0A, 0
disk_error_msg: db 0x0D, 0x0A, "FATAL: Failed to read disk. Sowwy :(", 0x0D, 0x0A, 0

bits 32
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax
    jmp _PM

_PM:
    call 0x1000
    hlt

times 510-($-$$) db 0
dw 0xAA55
