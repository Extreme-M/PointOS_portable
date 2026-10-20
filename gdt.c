#include "gdt.h"
#include "stdint.h"
#include "util.h"
extern void gdt_flush(uint32_t);
extern void tss_flush(void);
struct entry_sector entry[6];
struct ptr_sector ptr;
struct tss_sector_entry tss_entry;
void gdtAddress(uint32_t set, uint32_t base, uint32_t limit, uint8_t A_flag, uint8_t g_flag){
    // base segment
    entry[set].base_l1 = base & 0xFFFF;
    entry[set].base_l2 = (base >> 16) & 0xFF;
    entry[set].base_l3 = (base >> 24 ) & 0xFF;
    // limit segment
    entry[set].limit = limit & 0xFFFF;
    entry[set].all_flag = (limit >> 16) & 0x0F;
    entry[set].all_flag |= g_flag & 0xF0;
    entry[set].access = A_flag;
}
void writeTss(uint32_t num, uint16_t ss0, uint32_t esp0){
    uint32_t base = (uint32_t) &tss_entry;
    uint32_t limit = sizeof(tss_entry) - 1;
    gdtAddress(num, base, limit, 0B11101001, 0x00);
    memset(&tss_entry, 0, sizeof(tss_entry));
    tss_entry.ss0 = ss0;
    tss_entry.esp0 = esp0;
    tss_entry.cs = 0x08 | 0x3;
    tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x10 | 0x3;
}
void initialgdt(){
    ptr.limit = (sizeof(struct entry_sector) * 6) - 1;
    ptr.base = (uint32_t*)&entry;
    gdtAddress(0, 0, 0B00000000000000000000000000000000, 0B00000000, 0B00000000); //null pointer
    gdtAddress(1, 0, 0B11111111111111111111111111111111, 0B10011010, 0B11001111); //kernel code
    gdtAddress(2, 0, 0B11111111111111111111111111111111, 0B10010010, 0B11001111); //kernel data
    gdtAddress(3, 0, 0B11111111111111111111111111111111, 0B11111010, 0B11001111); //user code
    gdtAddress(4, 0, 0B11111111111111111111111111111111, 0B11110010, 0B11001111); //user data
    writeTss(5, 0x10, 0x0);//tss
    gdt_flush((uint32_t)&ptr);
    tss_flush();
}