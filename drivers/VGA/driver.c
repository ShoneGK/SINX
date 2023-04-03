#include "driver.h"

#include <iobyte.h>
#include <string.h>
#include <std.h>
#include <drivers/gpu/colorizer.h>

unsigned char VGAColor = WHITE | BLACK << 4;

void setVGACursor(int offset) {
    offset /= 2;
    outb(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    outb(VGA_DATA_REGISTER, (unsigned char) (offset >> 8));
    outb(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    outb(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}

int getVGACursor() {
    outb(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    int offset = inb(VGA_DATA_REGISTER) << 8;
    outb(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    offset += inb(VGA_DATA_REGISTER);
    return offset * 2;
}

void setVGAColor(unsigned char fg, unsigned char bg){
    unsigned char VGAColor = fg | bg << 4;
}

void putc(char character, int offset) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = VGAColor;
}

void puts(char *string) {
    int offset = getVGACursor();
    int i = 0;
    while (string[i] != 0) {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scrollLine(offset);
        }
        if (string[i] == '\n') {
            offset = setNewline(offset);
        } else {
            putc(string[i], offset);
            offset += 2;
        }
        i++;
    }
    setVGACursor(offset);
}

int getCellRow(int offset) {
    return offset / (2 * MAX_COLS);
}

char getCurrentChar(int offset){
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    return vidmem[offset];
}

int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int setNewline(int offset) {
    return get_offset(0, getCellRow(offset) + 1);
}

int scrollLine(int offset) {
    memcp(
            (char *) (uintptr_t) (get_offset(0, 1) + VIDEO_ADDRESS),
            (char *) (uintptr_t) (get_offset(0, 0) + VIDEO_ADDRESS),
            MAX_COLS * (MAX_ROWS - 1) * 2
    );

    for (int col = 0; col < MAX_COLS; col++) {
        putc(' ', get_offset(col, MAX_ROWS - 1));
    }

    return offset - 2 * MAX_COLS;
}

void clearVGA() {
    for (int i = 0; i < MAX_COLS * MAX_ROWS; ++i) {
        putc(' ', i * 2);
    }
    setVGACursor(get_offset(0, 0));
}

void enableVGACursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void disableCursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}