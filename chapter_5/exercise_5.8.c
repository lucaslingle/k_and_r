/*
There is no error checking in day_of_year or month_day.
Remedy this defect. 

// reference code
static char daytab[2][31] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; i < month; i++) {
        day += daytab[leap][i];
    }
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}
*/

#include <stdio.h>
#define DATE_RANGE_ERR -1

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (month < 1 || 12 < month)
        return DATE_RANGE_ERR;
    if (day < 1 || daytab[leap][month] < day)
        return DATE_RANGE_ERR;

    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    int yearday_min = 1;
    int yearday_max = 0;
    for (int j = 1; j <= 12; j++)
        yearday_max += daytab[leap][j];
    if (yearday < yearday_min || yearday_max < yearday) {
        *pmonth = DATE_RANGE_ERR;
        *pday = DATE_RANGE_ERR;
        return;
    }

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
    return;
}

int main() {
    int y1 = 2026;
    int m1 = 4;
    int d1 = 2;
    int doy1 = day_of_year(y1, m1, d1);
    printf("Date: %d/%d/%d, Day of Year: %d\n", y1, m1, d1, doy1);

    int m2;
    int d2;
    month_day(y1, doy1, &m2, &d2);
    printf("Date: %d/%d/%d, Day of Year: %d\n", y1, m2, d2, doy1);

    int y3 = 7777;
    int m3 = -7;
    int d3 = 7;
    int doy3 = day_of_year(y3, m3, d3);
    printf("Date: %d/%d/%d, Day of Year: %d\n", y3, m3, d3, doy3);

    int y4 = 7777;
    int m4 = 77;
    int d4 = 7;
    int doy4 = day_of_year(y4, m4, d4);
    printf("Date: %d/%d/%d, Day of Year: %d\n", y4, m4, d4, doy4);

    int y5 = 7777;
    int m5 = 7;
    int d5 = -7;
    int doy5 = day_of_year(y5, m5, d5);
    printf("Date: %d/%d/%d, Day of Year: %d\n", y5, m5, d5, doy5);

    int y6 = 7777;
    int m6 = 7;
    int d6 = 77;
    int doy6 = day_of_year(y6, m6, d6);
    printf("Date: %d/%d/%d, Day of Year: %d\n", y6, m6, d6, doy6);

    int m7;
    int d7;
    month_day(y6, doy6, &m7, &d7);
    printf("Date: %d/%d/%d, Day of Year: %d\n", y6, m7, d7, doy6);
}
