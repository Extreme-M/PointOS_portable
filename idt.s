global idt_flush
idt_flush:
    MOV eax, [esp+4]
    LIDT [eax]
    STI
    RET
extern isr_handler
isr_stub:
    pusha
    mov eax,ds
    PUSH eax
    MOV eax, cr2
    PUSH eax
    MOV ax, 0x10
    MOV ds, ax
    MOV es, ax
    MOV fs, ax
    MOV gs, ax
    PUSH esp
    CALL isr_handler
    ADD esp, 8
    POP ebx
    MOV ds, bx
    MOV es, bx
    MOV fs, bx
    MOV gs, bx
    POPA
    ADD esp, 8
    STI
    IRET
extern irq_handler
irq_stub:
    pusha
    mov eax,ds
    PUSH eax
    MOV eax, cr2
    PUSH eax

    MOV ax, 0x10
    MOV ds, ax
    MOV es, ax
    MOV fs, ax
    MOV gs, ax

    PUSH esp
    CALL irq_handler

    ADD esp, 8
    POP ebx
    MOV ds, bx
    MOV es, bx
    MOV fs, bx
    MOV gs, bx

    POPA
    ADD esp, 8
    STI
    IRET
%macro isr_ok 1
    global isr%1
    isr%1:
        CLI
        PUSH LONG 0
        PUSH LONG %1
        JMP isr_stub
%endmacro
%macro isr_notok 1
    global isr%1
    isr%1:
        CLI
        PUSH LONG %1
        JMP isr_stub
%endmacro
%macro irq_macro 2
    global irq%1
    iqr%1:
        CLI
        PUSH LONG 1
        PUSH LONG %2
        JMP irq_stub
%endmacro
isr_ok 0
isr_ok 1
isr_ok 2
isr_ok 3
isr_ok 4
isr_ok 5
isr_ok 6
isr_ok 7
isr_notok 8
isr_ok 9
isr_notok 10
isr_notok 11
isr_notok 12
isr_notok 13
isr_notok 14
isr_ok 15
isr_ok 16
isr_ok 17
isr_ok 18
isr_ok 19
isr_ok 20
isr_ok 21
isr_ok 22
isr_ok 23
isr_ok 24
isr_ok 25
isr_ok 26
isr_ok 27
isr_ok 28
isr_ok 29
isr_ok 30
isr_ok 31
isr_ok 128
isr_ok 177
irq_macro 0, 32
irq_macro 1, 33
irq_macro 2, 34
irq_macro 3, 35
irq_macro 4, 36
irq_macro 5, 37
irq_macro 6, 38
irq_macro 7, 39
irq_macro 8, 40
irq_macro 9, 41
irq_macro 10, 42
irq_macro 11, 43
irq_macro 12, 44
irq_macro 13, 45
irq_macro 14, 46
irq_macro 15, 47