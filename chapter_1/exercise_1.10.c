/*
Write a program to copy its input to its output, 
replacing each tab by \t, each nondestructive backspace by \b, and each backslash by \\. 
This makes tabs and backspaces visible in an unambiguous way. 

Work in progress.
*/

#include <stdio.h>

main() {
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            putchar('\\');
            putchar('t');
        } 
        else if (c == '\b') {
            putchar('\\');
            putchar('t');
        }
        else if (c == '\\') {
            putchar('\\');
            putchar('\\');
        }
        else {
            putchar(c);
        }
    }
}