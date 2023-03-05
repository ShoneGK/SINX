#pragma once

#include <string.h>
#include <drivers/VGA/driver.h>

void execute_command(char *input)
{
    if (strcmp(input, "poweroff") == 0)
    {

        puts("Powering Off...\n");

        asm volatile("hlt");
    }
    puts("Unknown command: ");
    puts(input);
    puts("\n> ");
}