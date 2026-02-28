/*
Write a program to copy its input to its output, 
replacing each string of one or more blanks by a single blank. 
*/

#include <stdio.h>

main() {
    int stored;
    int next;

    stored = EOF;
    next = getchar();

    while (next != EOF) {
        if (stored == EOF) {
            ;
        } else if ((stored == ' ') && (next == ' ')) {
            ;
        } else if ((stored == ' ') && (next != ' ')) {
            putchar(' ');
        } else {
            putchar(stored);
        }
        stored = next;
        next = getchar();
    }
}