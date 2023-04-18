#include "echo.h"

#include <drivers/VGA/driver.h>

int runEcho(char *input){
    // remove echo[5] from string
    char *toReturn = input + 5;
    puts(toReturn);
    puts("\n");
    toReturn = '\0';
}