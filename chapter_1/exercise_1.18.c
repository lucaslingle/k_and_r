/*
Write a program to remove trailing blanks and tabs from each line of input,
and to delete entirely blank lines.
*/

#include <stdio.h>
#define MAXLINE 1000

int mygetcleanline(char line[], int maxline);

int main() {
    int len, i;
    char line[MAXLINE];

    while ((len = mygetcleanline(line, MAXLINE)) > 0) {
        for (i = 0; i < len; i++) {
            putchar(line[i]);
        }
        putchar('\n');
    }
    return 0;
}

int mygetcleanline(char s[], int lim) {
    int i, c;
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    s[i] = '\0';

    i--;
    c = s[i];
    while (c == ' ' || c == '\t') {
        i--;
        c = s[i];
    }
    return i+1;
}
