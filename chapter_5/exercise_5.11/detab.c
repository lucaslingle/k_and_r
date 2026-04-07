/*
Modify the programs entab and detab (written as exercises in Chapter 1)
to accept a list of tab stops as arguments. 
Use the default tab settings if there are no arguments. 

// original detab exercise:
Write a program detab that replaces tabs in the input with the proper number of blanks 
to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. 
Should n be a variable or symbolic parameter?
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
    
    int c;
    int line_offset = 0;
    while ((c = getchar()) != EOF) {
        tab_stops = tab_stops0;
        if (c == '\n') {
            putchar('\n');
            line_offset = 0;
        } else if (c == '\t') {
            for (; *tab_stops != -1; tab_stops++) {
                if (line_offset < *tab_stops) {
                    for (int i = line_offset; i < *tab_stops; i++) {
                        putchar(' ');
                        line_offset++;
                    }
                    break;
                }
            }
        } else {
            putchar(c);
            line_offset++;
        }
    }
}
