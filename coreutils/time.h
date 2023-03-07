#pragma once

#include <sinx/rtc.h>
#include <drivers/VGA/driver.h>

int runTime()
{
    struct Time cmosTime;

    readTime(&cmosTime);
    puts(longtostr(cmosTime.hr));
    puts(":");
    puts(longtostr(cmosTime.min));
    puts(":");
    puts(longtostr(cmosTime.sec));
}