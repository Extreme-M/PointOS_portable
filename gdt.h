#include "stdint.h"
struct entry_sector{
    uint16_t limit;
    uint16_t base_l1;
    uint8_t base_l2;
    uint8_t access;
    uint8_t all_flag;
    uint8_t base_l3;
}__attribute__((packed));
struct ptr_sector{
    uint16_t limit;
    uint32_t *base;
}__attribute__((packed));
struct tss_sector_entry{
    uint32_t prev_tss;
    uint32_t esp0;
    uint32_t ss0;
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldtr;
    uint32_t trap;
    uint32_t iomap_base;
}__attribute__((packed));
void initialgdt();
void gdtAddress(uint32_t set, uint32_t base, uint32_t limit, uint8_t A_flag, uint8_t g_flag);
void writeTss(uint32_t num, uint16_t ss0, uint32_t esp0);

