#include "stdint.h"
#include "util.h"
#include "vga.h"
#include "idt.h"
extern void idt_flush(uint32_t);
struct idt_entry idt_entries[256];
struct idt_ptr _ptr;
void initialidt(){
    _ptr.limit = sizeof(struct idt_entry) * 256 - 1;
    _ptr.base = (uint32_t) &idt_entries;
    memset(&idt_entries, 0, sizeof(struct idt_entry) * 256);
    outPortB(0x20, 0x11);
    outPortB(0xA0, 0x11);
    outPortB(0x21, 0x20);
    outPortB(0xA1, 0x28);
    outPortB(0x21, 0x04);
    outPortB(0xA1, 0x02);
    outPortB(0x21, 0x01);
    outPortB(0x21, 0x01);
    outPortB(0x21, 0x0);
    outPortB(0xA1, 0x0);
    idtAddress(0, (uint32_t)isr0, 0x08, 0x8E);
    idtAddress(1, (uint32_t)isr1, 0x08, 0x8E);
    idtAddress(2, (uint32_t)isr2, 0x08, 0x8E);
    idtAddress(3, (uint32_t)isr3, 0x08, 0x8E);
    idtAddress(4, (uint32_t)isr4, 0x08, 0x8E);
    idtAddress(5, (uint32_t)isr5, 0x08, 0x8E);
    idtAddress(6, (uint32_t)isr6, 0x08, 0x8E);
    idtAddress(7, (uint32_t)isr7, 0x08, 0x8E);
    idtAddress(8, (uint32_t)isr8, 0x08, 0x8E);
    idtAddress(9, (uint32_t)isr9, 0x08, 0x8E);
    idtAddress(10, (uint32_t)isr10, 0x08, 0x8E);
    idtAddress(11, (uint32_t)isr11, 0x08, 0x8E);
    idtAddress(12, (uint32_t)isr12, 0x08, 0x8E);
    idtAddress(13, (uint32_t)isr13, 0x08, 0x8E);
    idtAddress(14, (uint32_t)isr14, 0x08, 0x8E);
    idtAddress(15, (uint32_t)isr15, 0x08, 0x8E);
    idtAddress(16, (uint32_t)isr16, 0x08, 0x8E);
    idtAddress(17, (uint32_t)isr17, 0x08, 0x8E);
    idtAddress(18, (uint32_t)isr18, 0x08, 0x8E);
    idtAddress(19, (uint32_t)isr19, 0x08, 0x8E);
    idtAddress(20, (uint32_t)isr20, 0x08, 0x8E);
    idtAddress(21, (uint32_t)isr21, 0x08, 0x8E);
    idtAddress(22, (uint32_t)isr22, 0x08, 0x8E);
    idtAddress(23, (uint32_t)isr23, 0x08, 0x8E);
    idtAddress(24, (uint32_t)isr24, 0x08, 0x8E);
    idtAddress(25, (uint32_t)isr25, 0x08, 0x8E);
    idtAddress(26, (uint32_t)isr26, 0x08, 0x8E);
    idtAddress(27, (uint32_t)isr27, 0x08, 0x8E);
    idtAddress(28, (uint32_t)isr28, 0x08, 0x8E);
    idtAddress(29, (uint32_t)isr29, 0x08, 0x8E);
    idtAddress(30, (uint32_t)isr30, 0x08, 0x8E);
    idtAddress(31, (uint32_t)isr31, 0x08, 0x8E);
    idtAddress(128, (uint32_t)isr128, 0x08, 0x8E); //syscall
    idtAddress(177, (uint32_t)isr177, 0x08, 0x8E); //syscall
    idt_flush((uint32_t)&_ptr);
}
void idtAddress(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags){
    idt_entries[num].base1 = base & 0xFFFF;
    idt_entries[num].base2 = (base >> 16) & 0xFFFF;
    idt_entries[num].sel = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags = flags | 0x60;
}
unsigned char* exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Fault",
    "Machine Check", 
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};
void isr_handler(struct InterruptRegisters* regs){
    if (regs->int_no < 32){
        printf(exception_messages[regs->int_no]);
        printf("\n");
        printf("Exception! System Halted\n");
        for (;;);
    }
}
void *irq_routines[16] = {
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};
void irq_install_handler (int irq, void (*handler)(struct InterruptRegisters *r)){
    irq_routines[irq] = handler;
}
void irq_uninstall_handler(int irq){
    irq_routines[irq] = 0;
}
void irq_handler(struct InterruptRegisters* regs){
    void (*handler)(struct InterruptRegisters *regs);
    handler = irq_routines[regs->int_no - 32];
    if (handler){
        handler(regs);
    }
    if (regs->int_no >= 40){
        outPortB(0xA0, 0x20);
    }
    outPortB(0x20,0x20);
}