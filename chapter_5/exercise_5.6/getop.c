/*
Rewrite appropriate programs from earlier chapters and exercises
with pointers instead of array indexing. 

Good possibilities include:
 - getline (Ch. 1, 4)
 - atoi (Ch. 4)
 - itoa (Ch. 3)
 - reverse (Ch. 3)
 - strindex (Ch. 4)
 -> getop (Ch. 4)
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define NUMBER 0
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int book_getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void book_ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void helper_clear(void) {
    bufp = 0;
}

int book_getop(char s[]) {
    int i, c;
    while ((s[0] = c = book_getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = book_getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = book_getch()))
    s[i] = '\0';
    if (c != EOF)
        book_ungetch(c);
    return NUMBER;
}

int exercise_getop(char *s) {
    char *s0 = s;
    int c;
    while ((*s = c = book_getch()) == ' ' || c == '\t')
        ;
    *++s = '\0';
    if (!isdigit(c) && c != '.')
        return c;
    s = s0;
    if (isdigit(c))
        while (isdigit(*++s = c = book_getch()))
            ;
    if (c == '.')
        while (isdigit(*++s = c = book_getch()))
    *s = '\0';
    if (c != EOF)
        book_ungetch(c);
    return NUMBER;
}

int main() {
    char s[100];
    int n = exercise_getop(s);
    printf("\n-----\n");
    printf("%d\n", n);
    printf("%s\n", s);
    printf("%lu\n", strlen(s));
}
