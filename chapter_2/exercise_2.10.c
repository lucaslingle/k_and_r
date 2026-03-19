/*
Rewrite the function lower, which converts upper case letters to lower case, 
with a conditional expression instead of if-else. 

// original function lower
int lower(int c) {
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    else
        return c;
}
*/

#include <stdio.h>

int lower(int c) {
    return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
}


int main() {
    int c;

    c = 'A';
    putchar(c);
    printf("->");
    putchar(lower(c));
    printf("\n");

    c = 'a';
    putchar(c);
    printf("->");
    putchar(lower(c));
    printf("\n");

    c = 'B';
    putchar(c);
    printf("->");
    putchar(lower(c));
    printf("\n");

    c = 'b';
    putchar(c);
    printf("->");
    putchar(lower(c));
    printf("\n");

    c = 'Z';
    putchar(c);
    printf("->");
    putchar(lower(c));
    printf("\n");

    c = 'z';
    putchar(c);
    printf("->");
    putchar(lower(c));
    printf("\n");

    c = '0';
    putchar(c);
    printf("->");
    putchar(lower(c));
    printf("\n");

    c = '9';
    putchar(c);
    printf("->");
    putchar(lower(c));
    printf("\n");
}