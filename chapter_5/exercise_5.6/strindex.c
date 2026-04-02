/*
Rewrite appropriate programs from earlier chapters and exercises
with pointers instead of array indexing. 

Good possibilities include:
 - getline (Ch. 1, 4)
 - atoi (Ch. 4)
 - itoa (Ch. 3)
 - reverse (Ch. 3)
 -> strindex (Ch. 4)
 - getop (Ch. 4)
*/

#include <stdio.h>

int book_strindex(char s[], char t[]) {
    int i, k;
    for (i = 0; s[i] != '\0'; i++) {
        for (k = 0; t[k] != '\0' && s[i+k] == t[k]; k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

int exercise_strindex(char *s, char *t) {
    char *si, *sipk, *tk;
    for (si = s; *si != '\0'; si++) {
        for (sipk = si, tk = t; *tk != '\0' && *sipk == *tk; sipk++, tk++)
            ;
        if (tk > t && *tk == '\0')
            return (si - s);
    }
    return -1;
}

int main() {
    char s[100] = "Hello World!";
    char t[100] = "World";
    printf("%d\n", book_strindex(s, t));
    printf("%d\n", exercise_strindex(s, t));
}
