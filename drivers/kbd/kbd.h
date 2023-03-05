#pragma once

#include <string.h>
#include <dtypes.h>
#include <iobyte.h>
#include <drivers/VGA/driver.h>
#include <drivers/keyboard/keys.h>

static char key_buffer[256];
#define BACKSPACE_KEY 0x0E

static void keyboard_callback()
{
    while (1 == 1)
    {
        uint8_t scancode = inb(0x60);

        if (scancode == BACKSPACE_KEY)
        {
            if (backspace_func(key_buffer))
            {
                print_backspace();
            }
        }
        else
        {
            char letter = get_ascii_char(scancode);
            join(key_buffer, letter);
            char str[2] = {letter, '\0'};
            puts(str);
        }
    }
}

// static void keyboard_callbackSS() {
//     while (1==1){
//     uint8_t scancode = inb(0x60);
//
//     char letter = get_ascii_char(scancode);
//     join(key_buffer, letter);
//     char str[2] = {letter, '\0'};
//     puts(str);
//     }
// }

int backspace_func(char buffer[])
{
    int len = strlen(buffer);
    if (len > 0)
    {
        buffer[len - 1] = '\0';
        return 1;
    }
    else
    {
        return 0;
    }
}

void print_backspace()
{

    int newCursor = getVGACursor() - 2;

    putc(' ', newCursor);
    setVGACursor(newCursor);
}
