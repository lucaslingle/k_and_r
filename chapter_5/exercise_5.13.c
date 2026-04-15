/*
Write the program tail, which prints the last n lines of its input.
By default n is 10, let us say, but it can be changed by an optional argument, 
so that
    tail -n
prints the last n lines. The program should behave rationally no matter how
unreasonable the input or the value of n. Write the program so that it makes 
the best use of available storage; lines should be stored as in the sorting program
of Section 5.6, not in a two-dimensional array of fixed size. 
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLINES 1000
#define MAXLEN 100
#define ALLOCSIZE 100000

int my_atoi(char *s);
int my_getline(char *s, int lim);

int main(int argc, char *argv[]) {
    int n = 10;
    if (argc > 1 && (*++argv)[0] == '-')
        n = -my_atoi(*argv);
    if (n > MAXLINES)
        printf("WARNING: Printing only the last %d lines\n", MAXLINES);
    n = (MAXLINES < n) ? MAXLINES : n;

    char buffer[ALLOCSIZE];
    char *tail = buffer;
    char *lineptrs[n];
    char temp[MAXLEN];
    int len;
    int i, j;
    for (i = 0; i < MAXLINES && (len = my_getline(temp, MAXLEN)) > 0; i++) {
        lineptrs[i % n] = tail;
        for (j = 0; j <= len; j++) { // includes ending null byte
            *tail = temp[j];
            tail++;
        }
    }
    for (int k = n-1; k >= 0; k--)
        printf("%s", lineptrs[(((i-1) % n) - k + n) % n]);
}

int my_atoi(char *s) {
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

int my_getline(char *s, int lim) {
    char *s0 = s;
    int c;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return (s - s0);
}
