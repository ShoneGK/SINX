#include "date.h"

#include <sinx/rtc.h>
#include <drivers/VGA/driver.h>

int runDate()
{
    struct Date cmosDate;

    readDate(&cmosDate);
    puts(longtostr(cmosDate.month));
    puts("-");
    puts(longtostr(cmosDate.day));
    puts("-");
    puts(longtostr(cmosDate.year));
}