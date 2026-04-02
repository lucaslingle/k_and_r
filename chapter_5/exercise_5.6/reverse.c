/*
Rewrite appropriate programs from earlier chapters and exercises
with pointers instead of array indexing. 

Good possibilities include:
 - getline (Ch. 1, 4)
 - atoi (Ch. 4)
 - itoa (Ch. 3)
 -> reverse (Ch. 3)
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

void exercise_reverse(char s[]) {
    int c;
    char *s0 = s;
    while (*(s+1))
        s++;
    for (; s0 < s; s0++, s--) {
        c = *s0;
        *s0 = *s;
        *s = c;
    }
}

int main() {
    char s[100] = "Hello World!";
    book_reverse(s);
    printf("%s\n", s);

    char s2[100] = "Hello World!";
    exercise_reverse(s2);
    printf("%s\n", s2);
}
