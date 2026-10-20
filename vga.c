#include "vga.h"
#include "stdint.h"
uint16_t column = 0;
uint16_t line = 0;
uint16_t* const vga = (uint16_t* const)0xB8000;
const uint16_t defaultColor = (COLOR8_BLACK << 8) | (COLOR8_WHITE << 12);
uint16_t currentcolor = defaultColor;
void reset(){
    line = 0;
    column = 0;
    currentcolor = defaultColor;
    for(uint16_t y = 0; y < HEIGHT; y++){
        for(uint16_t x = 0; x < WIDTH; x++){
            vga[y * WIDTH + x] = ' ' | defaultColor;
        }
    }
}
void newline(){
    if (line < HEIGHT - 1){
        line++;
        column = 0;
    }
    else{
        scrollup();
        column = 0;
    }
}
void scrollup(){
    for (uint16_t y = 0; y < HEIGHT; y++){
        for (uint16_t x = 0; x < WIDTH; x++){
            vga[(y - 1) * WIDTH + x] = vga[y * WIDTH + x];
        }
    }
    for (uint16_t x = 0; x < WIDTH; x++){
        vga[(HEIGHT - 1) * WIDTH + x] = ' ' | currentcolor;
    }
}
void printf(const char* s){
    while(*s){
        switch(*s){
            case '\n':
                newline();
                break;
            case '\r':
                column = 0;
                break;
            case '\t':
                if (column == WIDTH){
                    newline();
                }
                uint16_t tablen = 4 - (column % 4);
                while(tablen != 0){
                    vga[line * WIDTH + (column++)] = ' ' | currentcolor;
                    tablen--;
                }
                break;
            default:
                if (column == WIDTH){
                    newline();
                }
                vga[line * WIDTH + (column++)] = *s | currentcolor;
                break;
        }
        s++;
    }
}