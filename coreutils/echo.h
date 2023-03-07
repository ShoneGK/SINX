#pragma once

#include <stdio/printf.h>

int runEcho(char *input){
    // remove echo[5] from string
    char *toReturn = input + 5;
    printf(toReturn);
}