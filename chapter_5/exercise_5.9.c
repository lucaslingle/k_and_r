/*
Rewrite the routines day_of_year and month_day 
with pointers instead of indexing. 

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

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    char *lengths = (!leap) ? daytab[0] : daytab[1];
    char *lengths0 = lengths;
    for (; lengths - lengths0 < month; lengths++)
        day += *lengths;
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    char *lengths = (!leap) ? daytab[0] : daytab[1];
    char *lengths0 = lengths;
    for (; yearday > *lengths; lengths++)
        yearday -= *lengths;
    *pmonth = lengths - lengths0;
    *pday = yearday;
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
}
