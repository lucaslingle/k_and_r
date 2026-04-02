/*
Rewrite appropriate programs from earlier chapters and exercises
with pointers instead of array indexing. 

Good possibilities include:
 - getline (Ch. 1, 4)
 -> atoi (Ch. 4)
 - itoa (Ch. 3)
 - reverse (Ch. 3)
 - strindex (Ch. 4)
 - getop (Ch. 4)
*/

#include <stdio.h>
#include <ctype.h>

int book_atoi(char s[]) {
    int i, n, sign;
    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}

int exercise_atoi(char *s) {
    int n, sign;
    for (; isspace(*s); s++)
        ;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}

int main() {
    char s[100] = "-1337";
    printf("%d\n", book_atoi(s));
    printf("%d\n", exercise_atoi(s));

    char s2[100] = "+0";
    printf("%d\n", book_atoi(s2));
    printf("%d\n", exercise_atoi(s2));
}
