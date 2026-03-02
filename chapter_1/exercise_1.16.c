/*
Revise the main routine of the longest-line program so that it will 
correctly print the lengths of arbitrary length input lines, and so that it will
print as much as possible of the text.
*/

#include <stdio.h>
#define MAXLINE 10

int mygetline(char line[], int maxline);
void mycopy(char to[], char from[]);

int main() {
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = mygetline(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            mycopy(longest, line);
        }
    }
    printf("%s", longest);
    return 0;
}

int mygetline(char s[], int lim) {
    int i, c;

    i = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        if (i < lim - 1) {
            s[i] = c;
        }
        i++;
    }

    if (i > lim - 1) {
        s[lim - 1] = '\0';
    } else {
        s[i] = '\0';
    }
    return i;
}

void mycopy(char to[], char from[]) {
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0') {
        i++;
    }
}