/*
Write a program to count blanks, tabs, and newlines.
*/

#include <stdio.h>

main() {
    int c;
    int nb, nt, nn;

    nb = 0;
    nt = 0;
    nn = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ')
            nb++;
        if (c == '\t')
            nt++;
        if (c == '\n')
            nn++;
    }
    printf("Num blanks: %d\n", nb);
    printf("Num tabs: %d\n", nt);
    printf("Num newlines: %d\n", nn);
}