/*
Write a program detab that replaces tabs in the input with the proper number of blanks 
to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. 
Should n be a variable or symbolic parameter?
*/

#include <stdio.h>
#define N 8

int main() {
    int c, i, line_offset;
    line_offset = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            putchar('\n');
            line_offset = 0;
        } else if (c == '\t') {
            for (i = (line_offset % N); i < N; i++) {
                putchar(' ');
                line_offset++;
            }
        } else {
            putchar(c);
            line_offset++;
        }
    }
}