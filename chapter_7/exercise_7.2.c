/*
Write a program that prints arbitrary input in a sensible way.
At a minimum, it should print non-graphic characters in octal or hexidecimal
according to local custom, and break long text lines.
*/
#include <stdio.h>
#include <ctype.h>
#define LINE_LEN 80

int main(int argc, char *argv[]) {
    int c;
    int n = 0;
    while ((c = getchar()) != EOF) {
        if (n == LINE_LEN - 1) {
            printf("%%\n");  // print one '%' followed by a newline
            n = 0;
        }
        if (!iscntrl(c)) {
            printf("\\x%x", c);  // print non-printable chars using hex
        } else if (c == '\\') {
            printf("\\\\");  // print two '\' for every one appearing in original input
        } else if (c == '%') {
            printf("%%%%");  // print two '%' for every one appearing in original input
        } else {
            putchar(c);
        }
        n++;
    }
}
