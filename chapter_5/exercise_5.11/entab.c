/*
Modify the programs entab and detab (written as exercises in Chapter 1)
to accept a list of tab stops as arguments. 
Use the default tab settings if there are no arguments. 

// original entab exercise:
Write a program entab that replaces strings of blanks by the minimum number 
of tabs and blanks to achieve the same spacing. 
Use the same tab stops as for the previous problem. 

When either a tab or a single blank would suffice to reach a tab stop, 
which should be given preference? 
*/

#include <stdio.h>
#include <ctype.h>

int exercise_atoi(char *s) {
    int n, sign;
    for (; isspace(*s); s++)
        ;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}

// note: my code assumes no tab chars included in the input, only allows in output.
int main(int argc, char *argv[]) {
    int *tab_stops; 
    int *tab_stops0 = tab_stops;
    if (argc == 1)
        for (int j = 0; j < 10; j++)
            *tab_stops++ = (j + 1) * 8;
    else
        while (--argc > 0) {
            ++argv;
            *tab_stops++ = exercise_atoi(*argv);
        }
    *tab_stops = -1;

    int space_streak = 0;
    int line_offset = 0;
    int c;
    while ((c = getchar()) != EOF) {
        for (tab_stops = tab_stops0; *tab_stops != -1; tab_stops++)
            if (space_streak > 0 && line_offset == *tab_stops) {
                putchar('\t');
                space_streak = 0;
                break;
            }
        
        if (c == ' ') {
            space_streak++;
            line_offset++;
        } else {
            putchar(c);
            space_streak = 0;
            line_offset++;
        }
    }
}
