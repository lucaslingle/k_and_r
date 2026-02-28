/*
Write a program to print a histogram of 
the frequencies of different characters in its input. 
*/

#include <stdio.h>
#define CHARCOUNT 256

main() {
    int c, i, j;
    int hist[CHARCOUNT];

    for (i = 0; i < CHARCOUNT; i++) {
        hist[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        hist[c]++;
    }

    for (i = 1; i <= CHARCOUNT; i++) {
        printf("%3d ", i);
        for (j = 0; j < hist[i-1]; j++) {
            putchar('*');
        }
        putchar('\n');
    }
}