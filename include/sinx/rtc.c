#include "rtc.h"

#include <iobyte.h>

char *longtostr(long zahl)
{
    static char text[20]; // Make me static, otherwise it's on the stack and will screw up soon, if it's static, it's allocated always, but is not safe for multi-tasking/threading.
    int loc = 19;
    text[19] = 0; // NULL terminate the string
    while (zahl)  // While we have something left, lets add a character to the string
    {
        --loc;
        text[loc] = (zahl % 10) + '0';
        zahl /= 10;
    }
    if (loc == 19) // Nothing, lets at least put a 0 in there!
    {
        --loc;
        text[loc] = '0';
    }
    return &text[loc]; // Start from where loc left off
}

unsigned char readCmos(unsigned char address)
{
    unsigned char data;
    outb(CMOS_ADDREG, address);
    data = inb(CMOS_DATAREG);
    return data;
}

void readTime(struct Time *getTime)
{
    getTime->sec = readCmos(SecIndex);
    getTime->min = readCmos(MinIndex);
    getTime->hr = readCmos(HourIndex);
}

void readDate(struct Date *getDate)
{
    getDate->year = readCmos(YearIndex);
    getDate->month = readCmos(MonthIndex);
    getDate->day = readCmos(DayIndex);
}