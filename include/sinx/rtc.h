#pragma once

#define BCD2BIN(bcd) ((((bcd)&15) + ((bcd) >> 4) * 10))
#define CMOS_ADDREG 0x70
#define CMOS_DATAREG 0x71
#define CMOS_DISABLE_NMI 0x80

#define SecIndex 0
#define MinIndex 2
#define HourIndex 4
#define DayIndex 7
#define MonthIndex 8
#define YearIndex 9

struct Time
{
    unsigned long sec;
    unsigned long min;
    unsigned long hr;
};

struct Date
{
    unsigned long year;
    unsigned char month;
    unsigned char day;
};

char *longtostr(long zahl);
unsigned char readCmos(unsigned char address);
void readTime(struct Time *getTime);
void readDate(struct Date *getDate);
