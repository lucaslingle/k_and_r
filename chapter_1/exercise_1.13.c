/*
Write a program to print a histogram of the lengths of words in its input.
It is easy to draw the histogram bars horizontal; 
a vertical orientation is more challenging. 
*/

#include <stdio.h>

main() {
    int c, i, j, len;
    int hist[10];

    len = 0;
    for (i = 0; i < 10; i++) {
        hist[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (len > 10) {
                len = 10;
            }
            hist[len - 1]++;
            len = 0;
        } else if (c != ' ' && c != '\t' && c != '\n') {
            len++;
        }
    }

    for (i = 1; i <= 10; i++) {
        printf("%3d ", i);
        for (j = 0; j < hist[i-1]; j++) {
            putchar('*');
        }
        putchar('\n');
    }
}