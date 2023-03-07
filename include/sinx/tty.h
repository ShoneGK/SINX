#pragma once

#include <string.h>
#include <drivers/VGA/driver.h>
#include <coreutils/echo.h>
#include <coreutils/time.h>
#include <coreutils/date.h>

int startswith(char *str, char *substr)
{
    int startsWith = 0;
    for (int i = 0; substr[i] != '\0'; i++)
    {
        if (str[i] != substr[i])
        {
            startsWith = 0;
            break;
        }
        startsWith = 1;
    }
    return startsWith;
}

void execute_command(char *input)
{

    if (startswith(input, "poweroff"))
    {
        puts("Powering Off...\n");

        disableCursor();
        asm volatile("hlt");
    }
    else if (startswith(input, "echo"))
    {
        runEcho(input);
    }
    else if (startswith(input, "time"))
    {
        runTime();
    }
    else if (startswith(input, "date"))
    {
        runDate();
    }
    else
    {
        puts("Unknown command: ");
        puts(input);
    }
    puts("\n> ");
}