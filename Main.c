/* 
    MADE BY: EXTREME_M
    VER 0.6.0 x86
    EMAIL: lamyanksh@gmail.com
    Pendrive bootable OS
    **POINTOS_PORTABLE**
*/
#include "vga.h"    // boot/vga.h 
#include "stdint.h" // boot/stdint.h
#include "gdt.h"    // boot/gdt.h
#include "util.h"   // boot/util.h
int kmain(void){
    reset();
    printf("welcome to pointOS-Portable\n");
    printf("version 0.6.0 x86\n");
    initialgdt();
    printf("GDT initialized\n");
    printf("kernel$ ");
    return 0;
}