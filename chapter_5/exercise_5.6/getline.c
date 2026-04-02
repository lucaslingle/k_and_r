/*
Rewrite appropriate programs from earlier chapters and exercises
with pointers instead of array indexing. 

Good possibilities include:
 -> getline (Ch. 1, 4)
 - atoi (Ch. 4)
 - itoa (Ch. 3)
 - reverse (Ch. 3)
 - strindex (Ch. 4)
 - getop (Ch. 4)
*/

#include <stdio.h>
#include <string.h>

int book_getline(char s[], int lim) {
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int exercise_getline(char *s, int lim) {
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return i;
}

int main() {
    char s1[100];
    book_getline(s1, 100);
    printf("%s", s1);

    char s2[100];
    exercise_getline(s2, 100);
    printf("%s", s2);

    printf("%d\n", strcmp(s1, s2) == 0);
}
