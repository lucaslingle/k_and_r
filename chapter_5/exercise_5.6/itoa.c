/*
Rewrite appropriate programs from earlier chapters and exercises
with pointers instead of array indexing. 

Good possibilities include:
 - getline (Ch. 1, 4)
 - atoi (Ch. 4)
 -> itoa (Ch. 3)
 - reverse (Ch. 3)
 - strindex (Ch. 4)
 - getop (Ch. 4)
*/

#include <stdio.h>
#include <string.h>

void book_reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void book_itoa(int n, char s[]) {
    int i, sign;
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = (n % 10) + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    book_reverse(s);
}

void exercise_itoa(int n, char *s) {
    int sign;
    char *s0 = s;
    if ((sign = n) < 0)
        n = -n;
    do {
        *s++ = (n % 10) + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    book_reverse(s0);
}

int main() {
    char s[100];
    book_itoa(-1337, s);
    printf("%s\n", s);

    char s2[100];
    exercise_itoa(-1337, s2);
    printf("%s\n", s2);
}
