/*
Adapt the ideas of printd to write a recursive version of itoa;
that is, convert an integer into a string by calling a recursive routine. 
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>

void printd(int n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}

void itoa(int n, char s[]) {
    // our impl handles largest negative number, thanks to sign juggling. 
    static int i;
    static int sign;
    if (n <= -10 || 10 <= n) {
        itoa(n / 10, s);
        s[i++] = (sign * (n % 10)) + '0';  // mod in c is really "sign(n) * (|n| % modulus)".
    } else {
        i = 0;
        sign = (n < 0) ? -1 : 1;
        if (sign == -1) {
            s[i++] = '-';
        }
        s[i++] = (sign * n) + '0';
    }
    s[i] = '\0';  // write null byte to next index, if we're done it won't be overwritten.
}

int main() {
    char s[100];
    int ns[] = {123, -123, INT_MIN, INT_MAX, 0, 1};
    for (int i = 0; i < sizeof(ns) / sizeof(0); i++) {
        itoa(ns[i], s);
        printf("s: %s\n", s);
    }
}
